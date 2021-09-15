#include "good.h"
#include "stockex.h"
#include "queue.h"
#include "utility.h"
#include "testing_functions.h"



int wallet_tests()
{
  int k = 0;
  struct wallet w = {{1000,10,1}};
  
  if (wallet__value(w) == 1000*1 + 10*20 + 1*10) {  //test wallet_value
   
    k++;
  }
  else {
    printf("ERROR_stockex_num_transaction\n");
  }
 printf("\n\n TOTAL TEST WALLET PASSE: %d / 1 \n", k);
 return k;
} 


int stockex_tests()
{
  const struct transac s0 = {
			     {{10,1,0}},  //paye par le teddy 
			     {{0,0,1}}  //vendu
  };
  const struct transac s1 = {
			     {{0,0,1}},  //paye par le teddy 
			     {{20,0,0}}  //vendu
  };
  const struct transac s2 = {
			     {{0,3,1}},  //paye par le teddy 
			     {{20,15,0}}  //vendu
  };
  const struct stockex stock = {
				2,  //nombre de transactions
				"catane",  //nom 
				{s0,s1}  //transactions disponibles
  };
  const struct stockex stock2 = {
				 3,  //nombre de transactions
				 "talence",  //nom 
				 {s0,s1,s2}  //transactions disponibles
  };
  int k = 0;

  if (stockex__num_transactions(&stock) == 2) {  //test num_transac
   
    k++;
  }
  else {
    printf("ERROR_stockex_num_transaction\n");
  }

  
  if (stockex__num_transactions(&stock2) == 3) {  //test num_transac (2)
   
    k++;
  }
  else {
    printf("ERROR_stockex_num_transaction\n");
  }

  struct wallet w_achete = transac__in_wallet(&s0);
  struct wallet w_vendu = transac__out_wallet(&s0);

  if (w_achete.data[0] == 10 && w_achete.data[1] == 1 && w_achete.data[2] == 0 ) {  //transac_in_wallet
   
    k++;
  }
  else {
    printf("ERROR_stockex_transac_in_wallet\n");
  }


  if (w_vendu.data[0] == 0 && w_vendu.data[1] == 0 && w_vendu.data[2] == 1 ) {  //transac_out_wallet
    k++;
  }
  else {
    printf("ERROR_stockex_transac_out_wallet\n");
  }


  printf("\n\n TOTAL TEST STOCKEX PASSE: %d / 4 \n\n", k);
  return k;
}

int queue_tests()
{
  struct teddy ted = {
		      0,  //numero du teddy 
		      {{500,0,0}},  //son portefeuille
		      1,  //son temps de jeu 
		      500  //la valeur de son portefeuille
  };
  
  struct teddy ted1 = {
		       1,  //numero du teddy 
		       {{1000,0,0}},  //son portefeuille
		       100,  //son temps de jeu
		       1000  //la valeur de son portefeuille
  };
  
  struct teddy ted2 = {
		       2,  //numero du teddy 
		       {{10,0,0}},  //son portefeuille
		       500,  //son temps de jeu
		       10  //la valeur de son portefeuille
  };
  struct teddy ted3 = {
		       20,  //numero du teddy 
		       {{10,0,0}},  //son portefeuille
		       1000,  //son temps de jeu
		       10  //la valeur de son portefeuille
  };
  struct queue queue_void = queue__new();
  struct queue q = queue__new();
  struct queue q2 = queue__new();
  int k = 0;
  struct teddy* teddy_test_void = queue__pop(&queue_void); //enlever un teddy d'une queue vide
  if (teddy_test_void == NULL) {
    k++;
  }
  else {
       printf("ERROR_queue__pop\n");
  }


  queue__push(&q, ted3.time_played, &ted3); 
  queue__push(&q, ted1.time_played, &ted1);
  queue__push(&q, ted2.time_played, &ted2);

  struct teddy* ted_priority = queue__top(&q);  //recupperer le teddy prioritaire
  if (ted_priority->time_played == 100) {
    k++;
  }
  else {
    printf("ERROR_queue__top");
  }


  queue__push(&q, ted.time_played, &ted);    //recuperer le teddy prioritaire (2)
  struct teddy* ted_priority2 = queue__top(&q);
  if (ted_priority2->time_played == 1) {
   
    k++;
  }
  else {
    printf("ERROR_queue__top");
  }

  for(int i = 0; i < MAX_TED; i++) {
    queue__push(&q2, ted1.time_played, &ted1);
  }
  queue__push(&q2, ted.time_played, &ted);   //ajouter un teddy a une queue pleine 
  if (queue__top(&q2)->time_played == 100) {
    
      k++;
      }
  else {
    printf("ERROR_queue_push\n");
  }

  printf("\n TOTAL TEST QUEUE PASSE: %d / 4 \n", k);
  return k;
}

