

/*
  Author: Redha.ABDERRAHMANE / Fouad.BOULOUIZ   
  Creation date: 17-Apr-2024 16:14
  Last file update: 7-June-2024 23:30
*/



#include "data.h"

// Rôle : Trouve un mot à partir d'un fichier en fonction de la ligne donnée
// Paramètres:
//   - ligne: Numéro de la ligne du fichier où se trouve le mot
//   - mot: Chaine de caractères où le mot sera stocké
static void trouverMot(int ligne, char* mot) {
    FILE *fichier; // Déclaration d'un pointeur de type FILE
    if ((fichier = fopen("DicoMotus.txt", "r")) == NULL) { // Ouvrir le fichier en mode lecture et vérifier si l'ouverture a réussi
        perror("DicoMotus.txt"); // Afficher un message d'erreur si l'ouverture a échoué
        exit(errno); // Quitter le programme avec le code d'erreur
    }
    int cpt = 1; // Initialiser le compteur de lignes à 1
    while ((fscanf(fichier, "%s", mot) > 0)) { // Lire les mots du fichier ligne par ligne
        // Invariant de boucle : Avant chaque itération, 'cpt' représente le nombre de lignes lues et
        // nous n'avons pas encore trouvé la ligne souhaitée, sauf si 'cpt' est égal à 'ligne'.
        
        if (cpt == ligne) { // Si on atteint la ligne souhaitée
            fclose(fichier); // Fermer le fichier
            // Invariant de boucle (après fermeture) : Nous avons trouvé la ligne souhaitée, donc la boucle se termine.
        } else {
            if (cpt != ligne) { // Si ce n'est pas la ligne souhaitée
                cpt++; // Incrémenter le compteur de lignes
            }
            // Invariant de boucle (suite) : 'cpt' a été incrémenté et représente le nombre de lignes lues jusqu'à la position actuelle.
        }
    }
    if(!(cpt==ligne)){fclose(fichier);} // Fermer le fichier
    
}


// Rôle : Remplace les caractères d'une chaîne par des '_', sauf le premier caractère
// Paramètre:
//   - mot: Chaine de caractères à flouter
static void flouter(char* mot) {
    char* motFlouter = mot + 1; // Définir un pointeur qui pointe sur le deuxième caractère de la chaîne
    while (*motFlouter != '\0') { // Parcourir la chaîne jusqu'à la fin
        *motFlouter = '_'; // Remplacer chaque caractère par '_'
        motFlouter++; // Passer au caractère suivant
    }
}





// Rôle : Initialise les champs motOriginal, motFloute et alloue la mémoire pour motProp
// Paramètres:
//   - d: Pointeur vers la structure Donnees

void initialise_Mots(Donnees *d) {
    srand(time(NULL));
    d->motOriginal = malloc(sizeof(char) * MAXLENGTH); // Allocation de mémoire pour le mot original
    d->motFloute = malloc(sizeof(char) * MAXLENGTH); // Allocation de mémoire pour le mot flouté
    d->motPrec = malloc(sizeof(char) * MAXLENGTH); // Allocation de mémoire pour les anciennes saisies de l'utilisateur
    d->motProp= malloc(sizeof(char) * MAXLENGTH);// Allocation de mémoire pour le mot proposé par l'utilisateur
    d->motProp="";

    
    trouverMot((rand()%NB_WORDS)+1,d->motOriginal); //Trouve le  mot à une ligne calculée aléatoirement  dans un fichier dictionnaire

    strcpy(d->motFloute,d->motOriginal);// Copier le mot original 
    flouter(d->motFloute);// Flouter le mot original copié

    strcpy(d->motPrec,d->motFloute);// Copier le mot flouté comme et le définir comme mot précédent
}

// Rôle :Liberer la mémoire des pointeurs créés dans initialise_Mots
// Paramètres:
//   - d: Pointeur vers la structure Donnees

