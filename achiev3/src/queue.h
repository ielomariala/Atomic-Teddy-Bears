#include <stdio.h>
#define MAX_STOCKEX 100
#define MAX_TED 20
#define MAX_STR 64

// La structure d'un teddy 
struct teddy{
  int num;
  struct wallet w;
  int time_played;
  int value;
  const struct stockex* current_stock;  // la place d'echange courante du teddy 
  int nbr_stockex;  // le nombre de places d'echanges ou le teddy a deja joue
  char tab_stockex_names[MAX_STOCKEX][MAX_STR];  // tableau des noms de place d'echanges ou le teddy a deja joué
  int strategy; //0 si il n'est pas optimal, sinon le num de sa stratègie
  const struct transac* favourite_transac; // Sa transaction favoris si il est stratège de niveau 3 ou 4
};

// La structure d'une file de priorité
struct queue{
  int n;    
  struct teddy* tab_queue[MAX_TED];
  struct wallet wallet_all_teddies;
};

// Cree une nouvelle queue
struct queue queue__new();

// Pousse le teddy `t` dans la  queue `h` avec la priorite `priority`
void queue__push(struct queue* h, int priority, struct teddy* t); 

// Retourne le teddy prioritaire de la queue `h`
struct teddy* queue__top(struct queue* h);  

// Retourne et retire de la queue `h` le teddy prioritaire
struct teddy* queue__pop(struct queue* h); 

// Trie tab_queue par ordre croissant des valeurs
void queue__sort_tab(struct queue* h);

// Calcule la valeur du portefeuille `w`
int wallet__value(struct wallet w);

// Affiche le portefeuille `w`
void wallet__print(struct wallet w);

// Affiche le teddy `t`
void teddy__print(struct teddy* t);

// Affiche la queue `h`
void queue__print(struct queue* h);






