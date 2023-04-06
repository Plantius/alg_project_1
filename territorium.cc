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
  totale_zetten = 0, zetten_ronde = 0;
  fill(zetten, zetten+(MaxDimensie*MaxDimensie), GeenZet);
  fill(vakjeKeuzes, vakjeKeuzes+(MaxDimensie*MaxDimensie), GeenZet);
  fill(volgorde, volgorde+(MaxDimensie*MaxDimensie), 0);
  fill(volgordeCoord, volgordeCoord+(MaxDimensie*MaxDimensie), GeenZet);
  fill(&bord[0][0], &bord[0][0]+(MaxDimensie*MaxDimensie), 0);
  kopie();
  teller = 0;
  

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
  fill(zetten, zetten+(MaxDimensie*MaxDimensie), GeenZet);
  fill(vakjeKeuzes, vakjeKeuzes+(MaxDimensie*MaxDimensie), GeenZet);
  fill(volgorde, volgorde+(MaxDimensie*MaxDimensie), 0);
  fill(volgordeCoord, volgordeCoord+(MaxDimensie*MaxDimensie), GeenZet);
  fill(&bord[0][0], &bord[0][0]+(MaxDimensie*MaxDimensie), 0);

  vulBord();
  kopie();
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
  for (int i=hoogte-1; i>0; --i) {
    for (int j = breedte-1; j>0; j--){
      swap(bord[i][j],bord[randomGetal(0, i)][randomGetal(0, j)]);
    }
  }
  vulVolgorde();
}