void freeDonnees(Donnees *d){
    free(d->motOriginal); // Liberer la mémoire du mot original
    free(d->motFloute); // Liberer la mémoire du mot flouté
    free(d->motPrec); // Liberer la mémoire du mot précédent
}

// Rôle : Calcule la longueur d'une chaîne de caractères
// Paramètre:
//   - mot: Chaine de caractères dont on veut calculer la longueur
// Retourne: La longueur de la chaîne de caractères
static int longueur(char* mot) {
    int i = 0; // Initialiser le compteur à 0
    while (mot[i] != '\0') { // Parcourir la chaîne jusqu'à la fin
        i++; // Incrémenter le compteur
    }
    return i; // Retourner la longueur de la chaîne
}



// Rôle : Initialise le nombre de tentatives
// Paramètre:
//   - d: Pointeur vers la structure Donnees
void initialiseTentative(Donnees *d) {
    d->tentative = TENTATIVES; // Définir le nombre de tentatives à 6
}
// Rôle : Initialise le mot précédent 
// Paramètre:
//   - d: Pointeur vers la structure Donnees
//   - mot: Chaine de caractères contenant le mot proposé par l'utilisateur
void SetmotPrec(Donnees *d,char* mot) {
    strcpy(d->motPrec,mot);
}

// Rôle : Initialise la taille du mot
// Paramètres:
//   - d: Pointeur vers la structure Donnees
void initialise_Taille(Donnees *d) {
    d->taille = longueur(d->motOriginal); // Initialiser la taille du mot
}


// Rôle : Retourne le nombre de tentatives restantes
// Paramètre:
//   - d: Pointeur vers la structure Donnees
// Retourne: Le nombre de tentatives restantes
int ReturnTentative(Donnees *d) {
    return d->tentative;
}

// Rôle : Retourne le mot original
// Paramètre:
//   - d: Pointeur vers la structure Donnees
// Retourne: Le mot original
char* ReturnMotOriginal(Donnees *d) {
    return d->motOriginal;
}




// Rôle : Retourne le mot flouté
// Paramètre:
//   - d: Pointeur vers la structure Donnees
// Retourne: Le pointeur du  mot flouté du type char*
char* ReturnMotFloute(Donnees *d) {
    return d->motFloute;
}

// Rôle : Retourne le mot proposé
// Paramètre:
//   - d: Pointeur vers la structure Donnees
// Retourne: Le pointeur du mot proposé du type char*
char* ReturnMotProp(Donnees *d) {
    return d->motProp;
}

// Rôle : Retourne le mot précédent
// Paramètre:
//   - d: Pointeur vers la structure Donnees
// Retourne: Le pointeur dumot précédent du type char*
char* ReturnMotPrec(Donnees *d) {
    return d->motPrec;
}

// Rôle : Retourne la taille du mot original
// Paramètre:
//   - d: Pointeur vers la structure Donnees
// Retourne: La taille du mot de type entier
int ReturnTaille(Donnees *d) {
    return d->taille;
}

// Rôle : Décrémente le nombre de tentatives
// Paramètre:
//   - d: Pointeur vers la structure Donnees
void DecrementeTentative(Donnees *d) {
    d->tentative--; // Décrémenter le nombre de tentatives
}

// Rôle : Modifie la proposition de mot
// Paramètre:
//   - d: Pointeur vers la structure Donnees
//   - mot: Chaine de caractères contenant le mot proposé
void SetmotProp(Donnees *d, char* mot) {
    d->motProp = mot; // Définir le mot proposé
}





// Rôle : Remplace un caractère dans motFloute par 'x', 'O' ou '-'
// Paramètres:
//   - d: Pointeur vers la structure Donnees
//   - i: indice du caractère à remplacer
//   - c: Caractère de remplacement ('x', 'O' ou '-')
static void remplacer(Donnees* d, int i, const char c) {
    char* motFloute = d->motFloute; // Définir un pointeur vers motFloute
    *(motFloute + i) = c; // Remplacer le caractère à l'indice i par c
}



