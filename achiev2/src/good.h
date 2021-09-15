#define UINT_MAX 4294967295U
// L'enumerations des ressources
enum good {
           Miel,           // Toujours en premier 
           Cle_a_molette,
           Moteur_de_hors_bord,
           MAX_GOOD,        // Toujours en dernier 
           ERROR_GOOD = -1, // Toujours -1
};

// La description d'une ressource
const char* good__string(enum good g);

// La valeur de base d'une ressoucrce (en Miel)      
unsigned int good__value(enum good g);

// Un wallet contient differentes quentitees de ressources
struct wallet {
  unsigned int data[MAX_GOOD];
};

