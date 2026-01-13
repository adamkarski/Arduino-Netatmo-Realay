
const fs = require('fs');
const path = require('path');
const axios = require('axios');


const config = JSON.parse(fs.readFileSync(path.join(__dirname, 'config.json')));



//The enrich_rooms_with_battery_state function would need to be translated to javascript.
function extractBatteryState(data) {
  // Create a dictionary to map module IDs to battery states
  const modules = {};

  // Safe access to homestatus modules
  const homeStatusBody = data?.meta?.homestatus?.body?.home;
  if (homeStatusBody && Array.isArray(homeStatusBody.modules)) {
    homeStatusBody.modules.forEach((module) => {
      if (module.battery_state) {
        modules[module.id] = module;
        /*   
        
        id: '04:00:00:6d:61:08',
        type: 'NATherm1',
        battery_state: 'very_low',
        battery_level: 2551,
        reachable: false, 
        
      */
      }
    });
  }

  // Safe access to homesdata rooms
  const homesDataBody = data?.meta?.homesdata?.body?.homes;
  // Check if homes array exists and has at least one element
  const homesRooms = (homesDataBody && homesDataBody.length > 0) ? homesDataBody[0].rooms : null;

  if (homesRooms && Array.isArray(homesRooms)) {
    homesRooms.forEach((room) => {
      if (room.module_ids && Array.isArray(room.module_ids)) {
        room.module_ids.forEach((module_id) => {
          if (modules[module_id]) {
            // room.battery_state = modules[module_id].battery_state;
            // ... (local update commented out in original, keeping logic clean)
            
            // Update combined rooms in data.rooms
            if (data.rooms && Array.isArray(data.rooms)) {
              data.rooms.forEach((roomO) => {
                if (roomO.id === room.id) {
                  roomO.battery_state = modules[module_id].battery_state;
                  roomO.battery_level = modules[module_id].battery_level;
                  roomO.rf_strength = modules[module_id].rf_strength;
                  roomO.reachable = modules[module_id].reachable;
                  roomO.firmware_revision = modules[module_id].firmware_revision;
                }
              });
            }
          }
        });
      } else {
        // If room has no module_ids or it's not an array
        if (data.rooms && Array.isArray(data.rooms)) {
           data.rooms.forEach((roomO) => {
                if (roomO.id === room.id) {
                  roomO.warning = "No module_ids found for this room";
                }
           });
        }
      }
    });
  } else {
    // If homesdata rooms are missing, mark error in output
    if (data.rooms && Array.isArray(data.rooms)) {
       data.rooms.forEach(r => r.error_config = "Missing homesdata configuration");
    }
  }

  // Create a dictionary to map module IDs to room IDs
 /*  const module_to_room = {};
  data.homesdata.body.homes.forEach((home) => {
    home.rooms.forEach((room) => {
      room.module_ids.forEach((module_id) => {
        module_to_room[module_id] = room.id;
      });
    });
  }); */

  // // Iterate through the rooms and add the battery state
  // data.rooms.forEach((room) => {
  //   const roomId = room.id;
  //   let battery_state = null;

  //   // Find the module IDs associated with the room
  //   const module_ids_in_room = Object.keys(module_to_room).filter(
  //     (module_id) => module_to_room[module_id] === roomId
  //   );

  //   // If there are modules in the room, get the battery state of the first thermostat
  //   if (module_ids_in_room.length > 0) {
  //     const module_id = module_ids_in_room[0]; // Take the first module ID
  //     battery_state = module_battery_states[module_id] || null;
  //   }

  //   // Add the battery state to the room
  //   room.battery_state = battery_state;
  // });
// console.log(data);
  return data;
}


function filterHomestatusData(data) {
  if (!data || !data.body || !data.body.home || !data.body.home.rooms) {
    return [];
  }

  return data.body.home.rooms.map(room => ({
    id: room.id || null,
    reachable: room.reachable || null,
    anticipating: room.anticipating || null,
    // heating_power_request: room.heating_power_request || null,
    open_window: room.open_window || null,
    therm_measured_temperature: room.therm_measured_temperature || null,
    therm_setpoint_temperature: room.therm_setpoint_temperature || null,
    therm_setpoint_mode: room.therm_setpoint_mode || null
  }));
}

function filterHomesdata(data) {
  if (!data || !data.body || !data.body.homes || data.body.homes.length === 0 || !data.body.homes[0].rooms) {
    return [];
  }

  return data.body.homes[0].rooms.map(room => ({
    id: room.id || null,
    name: room.name || null,
    type: room.type || null
  }));
}

function combineRoomData(homestatusRooms, homesdataRooms) {
  const statusRooms = Array.isArray(homestatusRooms) ? homestatusRooms : [];
  const configRooms = Array.isArray(homesdataRooms) ? homesdataRooms : [];

  // If status is missing but config exists, return config with error
  if (statusRooms.length === 0 && configRooms.length > 0) {
    return configRooms.map(room => ({
      ...room,
      error: "Missing homestatus data from Netatmo"
    }));
  }

  return statusRooms.map(statusRoom => {
    const dataRoom = configRooms.find(room => room.id === statusRoom.id) || { warning: "Missing room config" };
    return { ...statusRoom, ...dataRoom };
  });
}

module.exports = { filterHomestatusData, filterHomesdata, combineRoomData , extractBatteryState};