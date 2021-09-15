#include "good.h"
#include "stockex.h"
#include "stdio.h"

// Une place d'echange
const struct stockex stock ={
			     2,  //nombre de transactions
			     "catane" ,  //nom de la place
			     {
			      {{{15,15,0}}, {{10,0,0}}} ,  //transaction 0 ({a payer pour le teddy}, {vendu})
			      {{{10,20,15}},{{20,0,0}}}  //transaction 1 ({a payer pour le teddy}, {vendu})
			     }
};

// La place d'echange initiale
const struct stockex* starting_stockex()
{
  return &stock;
}

// Le nom de la place d'echange
const char* stockex__name(const struct stockex* s)
{
  return s->name;
}

//Le nombre de transactions disponibles dans une place d'echange
size_t stockex__num_transactions(const struct stockex* t)
{
  return t->n;
}

//Renvoie la transaction indexee `num` de la place d echange
const struct transac* stockex__transaction(const struct stockex* t, size_t num)
{
  return &(t->tab_transac[num]);
}

// Les ressources achetees par la place d'echange
struct wallet transac__in_wallet(const struct transac* s)
{
  return s->bought;
}

// Les ressources vendues par la place d'echange
struct wallet transac__out_wallet(const struct transac* s)
{
  return s->sold;
}

//affiche la transaction `s`
void transac__print(const struct transac* s)
{
  printf("Acheté:\n");
  wallet__print(transac__in_wallet(s));
  printf("Vendu:\n");
  wallet__print(transac__out_wallet(s));
}     
