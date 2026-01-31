const dgram = require('dgram');
const fetch = require('node-fetch'); // npm i node-fetch

const IP = '192.168.8.5';
const MAC = 'c8f74254a747'; // mały hex

class OEMT1Thermostat {
  constructor(ip, mac) {
    this.ip = ip;
    this.mac = mac.replace(/:/g, '').toLowerCase();
  }

  // 1. HTTP temperature (jeśli dostępne)
  async getTemperatureHttp() {
    try {
      const res = await fetch(`http://${this.ip}:9876/temperature?deviceMac=${this.mac}`);
      const data = await res.json();
      return parseFloat(data.temperature);
    } catch {
      return null;
    }
  }

  // 2. UDP Broadlink AC (z repo broadlink_ac_mqtt)
  async getStatusUdp() {
    const client = dgram.createSocket('udp4');
    const cmd = Buffer.from([0xAA, 0x00, 0x06, 0xEC, 0x01, 0x00]); // Status request dla AC/T1
    const packet = Buffer.from([0xD0, 0x00, 0x00, 0x54, ...cmd]); // Prosty header

    return new Promise((resolve) => {
      client.send(packet, 80, this.ip, () => {
        client.once('message', (msg) => {
          // Parsuj: temp ~ bajt 10-11 /10 (z monitor.py)
          if (msg.length > 20) {
            const temp = msg.readUInt8(10) / 2; // Przykładowe
            resolve(temp);
          } else resolve(null);
        });
        setTimeout(() => client.close(), 2000);
      });
    });
  }

  async getAll() {
    console.log(`Testuję ${this.ip} (${this.mac})...`);
    const httpTemp = await this.getTemperatureHttp();
    if (httpTemp) {
      console.log(`✅ HTTP: ${httpTemp}°C`);
      return httpTemp;
    }

    const udpTemp = await this.getStatusUdp();
    if (udpTemp) console.log(`✅ UDP: ${udpTemp}°C`);
    else console.log('❌ Brak odpowiedzi');
  }
}

// Uruchom
(async () => {
  const thermo = new OEMT1Thermostat(IP, MAC);
  await thermo.getAll();
})();
