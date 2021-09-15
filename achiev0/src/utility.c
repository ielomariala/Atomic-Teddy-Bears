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

// renvoie 0 si le teddy peut faire N fois la transaction, 1 sinon  
int utility__cant_make_transac(struct teddy* ted , const struct transac* transac, int N)
{
  for (int i=0; i < MAX_GOOD; i++) {
    if ((ted->w).data[i] < N*transac__out_wallet(transac).data[i]) { 
      return 1;
    }
  }
  return 0;
}   

// Affiche les resultats de la partie
void display_results(struct queue Q)
{
  queue__sort_tab(&Q);
  printf("=-=-=-=-==-=--=-==-=-=-=-==-=-=-=-=-=-=\nEt maintenant que le jeu est fini,le classement est:\n");
  queue__print(&Q);
  printf("Nous vous presentons donc le gagnant: le teddy num (%d) avec dans son portefeuille l'equivalent de %d unites de miel.\n ",(Q.tab_queue[(Q.n) - 1])->num , (Q.tab_queue[(Q.n) - 1])->value);
}  
