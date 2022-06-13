
#include <iostream>
#include <windows.h>
#include <cstdlib>			// programi kullanabilmek icin gerekli kutuphaneler
#include <list>
#include <string>
using namespace std;// isim uzayi
struct colors_t// renkli yazim icin gerekli fonksiyonlar
{
	HANDLE hstdout;
	int initial_colors;

	colors_t()
	{
		hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
		initial_colors = getcolors();
	}

	~colors_t()
	{
		setcolors(initial_colors);
	}

	int getcolors() const
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(hstdout, &csbi);
		return csbi.wAttributes;
	}

	void setcolors(int color)
	{
		SetConsoleTextAttribute(hstdout, color);
	}

	void setfg(int color)
	{
		int current_colors = getcolors();
		setcolors((current_colors & 0xF0) | (color & 0x0F));
	}

	void setbg(int color)
	{
		int current_colors = getcolors();
		setcolors(((color & 0x0F) << 4) | (current_colors & 0x0F));
	}

	int getfg() const { return  getcolors() & 0x0F; }
	int getbg() const { return (getcolors() >> 4) & 0x0F; }
};
enum RENKLER
{
	LIGHTBLUE = 9,
	LIGHTGREEN = 10,
	LIGHTCYAN = 11,
	LIGHTRED = 12,
	LIGHTMAGENTA = 13,
	YELLOW = 14,

};
class karakter // karakter adli bir sinif ve icerisinde public olarak tutulan harf1 ve renk degiskenleri 
{
public:
	char harf1;
	int renk;
};
char DUZCIZGI = 205;
char SOLUSTKOSE = 201;
char SAGUSTKOSE = 187;
char DIKEYCIZGI = 186;   // kutucuk icerisinde yazmak icin gerekli degiskenler
char ASAGIAYRAC = 203;
char SOLALTKOSE = 200;
char SAGALTKOSE = 188;
char YUKARIAYRAC = 202;

std::list<karakter> harfler; // karakter ekle ve karakter cikarma fonksiyonlarini hafizada tutabilmek icin liste kullanildi.

int renk;
int randomHarf;
int randomRenk;	 // program icin gerekli degiskenler bildirildi.
int sayiAl;
char harf;
int sayac;
void karakterEkle() 
{
	sayac++;
	cout << " eklenen  kutucuk sayisi: " << sayac << endl; // eklenen kutucuk miktarini gosteren kod.


	randomHarf = rand() % 26;     
	harf = 'A' + randomHarf;                   // random harf uretimi yapildi. 
	randomRenk = rand() % 10+5 ; // random renk uretildi.
	karakter obj; // karakterler sinifindan obj adli nesne uretildi
	obj.harf1 = randomHarf;
	obj.renk = randomRenk;  // karakter sinifindaki degiskenlere ulasýlarak deger atandi.
	if (harfler.size() == 0) // eger harfler listesi bos ise listenin basindan baslanarak obj nesnesi listeye yazilmaya baslandi.
	{
		harfler.insert(harfler.begin(), obj);
	}
	else // eger liste bos degil ise obj nesnesi listeye sondan eklenmeye basladi.
	{
		harfler.push_back(obj);
	}
	for (list<karakter>::iterator iter = harfler.begin(); iter != harfler.end(); iter++) // iter degiskeni ile tekrarlayici bildirimi yapildi ve dongu kuruldu.
	{
		cout << SOLUSTKOSE << DUZCIZGI << DUZCIZGI << SAGUSTKOSE; // kutucuk formunu vermek icin gerekli kodlar ekrana basildi.


	}
	cout << endl;
	for (list<karakter>::iterator iter = harfler.begin(); iter != harfler.end(); iter++)
	{
		colors_t colors; // renkleri kullanabilmek icin.
		harf = 'A' + iter->harf1; // liste icindeki harf1 degiskenine atama yapildi.

		cout << DIKEYCIZGI << " ";// kutucuk formunu vermek icin gerekli kodlar ekrana basildi.
		colors.setfg(iter->renk); // liste icerisindeki renk degiskenine atama yapildi
		cout << harf;// harf degiskeni ekrana bastirildi
		colors.setcolors(colors.initial_colors);// tum konsol yazilari renkli olmasin diye duzeltme kodu
		cout << DIKEYCIZGI;// kutucuk formunu vermek icin gerekli kodlar ekrana basildi.
	}
	cout << endl;
	for (list<karakter>::iterator iter = harfler.begin(); iter != harfler.end(); iter++)
	{

		cout << SOLALTKOSE << DUZCIZGI << DUZCIZGI << SAGALTKOSE;// kutucuk formunu vermek icin gerekli kodlar ekrana basildi.


	}
	cout << endl;	

}
void karakterCikar()
{
	sayac--;
	cout << "silinen kutucuk sayisi: " << sayac << endl;
	if (sayac <=0)                                                 // silinen kutucuk sayisi miktarini gosteren kod.
	{
		cout <<  "silme islemi yapilamaz" << endl;
		exit(0);
	}
		

	harfler.pop_back(); // listedeki son elemani silme fonksiyonu
	for (list<karakter>::iterator iter = harfler.begin(); iter != harfler.end(); iter++)
	{
		cout << SOLUSTKOSE << DUZCIZGI << DUZCIZGI << SAGUSTKOSE;// kutucuk formunu vermek icin gerekli kodlar ekrana basildi.


	}
	cout << endl;
	for (list<karakter>::iterator iter = harfler.begin(); iter != harfler.end(); iter++)
	{
		colors_t colors;
		harf = 'A' + iter->harf1;



		cout << DIKEYCIZGI << " ";// kutucuk formunu vermek icin gerekli kodlar ekrana basildi.
		colors.setfg(iter->renk);// liste icerisindeki renk degiskenine atama yapildi
		cout << harf;
		colors.setcolors(colors.initial_colors);// tum konsol yazilari renkli olmasin diye duzeltme kodu
		cout << DIKEYCIZGI;// kutucuk formunu vermek icin gerekli kodlar ekrana basildi.



	}
	cout << endl;
	for (list<karakter>::iterator iter = harfler.begin(); iter != harfler.end(); iter++)
	{

		cout << SOLALTKOSE << DUZCIZGI << DUZCIZGI << SAGALTKOSE;// kutucuk formunu vermek icin gerekli kodlar ekrana basildi.


	}
	cout << endl;
	
}

int main()
{

	srand(time(NULL));// rand fonskiyonu kullanimi icin gerekli kod
	int secim;
	do
	{
		cout << "<--------------- Renkli Sayilar------------>" << endl;
		cout << endl;
		cout << endl;
		cout << "1-Karakter Ekle" << endl;                  // program secim menüsü
		cout << "2-Karakter Cikar" << endl;
		cout << "3-Cikis" << endl;
		cin >> secim;
		if (secim == 1) // karakter ekleme 
		{
			cout << endl;
			karakterEkle(); 
		}
		if (secim == 2)// karakter cikarma 
		{
			cout << endl;
			karakterCikar();
		}



	} while (secim != 3);//cikis
}
