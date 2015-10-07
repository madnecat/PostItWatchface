#include "minDozManag.h"

// -------------------------------------------
// --------- Déclarations --------------------
// -------------------------------------------
  
//layer de dessin des dizaines des minutes
Layer *min_doz_layer;

//séquence d'animation des dizaines des minutes
GDrawCommandSequence *min_doz_sequence;

//booléen marquant la première exécution graphique
bool md_init = true;

//mémoires de la valeur actuelle
int cur_min_doz;

//index de parcours de la séquence
int md_index;
int md_limit;

//booléen d'arrêt d'affichage
bool md_stop = false;

  
// -------------------------------------------
// ----------- Procédures --------------------
// -------------------------------------------
  
  
//boucle de lancement de l'animation pour les dizaines des minutes
void min_doz_next_frame_handler(void *context) {
  
  // Draw the next frame
  layer_mark_dirty(min_doz_layer);
  
  //si animation pas finie
  if(! md_stop)
    // Continue the sequence
    app_timer_register(DELTA, min_doz_next_frame_handler, NULL);

  //si animation finie, on repasse le booléen à faux
  else
    md_stop = false;
    
}

//fonction de dessin de l'image actuelle au sein de l'animation pour les dizaines des minutes
void min_doz_update_proc(Layer *layer, GContext *ctx) {
  
  // Get the next frame
  GDrawCommandFrame *frame = gdraw_command_sequence_get_frame_by_index(min_doz_sequence, md_index);
  
  // If another frame was found, draw it    
  if (frame) {
    gdraw_command_frame_draw(ctx, min_doz_sequence, frame, GPoint(0, 0));
  }
  
  // Advance to the next frame, wrapping if neccessary
  int num_frames = gdraw_command_sequence_get_num_frames(min_doz_sequence);
  
  //si on a atteint l'heure actuelle, on arrête
  if(md_index == md_limit)
    md_stop = true;
  //sinon on incrémente
  else
    md_index++;
  
  //si fin de l'animation on reboucle
  if (md_index >= num_frames) {
    md_index = 0;
  }
  
}