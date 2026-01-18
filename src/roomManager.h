#ifndef ROOMMANAGER_H
#define ROOMMANAGER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <EEPROM.h>
#include <vector>
#include <iostream>
#include <map>
#include <cstring>

// API endpoints
const char *api_url = "http://netatmo.dm73147.domenomania.eu/getdata";

struct RoomData
{
    char name[32];                    // Nazwa pokoju (char[] zamiast String)
    int ID;                           // ID pokoju
    int8_t pinNumber;                 // Numer przyporzadkowanego pinu (zmniejszono z int)
    float targetTemperatureNetatmo;   // Temperatura zadana Netatmo (Slider 1)
    float targetTemperatureFireplace; // Temperatura zadana Kominek (Slider 2)
    float currentTemperature;         // Temperatura aktualna
    bool forced;                      // Czy jest to tryb wymuszony
    char battery_state[12];           // Stan baterii
    uint16_t battery_level;           // Poziom baterii (zmniejszono z int)
    uint8_t rf_strength;              // Siła sygnału (zmniejszono z int)
    char type[16];                    // Typ pokoju
    bool reachable;                   // Czy pokój jest osiągalny
    char anticipating[16];            // Czy pokój jest w trybie oczekiwania
    float priority;                   // Priorytet pokoju
    bool valve;                       // Czy zawór jest otwarty (dla pokoju z najwyższym priorytetem)
    char valveMode[12];               // Tryb zaworu: "primary", "secondary", "off"
    std::vector<float> tempHistory;   // Historia temperatur (vector zamiast deque)

    RoomData() : ID(-1), pinNumber(0), targetTemperatureNetatmo(0.0), targetTemperatureFireplace(0.0), currentTemperature(0.0), forced(false), battery_level(0), rf_strength(0), reachable(false), priority(0), valve(false) 
    {
        name[0] = '\0';
        battery_state[0] = '\0';
        type[0] = '\0';
        anticipating[0] = '\0';
        strcpy(valveMode, "off");
    }

    RoomData(const char* name, int ID, int8_t pinNumber, float targetTemperatureNetatmo, float targetTemperatureFireplace, float currentTemperature, bool forced, const char* battery_state, uint16_t battery_level, uint8_t rf_strength, bool reachable, const char* anticipating, float priority = 0.0, bool valve = false, const char* valveMode = "off")
        : ID(ID), pinNumber(pinNumber), targetTemperatureNetatmo(targetTemperatureNetatmo), targetTemperatureFireplace(targetTemperatureFireplace), currentTemperature(currentTemperature), forced(forced), battery_level(battery_level), rf_strength(rf_strength), reachable(reachable), priority(priority), valve(valve) 
    {
        strncpy(this->name, name, sizeof(this->name) - 1); this->name[sizeof(this->name) - 1] = '\0';
        strncpy(this->battery_state, battery_state, sizeof(this->battery_state) - 1); this->battery_state[sizeof(this->battery_state) - 1] = '\0';
        // type nie jest przekazywany w konstruktorze w starym kodzie, ale warto go inicjalizować
        this->type[0] = '\0'; 
        strncpy(this->anticipating, anticipating, sizeof(this->anticipating) - 1); this->anticipating[sizeof(this->anticipating) - 1] = '\0';
        strncpy(this->valveMode, valveMode, sizeof(this->valveMode) - 1); this->valveMode[sizeof(this->valveMode) - 1] = '\0';
    }

    // Metoda do dodawania odczytu do historii
    void addHistory(float temp) {
        tempHistory.push_back(temp);
        // Przechowuj ostatnie 40 odczytów (przy odświeżaniu co ~65s daje to ok. 45 minut historii)
        if (tempHistory.size() > 40) {
            tempHistory.erase(tempHistory.begin()); // Usuń najstarszy element
        }
    }
};

class RoomManager
{
public:
    RoomManager() : requestInProgress(false)
    {
        // Inicjalizacja domyślnego mapowania ID na piny
        idToPinMap[1868270675] = 0; // ŁAZIENKA
        idToPinMap[206653929] = 1;  // KUCHNIA
        idToPinMap[1812451076] = 2; // AE SYPIALNIA
        idToPinMap[38038562] = 3;   // WALERIA
    }

