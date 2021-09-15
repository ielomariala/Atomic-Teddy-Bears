#include <string.h> //on utilise strcpy et strcmp
#include <time.h>
#include <math.h>
#define MAX_TRANSAC 100

// Donne un entier aleatoire inférieure à 'i'
int random(int i);

// Genere des nombres semi aléatoires a partir de seed
void generate_seed(int s); 

// Affiche les resultats de la partie
void display_results(struct queue Q);

// Portefeuille aprés `n` fois la transaction `s`
struct wallet utility__wallet_after_transac(struct teddy* ted,const struct transac* s,int n);

// Renvoie 0 si le teddy peut faire `N` fois la transaction, 1 sinon
int utility__cant_make_transac(struct teddy* ted , const struct transac* transac, int N);

// Choisit une transaction qui débloque un nouveau stock s'il existe, sinon choisit aléatoirement une transaction du stock
const struct transac* utility__transac_choice(const struct stockex* stock, struct teddy* ted );

// Renvoi 1 si ted a deja joué dans cette place d'echange, 0 sinon
int utility__stockex_already_visited(const struct stockex* stock, struct teddy* ted);


