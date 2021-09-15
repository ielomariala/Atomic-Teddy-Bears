#include "good.h"
#include "stockex.h"
#include "queue.h"
#include "utility.h"
#include "strategy.h"
#include "testing_functions.h"

int stock_change_tests(int test)
{
  const struct stockex stock4 = {
				 2,  //nombre de transactions
				 "catcat",  //nom
				 {
				  {  //transaction 0
				   {{0,0,1}},  //acheté par le teddy
				   {{20,0,0}},  //à payer par le teddy
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
  struct teddy ted0 = {
		       0,  //numero du teddy 
		       {{500,0,0}},  //son portefeuille
		       1,  //son temps de jeu 
		       500,  //la valeur de son portefeuille
		       &stock4,  //la place actuelle
		       0,  //son nombre de places visitees
		       {},  //les places visitees
		       0,  //numero de sa stratégie; 0 signifie stratégie aléatoire
		       NULL //sa transaction préférée, ce champ n'a de sens que lorseque le teddy est un stratège de niveau minimum 3
  };
  struct teddy ted1 = {
		       1,  //numero du teddy 
		       {{1000,0,0}} ,  //son portefeuille
		       100 ,  //son temps de jeu 
		       1000,  //la valeur de son portefeuille
		       &stock4 ,  //la place actuelle
		       1 ,  //son nombre de places visitees
		       {"catane"},  //les places visitees
		       0,  //numero de sa stratégie; 0 signifie stratégie aléatoire
		       NULL //sa transaction préférée, ce champ n'a de sens que lorseque le teddy est un stratège de niveau minimum 3
  };
  struct teddy ted2 = {
		       2 ,  //numero du teddy 
		       {{10,0,0}} ,  //son portefeuille
		       500 ,  //son temps de jeu 
		       10 ,  //la valeur de son portefeuille
		       &stock4 ,  //la place actuelle
		       2,  //son nombre de places visitees
		       {"talence","catane"},  //les places visitees
		       0,  //numero de sa stratégie; 0 signifie stratégie aléatoire
		       NULL //sa transaction préférée, ce champ n'a de sens que lorseque le teddy est un stratège de niveau minimum 3
  };
  struct teddy ted3 = {
		       3 ,  //numero du teddy 
		       {{10,0,0}} ,  //son portefeuille
		       1000 ,  //son temps de jeu 
		       10 ,  //la valeur de son portefeuille
		       &stock4 ,  //la place actuelle
		       1 ,  //son nombre de places visitees
		       {"merignac"},  //les places visitees
		       0,  //numero de sa stratégie; 0 signifie stratégie aléatoire
		       NULL //sa transaction préférée, ce champ n'a de sens que lorseque le teddy est un stratège de niveau minimum 3
  };
  size_t n = stockex__num_transactions(&stock4);
  int cpt =0;
  switch(test) {

  case 0:  // vérifie que le teddy ted0 n'a pas encore joué dans "catane"
    return utility__stockex_already_visited( &stock0 , &ted0) == 0 ;
    
  case 1:  //vérifie que le teddy ted1 a déjà joué dans le stock d'indice 2      
    return utility__stockex_already_visited( &stock0 , &ted1) == 1 ;
    
  case 2:  //vérifie le nbre de transactions existantes dans ce stock 
    return stockex__num_transactions(&stock4) == 2;
    
  case 3:  //ajoute un stock au tableau de stockex dont ted1 a joué
    strcpy(ted1.tab_stockex_names[ted1.nbr_stockex],stockex__name(&stock4)); 
    ted1.nbr_stockex++;
    return utility__stockex_already_visited( &stock4 , &ted1 ) == 1;
    
  case 4: //donne le nombre des transactions dans le stock 4 qui débloquent un nouveau stock pour ted1
    for (size_t i = 0 ; i < n ; i++) {
      if ( ! utility__stockex_already_visited(transac__next_stockex( stockex__transaction(&stock4 , i) ) , &ted1)) {
	
	cpt++;
      }
    }   
    return cpt == 1;
    
  case 5://de meme mais pour ted0
    for (size_t i = 0 ; i < n ; i++) {
      if ( ! utility__stockex_already_visited(transac__next_stockex( stockex__transaction(&stock4 , i) ) , &ted0) ) {
	cpt++;
      }
    }    
    return cpt == 2;
    
  case 6://de meme mais pour ted2
    for (size_t i = 0 ; i < n ; i++) {
      if ( ! utility__stockex_already_visited(transac__next_stockex( stockex__transaction(&stock4 , i) ) , &ted2) ) {
	cpt++;
      }
    }    
    return cpt == 0;
    
  case 7://de meme mais pour ted3
    for (size_t i = 0 ; i < n ; i++) {
      if ( ! utility__stockex_already_visited(transac__next_stockex( stockex__transaction(&stock4 , i) ) , &ted3) ) {
	cpt++;
      }
    }    
    return cpt == 2;
  default:
    return 0;
  }
}

int stock_change_tests_loop()
{
  int nbre_test = 8;
  int k = 0;
  for(int i = 0; i < nbre_test; i++) {
    if (stock_change_tests(i)) {
      k++;
    }
    else {
	printf ("ERROR_stock_change_tests case %d\n", i);
      }
  }
  printf("\n TOTAL TEST  STOCK_CHANGE PASSE: %d / %d \n", k, nbre_test);
  return k;
}
