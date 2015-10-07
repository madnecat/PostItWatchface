#include "hourUnitManag.h"

  
// -------------------------------------------
// --------- Déclarations --------------------
// -------------------------------------------
  
//layer de dessin des unités des heures
Layer *hour_unit_layer;

//séquence d'animation des unités des heures
GDrawCommandSequence *hour_unit_sequence;
GDrawCommandSequence *hour_unit_loop_sequence;

//booléen marquant la valeur de minuit
bool hu_loop = false;

//mémoires de la valeur actuelle
int cur_hour_unit;

//index de parcours de la séquence
int hu_index = 0;
int hu_limit;


// -------------------------------------------
// ----------- Procédures --------------------
// -------------------------------------------

  
//boucle de lancement de l'animation pour les unités des heures
void hour_unit_next_frame_handler(void *context) {
  
  // Draw the next frame
  layer_mark_dirty(hour_unit_layer);
  
  //si animation pas finie
  if(hu_index != hu_limit)
    // Continue the sequence
    app_timer_register(DELTA, hour_unit_next_frame_handler, NULL);

    
}

//fonction de dessin de l'image actuelle au sein de l'animation pour les unités des heures
void hour_unit_update_proc(Layer *layer, GContext *ctx) {
  
  //frame suivante
  GDrawCommandFrame *frame;
  
  //si on doit lancer l'animation 3 -> 4 mais qu'il est 23h passé : 3 -> 0
  if(hu_loop) {
    
    //raz index
    hu_index = 0;
    
    //maj limite
    hu_limit = 26;
    
    // Get the next frame
    frame = gdraw_command_sequence_get_frame_by_index(hour_unit_sequence, hu_index);
    
  } else
    
    // Get the next frame
    frame = gdraw_command_sequence_get_frame_by_index(hour_unit_sequence, hu_index);
  
  // If another frame was found, draw it    
  if (frame) {
    gdraw_command_frame_draw(ctx, hour_unit_sequence, frame, GPoint(0, 0));
  }
  
  // Advance to the next frame, wrapping if neccessary
  int num_frames = gdraw_command_sequence_get_num_frames(hour_unit_sequence);

  //si index différent de limite on incrémente
  if(hu_index != hu_limit)
    hu_index++;
  
  //si fin de l'animation on reboucle
  if (hu_index >= num_frames) {
    hu_index = 0;
  }
  
  //si fin de loop spécial, on remet index à 0
  if(hu_index == hu_limit && hu_loop)
    hu_index = 0;
  
}