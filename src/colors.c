#include <pebble.h>
#include "colors.h"

//type énuméré contenant les couleurs supportées  
typedef enum couleurs {
  green,
  yellow,
  cyan,
  ShockingPink,
  ChromeYellow,
  VividViolet,
  nombre
} couleurs;

//couleur sélectionnée
enum couleurs couleur;

//fonction de récupération d'une couleur aléatoire
GColor getRandomColor() {
  
  //mise aléatoire de la fonction aléatoire
  srand(time(NULL));
  
  //récupération aléatoire de la couleur
  couleur = rand() % nombre;
  
  //comparaison de la couleur récupérée et retour de la valeur
  switch (couleur) {
    
    //vert
    case green : 
      return GColorGreen;
    
    //jaune
    case yellow : 
      return GColorYellow;
      
    //cyan
    case cyan : 
      return GColorCyan;
    
    //rose
    case ShockingPink :
      return GColorShockingPink;
    
    //orange
    case ChromeYellow : 
      return GColorChromeYellow;
    
    //violet
    case VividViolet : 
      return GColorVividViolet;
    
    //sinon (erreur) blanc
    default :
      return GColorWhite;
    
  }
  
}