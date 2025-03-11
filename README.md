# PDF Booklet Creator

PDF Booklet Creator adalah aplikasi GUI berbasis GTK untuk mengatur parameter dan membuat booklet dari file PDF menggunakan `pdfbook2`.

## Fitur
- Memilih file PDF melalui file chooser.
- Mengatur parameter booklet seperti ukuran kertas, margin, dan signature.
- Eksekusi otomatis perintah `pdfbook2`.

## Persyaratan
Sebelum menggunakan aplikasi ini, pastikan telah menginstal:
- `g++`
- `GTK+ 3` atau `GTK+ 4`
- `pdfbook2`

Untuk menginstal GTK+ dan pdfbook2 di Ubuntu/Debian:
```sh
sudo apt install g++ libgtk-3-dev texlive-extra-utils
```

## Cara Kompilasi
Gunakan perintah berikut untuk mengompilasi kode:
```sh
g++ -o pdfbooklet main.cpp `pkg-config --cflags --libs gtk+-3.0`
```
Atau jika menggunakan GTK4:
```sh
g++ -o pdfbooklet main.cpp `pkg-config --cflags --libs gtk4`
```

## Cara Menjalankan
Jalankan program dengan perintah:
```sh
./pdfbooklet
```

## Penggunaan
1. Masukkan parameter booklet sesuai kebutuhan.
2. Klik tombol "Select PDF Files".
3. Pilih file PDF yang ingin dikonversi.
4. Program akan menjalankan `pdfbook2` secara otomatis dengan parameter yang telah diatur.

## Lisensi
Proyek ini dirilis di bawah lisensi MIT.


