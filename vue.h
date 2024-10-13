
/*
  Author: Redha.ABDERRAHMANE  
  Creation date: 17-Apr-2024 16:14
  Last file update: 8-June-2024 16:41
*/
#include <stdio.h>
#include <stdlib.h>
#include <libsx.h>

#pragma once
extern Widget 
            ZoneSaisie,//Widget pour la zone de saisie
            ZoneTentative,//Widget pour la zone d'affichage pour le nombre de tentatives restantes
            ZoneTailleMot,//Widget pour la zone d'affichage pour la taille du mot
            ZoneMotPrec,//Widget pour la zone d'affichage pour le mot précédent
            DisplayArea,//Widget pour la zone de dessin
            BStart, // Widget pour le bouton "Start"
            BEnter; // Widget pour le bouton "Enter"
extern void init_display(int, char *[],void*);// Rôle :création et assemblage des widgets

