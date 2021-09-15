#include <stdlib.h>
#include <string.h> //on utilise strcpy et strcmp
#include <time.h>
#include <math.h>
#define MAX_TRANSAC 100

// Donne un entier aleatoire inférieur strictement à 'i'
int random(int i);

// Genere des nombres semi aléatoires a partir de seed
void generate_seed(int s); 

// Portefeuille aprés `n` fois la transaction `s`
struct wallet utility__wallet_after_transac(struct teddy* ted,const struct transac* s,int n);

// Affiche les resultats de la partie
void display_results(struct queue Q);

// Affiche la transaction `s`
void transac__print(const struct transac* s);

// Retourne 0 si le teddy peut faire `N` fois la transaction, 1 sinon
int utility__transac_cant_make(struct teddy* ted , const struct transac* transac, int N);

// Retourne 1 si ted a deja joué dans cette place d'echange, 0 sinon
int utility__stockex_already_visited(const struct stockex* stock, struct teddy* ted);

// Affiche les noms des places d'echanges visitees par le teddy gagnant
void stockex__print_visited(struct teddy* ted);


