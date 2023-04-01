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
  keuzesGeel = 0, keuzesBlauw = 0;

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

void Territorium::vulVolgorde(){
  int temp[MaxDimensie*MaxDimensie];
  pair<int, int> tempPair;
  int temp_item;
  volgorde_eind = 0;

  for (int i = 0; i< hoogte; i++){
    for (int j = 0; j< breedte; j++){
      if (bord[i][j] < 0 && volgorde_eind < MaxDimensie*MaxDimensie){
        temp[volgorde_eind] = bord[i][j];
        volgorde[volgorde_eind] = make_pair(i, j);
        volgorde_eind++;
      }
    }
  }

  // Sorteert de volgorde array in oplopende volgorde
  for (int i = 0; i < volgorde_eind; i++){
    for (int j = i + 1; j < volgorde_eind; j++){
      if (temp[i] < temp[j]){
        temp_item = temp[i];
        tempPair = volgorde[i];
        temp[i] = temp[j];
        volgorde[i] = volgorde[j];
        temp[j] = temp_item;
        volgorde[j] = tempPair;
      }
    }
  }
}

void Territorium::verwijderKeuze(int keuze){
  // Verwijdert de gemaakte keuze uit de volgorde array 
  for (int i = keuze; i < (volgorde_eind+1);i++){
    volgorde[i] = volgorde[i+1];
  }
  volgorde[volgorde_eind-1] = make_pair(-1, -1);
  volgorde_eind--;
}

bool Territorium::leesInBord (const char* invoernaam)
{
int getal;
int getalcount = 0, hoogte_tel = 0, breedte_tel = 0;
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
        bord[hoogte_tel][breedte_tel] = getal;
        if (breedte_tel == breedte - 1) {
          breedte_tel = 0;
          hoogte_tel++;
        }else{
          breedte_tel++;
        }
     }
    getalcount++;
  }
  vulVolgorde();
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

for (int i= 0; i < hoogte; i++){
  for (int j=0; j < breedte; j++){
    if (bord[i][j]<0){
      return false;
    }
  }
}
return true;

} // eindstand


void Territorium::vakjesMogelijk(){
  
  //  welke vakjes nog mogelijk
  cout << "Mogelijke keuzes: ";
  int g=0;

  if (aanBeurt == 0){
      for (int i = (keuzesBlauw + keuzesGeel); i < volgorde_eind ; i++){
        if (volgorde[i] != make_pair(-1, -1) && g < keuzeAantalGeel){
          cout << "(" << volgorde[i].first << "," << volgorde[i].second << ") ";
          g++;
        }
      }
    keuzesGeel+=keuzeAantalGeel;
  } if (aanBeurt == 1){
      for (int i = (keuzesBlauw + keuzesGeel); i < volgorde_eind ; i++){
        if (volgorde[i] != make_pair(-1, -1) && g < keuzeAantalBlauw){
          cout << "(" << volgorde[i].first << "," << volgorde[i].second << ") ";
          g++;
        }
      }
    keuzesBlauw+=keuzeAantalBlauw;
  } cout << endl;
  cout << keuzesGeel << ", " << keuzesBlauw << endl;
}

//*************************************************************************

void Territorium::drukAf ()
{
  // TODO: implementeer deze memberfunctie
  for (int i=0; i < hoogte; i++){
    cout << i << " " << "|" << " ";
    for (int j=0; j < breedte; j++){
      if (bord[i][j] > 9 || bord[i][j] < -9){
        cout << bord[i][j] << " " ;
      } else if (bord[i][j] < 0 && bord[i][j] > -10){
        cout << " " << bord[i][j] << " " ;
      } else {
        cout << "  " << bord[i][j] << " " ;
      }
    } // for
    cout << " " << endl;
  } // for

  // breedte nummering
  cout << "    ";
  for (int z=0; z < breedte; z++){
    cout << "\u2014\u2014\u2014" << " ";
  }
  cout << endl << "    ";
  for (int k=0; k < breedte; k++){
    cout << "  " << k << " "; 
  }
  cout << endl;

  // speler beurt:
  cout << "Speler aan de beurt: ";
  if (aanBeurt==0){
    cout << "geel" << endl; ;
  } else{
    cout << "blauw" << endl;
  }

  vakjesMogelijk();
}  // drukAf


//*************************************************************************

pair<int,int> Territorium::bepaalZet (int j)
{
  // TODO: implementeer deze memberfunctie
  // moet alleen er nog voor zorgen dat niet de volgende keuze wordt genomen
  int g=0;
  if (aanBeurt==0 && j>=1 && j<= keuzeAantalGeel){ // geel 
    for (int i=0; i < volgorde_eind ; i++){
        if (volgorde[i] != make_pair(-1, -1) && g < keuzeAantalGeel){
          g++;
        }//if
        else if(g == j){
          return make_pair(volgorde[i].first, volgorde[i].second);
        }
    }
  }
  else if (aanBeurt==1 && j>=1 && j <= keuzeAantalBlauw){
    for (int i=0; i < volgorde_eind ; i++){
        if (volgorde[i] != make_pair(-1, -1) && g < keuzeAantalBlauw){
          g++;
        }//if
        else if(g == j){
          return make_pair(volgorde[i].first, volgorde[i].second);
        }
    }      
  }
  else{
    return make_pair(11,11);
  }
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