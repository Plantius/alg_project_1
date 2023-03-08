// Hoofdprogramma voor oplossing voor eerste programmeeropdracht Algoritmiek,
// voorjaar 2023: Territorium
//
// Biedt de gebruiker een menustructuur om
// * het spel te spelen
//   - vanaf een nieuw, leeg bord
//   - vanaf een in te lezen, en mogelijk (deels) gevuld bord
//   waarbij de gebruiker steeds
//   - een zet kan uitvoeren (een tegel neerleggen op een leeg vakje)
//   - de laatste zet ongedaan kan maken
//   - kan vragen om een mogelijke zet voor de speler die aan de beurt is
//   - kan vragen om de score voor de speler die aan de beurt is, als beide
//     spelers vanaf dit moment optimaal verder spelen
//   - kan vragen om een `goede zet' voor de speler die aan de beurt is
//   - kan vragen om de eindscore voor de speler die aan de beurt is,
//     als hij vanaf nu een `goede zet' doet, terwijl de andere speler
//     steeds een beste zet doet
//
// * een experiment uit te voeren, waarbij voor een reeks maten van borden
//   het spel vanaf het begin tot het einde wordt uitgespeeld met `goede
//   zetten' tegen beste zetten
//
// Namen van studenten, datum

#include <iostream>
#include <ctime>  // voor clock() en clock_t
#include "territorium.h"
using namespace std;
const int MaxBestandsNaamLengte = 30; // maximale lengte van een bestandsnaam

//*************************************************************************

// Vraag de gebruikers om waardes in te voeren voor hoogte, breedte,
// kansNietBeschikbaar, keuzeAantalGeel en keuzeAantalBlauw
void vraagParameters (int &hoogte, int &breedte, int &kansNietBeschikbaar,
                      int &keuzeAantalGeel, int &keuzeAantalBlauw)
{
  cout << "Geef de hoogte van het bord (1.." << MaxDimensie
       << "): ";
  cin >> hoogte;
  cout << "Geef de breedte van het bord (1.." << MaxDimensie
       << "): ";
  cin >> breedte;
  cout << "Geef de kans op een niet beschikbaar vakje (0..100): ";
  cin >> kansNietBeschikbaar;
  cout << "Geef het aantal vakjes waaruit speler " << Geel
       << " kan kiezen (>0): ";
  cin >> keuzeAantalGeel;
  cout << "Geef het aantal vakjes waaruit speler " << Blauw
       << " kan kiezen (>0): ";
  cin >> keuzeAantalBlauw;

}  // vraagParameters

//*************************************************************************

// Schrijf het menu op het scherm en vraag een keuze van de gebruiker.
// Retourneer: de keuze van de gebruiker
int keuzeUitMenu ()
{ int keuze;

  cout << endl;
  cout << "1. Een zet uitvoeren" << endl;
  cout << "2. Laatste zet ongedaan maken" << endl;
  cout << "3. Een mogelijke zet voor huidige speler bepalen" << endl;
  cout << "4. Beste score (met beste zet) bepalen" << endl;
  cout << "5. Een goede zet bepalen" << endl;
  cout << "6. Score goed tegen best bepalen" << endl;
//  cout << "   of Score random tegen goed" << endl;
  cout << "7. Stoppen met dit spel" << endl;
  cout << endl;
  cout << "Maak een keuze: ";
  cin >> keuze;

  return keuze;

}  // keuzeUitMenu

//*************************************************************************

// Roep ter1->besteScore aan, meet de benodigde tijd, en zet de relevante
// data op het scherm.
void roepBesteScoreAan (Territorium *ter1)
{ clock_t t1, t2;
  pair<int,int> besteZet;
  int score;
  long long aantalStanden;  // aantal bekeken standen bij aanroep besteScore

  t1 = clock ();
  score = ter1 -> besteScore (besteZet, aantalStanden);
  t2 = clock ();
  cout << endl;
  cout << "Beste score is: " << score << endl;
  cout << "Een beste zet is: (" << besteZet.first << "," << besteZet.second
       << ")" << endl;
  cout << "We hebben hiervoor " << aantalStanden
       << " standen bekeken." << endl;
  cout << "Dit kostte " << (t2-t1) << " clock ticks, ofwel "
       << (((double)(t2-t1))/CLOCKS_PER_SEC) << " seconden." << endl;

}  // roepBesteScoreAan

//*************************************************************************

