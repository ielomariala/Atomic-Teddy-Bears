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
         
// Choisit une transaction qui débloque un nouveau stock s'il existe, sinon choisit aléatoirement une transaction du stock
const struct transac* utility__transac_choice(const struct stockex* stock, struct teddy* ted )
{
  if (! utility__stockex_already_visited(ted->current_stock , ted)) {  // copier la place d'echange dans le tableau de noms de stockex si il n'y avait pas encore joué
 
    strcpy(ted->tab_stockex_names[ted->nbre_stockex],stockex__name(ted->current_stock)); 
    ted->nbre_stockex++;
  }
  size_t n = stockex__num_transactions(stock);
  size_t tab_indice_transac[MAX_TRANSAC] = {0};  // un tableau que l'on va remplire avec les indices de transactions qui débloquent une nouvelle place d'echange
  int cpt = 0;
  for (size_t i = 0 ; i < n ; i++) {  // recherche des transactions qui débloquent un nouveau stocke nouvelle place 
    
    if ( ! utility__stockex_already_visited(transac__next_stockex( stockex__transaction(stock , i) ) , ted) ) {
	
      tab_indice_transac[cpt] = i;  // remplissage du tableau 
      cpt++;
    }
  }  
  if ( cpt != 0 ) {  // SI il y a au moins une transaction qui débloque un nouveau stock
    
    int r = random(cpt); // choisit un nombre entre 0 et le nombre de transactions qui débloquent un nouveau stock
    return stockex__transaction( stock , tab_indice_transac[r] );  // le tab_indice_transac retourne l'indice de cette transaction dans tab_stockex
  }
  else {
    size_t j = random(n);
    return stockex__transaction( stock , j );  // SINON, retourne une transaction aleatoire
  }
}
      
// Renvoi 1 si ted a deja joué dans cette place d'echange, 0 sinon
int utility__stockex_already_visited(const struct stockex* stock, struct teddy* ted)
{
  int i=0;
  while( i != ted->nbre_stockex) {
    if (strcmp(ted->tab_stockex_names[i],stockex__name(stock)) == 0 ) {
      return 1;
    }
    i++;
  }
  return 0;
}


	
