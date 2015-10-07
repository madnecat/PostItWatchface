#ifndef HOURDOZ_H
#define HOURDOZ_H
#include <pebble.h>

//nombre d'images dans une animation (ex : 1 -> 2)
#define CYCLE 25

//nombre de millisecondes entre 2 images de l'animation
#define DELTA 50
  
//position du point d'origine du dessin dans le layer
#define _XHD 2
#define _YHD 2
  
//Fichier de déclaration des variables, procédures liées aux dizaines d'heures
  
// -------------------------------------------
// --------- Déclarations --------------------
// -------------------------------------------
  
//mémoires de la valeur actuelle
extern int cur_hour_doz;
  
//index de parcours de la séquence
extern int hd_index; 
extern int hd_limit;
  
//layer de dessin des dizaines d'heures
extern Layer *hour_doz_layer;

//séquence d'animation des dizaines d'heures
extern GDrawCommandSequence *hour_doz_sequence;
  
// -------------------------------------------
// ----------- Procédures --------------------
// -------------------------------------------

//boucle de lancement de l'animation pour les dizaines d'heures
void hour_doz_next_frame_handler(void *context);

//fonction de dessin de l'image actuelle au sein de l'animation pour les dizaines d'heures
void hour_doz_update_proc(Layer *layer, GContext *ctx);

#endif