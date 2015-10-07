#include <pebble.h>
#include "tools.h"
  
//procédure de récupération de la dizaine d'heure
int getCurrentHourDoz() {
  
  //initialisation de l'heure
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);
  static char buffer[] = "00";
  
  strftime(buffer, sizeof("00"), "%H", tick_time);
  
  //retour de l'heure / 10 pour avoir les dizaines
  return (atoi(buffer) / 10 );
  
}

//procédure de récupération de la unités d'heure
int getCurrentHourUnit() {
  
  //initialisation de l'heure
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);
  static char buffer[] = "00";
  
  strftime(buffer, sizeof("00"), "%H", tick_time);
  
  //retour de l'heure % 10 pour avoir les unités
  return (atoi(buffer) % 10 );
  
}

//procédure de récupération de la dizaines de minutes
int getCurrentMinDoz() {
  
  //initialisation de l'heure
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);
  static char buffer[] = "00";
  
  strftime(buffer, sizeof("00"), "%M", tick_time);
  
  //retour de l'heure / 10 pour avoir les dizaines
  return (atoi(buffer) / 10 );
  
}

//procédure de récupération de la unités de minutes
int getCurrentMinUnit() {
  
  //initialisation de l'heure
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);
  static char buffer[] = "00";
  
  strftime(buffer, sizeof("00"), "%M", tick_time);
  
  //retour de l'heure % 10 pour avoir les unités
  return (atoi(buffer) % 10 );
  
}