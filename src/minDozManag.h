#ifndef MINDOZ_H
#define MINDOZ_H
#include <pebble.h>

//nombre d'images dans une animation (ex : 1 -> 2)
#define CYCLE 25

//nombre de millisecondes entre 2 images de l'animation
#define DELTA 50

//position du point d'origine du dessin dans le layer
#define _X 2
#define _Y 2
  
//Fichier de déclaration des variables, procédures liées aux dizaines de minutes
  
// -------------------------------------------
// --------- Déclarations --------------------
// -------------------------------------------
  
//layer de dessin des dizaines des minutes
static Layer *min_doz_layer;

//séquence d'animation des dizaines des minutes
static GDrawCommandSequence *min_doz_sequence;

  
// -------------------------------------------
// ----------- Procédures --------------------
// -------------------------------------------

//boucle de lancement de l'animation pour les dizaines des minutes
void min_doz_next_frame_handler(void *context);

//fonction de dessin de l'image actuelle au sein de l'animation pour les dizaines des minutes
void min_doz_update_proc(Layer *layer, GContext *ctx);

#endif