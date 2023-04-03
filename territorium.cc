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
  zetten_ronde = 0;
  fill(zetten, zetten+(MaxDimensie*MaxDimensie), make_pair(-1, -1) );
  fill(volgorde, volgorde+(MaxDimensie*MaxDimensie), 0);
  fill(volgordeCoord, volgordeCoord+(MaxDimensie*MaxDimensie), make_pair(-1, -1));

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

void Territorium::sorteerVolgorde(){
  pair<int, int> tempPair;
  int temp_item;
  
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
  sorteerVolgorde();
}

void Territorium::verwijderKeuze(int keuze){
  // Verwijdert de gemaakte keuze uit de volgorde array 
  for (int i = keuze; i < volgorde_eind ;i++){
    volgordeCoord[i] = volgordeCoord[i+1];
    volgorde[i] = volgorde[i+1];
  }
  volgordeCoord[volgorde_eind-1] = make_pair(-1, -1);
  volgorde[volgorde_eind-1] = 0;
  volgorde_eind--;
  sorteerVolgorde();
}

void Territorium::voegKeuzeToe(pair<int, int> coord){
  // Voegt de keuze toe aan de array van keuzes 
  volgordeCoord[volgorde_eind] = coord;
  volgorde[volgorde_eind] = zettenVolgorde[totale_zetten];
  volgorde_eind++;

  // Sorteert de volgorde array in oplopende volgorde
  sorteerVolgorde();
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
      for (int i=keuzesGeel+keuzesBlauw-zetten_ronde; i < volgorde_eind ; i++){
        if (volgordeCoord[i] != make_pair(-1, -1) && g < keuzeAantalGeel){
          cout << "(" << volgordeCoord[i].first << "," << volgordeCoord[i].second << ") ";
          vakjeKeuzes[g] = volgordeCoord[i];
          g++;
        }
      }
  } if (aanBeurt == 1){
      for (int i=keuzesGeel+keuzesBlauw-zetten_ronde; i < volgorde_eind ; i++){
        if (volgordeCoord[i] != make_pair(-1, -1) && g < keuzeAantalBlauw){
          cout << "(" << volgordeCoord[i].first << "," << volgordeCoord[i].second << ") ";
          vakjeKeuzes[g] = volgordeCoord[i];
          g++;
        }
      }
  } cout << endl;
  for (int i = 0; i < volgorde_eind; i++){
    cout << i<<"(" << volgordeCoord[i].first << "," << volgordeCoord[i].second << ") ";
  } cout << endl;
  for (int i = 0; i < volgorde_eind; i++){
    cout << volgorde[i] << " ";
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
    return make_pair(MaxDimensie+1,MaxDimensie+1);
  }
}  // bepaalZet

//*************************************************************************

void Territorium::zettenArray(pair<int, int> zet, int keuze){
  for (int i = 0; i < MaxDimensie*MaxDimensie; i++){
    if (zetten[i] == make_pair(-1, -1)){
      totale_zetten = i;
      break;
    }
  }
  zettenVolgorde[totale_zetten] = volgorde[keuze];
  zetten[totale_zetten] = zet;
  for (int i = 0; i< totale_zetten+1; i++){
    cout << "("<< zetten[i].first <<", " << zetten[i].second << ")" << " | " << zettenVolgorde[i] << " ";
  }cout <<endl;
}

bool Territorium::zetSpeler(int speler, int keuzeAantal, int rij, int kolom){
  cout << speler << " | " << keuzeAantal << " | " << rij << " | " << kolom << endl;
  cout << bord[rij][kolom] << endl;
  for (int i = 0; i < keuzeAantal; i++){
      if (bord[rij][kolom] == volgorde[i+keuzesBlauw+keuzesGeel-zetten_ronde]
          && inArray(volgordeCoord[i+keuzesBlauw+keuzesGeel-zetten_ronde], vakjeKeuzes, keuzeAantal)){
        
        zettenArray(make_pair(rij, kolom), i+keuzesBlauw+keuzesGeel-zetten_ronde);
        cout << "TEST " << i+keuzesBlauw+keuzesGeel-zetten_ronde <<" " << volgorde[i+keuzesBlauw+keuzesGeel-zetten_ronde] << endl;
        verwijderKeuze(i+keuzesBlauw+keuzesGeel-zetten_ronde);
        zetten_ronde++;
        if (speler == 0){
          bord[rij][kolom] = 1;
          keuzesGeel+=keuzeAantalGeel;
        } else if (speler == 1){
          bord[rij][kolom] = 2;
          keuzesBlauw+=keuzeAantalBlauw;
        }
        aanBeurt = !aanBeurt;
        if ((keuzesBlauw + keuzesGeel-zetten_ronde) >= volgorde_eind){
          keuzesBlauw = 0;
          keuzesGeel = 0;
          zetten_ronde = 0;
        }
        return true;
      } else if (bord[rij][kolom] > 0){
        cout << keuzesBlauw << ", "  << false << endl;
        return false;
      }
  }
  return false;
}

