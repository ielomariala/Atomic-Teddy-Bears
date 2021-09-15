#include "good.h"

// La description d'une ressource
const char* good__string(enum good g)
{
  switch (g) {
  case Miel:
    return "Miel\n";
  case Cle_a_molette:
    return "Cle_a_molette\n";
  case Moteur_de_hors_bord:
    return "Moteur_de_hors_bord\n";
  case MAX_GOOD:
    return "Le nombre de ressources différentes est\n";
  default:
    return "Cet aliment n'est pas en vente\n";
  }
}
      
// La valeur de base d'une ressource (en Miel)
unsigned int good__value(enum good g)
{
  switch (g) {
  case Miel:
    return 1;
  case Cle_a_molette:
    return 20;
  case Moteur_de_hors_bord:
    return 10;
  default:
    return 0;
  }
}