    void addRoom(const RoomData &room)
    {
        rooms.push_back(room);
        Serial.print("Added room: ");
        Serial.println(room.name);
    }

    void updateOrAddRoom(const RoomData &room)
    {
        bool roomExists = false;
        for (auto &existingRoom : rooms)
        {
            if (existingRoom.ID == room.ID)
            {
                updateRoomParams(existingRoom, room);
                roomExists = true;
                Serial.print("Updated room: ");
                Serial.println(room.name);
                break;
            }
        }
        if (!roomExists)
        {
            addRoom(room);
        }
    }
    void resetAllValves()
    {
        for (auto &room : rooms)
        {
            room.valve = false;
            strcpy(room.valveMode, "off");
        }
    }
    void updateValveStatus(int roomId, bool valveState, String mode = "off")
    {
        // Iterujemy przez wektor pokoi (potrzebujemy dostępu do modyfikacji)
        for (auto &room : rooms)
        { // 'rooms' jest prywatnym członkiem klasy
            if (room.ID == roomId)
            {
                if (room.valve != valveState || strcmp(room.valveMode, mode.c_str()) != 0)
                { // Aktualizuj i loguj tylko jeśli stan się zmienia
                    room.valve = valveState;
                    strncpy(room.valveMode, mode.c_str(), sizeof(room.valveMode) - 1); room.valveMode[sizeof(room.valveMode) - 1] = '\0';
                    Serial.printf("  [Valve Update] Room %d (%s) valve set to %s\n",
                                  roomId, room.name, valveState ? "ON" : "OFF");
                }
                break; // Znaleziono pokój, można przerwać pętlę
            }
        }
    }
    void updateRoomParams(RoomData &existingRoom, const RoomData &newRoom)
    {
        // Update Netatmo target temp if provided in newRoom (usually from fetchJsonData)
        // Only update if the value is significantly different to avoid floating point noise if needed, or just update if non-zero
        if (newRoom.targetTemperatureNetatmo != 0.0) // Or use a small epsilon comparison if needed
            existingRoom.targetTemperatureNetatmo = newRoom.targetTemperatureNetatmo;

        // Allow updating fireplace target (e.g. from EEPROM load or explicit update)
        existingRoom.targetTemperatureFireplace = newRoom.targetTemperatureFireplace;

        // Aktualizacja nazwy pokoju
        if (strlen(newRoom.name) > 0) {
            strncpy(existingRoom.name, newRoom.name, sizeof(existingRoom.name) - 1);
            existingRoom.name[sizeof(existingRoom.name) - 1] = '\0';
        }
        if (newRoom.ID != -1)
            existingRoom.ID = newRoom.ID;
        if (newRoom.pinNumber != 0) // Keep existing pin if new one is 0
            existingRoom.pinNumber = newRoom.pinNumber;

        if (newRoom.currentTemperature != 0.0) { // Or use epsilon comparison
            existingRoom.currentTemperature = newRoom.currentTemperature;
            existingRoom.addHistory(newRoom.currentTemperature); // Dodaj do historii
        }
        if (strlen(newRoom.battery_state) > 0) {
            strncpy(existingRoom.battery_state, newRoom.battery_state, sizeof(existingRoom.battery_state) - 1);
            existingRoom.battery_state[sizeof(existingRoom.battery_state) - 1] = '\0';
        }
        if (newRoom.battery_level != 0)
            existingRoom.battery_level = newRoom.battery_level;
        if (newRoom.rf_strength != 0)
            existingRoom.rf_strength = newRoom.rf_strength;
        // Always update reachable status
        existingRoom.reachable = newRoom.reachable;
        if (strlen(newRoom.anticipating) > 0) {
            strncpy(existingRoom.anticipating, newRoom.anticipating, sizeof(existingRoom.anticipating) - 1);
            existingRoom.anticipating[sizeof(existingRoom.anticipating) - 1] = '\0';
        }
        // Always update forced status from newRoom data (usually comes from WebSocket update)

        existingRoom.forced = newRoom.forced;
        if (newRoom.valve != existingRoom.valve)
        {
            existingRoom.valve = newRoom.valve;
            strncpy(existingRoom.valveMode, newRoom.valveMode, sizeof(existingRoom.valveMode) - 1); existingRoom.valveMode[sizeof(existingRoom.valveMode) - 1] = '\0';
        }

        // Priority calculation might need adjustment based on which target temp is relevant
        // For now, let's keep it based on Netatmo target, logic in main.cpp will use effective target.
        // Or maybe calculate based on fireplace target? Let's stick to Netatmo for now for the stored 'priority' value.
        existingRoom.priority = existingRoom.targetTemperatureNetatmo - existingRoom.currentTemperature;
    }

