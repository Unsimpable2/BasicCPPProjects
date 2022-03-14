#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

class Operacja
{
public:

	virtual int Convert_vector(vector <string>* s) = 0;	
};


class Operacja_D : public Operacja
{
public:

	virtual int Convert_vector(vector <string> *s)
	{
		for (auto& i : *s)
			for (auto& s : i)
				s = tolower(s);
		return 0;
	}
};

class Operacja_M : public Operacja
{
public:

	virtual int Convert_vector(vector <string> *s)
	{
		for (auto& i : *s)
			for (auto& s : i)
				s = toupper(s);
		return 0;
	}
};

class Operacja_P : public Operacja
{
public:

	virtual int Convert_vector(vector <string> *s)
	{
		string add;
		int a;

		cout << "Podaj ile nowych linii ma zostac dodanych do tekstu: " << endl;
		cin >> a;

		if (a <= 0)
		{
			cout << "Podana ilosc linii do dodania musi byc wieksza od 0!" << endl;
			return -1;
		}

		cout << "Program zapyta sie " << a << " o podanie nowej linii do tekstu!" << endl;
		cout << "Podaj nowa linie do dodania!" << endl;

		for (int i = 0; i < a; i++)
		{
			cin >> add;
			s->push_back(add);
			add.clear();
		}
		return 0;
	}
};

class Operacja_L : public Operacja
{
public:

	virtual int Convert_vector(vector <string> *s)
	{
		reverse(s->begin(), s->end());
		return 0;
	}
};

class Operacja_U : public Operacja
{
public:

	virtual int Convert_vector(vector <string> *s)
	{
		int a = 0, b = 0;
		cout << "Podaj ile linii ma zostac usunietych z pliku: ";
		cin >> a;

		if (a <= 0)
		{
			cout << "Podana wartosc musi byc wieksza od 0!" << endl;
			return -1;
		}

		if (a >= s->size())
		{
			cout << "Wprowadzona ilosc linii do usuniecia jest wieksza niz ilosc linii w teskscie!" << endl;
			return -1;
		}

		cout << "Podaj numer linii do usuniecia!" << endl;
		cout << "Program zapyta sie " << a << " o podanie numeru linii do usuniecia" << endl;

		for (int i = 0; i < a; i++)
		{
			cin >> b;

			if (b <= 0)
			{
				cout << "Podana wartosc musi byc wieksza od 0!" << endl;
				return -1;
			}

			if (b >= s->size())
			{
				cout << "Wprowadzony numer linii jest wiekszy niz ilosc lini w pliku!" << endl;
				return -1;
			}
			s->erase(s->begin() + b - 1);
			b = 0;
		}
		return 0;
	}
}; 

class GKlasa
{
protected:

	string linia, ifn, ofn, par, b_par;
	fstream p1, p2;
	vector<string> vek_string, help_string;

	int argum(int argc, char* argv[])
	{
		bool is_input = false, is_output = false, is_parm = false;

		if ((argc == 1) || (strcmp(argv[1], "-h") == 0))
		{
			for (size_t i = 0; i < help_string.size(); i++)
			{
				cout << help_string.at(i) << endl;
			}
			return -1;
		}

		for (int i = 1; i < argc; i++)
		{
			if (strcmp(argv[i], "-i") == 0)
			{
				ifn = argv[i + 1];
				is_input = true;
			}

			if (strcmp(argv[i], "-o") == 0)
			{
				ofn = argv[i + 1];
				is_output = true;
			}

			if (strcmp(argv[i], "-a") == 0)
			{
				par = argv[i + 1];
				is_parm = true;
			}
		}

		if ((is_input && is_output && is_parm) != true)
		{
			cout << "Zle argumenty wejsciowe!" << endl;
			return -1;
		}

		for (size_t i = 0; i < par.size(); i++)
		{
			if (b_par.find_first_of(par[i]) == string::npos)
			{
				cout << "Zle pararametry operacji, nieprawidlowe skroty!" << endl;
				return -1;
			}
		}
		return 0;
	}

