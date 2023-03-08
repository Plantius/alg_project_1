// Implementatie van standaard functies.

#include <iostream>
#include <cstdlib>  // voor rand
#include "standaard.h"
using namespace std;

//*************************************************************************

bool integerInBereik (const char *variabele, int waarde,
                      int minWaarde, int maxWaarde)
{
  if (waarde>=minWaarde && waarde<=maxWaarde)
    return true;
  else
  { cout << variabele << "=" << waarde << ", maar moet in [" << minWaarde
         << "," << maxWaarde << "] liggen." << endl;
    return false;
  }

}  // integerInBereik

//*************************************************************************

bool integerInBereik (int waarde, int minWaarde, int maxWaarde)
{
  if (waarde>=minWaarde && waarde<=maxWaarde)
    return true;
  else
    return false;

}  // integerInBereik

//*************************************************************************

bool integerPositief (const char *variabele, int waarde)
{

  if (waarde>0)
    return true;
  else
  { cout << variabele << "=" << waarde << ", maar moet positief zijn."
         << endl;
    return false;
  }

}  // integerPositief

//*************************************************************************

int randomGetal (int min, int max)
{ int bereik,
      r;

  bereik = max - min + 1;

  r = ((rand())%bereik) + min;
  return r;

}  // randomGetal

