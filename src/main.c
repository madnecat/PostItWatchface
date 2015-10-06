#include <pebble.h>

//fenêtre principale
static Window *s_main_window;

//chargement de la fenêtre principale
static void main_window_load(Window *window) {
  
  //layer de la fenêtre principale
  Layer *window_layer = window_get_root_layer(window);
  
  //coordonnées de la fenêtre principale
  GRect bounds = layer_get_bounds(window_layer);

}

//destruction des objets dynamiques
static void main_window_unload(Window *window) {

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
  
  //construction de la fenêtre sur la pile
  window_stack_push(s_main_window, true);
}

//destructeur du projet
static void deinit() {
  window_destroy(s_main_window);
}

//proicédure principale
int main() {
  init();
  app_event_loop();
  deinit();
}