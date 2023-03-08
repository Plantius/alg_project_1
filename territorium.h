// Definitie van klasse Territorium

#ifndef TerritoriumHVar  // voorkom dat dit bestand meerdere keren
#define TerritoriumHVar  // ge-include wordt

#include <vector>
#include <string>
#include "constantes.h"
using namespace std;

class Territorium
{ public:
    // Default constructor.
    Territorium ();

    // Constructor met parameters voor hoogte en breedte van het bord,
    // voor kans dat een vakje niet beschikbaar is, en voor keuzeAantalGeel
    // en keuzeAantalBlauw.
    // Controleer eerst nog wel of deze parameters geldig zijn.
    // De eerste twee moeten >= 1 en <= MaxDimensie zijn. De kans moet >= 0
    // en <= 100 zijn (een soort percentage dus), de keuzeAantallen moeten
    // >= 1 zijn.
    // Post:
    // * Als de controles goed uitpakken is een bord van nwHoogte*nwBreedte
    //   gemaakt, waarbij elk vakje Leeg is of NietBeschikbaar (dit laatste
    //   met een kans van kansNietBeschikbaar). Ook keuzeAantalGeel en
    //   keuzeAantalBlauw hebben de aangegeven waarde gekregen.
    // * Als niet alle controles goed uitpakken, is een default bord gemaakt.
    Territorium (int nwHoogte, int nwBreedte,
                 int kansNietBeschikbaar,
                 int nwKeuzeAantalGeel, int nwKeuzeAantalBlauw);

    // Getters voor hoogte en breedte
    int getHoogte()
    { return hoogte;
    }

    int getBreedte()
    { return breedte;
    }

    // Getter voor de inhoud van vakje (rij,kolom) op het bord
    // (rijen genummerd van 0..hoogte-1, van boven naar beneden,
    //  kolommen van 0..breedte-1, van links naar rechts)
    int getVakje(int rij, int kolom)
    { return bord[rij][kolom];
    }

    // Lees een bord in vanuit tekstbestand invoernaam, mogelijk al (deels)
    // gevuld met tegels.
    // Controleer daarbij
    // * of het bestand wel te openen is
    // Retourneer:
    // * true, als het bestand te openen was
    // * false, anders
    // Post:
    // * Als het bestand te openen is, is het bord met de tegels
    //   en de vulvolgorde opgeslagen in membervariabelen, en staat aanBeurt
    //   goed.
    // * Als het bestand niet te openen was, is het bestaande bord niet
    //   veranderd.
    bool leesInBord (const char* invoernaam);

    // Controleer of we een eindstand hebben bereikt, dat wil zeggen:
    // of het bord vol is.
    // Retourneer:
    // * true, als we een eindstand hebben bereikt
    // * false, als we geen eindstand hebben bereikt
    bool eindstand ();

    // Druk de hele stand (bord met tegels, speler aan beurt,
    // uit welke vakjes mag speler aan beurt kiezen) af op het scherm.
    void drukAf ();

    // Bepaal de j-de mogelijke zet van de huidige speler.
    // Controleer eerst of j>=1, of de speler wel uit minstens j zetten kan
    // kiezen, en of er nog j vakjes leeg zijn.
    // Retourneer:
    // * de j-de mogelijke zet (rij,kolom) als de controles goed uitpakken
    // * een passende default-waarde (duidelijk herkenbaar als niet-geldige
    //   zet) anders
    pair<int,int> bepaalZet (int j);

