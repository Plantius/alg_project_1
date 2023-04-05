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
  fill(zetten, zetten+(MaxDimensie*MaxDimensie), make_pair(-1, -1));
  fill(vakjeKeuzes, vakjeKeuzes+(MaxDimensie*MaxDimensie), make_pair(-1, -1));
  fill(volgorde, volgorde+(MaxDimensie*MaxDimensie), 0);
  fill(volgordeCoord, volgordeCoord+(MaxDimensie*MaxDimensie), make_pair(-1, -1));
  fill(&bord[0][0], &bord[0][0]+(MaxDimensie*MaxDimensie), 0);
  teller = 1;
  

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
  kopie();
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
          cout << "(" << volgordeCoord[i].first << ", " << volgordeCoord[i].second << "), ";
          vakjeKeuzes[g] = volgordeCoord[i];
          g++;
        }
      }
  } if (aanBeurt == 1){
      for (int i=keuzesGeel+keuzesBlauw-zetten_ronde; i < volgorde_eind ; i++){
        if (volgordeCoord[i] != make_pair(-1, -1) && g < keuzeAantalBlauw){
          cout << "(" << volgordeCoord[i].first << ", " << volgordeCoord[i].second << "), ";
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

  // De j-de keuze uit de keuze mogelijkheden lijst wordt genomen
  int g = 0;
  if (aanBeurt==0 && j>=1 && j<= keuzeAantalGeel && volgordeCoord[0] != make_pair(-1, -1)){ // geel 
    for (int i=0; i < volgorde_eind ; i++){
        if(g == j-1){
          return vakjeKeuzes[i];
        }
        if (volgordeCoord[i] != make_pair(-1, -1) && g < keuzeAantalGeel){
          g++;
        }//if
    }
  }
  else if (aanBeurt==1 && j>=1 && j <= keuzeAantalBlauw && volgordeCoord[0] != make_pair(-1, -1)){ // blauw
    for (int i=0; i < volgorde_eind ; i++){
        if(g == j-1){
          return vakjeKeuzes[i];
        }
        if (volgordeCoord[i] != make_pair(-1, -1) && g < keuzeAantalBlauw){
          g++;
        }//if
    }      
  }
  else{ //als j niet overeenkomt met de keuze mogelijkheden returnt het GeenZet
    return GeenZet;
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
}

bool Territorium::zetSpeler(int speler, int keuzeAantal, int rij, int kolom){
  for (int i = 0; i < keuzeAantal; i++){
      if (bord[rij][kolom] == volgorde[i+keuzesBlauw+keuzesGeel-zetten_ronde]
          && inArray(volgordeCoord[i+keuzesBlauw+keuzesGeel-zetten_ronde], vakjeKeuzes, keuzeAantal)){
        
        zettenArray(make_pair(rij, kolom), i+keuzesBlauw+keuzesGeel-zetten_ronde);
        verwijderKeuze(i+keuzesBlauw+keuzesGeel-zetten_ronde);
        zetten_ronde++;
        if (speler == 0){
          bord[rij][kolom] = Geel;
          keuzesGeel+=keuzeAantalGeel;
        } else if (speler == 1){
          bord[rij][kolom] = Blauw;
          keuzesBlauw+=keuzeAantalBlauw;
        }
        aanBeurt = !aanBeurt;
        if ((keuzesBlauw + keuzesGeel-zetten_ronde) >= volgorde_eind){
          keuzesBlauw = 0;
          keuzesGeel = 0;
          zetten_ronde = 0;
        }
        cout << "return true" << endl;
        return true;
      } else if (bord[rij][kolom] > 0){
        cout << "return false want > 0" << endl;
        return false;
      }
  }
  cout << "returnt laatste false, niet in loop" << endl;
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
//bijna klaar
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
    for (int r =0; r < hoogte ; r++){
      for (int k=0; k < breedte; k++){
        if(bord[r][k]==Geel && aanBeurt==0){
          geelstand++;
        }
        else if (bord[r][k]==Blauw && aanBeurt==1){
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
    if (aanBeurt==0){
      for (int i =1; i <= keuzeAantalGeel; i++){
        vakjeKeuzes[i-1] = bepaalZet(i);
        cout << "vakje " << vakjeKeuzes[i-1].first << vakjeKeuzes[i-1].second << endl;
      }
    }
    else if (aanBeurt==1){
      for (int i =1; i <= keuzeAantalGeel; i++){
          vakjeKeuzes[i-1] = bepaalZet(i);
          cout << "vakje " << vakjeKeuzes[i-1].first << vakjeKeuzes[i-1].second << endl;
      }
    }
    
    for (int j =0; j < keuzeAantalGeel ;j++){
      doeZet (vakjeKeuzes[j].first, vakjeKeuzes[j].second);
      cout << "vakje: " << vakjeKeuzes[j].first <<  vakjeKeuzes[j].second << endl; //doet hij dit echt 
      aantalStanden ++;
      score = - besteScore (besteZet, aantalStanden); //hij eindigt niet, geen eindstand
      if (score > bestescore){
        score = bestescore;
        besteZet= vakjeKeuzes[j];
      }
      cout << endl << "standen: " << aantalStanden << "score: " << score << endl;
      unDoeZet ();
     // onthoud beste score en bijbehorende zet
    }
    
  } // else
  return score; 
}  // besteScore

//*************************************************************************

void Territorium::kopie(){
  for(int i = 0; i < hoogte; i++){
    for (int j = 0; j < breedte; j++){
      bordKopie[i][j] = bord[i][j];
    }
  }
}

int Territorium::telTerritorium(pair<int, int> loper , int speler){
  if(bordKopie[loper.first][loper.second] < 0 && loper.first >= 0 && loper.second >= 0){
    for (int i = 0; i < 4; i++){
      if (i == 0 && bordKopie[loper.first-1][loper.second] == speler + 1){
        cout << "[0]" << endl;
        bordKopie[loper.first][loper.second] = 0;
        teller ++;
        telTerritorium(make_pair(loper.first-1, loper.second), speler);
      }
      if (i == 1 && bordKopie[loper.first][loper.second + 1] == speler + 1){
        cout << "[1]" << endl;
        bordKopie[loper.first][loper.second] = 0;
        teller ++;
        telTerritorium(make_pair(loper.first, loper.second+1), speler);
      }
      if (i == 2 && bordKopie[loper.first+1][loper.second] == speler + 1){
        cout << "[2]" << endl;
        bordKopie[loper.first][loper.second] = 0;
        teller ++;
        telTerritorium(make_pair(loper.first+1, loper.second), speler);
      }
      if (i == 3 && bordKopie[loper.first][loper.second-1] == speler + 1){
        cout << "[3]" << endl;
        bordKopie[loper.first][loper.second] = 0;
        teller ++;
        telTerritorium(make_pair(loper.first, loper.second-1), speler);
      }
    }
  }
  return teller;
}

pair<int,int> Territorium::bepaalGoedeZet ()
{
  int hoogste_score = 0, score = 0;
  pair<int, int> goedeZet;
  kopie();
  
  if (!eindstand()){
    if(aanBeurt == 0){
      for (int i = 0; i< keuzeAantalGeel; i++){
        cout << vakjeKeuzes[i].first << ", " << vakjeKeuzes[i].second << endl;
        score = telTerritorium(vakjeKeuzes[i], aanBeurt);

        if (score > hoogste_score){
          hoogste_score = score;  
          goedeZet = vakjeKeuzes[i];
        }
        kopie();
        teller = 1;
      }
    } if(aanBeurt == 1){
      for (int i = 0; i< keuzeAantalBlauw; i++){
        cout << vakjeKeuzes[i].first << ", " << vakjeKeuzes[i].second << endl;
        score = telTerritorium(vakjeKeuzes[i], aanBeurt);

        if (score > hoogste_score){
          hoogste_score = score;
          goedeZet = vakjeKeuzes[i];
        }
        kopie();
        teller = 1;
      }
    }
    cout << "Beste score: " << hoogste_score << ", (" << goedeZet.first << ", " << goedeZet.second << ") Speler: "<< aanBeurt << endl;
    return goedeZet;
  }
  return GeenZet;

}  // bepaalGoedeZet

//*************************************************************************

int Territorium::bepaalGoedeScore ()
{

// TODO: implementeer deze memberfunctie

  return 0;

}  // bepaalGoedeScore