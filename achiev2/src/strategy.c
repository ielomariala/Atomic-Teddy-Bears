#include "good.h"
#include "stockex.h"
#include "queue.h"
#include "utility.h"
#include "strategy.h"


// Choisit une transaction qui débloque un nouveau stock s'il existe, sinon choisit aléatoirement une transaction du stock
const struct transac* strategy__transac_random_choice(const struct stockex* stock, struct teddy* ted )
{
  if (! utility__stockex_already_visited(ted->current_stock , ted)) {  // copier la place d'echange dans le tableau de noms de stockex si il n'y avait pas encore joué
 
    strcpy(ted->tab_stockex_names[ted->nbr_stockex],stockex__name(ted->current_stock)); 
    ted->nbr_stockex++;
  }
  size_t n = stockex__num_transactions(stock);
  size_t tab_indice_transac[MAX_TRANSAC] = {0};  // un tableau que l'on va remplire avec les indices de transactions qui débloquent une nouvelle place d'echange
  int cpt = 0;
  for (size_t i = 0 ; i < n ; i++) {  // recherche des transactions qui débloquent un nouveau stocke nouvelle place 
    
    if ( ! utility__stockex_already_visited(transac__next_stockex( stockex__transaction(stock , i) ) , ted) ) {
	
      tab_indice_transac[cpt] = i;  // remplissage du tableau 
      cpt++;
    }
  }  
  if ( cpt != 0 ) {  // SI il y a au moins une transaction qui débloque un nouveau stock
    
    int r = random(cpt); // choisit un nombre entre 0 et le nombre de transactions qui débloquent un nouveau stock
    return stockex__transaction( stock , tab_indice_transac[r] );  // le tab_indice_transac retourne l'indice de cette transaction dans tab_stockex
  }
  else {
    size_t j = random(n);
    return stockex__transaction( stock , j );  // SINON, retourne une transaction aleatoire
  }
}

int strategy__transac_gain(const struct transac *s)
{
  int k=0;//le profit de cette transaction
  for (int i=0 ; i<MAX_GOOD; i++)
    {
      k += (transac__in_wallet(s).data[i]-transac__out_wallet(s).data[i])*good__value(i);
    }
  return k;
} 	

size_t index_max_tab(int tab[], size_t n)
{
  size_t i=1;
  size_t indice_max=0;
  for(i=1 ; i < n ; i++)
    {
      indice_max=(tab[indice_max] >= tab[i]) ? indice_max : i;
    }
  return indice_max;
}

size_t index_min_tab(int tab[], size_t n)
{
  size_t i=1;
  size_t indice_min=0;
  for(i=1 ; i < n ; i++)
    {
      indice_min=(tab[indice_min] <= tab[i]) ? indice_min : i;
    }
  return indice_min;
}

int max_tab(int tab[], size_t n)//donne le max d'un tableau tab de longueur n
{
  size_t i=1;
  int max=tab[0];
  for(i=1 ; i < n ; i++)
    {
      max = (max >= tab[i]) ? max : tab[i];
    }
  return max;
}

const struct transac* strategy__strategy1(struct teddy *ted)
{ 
  if (! utility__stockex_already_visited(ted->current_stock , ted))
    {
      strcpy(ted->tab_stockex_names[ted->nbr_stockex],stockex__name(ted->current_stock)); 
      ted->nbr_stockex++;
    }
  const struct stockex* stock = ted->current_stock;
  size_t i = 0, n = stockex__num_transactions(stock);
  int profitab[MAX_TRANSAC];
  for (i=0 ; i<n ; i++){
    profitab[i]=strategy__transac_gain(stockex__transaction(stock,i));
  }
  size_t indice_max=index_max_tab(profitab,n);
  size_t indice_min=index_min_tab(profitab,n);
  const struct transac* transac = stockex__transaction(stock,indice_max);
  size_t cpt = 0;
  while ( cpt < n && utility__transac_cant_make(ted , transac, 1) ) { 
    profitab[indice_max]=profitab[indice_min];
    transac = stockex__transaction(stock,index_max_tab(profitab,n));
    cpt++;
  }
  return transac;
}

