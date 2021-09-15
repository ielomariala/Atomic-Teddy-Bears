#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_GOODS 20
#define MAX_PARTY_TIME 1000
#include "good.h"
#include "stockex.h"
#include "queue.h"
#include "utility.h"
#include "strategy.h"


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
int main (int argc,char* argv[])
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
			{},  // le tableau unitialement vide des places visitees
			i,  //le numéro de la stratégie qu'exerce ce teddy
			NULL  //la transaction favoris du teddy, ce champ n'est utilisée que si le teddy est stratège de niveau 3 ou 4 
    };
    tab[i] = ted;
    queue__push(&Q , 0 , &tab[i]);
  }           
 
  Q.wallet_all_teddies.data[0] = n * 1000;
  for (int j = 1; j < MAX_GOOD; j++) {
    good__set_total_amount(j, 2000);
    Q.wallet_all_teddies.data[j] = 0;
  }   

  int global_time = 0;
  while (global_time < turns) {
    struct teddy* active_ted = queue__pop(&Q);  // Le teddy prioritaire est choisi 	
    int teddytime = active_ted->time_played;  
    const struct stockex* stock = active_ted->current_stock;
    const struct transac* transac = strategy__transac_choice( stock , active_ted );
    
    if ( ! utility__transac_cant_make(active_ted, transac, 1)
	 && utility__check_total(&Q, transac)) {
      utility__good_set_value(&Q, transac);  // les valeurs des ressources sont modifiees si besoin
      active_ted->w = utility__wallet_after_transac(active_ted->w, transac, 1); // le teddy effectue la transaction 
      Q.wallet_all_teddies = utility__wallet_after_transac(Q.wallet_all_teddies,transac,1); // le portefeuille globale des teddies est modifie
      active_ted->time_played += 1 + log(1) / log(2);
      active_ted->current_stock = transac__next_stockex(transac);
    }
    else {
      active_ted->time_played++;
      if (active_ted->strategy != 0){
	active_ted->current_stock = transac__next_stockex(transac);   // Un teddy stratege ne peut pas se bloquer stupidement car il veut découvrir un stock
      }
    }
    global_time += active_ted->time_played - teddytime;  // on ajoute juste le temps du tour qu'a joué le teddy
    queue__push(&Q , active_ted->time_played , active_ted);  // on remet le teddy dans la file de priorite, à la bonne place
  }
  for (int k = 0; k < n; k++){
    Q.tab_queue[k]->value = wallet__value(Q.tab_queue[k]->w);
  }
  printf(" ========================\nLe temps global est: %d, la partie est donc terminee.\n", global_time);
  display_results(Q);
  return 0;
}


