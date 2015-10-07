#ifndef MINUNIT_H
#define MINUNIT_H
#include <pebble.h>

//nombre d'images dans une animation (ex : 1 -> 2)
#define CYCLE 25

//nombre de millisecondes entre 2 images de l'animation
#define DELTA 50
  
//position du point d'origine du dessin dans le layer
#define _XMU 72
#define _YMU 86
  

//Fichier de déclaration des variables, procédures liées aux unités de minutes

//mémoires de la valeur actuelle
extern int cur_min_unit;
  
//booléen marquant la première exécution graphique
extern bool mu_init;
  
//index de parcours de la séquence
extern int mu_index;
extern int mu_limit;
  
//layer de dessin des unités des minutes
extern Layer *min_unit_layer;

//séquence d'animation des unités des minutes
extern GDrawCommandSequence *min_unit_sequence; 

// -------------------------------------------
// ----------- Procédures --------------------
// -------------------------------------------


//boucle de lancement de l'animation pour les unités des minutes
void min_unit_next_frame_handler(void *context);

//fonction de dessin de l'image actuelle au sein de l'animation pour les unités des minutes
void min_unit_update_proc(Layer *layer, GContext *ctx);

#endif