// Rôle : Retourne une liste d'indices où un caractère est présent dans d->motOriginal
// Paramètres:
//   - d: Pointeur vers la structure Donnees
//   - j: Indice du caractère dans motProp
//   - indicesTab: Tableau d'indices où le caractère est présent
// Retourne: Tableau d'indices mis à jour de type short // Pointeur sur le premier élement du tableau short*
static short* occurence(Donnees *d, int j, short* indicesTab) {
    char* motOriginal = d->motOriginal; // Définir un pointeur vers motOriginal
    short indice = 0; // Initialiser l'indice à 0
    char c = d->motProp[j]; // Définir le caractère à rechercher
    int cpt = 0; // Initialiser le compteur à 0
    for (int i = 0; i < 7; i++) {
        indicesTab[i] = -1; // Initialiser le tableau d'indices à -1
    }
    while (*motOriginal != '\0') { // Parcourir motOriginal jusqu'à la fin
        // Invariant de boucle : Avant chaque itération, les indices des occurrences du caractère 'c'
        // dans 'motOriginal' jusqu'à la position actuelle ont été correctement enregistrés dans 'indicesTab'.

        if (*motOriginal == c) { // Si le caractère est trouvé
            indicesTab[cpt++] = indice; // Enregistrer l'indice
        }
        indice++; // Incrémenter l'indice
        motOriginal++; // Passer au caractère suivant

        // Invariant de boucle (suite) : Après chaque itération, les indices des occurrences du caractère 'c'
        // dans 'motOriginal' jusqu'à la position actuelle ont été correctement enregistrés dans 'indicesTab'.
    }
    return indicesTab; // Retourner le tableau d'indices
}



// Rôle : Affiche le mot original
// Paramètre:
//   - d: Pointeur vers la structure Donnees
void printMotOriginal(Donnees* d) {
    printf("\nLe mot Original :  (%s) de taille :%i\n", ReturnMotOriginal(d), d->taille);
}

// Rôle : Affiche le mot flouté
// Paramètre:
//   - d: Pointeur vers la structure Donnees
void printMotFloute(Donnees *d) {
    printf("\nLe mot Floute :  (%s) de taille :%i\n", d->motFloute, d->taille);
}

// Rôle : Affiche le mot proposé
// Paramètre:
//   - d: Pointeur vers la structure Donnees
void printMotProp(Donnees *d) {
    printf("\nLe mot proposee:  (%s) de taille :%i\n", d->motProp, longueur(d->motProp));
}

// Rôle : Vérifie si le mot proposé est présent dans le dictionnaire
// Paramètre:
//   - d: Pointeur vers la structure Donnees
// Retourne: 1 si le mot est dans le dictionnaire, sinon 0
static int verifierDico(Donnees *d) {
    if (longueur(d->motProp) >= MAXLENGTH){return 0;} // Vérifier si la longueur du mot proposé est valide
    char*  mot = malloc(sizeof(char) * MAXLENGTH); // Allouer la mémoire pour un mot

    FILE *fichier; // Déclaration d'un pointeur de type FILE
    if ((fichier = fopen("DicoMotus.txt", "r")) == NULL) { // Ouvrir le fichier en mode lecture et vérifier si l'ouverture a réussi
        perror("DicoMotus.txt"); // Afficher un message d'erreur si l'ouverture a échoué
        exit(errno); // Quitter le programme avec le code d'erreur
    }
    while (fscanf(fichier, "%s", mot) > 0) { // Lire les mots du fichier ligne par ligne
        // Invariant de boucle : À chaque itération, 'mot' contient le prochain mot du fichier
        // et tous les mots précédemment lus n'ont pas satisfait les conditions de correspondance.

        if (mot[strlen(mot) - 1] == '\n') { // Si le dernier caractère est un saut de ligne
            mot[strlen(mot) - 1] = '\0'; // Le remplacer par un caractère de fin de chaîne
        }

        if (mot[0] != '\n' && strlen(mot) == strlen(d->motProp) && mot[0] == d->motProp[0] && mot[strlen(mot) - 1] == d->motProp[strlen(mot) - 1]) {
            // Si le mot a la même longueur que le mot proposé et commence et finit par les mêmes lettres
            if (strcmp(d->motProp, mot) == 0) { // Si les mots sont identiques
                fclose(fichier); // Fermer le fichier
                free(mot); // Libérer la mémoire
                return 1; // Retourner 1 (mot trouvé)
            }
        }
        // Invariant de boucle (suite) : Après chaque itération, 'mot' a été vérifié et n'est pas identique à 'd->motProp',
        // et tous les mots précédemment lus n'ont pas satisfait les conditions de correspondance.
    }

    fclose(fichier); // Fermer le fichier
    free(mot); // Libérer la mémoire
    return 0; // Retourner 0 (mot non trouvé)
}

