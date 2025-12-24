#include <stdio.h>
#include <string.h>

// Sabitler
#define Kota_siniri_gb 6.0
#define Mb_to_Gb 1024.0
#define Asim_ucreti 0.011719

int main() {
    // Değişken tanımlamaları
    FILE *dosyaIslem;
    char dosyaAy[20], istenenAy[20];
    int gun;
    float uploadMB, downloadMB;
    float toplamUploadMB = 0.0, toplamDownloadMB = 0.0;

    // Kullanıcıdan ay bilgisi alma
    printf("Hangi ayin faturasini istiyorsunuz (Orn: Ocak, Subat): ");
    scanf("%s", istenenAy);

    // --- DOSYA OKUMA İŞLEMİ ---
    // Kodun çalıştığı klasördeki adsl.txt dosyasını arar.
    // Eğer dosya masaüstündeyse tam yol yazmanız gerekir (örn: "C:\\Users\\Ad\\Desktop\\adsl.txt")
    dosyaIslem = fopen("adsl.txt", "r");

    if (dosyaIslem == NULL) {
        printf("Hata: 'adsl.txt' dosyasi bulunamadi!\n");
        printf("Lutfen dosyanin programla ayni klasorde oldugundan emin olun.\n");
        return 1;
    }

    // Dosyadan veri okuma döngüsü
    while (fscanf(dosyaIslem, "%s %d %f %f", dosyaAy, &gun, &uploadMB, &downloadMB) != EOF) {
        if (strcmp(dosyaAy, istenenAy) == 0) {
            toplamUploadMB += uploadMB;
            toplamDownloadMB += downloadMB;
        }
    }
    fclose(dosyaIslem);

    // --- HESAPLAMA KISMI ---
    float toplamUploadGB = toplamUploadMB / Mb_to_Gb;
    float toplamDownloadGB = toplamDownloadMB / Mb_to_Gb;
    float kotaAsimUcreti = 0.0;

    if (toplamDownloadGB > Kota_siniri_gb) {
        float asimMiktariMB = toplamDownloadMB - (Kota_siniri_gb * Mb_to_Gb);
        kotaAsimUcreti = asimMiktariMB * Asim_ucreti;
    }

    // --- YAZDIRMA KISMI ---

    // 1. Ekrana Yazdırma
    printf("\n-----EKRAN-CIKTISI-----\n");
    printf("Fatura Donemi: %s 2012\n", istenenAy);
    printf("Toplam Upload  : %.2f GB\n", toplamUploadGB);
    printf("Toplam Download: %.2f GB\n", toplamDownloadGB);

    if (kotaAsimUcreti > 0)
        printf("Kota Asim Ucreti: %.2f TL\n", kotaAsimUcreti);
    else
        printf("Kota Asim Ucreti: 0 TL\n");
    printf("---------------------\n");

    // 2. Dosyaya Yazdırma (fatura.txt)
    FILE *fCikis = fopen("fatura.txt", "w");
    if (fCikis != NULL) {
        fprintf(fCikis, "%s 2012\n", istenenAy);
        fprintf(fCikis, "Toplam\n");
        fprintf(fCikis, "yukleme (upload)   :\n");
        fprintf(fCikis, "%.2f GB\n", toplamUploadGB);
        fprintf(fCikis, "Toplam\n");
        fprintf(fCikis, "indirme (download) :\n");
        fprintf(fCikis, "%.2f GB\n", toplamDownloadGB);
        fprintf(fCikis, "Kota asim ucreti   :\n");
        if (kotaAsimUcreti > 0) fprintf(fCikis, "%.2f TL\n", kotaAsimUcreti);
        else fprintf(fCikis, "0 TL\n");

        fclose(fCikis);
        printf("Detaylar 'fatura.txt' dosyasina yazildi.\n");
    } else {
        printf("Hata: fatura.txt olusturulamadi.\n");
    }

    return 0;
}