	int ot_pli()
	{
		p1.open(ifn, ios::in | ios::out);

		if (p1.good() == false)
		{
			cout << "Plik nie istnieje lub nie znajdue sie w odpowiedniej lokalizacji!" << endl;
			return -1;
		}

		else if (p1.peek() == fstream::traits_type::eof())
		{
			cout << "Plik jest pusty! Brak zawartosci do sprawdzenia!" << endl;
			p1.close();
			return -1;
		}

		while (!p1.eof())
		{
			getline(p1, linia);
			vek_string.push_back(linia);
		}
		p1.close();
		return 0;
	}

	int zapis()
	{
		p2.open(ofn, ios::in | ios::out | ios::trunc);

		if (p2.good() == false)
		{
			cout << "Plik nie istnieje lub nie moze zostac otwarty!" << endl;
			return -1;
		}

		for (size_t i = 0; i < vek_string.size(); i++)
		{
			p2 << vek_string[i] << endl;
		}
		p2.close();
		return 0;
	}

public:

	virtual int parametry()
	{
		Operacja* s;

		for (size_t i = 0; i < par.size(); i++)
		{
			switch (par[i])
			{
			case 'D':
				s = new Operacja_D;
				s->Convert_vector(&vek_string);
				break;

			case 'M':
				s = new Operacja_M;
				s->Convert_vector(&vek_string);
				break;

			case 'P':
				s = new Operacja_P;
				s->Convert_vector(&vek_string);
				break;
				
			case 'L':
				s = new Operacja_L;
				s->Convert_vector(&vek_string);
				break;

			case 'U':
				s = new Operacja_U;
				s->Convert_vector(&vek_string);
				break;
			}
		}
		return 0;
	}

	GKlasa()
	{
		b_par = "DMPLU";
		help_string.push_back("------------------------------------------------Pomoc----------------------------------------------------");
		help_string.push_back("Najbardziej optymalny sposbo wprowadzania agrumentow z plikami --> '-i input.txt -o output.txt -a dmalc',");
		help_string.push_back("gdzie 'dmalc' to przyklad operacji do wykonania, mozna zmienic kolejnosc ale operacje maja byc na samym koncu");
		help_string.push_back("oraz zawsze przed plikiem z tekstem powinnien sie znajdowac argument '-i' oraz przed plikiem do zapisu '-o'");
		help_string.push_back("Za '-a' powinny znajdowac sie parametry do operacji, spis parametrow zostal podany pod '-h'\n\n");
		help_string.push_back("------------------------------------------------Pomoc----------------------------------------------------");
		help_string.push_back("Przyklad poprawnej komendy '-i input.txt -o output.txt -a DAMLC'<----- parametry odpowiednie pod operacje na tekscie.");
		help_string.push_back("D- Zamiana duzych liter na male!");
		help_string.push_back("M- Zamiana malych liter na duze!");
		help_string.push_back("P- Dodaje nowa linie do tekstu! Program zapyta uzytkownika o podanie tekstu! Zostaja one dodane na koncu pliku!");
		help_string.push_back("L- Odbija tekst wzgledem konca!");
		help_string.push_back("U- Usuwa podana linie tekstu! Program zapyta uzytkownika o podnie numeru linii do usuniecia!");
	}

	~GKlasa()
	{
		vek_string.clear();
		help_string.clear();
	}

	int main_function(int argc, char* argv[])
	{
		if (argum(argc, argv) != 0)
			return -1;

		if (ot_pli() != 0)
			return -1;

		if (parametry() != 0)
			return -1;

		if (zapis() != 0)
			return -1;

		cout << "Program zadzialal prawidlowo!" << endl;

		return 0;
	}
};

int main(int argc, char* argv[])
{
	GKlasa a;
	return a.main_function(argc, argv);
}