const struct transac* strategy__strategy2(struct teddy *ted)
{
  if (! utility__stockex_already_visited(ted->current_stock , ted))
    {
      strcpy(ted->tab_stockex_names[ted->nbr_stockex],stockex__name(ted->current_stock)); 
      ted->nbr_stockex++;
    }
  const struct stockex* stock = ted->current_stock;
  size_t i = 0, j = 0, n = stockex__num_transactions(stock);
  int profitab_stock[MAX_TRANSAC][MAX_TRANSAC];//profitab_stock[i][k] signifie le profit de la transaction d'indice k dans le stock débloqué par la transaction d'indice i dans le stock actuel du teddy
  int profitab[MAX_TRANSAC];
  for (i=0 ; i<n ; i++){
    const struct transac* couple_transac = stockex__transaction(stock,i);
    stock = transac__next_stockex(couple_transac);
    size_t m = stockex__num_transactions(stock);
    for (j=0 ; j<m ; j++){
      profitab_stock[i][j] = strategy__transac_gain(couple_transac)+strategy__transac_gain(stockex__transaction(stock,j));
    }
    stock = ted->current_stock;    
    profitab[i] = strategy__transac_gain(stockex__transaction(stock,i))+max_tab(profitab_stock[i],m);
  }
  size_t indice_max=index_max_tab(profitab,n);
  size_t indice_min=index_min_tab(profitab,n);
  const struct transac* transac = stockex__transaction(stock,indice_max);
  size_t cpt = 0;
  while ( cpt < n && utility__transac_cant_make(ted , transac, 1) ) { 
    profitab[indice_max]=profitab[indice_min];
    transac = stockex__transaction(stock,index_max_tab(profitab,n));
    cpt++;
  }
  return transac;
}

const struct transac* strategy__strategy3(struct teddy *ted)
{
  const struct transac* transac = strategy__strategy1(ted);
  ted->favourite_transac = (ted->favourite_transac == NULL || strategy__transac_gain(ted->favourite_transac) < strategy__transac_gain(transac) ) ? transac : ted->favourite_transac ;
  if ( ! utility__transac_cant_make(ted, ted->favourite_transac , 1) ){
    return ted->favourite_transac;}
  else {return transac;}
}

const struct transac* strategy__strategy4(struct teddy *ted)
{
  const struct transac* transac =strategy__strategy2(ted);
  ted->favourite_transac = (ted->favourite_transac == NULL || strategy__transac_gain(ted->favourite_transac) < strategy__transac_gain(transac) ) ? transac : ted->favourite_transac ;
  if ( ! utility__transac_cant_make(ted, ted->favourite_transac , 1) ){
    return ted->favourite_transac;}
  else {return transac;}
}

// Choisit une transaction profitable qui débloque un nouveau stock s'il existe, sinon il choisit sa transaction favoris ou la transaction la plus profitable du stock courant.
const struct transac* strategy__strategy5(const struct stockex* stock, struct teddy* ted )
{
  if (! utility__stockex_already_visited(ted->current_stock , ted)) {  // copier la place d'echange dans le tableau de noms de stockex si il n'y avait pas encore joué
 
    strcpy(ted->tab_stockex_names[ted->nbr_stockex],stockex__name(ted->current_stock)); 
    ted->nbr_stockex++;
  }
  size_t n = stockex__num_transactions(stock);
  size_t tab_indice_transac[MAX_TRANSAC] = {0};  // un tableau que l'on va remplire avec les indices de transactions qui débloquent une nouvelle place d'echange
  int cpt = 0;
  for (size_t i = 0 ; i < n ; i++) {  // recherche des transactions qui débloquent un nouveau stocke nouvelle place 
    const struct transac* transac = strategy__strategy1(ted);
    ted->favourite_transac = (ted->favourite_transac == NULL || strategy__transac_gain(ted->favourite_transac) < strategy__transac_gain(transac) ) ? transac : ted->favourite_transac ; // il change sa transaction favoris s'il a trouvé une transaction plus profitable
    if ( ! utility__stockex_already_visited(transac__next_stockex( stockex__transaction(stock , i) ) , ted) ) {
	
      tab_indice_transac[cpt] = i;  // remplissage du tableau 
      cpt++;
    }
  }  
  if ( cpt != 0 ) {  // SI il y a au moins une transaction qui débloque un nouveau stock
    const struct transac* t = stockex__transaction( stock, tab_indice_transac[0]);
    for (int k=1; k< cpt; k++){
      const struct transac* t2 = stockex__transaction( stock, tab_indice_transac[k] );
      t = ( strategy__transac_gain(t) >= strategy__transac_gain(t2) ) ? t : t2 ;
    }
    return t;// On retourne la transaction la plus profitable qui débloque une nouvelle place d'échange
  }
  else {
    if ( ! utility__transac_cant_make(ted, ted->favourite_transac , 1) ){
      return ted->favourite_transac;}
    else {return strategy__strategy1(ted);}   // SINON, retourne sa transaction favoris s'il peut la faire, sinon la transaction la plus profitable dans ce lieu
  }
}

const struct transac* strategy__transac_choice(const struct stockex*stock, struct teddy *ted ) {
  switch (ted->strategy) {
  case 1:
    return strategy__strategy1(ted);
  case 2:
    return strategy__strategy2(ted);
  case 3:
    return strategy__strategy3(ted);
  case 4:
    return strategy__strategy4(ted);
  case 5:
    return strategy__strategy5(stock, ted);
  default:
    return strategy__transac_random_choice(stock,ted);
  }
}
