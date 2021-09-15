#include "good.h"
#include "stockex.h"
#include "queue.h"
#include "utility.h"
#include "strategy.h"
#include "testing_functions.h"


int good_rare_tests(int test)
{
  const struct stockex stock4 = {
				 2,  //nombre de transactions
				 "catcat",  //nom
				 {
				  {  //transaction 0
				   {{0,0,1}},  //acheté par le teddy
				   {{20,1,0}},  //à payer par le teddy
				   &stock4 ,  //place d'echange de la transaction 0
				   &stock0  //place d'echange debloquee par la transaction 0
				  } ,
				  {  //transaction 1
				   {{10,1,0}},  //acheté par le teddy
				   {{0,0,1}} ,  //à payer par le teddy
				   &stock4 ,  //place d'echange de la transaction 1
				   &stock1  //place d'echange debloquee par la transaction 1
				  }
				 }
  };

  struct teddy ted4 = {
		       4 ,  //numero du teddy 
		       {{100,100,1450}} ,  //son portefeuille
		       0 ,  //son temps de jeu 
		       3100 ,  //la valeur de son portefeuille
		       &stock4 ,  //la place actuelle
		       1 ,  //son nombre de places visitees
		       {"merignac"},  //les places visitees
		       0,  //numero de sa stratégie; 0 signifie stratégie aléatoire
		       NULL //sa transaction préférée, ce champ n'a de sens que lorseque le teddy est un stratège de niveau minimum 3
  };
  struct queue Q = queue__new();
  for (int j = 0; j < MAX_GOOD; j++){
    Q.wallet_all_teddies.data[j] = 0;
  }
  queue__push(&Q, 0, &ted4);
  Q.wallet_all_teddies.data[0] = 100;
  Q.wallet_all_teddies.data[1] = 100;
  Q.wallet_all_teddies.data[2] = 1450;
    switch(test){
    case 0:// Vérification de good__set_value
      good__set_value(1,23);
      if ( good__value(1) == 23 )
	{return 1;}
      return 0; 
    case 1:// Vérification de good__set_value
      good__set_value(2,500);
      if ( good__value(2) == 500 ) {
	return 1;
      }
      return 0; 
    case 2:// Vérification de good_*_limit
      queue__push(&Q, 0, &ted4);
      return utility__good_greater_limit(1, &Q) == 0 && utility__good_lesser_limit(1, &Q) == 1;
    case 3:// Vérification de check_total
      return utility__check_total(&Q, stockex__transaction(&stock4, 0)) == 1; 
    case 4:// Vérification de good_set_value au besoin
      utility__good_set_value(&Q, stockex__transaction(&stock4, 0));
      return  good__value(1) == 22 ;  
    case 5:// Vérification de good_set_value au besoin
      utility__good_set_value(&Q, stockex__transaction(&stock4, 1));
      return  good__value(2) == 501 ;  
    case 6:// Vérification de good_set_total amount
      good__set_total_amount(1, 7000);
      return good__total_amount(1) == 7000;
    default:
      return 0;
    }
}




int good_rare_tests_loop()
{
  int nbre_test = 7;
  int k = 0;
  for(int i = 0; i < nbre_test; i++) {
    if (good_rare_tests(i)) {
      k++;
    }
    else {
      printf ("\nERROR_good_rare_tests case %d\n", i);
    } 
  }
  printf("\n TOTAL TEST RARE GOOD PASSE: %d / %d \n", k, nbre_test);
  return k;
}
