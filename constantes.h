// Enkele constantes voor implementatie Territorium

#ifndef ConstantesHVar  // voorkom dat dit bestand meerdere keren
#define ConstantesHVar  // ge-include wordt

using namespace std;

const int MaxDimensie = 10;  // maximaal aantal rijen en maximaal aantal
                             // kolommen in een spel
const int Leeg = 0;
const int Geel = 1;
const int Blauw = 2;
const int NietBeschikbaar = 3;

const pair<int,int> GeenZet = make_pair (-1,-1);  // ongeldige zet

#endif

