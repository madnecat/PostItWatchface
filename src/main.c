#include <pebble.h>
#include "minUnitManag.h"
#include "minDozManag.h"
#include "hourUnitManag.h"
#include "hourDozManag.h"
  
// -------------------------------------------
// --------- Déclarations --------------------
// -------------------------------------------
  
  
//fenêtre principale
static Window *s_main_window;

//mémoires de minutes, heures
static int cur_min_unit = 0,
  cur_min_doz = 0, 
  cur_hour_unit = 0, 
  cur_hour_doz = 0;



// -------------------------------------------
// ----------- Procédures --------------------
// -------------------------------------------



//hook appelé lors du changement de temps
static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  
  // Start the animation
//  app_timer_register(DELTA, next_frame_handler, NULL);
  
}

//chargement de la fenêtre principale
static void main_window_load(Window *window) {
  
  //layer de la fenêtre principale
  Layer *window_layer = window_get_root_layer(window);
  
  //coordonnées de la fenêtre principale
  GRect bounds = layer_get_bounds(window_layer);
  
  //initialisation des variables graphiques
  
  //partie dizaine d'heures
  hour_doz_layer = layer_create(GRect(0, 0, bounds.size.w / 2, bounds.size.h / 2));
  hour_doz_sequence = gdraw_command_sequence_create_with_resource(RESOURCE_ID_FRAMES_0_2);
  layer_set_update_proc(hour_doz_layer, hour_doz_update_proc);
  layer_add_child(window_layer, hour_doz_layer);
  
  //partie unité d'heures
  hour_unit_layer = layer_create(GRect(0, 0, bounds.size.w / 2, bounds.size.h / 2));
  hour_unit_sequence = gdraw_command_sequence_create_with_resource(RESOURCE_ID_FRAMES_0_9);
  layer_set_update_proc(hour_unit_layer, hour_unit_update_proc);
  layer_add_child(window_layer, hour_unit_layer);
  
  //partie dizaine de minutes
  min_doz_layer = layer_create(GRect(0, 0, bounds.size.w / 2, bounds.size.h / 2));
  min_doz_sequence = gdraw_command_sequence_create_with_resource(RESOURCE_ID_FRAMES_0_6);
  layer_set_update_proc(min_doz_layer, min_doz_update_proc);
  layer_add_child(window_layer, min_doz_layer);
  
  //partie unité de minutes
  min_unit_layer = layer_create(GRect(0, 0, bounds.size.w / 2, bounds.size.h / 2));
  min_unit_sequence = gdraw_command_sequence_create_with_resource(RESOURCE_ID_FRAMES_0_9);
  layer_set_update_proc(min_unit_layer, min_unit_update_proc);
  layer_add_child(window_layer, min_unit_layer);
  
  // Start the animation
  app_timer_register(DELTA, min_unit_next_frame_handler, NULL);
  app_timer_register(DELTA, min_doz_next_frame_handler, NULL);
  app_timer_register(DELTA, hour_unit_next_frame_handler, NULL);
  app_timer_register(DELTA, hour_doz_next_frame_handler, NULL);
}

//destruction des objets dynamiques
static void main_window_unload(Window *window) {
  
  //désallocation des layers
  layer_destroy(min_unit_layer);
  layer_destroy(min_doz_layer);
  layer_destroy(hour_unit_layer);
  layer_destroy(hour_doz_layer);
  
  //désallocation des séquences
  gdraw_command_sequence_destroy(min_unit_sequence);
  gdraw_command_sequence_destroy(min_doz_sequence);
  gdraw_command_sequence_destroy(hour_unit_sequence);
  gdraw_command_sequence_destroy(hour_doz_sequence);
  
  
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