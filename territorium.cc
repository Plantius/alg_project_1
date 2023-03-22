// Implementatie van klasse Territorium

#include "territorium.h"
#include "standaard.h"
#include <fstream>   // voor inlezen van bord
#include <iostream>
using namespace std;

//*************************************************************************

Territorium::Territorium ()
{

// TODO: implementeer deze constructor, voorzover nodig
  hoogte=5;
  breedte=5;
  hoeveelNietBeschikbaar=25;
  keuzeAantalGeel=2;
  keuzeAantalBlauw=2;

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
  hoeveelNietBeschikbaar = kansNietBeschikbaar;
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
int getal;
int getalcount = 0, hoogte_tel = 0;
// TODO: implementeer deze memberfunctie
ifstream file(invoernaam);
if (file.good()){
  while (file.good()){
    file >> getal;
    if (getalcount == 0){
      hoogte = getal;
    } if (getalcount == 1){
      breedte = getal;
    } if(getalcount == hoogte*breedte + 2){
      keuzeAantalGeel = getal;
    } if(getalcount == hoogte*breedte + 3){
      keuzeAantalBlauw = getal;
    } if (getalcount > 1 && getalcount < hoogte*breedte + 2){
        bord[hoogte_tel][getalcount-2] = getal;
        cout << getal << " ";
        if ((getalcount-1) % breedte == 0 && (getalcount-2 != 0)){
          hoogte_tel++;
          cout << endl;
        } 
    }
    getalcount++;
  }
  cout << hoogte << ", " << breedte << endl;
  cout << keuzeAantalGeel << ", " << keuzeAantalBlauw << endl;
  return true;
}
else{
  cout << "Deze file is niet leesbaar." << endl;
  return false;
}

file.close();

// Staat het bord goed?

}  // leesInBord

//*************************************************************************

bool Territorium::eindstand ()
{

// TODO: implementeer deze memberfunctie
char variabel;

for (int i= 0; i <= hoogte; i++){
  for (int j=0; j <= breedte; j++){
    if (bord[i][j]<0){
      return false;
    }
  }
}
return true;

} // eindstand

//*************************************************************************

void Territorium::drukAf ()
{
  // TODO: implementeer deze memberfunctie
  for (int i=0; i < hoogte; i++){
      cout << i << " " << "|" << " ";
    for (int j=0; j < breedte; j++){
      cout << bord[i][j] << " " ;

      if ((i == (hoogte/2) && hoogte >1 ) && (j == breedte -1 && breedte >1)){
        cout << "Speler aan de beurt: " << aanBeurt;
      } // if

    } // for
    cout << " " << endl;
  } // for

  // breedte nummering
  cout << "    ";
  for (int z=0; z < breedte; z++){
    cout << "\u2014" << " ";
  }
  cout << endl << "    ";
  for (int k=0; k < breedte; k++){
    cout << k << " "; 
  }
  cout << endl;

  //  welke vakjes nog mogelijk
  if (aanBeurt == 0){
    while(int g < keuzeAantalGeel){
      
    }
  }

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

