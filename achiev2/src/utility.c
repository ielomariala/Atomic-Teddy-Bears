#include "good.h"
#include "stockex.h"
#include "queue.h"
#include "utility.h"


// Donne un entier aleatoire inférieur à `i`
int random(int i)
{
  int r = rand();
  return (r%i);
  }

// Genere des nombres semi aléatoires a partir de seed  
void generate_seed(int s)
{
  if (s <= 0) {
    srand(time(NULL));
  }
  else { srand(s); }
} 

// Portefeuille apres `n` fois la transaction `s` 
struct wallet utility__wallet_after_transac(struct teddy* ted,const struct transac* s,int n)
{
  for (int i = 0 ; i < MAX_GOOD ; i++) {
    (ted->w).data[i] += n * transac__in_wallet(s).data[i];
    (ted->w).data[i] -= n * transac__out_wallet(s).data[i];
  }
  return ted->w;
}

// Affiche les resultats de la partie
void display_results(struct queue Q)
{
  queue__sort_tab(&Q);
  printf("=-=-=-=-==-=--=-==-=-=-=-==-=-=-=-=-=-=\nEt maintenant que le jeu est fini,le classement est:\n");
  queue__print(&Q);
  printf("Nous vous presentons donc le gagnant: le teddy num (%d) avec dans son portefeuille l'equivalent de %d unites de miel.\n ",(Q.tab_queue[(Q.n) - 1])->num , (Q.tab_queue[(Q.n) - 1])->value);
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

//affiche la transaction `s`
void transac__print(const struct transac* s)
{
  printf("Acheté par le teddy:\n");
  wallet__print(transac__in_wallet(s));
  printf("Vendu:\n");
  wallet__print(transac__out_wallet(s));
}

// renvoie 0 si le teddy peut faire N fois la transaction, 1 sinon  
int utility__transac_cant_make(struct teddy* ted , const struct transac* transac, int N)
{
  for (int i=0; i < MAX_GOOD; i++) {
    if ((ted->w).data[i] < N*transac__out_wallet(transac).data[i]) { 
      return 1;
    }
  }
  return 0;
}                                                              
         
      
// Renvoi 1 si ted a deja joué dans cette place d'echange, 0 sinon
int utility__stockex_already_visited(const struct stockex* stock, struct teddy* ted)
{
  int i=0;
  while( i != ted->nbr_stockex) {
    if (strcmp(ted->tab_stockex_names[i],stockex__name(stock)) == 0 ) {
      return 1;
    }
    i++;
  }
  return 0;
}

// Affiche les noms des places d'echanges visitees par le teddy gagnant
void stockex__print_visited(struct teddy* ted)
{
  int n = ted->nbr_stockex;
  printf("Le teddy gagnant a visité %d places d'echange dans cette partie:\n", n );
  for(int i = 0 ; i < n ; i++) {
    printf("%s | ", ted->tab_stockex_names[i]);
  }
  printf("\n");
}

