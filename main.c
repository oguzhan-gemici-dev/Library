#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_KITAP_ISMI 100
#define MAX_YAZAR_ISMI 50
#define MAX_ISBN_LENGTH 15
#define MAX_BOOKS 1000
#define DATA_FILE "library_Data.txt"
//kitap bilgileri
typedef struct{
    int id;                         //kitabýn id numarasý(kimliði)
    char kitap_ismi[MAX_KITAP_ISMI];//kitap adý
    char yazar[MAX_YAZAR_ISMI];     //yazar ismi
    char ISBN[MAX_ISBN_LENGTH];     //ISBN
    int toplam_adet;                //kütüphanede bulunan toplam adet
    int kullanilabilir_adet;        //kütüphanedeki alýnabilir/kiralanabilir adet
}Kitap;
Kitap library[MAX_BOOKS]; // Sabit boyutlu dizi
int book_count = 0;      // Dizideki mevcut kitap sayýsý (sayacýmýz)
int last_id = 0;         // Son atanan ID

// Dosyadan verileri baðlý listeye yükler
void load_data_from_file();
// Baðlý listedeki tüm verileri dosyaya kaydeder
void save_data_to_file();

//fonksiyon prototipleri
    void menu();
    void kitap_ekleme();
    void kitap_arama();
    void kitap_listele();
    void kitap_silme();
    void buffer_temizleme();
int main(){
    int choice;
    load_data_from_file();

    printf("KUTUPHANE YONETIM SISTEMI\n");
    printf("-------------------------\n");

    do{
        menu();
        printf("Secim yapiniz: ");

        if(scanf("%d",&choice)!=1){
            buffer_temizleme();
            choice=0;
        }
        switch(choice){
        case 1:
            kitap_ekleme();
            break;
        case 2:
            kitap_arama();
            break;
        case 3:
            kitap_listele();
            break;
        case 4:
            kitap_silme();
        case 5:
            printf("Programdan cikiliyor. Veriler kaydediliyor.\n");
            save_data_to_file();//veri kaydý
            break;
        default:
            printf("Gecersiz secim. Lütfen 1-5 arasinda bir sayi giriniz.\n");
        }
        printf("n");
    }while(choice!=5);
return 0;
}

//Menü fonksiyonu
void menu(){
    printf("\n--Ana Menu--\n");
    printf("1. Yeni Kitap Ekle\n");
    printf("2. Kitap Ara\n");
    printf("3. Tum Kitaplari Listele\n");
    printf("4. Kitap Sil\n");
    printf("5. Cikis\n");
}
void buffer_temizleme() {
    int c;
    while((c=getchar())!='\n' && c!=EOF);
}

void load_data_from_file(){
    FILE *file = fopen(DATA_FILE, "r");
    if (file == NULL) {
        printf("Veri dosyasi bulunamadi. Yeni veri dosyasi olusturuluyor...\n");
        book_count=0; // Baþlangýçta kitap sayýsý sýfýr
        return;
    }

    // Dosyanýn sonuna kadar okur ve her okunaný diziye ekler
    while (book_count < MAX_BOOKS &&
           fscanf(file, "%d;%[^;];%[^;];%[^;];%d;%d\n",
                  &library[book_count].id,
                  library[book_count].kitap_ismi,
                  library[book_count].yazar,
                  library[book_count].ISBN,
                  &library[book_count].toplam_adet,
                  &library[book_count].kullanilabilir_adet)==6){

        // En son ID'yi takip et
        if (library[book_count].id>last_id){
            last_id = library[book_count].id;
        }
        book_count++; // Her baþarýlý okumada kitap sayacýný artýrýr
    }

    fclose(file);
    printf("Veriler basariyla yuklendi. Toplam kitap: %d (Son ID: %d)\n", book_count, last_id);
}

