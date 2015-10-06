#include "hourDozManag.h"

int hd_index = 0;
  
//boucle de lancement de l'animation pour les dizaines d'heures
void hour_doz_next_frame_handler(void *context) {
  
  // Draw the next frame
  layer_mark_dirty(hour_doz_layer);
  
  //si animation pas finie
  if(hd_index != -1)
    
    // Continue the sequence
    app_timer_register(DELTA, hour_doz_next_frame_handler, NULL);
  
  else
    
    //raz index
    hd_index = 0;
    
}

//fonction de dessin de l'image actuelle au sein de l'animation pour les dizaines d'heures
void hour_doz_update_proc(Layer *layer, GContext *ctx) {
  
  // Get the next frame
  GDrawCommandFrame *frame = gdraw_command_sequence_get_frame_by_index(hour_doz_sequence, hd_index);
  
  // If another frame was found, draw it    
  if (frame) {
    gdraw_command_frame_draw(ctx, hour_doz_sequence, frame, GPoint(_X, _Y));
  }
  
  // Advance to the next frame, wrapping if neccessary
  int num_frames = gdraw_command_sequence_get_num_frames(hour_doz_sequence);
  hd_index++;
  
  if (hd_index >= num_frames) {
    hd_index = -1;
  }
  
}