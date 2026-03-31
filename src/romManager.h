#ifndef ROMMANAGER_H
#define ROMMANAGER_H

#include <Arduino.h>
#include <EEPROM.h>
#include "roomManager.h"

// --- EEPROM Settings ---
#define MAX_ROOMS_EEPROM 10
const byte EEPROM_MAGIC_VALUE = 0xAD; // Zmieniono magic value, aby wymusić re-inicjalizację po zmianie struktury

// Define EEPROM Addresses - START AT 1024 to avoid IotWebConf collision
const int ADDR_EEPROM_START = 1024;
const int ADDR_MAGIC = ADDR_EEPROM_START;
const int ADDR_USE_GAZ = ADDR_MAGIC + sizeof(byte);
const int ADDR_MIN_OPERATING_TEMP = ADDR_USE_GAZ + sizeof(bool);
const int ADDR_BOOST_ENABLED = ADDR_MIN_OPERATING_TEMP + sizeof(float);
const int ADDR_ROOM_COUNT = ADDR_BOOST_ENABLED + sizeof(bool);
const int ADDR_ROOM_DATA_START = ADDR_ROOM_COUNT + sizeof(byte);

const int ROOM_DATA_SIZE = sizeof(int) + sizeof(int8_t) + sizeof(bool) + sizeof(float);
const int EEPROM_SIZE = 2048; // Zwiększono całkowity rozmiar EEPROM

void saveSettings(const RoomManager &mgr, bool currentUseGaz, float manifoldMinTemp, bool boostEnabled) {
  Serial.println("Saving settings to EEPROM...");
  // Bufor jest już zainicjowany w setup()

  EEPROM.put(ADDR_MAGIC, EEPROM_MAGIC_VALUE);
  EEPROM.put(ADDR_USE_GAZ, currentUseGaz);
  EEPROM.put(ADDR_MIN_OPERATING_TEMP, manifoldMinTemp);
  EEPROM.put(ADDR_BOOST_ENABLED, boostEnabled);

  const std::vector<RoomData> &currentRooms = mgr.getAllRooms();
  byte roomCountToSave = min((byte)currentRooms.size(), (byte)MAX_ROOMS_EEPROM);
  EEPROM.put(ADDR_ROOM_COUNT, roomCountToSave);

  int currentAddr = ADDR_ROOM_DATA_START;
  for (byte i = 0; i < roomCountToSave; ++i) {
    const RoomData &room = currentRooms[i];
    EEPROM.put(currentAddr, room.ID);
    currentAddr += sizeof(int);
    EEPROM.put(currentAddr, room.pinNumber);
    currentAddr += sizeof(int8_t);
    EEPROM.put(currentAddr, room.forced);
    currentAddr += sizeof(bool);
    EEPROM.put(currentAddr, room.targetTemperatureFireplace);
    currentAddr += sizeof(float);
  }

  if (!EEPROM.commit()) {
    Serial.println("EEPROM commit failed!");
  } else {
    Serial.println("Settings saved successfully");
  }
  // Nie używamy EEPROM.end(), aby nie zwalniać bufora współdzielonego z IotWebConf
}

bool loadSettings(RoomManager &mgr, bool &outUseGaz, float &outManifoldTemp, bool &outBoostEnabled) {
  Serial.println("Loading settings from EEPROM...");
  // Bufor jest już zainicjowany w setup()

  byte magic = 0;
  EEPROM.get(ADDR_MAGIC, magic);
  if (magic != EEPROM_MAGIC_VALUE) {
    Serial.println("No valid settings found in EEPROM");
    return false;
  }

  EEPROM.get(ADDR_USE_GAZ, outUseGaz);
  EEPROM.get(ADDR_MIN_OPERATING_TEMP, outManifoldTemp);
  EEPROM.get(ADDR_BOOST_ENABLED, outBoostEnabled);

  byte roomCount = 0;
  EEPROM.get(ADDR_ROOM_COUNT, roomCount);
  if (roomCount > MAX_ROOMS_EEPROM) roomCount = MAX_ROOMS_EEPROM;

  int currentAddr = ADDR_ROOM_DATA_START;
  for (byte i = 0; i < roomCount; ++i) {
    int id = -1;
    int8_t pin = 0;
    bool forced = false;
    float temp = 0.0;

    EEPROM.get(currentAddr, id);
    currentAddr += sizeof(int);
    EEPROM.get(currentAddr, pin);
    currentAddr += sizeof(int8_t);
    EEPROM.get(currentAddr, forced);
    currentAddr += sizeof(bool);
    EEPROM.get(currentAddr, temp);
    currentAddr += sizeof(float);

    RoomData room;
    room.ID = id;
    room.pinNumber = pin;
    room.forced = forced;
    room.targetTemperatureFireplace = temp;
    mgr.updateOrAddRoom(room);
  }

  return true;
}

#endif