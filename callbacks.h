/*
  Author: Redha.ABDERRAHMANE  
  Creation date: 17-Apr-2024 16:14
  Last file update: 8-June-2024 19:20
*/


#include <stdlib.h>
#include <stdio.h>
#include "data.h"
#include "vue.h"

#pragma once
#define TAILLEBOX 70  // Définition d'une constante pour la taille de la boîte




extern void quit(Widget, void *);// Rôle :terminer l'application
extern void redisplay(Widget , int , int , void *);// Rôle : Créer la zone de dessin sur l'interface graphique et afficher le message du début
extern void enter(Widget , void* );// Rôle : Démarrer le jeu et initialiser les composants de la structure partagée
extern void start(Widget , void *);// Rôle :gérer l'entrée de l'utilisateur et mettre à jour l'affichage
