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
  breedte=5;
  NietBeschikbaar=25;
  keuzeAantalGeel=2;
  keuzeAantalBlauw=2;
  //MaxDimensie=20;

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

else if (nwBreedte >= 1 && nwBreedte <= MaxDimensie){
  breedte= nwBreedte;
}

// kloppen de variabel namen?
else if (kansNietBeschikbaar >= 0 && kansNietBeschikbaar <= 100){
  NietBeschikbaar = kansNietBeschikbaar;
}

else if (nwKeuzeAantalGeel >=1){
  keuzeAantalGeel = nwKeuzeAantalGeel;
}

else if (nwKeuzeAantalBlauw >=1){
  keuzeAantalBlauw = nwKeuzeAantalBlauw;
}

}  // constructor met parameters

//*************************************************************************

bool Territorium::leesInBord (const char* invoernaam)
{

// TODO: implementeer deze memberfunctie

// Eerst kijken of die geopend kan worden: nog niet goed
  ifstream input;
  input.open(invoernaam.c_str(), ios::in);
  if(ios::fail()== true){
    return false;
  }

  //invoernaam = _invoernaam;
  return false;

  // Staat het bord goed?

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

