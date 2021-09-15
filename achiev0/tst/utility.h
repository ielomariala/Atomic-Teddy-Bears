#include <time.h>
#include <math.h>

// Donne un entier aleatoire
int random(int i);

// Genere des nombres semi aléatoires a partir de seed
void generate_seed(int s); 

// Affiche les resultats de la partie
void display_results(struct queue Q);

// Renvoie 0 si le teddy peut faire `N` fois la transaction, 1 sinon
int utility__cant_make_transac(struct teddy* ted , const struct transac* transac, int N);

// Portefeuille aprés `n` fois la transaction `s`
struct wallet utility__wallet_after_transac(struct teddy* ted,const struct transac* s,int n);
