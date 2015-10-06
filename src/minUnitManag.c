#include "minUnitManag.h"

int mu_index = 0;
  
//boucle de lancement de l'animation pour les unités des minutes
void min_unit_next_frame_handler(void *context) {
  
  // Draw the next frame
  layer_mark_dirty(min_unit_layer);
  
  //si animation pas finie
  if(mu_index != -1)
    
    // Continue the sequence
    app_timer_register(DELTA, min_unit_next_frame_handler, NULL);
  
  else
    
    //raz index
    mu_index = 0;
    
}

//fonction de dessin de l'image actuelle au sein de l'animation pour les unités des minutes
void min_unit_update_proc(Layer *layer, GContext *ctx) {
  
  // Get the next frame
  GDrawCommandFrame *frame = gdraw_command_sequence_get_frame_by_index(min_unit_sequence, mu_index);
  
  // If another frame was found, draw it    
  if (frame) {
    gdraw_command_frame_draw(ctx, min_unit_sequence, frame, GPoint(_X, _Y));
  }
  
  // Advance to the next frame, wrapping if neccessary
  int num_frames = gdraw_command_sequence_get_num_frames(min_unit_sequence);
  mu_index++;
  
  if (mu_index >= num_frames) {
    mu_index = -1;
  }
  
}