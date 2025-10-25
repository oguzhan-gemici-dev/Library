# Library
C-based CLI Library Management System demonstrating File I/O for data persistence and Array Compaction logic.
# 📚 Basit Kütüphane Yönetim Sistemi (CLI)

> **Proje Özeti:** C programlama dili kullanılarak geliştirilmiş, kütüphane portalının temel kataloglama ve stok takibi işlevlerini simüle eden bir Komut Satırı Arayüzü (CLI) uygulamasıdır. Veri kalıcılığı için yerel dosya (TXT) yönetimi kullanılır.

---

## ✨ Projenin Amacı ve Öne Çıkan Özellikler

Bu proje, bir stajyer adayının temel sistem yönetimi, veri yapısı ve algoritma bilgisini göstermek amacıyla C dilinin temel yetenekleri kullanılarak geliştirilmiştir.

### Temel Fonksiyonlar

1.  **Yeni Kitap Ekleme:** Benzersiz ID ataması ve stok (toplam/kullanılabilir adet) kaydı.
2.  **Tüm Kitapları Listeleme:** Katalogdaki tüm kitapların formatlı çıktısı.
3.  **Kitap Arama:** Kitap Adı veya Yazar Adına göre esnek arama.
4.  **Kitap Silme:** ID'ye göre silme işlemi.
5.  **Veri Kaydetme/Yükleme:** Program kapatıldığında verileri `.txt` dosyasına kaydetme ve açılışta yükleme.

### 💡 Uygulanan Kritik C Becerileri ve Algoritmalar

* **Veri Kalıcılığı (Persistence):** C dilinin standart Dosya Giriş/Çıkış (I/O) fonksiyonları (`fopen`, `fprintf`, `fscanf`) kullanılarak program verilerinin kalıcı olarak diske yazılması ve okunması.
* **Dizi Yönetimi:** Kitap verileri (`struct` içinde `Book`) sabit boyutlu dizide tutulmuş, `book_count` sayacı ile dinamik olarak yönetilmiştir.
* **Dizi Sıkıştırma Algoritması:** Kitap silme işleminde, silinen elemanın yerini doldurmak ve dizide boşluk bırakmamak için sonraki tüm elemanları kaydıran **verimli dizi sıkıştırma** algoritması uygulanmıştır.
* **String İşleme:** `strstr` gibi kütüphane fonksiyonları kullanılarak büyük/küçük harf duyarlı hızlı arama yeteneği entegre edilmiştir.

---

## 🛠 Kullanım ve Kurulum

### Gereksinimler

* Bir C Derleyicisi (GCC önerilir).
* Temel Komut Satırı (CLI) bilgisi.

### Derleme ve Çalıştırma

Projeyi yerel sisteminizde çalıştırmak için aşağıdaki adımları izleyin:

1.  **Depoyu Klonlayın:**
    ```bash
    git clone [https://github.com/oguzhan-gemici-dev/Library]
    cd library-management-system # Proje klasörüne geçin
    ```

2.  **Derleme:**
    ```bash
    gcc -o library main.c -std=c99 
    ```
    *(Not: Tüm kodunuz tek bir `main.c` dosyasındaysa bu komut yeterlidir.)*

3.  **Çalıştırma:**
    ```bash
    ./library
    ```
    *Program ilk çalıştığında, verileri saklamak için otomatik olarak `library_Data.txt` dosyasını oluşturacaktır.*

---

## 📅 Gelecekteki Geliştirmeler (Optional)

* [ ] Harf duyarsız (case-insensitive) arama eklenmesi.
* [ ] Kitap ödünç alma/iade etme (kullanılabilir adet güncelleme) işlevselliği.
* [ ] Kitap verilerini silmek yerine, "arşivlendi" olarak işaretleme.
