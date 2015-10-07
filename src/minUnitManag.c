#include "minUnitManag.h"

  
// -------------------------------------------
// --------- Déclarations --------------------
// -------------------------------------------
  
  
//layer de dessin des unités des minutes
Layer *min_unit_layer;

//séquence d'animation des unités des minutes
GDrawCommandSequence *min_unit_sequence;  
  
//booléen marquant la première exécution graphique
bool mu_init = true;
  
//mémoires de la valeur actuelle
int cur_min_unit;

//index de parcours de la séquence
int mu_index = 0;
int mu_limit;

//booléen d'arrêt d'affichage
bool mu_stop = false;
  

// -------------------------------------------
// ----------- Procédures --------------------
// -------------------------------------------


//boucle de lancement de l'animation pour les unités des minutes
void min_unit_next_frame_handler(void *context) {

  // Draw the next frame
  layer_mark_dirty(min_unit_layer);

  //si animation pas finie
  if(! mu_stop)
    // Continue the sequence
    app_timer_register(DELTA, min_unit_next_frame_handler, NULL);

  //si animation finie, on repasse le booléen à faux
  else
    mu_stop = false;
    
}

//fonction de dessin de l'image actuelle au sein de l'animation pour les unités des minutes
void min_unit_update_proc(Layer *layer, GContext *ctx) {
  
  // Get the next frame
  GDrawCommandFrame *frame = gdraw_command_sequence_get_frame_by_index(min_unit_sequence, mu_index);
  
  // If another frame was found, draw it    
  if (frame) { 

    gdraw_command_frame_draw(ctx, min_unit_sequence, frame, GPoint(0, 0));
  }

  // Advance to the next frame, wrapping if neccessary
  int num_frames = gdraw_command_sequence_get_num_frames(min_unit_sequence);
  
  //si on a atteint l'heure actuelle, on arrête
  if(mu_index == mu_limit)
    mu_stop = true;
  //sinon on incrémente
  else
    mu_index++;
  
  //si fin de l'animation on reboucle
  if (mu_index >= num_frames) {
    mu_index = 0;
  }
  
}