    RoomData& getRoom(size_t index)
    {
        if (index < rooms.size())
        {
            return rooms[index];
        }
        else
        {
            Serial.println("Index out of range");
            static RoomData empty; return empty; // Zwraca pusty RoomData w przypadku błędu (bezpieczniej niż kopia)
        }
    }

    // get room by ID - returns pointer to avoid copy and allow nullptr check
    RoomData* getRoomByID(int roomID)
    {
        for (auto &room : rooms)
        {
            if (room.ID == roomID)
            {
                return &room;
            }
        }
        Serial.println("Room ID not found");
        return nullptr;
    }

    void updateRoom(size_t index, const RoomData &room)
    {
        if (index < rooms.size())
        {
            rooms[index] = room;
        }
        else
        {
            Serial.println("Index out of range");
        }
    }

    bool isRequestInProgress() const
    {
        return requestInProgress;
    }

    void setRequestInProgress(bool inProgress)
    {
        requestInProgress = inProgress;
    }

    String getRoomsAsJson()
    {
        // Zwiększono rozmiar dokumentu, aby bezpiecznie zmieścić dane wszystkich pokoi i metadane.
        DynamicJsonDocument docx(4096);
        JsonArray roomsArray = docx.createNestedArray("rooms");

        for (const auto &room : rooms)
        {
            JsonObject roomObject = roomsArray.createNestedObject();
            roomObject["name"] = room.name;
            roomObject["id"] = room.ID;
            roomObject["pinNumber"] = room.pinNumber;
            roomObject["targetTemperatureNetatmo"] = room.targetTemperatureNetatmo;
            roomObject["targetTemperatureFireplace"] = room.targetTemperatureFireplace; // Add fireplace target
            roomObject["currentTemperature"] = room.currentTemperature;
            roomObject["forced"] = room.forced;
            roomObject["battery_state"] = room.battery_state;
            roomObject["battery_level"] = room.battery_level;
            roomObject["rf_strength"] = room.rf_strength;
            roomObject["reachable"] = room.reachable;
            roomObject["anticipating"] = room.anticipating;
            // Priority sent is based on Netatmo target, actual logic uses effective target
            roomObject["priority"] = room.targetTemperatureNetatmo - room.currentTemperature;
            roomObject["valve"] = room.valve;
            roomObject["valveMode"] = room.valveMode;

            // Dodaj historię do JSON
            JsonArray history = roomObject.createNestedArray("history");
            for (float t : room.tempHistory) {
                // Zaokrąglij do 1 miejsca po przecinku, aby zmniejszyć rozmiar JSON (np. 13.3999 -> 13.4)
                history.add(round(t * 10.0) / 10.0);
            }
        }

        // Zamiast kopiować cały obiekt docPins (co jest ryzykowne ze względu na rozmiar),
        // dodajemy tylko potrzebne pola do obiektu "meta".
        JsonObject meta = docx.createNestedObject("meta");
        meta["manifoldMinTemp"] = docPins["manifoldMinTemp"];
        meta["manifoldTemp"] = docPins["manifoldTemp"];
        meta["boostEnabled"] = docPins["boostEnabled"];
        meta["usegaz"] = docPins["usegaz"];
        // Upewnij się, że inne potrzebne wartości (np. boostThreshold) są również dodawane do docPins lub przekazywane tutaj.

        String jsonString;

        serializeJson(docx, jsonString);
        // Serial.println(jsonString);
        return jsonString;
    }

