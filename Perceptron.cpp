//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TForm1 *Form1;
#include <strstrea.h>
#include <fstream.h>
#include <iostream.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
float x0, x1[100], x2[100], w0, w1, w2, wf0, wf1, wf2, S, y, a, b;
int d[100], i, size;
int ok, ok1;
int lrn;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	time_t t;
	srand((unsigned)time(&t));
	w0 = (rand() % 200) - 100;
	w1 = (rand() % 200) - 100;
	w2 = (rand() % 200) - 100;
	wf0 = w0 / 100;
	wf1 = w1 / 100;
	wf2 = w2 / 100;
	x0 = -1;
	w0 = wf0;
	w1 = wf1;
	w2 = wf2;

}
//---------------------------------------------------------------------------
void TForm1::Przelicz()
{
	i = 0;
	int err = 0;
	Label13->Caption = "";
	Label1->Caption = "";
	Label2->Caption = "";
	Label13->Caption = FloatToStrF(w0, ffFixed, 1, 3);
	Label1->Caption = FloatToStrF(w1, ffFixed, 1, 3);
	Label2->Caption = FloatToStrF(w2, ffFixed, 1, 3);
	int t1 = 0;
	i = 0;
	do
	{
		lrn++;
		Label8->Caption = FloatToStrF(x1[i], ffFixed, 10, 2);
		Label9->Caption = FloatToStrF(x2[i], ffFixed, 10, 2);
		Label10->Caption = FloatToStrF(d[i], ffFixed, 10, 0);

		S = x0 * w0 + x1[i] * w1 + x2[i] * w2;

		if (S >= 0)
		{
			y = 1;
		}
		else
		{
			y = -1;
		}
		w0 = w0 + 0.1*(d[i] - y)*x0;
		w1 = w1 + 0.1*(d[i] - y)*x1[i];
		w2 = w2 + 0.1*(d[i] - y)*x2[i];
		i++;

	} while (i != size);
	a = -w1 / w2;
	b = w0 / w2;
	Label13->Caption = "";
	Label1->Caption = "";
	Label2->Caption = "";
	Label8->Caption = "";
	Label9->Caption = "";
	Label10->Caption = "";
	Label13->Caption = FloatToStrF(w0, ffFixed, 1, 3);
	Label1->Caption = FloatToStrF(w1, ffFixed, 1, 3);
	Label2->Caption = FloatToStrF(w2, ffFixed, 1, 3);
	Label17->Caption = FloatToStrF(a, ffFixed, 10, 2);
	Label18->Caption = FloatToStrF(b, ffFixed, 10, 0);
	Label21->Caption = "";
	Label11->Caption = "KONIEC - NAUCZONY !!!";

}
//---------------------------------------------------------------------------

void TForm1::Sprawdz()
{
	i = 0;
	ok = 0;
	ok1 = 0;
	do
	{
		Label8->Caption = FloatToStrF(x1[i], ffFixed, 10, 2);
		Label9->Caption = FloatToStrF(x2[i], ffFixed, 10, 2);
		Label10->Caption = FloatToStrF(d[i], ffFixed, 10, 0);

		S = x0 * w0 + x1[i] * w1 + x2[i] * w2;

		if (S >= 0)
		{
			y = 1;
		}
		else
		{
			y = -1;
		}
		if (d[i] != y)
		{
			ok = 1;
		}
		else
		{
			ok = 0;
		}
		i++;
		if (i == size + 1)
		{
			ok = 1;
			ok1 = 1;
		}
	} while (ok == 0);
}

//---------------------------------------------------------------------------

