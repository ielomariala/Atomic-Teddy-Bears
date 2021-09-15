#include "good.h"
#include "stdio.h"

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

// Calcule la valeur du portefeuille `w`
int wallet__value(struct wallet w)
{
  int v = 0;
  for (int i = 0 ; i < MAX_GOOD ; i++) {
    v = v + (w.data[i] * good__value(i));
  }
  return v;
}

// afiche le portefeuille `w`
void wallet__print(struct wallet w)
{
  for (int i = 0 ; i < MAX_GOOD ; i++) {
    printf("%s: %d\n",good__string(i),w.data[i]);
  }
}
