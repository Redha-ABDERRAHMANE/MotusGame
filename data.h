

/*
  Author: Redha.ABDERRAHMANE  
  Creation date: 17-Apr-2024 16:14
  Last file update: 8-June-2024 19:20
*/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<assert.h>
#include<ctype.h>
#include<time.h>
#include<errno.h>

#pragma once



#define NB_WORDS 103949 //Nombre de lignes dans le dictionnaire

#define MAXLENGTH 11  // Longueur maximale de la chaine de caractères 
#define TENTATIVES 6 //Nombre de tentatives

typedef struct {
  int taille;           // Taille du mot original
  int tentative;       // Nombre de tentatives restant
  char* motPrec;       // Pointeur vers une chaîne de caractères représentant le mot précédent
  char* motFloute;     // Pointeur vers une chaîne de caractères représentant le mot flouté 
  char* motOriginal;   // Pointeur vers une chaîne de caractères représentant le mot original 
  char* motProp;       // Pointeur vers une chaîne de caractères représentant le mot proposé par l'utilisateur
} Donnees;





extern void initialise_Mots(Donnees *);// Rôle : Initialise les champs motOriginal, motFloute et alloue la mémoire pour motProp
extern void freeDonnees(Donnees *d);// Rôle : Liberer la mémoire des pointeurs créés dans initialise_Mots


extern void initialiseTentative(Donnees *);// Rôle : Initialise le nombre de tentatives
extern void SetmotPrec(Donnees *,char* );// Rôle : Initialise le mot précédent
extern void initialise_Taille(Donnees*);
extern void SetmotProp(Donnees*,char* s ); // Rôle : Modifie la proposition de mot
extern int ReturnTentative(Donnees *);// Rôle : Retourne le nombre de tentatives restantes

extern char* ReturnMotOriginal(Donnees *);// Rôle : Retourne le mot original

extern char* ReturnMotFloute(Donnees *);// Rôle : Retourne le mot flouté

extern char* ReturnMotProp(Donnees *);// Rôle : Retourne le mot proposé
extern char* ReturnMotPrec(Donnees *);// Rôle : Retourne le mot précédent

extern int ReturnTaille(Donnees *); // Rôle : Retourne la taille du mot original

extern void DecrementeTentative(Donnees *);// Rôle : Décrémente le nombre de tentatives




//procedures pour le debug 
////////////////////////////////////////////////////////////////////

extern void printMotOriginal(Donnees* );// Rôle : Affiche le mot original

extern void printMotFloute(Donnees *);// Rôle : Affiche le mot flouté


extern void printMotProp(Donnees *);// Rôle : Affiche le mot proposé

/////////////////////////////////////////////////////////////////


extern void verifierOccurence(Donnees* ,short*); // Rôle : Vérifie les occurrences des caractères dans le mot proposé et met à jour le mot flouté


extern int RecevoirMot(Donnees* ,char*);// Rôle : Reçoit le mot proposé par le joueur et vérifie sa validité


extern int gagnant(Donnees*);// Rôle :  Vérifie si le joueur a gagné