    // Sets Netatmo target temperature and updates proxy
    void setTemperature(int roomID, float temp)
    {
        // Update local Netatmo target first
        bool roomFound = false;
        for (auto &room : rooms)
        {
            if (room.ID == roomID)
            {
                room.targetTemperatureNetatmo = temp;
                roomFound = true;
                break;
            }
        }
        if (!roomFound)
        {
            Serial.printf("Room ID %d not found locally for setTemperature.\n", roomID);
            // Optionally handle this case, maybe fetch data first?
        }

        Serial.printf("Setting Netatmo temperature for room %d to %.1f\n", roomID, temp);

        if (WiFi.status() == WL_CONNECTED)
        {
            WiFiClient client;

            HTTPClient http;

            // Note: Using String() for float conversion might lose precision, consider dtostrf if needed
            String url = "http://netatmo.dm73147.domenomania.eu/setRoomTemperature?mode=manual&temperature=" + String(temp, 1) + "&room_id=" + String(roomID);
            http.begin(client, url);
            int httpCode = http.GET();

            Serial.printf("Netatmo proxy setTemperature request code: %d\n", httpCode);
            Serial.printf("URL: %s\n", url.c_str());

            Serial.println(http.getString());

            http.end(); // Dodano http.end()

            // Pobierz aktualne dane po zmianie temperatury
            // Consider adding error handling based on httpCode
            if (httpCode < 0)
            {
                Serial.printf("HTTP GET request failed, error: %s\n", http.errorToString(httpCode).c_str());
            }
            else
            {
                Serial.println(http.getString()); // Print proxy response
            }

            http.end(); // Dodano http.end()

            // Fetch updated data from Netatmo after setting temperature
            // Maybe add a small delay before fetching?
            // delay(1000); // Optional delay
            fetchJsonData(api_url); // Refresh local data

            // Data will be broadcasted by the timer in main.cpp
        }
        else
        {
            Serial.println("WiFi not connected, cannot set Netatmo temperature.");
        }
    }

    // Sets Fireplace target temperature locally ONLY
    void setFireplaceTemperature(int roomID, float temp)
    {
        bool roomFound = false;
        for (auto &room : rooms)
        {
            if (room.ID == roomID)
            {
                room.targetTemperatureFireplace = temp;
                roomFound = true;
                Serial.printf("Set fireplace target for room %d to %.1f\n", roomID, temp);
                break;
            }
        }
        if (!roomFound)
        {
            Serial.printf("Room ID %d not found locally for setFireplaceTemperature.\n", roomID);
        }
        // No need to call Netatmo or fetch data here
        // Data will be broadcasted by the timer in main.cpp
    }

