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
  fill(volgorde, volgorde+(MaxDimensie*MaxDimensie), 0);
  fill(volgordeCoord, volgordeCoord+(MaxDimensie*MaxDimensie), GeenZet);
  fill(&bord[0][0], &bord[0][0]+(MaxDimensie*MaxDimensie), 0);
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
  fill(volgorde, volgorde+(MaxDimensie*MaxDimensie), 0);
  fill(volgordeCoord, volgordeCoord+(MaxDimensie*MaxDimensie), GeenZet);
  fill(&bord[0][0], &bord[0][0]+(MaxDimensie*MaxDimensie), 0);

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


// haalt alle volgordes uit bord
void Territorium::vulVolgorde(){
  volgorde_eind = 0;

  for (int i = 0; i< hoogte; i++){
    for (int j = 0; j< breedte; j++){
      if (bord[i][j] < 0 && volgorde_eind < MaxDimensie*MaxDimensie){
        volgordeBord temp;
        temp.volgorde_nr = bord[i][j];
        temp.volgorde_coord = make_pair(i, j);
        volgordeSet.insert(temp);
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
    cout << "EMPTY" << endl;
    for (auto k = volgordeSet.begin(); k != volgordeSet.end(); k++){
      cout << "(" << k->volgorde_coord.first << ", " << k->volgorde_coord.second << ") ";
      volgordeBord temp;
      temp.volgorde_nr = k->volgorde_nr;
      temp.volgorde_coord = k->volgorde_coord;
      vakjeKeuzes.insert(temp);
    }
  }
  else {
    cout << "ELSE" << endl;
    for (auto k = volgordeSet.begin(); k != volgordeSet.end(); k++){
      cout << (k->volgorde_nr <= k->volgorde_nr - keuzesTotaal) << " | "<< (k->volgorde_nr > k->volgorde_nr - keuzesTotaal - keuzeAantal) << endl;
      if (k->volgorde_nr <= k->volgorde_nr - keuzesTotaal && k->volgorde_nr > k->volgorde_nr - keuzesTotaal - keuzeAantal){
        cout << "(" << k->volgorde_coord.first << ", " << k->volgorde_coord.second << ") ";
        volgordeBord temp = {k->volgorde_nr, k->volgorde_coord};
        vakjeKeuzes.insert(temp);
      }
    }
    if (vakjeKeuzes.size() < keuzeAantal){
      for (auto k = volgordeSet.begin(); k != volgordeSet.end(); k++){
        if (vakjeKeuzes.size() < keuzeAantal){
          cout << "(" << k->volgorde_coord.first << ", " << k->volgorde_coord.second << ") ";
          volgordeBord temp;
          temp.volgorde_nr = k->volgorde_nr;
          temp.volgorde_coord = k->volgorde_coord;
          vakjeKeuzes.insert(temp);
        }
      }
    }
  }
}

void Territorium::vakjesMogelijk(){
  
  //  welke vakjes nog mogelijk
  cout << "Mogelijke keuzes: ";
  if (aanBeurt == Geel -1){
    keuzeSpeler(keuzeAantalGeel);
  }else if (aanBeurt == Blauw -1){
    keuzeSpeler(keuzeAantalBlauw);
  } cout << endl;
  
  for (auto i = volgordeSet.begin(); i != volgordeSet.end(); i++){
    cout << i->volgorde_nr << ": " << i->volgorde_coord.first <<"," << i->volgorde_coord.second << " ";
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
    cout << "geel" << endl; ;
  } else if (aanBeurt == Blauw - 1){
    cout << "blauw" << endl;
  }

  vakjesMogelijk();
  cout << "YO "<<vakjeKeuzes.size() << " " << volgordeSet.size() << endl;

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
  volgordeBord temp = {0, make_pair(-1, -1)};
  temp.volgorde_coord = make_pair(rij, kolom);
  auto coord = vakjeKeuzes.find(temp);
  if (coord != vakjeKeuzes.end()){
    zetten.push_back(*coord);
    totale_zetten++;
    zetten_ronde++;
    volgordeSet.erase(coord);

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
    cout<<"UNDO " << zetten.back().volgorde_coord.first << ", " << zetten.back().volgorde_coord.second << endl;
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
  return teller++;
}

pair<int,int> Territorium::bepaalGoedeZet ()
{
  int hoogste_score = 0, score = 0;
  pair<int, int> goedeZet;
  
  if (!eindstand()){
    for (auto i = vakjeKeuzes.begin(); i != vakjeKeuzes.end(); i++){
      score = telTerritorium(i->volgorde_coord, aanBeurt);

      if (score > hoogste_score){
        hoogste_score = score;  
        goedeZet = i->volgorde_coord;
      }
      score = 0;
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