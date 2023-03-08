// Defintie van standaard functies.

#ifndef StandaardHVar  // om te voorkomen dat dit .h bestand meerdere keren
#define StandaardHVar  // wordt ge-include 

// Controleer of variabele met naam `variabele' een waarde `waarde' heeft
// die tussen (inclusief) minWaarde en maxWaarde in ligt.
// Zo nee, geef een passende foutmelding.
//
// Voorbeeld van aanroep:
//   if (integerInBereik ("teller", teller, 0, 1000))
//     ...
bool integerInBereik (const char *variabele, int waarde,
                      int minWaarde, int maxWaarde);

// Controleer of waarde `waarde' tussen (inclusief) minWaarde en maxWaarde
// in ligt.
// Geef GEEN foutmelding als het niet zo is.
bool integerInBereik (int waarde, int minWaarde, int maxWaarde);

// Controleer of variabele met naam `variabele' een waarde `waarde' heeft
// die positief is.
// Zo nee, geef een passende foutmelding.
//
// Voorbeeld van aanroep:
//   if (integerPositief ("teller", teller))
//     ...
bool integerPositief (const char *variabele, int waarde);

// Genereer een random geheel getal r waarvoor  min <= r <= max.
// Pre: min <= max;
int randomGetal (int min, int max);

#endif

