#include "hourUnitManag.h"

  
// -------------------------------------------
// --------- Déclarations --------------------
// -------------------------------------------
  
//layer de dessin des unités des heures
Layer *hour_unit_layer;

//séquence d'animation des unités des heures
GDrawCommandSequence *hour_unit_sequence;

//booléen marquant la première exécution graphique
bool hu_init = true;

//mémoires de la valeur actuelle
int cur_hour_unit;

//index de parcours de la séquence
int hu_index = 0;
int hu_limit;

//booléen d'arrêt d'affichage
bool hu_stop = false;

  
// -------------------------------------------
// ----------- Procédures --------------------
// -------------------------------------------

  
//boucle de lancement de l'animation pour les unités des heures
void hour_unit_next_frame_handler(void *context) {
  
  // Draw the next frame
  layer_mark_dirty(hour_unit_layer);
  
  //si animation pas finie
  if(! hu_stop)
    // Continue the sequence
    app_timer_register(DELTA, hour_unit_next_frame_handler, NULL);

  //si animation finie, on repasse le booléen à faux
  else
    hu_stop = false;
    
}

//fonction de dessin de l'image actuelle au sein de l'animation pour les unités des heures
void hour_unit_update_proc(Layer *layer, GContext *ctx) {
  
  // Get the next frame
  GDrawCommandFrame *frame = gdraw_command_sequence_get_frame_by_index(hour_unit_sequence, hu_index);
  
  // If another frame was found, draw it    
  if (frame) {
    gdraw_command_frame_draw(ctx, hour_unit_sequence, frame, GPoint(0, 0));
  }
  
  // Advance to the next frame, wrapping if neccessary
  int num_frames = gdraw_command_sequence_get_num_frames(hour_unit_sequence);
  //si on a atteint l'heure actuelle, on arrête
  if(hu_index == hu_limit)
    hu_stop = true;
  //sinon on incrémente
  else
    hu_index++;
  
  //si fin de l'animation on reboucle
  if (hu_index >= num_frames) {
    hu_index = 0;
  }
  
}