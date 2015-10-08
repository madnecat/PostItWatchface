#include "hourUnitManag.h"

#define LIMIT_LOOP 26
  
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
bool hu_trigger_spe = false;
bool init_spe_seq = true;

//mémoires de la valeur actuelle
int cur_hour_unit;

//index de parcours de la séquence
int hu_index = 0;
int hu_index_loop = 0;
int hu_limit;


// -------------------------------------------
// ----------- Procédures --------------------
// -------------------------------------------

  
//boucle de lancement de l'animation pour les unités des heures
void hour_unit_next_frame_handler(void *context) {
  
  // Draw the next frame
  layer_mark_dirty(hour_unit_layer);
  
  //si animation pas finie
  if(hu_index != hu_limit && !hu_loop) {
  
    // Continue the sequence
    app_timer_register(DELTA, hour_unit_next_frame_handler, NULL);
    
  } else if(hu_index_loop == LIMIT_LOOP && hu_loop) {
    
    hu_loop = false;
    hu_limit = 0;
  
  } else if(hu_loop)
    
    app_timer_register(DELTA, hour_unit_next_frame_handler, NULL);
}

//fonction de dessin de l'image actuelle au sein de l'animation pour les unités des heures
void hour_unit_update_proc(Layer *layer, GContext *ctx) {
  
  //frame suivante
  GDrawCommandFrame *frame;
  
  if(hu_trigger_spe && hu_index_loop < LIMIT_LOOP) {
    
    frame = gdraw_command_sequence_get_frame_by_index(hour_unit_loop_sequence, hu_index_loop);
  } else {
  
    // Get the next frame
    frame = gdraw_command_sequence_get_frame_by_index(hour_unit_sequence, hu_index);
  }
  
  // If another frame was found, draw it    
  if (frame) {
    gdraw_command_frame_draw(ctx, hour_unit_sequence, frame, GPoint(0, 0));
  }
  
  // Advance to the next frame, wrapping if neccessary
  int num_frames = gdraw_command_sequence_get_num_frames(hour_unit_sequence);

  if(!hu_trigger_spe) {
  
    //si index différent de limite on incrémente
    if(hu_index != hu_limit)
      
      hu_index++;
    
    //si fin de l'animation on reboucle
    if (hu_index >= num_frames) {
      
      hu_index = 0;
      
    }
  
  } else {
    
    if(hu_index_loop != LIMIT_LOOP)
      
      hu_index_loop++;
    
    if(!hu_loop) {
      
      hu_trigger_spe = false;
      hu_index_loop = 0;
      
    }
    
  }
    
}