    void fetchJsonData(const char *url)
    {

        if (isRequestInProgress())
        {
            Serial.println("Request already in progress");
            return;
        }

        setRequestInProgress(true);
        Serial.println("Fetching JSON data from API");

        if (WiFi.status() == WL_CONNECTED)
        {
            WiFiClient client;

            HTTPClient http;
            http.setTimeout(2500); // Zmniejszono timeout do 2.5s (bezpieczne dla WDT)
            http.begin(client, url);
            int httpCode = http.GET();

            Serial.printf("HTTP GET request code: %d\n", httpCode);

            if (httpCode > 0)
            {
                // OPTYMALIZACJA: Zamiast pobierać cały String (payload), parsujemy strumieniowo.
                // To oszczędza mnóstwo pamięci RAM i zapobiega fragmentacji.
                DynamicJsonDocument doc(5120); // Zmniejszono do 5KB dla bezpieczeństwa pamięci
                
                // Używamy http.getStream() zamiast http.getString()
                DeserializationError error = deserializeJson(doc, http.getStream());

                if (error) {
                    Serial.print(F("Błąd podczas parsowania JSON z API Netatmo: "));
                    Serial.println(error.c_str());
                    setRequestInProgress(false);
                    return;
                }

                    //       "id": "1812451076",
                    //       "reachable": true,
                    //       "anticipating": null,
                    //       "open_window": null,
                    //       "therm_measured_temperature": 15.4,
                    //       "therm_setpoint_temperature": 12.5,
                    //       "therm_setpoint_mode": "away",
                    //       "name": "Łazienka",
                    //       "type": "bathroom",
                    //       "battery_state": "full",
                    //       "battery_level": 4160,
                    //       "rf_strength": 71
                    //     },
                JsonArray rooms = doc["rooms"];
                if (!rooms.isNull()) {
                    for (JsonObject room : rooms)
                    {
                        const char* namePtr = room["name"].as<const char*>();
                        const char* name = namePtr ? namePtr : "Unknown";
                        
                        int id = room["id"].as<int>();
                        float currentTemperature = room["therm_measured_temperature"].as<float>();
                        float targetTemperatureNetatmo = room["therm_setpoint_temperature"].as<float>(); // This is Netatmo's target
                        // Preserve existing forced status and fireplace target
                        bool forced = false;
                        float targetTemperatureFireplace = 0.0; // Default if room doesn't exist yet
                        int8_t existingPinNumber = 0;           // Default pin

                        // Sprawdź, czy pokój już istnieje w naszej kolekcji
                        for (const auto &existingRoom : this->rooms)
                        {
                            if (existingRoom.ID == id)
                            {
                                forced = existingRoom.forced;                                         // Keep existing forced status
                                targetTemperatureFireplace = existingRoom.targetTemperatureFireplace; // Keep existing fireplace target
                                existingPinNumber = existingRoom.pinNumber;                           // Keep existing pin number
                                break;                                                                // Found the existing room
                            }
                        }

                        const char* battery_state = room["battery_state"].as<const char *>();
                        uint16_t battery_level = room["battery_level"].as<uint16_t>();
                        uint8_t rf_strength = room["rf_strength"].as<uint8_t>();
                        const char* type = room["type"].as<const char *>();
                        bool reachable = room["reachable"].as<bool>();
                        const char* anticipating = room["anticipating"].as<const char *>();
                        // Priority calculation is done in updateRoomParams

                        // Determine pin number: use existing if available, otherwise map from ID
                        int8_t pinNumber = (existingPinNumber != 0) ? existingPinNumber : (int8_t)this->idToPinMap[id];
                        if (pinNumber == 0 && existingPinNumber == 0)
                        { // Check if ID was not in map initially
                            Serial.printf("Warning: No pin mapping found for new room ID %d. Defaulting to 0.\n", id);
                        }

                        // Create RoomData object with both temperatures
                        RoomData fetchedRoom(name, id, pinNumber, targetTemperatureNetatmo, targetTemperatureFireplace, currentTemperature, forced, battery_state, battery_level, rf_strength, reachable, anticipating);
                        
                        // Set type separately as it's not in constructor
                        if (type) { strncpy(fetchedRoom.type, type, sizeof(fetchedRoom.type)-1); fetchedRoom.type[sizeof(fetchedRoom.type)-1] = '\0'; }

                        // Update or add the room
                        updateOrAddRoom(fetchedRoom);
                    }
                }
            }
            else
            {
                Serial.printf("HTTP GET request failed, error: %s\n", http.errorToString(httpCode).c_str());
            }
            http.end();
        }
        else
        {
            Serial.println("WiFi not connected");
        }

        setRequestInProgress(false);
    }

    std::map<int, int8_t> idToPinMap; // Przenieś mapowanie tutaj, zoptymalizowano typ wartości

    void updatePinMapping(int roomId, int newPin)
    {
        idToPinMap[roomId] = newPin;
        // Zaktualizuj też pin w odpowiednim pokoju
        for (auto &room : rooms)
        {
            if (room.ID == roomId)
            {
                room.pinNumber = newPin;
                break;
            }
        }
    }

    // Dodaj metodę do serializacji mapowania pinów
    String getPinMappingAsJson()
    {
        DynamicJsonDocument doc(1024);
        JsonArray mappings = doc.createNestedArray("pinMappings");

        for (const auto &room : rooms)
        {
            JsonObject mapping = mappings.createNestedObject();
            mapping["roomId"] = room.ID;
            mapping["name"] = room.name;
            mapping["pin"] = room.pinNumber;
        }

        String jsonString;
        serializeJson(doc, jsonString);
        return jsonString;
    }

    // Metoda zwracająca referencję do wektora pokoi
    const std::vector<RoomData> &getAllRooms() const
    {
        return rooms;
    }

    // Metoda zwracająca liczbę pokoi
    size_t getRoomCount() const
    {
        return rooms.size();
    }

private:
    std::vector<RoomData> rooms;
    bool requestInProgress;
};

#endif