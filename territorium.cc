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
  offset = 0;
  fill(&bord[0][0], &bord[0][0]+(MaxDimensie*MaxDimensie), 0);
  fill(&bordKopie[0][0], &bordKopie[0][0]+(MaxDimensie*MaxDimensie), false);
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
  fill(&bordKopie[0][0], &bordKopie[0][0]+(MaxDimensie*MaxDimensie), false);
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
  // zorgt dat het spel een set heeft met een vulvolgorde
  vulVolgorde();
}

// verzamelt alle mogelijke zetten en stopt het in een set.
void Territorium::vulVolgorde(){
  volgorde_eind = 0;

  for (int i = 0; i< hoogte; i++){
    for (int j = 0; j< breedte; j++){
      if (bord[i][j] < 0 && volgorde_eind < MaxDimensie*MaxDimensie){
        volgordeBord temp = {bord[i][j], make_pair(i, j), -bord[i][j]};
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
  
  // leest het bord, de hoogte, breedte en keuzeaantallen in
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
    // bepaalt alle lege vakjes
    vulVolgorde();
    file.close();
    return true;
  }
  else{
    file.close();
    cout << "Deze file is niet leesbaar." << endl;
    file.close();
    return false;
  }
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

// bepaalt de precieze keuze volgorde waaruit een speler mag kiezen op basis van een keuzeaantal
void Territorium::keuzeSpeler(int keuzeAantal){
  // keuzetotaal=0 aan het begin van een spel
  vakjeKeuzes.clear();
  int size = volgordeSet.size();

  // als de vorige zet begon aan het einde vd set
  if (keuzesTotaal <  0){
    keuzesTotaal = (size+keuzesTotaal-1);
  } if (keuzesTotaal >= (size)){ // als het aantal keuzes gelijk is aan de size vd volgorde set
    keuzesTotaal -= (size);
  } 
  if (size < keuzeAantal){ // als de size kleiner is dan een keuzeaantal
    for (auto k = volgordeSet.begin(); k != volgordeSet.end(); k++){
      volgordeBord temp = {k->volgorde_nr, k->volgorde_coord};
      vakjeKeuzes.insert(temp);
    }
  }

  // voor andere opties wordt de volgorde van de keuzes bepaald
  else {
    auto beg_it = volgordeSet.begin();
    for(int i = 0; i < keuzesTotaal; i++){ // kijkt naar alle keuzes die zijn gemaakt
      beg_it++;
    }
    auto end_it = beg_it;
    for (int i = 0; i < keuzeAantal; i++){ // kijkt naar alle mogelijke zetten
      if(end_it != volgordeSet.end()){
        end_it++;
      }
    }
    
    for (auto k = beg_it; k != end_it; k++){
      volgordeBord temp = {k->volgorde_nr, k->volgorde_coord};
      vakjeKeuzes.insert(temp);
    }
    
    if (size-keuzesTotaal < keuzeAantal){
      for (auto k = volgordeSet.begin(); k != volgordeSet.end(); k++){
        int size_keuzes = vakjeKeuzes.size();
        if (size_keuzes < keuzeAantal){
          volgordeBord temp = {k->volgorde_nr, k->volgorde_coord};
          vakjeKeuzes.insert(temp);
        }
      }
    }
  }
}


// per speler worden de mogelijke vakjes bepaald
void Territorium::vakjesMogelijk(){
  if (aanBeurt == Geel -1){
    keuzeSpeler(keuzeAantalGeel);
  }else if (aanBeurt == Blauw -1){
    keuzeSpeler(keuzeAantalBlauw);
  } 

}

//*************************************************************************

// drukt het spelbord af
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

  // laat de mogelijke keuzes zien
  vakjesMogelijk();
  if (!eindstand()){
    cout << "Mogelijke keuzes: ";
    for (auto i = vakjeKeuzes.begin(); i != vakjeKeuzes.end(); i++){
      cout << "(" << i->volgorde_coord.first << "," << i->volgorde_coord.second << ")  ";
    }cout << endl;
  }
}  // drukAf


//*************************************************************************
// geeft mogelijke j-de zet
pair<int,int> Territorium::bepaalZet (int j)
{
  // De j-de keuze uit de keuze mogelijkheden lijst wordt genomen
  if (((aanBeurt == Geel-1 && j>=1 && j<= keuzeAantalGeel) || 
        (aanBeurt == Blauw -1 && j>=1 && j <= keuzeAantalBlauw)) && volgordeSet.size() != 0){ 
      volgordeBord x = *next(vakjeKeuzes.begin(), j-1);
      return x.volgorde_coord;
  }
  return GeenZet; //als j niet overeenkomt met de keuze mogelijkheden returnt het GeenZet
  
}  // bepaalZet

//*************************************************************************

// doet een zet op het bord en returnt true voor de doezet functie
bool Territorium::zetSpeler(int speler, int keuzeAantal, int rij, int kolom){
  volgordeBord temp = {bord[rij][kolom], make_pair(rij, kolom)};
  auto coord = vakjeKeuzes.find(temp);
  int keuze_nr = 1;
  if (vakjeKeuzes.find(temp) != vakjeKeuzes.end()){
    volgordeBord zet = {coord->volgorde_nr, coord->volgorde_coord, coord->keuze_nr};
    zetten.push_back(zet);
    volgordeSet.erase(zet);
    
    for (auto i = volgordeSet.begin(); i != volgordeSet.end(); i++){
      i->keuze_nr = keuze_nr;
      keuze_nr++;
    }


    if (speler == Geel -1){
      bord[rij][kolom] = Geel;
      keuzesTotaal += (keuzeAantalGeel-1);
    } else if (speler == Blauw -1){
      bord[rij][kolom] = Blauw;
      keuzesTotaal += (keuzeAantalBlauw-1);
    }  
    aanBeurt = !aanBeurt;     
    return true;
  }
  return false;
}

// controleert of een zet mag en doet deze mbv zetSpeler
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

// kijkt of een zet ongedaan mag worden en doet dat als het mag
bool Territorium::unDoeZet ()
{
  int size = zetten.size();
  int keuze_nr = 1;
  if(size > 0){ 
    if (aanBeurt == Geel -1){
      keuzesTotaal -= (keuzeAantalBlauw-1);
    } if (aanBeurt == Blauw -1){
      keuzesTotaal -= (keuzeAantalGeel-1);
    } 

    volgordeSet.insert(zetten.back());

    for (auto i = volgordeSet.begin(); i != volgordeSet.end(); i++){
      i->keuze_nr = keuze_nr;
      keuze_nr++;
    }

    bord[zetten.back().volgorde_coord.first][zetten.back().volgorde_coord.second] = zetten.back().volgorde_nr;
    
    zetten.pop_back();
    aanBeurt = !aanBeurt;
    
    return true;
  }else {
    return false;
  }
  

}  // unDoeZet

//*************************************************************************

// kiest het grootste territorium 
int Territorium::grootsteTerritorium(int speler){
  // er wordt een kopie van het bord gemaakt een daarna wordt er gekeken welke score van
  // alle territoria het grootst is
  int score = 0, hoogste_score = 0;
  fill(&bordKopie[0][0], &bordKopie[0][0]+(MaxDimensie*MaxDimensie), false);

  for (int i = 0; i< hoogte; i++){
    for (int j = 0; j < breedte; j++){
      if (!bordKopie[i][j] && bord[i][j] == speler + 1){
        score = telTerritorium(make_pair(i, j), speler);
        if (score > hoogste_score){
          hoogste_score = score;
        }
      }
      bordKopie[i][j] = true;
      score = 0;
    }
  }
  return hoogste_score;
}


//  telt een territorium en zijn score dmv een teller
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
        vakjesMogelijk();
        if (doeZet(i, j)){
          aantalStanden++;
          score = - besteScore(zet, aantalStanden);
          
          if (score > besteScoreHoogst){
            besteScoreHoogst = score;
            besteZet = make_pair(i, j);
            zet = make_pair(i, j);
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
    vakjesMogelijk();
    for (auto i = vakjeKeuzes.begin(); i != vakjeKeuzes.end(); i++){
      if(doeZet(i->volgorde_coord.first, i->volgorde_coord.second)){
        score = grootsteTerritorium(!aanBeurt);

        if (score >= hoogste_score){
          hoogste_score = score;  
          goedeZet = i->volgorde_coord;
        }
        score = 0;
        unDoeZet();
      }
    }
    return goedeZet;
  }
  return GeenZet;
}  // bepaalGoedeZet

//*************************************************************************

// Speelt een spel met bestescore tegen bepaalgoedezet
int Territorium::bepaalGoedeScore ()
{
  pair<int, int> zet1, zet2;
  pair<int, int> besteZet;
  clock_t c1, c2;
  int score=0, speler = 0;
  int i =0;
  if (aanBeurt == Geel -1){
    speler = 0;
  }else if (aanBeurt == Blauw -1){
    speler = 1;
  }
  // zolang het spel niet klaar is worden er zetten gedaan
  c1 = clock ();
  while (!eindstand()){
    c2 = clock ();
    // als bij het runnen het langer dan 5 min duurt returnen wij een error
    if ((((double)(c2-c1))/CLOCKS_PER_SEC) > (300*CLOCKS_PER_SEC)){
      return -100;
    }
    if (aanBeurt == speler){
      zet1 = bepaalGoedeZet();
      doeZet(zet1.first, zet1.second);
      i++;
    }
    else{
      long long aantalStanden=0;
      besteScore(besteZet, aantalStanden);
      zet2= besteZet;
      doeZet(zet2.first, zet2.second);
      i++;
    }
  }
  score= grootsteTerritorium(aanBeurt) - grootsteTerritorium(!aanBeurt);
  cout << "1: " << grootsteTerritorium(aanBeurt) << " 2: " << grootsteTerritorium(!aanBeurt) << endl;
  while (i != 0){
    unDoeZet();
    i--;
  }
  return score;
}  // bepaalGoedeScore