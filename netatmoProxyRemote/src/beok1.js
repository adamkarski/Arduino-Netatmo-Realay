const dgram = require('dgram');
const crypto = require('crypto');

const IP = '192.168.8.5';
const KEY = Buffer.from('0123456789abcdef0123456789abcdef', 'hex'); // Domyślny

class BroadlinkOEMThermostat {
  constructor(ip, key = KEY) {
    this.ip = ip;
    this.key = key;
    this.client = null;
  }

  encrypt(data) {
    const iv = Buffer.alloc(16, 0);
    const cipher = crypto.createCipheriv('aes-128-cbc', this.key, iv);
    let encrypted = cipher.update(data);
    return Buffer.concat([encrypted, cipher.final()]);
  }

  async sendCommand(cmdBytes) {
    this.client = dgram.createSocket('udp4');
    const packet = Buffer.alloc(0x38, 0);
    packet.writeUInt32LE(0x5a5a5a5a, 0x00);
    packet.writeUInt32LE(0x00000000, 0x04);
    packet.writeUInt32LE(cmdBytes.length, 0x08);
    packet.writeUInt32LE(0x00000000, 0x0c);
    this.key.copy(packet, 0x10);

    const payload = Buffer.from(cmdBytes);
    const encrypted = this.encrypt(payload);
    encrypted.copy(packet, 0x20);

    return new Promise((resolve, reject) => {
      this.client.send(packet, 80, this.ip, (err) => {
        if (err) return reject(err);
        this.client.once('message', (msg) => resolve(msg));
        setTimeout(() => reject(new Error('Timeout')), 3000);
      });
    });
  }

  async getTemperature() {
    try {
      // Komendy z hass-floureon dla Beok OEM
      const response = await this.sendCommand([0x01, 0x11]); // Status
      if (response.length >= 0x26) {
        const tempRaw = response.readUInt16LE(0x1e); // Pozycja z komponentu
        const temp = (tempRaw & 0x7f) / 2; // /2 bo często ×2
        return temp.toFixed(1);
      }
      return null;
    } catch (e) {
      throw e;
    }
  }

  async getFullStatus() {
    try {
      const status = await this.sendCommand([0x01, 0x11]);
      console.log('Raw status (hex):', status.toString('hex'));
      
      // Parsowanie typowe dla Beok:
      const power = status[0x24] === 1 ? 'ON' : 'OFF';
      const mode = status[0x25]; // 0=off,1=heat,2=cool?
      const targetTemp = (status.readUInt16LE(0x1c) / 10).toFixed(1);
      const currentTemp = (status.readUInt16LE(0x1e) / 10).toFixed(1);
      
      return { power, mode: mode.toString(16), target: targetTemp, current: currentTemp };
    } catch (e) {
      console.error('Błąd statusu:', e);
      return null;
    }
  }
}

// TEST
(async () => {
  const thermo = new BroadlinkOEMThermostat(IP);
  try {
    console.log('=== BroadLink OEM-T1-54 (Beok) ===');
    const temp = await thermo.getTemperature();
    console.log(`Aktualna temperatura: ${temp || '❌ brak danych'}°C`);

    const status = await thermo.getFullStatus();
    console.log('Pełny status:', status);
  } catch (e) {
    console.error('❌ Błąd:', e.message);
    console.log('Spróbuj:');
    console.log('1. nmap -sU -p 80 192.168.8.5');
    console.log('2. Wyłącz firewall');
    console.log('3. Inny KEY? Wireshark podczas apki Beok Home');
  } finally {
    if (thermo.client) thermo.client.close();
  }
})();