// Speel het spel op het bord van ter1.
// Hierbij krijgt de gebruiker herhaaldelijk de keuze om
// * een zet uit te voeren (een tegel neerleggen op een leeg vakje)
// * de laatste zet ongedaan te maken
// * een mogelijke zet te bepalen voor de speler die aan de beurt is
// * te vragen om de score voor de speler die aan de beurt is, als beide
//   spelers vanaf dit moment optimaal verder spelen
// * te vragen om een `goede zet' voor de speler die aan de beurt is
// * te vragen om de eindscore voor de speler die aan de beurt is,
//   als hij vanaf nu een `goede zet' doet, terwijl de andere speler
//   steeds een beste zet doet
//
// Voor elke iteratie van het menu wordt de stand afgedrukt.
//
// Dit alles gaat door
// * totdat er een eindstand is bereikt (het bord is vol)
// * of totdat de gebruiker aangeeft dat hij wil stoppen met het spel
void doeSpel (Territorium *ter1)
{ int hoogte, breedte,
      keuze,
      rij, kolom,
      j,        // nummer van een mogelijke zet (>= 1)
      score;
  pair<int,int> zet;
  long long aantalStanden;  // aantal bekeken standen bij aanroep besteScore

  hoogte = ter1->getHoogte();
  breedte = ter1->getBreedte();

  keuze = 0;
  while (keuze!=7 && !ter1->eindstand())
  {
    ter1 -> drukAf ();

    keuze = keuzeUitMenu ();

    switch (keuze)
    { case 1: cout << endl;
              cout << "Geef het nummer van de rij (0.." << hoogte-1 << "): ";
              cin >> rij;
              cout << "Geef het nummer van de kolom (0.." << breedte-1 << "): ";
              cin >> kolom;
              if (!(ter1->doeZet (rij, kolom)))
              { cout << endl;
                cout << "Er is geen zet gedaan." << endl;
              }
              break;
      case 2: if (!(ter1->unDoeZet ()))
              { cout << endl;
                cout << "Er is geen zet ongedaan gemaakt." << endl;
              }
              break;
      case 3: cout << endl;
              cout << "Geef het nummer van de zet van de huidige speler die je wil weten (>= 1): ";
              cin >> j;
              zet = ter1->bepaalZet (j);
              cout << "De " << j
                   << "-de mogelijke zet voor de huidige speler is ("
                   << zet.first << "," << zet.second << ")" << endl;
              break;
      case 4: roepBesteScoreAan (ter1);
              break;
      case 5: zet = ter1 -> bepaalGoedeZet ();
              cout << endl;
              cout << "Een goede zet is: (" << zet.first << ","
                   << zet.second << ")" << endl;
              break;
      case 6: score = ter1 -> bepaalGoedeScore ();
              cout << endl;
              cout << "Score goed tegen best is: " << score << endl;
              break;
      case 7: break;
      default: cout << endl;
               cout << "Voer een goede keuze in!" << endl;
    }  // switch

  }  // while

  if (ter1->eindstand())
  { ter1 -> drukAf ();
    cout << endl;
    cout << "De huidige stand is een eindstand.\n";
    cout << "De score voor de speler die aan de beurt zou zijn is: "
         << ter1->besteScore (zet, aantalStanden) << endl;
  }

}  // doeSpel

//*************************************************************************

// Voert experiment uit zoals beschreven in de opdracht.
void doeExperiment ()
{
      
// TODO: implementeer deze functie

}  // doeExperiment

//*************************************************************************

void hoofdmenu ()
{ Territorium *ter1;  // pointer, om makkeijk nieuwe objecten te kunnen maken
                      // en weer weg te gooien
  int keuze,
      breedte, hoogte,
      kansNietBeschikbaar,
      keuzeAantalGeel, keuzeAantalBlauw;
  char invoernaam[MaxBestandsNaamLengte+1];

  do
  {
    cout << endl;
    cout << "1. Een nieuw spel starten" << endl;
    cout << "2. Een spel inlezen" << endl;
    cout << "3. Experiment uitvoeren" << endl;
    cout << "4. Stoppen" << endl;
    cout << endl;
    cout << "Maak een keuze: ";
    cin >> keuze;
    switch (keuze)
    { case 1: vraagParameters (hoogte, breedte, kansNietBeschikbaar,
                   keuzeAantalGeel, keuzeAantalBlauw);
              ter1 = new Territorium (hoogte, breedte, kansNietBeschikbaar,
                                     keuzeAantalGeel, keuzeAantalBlauw);
              doeSpel (ter1);
              delete ter1;  // netjes opruimen
              break;
      case 2: ter1 = new Territorium ();
              cout << "Geef de naam van het tekstbestand met het spel: ";
              cin >> invoernaam;
              if (ter1 -> leesInBord (invoernaam))
                doeSpel (ter1);
              delete ter1;  // netjes opruimen
              break;
      case 3: doeExperiment ();
              break;
      case 4: break;
      default: cout << endl;
               cout << "Voer een goede keuze in!" << endl;
    }

  } while (keuze!=4);

}  // hoofdmenu

//*************************************************************************
  
int main ()
{
  hoofdmenu ();

  return 0;

}
