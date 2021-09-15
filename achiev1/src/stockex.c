#include "good.h"
#include "stockex.h"
#include "stdio.h"


// Les places d'echanges
const struct stockex stock0 = {
			       2,  // nombre de transactions
			       "catane",  //nom de la place d'echanges
			       {
				{
				 {{15,15,0}},{{10,0,0}},  // transaction 0 ({a payer pour le teddy}, {vendu})
				 &stock0,  // la place d'echange ou se deroule la transaction 0
				 &stock1  // la place d'echange que debloque cette transaction 0
				},
				{
				 {{10,20,15}},{{20,0,0}},  // transaction 1 ({a payer pour le teddy}, {vendu})
				 &stock0,  // la place d'echange ou se deroule la transaction 1
				 &stock3  // la place d'echange que debloque cette transaction 1
				}
			       }
};

const struct stockex stock1 = {
			       2,  // nombre de transactions
			       "talence",  //nom de la place d'echanges
			       {
				{
				 {{13,13,0}},{{9,0,1}},  // transaction 0 ({a payer pour le teddy}, {vendu})
				 &stock1,  // la place d'echange ou se deroule la transaction 0
				 &stock3  // la place d'echange que debloque cette transaction 0
				},
				{
				 {{7,20,15}},{{17,0,0}},  // transaction 1 ({a payer pour le teddy}, {vendu})
				 &stock1,  // la place d'echange ou se deroule la transaction 1
				 &stock2  // la place d'echange que debloque cette transaction 1
				}
			       }
};

const struct stockex stock2 = {
			       2,  // nombre de transactions
			       "pessac",  //nom de la place d'echanges
			       {
				{
				 {{27,13,0}},{{9,25,1}},  // transaction 0 ({a payer pour le teddy}, {vendu})
				 &stock2,  // la place d'echange ou se deroule la transaction 0
				 &stock3  // la place d'echange que debloque cette transaction 0
				},
				{
				 {{7,20,15}},{{17,0,0}},  // transaction 1 ({a payer pour le teddy}, {vendu})
				 &stock2,  // la place d'echange ou se deroule la transaction 1
				 &stock0  // la place d'echange que debloque cette transaction1
				}
			       }
};

const struct stockex stock3 = {
			       4,  // nombre de transactions
			       "merignac",  //nom de la place d'echanges
			       {
				{
				 {{30,2,0}},{{2,10,0}},  // transaction 0 ({a payer pour le teddy}, {vendu})
				 &stock3,  // la place d'echange ou se deroule la transaction 0
				 &stock0  // la place d'echange que debloque cette transaction 0
				},
				{
				 {{7,25,15}},{{14,0,2}},  // transaction 1 ({a payer pour le teddy}, {vendu})
				 &stock3,  // la place d'echange ou se deroule la transaction 1
				 &stock1  // la place d'echange que debloque cette transaction 1
				},
				{
				 {{26,3,10}},{{1,15,2}},  // transaction 2 ({a payer pour le teddy}, {vendu})
				 &stock3,  // la place d'echange ou se deroule la transaction 2
				 &stock2  // la place d'echange que debloque cette transaction 2
				},
				{
				 {{7,2,5}},{{4,2,20}},  // transaction 3 ({a payer pour le teddy}, {vendu})
				 &stock3,  // la place d'echange ou se deroule la transaction 3
				 &stock0  // la place d'echange que debloque cette transaction 3
				}
			       }
};

// Le tableau regroupant ces places d'echanges
const struct stockex* stocks[MAX_STOCKEX] = {&stock0, &stock1, &stock2, &stock3};

// La place d'echange initiale
const struct stockex* starting_stockex()
{ 
  return stocks[0];
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

//affiche la transaction `s`
void transac__print(const struct transac* s)
{
  printf("Acheté:\n");
  wallet__print(transac__in_wallet(s));
  printf("Vendu:\n");
  wallet__print(transac__out_wallet(s));
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
           
// La place d'echange ou la transaction `s` est realisee
const struct stockex* transac__stockex(const struct transac* s)
{
  return s->stock;
}

// La place d'echange que debloque la transaction `s`
const struct stockex* transac__next_stockex(const struct transac* s)
{
  return s->next_stock;
}




