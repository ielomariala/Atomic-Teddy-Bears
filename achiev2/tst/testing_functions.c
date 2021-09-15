#include "good.h"
#include "stockex.h"
#include "queue.h"
#include "utility.h"
#include "strategy.h"
#include "testing_functions.h"



int strategy_tests( int test ){
 const struct stockex stock5 = {
    1,  //nombre de transactions
    "catcat5",  //nom
    {
      {  //transaction 0
	{{0,0,1}},  //acheté par le teddy
	{{20,158,0}},  //à payer par le teddy
	&stock5 ,  //place d'echange de la transaction 0
	&stock5  //place d'echange debloquee par la transaction 0
      } 
    }
  };
 const struct stockex stock6 = {
    1,  //nombre de transactions
    "catcat6",  //nom
    {
      {  //transaction 0
	{{0,4569,1}},  //acheté par le teddy
	{{20,0,0}},  //à payer par le teddy
	&stock6 ,  //place d'echange de la transaction 0
	&stock6  //place d'echange debloquee par la transaction 0
      } 
    }
  };

  const struct stockex stock4 = {
    2,  //nombre de transactions
    "catcat",  //nom
    {
      {  //transaction 0
	{{0,50,1}},  //acheté par le teddy
	{{20,0,0}},  //à payer par le teddy
	&stock4 ,  //place d'echange de la transaction 0
	&stock5  //place d'echange debloquee par la transaction 0
      } ,
      {  //transaction 1
	{{0,40,1}},  //acheté par le teddy
	{{20,0,0}} ,  //à payer par le teddy
	&stock4 ,  //place d'echange de la transaction 1
	&stock6  //place d'echange debloquee par la transaction 1
      }
    }
  };


  int players=5, seed=0, turns=50;
  int  gagne0=0, gagne1=0, gagne2=0, gagne3=0, gagne4=0 ;
  generate_seed(seed);
  int nbre =players;  // BEGIN init_queue
  const struct stockex* stocky = starting_stockex();
  struct queue Q = queue__new();
  struct teddy tableau[MAX_TED]; 
  for (int i=0; i<nbre; i++)  
    {
      struct teddy ted = {i, {{1000,0,0}} , 0 , 1000 , stocky,0,{},i , NULL};
      tableau[i]=ted;
      queue__push(&Q , 0 , &tableau[i]);
    } //END init_queue

  struct teddy ted4 = {
		       4 ,  //numero du teddy 
		       {{100,100,100}} ,  //son portefeuille
		       0 ,  //son temps de jeu 
		       3100 ,  //la valeur de son portefeuille
		       &stock4 ,  //la place actuelle
		       1 ,  //son nombre de places visitees
		       {"merignac"},  //les places visitees
		       0,  //numero de sa stratégie; 0 signifie stratégie aléatoire
		       NULL //sa transaction préférée, ce champ n'a de sens que lorseque le teddy est un stratège de niveau minimum 3
  };

int global_time = 0;
  switch (test){ 
  case 0:
    if (strategy__transac_gain(stockex__transaction(&stock5,0)) == -3170){
      return 1;
    }
    return 0;
  case 1:
    if (strategy__transac_gain(stockex__transaction(&stock6,0)) == 91370){
      return 1;
    }
    return 0;
  case 2:
    return strategy__transac_gain(strategy__strategy1(&ted4)) == 990;//alors que cette stratégie débloque stock5 qui des déficits insupportables(voir case 0)
  case 3:      
    return strategy__transac_gain(strategy__strategy2(&ted4)) == 790;//alors que cette stratégie débloque stock6 qui des gains merveilleux(voir case 1)
  case 4: 
    for (int k=0; k < 3; k++) {
      stocky = starting_stockex();
      Q = queue__new();
      for (int i=0; i<nbre; i++) {
	struct teddy ted = {i, {{1000,0,0}} , 0 , 1000 , stocky,0,{},i , NULL};
	tableau[i]=ted;
	queue__push(&Q , 0 , &tableau[i]);
      }
      global_time = 0;
      while (global_time < turns) {
	struct teddy *active_ted = queue__pop(&Q);
	int teddytime = active_ted->time_played;
	const struct stockex *stock = active_ted->current_stock;
	const struct transac *transac = strategy__transac_choice( stock , active_ted );
      
	if ( ! utility__transac_cant_make(active_ted, transac, 1) ) {
	  active_ted->w = utility__wallet_after_transac(active_ted,transac,1);
	  //	  active_ted->value = wallet__value(active_ted->w);
	  active_ted->time_played += 1+log(1)/log(2);
	  active_ted->current_stock = transac__next_stockex(transac);
	}  
	else {
	  active_ted->time_played++;
	  if (active_ted->strategy != 0){
	    active_ted->current_stock = transac__next_stockex(transac);   // Un teddy stratege ne peut pas se bloquer stupidement car il veut découvrir un stock
	  }
	}
	global_time += active_ted->time_played - teddytime;
	queue__push(&Q , active_ted->time_played , active_ted);
      }
      
      for (int k = 0; k<Q.n; k++){
	Q.tab_queue[k]->value = wallet__value(Q.tab_queue[k]->w);
      }

      queue__sort_tab(&Q);
      if (Q.tab_queue[nbre-1]->num == 0) { gagne0++;}
      if (Q.tab_queue[nbre-1]->num == 1) { gagne1++;}
      if (Q.tab_queue[nbre-1]->num == 2) { gagne2++;}
      if (Q.tab_queue[nbre-1]->num == 3) { gagne3++;} // Dans les conditions normales, sans changement de valeur, si le 3 gagne le 4 a la meme valeur, il gagne aussi
      if (Q.tab_queue[nbre-1]->num == 4) { gagne4++;}
    } 
    if ( ! gagne0 )
      {return 1;}
    return 0;
  default:
    return 0;
  }
}

int strategy_tests_loop()
{
  int nbre_test = 5;
  int k = 0;
  for(int i = 0; i < nbre_test; i++) {
    if (strategy_tests(i)) {
      k++;
    }
    else {
      printf ("\nERROR_strategy_tests case %d\n", i);
      }
  }
  printf("\n TOTAL TEST STRATEGY PASSE: %d / %d \n", k, nbre_test);
  return k;
}





