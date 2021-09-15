#include "good.h"
#include "queue.h"


// Cree une nouvelle queue
struct queue queue__new() 
{
  struct queue nq;
  nq.n = 0;
  return nq;
}

// Pousse le teddy `t` dans la  queue `h` avec la priorite `priority`
void queue__push(struct queue* h, int priority, struct teddy* t) 
{     
  if (h->n < MAX_TED) {  // on ne remplis pas une queue pleine    
    int len = h->n;  // `len` est la longueur de queue avant le push, et l'indice du dernier teddy de la queue apres
    int j = len-1;
    h->n ++;  // on incrémente la longueur de la queue
    while ( j >= 0  && (h->tab_queue[j])->time_played < priority ) { 
      h->tab_queue[j+1] = h->tab_queue[j];
      j--;
    }  // tant que l'ours `t` n'est pas a sa place, on décale l'ours courant et on décrémente `j`. Si j < 0, l'ours `t` est celui qui a joué le plus, il rentre a la position d'indice 0
    h->tab_queue[j+1] = t; 
  }
}

// Trie tab_queue par ordre croissant des valeurs
void queue__sort_tab(struct queue* h)
{
  int N = h->n;
  for(int j = N-1 ; j > 0 ; j--) {
    for(int i = 1 ; i <= j ; i++) {
      if ( (h->tab_queue[i - 1])->value > (h->tab_queue[i])->value ) {
	struct teddy* ted = h->tab_queue[i - 1];
	h->tab_queue[i - 1] = h->tab_queue[i];
	h->tab_queue[i] = ted;
      }  
    }
  } 
}

// Retourne le teddy prioritaire de la queue `h`
struct teddy* queue__top(struct queue* h)  
{
  return h->tab_queue[h->n - 1];
}

// Retourne et retire de la queue `h` le teddy prioritaire
struct teddy* queue__pop(struct queue* h)
{
  struct teddy* priority;
  if (h->n == 0) {
    return NULL;
  }
  else {
    priority = queue__top(h);
    h->n -= 1;
    return priority;
  }
}

// Affiche le teddy `t`
void teddy__print(struct teddy* t)
{
  printf("Portefeuille du teddy numero (%d):\n", t->num);
  wallet__print(t->w);
  printf("Temps de jeu: %d\n", t->time_played);
  printf("Valeur du portefeuille: %d\n", wallet__value(t->w));
  printf("------------\n");
}

// Affiche la queue `h`
void queue__print(struct queue* h)
{
  int n = h->n;
  for(int i = 0 ; i < n ; i++) {
    printf("%d)\n",i+1);
    teddy__print(h->tab_queue[n - i - 1]);
    printf("_____________\n");
  }
}
