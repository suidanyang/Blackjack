#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<string.h>
using namespace std;

float x[52];

//shuffle.
void shuffle(float *a,float *b)
{
	int i,j;
	for (i = 0; i < 4; i++)
		for (j = 0 ; j < 13;j++)
			if(j<10) x[13*i+j] = j+1;
				else x[13 * i + j] = 0.5;
				*a = 0; *b = 0;
}

//deal.
int GetCards(float * s)
{
	int seed,i;
	seed = time(0);
	srand((unsigned int)seed);
	do
	{
		i = rand() % 52;
	} while (x[i] == 0);
	*s += x[i];
	x[i] = 0;
	return i;
}

//get the cards.
void CardsNumber(const int y)
{
	switch (y%4)
	{
	case 0:cout << " heart "; break;
	case 1:cout << " diamond "; break;
	case 2:cout << " spade "; break;
	case 3:cout << " club ";
	}
	switch (y%13)
	{
	case 0:cout << 'A'; break;
	case 10:cout << 'J'; break;
	case 11:cout << 'Q'; break;
	case 12:cout << 'K'; break;
	default:cout << (y+1) % 13;
	}
}

//player phase.
int player(float *score)
{
	int a[15],i=1,f;
	string q;
	cout << "Player phase" << endl << "Player got the cards :";
	a[0] = GetCards(score); CardsNumber(a[0]); a[1] = GetCards(score); CardsNumber(a[1]);
	cout << endl;
	while (1)
	{
		cout << "One more card?(y/n): ";
		while (1)
		{
			cin >> q;
			if (q != "Y" && q != "y" && q != "N" && q != "n"){cout << "Illegal input! Try again :";}
			else if (q == "y" || q == "Y") { f = 1; break; }
			else if (q == "n" || q == "N") { f = 0; break; }
		}
		if (f) 
		{ 
			cout << "One more card :";
			a[++i]=GetCards(score); 
			for (f = 0; f<i; f++)
				CardsNumber(a[f]);
			CardsNumber(a[i]);
			cout << endl;
			if (*score > 21) return 0;
		}
		else break;
	}
	return i+1;
}

//computer phase.
int ai(const float scorep, const int np,float *score)
{
	int a[15],i=1,n;
	cout << "Computer phase" << endl << "Computer got the cards :";
	a[0] = GetCards(score); CardsNumber(a[0]); a[1] = GetCards(score); CardsNumber(a[1]);
	cout << endl;
	while (*score<scorep||(*score==scorep&&i+1<np))
	{
		cout << "One more card :";
		a[++i] = GetCards(score);
		for (n = 0; n <= i; n++)
			CardsNumber(a[n]);
		cout << endl;
		if (*score>21) return 0;
	}
	return i + 1;
}

//judge won or lost.
void winornot(float sp, int np, float sai, int nai)
{
	if (sp > sai || sp == sai&&np > nai) cout << "YOU won." << endl;
	else if (sp == sai && np == nai) cout << "Draw." << endl;
	else cout << "You lost." << endl << endl;
}
int main()
{
	float sp, sai;
	int np, nai,f=0;
	string q, c;
	do
	{
		while (1)
		{
			shuffle(&sp, &sai);
			np = player(&sp);
			if (!np) { cout << "You lost." << endl << endl; break; }
			nai = ai(sp, np, &sai);
			if (!nai) { cout << "You won." << endl << endl; break; }
			winornot(sp, np, sai, nai);
			break;
		}
		cout << "Continue?(y/n): ";
		while (1)
		{
			try{
			cin >> c;
			if("y" == c || "n" == c || "Y" == c || "N" == c){
				return c[0];
			}
			throw 1;
			}
			catch(int i){
				cout << "Your input is illegal! Pleas try again: ";
			}
		}
		
	}
    while (f);
	return 0;
}
