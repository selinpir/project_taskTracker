#include<stdio.h>
#include<string.h>

#define COUNT_OF(arr) (sizeof(arr) / sizeof((arr)[0]))  // Makro burada tanýmlandý

typedef struct {
	int id;
	char gorev_adi[100];
	char son_teslim_tarihi[20];
	int oncelik; //(1-5)
	int tamamlandi_mi;
} gorev;

void gorevEkle(gorev gorevler[], int* gorev_sayisi);
void gorevListele(gorev gorevler[], int gorev_sayisi);
void tamamla(gorev gorevler[], int gorev_sayisi, int id);
void sil(gorev gorevler[], int* gorev_sayisi, int id);

int main() {
	gorev gorev[100];
	int gorev_sayisi = 0;
	int secim, id;

	while (1) {
		printf("\n--- Gorev Takip Uygulamasi ---\n");
		printf("1. Gorev Ekle\n");
		printf("2. Gorevleri Listele\n");
		printf("3. Gorevi Tamamla\n");
		printf("4. Gorev Sil\n");
		printf("5. Cikis\n");
		printf("Seciminiz: ");
		scanf_s("%d", &secim);

		switch (secim)
		{
		case 1:
			gorevEkle(gorev, &gorev_sayisi);

			break;
		case 2:
			gorevListele(gorev, gorev_sayisi);
			break;
		case 3:
			printf("Tamamlanacak gorevin ID'si: ");
			scanf_s("%d", &id);
			tamamla(gorev, gorev_sayisi, id);
			break;
		case 4:
			printf("Silinecek gorevin ID'si: ");
			scanf_s("%d", &id);
			sil(gorev, &gorev_sayisi, id);
			break;
		case 5:
			printf("Cikis yapiliyor...\n");
			return 0;

		default:
			printf("Lutfen gecerli bir islem seciniz.");
		}
	}
	

}

void gorevEkle(gorev gorevler[], int* gorev_sayisi) {
	gorev yeni_gorev;
	yeni_gorev.id = *gorev_sayisi + 1;
	yeni_gorev.tamamlandi_mi = 0;

	if (*gorev_sayisi >= 100) {
		printf("Maksimum gorev sayisina ulasildi. Yeni gorev eklenemez.\n");
		return;
	}
	
	do {
		printf("Gorev Adi: ");
		scanf_s("%99s", yeni_gorev.gorev_adi, COUNT_OF(yeni_gorev.gorev_adi));
		if (strlen(yeni_gorev.gorev_adi) == 0) {
			printf("Gorev adi bos olamaz. Lutfen tekrar girin.\n");
		}
	} while (strlen(yeni_gorev.gorev_adi) == 0);

	do {
		printf("Son teslim tarihi (dd-mm-yyyy): ");
		scanf_s("%19s", yeni_gorev.son_teslim_tarihi, COUNT_OF(yeni_gorev.son_teslim_tarihi));
		if (strlen(yeni_gorev.son_teslim_tarihi) != 10 || yeni_gorev.son_teslim_tarihi[2] != '-' || yeni_gorev.son_teslim_tarihi[5] != '-') {
			printf("Geçersiz tarih formatý. Lutfen dd-mm-yyyy formatýnda girin.\n");
		}
	} while (strlen(yeni_gorev.son_teslim_tarihi) != 10 || yeni_gorev.son_teslim_tarihi[2] != '-' || yeni_gorev.son_teslim_tarihi[5] != '-');

	do {
		
		printf("Gorevin oncelik durumu (1-5): ");
		scanf_s("%d", &yeni_gorev.oncelik);
		if (yeni_gorev.oncelik < 1 || yeni_gorev.oncelik > 5) {
			printf("Gecersiz oncelik. Lutfen 1 ile 5 arasinda bir deger girin.\n");
		}
	} while (yeni_gorev.oncelik < 1 || yeni_gorev.oncelik > 5);

	gorevler[*gorev_sayisi] = yeni_gorev;
	(*gorev_sayisi)++;
	printf("Goreviniz basariyla eklenmistir.\n");
}

void gorevListele(gorev gorevler[], int gorev_sayisi) {
	if (gorev_sayisi == 0)
	{
		printf("To-Do List bos.\n");
		return;
	}
	printf("Gorev Listesi: \n");
	for (int i = 0; i < gorev_sayisi; i++)
	{
		printf("ID: %d | Gorev Adi: %s | Son teslim tarihi: %s | Oncelik durumu: %d | Durum: %s\n",
			gorevler[i].id, gorevler[i].gorev_adi, gorevler[i].son_teslim_tarihi,
			gorevler[i].oncelik,
			gorevler[i].tamamlandi_mi ? "Tamamlandi" : "Tamamlanmadi");

	}
}
void tamamla(gorev gorevler[], int gorev_sayisi, int id) {
	int bul = 0;
	for (int i = 0; i < gorev_sayisi; i++) {
		if (gorevler[i].id == id) {
			gorevler[i].tamamlandi_mi = 1;
			bul = 1;
			printf("Gorev tamamlandi.\n");
			break;
		}
	}
	if (!bul)
	{
		printf("Gorev bulunamadi.\n");
	}
}
void sil(gorev gorevler[], int* gorev_sayisi, int id) {
	int bul = 0;
	for (int i = 0; i < *gorev_sayisi; i++)
	{
		if (gorevler[i].id == id)
		{
			bul = 1;
			for (int j = i; j < *gorev_sayisi - 1; j++)
			{
				gorevler[j] = gorevler[j + 1]; //görevleri yukarý taþýr
			}
			(*gorev_sayisi)--;
			printf("Gorev basariyla silindi.\n");
			break;
		}
	}
	if (!bul)
	{
		printf("Gorev Bulunamadi.\n");
	}

}