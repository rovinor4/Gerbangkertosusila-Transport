# Gerbangkertosusila Transport

<img src="AboutImage.png" style="border-radius: 20px;">

Gerbangkertosusila Transport adalah project C++ berbasis Abstract Data Type (ADT) yang mengimplementasikan multi linked list dengan relasi M ke N.
Project ini memodelkan hubungan antara alat transportasi darat dan daerah pada wilayah Gerbangkertosusila.

---
## Kontribusi

<p style="font-size: 15px;">Rovino Ramadhani (103072400031)</p>

---
## 📌 Project Information

Course : Struktur Data
Programming Language : C++

Concepts Used  
- Abstract Data Type (ADT)  
- Single Linked List  
- Double Linked List  
- Multi Linked List (M to N Relation)  
- Pointer based data structure  

Case Study  
Transportasi darat penghubung wilayah Gerbangkertosusila seperti Surabaya, Sidoarjo, Gresik, Mojokerto, dan Lamongan.

---

## 📂 Project Structure

Gerbangkertosusila Transport/
- common.h
- transport.h
- transport.cpp
- region.h
- region.cpp
- relation.h
- relation.cpp
- main.cpp
- README.md

---

## 📄 File Description

### common.h
Header umum berisi include standar dan using namespace std untuk menghindari include berulang.

### transport.h / transport.cpp
Mengelola data alat transportasi menggunakan double linked list.
Menyediakan fungsi insert, delete, search, dan display data transport.

### region.h / region.cpp
Mengelola data daerah menggunakan single linked list.
Setiap node region memiliki list relasi ke transport.

### relation.h / relation.cpp
Mengelola relasi M ke N antara region dan transport menggunakan pointer.

### main.cpp
Program utama berbasis menu terminal interaktif dengan data dummy otomatis.

---

## ⚙️ How to Run

1. Pastikan seluruh file berada dalam satu folder
2. Compile seluruh file .cpp
3. Jalankan program melalui terminal atau IDE
