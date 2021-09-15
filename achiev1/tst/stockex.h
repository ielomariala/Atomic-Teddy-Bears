#include <stdlib.h>
#define MAX_STOCKEX 100
#define MAX_TRANSAC 100

// La structure représentant une transaction
struct transac{
  struct wallet bought;
  struct wallet sold;
  const struct stockex* stock; //la place d'echange ou se deroule la transaction 
  const struct stockex*  next_stock; //la place d'echange que debloque cette transaction
};

// La structure représentant une place d'echange
struct stockex{
  int n;  //nombre de transactions possible dans cette place
  char* name;
  struct transac tab_transac[MAX_TRANSAC];
};

// La place d'echange initiale
const struct stockex*  starting_stockex();

// Le nom de la place d'echange
const char*  stockex__name(const struct stockex* s);

// Le nombre de transactions disponibles dans une place d'echange
size_t stockex__num_transactions(const struct stockex* t);

// Renvoie la transaction indexee `num` de la place d echange
const struct transac*  stockex__transaction(const struct stockex* t, size_t num);

// Les ressources achetees par la place d'echange
struct wallet  transac__in_wallet(const struct transac* s);

// Les ressources vendues par la place d'echange
struct wallet  transac__out_wallet(const struct transac* s);

// La place d'echange ou la transaction `s` est realisee
const struct stockex* transac__stockex(const struct transac* s);

// La place d'echange que debloque la transaction `s`
const struct stockex* transac__next_stockex(const struct transac* s);

// Affiche la transaction `s`
void transac__print(const struct transac* s);

// Les places d'echanges 
const struct stockex stock0;
const struct stockex stock1;
const struct stockex stock2;
const struct stockex stock3;

// Le tableau regroupant ces places d'echanges
const struct stockex* stocks[MAX_STOCKEX];

// Le nombre de places d'echanges
int nbre_stockex;
