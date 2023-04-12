// Implementatie van klasse Territorium

#include "territorium.h"
#include "standaard.h"
#include <fstream>   // voor inlezen van bord
#include <iostream>
using namespace std;

//*************************************************************************

Territorium::Territorium ()
{
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
  besteScoreHoogst = 0;
  

}  // default constructor

//*************************************************************************

// Constructor met parameters.
Territorium::Territorium (int nwHoogte, int nwBreedte,
                 int kansNietBeschikbaar,
                 int nwKeuzeAantalGeel, int nwKeuzeAantalBlauw)
{
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

// vult voor een nieuw bord willekeurige getallen
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

// kijkt of een paar in een array zit
bool Territorium::inArray(pair<int, int> element, pair<int, int> arr[]){
  for (int i = 0; i < MaxDimensie*MaxDimensie; i++){
    if(element == arr[i]){
      return true;
    }
  }
  return false;
}

// geeft grootte van array terug
int Territorium::sizeArray(pair<int, int> arr[]){
  for (int i = 0; i < hoogte*breedte+1; i++){
    if (arr[i] == GeenZet){
      return i;
    }
  }return -1;
}

// sorteert de vul volgorde
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

// maakt kopie van bord
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

// leest een file in over bord informatie
bool Territorium::leesInBord (const char* invoernaam)
{
  int getal;
  int getalcount = 0, hoogte_tel = 0, breedte_tel = 0;

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

}  // leesInBord

//*************************************************************************

// kijkt of het spel klaar is
bool Territorium::eindstand ()
{
  // geen eindstand wanneer nog een ongevuld vakje is
  for (int i = 0; i < hoogte; i++){
    for (int j = 0; j < breedte; j++){
      if (bord[i][j] < 0){
        return false;
      }
    }
  }
  return true;

} // eindstand

void Territorium::keuzeSpeler(int speler, int keuzeAantal){
  int g = 0;
  fill(vakjeKeuzes, vakjeKeuzes+(MaxDimensie*MaxDimensie), GeenZet);

  if (sizeArray(volgordeCoord) < keuzeAantal){
    for (int k = 0; k < sizeArray(volgordeCoord); k++){
      cout << "(" << volgordeCoord[k].first << ", " << volgordeCoord[k].second << ") ";
      vakjeKeuzes[k] = volgordeCoord[k];
    }
  }
  else {
    for (int i=keuzesGeel+keuzesBlauw-zetten_ronde; i < volgorde_eind ; i++){
      if (volgordeCoord[i] != GeenZet && g < keuzeAantal){
        cout << "(" << volgordeCoord[i].first << ", " << volgordeCoord[i].second << ") " ;
        vakjeKeuzes[g] = volgordeCoord[i];
        g++;
      }
    }
    
    for (int k = 0; k < volgorde_eind; k++){
      if(keuzeAantal-k-g > 0){
        cout << "(" << volgordeCoord[k].first << ", " << volgordeCoord[k].second << ") ";
        vakjeKeuzes[k+g] = volgordeCoord[k];
      }
    }
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
// geeft mogelijke j-de zet
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

bool Territorium::zetSpeler(int speler, int keuzeAantal, int rij, int kolom){
  for (int i = 0; i < keuzeAantal; i++){
    if (inArray(make_pair(rij, kolom), volgordeCoord) && make_pair(rij, kolom) == vakjeKeuzes[i]){
      cout<< "DOE " << vakjeKeuzes[i].first << ":" << vakjeKeuzes[i].second << endl;
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
    vakjesMogelijk();   
    if (aanBeurt == Geel -1 && rij != -1 && kolom != -1){
      return zetSpeler(aanBeurt, keuzeAantalGeel, rij, kolom);
    }else if (aanBeurt == Blauw -1 && rij != -1 && kolom != -1){
      return zetSpeler(aanBeurt, keuzeAantalBlauw, rij, kolom);
    }
  }
  return false;
}  // doeZet

bool Territorium::unDoeZet ()
{
  if(zetten[totale_zetten-1] != GeenZet && totale_zetten > 0){
    cout<<"UNDO " <<zetten[totale_zetten-1].first << ", " << zetten[totale_zetten-1].second << endl;
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
  }else {
    return false;
  }
  

}  // unDoeZet

//*************************************************************************

// kiest het grootste territorium 
int Territorium::grootsteTerritorium(int speler){
  int score = 0, hoogste_score = 0;
  teller = 0;

  for (int i = 0; i< hoogte; i++){
    for (int j = 0; j < breedte; j++){
      if (bordKopie[i][j] != 0 && bord[i][j] == speler + 1){
        score = telTerritorium(make_pair(i, j), speler);
        if (score > hoogste_score){
          hoogste_score = score;
        }
        score = 0;
      }
    }
  }
  return hoogste_score;
}

//bijna klaar
int Territorium::besteScore (pair<int,int> &besteZet,
                             long long &aantalStanden)
{
  int score = 0;
  pair<int,int> zet = make_pair(0,0);

  // berekent eerst de stand van de spelers
  if (eindstand()){
    
    return grootsteTerritorium(aanBeurt) - grootsteTerritorium(!aanBeurt); 
  }// als er geen eindstand is, worden alle zetten gespeeld
  else {  // kijken welke keuzes iedereen heeft
    for (int i = 0; i < hoogte; i++){
      for (int j = 0; j< breedte; j++){
        if (doeZet(i, j)){
          aantalStanden++;
          score = - besteScore(zet, aantalStanden);
          unDoeZet();
          if (score > besteScoreHoogst){
            besteScoreHoogst = score;
            besteZet = make_pair(i, j);
          }
          score = 0;
          
        }
      }
    }
  }     
  return besteScoreHoogst;
}// besteScore
//*************************************************************************

int Territorium::telTerritorium(pair<int, int> loper , int speler){
  teller = 0;
  if (loper.first-1 >= 0 && bordKopie[loper.first-1][loper.second] != 0 && bord[loper.first-1][loper.second] == speler + 1){
    bordKopie[loper.first -1][loper.second] = 0;
    telTerritorium(make_pair(loper.first-1, loper.second), speler);
  }
  if (loper.second+1 < breedte && bordKopie[loper.first][loper.second + 1] != 0 && bord[loper.first][loper.second+1] == speler + 1){
    bordKopie[loper.first][loper.second+1] = 0;
    telTerritorium(make_pair(loper.first, loper.second+1), speler);
  }
  if (loper.first+1 < hoogte && bordKopie[loper.first+1][loper.second] != 0 && bord[loper.first+1][loper.second] == speler + 1){
    bordKopie[loper.first+1][loper.second] = 0;
    telTerritorium(make_pair(loper.first+1, loper.second), speler);
  }
  if (loper.second-1 >= 0 && bordKopie[loper.first][loper.second - 1] != 0 && bord[loper.first][loper.second-1] == speler + 1){
    bordKopie[loper.first][loper.second-1] = 0;
    telTerritorium(make_pair(loper.first, loper.second-1), speler);
  } 
  return teller++;
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