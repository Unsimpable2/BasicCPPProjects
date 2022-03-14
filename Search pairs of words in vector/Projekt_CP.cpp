#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iterator>

using namespace std;

fstream p1, p2;

int owt_pliki()
{
	p1.open("input.txt", ios::in | ios::out);			//otwiera plik wejsciowy z tekstem do sprawdzenia

	if (p1.good() == false)				//sprawdza, czy plik udalo sie otworzyc, jesli nie, pojawia sie komunikat i program sie konczy
	{
		cout << "Plik nie istnieje lub nie znajdue sie w odpowiedniej lokalizacji!" << endl;
		return -1;
	}

	if (p1.peek() == fstream::traits_type::eof())			//jezeli plik do sprawdzenia jest pusty, pojawia sie komunikat a program sie konczy
	{
		cout << "Plik jest pusty! Brak zawartosci do sprawdzenia!" << endl;
		p1.close();
		return -1;
	}

	p2.open("output.txt", ios::in | ios::out | ios::trunc);				//otwiera plik wejsciowy z tekstem do sprawdzenia

	if (p2.good() == false)				//sprawdza, czy plik udalo sie otworzyc, jesli nie, pojawia sie komunikat i program sie konczy
	{
		cout << "Plik nie istnieje lub nie moze zostac otwarty!" << endl;
		p1.close();
		return -1;
	}
	return 0;
}

void zamknij_pliki()
{
	p1.close();				//zamyka dostep do pliku, zwalniajac w tym przypadku pamiec
	p2.close();				//zamyka dostep do pliku, zwalniajac w tym przypadku pamiec
}

void policz()
{
	string tekst, linia, wyraz, slowo, slowo_por;
	size_t q;
	int zliczanie = 1, pozycja = 1, pozycja_por = 1;

	while (!p1.eof())			//petla ktora skleja caly tekst w jednego stringa, na wypadek gdyby w pliku wejsciowym byly przejscia do nowej lini
	{
		getline(p1, linia);
		tekst += linia;
	}

	while ((q = tekst.find_first_of(",.!@#$%^&*()-_=+[{]}|';:></?")) != string::npos)			//petla ktora szuka w stingu do pierwszego podanego znaku, jesli go znajdzie, usuwa go, robi tak, az string bedzie wolny od tych konkretnych znakow podnych w funkcji
		tekst.erase(q, 1);			//usuwanie znalezionych znakow szczegolnych

	stringstream ciag(tekst);			//tworzymy strumien stringu o nazwie ciag z zawartoscia z pliku wejsciowego, juz bez jakis znakow szczegolnych
	istream_iterator<string> poczatek(ciag);			//okreslamy poczatek strumienia stringu ciag
	istream_iterator<string> koniec;			//okreslamy koniec strumienia stringu ciag

	vector<string> vek_string(poczatek, koniec);			//wpisujemy do vektora z deklaracja string oraz z powyzszymi deklaracjami o poczatku oraz koncu, by dalo sie latwo go podzielic na poszczegolne, osbne slowa

	vector<string> vek_por;			//tworzymy nowy pusty wektor 	

	while (pozycja < vek_string.size())			//petla ktora bedzie sie wykonywac az pozycja bedzie rowna dlugosci stringa w vektorze					
	{
		slowo = (vek_string[pozycja - 1] + " " + vek_string[pozycja]);			//tworzenie par sasiednich slow	

		vek_por.push_back(slowo);			//dodawanie ich do vectora

		pozycja += 2;		//zwiekszanie pozycji by stworzyc nowa pare
	}

	sort(vek_por.begin(), vek_por.end());			//sortujemy sring vektorowy w zaleznosci od ilosci powtarzajacych sie slow oraz w przypadku wystepowania identycznej ilosci slow, uklada je alfabetycznie

	while (pozycja_por < vek_por.size())			//petla ktora bedzie sie wykonywac az pozycja bedzie rowna dlugosci stringa w vektorze
	{
		slowo_por = vek_por[pozycja_por - 1];			//przypisywanie do do stringa pare slow

		if (slowo_por == vek_por[pozycja_por])			//warunek ktory sprawdza czy slowo jest takie same jak slowo w stringy vektorowym, jesli tak, wchodzi do srodka
		{
			zliczanie++;			//inkrementowanie zliczania par by podac odpowiednia ilosc pod koniec w pliku wyjsciowym
			pozycja_por++;				//inkrementowanie pozycji by program poszedl dalej z szukaniem par
		}
		else
		{
			pozycja_por++;			//inkrementowanie pozycji by program poszedl dalej z szukaniem par

			if (zliczanie % 2 == 0)				//jezeli liczba z dzielenia przez 2 jest rowna 0, wtedy mamy min. jedna pare
				p2 << "Para slow: " << slowo_por << " | Wystepuje: " << zliczanie << endl;				//wpisywanie par do pliku wyjsciowego

			zliczanie = 1;			//powrót do podstawowej wartosci by liczenie powtorek wyrazow dzialalo prawidlowo
		}
	}
}

int main()
{	
	cout << "Program szuka ilosc wystepowania danego slowa, zlicza pary danego slowa i zapisuje do pliku" << endl;
	cout << "W przypadku kiedy kilka slow bedzie wystepowac w tej samej ilosci, sa one wpisywane alfabetycznie" << endl << endl;

	if (owt_pliki() ==-1)
	{ 
		exit(0);
	}
	
	policz();
	
	zamknij_pliki();

	cout << "Zdrobione!" << endl;

	return 0;			//koniec programu, zadzialal on prawidlowo
}