void save_data_to_file(){
   FILE *file = fopen(DATA_FILE, "w"); // "w" modu ile var olan içeriðin üzerine yazýlýr
    if (file == NULL) {
        printf("HATA: Veri dosyasi yazilamiyor!\n");
        return;
    }

    // Sadece dizideki mevcut kitap sayacý kadar döngü kurar
    for (int i=0;i<book_count;i++){
        // Veriyi TXT dosyasýna özel ayýrýcý (;) kullanarak yazar
        fprintf(file, "%d;%s;%s;%s;%d;%d\n",
                library[i].id,
                library[i].kitap_ismi,
                library[i].yazar,
                library[i].ISBN,
                library[i].toplam_adet,
                library[i].kullanilabilir_adet);
    }

    fclose(file);
    printf("Tum veriler %s dosyasina kaydedildi.\n", DATA_FILE);
}
void kitap_ekleme(){
    // 1. Kapasite kontrolü yapýlýr
    if (book_count>= MAX_BOOKS){
        printf("HATA: Kutuphane kapasitesi doldu (%d kitap).\n", MAX_BOOKS);
        return;
    }
    Kitap *new_book=&library[book_count];
    // 2. Benzersiz ID atamasý yapar
    last_id++;
    new_book->id=last_id;

    buffer_temizleme();

    // 3. Kullanýcýdan bilgileri alýr
    printf("Kitap Adi (Max %d karakter):",MAX_KITAP_ISMI-1);
    if (fgets(new_book->kitap_ismi, MAX_KITAP_ISMI, stdin)==NULL) return;
    new_book->kitap_ismi[strcspn(new_book->kitap_ismi, "\n")] = 0;

    printf("Yazar Adi (Max %d karakter): ", MAX_YAZAR_ISMI-1);
    if (fgets(new_book->yazar, MAX_YAZAR_ISMI, stdin)==NULL) return;
    new_book->yazar[strcspn(new_book->yazar, "\n")]=0;

    printf("ISBN (Max %d karakter): ", MAX_ISBN_LENGTH-1);
    if (fgets(new_book->ISBN, MAX_ISBN_LENGTH, stdin)==NULL) return;
    new_book->ISBN[strcspn(new_book->ISBN, "\n")]=0;

    printf("Toplam Kopya Sayisi: ");
    if (scanf("%d", &new_book->toplam_adet)!=1 || new_book->toplam_adet< 1){
        printf("HATA: Gecersiz kopya sayisi. Kitap eklenmedi.\n");
        buffer_temizleme();
        last_id--; // ID'yi geri al
        return;
    }

    new_book->kullanilabilir_adet=new_book->toplam_adet;

    // 4. Kitap sayacýný artýrarak ekleme iþlemini tamamlar
    book_count++;
    printf("\nKitap basariyla eklendi! ID: %d, kitap ismi: %s (Toplam kitap: %d)\n", new_book->id, new_book->kitap_ismi, book_count);
}
void kitap_listele(){
    // 1. Kütüphanenin boþ olup olmadýðýný kontrol eder
    if (book_count==0){
        printf("Kutuphanede kayitli kitap bulunmamaktadir.\n");
        return;
    }
    // 2. Baþlýk satýrýný bastýrýr
    printf("------------------------------------------------------------------------------------------------------------------\n");
    printf("| ID   | Kitap Adý%37s | Yazar%16s | ISBN            | Toplam | Kullanilabilir |\n", " ", " ");
    printf("------------------------------------------------------------------------------------------------------------------\n");

    // 3. Diziyi dönerek her kitabý listeler
    for (int i = 0; i < book_count; i++){
        // Her kitabýn bilgilerini ekrana basar
        // %-5s gibi formatlar metinlerin hizalanmasýný saðlar.
        printf("| %-4d | %-45s | %-20s | %-15s | %-6d | %-14d |\n",
               library[i].id,
               library[i].kitap_ismi,
               library[i].yazar,
               library[i].ISBN,
               library[i].toplam_adet,
               library[i].kullanilabilir_adet);
    }

    // 4. Alt çizgiyi bastýr
    printf("------------------------------------------------------------------------------------------------------------------\n");
    printf("Toplam kayitli kitap sayisi: %d\n", book_count);
}
void kitap_arama(){
    if (book_count==0){
        printf("Kutuphanede kayitli kitap bulunmamaktadir.\n");
        return;
    }
    char search_term[MAX_KITAP_ISMI];
    int found_count=0; // Bulunan kitap sayýsýný tutar

    buffer_temizleme();
    printf("Aranacak kelimeyi (Kitap Adi veya Yazar) girin: ");

    // fgets ile arama terimini güvenli bir þekilde alýr
    if (fgets(search_term, MAX_KITAP_ISMI, stdin)==NULL) return;
    // Sondaki '\n' karakterini temizler
    search_term[strcspn(search_term, "\n")]=0;

    // Arama teriminin boþ olup olmadýðýný kontrol eder
    if (strlen(search_term)==0){
        printf("Arama terimi bos olamaz.\n");
        return;
    }

    printf("\n--- Arama Sonuçlarý ---\n");
    printf("------------------------------------------------------------------------------------------------------------------\n");
    printf("| ID   | Kitap Adý%37s | Yazar%16s | ISBN            | Toplam | Kullanilabilir |\n", " ", " ");
    printf("------------------------------------------------------------------------------------------------------------------\n");

    // Tüm kitap dizisini döner
    for (int i=0;i< book_count;i++){
        // strstr(aranacak_buyuk_dizi, aranacak_kucuk_dizi)
        // Kitap adýnda veya yazar adýnda arama teriminin geçip geçmediðini kontrol eder

        // ÖNEMLÝ NOT: Arama þu an *büyük/küçük harf duyarlýdýr*.
        if (strstr(library[i].kitap_ismi, search_term)!=NULL ||
            strstr(library[i].yazar, search_term)!=NULL) {

            // Eðer bulunduysa, kitabý listeler
            printf("| %-4d | %-45s | %-20s | %-15s | %-6d | %-14d |\n",
                   library[i].id,
                   library[i].kitap_ismi,
                   library[i].yazar,
                   library[i].ISBN,
                   library[i].toplam_adet,
                   library[i].kullanilabilir_adet);

            found_count++;
        }
    }

    printf("------------------------------------------------------------------------------------------------------------------\n");

    if (found_count==0){
        printf("'%s' terimiyle eslesen kitap bulunamadi.\n", search_term);
    } else {
        printf("Toplam %d kitap bulundu.\n", found_count);
    }
}
void kitap_silme(){
    if (book_count == 0){
        printf("Silinecek kayitli kitap bulunmamaktadir.\n");
        return;
    }
    int id_to_delete;
    printf("Silmek istediginiz kitabin ID'sini girin: ");
    // Kullanýcýdan ID alýr
    if (scanf("%d", &id_to_delete)!=1){
        printf("HATA: Gecersiz ID formati.\n");
        buffer_temizleme();
        return;
    }
    buffer_temizleme();

    int found_index=-1; // Silinecek kitabýn dizideki indeksini tutar

    // 1. Silinecek kitabý dizide arar
    for (int i=0;i<book_count;i++){
        if (library[i].id==id_to_delete){
            found_index=i;
            break; // Kitap bulundu, döngüyü sonlandýrýr
        }
    }

    // 2. Kitap bulunamazsa
    if (found_index == -1){
        printf("HATA: ID %d olan kitap bulunamadi.\n", id_to_delete);
        return;
    }

    // 3. Kitap bulundu, silme ve diziyi sýkýþtýrma iþlemi yapar

    // Silinen kitabýn adýný kullanýcýya bilgi vermek için tutar
    char deleted_title[MAX_KITAP_ISMI];
    strcpy(deleted_title, library[found_index].kitap_ismi);

    // Silinen elemandan sonraki tüm elemanlarý bir sola kaydýrýr
    for (int i=found_index;i<book_count-1;i++){
        library[i]=library[i+1]; // Sonraki elemaný, mevcut elemanýn yerine kopyalar
    }

    // 4. Kitap sayacýný azalt
    book_count--;

    printf("\nBasariyla silindi: ID %d, Baslik: %s\n", id_to_delete, deleted_title);
    printf("Kalan toplam kitap sayisi: %d\n", book_count);
}
