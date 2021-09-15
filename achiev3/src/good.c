#include "good.h"

// La description d'une ressource
const char* good__string(enum good g)
{
  switch (g) {
  case Miel:
    return "Miel";
  case Cle_a_molette:
    return "Cle_a_molette";
  case Moteur_de_hors_bord:
    return "Moteur_de_hors_bord";
  case MAX_GOOD:
    return "Le nombre de ressources différentes est";
  default:
    return "Cet aliment n'est pas en vente\n";
  }
}

static unsigned int good__values[MAX_GOOD+1]={
  1,
  20,
  10,
  0};

// La valeur de base d'une ressource (en Miel)
unsigned int good__value(enum good g)
{
  return good__values[g];
}

static unsigned int good__total_amounts[MAX_GOOD+1]={
  UINT_MAX,
  5000,
  1500,
  0};

unsigned int good__total_amount(enum good g){
  return good__total_amounts[g];
}

void good__set_value(enum good g, unsigned int v){
  good__values[g] = v;
}
  
void good__set_total_amount(enum good d, unsigned int v){
  good__total_amounts[d] = v;
}



