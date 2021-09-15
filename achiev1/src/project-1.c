#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_GOODS 20
#define MAX_PARTY_TIME 1000
#define MAX_OPERATIONS 100
#include "good.h"
#include "stockex.h"
#include "queue.h"
#include "utility.h"


// Valeurs par default de `seed`, `players` et `turns`
static int seed = 0;
static int players = 2;
static int turns = MAX_PARTY_TIME;

// Fonction qui permet a l'utilisateur de choisir les valeurs de quelques options
// Les options disponibles sont :
// -s <seed> : le paramêtre aleatoire
// -n <players> : le nombre de joueurs
// -m <turns> : le nombre de tour (le temps de jeu)
void parse_opts(int argc, char* argv[]) 
{
  int opt;
  while ((opt = getopt(argc, argv, "n:m:s:")) != -1) {
    switch (opt) {
    case 'n':
      if ( atoi(optarg) > MAX_TED || atoi(optarg)<=0 ) {
	printf("===>Vous avez choisi un nbre de joueurs <=0 ou bien > MAX_TED = 20, on se limitera à ce dernier\n");
      }
      players = (atoi(optarg) <= MAX_TED && atoi(optarg) > 0) ? atoi(optarg) : MAX_TED;
      break;
    case 'm':
      if ( atoi(optarg) > MAX_PARTY_TIME || atoi(optarg) <= 0 ) {
	printf("===>Vous avez choisi un nbre de turns <=0 ou bien > MAX_PARTY_TIME = 1000, on se limitera à ce dernier\n");
      }
      turns = ( atoi(optarg) <= MAX_PARTY_TIME && atoi(optarg) > 0 ) ? atoi(optarg) : MAX_PARTY_TIME;
      break;
    case 's':
      if ( atoi(optarg) <= 0 ) {
	printf("===>Vous avez choisi un seed <=0, on se limitera au temps comme génerateur aléatoire\n");
      }
      seed = (atoi(optarg) > 0) ? atoi(optarg) : 0;
      break; 
    default: 
      fprintf(stderr, "Usage: %s [-n players -m turns -s seed] \n",
	      argv[0]);
      exit(EXIT_FAILURE);
    }
  }
}


// La boucle principale du jeu 
int main (int argc,char*argv[])
{
  parse_opts(argc,argv);
  printf("Le `seed` choisi est %d.\n",seed);
  printf("Le nombre de joueurs choisi est %d.\n", players);
  printf("Le nombre de tours choisi est %d.\n\n", turns);
  
  
  generate_seed(seed);

  int n = players;
  const struct stockex* stocky = starting_stockex();
  struct queue Q = queue__new();
  struct teddy tab[MAX_TED];
  for (int i = 0; i < n; i++) {  // on initialise la queue   
    struct teddy ted = {i,  // le numero du teddy 
			{{1000,0,0}} ,  // son portefeuille iniiale
			0 ,  // son temps de jeu initial 
			1000,  // la valeur initiale de son portefeuille
			stocky,  // la place d'echange initiale, ou il se trouve
			0,  // le nombre initial de places visitees
			{}  // le tableau unitialement vide des places visitees
    };
    tab[i] = ted;
    queue__push(&Q , 0 , &tab[i]);
  }

  int global_time = 0;
  while (global_time < turns) {
    struct teddy* active_ted = queue__pop(&Q);  // le teddy prioritaire est choisi 	
    int teddytime = active_ted->time_played;  
    const struct stockex* stock = active_ted->current_stock;
    const struct transac* transac = utility__transac_choice( stock , active_ted );
    int N = random(MAX_OPERATIONS);
      
    while (  N!=0 && utility__cant_make_transac(active_ted , transac, N) ) { // il test si il peut faire `N` fois la transaction
	
      N = random(N);  // si il ne peut pas, il tire aleatoirement un nouveau `N` strictement inférieur et re-test
    }
      
    if (N > 0) {
      active_ted->w = utility__wallet_after_transac(active_ted, transac,N); // le teddy effectue la transaction 
      active_ted->value = wallet__value(active_ted->w);
      active_ted->time_played += 1 + log(N) / log(2);
      active_ted->current_stock = transac__next_stockex(transac);
    }
    else {
      active_ted->time_played++;
      active_ted->current_stock = transac__next_stockex(transac);   // si le teddy ne joue pas, il peut quand meme debloquer une place d'echange
    }
    global_time += active_ted->time_played - teddytime;  // on ajoute juste le temps du tour qu'a joué le teddy
    queue__push(&Q , active_ted->time_played , active_ted);  // on remet le teddy dans la file de priorite, a la bonne place
  }
  printf(" ========================\nLe temps global est: %d, la partie est donc terminee.\n", global_time);
  display_results(Q);
  return 0;
}
