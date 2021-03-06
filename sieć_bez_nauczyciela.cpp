//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include <math.h>
#include <strstrea.h>
#include <fstream.h>
#include <iostream.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
TForm3 *Form3;
float w[6][8], x[8], y[6], xu[12][8];
float d1[100];
int size_ok, i;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
	Wyczysc_wagi();
}
//---------------------------------------------------------------------------
void TForm3::Losuj()
{
	Wyczysc_wagi();
	time_t t;
	float w1;
	srand((unsigned)time(&t));
	for (i = 0; i<8; i++)
	{
		for (int j = 0; j<6; j++)
		{
			w1 = (rand() % 100);
			w[j][i] = w1;
		}
	}
	//Wyswietl_wagi();
}

//---------------------------------------------------------------------------
void TForm3::Wczytaj()
{
	size_ok = 0;
	int end = 0;
	i = 0;
	fstream neuron("d:\\siec_neuron.dat", ios::in | ios::out);
	if (!neuron)
	{
		ShowMessage(" Błąd otwarcia pliku \n\n           spróbuj jeszcze raz");
		neuron.clear(neuron.rdstate() & ~ios::badbit);
		return;
	}
	neuron.seekg(0);
	do
	{
		neuron >> xu[i][0];
		neuron >> xu[i][1];
		neuron >> xu[i][2];
		neuron >> xu[i][3];
		neuron >> xu[i][4];
		neuron >> xu[i][5];
		neuron >> xu[i][6];
		neuron >> xu[i][7];
		if (neuron.eof())
		{
			end = 1;
			neuron.clear(neuron.rdstate() & ~ios::eofbit);
			neuron.close();
			Label1->Caption = "koniec pliku";
		}
		size_ok++;
		i++;
	} while (end == 0);
	size_ok = size_ok - 1;
	i++;
}
//---------------------------------------------------------------------------
void TForm3::Naucz_sie()
{
	int j, win, roz, lrn, ix1;
	for (j = 0; j<100; j++)
	{
		win = 0;
		d1[j] = 0;
	}
	double s, x3;
	win = 0;
	lrn = 0;
	do
	{
		lrn++;
		for (ix1 = 0; ix1<12; ix1++)
		{
			for (j = 0; j<6; j++)     //liczenie odległości
			{
				s = 0;
				for (int i1 = 0; i1<8; i1++)
				{
					s = s + ((xu[ix1][i1] - w[j][i1])*(xu[ix1][i1] - w[j][i1]));
				}
				x3 = sqrt(s);
				d1[j] = x3;
				s = 0;
			}
			win = 1;

			for (j = 0; j<6; j++)       //wyznaczanie zwycięzcy
			{
				roz = d1[j] - d1[win];
				if (roz < 0)
				{
					win = j;
				}

			}
			int i1 = 0;
			for (i1 = 0; i1<8; i1++)         //korekta wag
			{
				w[win][i1] = w[win][i1] + (0.1*(xu[ix1][i1] - w[win][i1]));
			}
		}
	} while (lrn != 2000);
	Wyswietl_wagi();
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Button2Click(TObject *Sender)
{
	Losuj();
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Button3Click(TObject *Sender)
{
	Wczytaj();
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Button4Click(TObject *Sender)
{
	Naucz_sie();
}
//---------------------------------------------------------------------------

void TForm3::Wyswietl_wagi()
{
	Label42->Caption = FloatToStrF(w[0][0], ffFixed, 10, 2);
	Label43->Caption = FloatToStrF(w[0][1], ffFixed, 10, 2);
	Label44->Caption = FloatToStrF(w[0][2], ffFixed, 10, 2);
	Label45->Caption = FloatToStrF(w[0][3], ffFixed, 10, 2);
	Label46->Caption = FloatToStrF(w[0][4], ffFixed, 10, 2);
	Label47->Caption = FloatToStrF(w[0][5], ffFixed, 10, 2);
	Label48->Caption = FloatToStrF(w[0][6], ffFixed, 10, 2);
	Label49->Caption = FloatToStrF(w[0][7], ffFixed, 10, 2);

	Label2->Caption = FloatToStrF(w[1][0], ffFixed, 10, 2);
	Label3->Caption = FloatToStrF(w[1][1], ffFixed, 10, 2);
	Label4->Caption = FloatToStrF(w[1][2], ffFixed, 10, 2);
	Label5->Caption = FloatToStrF(w[1][3], ffFixed, 10, 2);
	Label6->Caption = FloatToStrF(w[1][4], ffFixed, 10, 2);
	Label7->Caption = FloatToStrF(w[1][5], ffFixed, 10, 2);
	Label8->Caption = FloatToStrF(w[1][6], ffFixed, 10, 2);
	Label9->Caption = FloatToStrF(w[1][7], ffFixed, 10, 2);

	Label10->Caption = FloatToStrF(w[2][0], ffFixed, 10, 2);
	Label11->Caption = FloatToStrF(w[2][1], ffFixed, 10, 2);
	Label12->Caption = FloatToStrF(w[2][2], ffFixed, 10, 2);
	Label13->Caption = FloatToStrF(w[2][3], ffFixed, 10, 2);
	Label14->Caption = FloatToStrF(w[2][4], ffFixed, 10, 2);
	Label15->Caption = FloatToStrF(w[2][5], ffFixed, 10, 2);
	Label16->Caption = FloatToStrF(w[2][6], ffFixed, 10, 2);
	Label17->Caption = FloatToStrF(w[2][7], ffFixed, 10, 2);

	Label18->Caption = FloatToStrF(w[3][0], ffFixed, 10, 2);
	Label19->Caption = FloatToStrF(w[3][1], ffFixed, 10, 2);
	Label20->Caption = FloatToStrF(w[3][2], ffFixed, 10, 2);
	Label21->Caption = FloatToStrF(w[3][3], ffFixed, 10, 2);
	Label22->Caption = FloatToStrF(w[3][4], ffFixed, 10, 2);
	Label23->Caption = FloatToStrF(w[3][5], ffFixed, 10, 2);
	Label24->Caption = FloatToStrF(w[3][6], ffFixed, 10, 2);
	Label25->Caption = FloatToStrF(w[3][7], ffFixed, 10, 2);

	Label26->Caption = FloatToStrF(w[4][0], ffFixed, 10, 2);
	Label27->Caption = FloatToStrF(w[4][1], ffFixed, 10, 2);
	Label28->Caption = FloatToStrF(w[4][2], ffFixed, 10, 2);
	Label29->Caption = FloatToStrF(w[4][3], ffFixed, 10, 2);
	Label30->Caption = FloatToStrF(w[4][4], ffFixed, 10, 2);
	Label31->Caption = FloatToStrF(w[4][5], ffFixed, 10, 2);
	Label32->Caption = FloatToStrF(w[4][6], ffFixed, 10, 2);
	Label33->Caption = FloatToStrF(w[4][7], ffFixed, 10, 2);

	Label34->Caption = FloatToStrF(w[5][0], ffFixed, 10, 2);
	Label35->Caption = FloatToStrF(w[5][1], ffFixed, 10, 2);
	Label36->Caption = FloatToStrF(w[5][2], ffFixed, 10, 2);
	Label37->Caption = FloatToStrF(w[5][3], ffFixed, 10, 2);
	Label38->Caption = FloatToStrF(w[5][4], ffFixed, 10, 2);
	Label39->Caption = FloatToStrF(w[5][5], ffFixed, 10, 2);
	Label40->Caption = FloatToStrF(w[5][6], ffFixed, 10, 2);
	Label41->Caption = FloatToStrF(w[5][7], ffFixed, 10, 2);

}

//---------------------------------------------------------------------------

void TForm3::Wyczysc_wagi()
{
	Label42->Caption = "";
	Label43->Caption = "";
	Label44->Caption = "";
	Label45->Caption = "";
	Label46->Caption = "";
	Label47->Caption = "";
	Label48->Caption = "";
	Label49->Caption = "";

	Label2->Caption = "";
	Label3->Caption = "";
	Label4->Caption = "";
	Label5->Caption = "";
	Label6->Caption = "";
	Label7->Caption = "";
	Label8->Caption = "";
	Label9->Caption = "";

	Label10->Caption = "";
	Label11->Caption = "";
	Label12->Caption = "";
	Label13->Caption = "";
	Label14->Caption = "";
	Label15->Caption = "";
	Label16->Caption = "";
	Label17->Caption = "";

	Label18->Caption = "";
	Label19->Caption = "";
	Label20->Caption = "";
	Label21->Caption = "";
	Label22->Caption = "";
	Label23->Caption = "";
	Label24->Caption = "";
	Label25->Caption = "";

	Label26->Caption = "";
	Label27->Caption = "";
	Label28->Caption = "";
	Label29->Caption = "";
	Label30->Caption = "";
	Label31->Caption = "";
	Label32->Caption = "";
	Label33->Caption = "";

	Label34->Caption = "";
	Label35->Caption = "";
	Label36->Caption = "";
	Label37->Caption = "";
	Label38->Caption = "";
	Label39->Caption = "";
	Label40->Caption = "";
	Label41->Caption = "";

}