#include <stdio.h>
#define MAX_TED 20 

// La structure d'un teddy 
struct teddy{
  int num;        
  struct wallet w;
  int time_played;
  int value;     
};

// La structure d'une file de priorité
struct queue{
  int n;    
  struct teddy* tab_queue[MAX_TED];
};

// Cree une nouvelle queue
struct queue queue__new();

// Pousse le teddy `t` dans la  queue `h` avec la priorite `priority`
void queue__push(struct queue* h, int priority, struct teddy* t); 

// Retourne le teddy prioritaire de la queue `h`
struct teddy* queue__top(struct queue* h);  

// Retourne et retire de la queue `h` le teddy prioritaire
struct teddy* queue__pop(struct queue* h); 

// Trie tab_queue par ordre croissant des valeurs de portefeuille
void queue__sort_tab(struct queue* h);

// Affiche le teddy `t` (a l'envers, utile pour le classement final)
void teddy__print(struct teddy* t);

// Affiche la queue `h`
void queue__print(struct queue* h);
