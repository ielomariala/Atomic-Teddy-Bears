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
struct wallet utility__wallet_after_transac(struct wallet w,const struct transac* s,int n)
{
  for (int i = 0 ; i < MAX_GOOD ; i++) {
    w.data[i] -= n * transac__in_wallet(s).data[i];
    w.data[i] += n * transac__out_wallet(s).data[i];
  }
  return w;
}

void good_print(struct queue* q)
{
  int len = q->n;
  printf("Good\tName\t\tValue\t\tTotalchezteddies/TOTAL\n");
  for (int i = 1; i < MAX_GOOD; i++){
    int somme = 0;
    for (int j = 0; j < len ; j++){
      somme += q->tab_queue[j]->w.data[i];
    }
    printf("%d- %s\t%d\t\t%d / %d\n",i,good__string(i),good__value(i),somme,good__total_amount(i)); 
  }
}

// Affiche les resultats de la partie
void display_results(struct queue Q)
{
  queue__sort_tab(&Q);
  printf("=-=-=-=-==-=--=-==-=-=-=-==-=-=-=-=-=-=\nEt maintenant que le jeu est fini,le classement est:\n");
  queue__print(&Q);
  printf("Nous vous presentons donc le gagnant: le teddy num (%d) avec dans son portefeuille l'equivalent de %d unites de miel.\n ",(Q.tab_queue[(Q.n) - 1])->num , (Q.tab_queue[(Q.n) - 1])->value);
  printf("------------------------------------ Un oeil sur les ressources\n");
  good_print(&Q);
} 

//affiche la transaction `s`
void transac__print(const struct transac* s)
{
  printf("Acheté par la place d'échange:\n");
  wallet__print(transac__in_wallet(s));
  printf("Vendu:\n");
  wallet__print(transac__out_wallet(s));
}

// renvoie 0 si le teddy peut faire N fois la transaction, 1 sinon  
int utility__transac_cant_make(struct teddy* ted , const struct transac* transac, int N)
{
  for (int i=0; i < MAX_GOOD; i++) {
    if ((ted->w).data[i] < N*transac__in_wallet(transac).data[i]) { 
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

// Cette fonction retourne 1 si le pourcentage de la ressource 'g', que les teddies ont, est >= 90%, et 0 sinon.
int utility__good_greater_limit(enum good g, struct queue* q){
  unsigned int somme = q->wallet_all_teddies.data[g];
  if (  100*somme >= 90*good__total_amount(g) ){
    return 1;
  }   
  return 0;
}

// Vérifie si en faisant la transaction 't', chaque ressource du portefeuille de la queue (c-à-d de tous les teddies) ne sera pas supérieure à sa quantité maximale.
int utility__check_total(struct queue* q, const struct transac* t){
  for (int g=1; g < MAX_GOOD; g++) {  //i=1 pour faire la supposition que g != HONEY
    if ( q->wallet_all_teddies.data[g] + transac__out_wallet(t).data[g] >= good__total_amount(g) ){
      return 0;
    }
  }
  return 1;
}

// Cette fonction retourne 1 si le pourcentage de la ressource 'g', que les teddies ont, est <= 10%, et 0 sinon.
int utility__good_lesser_limit(enum good g, struct queue *q){
  unsigned int somme = q->wallet_all_teddies.data[g];
  if ( 100*somme <= 10*good__total_amount(g) ){
      return 1;
  }
  return 0;
}

// Change les valeurs des ressources échangés pendant la transaction 't', si cela est nécessaire
void utility__good_set_value(struct queue*q, const struct transac* t)
{
  for (int i=1; i < MAX_GOOD; i++)/*i=1 pour faire la supposition que g != HONEY*/{
    int v=good__value(i);
    if (  transac__out_wallet(t).data[i] != 0 && utility__good_greater_limit(i, q) ){
      good__set_value( i, v+1);
    }
    if ( transac__in_wallet(t).data[i] != 0 && v>2 && utility__good_lesser_limit(i, q) ){

      good__set_value( i, v-1);
    }
  }     
}