// Rôle : Vérifie les occurrences des caractères dans le mot proposé et met à jour le mot flouté
// Paramètres:
//   - d: Pointeur vers la structure Donnees
//   - indicesTab: Tableau d'indices où les caractères sont présents
void verifierOccurence(Donnees *d, short* indicesTab) {
    //printMotProp(d); // Afficher le mot proposé
    for (int i = 0; i < d->taille; i++) { // Parcourir chaque caractère du mot proposé
        if (d->motOriginal[i] == d->motProp[i]) { // Si le caractère correspond à celui du mot original
            remplacer(d, i, 'x'); // Remplacer par 'x' dans le mot flouté
        } else {
            short* array = occurence(d, i, indicesTab); // Trouver les occurrences du caractère
            if (array[0] != -1) { // Si des occurrences existent
                for (int j = 0; j < 7; j++) { // Parcourir le tableau d'indices
                    if (array[j] != -1) { // Si l'indice est valide
                        remplacer(d, i, 'O'); // Remplacer par 'O' dans le mot flouté
                    }
                }
            } else {
                remplacer(d, i, '-'); // Remplacer par '-' si aucune occurrence n'est trouvée
            }
        }
    }
    //printMotFloute(d); // Afficher le mot flouté mis à jour

}

// Rôle : Reçoit le mot proposé par le joueur et vérifie sa validité
// Paramètres:
//   - d: Pointeur vers la structure Donnees
//   - mot: Chaine de caractères contenant le mot proposé
// Retourne: 1 si le mot est valide, sinon 0
int RecevoirMot(Donnees *d, char* mot) {
    //printMotOriginal(d); // Afficher le mot original
    //printf("\n tentative :%d\n", d->tentative); // Afficher le nombre de tentatives restantes

    SetmotProp(d, mot); // Définir le mot proposé

    DecrementeTentative(d); // Décrémenter le nombre de tentatives
    //printMotProp(d); // Afficher le mot proposé
    if ((strlen(d->motProp) != d->taille) || !(verifierDico(d))) { // Si la longueur du mot proposé est incorrecte ou si le mot n'est pas dans le dictionnaire

        //printf("\nDonnez un mot correct avec la taille exacte du mot à deviner\n"); // Message d'erreur
        //printf("\nTentative %i", d->tentative); // Afficher le nombre de tentatives restantes

        
        return 0; // Retourner 0 (mot incorrect)
    }

    return 1; // Retourner 1 (mot correct)
}

// Rôle :  Vérifie si le joueur a gagné
// Paramètre:
//   - d: Pointeur vers la structure Donnees
// Retourne: 1 si le joueur a gagné, sinon 0
int gagnant(Donnees *d) {
    int cpt = 0; // Initialiser le compteur à 0
    for (int i = 0; i < d->taille; i++) { // Parcourir le mot flouté
        if (d->motFloute[i] == 'x') cpt++; // Incrémenter le compteur pour chaque 'x'
    }
    return cpt == d->taille; // Retourner 1 si tous les caractères sont 'x', sinon 0
}

