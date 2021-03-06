#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>

using namespace std;
const char TUSCIA = '_';
const char LAIVAS = 'O';
const char SAUTA = '*';
const char PATAIKYTA = 'X';

class Laukas {
private: char Field[10][10];
		 int A[3]; // laivu kiekis
		 bool K[3]; //tiko kryptys arba ne
		 int x1; // isimena pradines koordinates kai pataiko
		 int y1;
public:
	//Pasiruosia lauka zaidimui
	void Clean_Field()
	{
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				Field[i][j] = TUSCIA;
		for (int i = 0; i < 4; i++)
			A[i] = 0; // skaiciuoja kiek kokiu laivu yra
	}
	//isveda zaidimo lauka i ekrana
	void Show_Field()
	{
		cout << "  R E S P U B L I K A <-y" << endl;
		for (int i = 0; i < 10; i++)
		{
			cout << i << " ";
			for (int j = 0; j < 10; j++)
				cout << Field[j][i] << " ";
			cout << endl;
		}
		cout << "x" << endl;
	}
	//nuskaito zaidejo koordinates ir pasivercia raides i atitinkamus skaicius(deliojant laivus)
	void Get_Coordinates(int &length, int &x, int &y, bool &hor)
	{
		bool pavyko = false;
		char x0;
		while (!pavyko)
		{
			pavyko = true;
			cout << "Iveskite: LAIVO ILGI, langelio RAIDE, SKAICIU ir KRYPTI (1 - horizontaliai; 0 - vertikaliai)" << endl;
			cin >> length >> x0 >> y >> hor;
			hor = hor % 2;
			if (length < 1 || length >4)
			{
				pavyko = false;
				cout << "Netinkamas laivo ilgis" << endl;
			}
			if (x0 == 'R') x = 0;
			else if (x0 == 'E') x = 1;
			else if (x0 == 'S') x = 2;
			else if (x0 == 'P') x = 3;
			else if (x0 == 'U') x = 4;
			else if (x0 == 'B') x = 5;
			else if (x0 == 'L') x = 6;
			else if (x0 == 'I') x = 7;
			else if (x0 == 'K') x = 8;
			else if (x0 == 'A') x = 9;
			else
			{
				pavyko = false;
				cout << "Netinkamos koordinates" << endl;
			}
			if (pavyko) A[length - 1]++;
			for (int i = 0; i < 4 && pavyko; i++)
			{
				if (A[i] > 4 - i)
				{
					pavyko = false;
					cout << "Tokio ilgio laivu jau pakanka" << endl;
					A[length - 1]--;
				}
			}
		}

	}
	//kompiuteris susidelioja laivus
	void Get_PC_Coordinates(int &x, int &y, bool &hor)
	{
		x = rand() % 10;
		y = rand() % 10;
		hor = rand() % 2;
	}
	//tikrinama ar su duotomis koordinatemis galima pastatyti toki laiva, jei taip - pastato
	void Place_Ships(int length, int x, int y, bool hor, bool &pavyko)
	{
		pavyko = true;
		if (x > 9 || x < 0 || y>9 || y < 0 || (hor && x + length > 10) || (!hor && y + length > 10))
		{
			pavyko = false; //tikrina ar telpa lauke
		}
		else //tikrina sonus
		{
			if (hor) //tikrina horizontalius
			{

				for (int i = 0; i < length && pavyko == true; i++)
				{
					if (Field[x][y] != TUSCIA || //center
						(Field[x - 1 + i][y] != TUSCIA && x != 0) || //up
						(Field[x - 1 + i][y + 1] != TUSCIA && x != 0 && y != 9) || //up-right
						(Field[x + i][y + 1] != TUSCIA && y != 9) || //right
						(Field[x + 1 + i][y + 1] != TUSCIA && x + i != 9 && y != 9) || //down-right
						(Field[x + 1 + i][y] != TUSCIA && x + i != 9) || //down
						(Field[x + 1 + i][y - 1] != TUSCIA && x + i != 9 && y != 0) || //down-left
						(Field[x + i][y - 1] != TUSCIA && y != 0) || //left
						(Field[x - 1 + i][y - 1 + i] != TUSCIA && x != 0 && y != 0))//up-left
						pavyko = false;
				}
			}
			else //tikrina vertikalius
			{
				for (int i = 0; i < length && pavyko == true; i++)
				{
					if (Field[x][y] != TUSCIA ||
						(Field[x - 1][y + i] != TUSCIA && x != 0) || //up
						(Field[x - 1][y + 1 + i] != TUSCIA && y + i != 9 && x != 0 && y != 9) || //up-right
						(Field[x][y + 1 + i] != TUSCIA && y + i != 9 && y != 9) || //right
						(Field[x + 1][y + 1 + i] != TUSCIA && y + i != 9 && x != 9 && y != 9) || //down-right
						(Field[x + 1][y + i] != TUSCIA && x != 9) || //down
						(Field[x + 1][y - 1 + i] != TUSCIA && x != 9 && y != 0) || //down-left
						(Field[x][y - 1 + i] != TUSCIA && y != 0) || //left
						(Field[x - 1][y - 1 + i] != TUSCIA && x != 0 && y != 0))//up-left
						pavyko = false;
				}
			}
		}
		if (pavyko)
		{
			for (int i = 0; i < length; i++)
			{
				if (hor) Field[x + i][y] = LAIVAS;
				else Field[x][y + i] = LAIVAS;
			}
		}
		if (!pavyko) A[length - 1]--;
	}
	//nuskaito koordinates kur saus zaidejas
	void Shooting(int &x, int &y)
	{
		char x0;
		for (int i = 0; i < 1; i++)
		{
			cout << "Iveskite langelio RAIDE ir NUMERI:" << endl;
			cin >> x0 >> y;
			if (x0 == 'R') x = 0;
			else if (x0 == 'E') x = 1;
			else if (x0 == 'S') x = 2;
			else if (x0 == 'P') x = 3;
			else if (x0 == 'U') x = 4;
			else if (x0 == 'B') x = 5;
			else if (x0 == 'L') x = 6;
			else if (x0 == 'I') x = 7;
			else if (x0 == 'K') x = 8;
			else if (x0 == 'A') x = 9;
			if (x > 9 || x < 0 || y>9 || y < 0)
			{
				i--;
				cout << "Netinkamos koordinates" << endl;
			}
		}

	}
	//koordinates kur saus vartotojas
	void R_Shooting(int &x, int &y)
	{
		x = rand() % 10;
		y = rand() % 10;
	}
	//patikrina ar galima sauti ten kur norima
	void Shoot(int x, int y, int &sauta)
	{
		if (Field[x][y] == SAUTA || Field[x][y] == PATAIKYTA)
		{
			//cout << "Cia jau sovete" << endl;
			sauta = -1;
		}
		else if (Field[x][y] == LAIVAS)
		{
			Field[x][y] = PATAIKYTA;
			sauta = 1;
		}
		else
		{
			Field[x][y] = SAUTA;
			sauta = 0;
		}
	}
	//pakeiciamas laukas
	void Change_Field(int x, int y, int sauta)
	{
		if (sauta == 1)
			Field[x][y] = PATAIKYTA;
		else Field[x][y] = SAUTA;
	}
	//kuomet kompiuteris pataiko i laiva imama ieskoti jo tesinio i visas kryptis, kryptys nusinulinamos, isimenamos pirmines koordinates
	void pat(int x, int y)
	{
		for (int i = 0; i < 4; i++)
		{
			K[i] = true;
		}
		x1 = x;
		y1 = y;

		if (x1 == 0) K[0] = false;
		if (x1 == 9) K[1] = false;
		if (y1 == 0) K[2] = false;
		if (y1 == 9) K[3] = false;
	}
	//is eiles saudoma visomis kryptimis kur galima
	void C_Shooting(int &x, int &y, int &kr)
	{
		if (kr != -1)
		{
			K[kr] = false;
			if (kr == 0 || kr == 1)
			{
				if (y != 0) Field[x][y - 1] = SAUTA;
				if (y != 9) Field[x][y + 1] = SAUTA;
			}
			else if (kr == 2 || kr == 3)
			{
				if (x != 0) Field[x - 1][y] = SAUTA;
				if (x != 9) Field[x + 1][y] = SAUTA;
			}
		}
		x = x1;
		y = y1;
		if (K[0] == true)
		{
			x = x1 - 1;
			kr = 0;
		}
		else if (K[1] == true)
		{
			x = x1 + 1;
			kr = 1;
		}
		else if (K[2] == true)
		{
			y = y1 - 1;
			kr = 2;
		}
		else if (K[3] == true)
		{
			y = y1 + 1;
			kr = 3;
		}
		else R_Shooting(x, y);
	}
	//jeigu pataikoma -  einama ta kryptimi kol neberanda laivo toje puseje, tada griztama ir toliau saaudoma nuo pradines koordinates kita kryptimi
	void go(int &x, int &y, int &kr)
	{
		if (kr == 0) 
		{
			if(y!=0) Field[x][y - 1] = SAUTA;
			if(y!=9) Field[x][y + 1] = SAUTA;
			x--;
		}
		else if (kr == 1)
		{
			if (y != 0) Field[x][y - 1] = SAUTA;
			if (y != 9) Field[x][y + 1] = SAUTA;
			x++;
		}
		else if (kr == 2)
		{
			if (x != 0) Field[x - 1][y] = SAUTA;
			if (x != 9) Field[x + 1][y] = SAUTA;
			y--;
		}
		else if (kr == 3)
		{
			if (x != 0) Field[x - 1][y] = SAUTA;
			if (x != 9) Field[x + 1][y] = SAUTA;
			y++;
		}

		if ((kr == 0 || kr == 1))
		{
			if(y1!=9)Field[x1][y1+1] = SAUTA;
			if(y1!=0)Field[x1][y1-1] = SAUTA;
			K[2] = false;
			K[3] = false;
		}
		if (kr == 2 || kr == 3)
		{
			if(x1!=9)Field[x1+1][y1] = SAUTA;
			if(x1!=0)Field[x1-1][y1] = SAUTA;
			K[0] = false;
			K[1] = false;
		}
		if ((x > 9 || x < 0) || (y > 9 || y < 0))
		{
			C_Shooting(x, y, kr);
		}
	}
	//tikrinama ar dar liko krypciu, kuriomis galima sauti
	void kryptis(bool &laiv)
	{
		if (K[0] == false && K[1] == false && K[2] == false && K[3] == false) laiv = false;
	}
};
int main()
{
	Laukas Human;
	Laukas PC;
	Laukas He; // Tai, ka mato zmogus
	int length, x, y, sauta, x1, y1, kr, xh, yh;
	bool hor, pavyko, laiv = false, laivzm = false;
	//Žmogus
	Human.Clean_Field();
	Human.Show_Field();
	for (int i = 0; i < 10; i++) //zmogus deliojasi laivus
	{
		Human.Get_Coordinates(length, xh, yh, hor);
		Human.Place_Ships(length, xh, yh, hor, pavyko);
		if (!pavyko)
		{
			i--;
			cout << "Laivas nepatalpintas" << endl;
		}
		else
		{
			//system("CLS");
			Human.Show_Field();
		}
	}

	PC.Clean_Field();
	srand(time(NULL));
	for (int ilg = 1; ilg < 5; ilg++)//Kompas susideda laivus
	{
		for (int kiek = 5 - ilg; kiek > 0; kiek--)
		{
			PC.Get_PC_Coordinates(x, y, hor);
			PC.Place_Ships(ilg, x, y, hor, pavyko);
			if (!pavyko) kiek++;
		}
	}

	He.Clean_Field(); // laukas kuri mato vartotojas
	int zpat = 0; //zmogaus pataikytu laivu skaicius
	int pcpat = 0; //kompiuterio pataikytu laivu skaicius
	while (zpat<20 && pcpat<20)
	{
		system("CLS");
		Human.Show_Field();
		cout << " ____________________" << endl;
		//PC.Show_Field();
		cout << " ____________________" << endl;
		He.Show_Field();

		for (int i = 0; i < 1; i++)
		{
			PC.Shooting(xh, yh);
			PC.Shoot(xh, yh, sauta);
			if (sauta == -1)
				i--;
			else if (sauta == 1)
			{
				system("CLS");
				Human.Show_Field();
				He.Change_Field(xh, yh, sauta);
				He.Show_Field();
				zpat++;
				if (zpat < 20)
				{
					i--;
					//cout << "Pataikete! Saukite dar karta" << endl;
				}
			}
			else
			{
				He.Change_Field(xh, yh, sauta);
			}
		}

		
		//zmogus
		for (int j = 0; j < 1; j++)
		{	
			if (laiv == false) Human.R_Shooting(x, y);
			else
			{
				if (sauta == 0 || sauta == -1 || kr == -1) Human.C_Shooting(x, y, kr);
				else if (sauta == 1) Human.go(x, y, kr);
			}
			Human.Shoot(x, y, sauta);
			if (sauta == 1)
			{
				pcpat++;
				j--;
				if (laiv == false)
				{
					Human.pat(x, y);
					kr = -1;
				}
				laiv = true;
			}
			else if (sauta == -1) j--;
			Human.kryptis(laiv);
			
		}

		
	}
	
	system("CLS");
	if (pcpat == 20) cout << "GAME OVER" << endl;
	else cout << "YOU WIN!" << endl;
	system("PAUSE");
	return 0;
}