    // Doe een zet voor de speler die aan de beurt is:
    // een tegel plaatsen op vakje (rij,kolom).
    // Controleer eerst of het wel een geldige zet is, dat wil zeggen,
    // - of rij en kolom geldige nummers zijn voor de rij en kolom,
    // - of het vakje beschikbaar en leeg is,
    // - en of de speler die aan de beurt is dit vakje mag kiezen.
    // Retourneer:
    // * true, als dit een geldige zet is
    // * false, als dit geen geldige zet is.
    // Post:
    // * als het een geldige zet is, is de zet uitgevoerd:
    //   - de tegel ligt op het bord in het aangegeven vakje
    //   - de speler aan beurt is gewisseld,
    //   - de zet is toegevoegd aan de lijst met gedane zetten
    //   - het vakje is uit de lijst van nog te kiezen vakjes gehaald
    // * als het geen geldige zet is, is de stand niet veranderd.
    bool doeZet (int rij, int kolom);

    // Maak de laatst gedane zet ongedaan.
    // Controleer eerst of er wel een zet is om ongedaan te maken,
    // opgeslagen in de lijst met zetten.
    // Retourneer:
    // * true, als er een zet was om ongedaan te maken
    // * false, anders
    // Post:
    // * als returnwaarde true is, is de zet ongedaan gemaakt:
    //   - de tegel is van het bord gehaald
    //   - de speler aan beurt is teruggewisseld,
    //   - de zet is van de lijst met uitgevoerde zetten gehaald
    //   - het vakje is teruggezet in de lijst van nog te kiezen vakjes
    // * als returnwaarde false is, is er niets veranderd
    bool unDoeZet ();

    // Bepaal met behulp van brute force en recursie de eindscore voor
    // de speler die in de huidige stand (= de stand van de huidige
    // recursieve aanroep) aan de beurt is, wanneer beide spelers vanaf
    // dit punt optimaal verder spelen.
    // De score is gelijk aan het aantal vakjes van het eigen grootste
    // territorium min het aantal vakjes van het grootste territorium van
    // de andere speler.
    // Post:
    // * als de huidige stand geen eindstand was, bevat parameter
    //   besteZet het vakje (rij,kolom) waarop de huidige speler
    //   de volgende tegel moet leggen, om de beste score te bereiken
    // * anders bevat parameter besteZet een passende default waarde
    // * aantalStanden is gelijk aan het aantal standen dat we hebben
    //   bekeken bij het bepalen van de beste eindscore
    // * de stand in het spel is nog onveranderd
    int besteScore (pair<int,int> &besteZet, long long &aantalStanden);

    // Bepaal een `goede zet' voor de speler die in de huidige stand aan
    // aan de beurt is: een zet die ertoe leidt dat hij (na deze ene zet)
    // een zo groot mogelijk territorium krijgt (zonder verder vooruit
    // te kijken).
    // Controleer eerst of de huidige stand geen eindstand is.
    // Retourneer:
    // * de gevonden zet (rij,kolom), als het geen eindstand is
    // * een passende default waarde, als het al wel een eindstand is
    pair<int,int> bepaalGoedeZet ();

    // Speel het spel uit vanaf de huidige stand. Laat hierbij de speler
    // die in de huidige stand aan de beurt is, steeds een `goede zet'
    // (gevonden met bepaalGoedeZet) doen, terwijl de andere speler steeds
    // een beste zet (gevonden met besteScore) doet.
    // Retourneer:
    // * de score aan het eind van het spel voor de speler die steeds
    //   een `goede zet' gedaan heeft
    // Post:
    // * de huidige stand is weer hetzelfde als aan het begin van de functie
    //   (zetten zijn dus weer ongedaan gemaakt)
    int bepaalGoedeScore ();

  private:
      // membervariabelen
    int bord[MaxDimensie][MaxDimensie];  // [rij][kolom]: inhoud van bord;
          // rijen genummerd van 0..hoogte-1, van beneden naar boven
          // kolommen genummerd van 0..breedte-1, van links naar rechts;
    int breedte, hoogte,  // van het bord
        keuzeAantalGeel,  // aantal vakjes waaruit Geel/Blauw steeds
        keuzeAantalBlauw, // kan kiezen voor nieuwe zet
        aanBeurt;       // speler die aan de beurt is

    // TODO: uw eigen memberfuncties en -variabelen

};

#endif