bool Territorium::doeZet (int rij, int kolom)
{
  if (integerInBereik(rij, 0, hoogte-1) && integerInBereik(kolom, 0, breedte-1) && bord[rij][kolom] < 0){
    if (aanBeurt == 0 && rij != -1 && kolom != -1){
      return zetSpeler(aanBeurt, keuzeAantalGeel, rij, kolom);
    }else if (aanBeurt == 1 && rij != -1 && kolom != -1){
      return zetSpeler(aanBeurt, keuzeAantalBlauw, rij, kolom);
    }
  }
  return false;
}  // doeZet

//*************************************************************************

bool Territorium::unDoeZet ()
{
  if(zetten[totale_zetten] != make_pair(-1, -1) && totale_zetten >= 0){
    cout << totale_zetten << endl;
    voegKeuzeToe(zetten[totale_zetten]);
    if (aanBeurt == 0){
      keuzesBlauw -= keuzeAantalBlauw;
    }else if (aanBeurt == 1){
      keuzesGeel -= keuzeAantalGeel;
    }
    bord[zetten[totale_zetten].first][zetten[totale_zetten].second] = zettenVolgorde[totale_zetten];
    aanBeurt = !aanBeurt;
    zetten[totale_zetten] = make_pair(-1, -1);
    zettenVolgorde[totale_zetten] = 0;
    totale_zetten--;
    zetten_ronde--;
    return true;
  }
  return false;

}  // unDoeZet

//*************************************************************************

int Territorium::besteScore (pair<int,int> &besteZet,
                             long long &aantalStanden)
{
// TODO: implementeer deze memberfunctie

int blauwstand=0;
int geelstand=0;
int bestescore=0;
int score=0;

  // berekent eerst de stand van de spelers
  if (eindstand()){
    for (int r =0; r <= hoogte ; r++){
      for (int k=0; k <= breedte; k++){
        if(bord[r][k]==1 && aanBeurt==0){
          geelstand++;
        }
        else if (bord[r][k]==2 && aanBeurt==1){
          blauwstand++;
        }
      }
    }
    if (aanBeurt==0){
      return geelstand;
    }
    else{
      return blauwstand;
    }
  }// als er geen eindstand is, worden alle zetten gespeeld

  else{ // alle mogelijke zetten z 
    // kijken welke keuzes iedereen heeft
    int g=0;
    if (aanBeurt == 0){ // geel
      for (int i=keuzesGeel+keuzesBlauw-zetten_ronde; i < volgorde_eind ; i++){
        if (volgordeCoord[i] != make_pair(-1, -1) && g < keuzeAantalGeel){
          vakjeKeuzes[g] = volgordeCoord[i];
          g++;
        }
      }
    }else if (aanBeurt == 1){ // blauw
      for (int i=keuzesGeel+keuzesBlauw-zetten_ronde; i < volgorde_eind ; i++){
        if (volgordeCoord[i] != make_pair(-1, -1) && g < keuzeAantalBlauw){
          vakjeKeuzes[g] = volgordeCoord[i];
          g++;
         }
      }
    }
    for (int j =0; j < volgorde_eind ;j++){
      doeZet (vakjeKeuzes[j].first, vakjeKeuzes[j].second);
      aantalStanden ++;
      score = - besteScore (besteZet, aantalStanden);
      if (score > bestescore){
        score = bestescore;
        besteZet= vakjeKeuzes[j];
      }
      unDoeZet ();
     // onthoud beste score en bijbehorende zet
    }
  } // else
  return score;
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