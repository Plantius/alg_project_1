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
  zetten = 0;

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

  if (nwBreedte >= 1 && nwBreedte <= MaxDimensie){
    breedte= nwBreedte;
  }

  // kloppen de variabel namen?
  if (kansNietBeschikbaar >= 0 && kansNietBeschikbaar <= 100){
    hoeveelNietBeschikbaar = kansNietBeschikbaar;
  }

  if (nwKeuzeAantalGeel >=1){
    keuzeAantalGeel = nwKeuzeAantalGeel;
  }

  if (nwKeuzeAantalBlauw >=1){
    keuzeAantalBlauw = nwKeuzeAantalBlauw;
  }

  vulBord();
  vulVolgorde();
}  // constructor met parameters

//*************************************************************************

void Territorium::vulBord(){
  int k = -1;
  for (int i = 0; i < hoogte; i++){
    for (int j = 0; j < breedte; j++){
      if (randomGetal(0, 100) < hoeveelNietBeschikbaar){
        bord[i][j] = 3;
      }else {
        bord[i][j] = k;
        k--;
      }
    }
  }
}

bool Territorium::inArray(pair<int, int> element, pair<int, int> arr[], int size){
  for (int i = 0; i < size; i++){
    if(element == arr[i]){
      return true;
    }
  }
  return false;
}

void Territorium::vulVolgorde(){
  pair<int, int> tempPair;
  int temp_item;
  volgorde_eind = 0;

  for (int i = 0; i< hoogte; i++){
    for (int j = 0; j< breedte; j++){
      if (bord[i][j] < 0 && volgorde_eind < MaxDimensie*MaxDimensie){
        volgorde[volgorde_eind] = bord[i][j];
        volgordeCoord[volgorde_eind] = make_pair(i, j);
        volgorde_eind++;
      }
    }
  }

  // Sorteert de volgorde array in oplopende volgorde
  for (int i = 0; i < volgorde_eind; i++){
    for (int j = i + 1; j < volgorde_eind; j++){
      if (volgorde[i] < volgorde[j]){
        temp_item = volgorde[i];
        tempPair = volgordeCoord[i];
        volgorde[i] = volgorde[j];
        volgordeCoord[i] = volgordeCoord[j];
        volgorde[j] = temp_item;
        volgordeCoord[j] = tempPair;
      }
    }
  }
}

void Territorium::verwijderKeuze(int keuze){
  // Verwijdert de gemaakte keuze uit de volgorde array 
  for (int i = keuze; i < (volgorde_eind+1);i++){
    volgordeCoord[i] = volgordeCoord[i+1];
    volgorde[i] = volgorde[i+1];
  }
  volgordeCoord[volgorde_eind-1] = make_pair(-1, -1);
  volgorde[volgorde_eind-1] = 0;
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
  file.close();
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
    if (bord[i][j] <= 0){
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
      for (int i=keuzesGeel+keuzesBlauw-zetten; i < volgorde_eind ; i++){
        if (volgordeCoord[i] != make_pair(-1, -1) && g < keuzeAantalGeel){
          cout << "(" << volgordeCoord[i].first << "," << volgordeCoord[i].second << ") ";
          vakjeKeuzes[g] = volgordeCoord[i];
          g++;
        }
      }
  } if (aanBeurt == 1){
      for (int i=keuzesGeel+keuzesBlauw-zetten; i < volgorde_eind ; i++){
        if (volgordeCoord[i] != make_pair(-1, -1) && g < keuzeAantalBlauw){
          cout << "(" << volgordeCoord[i].first << "," << volgordeCoord[i].second << ") ";
          vakjeKeuzes[g] = volgordeCoord[i];
          g++;
        }
      }
  } cout << endl;
  for (int i = 0; i < volgorde_eind+4; i++){
    cout << i<<"(" << volgordeCoord[i].first << "," << volgordeCoord[i].second << ") ";
  }
  cout << endl << "Kb: "<<keuzesBlauw << ", " << "Kg: "<< keuzesGeel << endl;

}

//*************************************************************************

void Territorium::drukAf ()
{
  // TODO: implementeer deze memberfunctie
  for (int i=0; i < hoogte; i++){
    cout << i << " | " ;
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
        if (volgordeCoord[i] != make_pair(-1, -1) && g < keuzeAantalGeel){
          g++;
        }//if
        else if(g == j){
          return make_pair(volgordeCoord[i].first, volgordeCoord[i].second);
        }
    }
  }
  else if (aanBeurt==1 && j>=1 && j <= keuzeAantalBlauw){
    for (int i=0; i < volgorde_eind ; i++){
        if (volgordeCoord[i] != make_pair(-1, -1) && g < keuzeAantalBlauw){
          g++;
        }//if
        else if(g == j){
          return make_pair(volgordeCoord[i].first, volgordeCoord[i].second);
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
  cout << rij << kolom << ", " << aanBeurt << "|" << zetten << endl;
  if ((keuzesBlauw + keuzesGeel) >= volgorde_eind){
    keuzesBlauw = 0;
    keuzesGeel = 0;
    zetten = 0;
  }
  // TODO: implementeer deze memberfunctie
  if (aanBeurt == 0 && rij != -1 && kolom != -1){
    for (int i = 0; i < keuzeAantalGeel; i++){
      if (bord[rij][kolom] == volgorde[i+keuzesBlauw+keuzesGeel-zetten] && inArray(volgordeCoord[i+keuzesBlauw+keuzesGeel-zetten], vakjeKeuzes, keuzeAantalGeel)){
        bord[rij][kolom] = 1;

        verwijderKeuze(i+keuzesBlauw+keuzesGeel-zetten);
        zetten++;
        keuzesGeel+=keuzeAantalGeel;
        cout << keuzesGeel << ", "  << true << endl;
        aanBeurt = !aanBeurt;
        return true;
      } else if (bord[rij][kolom] > 0){
        cout << keuzesGeel << ", "  << false << endl;
        return false;
      }
    }
  }else if (aanBeurt == 1 && rij != -1 && kolom != -1){
    for (int i = 0; i < keuzeAantalBlauw; i++){
      if (bord[rij][kolom] == volgorde[i+keuzesBlauw+keuzesGeel-zetten] && inArray(volgordeCoord[i+keuzesBlauw+keuzesGeel-zetten], vakjeKeuzes, keuzeAantalBlauw)){
        bord[rij][kolom] = 2;

        verwijderKeuze(i+keuzesBlauw+keuzesGeel-zetten);
        zetten++;
        keuzesBlauw+=keuzeAantalBlauw;
        cout << keuzesBlauw << ", "  << true << endl;
        aanBeurt = !aanBeurt;
        return true;
      } else if (bord[rij][kolom] > 0){
        cout << keuzesBlauw << ", "  << false << endl;
        return false;
      }
    }
  } 
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