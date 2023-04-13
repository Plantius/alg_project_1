// Implementatie van klasse Territorium

#include "territorium.h"
#include "standaard.h"
#include <fstream>   // voor inlezen van bord
#include <iostream>
#include <set>
using namespace std;

//*************************************************************************

Territorium::Territorium ()
{
  hoogte=5;
  breedte=5;
  hoeveelNietBeschikbaar=25;
  keuzeAantalGeel=2;
  keuzeAantalBlauw=2;
  keuzesTotaal = 0;
  totale_zetten = 0, zetten_ronde = 0;
  fill(&bord[0][0], &bord[0][0]+(MaxDimensie*MaxDimensie), 0);
  fill(&bordKopie[0][0], &bordKopie[0][0]+(MaxDimensie*MaxDimensie), 0);
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
  fill(&bord[0][0], &bord[0][0]+(MaxDimensie*MaxDimensie), 0);
  fill(&bordKopie[0][0], &bordKopie[0][0]+(MaxDimensie*MaxDimensie), 0);
  vulBord();
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



// haalt alle volgordes uit bord
void Territorium::vulVolgorde(){
  volgorde_eind = 0;

  for (int i = 0; i< hoogte; i++){
    for (int j = 0; j< breedte; j++){
      if (bord[i][j] < 0 && volgorde_eind < MaxDimensie*MaxDimensie){
        volgordeBord temp = {bord[i][j], make_pair(i, j)};
        volgordeSet.insert(temp);
      }
    }
  } 
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

void Territorium::keuzeSpeler(int keuzeAantal){
  vakjeKeuzes.clear();
  if (volgordeSet.size() < keuzeAantal){
    for (auto k = volgordeSet.begin(); k != volgordeSet.end(); k++){
      volgordeBord temp = {k->volgorde_nr, k->volgorde_coord};
      vakjeKeuzes.insert(temp);
    }
  }
  else {
    auto beg_it = volgordeSet.begin();
    for(int i = 0; i < keuzesTotaal; i++){
      beg_it++;
    }
    auto end_it = beg_it;
    for (int i = 0; i < keuzeAantal; i++){
      end_it++;
    }
    
    for (auto k = beg_it; k != end_it; k++){
      volgordeBord temp = {k->volgorde_nr, k->volgorde_coord};
      vakjeKeuzes.insert(temp);
    }
    
    if (vakjeKeuzes.size() < keuzeAantal){
      for (auto k = volgordeSet.begin(); k != volgordeSet.end(); k++){
        if (vakjeKeuzes.size() < keuzeAantal){
          volgordeBord temp = {k->volgorde_nr, k->volgorde_coord};
          vakjeKeuzes.insert(temp);
        }
      }
    }
  }
}

void Territorium::vakjesMogelijk(){
  
  //  welke vakjes nog mogelijk
  if (aanBeurt == Geel -1){
    keuzeSpeler(keuzeAantalGeel);
  }else if (aanBeurt == Blauw -1){
    keuzeSpeler(keuzeAantalBlauw);
  } 
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
    cout << "Geel" << endl; ;
  } else if (aanBeurt == Blauw - 1){
    cout << "Blauw" << endl;
  }

  vakjesMogelijk();
  cout << "Mogelijke keuzes: ";
  for (auto i = vakjeKeuzes.begin(); i != vakjeKeuzes.end(); i++){
    cout << "(" << i->volgorde_coord.first << ", " << i->volgorde_coord.second << ") ";
  }cout << endl;
}  // drukAf


//*************************************************************************
// geeft mogelijke j-de zet
pair<int,int> Territorium::bepaalZet (int j)
{
  // De j-de keuze uit de keuze mogelijkheden lijst wordt genomen
  if (((aanBeurt == Geel-1 && j>=1 && j<= keuzeAantalGeel) || 
        (aanBeurt == Blauw -1 && j>=1 && j <= keuzeAantalBlauw)) && volgordeSet.size() != 0){ // geel 
      volgordeBord x = *next(vakjeKeuzes.begin(), j-1);
      return x.volgorde_coord;
  }
  return GeenZet; //als j niet overeenkomt met de keuze mogelijkheden returnt het GeenZet
  
}  // bepaalZet

//*************************************************************************


bool Territorium::zetSpeler(int speler, int keuzeAantal, int rij, int kolom){
  volgordeBord temp = {bord[rij][kolom], make_pair(rij, kolom)};
  auto coord = vakjeKeuzes.find(temp);
  if (vakjeKeuzes.find(temp) != vakjeKeuzes.end()){
    volgordeBord zet = {coord->volgorde_nr, coord->volgorde_coord};
    zetten.push_back(zet);
    totale_zetten++;
    zetten_ronde++;
    volgordeSet.erase(zet);

    if (speler == Geel -1){
      bord[rij][kolom] = Geel;
      keuzesTotaal+=keuzeAantalGeel;
    } else if (speler == Blauw -1){
      bord[rij][kolom] = Blauw;
      keuzesTotaal+=keuzeAantalBlauw;
    }

    if (keuzesTotaal >= volgordeSet.size()){
      keuzesTotaal = 0;
      zetten_ronde = 0;
    }
    aanBeurt = !aanBeurt;     
    return true;
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
  if(zetten.size() > 0){
    //cout<<"UNDO " << zetten.back().volgorde_coord.first << ", " << zetten.back().volgorde_coord.second << endl;
    if (aanBeurt == Geel -1 && keuzesTotaal != 0){
      keuzesTotaal -= keuzeAantalBlauw;
    } else if (aanBeurt == Blauw -1 && keuzesTotaal != 0){
      keuzesTotaal -= keuzeAantalGeel;
    } else if (aanBeurt == Geel -1 && keuzesTotaal == 0){
      keuzesTotaal = volgordeSet.size()-1;
    } else if (aanBeurt == Blauw -1 && keuzesTotaal == 0){
      keuzesTotaal = volgordeSet.size()-1;
    }

    volgordeSet.insert(zetten.back());

    bord[zetten.back().volgorde_coord.first][zetten.back().volgorde_coord.second] = zetten.back().volgorde_nr;
    zetten.pop_back();

    aanBeurt = !aanBeurt;
    totale_zetten--;
    if (zetten_ronde != 0){
      zetten_ronde--;
    }
    vakjesMogelijk();
    return true;
  }else {
    return false;
  }
  

}  // unDoeZet

//*************************************************************************

// kiest het grootste territorium 
int Territorium::grootsteTerritorium(int speler){
  int score = 0, hoogste_score = 0;
  fill(&bordKopie[0][0], &bordKopie[0][0]+(MaxDimensie*MaxDimensie), 0);

  for (int i = 0; i< hoogte; i++){
    for (int j = 0; j < breedte; j++){
      if (!bordKopie[i][j] && bord[i][j] == speler + 1){
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

int Territorium::telTerritorium(pair<int, int> loper , int speler){
  bordKopie[loper.first][loper.second] = true;
  int teller = 0;
  if (loper.first-1 >= 0 && !bordKopie[loper.first-1][loper.second] && bord[loper.first-1][loper.second] == speler + 1){
    teller += telTerritorium(make_pair(loper.first-1, loper.second), speler);
  }
  if (loper.second+1 < breedte && !bordKopie[loper.first][loper.second + 1] && bord[loper.first][loper.second+1] == speler + 1){
    teller += telTerritorium(make_pair(loper.first, loper.second+1), speler);
  }
  if (loper.first+1 < hoogte && !bordKopie[loper.first+1][loper.second] && bord[loper.first+1][loper.second] == speler + 1){
    teller += telTerritorium(make_pair(loper.first+1, loper.second), speler);
  }
  if (loper.second-1 >= 0 && !bordKopie[loper.first][loper.second - 1] && bord[loper.first][loper.second-1] == speler + 1){
    teller += telTerritorium(make_pair(loper.first, loper.second-1), speler);
  } 
  return teller+1;
}

// kijkt wat de hoogst haalbare score is met de beste zet
int Territorium::besteScore (pair<int,int> &besteZet,
                             long long &aantalStanden)
{
  int score = 0;
  pair<int,int> zet = make_pair(0,0);

  // bij het einde van het spel wordt de score berekend
  if (eindstand()){
    return grootsteTerritorium(aanBeurt) - grootsteTerritorium(!aanBeurt); 
  }
  else {  // als er geen eindstand is, worden alle zetten gespeeld
    for (int i = 0; i < hoogte; i++){
      for (int j = 0; j< breedte; j++){
        if (doeZet(i, j)){
          aantalStanden++;
          score = - besteScore(zet, aantalStanden);
          
          if (score > besteScoreHoogst){
            besteScoreHoogst = score;
            besteZet = make_pair(i, j);
          }
          score = 0;
          unDoeZet();
        }
      }
    }
  }     
  return besteScoreHoogst;
}// besteScore
//*************************************************************************

// bepaalt een goede zet op basis van de hoogste score
pair<int,int> Territorium::bepaalGoedeZet ()
{
  int hoogste_score = 0, score = 0;
  pair<int, int> goedeZet;
  
  if (!eindstand()){
    for (auto i = vakjeKeuzes.begin(); i != vakjeKeuzes.end(); i++){
      doeZet(i->volgorde_coord.first, i->volgorde_coord.second);
      score = grootsteTerritorium(!aanBeurt);

      if (score >= hoogste_score){
        hoogste_score = score;  
        goedeZet = i->volgorde_coord;
      }
      score = 0;
      unDoeZet();
    }
    return goedeZet;
  }
  return GeenZet;
}  // bepaalGoedeZet

//*************************************************************************

// Speelt een spel met bestescore tegen bepaalgoedezet
int Territorium::bepaalGoedeScore ()
{
  pair<int, int> zet1;
  pair<int, int> zet2;
  pair<int, int> besteZet;
  int score=0;
  int i =0;

  // zolang het spel niet klaar is worden er zetten gedaan
  while (eindstand()){
    zet1 = bepaalGoedeZet();
    doeZet(zet1.first, zet1.second);
    //cout << "zet1: " << zet1 << endl;
    i++;

    long long aantalStanden=0;
    besteScore(besteZet, aantalStanden);
    zet2= besteZet;
    //cout << "zet 2: " << zet2 << endl;
    doeZet(zet2.first, zet2.second);
    i++;
  }
  score= grootsteTerritorium(aanBeurt) - grootsteTerritorium(!aanBeurt);
  // score cancelt elkaar uit, kan dit ???
  cout << "1: " << grootsteTerritorium(aanBeurt) << " 2: " << grootsteTerritorium(!aanBeurt) << endl;
  while (i != 0){
    unDoeZet();
    i--;
  }
  
  return score;
}  // bepaalGoedeScore