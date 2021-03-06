//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit4.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;

#include <strstrea.h>
#include <fstream.h>
#include <iostream.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include<math.h>

double e3, e3_u[6], w1[2][2], w2[2][2], w3[2][2], y[3][2], x_1[8], x_2[8], e[3][2], dx[6], s[3][2], delta[3][2];
int i, j, k, u, err1, err2;
long r;
double eds;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{
	Edit1->Text = "0";
	Edit2->Text = "0";

}
//---------------------------------------------------------------------------

void TForm4::Losuj()
{
	float z;
	i = 1000;  j = 0;  k = 100;
	time_t t;
	srand((unsigned)time(&t));
	z = ((rand() % i) - j);
	w1[0][0] = z / k;
	z = ((rand() % i) - j);
	w1[0][1] = z / k;
	z = ((rand() % i) - j);
	w1[1][0] = z / k;
	z = ((rand() % i) - j);
	w1[1][1] = z / k;
	z = ((rand() % i) - j);
	w2[0][0] = z / k;
	z = ((rand() % i) - j);
	w2[0][1] = z / k;
	z = ((rand() % i) - j);
	w2[1][0] = z / k;
	z = ((rand() % i) - j);
	w2[1][1] = z / k;
	z = ((rand() % i) - j);
	w3[0][0] = z / k;
	z = ((rand() % i) - j);
	w3[0][1] = z / k;
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Button1Click(TObject *Sender)
{
	Zeruj();
	Pobierz();

	err1 = 0;
	err2 = 0;
	Losuj();
	Wyswietl();

}
//---------------------------------------------------------------------------

void TForm4::Zeruj()
{

	Label1->Caption = 0;
	Label2->Caption = 0;
	Label3->Caption = 0;
	Label4->Caption = 0;
	Label5->Caption = 0;
	Label6->Caption = 0;
	Label7->Caption = 0;
	Label8->Caption = 0;
	Label9->Caption = 0;
	Label10->Caption = 0;
	Label11->Caption = 0;
	Label22->Caption = 0;
	Label23->Caption = 0;
	Label24->Caption = 0;
	Label25->Caption = 0;
	Label32->Caption = 0;
	Label33->Caption = 0;
	Label35->Caption = 0;
	Label38->Caption = 0;
}
//---------------------------------------------------------------------------

void TForm4::Wyswietl()
{

	Label1->Caption = FloatToStrF(w1[0][0], ffFixed, 8, 4);
	Label2->Caption = FloatToStrF(w1[0][1], ffFixed, 8, 4);
	Label3->Caption = FloatToStrF(w1[1][0], ffFixed, 8, 4);
	Label4->Caption = FloatToStrF(w1[1][1], ffFixed, 8, 4);
	Label5->Caption = FloatToStrF(w2[0][0], ffFixed, 8, 4);
	Label6->Caption = FloatToStrF(w2[0][1], ffFixed, 8, 4);
	Label7->Caption = FloatToStrF(w2[1][0], ffFixed, 8, 4);
	Label8->Caption = FloatToStrF(w2[1][1], ffFixed, 8, 4);
	Label9->Caption = FloatToStrF(w3[0][0], ffFixed, 8, 4);
	Label10->Caption = FloatToStrF(w3[0][1], ffFixed, 8, 4);
	Label11->Caption = FloatToStrF(y[2][0], ffFixed, 8, 4);
	Label22->Caption = FloatToStrF(y[0][0], ffFixed, 8, 4);
	Label23->Caption = FloatToStrF(y[0][1], ffFixed, 8, 4);
	Label24->Caption = FloatToStrF(y[1][0], ffFixed, 8, 4);
	Label25->Caption = FloatToStrF(y[1][1], ffFixed, 8, 4);
	Label32->Caption = FloatToStrF(x_1[u], ffFixed, 8, 4);
	Label33->Caption = FloatToStrF(x_2[u], ffFixed, 8, 4);
	Label35->Caption = FloatToStrF(dx[u], ffFixed, 8, 4);
	Label38->Caption = FloatToStrF(e[2][0], ffFixed, 8, 4);

}
//---------------------------------------------------------------------------
void __fastcall TForm4::Button3Click(TObject *Sender)
{
	err2 = 0.1;
	u = 0;
	r = 0;
	for (u = 0; u<5; u++)
	{
		e3_u[u] = 1;
	}
	do
	{
		if (r >= 700000)
		{
			Losuj();
			Zeruj();
			Wyswietl();
			Licz_y();
			Wsteczna();
			u = 0;
		}
		r++;
		Licz_y();
		Wsteczna();
		if (err1 == 1)
		{
			if (u != 0)
			{
				u = 0;
			}
		}
		else
		{
			if (u <= 5)
			{

				u++;
			}
		}
		eds = 0;
		for (int ui = 0; ui<5; ui++)
		{
			Licz_y();
			if ((fabs(eds)) < (fabs(e3_u[ui])))
			{
				eds = e3_u[ui];
				err2 = ui;
			}
		}
		if (u = 6)
			u = err2;

	} while ((fabs(eds) > 0.05));

	Wyswietl();
	Label41->Caption = "u =";
	Label42->Caption = FloatToStrF(u, ffFixed, 3, 0);
	Label43->Caption = "err =";
	Label44->Caption = FloatToStrF(fabs(eds), ffFixed, 3, 8);
	Label39->Caption = "il =";
	Label40->Caption = FloatToStrF(r, ffFixed, 8, 0);

}
//---------------------------------------------------------------------------
void TForm4::Licz_y()
{
	s[0][0] = w1[0][0] * x_1[u] + w1[0][1] * x_2[u];
	y[0][0] = 1 / (1 + exp(-s[0][0]));
	s[0][1] = w1[1][0] * x_1[u] + w1[1][1] * x_2[u];
	y[0][1] = 1 / (1 + exp(-s[0][1]));

	s[1][0] = w2[1][0] * y[0][0] + w2[0][1] * y[0][1];
	y[1][0] = 1 / (1 + exp(-s[1][0]));
	s[1][1] = w2[1][0] * y[0][0] + w2[1][1] * y[0][1];
	y[1][1] = 1 / (1 + exp(-s[1][1]));

	s[2][0] = w3[0][0] * y[1][0] + w3[0][1] * y[1][1];
	y[2][0] = 1 / (1 + exp(-s[2][0]));
}
//---------------------------------------------------------------------------
void TForm4::Wsteczna()
{

	/***************** obliczenia dla trzeciej warstwy ************************/
	e3 = dx[u] - y[2][0];
	delta[2][0] = e3 * y[2][0] * (1 - y[2][0]);
	e3_u[u] = e3;
	/***************** obliczenia dla drugiej warstwy ************************/
	e[1][0] = delta[2][0] * w3[0][0];
	delta[1][0] = e[1][0] * y[1][0] * (1 - y[1][0]);

	e[1][1] = delta[2][0] * w3[0][1];
	delta[1][1] = e[1][1] * y[1][1] * (1 - y[1][1]);

	/***************** obliczenia dla pierwszej warstwy ************************/
	e[0][0] = delta[1][0] * w2[0][0] + delta[1][1] * w2[1][0];
	delta[0][0] = e[0][0] * y[0][0] * (1 - y[0][0]);

	e[0][1] = delta[1][0] * w2[0][1] + delta[1][1] * w2[1][1];
	delta[0][1] = e[0][1] * y[0][1] * (1 - y[0][1]);

	if (fabs(e3) <= 0.05)
	{
		err1 = 0;
	}
	else
	{
		err1 = 1;
		/*********************** przeliczanie wag *******************************/



		/********************* dla trzeciej warstwy *****************************/
		w3[0][0] = w3[0][0] + 2 * 0.2*delta[2][0] * y[2][0];
		w3[0][1] = w3[0][1] + 2 * 0.2*delta[2][0] * y[2][1];

		/********************* dla drugiej warstwy *****************************/
		w2[0][0] = w2[0][0] + 2 * 0.2*delta[1][0] * y[1][0];
		w2[0][1] = w2[0][1] + 2 * 0.2*delta[1][0] * y[1][1];
		w2[1][0] = w2[1][0] + 2 * 0.2*delta[1][1] * y[1][0];
		w2[1][1] = w2[1][1] + 2 * 0.2*delta[1][1] * y[1][1];

		/********************* dla pierwszej warstwy *****************************/
		w1[0][0] = w2[0][0] + 2 * 0.2*delta[0][0] * y[0][0];
		w1[0][1] = w2[0][1] + 2 * 0.2*delta[0][0] * y[0][1];
		w1[1][0] = w2[1][0] + 2 * 0.2*delta[0][1] * y[0][0];
		w1[1][1] = w2[1][1] + 2 * 0.2*delta[0][1] * y[0][1];
	}
	//---------------------------------------------------------------------------
}

void TForm4::Pobierz()
{

	int i, end;
	i = 0;
	end = 0;
	fstream str1("c:\\siec_z_naucz.dat", ios::in | ios::out);
	if (!str1)
	{
		ShowMessage(" Błąd otwarcia pliku \n\n           spróbuj jeszcze raz");
		str1.clear(str1.rdstate() & ~ios::badbit);
		return;
	}
	str1.seekg(0);
	do
	{
		str1 >> x_1[i];
		str1 >> x_2[i];
		str1 >> dx[i];
		if (str1.eof())
		{
			end = 1;
			str1.clear(str1.rdstate() & ~ios::eofbit);
			str1.close();
			Label11->Caption = "koniec pliku";
		}
		i++;
	} while (end == 0);
}

//---------------------------------------------------------------------------

void __fastcall TForm4::Button2Click(TObject *Sender)
{
	exit(0);
}
//---------------------------------------------------------------------------


void __fastcall TForm4::Button4Click(TObject *Sender)
{
	u = 7;
	x_1[u] = StrToFloat(Edit1->Text);
	x_2[u] = StrToFloat(Edit2->Text);
	Licz_y();
	Wyswietl();
	Label47->Caption = FloatToStrF(y[2][0] * 10, ffFixed, 8, 4);

}
//---------------------------------------------------------------------------

void __fastcall TForm4::FormCreate(TObject *Sender)
{
	Edit1->Text = "0";
	Edit2->Text = "0";

}
//---------------------------------------------------------------------------
