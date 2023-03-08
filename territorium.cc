// Implementatie van klasse Territorium

#include "territorium.h"
#include "standaard.h"
#include <fstream>   // voor inlezen van bord
#include <iostream>

//*************************************************************************

Territorium::Territorium ()
{

// TODO: implementeer deze constructor, voorzover nodig
  hoogte=5;
  breedye=5;
  kansNietBeschikbaar=25;
  KeuzeAantalGeel=2;
  KeuzeAantalBlauw=2;
  MaxDimensie=20;

}  // default constructor

//*************************************************************************

// Constructor met parameters.
Territorium::Territorium (int nwHoogte, int nwBreedte,
                 int kansNietBeschikbaar,
                 int nwKeuzeAantalGeel, int nwKeuzeAantalBlauw)
{

// TODO: implementeer deze constructor

if (nwHoogte >= 1 && nwHoogte <= MaxDimensie){
  hoogte = nwHoogte;
}

else if (nwBreedte >= 1 && nwBreedte MaxDimensie){
  breedte= nwBreedte;
}

// kloppen de variabel namen?
else if (kansNietBeschikbaar >= 0 && kansNietBEschikbaar <= 100){
  kansNietBeschikbaar = kansNietBeschikbaar;
}

else if (nwKeuzeAantalGeel >=1){
  KeuzeAantalGeel = nwKeuzeAantalGeel;
}

else if (nwKeuzeAantalBlauw >=1){
  keuzeAantalBlauw = nwKeuzeAantalBlauw;
}

}  // constructor met parameters

//*************************************************************************

bool Territorium::leesInBord (const char* invoernaam)
{

// TODO: implementeer deze memberfunctie


  return false;

}  // leesInBord

//*************************************************************************

bool Territorium::eindstand ()
{

// TODO: implementeer deze memberfunctie

  return false;

} // eindstand

//*************************************************************************

void Territorium::drukAf ()
{

// TODO: implementeer deze memberfunctie

}  // drukAf

//*************************************************************************

pair<int,int> Territorium::bepaalZet (int j)
{

// TODO: implementeer deze memberfunctie

  return GeenZet;

}  // bepaalZet

//*************************************************************************

bool Territorium::doeZet (int rij, int kolom)
{

// TODO: implementeer deze memberfunctie

  return false;

}  // doeZet

//*************************************************************************

bool Territorium::unDoeZet ()
{

// TODO: implementeer deze memberfunctie

  return false;

}  // unDoeZet

//*************************************************************************

int Territorium::besteScore (pair<int,int> &besteZet,
                             long long &aantalStanden)
{

// TODO: implementeer deze memberfunctie

  return 0;

}  // besteScore

//*************************************************************************

pair<int,int> Territorium::bepaalGoedeZet ()
{

// TODO: implementeer deze memberfunctie

  return GeenZet;

}  // bepaalGoedeZet

//*************************************************************************

int Territorium::bepaalGoedeScore ()
{

// TODO: implementeer deze memberfunctie

  return 0;

}  // bepaalGoedeScore

