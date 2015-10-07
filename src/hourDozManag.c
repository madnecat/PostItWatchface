#include "hourDozManag.h"
  
// -------------------------------------------
// --------- Déclarations --------------------
// -------------------------------------------
  
//layer de dessin des dizaines d'heures
Layer *hour_doz_layer;

//séquence d'animation des dizaines d'heures
GDrawCommandSequence *hour_doz_sequence;

//booléen marquant la première exécution graphique
bool hd_init = true;
  
//mémoires de la valeur actuelle
int cur_hour_doz;

//index de parcours de la séquence
int hd_index = 0;
int hd_limit;


// -------------------------------------------
// ----------- Procédures --------------------
// -------------------------------------------

  
//boucle de lancement de l'animation pour les dizaines d'heures
void hour_doz_next_frame_handler(void *context) {
  
  // Draw the next frame
  layer_mark_dirty(hour_doz_layer);
  
  //si animation pas finie
  if(hd_index != hd_limit)
    // Continue the sequence
    app_timer_register(DELTA, hour_doz_next_frame_handler, NULL);
    
}

//fonction de dessin de l'image actuelle au sein de l'animation pour les dizaines d'heures
void hour_doz_update_proc(Layer *layer, GContext *ctx) {
  
  // Get the next frame
  GDrawCommandFrame *frame = gdraw_command_sequence_get_frame_by_index(hour_doz_sequence, hd_index);
  
  // If another frame was found, draw it    
  if (frame) {
    gdraw_command_frame_draw(ctx, hour_doz_sequence, frame, GPoint(0, 0));
  }
  
  // Advance to the next frame, wrapping if neccessary
  int num_frames = gdraw_command_sequence_get_num_frames(hour_doz_sequence);

  //si index différent de limite on incrémente
  if(hd_index != hd_limit)
    hd_index++;
  
  //si fin de l'animation on reboucle
  if (hd_index >= num_frames) {
    hd_index = 0;
  }
  
}