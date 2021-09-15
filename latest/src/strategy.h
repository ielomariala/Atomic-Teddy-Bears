
// Choisit une transaction qui débloque un nouveau stock s'il existe, sinon choisit aléatoirement une transaction du stock
const struct transac* strategy__transac_random_choice(const struct stockex* stock, struct teddy* ted );

// Calcule et retourne le profit de la transaction 'transac'
int strategy__transac_gain(const struct transac* transac);

// Retourne l'indice du maximum du tableau 'tab' qui est de taille 'n'
size_t index_max_tab(int tab[], size_t n);

// Retourne l'indice du minimum du tableau 'tab' qui est de taille 'n'
size_t index_min_tab(int tab[], size_t n);

// Retourne le max du tableau 'tab' de longueur 'n'
int max_tab(int tab[], size_t n);

// Retourne la meilleure transaction (la transaction avec le plus de profit)  dans le stock actuel de 'ted'	
const struct transac* strategy__strategy1(struct teddy* ted);

// Retourne la meilleure transaction, en prenant en considération les transactions des stocks débloqués par cette transaction
const struct transac* strategy__strategy2(struct teddy* ted);

// Retourne soit la transaction favorite du teddy s'il peut la faire, et si la transaction qu'a choisit 'ted' par "strategy1" est moins optimale. Sinon la transaction favorite est mise à jour, et cette fonction retourne effectivement strategy1(ted) 
const struct transac* strategy__strategy3(struct teddy* ted);

// Retourne soit la transaction favorite du teddy s'il peut la faire, et si la transaction qu'a choisit 'ted' par "strategy2" est moins optimale. Sinon la transaction favorite est mise à jour, et cette fonction retourne effectivement recursive_strategy(ted) 
const struct transac* strategy__strategy4(struct teddy* ted);

// Le teddy découvre toutes les places d'échange et choisit parfaitement sa transaction favorite, ensuite il la fait s'il peut, sinon il fait la transaction avec le maximum de profit dans sa place d'échange actuelle
const struct transac* strategy__strategy5(const struct stockex* stock, struct teddy* ted);

// Retourne une transaction suivant une stratègie précise 
const struct transac* strategy__transac_choice(const struct stockex* stock, struct teddy* ted );
