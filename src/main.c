#include <pebble.h>

//nombre d'images dans une animation (ex : 1 -> 2)
#define CYCLE 25

//nombre de millisecondes entre 2 images de l'animation
#define DELTA 50
// -------------------------------------------
// --------- Déclarations --------------------
// -------------------------------------------

//type structure composite
struct liste_sequence_layer {
  //layer de dessin
  Layer *active_layer;
  //séquence d'animation
  GDrawCommandSequence *active_sequence;
  //point d'origine
  GPoint *origine;
  //élément suivant
  struct liste_sequence_layer *suivant;
} liste_sequence_layer;

static struct liste_sequence_layer *s_maillon_actuel, 
  *s_maillon_origine;

//fenêtre principale
static Window *s_main_window;


//mémoires de minutes, heures
static int cur_min_unit = 0,
  cur_min_doz = 0, 
  cur_hour_unit = 0, 
  cur_hour_doz = 0;

//index actuel dans l'animation
static int s_index = 0;

// -------------------------------------------
// ----------- Procédures --------------------
// -------------------------------------------

//boucle de lancement de l'animation
static void next_frame_handler(void *context) {
  
  // Draw the next frame
  layer_mark_dirty(s_maillon_actuel->active_layer);

  //si animation pas finie
  if(s_index != -1)
  
    // Continue the sequence
    app_timer_register(DELTA, next_frame_handler, NULL);
  
  //sinon si liste pas totalement déroulée
  else if (s_maillon_actuel != NULL) {
    
    //maillon suivant
    s_maillon_actuel = s_maillon_actuel->suivant;
    
    //raz index
    s_index = 0;    
    
    // Continue the sequence
    app_timer_register(DELTA, next_frame_handler, NULL);
  
  } else {
    
    //remise à l'origine du maillon
    s_maillon_actuel = s_maillon_origine;
    
    //raz index
    s_index = 0;
    
  }
}

//fonction de dessin de l'image actuelle au sein de l'animation
static void update_proc(Layer *layer, GContext *ctx) {
  
  // Get the next frame
  GDrawCommandFrame *frame = gdraw_command_sequence_get_frame_by_index(s_maillon_actuel->active_sequence, s_index);
  
  // If another frame was found, draw it    
  if (frame) {
    gdraw_command_frame_draw(ctx, s_maillon_actuel->active_sequence, frame, *(s_maillon_actuel->origine));
  }

  // Advance to the next frame, wrapping if neccessary
  int num_frames = gdraw_command_sequence_get_num_frames(s_maillon_actuel->active_sequence);
  s_index++;
  if (s_index == num_frames) {
    s_index = -1;
  }
  
}

//hook appelé lors du changement de temps
static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  
  // Start the animation
  app_timer_register(DELTA, next_frame_handler, NULL);
  
}

//chargement de la fenêtre principale
static void main_window_load(Window *window) {
  
  //layer de la fenêtre principale
  Layer *window_layer = window_get_root_layer(window);
  
  //coordonnées de la fenêtre principale
  GRect bounds = layer_get_bounds(window_layer);
  
  //allocation premier maillon
  s_maillon_actuel = malloc(sizeof *s_maillon_actuel);
  
  //sauvegarde adresse premier maillon
  s_maillon_origine = s_maillon_actuel;
  
  //instanciation premier maillon -> hour doz
  s_maillon_actuel->active_layer = layer_create(GRect(0, 0, bounds.size.w, bounds.size.h));
  s_maillon_actuel->active_sequence = gdraw_command_sequence_create_with_resource(RESOURCE_ID_FRAMES_0_2);
  s_maillon_actuel->origine = &(GPoint(0,2));
  s_maillon_actuel->suivant = malloc(sizeof *s_maillon_actuel);
  layer_set_update_proc(s_maillon_actuel->active_layer, update_proc);
  
  //maillon suivant
  s_maillon_actuel = s_maillon_actuel->suivant;
  
  //instanciation second maillon -> hour unit
  s_maillon_actuel->active_layer = layer_create(GRect(0, 0, bounds.size.w, bounds.size.h));
  s_maillon_actuel->active_sequence = gdraw_command_sequence_create_with_resource(RESOURCE_ID_FRAMES_0_9);
  s_maillon_actuel->origine = &(GPoint(72,2));
  s_maillon_actuel->suivant = malloc(sizeof *s_maillon_actuel);
  layer_set_update_proc(s_maillon_actuel->active_layer, update_proc);
  
    //maillon suivant
  s_maillon_actuel = s_maillon_actuel->suivant;
  
  //instanciation troisième maillon -> min doz
  s_maillon_actuel->active_layer = layer_create(GRect(0, 0, bounds.size.w, bounds.size.h));
  s_maillon_actuel->active_sequence = gdraw_command_sequence_create_with_resource(RESOURCE_ID_FRAMES_0_6);
  s_maillon_actuel->origine = &(GPoint(0,86));
  s_maillon_actuel->suivant = malloc(sizeof *s_maillon_actuel);
  layer_set_update_proc(s_maillon_actuel->active_layer, update_proc);
  
    //maillon suivant
  s_maillon_actuel = s_maillon_actuel->suivant;
  
  //instanciation quatrième maillon -> min unit
  s_maillon_actuel->active_layer = layer_create(GRect(0, 0, bounds.size.w, bounds.size.h));
  s_maillon_actuel->active_sequence = gdraw_command_sequence_create_with_resource(RESOURCE_ID_FRAMES_0_9);
  s_maillon_actuel->origine = &(GPoint(72,86));
  s_maillon_actuel->suivant = NULL;
  layer_set_update_proc(s_maillon_actuel->active_layer, update_proc);
  
  //initialisation du maillon du parcours
  s_maillon_actuel = s_maillon_origine;
  
}

//destruction des objets dynamiques
static void main_window_unload(Window *window) {
  
  //variable temporaire
  struct liste_sequence_layer *tmp = s_maillon_origine;
  
  //parcours des maillons
  while(s_maillon_origine != NULL) {
    
    tmp = s_maillon_origine->suivant;
    free(s_maillon_origine);
    s_maillon_origine = tmp;
    
  } //fin désallocation liste
  
}

//initialisation du projet
static void init() {
  
  //création de la fenêtre principale
  s_main_window = window_create();
  
  //définition des constructeurs et destructeurs de la fenêtre principale
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
  });
  
  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  
  //construction de la fenêtre sur la pile
  window_stack_push(s_main_window, true);
  
  // Start the animation
  app_timer_register(DELTA, next_frame_handler, NULL);
  
}

//destructeur du projet
static void deinit() {
  
  //destruction de la fenêtre
  window_destroy(s_main_window);
  
}

//procédure principale
int main() {
  
  init();
  app_event_loop();
  deinit();
  
}