bool Territorium::inArray(pair<int, int> element, pair<int, int> arr[]){
  for (int i = 0; i < MaxDimensie*MaxDimensie; i++){
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

void Territorium::kopie(){
  for(int i = 0; i < hoogte; i++){
    for (int j = 0; j < breedte; j++){
      bordKopie[i][j] = bord[i][j];
    }
  }
}

// haalt alle volgordes uit bord
void Territorium::vulVolgorde(){
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
  volgordeCoord[volgorde_eind-1] = GeenZet;
  volgorde[volgorde_eind-1] = 0;
  volgorde_eind--;

  // Sorteert de volgorde array in oplopende volgorde
  sorteerVolgorde();
}

void Territorium::voegKeuzeToe(pair<int, int> coord){
  // Voegt de keuze toe aan de array van keuzes 
  volgordeCoord[volgorde_eind] = coord;
  volgorde[volgorde_eind] = zettenVolgorde[totale_zetten-1];
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

  for (int i = 0; i < hoogte; i++){
    for (int j = 0; j < breedte; j++){
      if (bord[i][j] <= 0){
        return false;
      }
    }
  }
  return true;

} // eindstand

void Territorium::keuzeSpeler(int speler, int keuzeAantal){
  int g = 0;
  if (sizeArray(volgordeCoord) < keuzeAantal){
    for (int k = 0; k < sizeArray(volgordeCoord); k++){
      cout << "(" << volgordeCoord[k].first << ", " << volgordeCoord[k].second << ") ";
      vakjeKeuzes[k+g] = volgordeCoord[k];
    }
    }
  else {
    for (int i=keuzesGeel+keuzesBlauw-zetten_ronde; i < volgorde_eind ; i++){
      cout << "i " << i << ", " << zetten_ronde  << ", G: " << keuzesGeel<< ", B: " << keuzesBlauw << "| EIND "<< volgorde_eind << endl;
      if (volgordeCoord[i] != GeenZet && g < keuzeAantal){
        cout << "(" << volgordeCoord[i].first << ", " << volgordeCoord[i].second << ") " ;
        vakjeKeuzes[g] = volgordeCoord[i];
        g++;
      }
    }
    
    for (int k = 0; k < volgorde_eind; k++){
      cout << "k " << k << ", " << g << endl;
      if(keuzeAantal-k-g > 0){
        cout << "(" << volgordeCoord[k].first << ", " << volgordeCoord[k].second << ") ";
        vakjeKeuzes[k+g] = volgordeCoord[k];
      }
    }
  }cout << endl;
  for (int i = 0; i< volgorde_eind; i++){
    cout << "(" << volgordeCoord[i].first << ", " << volgordeCoord[i].second << ") " ;
  }cout << endl;
  for (int i = 0; i< volgorde_eind; i++){
    cout << volgorde[i] << " ";
  }
}

void Territorium::vakjesMogelijk(){
  
  //  welke vakjes nog mogelijk
  cout << "Mogelijke keuzes: ";
  if (aanBeurt == Geel -1){
    keuzeSpeler(aanBeurt, keuzeAantalGeel);
  } if (aanBeurt == Blauw -1){
    keuzeSpeler(aanBeurt, keuzeAantalBlauw);
  } cout << endl;
  
}

//*************************************************************************

void Territorium::drukAf ()
{
  // TODO: implementeer deze memberfunctie
  for (int i=0; i < hoogte; i++){
    cout << i << " | " ;
    for (int j=0; j < breedte; j++){
      if (bord[i][j] < 0 ){
        cout << Leeg << " " ;
      } else {
        cout << bord[i][j] << " " ;
      }
    } // for
    cout << " " << endl;
  } // for

  // breedte nummering
  cout << "    ";
  for (int z=0; z < breedte; z++){
    cout << "\u2014\u2014";
  }
  cout << endl << "    ";
  for (int k=0; k < breedte; k++){
    cout << k << " "; 
  }
  cout << endl;

  // speler beurt:
  cout << "Speler aan de beurt: ";
  if (aanBeurt == Geel -1){
    cout << "geel" << endl; ;
  } else if (aanBeurt == Blauw - 1){
    cout << "blauw" << endl;
  }

  vakjesMogelijk();
}  // drukAf


//*************************************************************************
pair<int,int> Territorium::bepaalZet (int j)
{
  // De j-de keuze uit de keuze mogelijkheden lijst wordt genomen
  if (aanBeurt == Geel-1 && j>=1 && j<= keuzeAantalGeel && volgordeCoord[0] != GeenZet){ // geel 
    if (sizeArray(volgordeCoord) >= j){
      return vakjeKeuzes[j-1];
    }
  }
  else if (aanBeurt == Blauw -1 && j>=1 && j <= keuzeAantalBlauw && volgordeCoord[0] != GeenZet){ // blauw
    if (sizeArray(volgordeCoord) >= j){
      return vakjeKeuzes[j-1];
    }     
  }
  return GeenZet; //als j niet overeenkomt met de keuze mogelijkheden returnt het GeenZet
  
}  // bepaalZet

//*************************************************************************

int Territorium::sizeArray(pair<int, int> arr[]){
  for (int i = 0; i < hoogte*breedte; i++){
    if (arr[i] == GeenZet){
      return i;
    }
  }return -1;
}

bool Territorium::zetSpeler(int speler, int keuzeAantal, int rij, int kolom){
  for (int i = 0; i < keuzeAantal; i++){
    if (inArray(make_pair(rij, kolom), volgordeCoord) && make_pair(rij, kolom) == vakjeKeuzes[i]){
      for (int k = 0; k < volgorde_eind; k++){
        if(volgordeCoord[k] == vakjeKeuzes[i]){
          zetten[totale_zetten] = volgordeCoord[k];
          zettenVolgorde[totale_zetten] = volgorde[k];
          totale_zetten++;
          zetten_ronde++;
          verwijderKeuze(k); 

          if (speler == 0){
            bord[rij][kolom] = Geel;
            keuzesGeel+=keuzeAantalGeel;
          } else if (speler == 1){
            bord[rij][kolom] = Blauw;
            keuzesBlauw+=keuzeAantalBlauw;
          }
          if ((keuzesBlauw + keuzesGeel-zetten_ronde) >= volgorde_eind){
            keuzesBlauw = 0;
            keuzesGeel = 0;
            zetten_ronde = 0;
          }
          aanBeurt = !aanBeurt;      
          return true;
        }
      }
    }
  }
  return false;
}

bool Territorium::doeZet (int rij, int kolom)
{
  if (integerInBereik(rij, 0, hoogte-1) && integerInBereik(kolom, 0, breedte-1) && bord[rij][kolom] < 0){
    if (aanBeurt == Geel -1 && rij != -1 && kolom != -1){
      return zetSpeler(aanBeurt, keuzeAantalGeel, rij, kolom);
    }else if (aanBeurt == Blauw -1 && rij != -1 && kolom != -1){
      return zetSpeler(aanBeurt, keuzeAantalBlauw, rij, kolom);
    }
  }
  return false;
}  // doeZet

//*************************************************************************

bool Territorium::unDoeZet ()
{
  if(zetten[totale_zetten-1] != GeenZet && totale_zetten > 0){
    voegKeuzeToe(zetten[totale_zetten-1]);

    bord[zetten[totale_zetten-1].first][zetten[totale_zetten-1].second] = zettenVolgorde[totale_zetten-1];
    zetten[totale_zetten-1] = GeenZet;
    zettenVolgorde[totale_zetten-1] = 0;
    
    if (aanBeurt == Geel -1 && keuzesBlauw !=0){
      keuzesBlauw -= keuzeAantalBlauw;
    } else if (aanBeurt == Blauw -1 && keuzesGeel !=0){
      keuzesGeel -= keuzeAantalGeel;
    } else if (aanBeurt == Geel -1 && keuzesBlauw == 0){
      keuzesBlauw = volgorde_eind-1;
    } else if (aanBeurt == Blauw -1 && keuzesGeel == 0){
      keuzesGeel = volgorde_eind-1;
    }
    aanBeurt = !aanBeurt;
    totale_zetten--;
    if (zetten_ronde != 0){
      zetten_ronde--;
    }
    
    return true;
  }
  return false;

}  // unDoeZet

//*************************************************************************

int Territorium::grootsteTerritorium(int speler){
  int score = 0, hoogste_score = 0;
  teller = 0;
  kopie();

  for (int i = 0; i< hoogte; i++){
    for (int j = 0; j < breedte; j++){
      if (bordKopie[i][j] == speler + 1){
        score = telTerritorium(make_pair(i, j), speler);
        if (score > hoogste_score){
          hoogste_score = score;
        }
        kopie();
        teller=0;
      }
    }
  }
  return hoogste_score;
}

//bijna klaar
int Territorium::besteScore (pair<int,int> &besteZet,
                             long long &aantalStanden)
{
// TODO: implementeer deze memberfunctie
  int hoogste_score=0;
  int score=0;
  pair<int, int> zet;
  pair<int, int> mogelijk[MaxDimensie*MaxDimensie];

  // berekent eerst de stand van de spelers
  kopie();
  if (eindstand()){
    return grootsteTerritorium(aanBeurt) - grootsteTerritorium(!aanBeurt); 
  }// als er geen eindstand is, worden alle zetten gespeeld
  else{  // kijken welke keuzes iedereen heeft
    if (aanBeurt == Geel -1){ // geel
      for (int i =1; i <= keuzeAantalGeel; i++){
        mogelijk[i-1] = bepaalZet(i);
        cout << "vakje " << mogelijk[i-1].first << mogelijk[i-1].second << endl;
      }
    }
    else if (aanBeurt == Blauw -1){ //blauw
      for (int i =1; i <= keuzeAantalBlauw; i++){
        mogelijk[i-1] = bepaalZet(i);
        cout << "vakje " << mogelijk[i-1].first << mogelijk[i-1].second << endl;
      }
    }
    
    // recursie 
    for (int j =0; j < keuzeAantalGeel; j++){
      doeZet (mogelijk[j].first, mogelijk[j].second);
      cout << "vakje: " << mogelijk[j].first <<  mogelijk[j].second << endl;
      aantalStanden ++;
      score = - besteScore (besteZet, aantalStanden); //hij eindigt niet, geen eindstand
      if (score > hoogste_score){
        score = hoogste_score;
        besteZet= mogelijk[j];
      // }
      // cout << endl << "standen: " << aantalStanden << "score: " << score << endl;
      unDoeZet ();
      } 
    } // else
    return score; 
  } 
  return score;
}// besteScore
//*************************************************************************

int Territorium::telTerritorium(pair<int, int> loper , int speler){
  if(loper.first >= 0 && loper.second >= 0 && loper.first < hoogte && loper.second < breedte){
    for (int i = 0; i < 4; i++){
      if (i == 0 && loper.first > 0 && bordKopie[loper.first-1][loper.second] == speler + 1){
        bordKopie[loper.first][loper.second] = 0;
        telTerritorium(make_pair(loper.first-1, loper.second), speler);
      }
      if (i == 1 && loper.second < breedte-1 && bordKopie[loper.first][loper.second + 1] == speler + 1){
        bordKopie[loper.first][loper.second] = 0;
        telTerritorium(make_pair(loper.first, loper.second+1), speler);
      }
      if (i == 2 && loper.first < hoogte-1 && bordKopie[loper.first+1][loper.second] == speler + 1){
        bordKopie[loper.first][loper.second] = 0;
        telTerritorium(make_pair(loper.first+1, loper.second), speler);
      }
      if (i == 3 && loper.second > 0 && bordKopie[loper.first][loper.second - 1] == speler + 1){
        bordKopie[loper.first][loper.second] = 0;
        telTerritorium(make_pair(loper.first, loper.second-1), speler);
      }
      
    }
    teller ++;
    
  }
  return teller;
}

pair<int,int> Territorium::bepaalGoedeZet ()
{
  int hoogste_score = 0, score = 0;
  pair<int, int> goedeZet;
  teller = 0;
  kopie();
  
  if (!eindstand()){
    if(aanBeurt == Geel -1){
      for (int i = 0; i< keuzeAantalGeel; i++){
        score = telTerritorium(vakjeKeuzes[i], aanBeurt);

        if (score > hoogste_score){
          hoogste_score = score;  
          goedeZet = vakjeKeuzes[i];
        }
        kopie();
        teller = 0;
      }
    } if(aanBeurt == Blauw-1){
      for (int i = 0; i< keuzeAantalBlauw; i++){
        score = telTerritorium(vakjeKeuzes[i], aanBeurt);

        if (score > hoogste_score){
          hoogste_score = score;
          goedeZet = vakjeKeuzes[i];
        }
        kopie();
        teller = 0;
      }
    }
    return goedeZet;
  }
  return GeenZet;

}  // bepaalGoedeZet

//*************************************************************************

int Territorium::bepaalGoedeScore ()
{
  // TODO: implementeer deze memberfunctie
  pair<int, int> zet1;
  pair<int, int> zet2;
  pair<int, int> besteZet;
  pair<int, int> zettengedaan[MaxDimensie*MaxDimensie];
  int score=0;
  int i =0;

  while (eindstand()){
    zet1 = bepaalGoedeZet();
    doeZet(zet1.first, zet1.second);
    zettengedaan[i]=zet1;
    i++;

    long long aantalStanden=0;
    besteScore(besteZet, aantalStanden);
    zet2= besteZet;
    doeZet(zet2.first, zet2.second);
    zettengedaan[i]=zet2;
    i++;
  }
  score= grootsteTerritorium(aanBeurt) - grootsteTerritorium(!aanBeurt);
  while (i != 0){
    unDoeZet();
    i--;
  }
  
  return score;

}  // bepaalGoedeScore