void TForm1::Wczytaj()
{
	int end = 0;
	i = 0;
	fstream strum1("d:\\perceptr.dat", ios::in | ios::out);
	if (!strum1)
	{
		ShowMessage(" Błąd otwarcia pliku \n\n           spróbuj jeszcze raz");
		strum1.clear(strum1.rdstate() & ~ios::badbit);
		return;
	}
	size = 0;
	strum1.seekg(0);
	do
	{
		strum1 >> x1[i];
		strum1 >> x2[i];
		strum1 >> d[i];
		if (strum1.eof())
		{
			end = 1;
			strum1.clear(strum1.rdstate() & ~ios::eofbit);
			strum1.close();
			Label11->Caption = "koniec pliku";
		}
		size++;
		i++;
	} while (end == 0);
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button2Click(TObject *Sender)
{
	int i;
	lrn = 0;
	do
	{
		Przelicz();
		Sprawdz();

	} while (ok1 == 0);
	Label13->Caption = FloatToStrF(w0, ffFixed, 1, 3);
	Label1->Caption = FloatToStrF(w1, ffFixed, 1, 3);
	Label2->Caption = FloatToStrF(w2, ffFixed, 1, 3);
	Label17->Caption = FloatToStrF(a, ffFixed, 10, 2);
	Label18->Caption = FloatToStrF(b, ffFixed, 10, 0);
	Label20->Caption = FloatToStrF(lrn, ffFixed, 10, 0);
	lrn = 0;
	fstream strum("d:\\perc_wyk.dat", ios::in | ios::out | ios::trunc);
	if (!strum)
	{
		ShowMessage(" Błąd otwarcia pliku \n\n           spróbuj jeszcze raz");
		strum.clear(strum.rdstate() & ~ios::badbit);
		return;
	}
	strum.seekg(0);
	strum << w0 << " " << w1 << " " << w2 << " \n" << a << " " << b;
	strum.close();
	i = 0;
	Label8->Caption = FloatToStrF(x1[i], ffFixed, 10, 2);
	Label9->Caption = FloatToStrF(x2[i], ffFixed, 10, 2);
	Label10->Caption = FloatToStrF(d[i], ffFixed, 10, 0);


}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	Wczytaj();

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
	time_t t;
	srand((unsigned)time(&t));
	w0 = (rand() % 200) - 100;
	w1 = (rand() % 200) - 100;
	w2 = (rand() % 200) - 100;
	wf0 = w0 / 100;
	wf1 = w1 / 100;
	wf2 = w2 / 100;
	x0 = -1;
	w0 = wf0;
	w1 = wf1;
	w2 = wf2;
	Label13->Caption = FloatToStrF(w0, ffFixed, 1, 3);
	Label1->Caption = FloatToStrF(w1, ffFixed, 1, 3);
	Label2->Caption = FloatToStrF(w2, ffFixed, 1, 3);
	Label21->Caption = "Losowanie wag zakończone";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
	S = x0 * w0 + StrToFloat(Edit1->Text)*w1 + StrToFloat(Edit2->Text)*w2;

	if (S >= 0)
	{
		y = 1;
	}
	else
	{
		y = -1;
	}
	if (y == 1)
	{
		Label25->Font->Height = 20;
		Label25->Font->Name = "Times New Roman";
		Label25->Font->Color = clBlue;
		Label25->Caption = "Zdrowy";
	}
	else
	{
		Label25->Font->Height = 12;
		Label25->Font->Name = "PMingLiU'";
		Label25->Font->Color = clRed;
		Label25->Caption = "Chory";
	}




}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
	exit(0);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
	Label13->Caption = "";
	Label1->Caption = "";
	Label2->Caption = "";
	Label8->Caption = "";
	Label9->Caption = "";
	Label10->Caption = "";
	Label17->Caption = "";
	Label18->Caption = "";
	Label20->Caption = "";
	Label21->Caption = "";
	Label11->Caption = "";
	Edit3->Text = "0";
	Label25->Caption = "";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{

	int dana = StrToInt(Edit3->Text);
	if (dana >= size)
	{
		Label11->Caption = "Nie ma takiej wartości i w tablicy";
		return;
	}
	else
	{
		Label11->Caption = "";
		Label8->Caption = FloatToStrF(x1[dana], ffFixed, 10, 2);
		Label9->Caption = FloatToStrF(x2[dana], ffFixed, 10, 2);
		Label10->Caption = FloatToStrF(d[dana], ffFixed, 10, 0);
	}
}
//---------------------------------------------------------------------------
