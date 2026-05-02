# IoT Temperature & Humidity Monitoring with MQTT & Node-RED

Proyek ini mendemonstrasikan sistem monitoring suhu dan kelembapan menggunakan sensor **DHT22** dan kontrol **LED** secara remote melalui protokol komunikasi **MQTT**. Proyek ini disimulasikan menggunakan **Wokwi** dengan metode upload program menggunakan **Binary File (.bin)**.[cite: 1, 2]

---

## 🚀 Fitur Utama
* **Monitoring Real-time**: Membaca data suhu dan kelembapan dari sensor DHT22.[cite: 1]
* **Protokol MQTT**: Mengirimkan data dalam format string tunggal dan format JSON ke broker EMQX.[cite: 1]
* **Kontrol LED**: Mengendalikan status LED (ON/OFF) melalui dashboard Node-RED.[cite: 1]
* **Dashboard Node-RED**: Visualisasi data menggunakan gauge dan chart yang interaktif.[cite: 1]

---

## 🛠️ Skema Wiring (Simulasi Wokwi)
Penyusunan komponen pada ESP32 dilakukan sebagai berikut:[cite: 1, 2]

| Komponen | Pin ESP32 | Keterangan |
| :--- | :--- | :--- |
| **DHT22 (Data)** | GPIO 14 | Input Sensor |
| **LED (Anoda)** | GPIO 2 | Output Kontrol |
| **VCC** | 3.3V | Catu Daya |
| **GND** | GND | Ground |

![Wiring Diagram](image_a4efbd.png)
*Gambar 1: Tata letak komponen pada simulator Wokwi.*

---

## 📂 Dokumentasi Lengkap (PDF)
Untuk penjelasan mendalam mengenai langkah-langkah teknis, silakan unduh dokumen berikut:

👉 **[Download Dokumentasi_Proyek_IoT.pdf](docs/Dokumentasi_Proyek_IoT.pdf)**

---

## ⚙️ Cara Membuat Binary File (.bin)
Untuk menjalankan simulasi di Wokwi tanpa kode sumber, ikuti langkah ini di Arduino IDE:[cite: 1, 2]

1.  Buka file sketsa (`.ino`).
2.  Pilih board: **Tools** > **Board** > **ESP32** > **ESP32 Dev Module**.
3.  Klik menu **Sketch** > **Export Compiled Binary**.[cite: 1, 2]
4.  File `.bin` akan muncul di folder proyek Anda (biasanya di dalam folder `build`).[cite: 1, 2]

![Export Binary](image_a4ef7f.png)
*Gambar 2: Proses export binary di Arduino IDE.*[cite: 2]

---

## 📊 Integrasi Node-RED
Sistem mengirimkan data ke topic `bdur/dht` dalam format JSON. Node-RED kemudian melakukan *parsing* data untuk ditampilkan pada dashboard.[cite: 1, 2]

**Topic MQTT:**
* `bdur/temperature`: Data suhu (String)[cite: 1]
* `bdur/humidity`: Data kelembapan (String)[cite: 1]
* `bdur/dht`: Data suhu & kelembapan (JSON)[cite: 1]
* `bdur/led`: Kontrol lampu (1=ON, 0=OFF)[cite: 1]

![Node-RED Dashboard](image_a4ef9f.png)
*Gambar 3: Tampilan dashboard monitoring dan flow Node-RED.*[cite: 2]

---

## 👨‍💻 Author
**Abdurrahman**
*   IoT Engineer & Educator
*   Bogor/Sentul, Indonesia
