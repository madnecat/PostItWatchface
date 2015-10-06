#ifndef HOURUNIT_H
#define HOURUNIT_H
#include <pebble.h>

//nombre d'images dans une animation (ex : 1 -> 2)
#define CYCLE 25

//nombre de millisecondes entre 2 images de l'animation
#define DELTA 50
  
//position du point d'origine du dessin dans le layer
#define _X 2
#define _Y 2
  
//Fichier de déclaration des variables, procédures liées aux unités d'heures
  
// -------------------------------------------
// --------- Déclarations --------------------
// -------------------------------------------
  
//layer de dessin des unités des heures
static Layer *hour_unit_layer;

//séquence d'animation des unités des heures
static GDrawCommandSequence *hour_unit_sequence;

  
// -------------------------------------------
// ----------- Procédures --------------------
// -------------------------------------------

//boucle de lancement de l'animation pour les unités des heures
void hour_unit_next_frame_handler(void *context);

//fonction de dessin de l'image actuelle au sein de l'animation pour les unités des heures
void hour_unit_update_proc(Layer *layer, GContext *ctx);

#endif