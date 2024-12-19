# Tugas 6 Sistem Mikroprosesor : Wireless ESP32
Kode pada tugas ini dibuat untuk compiler Arduino IDE menggunakan bahasa C-Lite.

## 1. ESP32 sebagai Bluetooth
**Deskripsi :**
ESP32 digunakan fitur Bluetooth-nya untuk disambungkan pada perangkat lain. Terdapat 2 buah fungsi utama yang dirancang pada program ini, yaitu :
  a) Output LED dengan input serial pada perangkat yang disambung dengan Bluetooth
  b) Input tombol untuk mengeluarkan output serial pada perangkat yang disambung dengan Bluetooth

## 2. ESP32 sebagai WiFi Client
**Deskripsi :**
ESP32 akan disambungkan pada WiFi dan menjalankan web server untuk melihat keterhubungan antara WiFi dan ESP32.

## 3. ESP32 sebagai Access Point
**Deskripsi :**
ESP32 akan digunakan sebagai perangkat WiFi (access point) untuk menjalankan web server. Nama access point yang digunakan sesuai dengan nama/NIM kelompok.

## 4. Web Server dengan Library WiFiServer
**Deskripsi :**
Sebuah web server dirancang dengan library WiFiServer yang dapat minimal menampilkan nama/NIM anggota kelompok.

## 5. Web Server dengan Library ESPAsyncWebServer
**Deskripsi :**
Sebuah web server dirancang dengan library ESPAsyncWebServer yang dapat minimal menampilkan nama/NIM anggota kelompok.

## 6. Form HTML dan ESP32 Web Server
**Deskripsi :**
Form HTML dihubungkan dengan web server ESP32 dengan isi form terdiri atas parameter lampu kedip (durasi ON & OFF).

## 7. Form HTML dan ESP32 Web Server dengan Penyimpanan EEPROM/Flash
**Deskripsi :**
Form HTML dengan parameter sama seperti modul sebelumnya dirancang dengan penyimpanan parameter pada EEPROM/Flash.
