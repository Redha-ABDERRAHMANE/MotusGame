
/*
  Author: Redha.ABDERRAHMANE / Fouad.BOULOUIZ   
  Creation date: 17-Apr-2024 16:14
  Last file update: 8-June-2024 23:20
*/


#include "callbacks.h"
       // Définition d'une constante pour la taille de la boîte

// Déclaration des widgets pour différentes zones de l'interface utilisateur
Widget ZoneSaisie, ZoneTentative, ZoneTailleMot,ZoneMotPrec, DisplayArea,BEnter,BStart;

/*
 * Rôle : terminer l'application

 * Antecedent : la fonction peut être appelée par un bouton ou autre événement pour quitter l'application
 * - Widget w : le widget qui a déclenché l'événement
 * - void *d :  la structure partagée 
 */
void quit(Widget w, void *d) {
    exit(EXIT_SUCCESS); // Terminer le programme avec un code de succès
}




/*
 * Le code suivant de Get_RGBColor   est une redefinition pour contourner l'erreur segmentation fault (core dumped) 
 * causé par le GetRGBColor de la bibliotèque libsx
 * Une couleur RGB est composée de 3 composantes R:rouge , G: vert , B: bleu
 * Chaque composante est codée sur 8 bits 
 * Pour représenter une couleur RGB on doit assurer que chaque composante est codée sur 8 bits donc maximum 255
 * Les 8 bits de poid fort de la couleur représente la composante rouge donc on doit faire un décalage à gauche de 16 bits
 * Les 8 bits du milieu de la couleur représente la composante verte donc on doit faire un décalage à gauche de 8 bits
 * Les 8 bits de poid faible de la couleur représente la composante bleue donc on ne doit faire aucun un décalage.
 * Rôle : Combiner les valeurs RGB en une seule valeur couleur.
 *
 * Antécédent : Les valeurs des composants rouges, verts et bleus (R, G, B) 
 * 
 * - int r : la composante rouge (doit être comprise entre 0 et 255)
 * - int g : la composante verte (doit être comprise entre 0 et 255)
 * - int b : la composante bleue (doit être comprise entre 0 et 255)
 */
static unsigned int Get_RGBColor(int r, int g, int b) {
    // Vérifier si la valeur de r est inférieure à 0
    if (r < 0) r = 0;  // Si oui, la régler à 0
    // Vérifier si la valeur de r est supérieure à 255
    if (r > 255) r = 255;  // Si oui, la régler à 255

    // Vérifier si la valeur de g est inférieure à 0
    if (g < 0) g = 0;  // Si oui, la régler à 0
    // Vérifier si la valeur de g est supérieure à 255
    if (g > 255) g = 255;  // Si oui, la régler à 255

    // Vérifier si la valeur de b est inférieure à 0
    if (b < 0) b = 0;  // Si oui, la régler à 0
    // Vérifier si la valeur de b est supérieure à 255
    if (b > 255) b = 255;  // Si oui, la régler à 255

    // Combiner les valeurs RGB en une seule valeur couleur
    unsigned int color = (r << 16) | (g << 8) | b;
    // 'r << 16' place la composante rouge sur les 8 bits de poids fort
    // 'g << 8' place la composante verte sur les 8 bits du milieu
    // 'b' place la composante bleue sur les 8 bits de poids faible
    
    // Retourner la valeur couleur combinée
    return color;
}






/*
 * Rôle : afficher le nombre de tentatives restantes

 * Antecedent : le widget et le nombre de tentatives 
 * - Widget w : le widget où afficher le message
 * - int nombre : le nombre de tentatives restantes
 */
static void afficherInfoTentatives(Widget w, int nombre) {
    char Phrase[50]; // Buffer pour stocker la chaîne formatée
    sprintf(Phrase, "Tentatives restantes : %d", nombre); // Formater le nombre de tentatives
    SetStringEntry(w, Phrase); // Mettre à jour le widget avec la chaîne formatée
}

/*
 * Rôle : afficher la taille du mot à trouver 

 * Antecedent : le widget et la taille du mot 
 * - Widget w : le widget où afficher le message
 * - int nombre : la taille du mot
 */
static void afficherInfoTaille(Widget w, int nombre) {
    char s[50]; // Buffer pour stocker la chaîne formatée
    sprintf(s, "Taille du mot : %d", nombre); // Formater la taille du mot
    SetStringEntry(w, s); // Mettre à jour le widget avec la chaîne formatée
}

/*
 * Rôle : afficher le  mot à trouver 

 * Antecedent : le widget et la structure partagée 
 * - Widget w : le widget où afficher le message
 * - void *d :  la structure partagée 
 */
static void afficherMotADeviner(Widget w, void* d) {
    char s[50]; // Buffer pour stocker la chaîne formatée
    sprintf(s, "Mot a deviner : %s", ReturnMotOriginal(d)); // Formater le mot à deviner
    SetStringEntry(w, s); // Mettre à jour le widget avec la chaîne formatée
}

/*
 * Rôle : afficher le  mot précédent 

 * Antecedent : le widget et la structure partagée 
 * - Widget w : le widget où afficher le message
 * - void *d :  la structure partagée 
 * - char* mot: la chaine de caractères du mot précédent
 */
static void afficherInfoMotPrec(Widget w,void* d, char* mot) {

    if(!strcmp(mot,ReturnMotFloute(d))){ SetStringEntry(w, "Mot precedent: INVALIDE"); }// Si le mot proposé par l'utilisateur est invalide dès la première tentative
    else{
        char s[50]; // Buffer pour stocker la chaîne formatée
        sprintf(s, "Mot precedent : %s", mot); // Formater le mot précédent
        SetStringEntry(w, s); // Mettre à jour le widget avec la chaîne formatée
    }


}




/*
 * Rôle : dessiner une case avec la couleur et la lettre appropriée

 * Antecedent : les paramètres de couleur, position, mot, et indice 
 * - Widget w : le widget sur lequel dessiner
 * - int couleur1 : composante rouge de la couleur
 * - int couleur2 : composante verte de la couleur
 * - int couleur3 : composante bleue de la couleur
 * - int xB : position x de la boîte
 * - int xT : position x du texte
 * - int y : position y de la boîte et du texte
 * - char* mot : le mot à afficher
 * - int i : indice de la lettre dans le mot
 * - int CercleCondition: booléen indiquant lorsqu'il faut dessiner un cerlce
 */
static void dessinerReponseCase(Widget w, int couleur1, int couleur2, int couleur3, int xB, int xT, int y, const char* mot, int i,int CercleCondition) {


    char text[2]; // Chaine de caractères pour stocker le caractère à dessiner
    text[0] = mot[i]; // Stocker le caractère dans l'indice 0 de la chaine de caractères
    text[1] = '\0';  // fermer la chaine de caractères

    int couleur=Get_RGBColor(couleur1, couleur2, couleur3);//Définir la couleur
    int white=Get_RGBColor(255,255,255);//Définir la couleur blanche
    int black=Get_RGBColor(0,0,0);//Définir la couleur noire
    int yellow=Get_RGBColor(255,255,0);//Définir la couleur noire
    SetColor(couleur); // Définir la couleur de remplissage

    DrawFilledBox(xB, y, TAILLEBOX, TAILLEBOX); // Dessiner une boîte remplie avec la couleur définie

    SetColor(black); // Définir la couleur noire pour le texte

    if(CercleCondition){

        SetColor(yellow);

        DrawFilledArc(xT-30,y,70,70,0,360);//Dessiner un cercle de rayon 35
        SetColor(black);
        SetBgColor(DisplayArea,yellow); // Définir la couleur de fond pour le texte
        DrawText(text, xT, y + 35); // Dessiner le texte à la position spécifiée
    } 
    else{
    SetColor(black);
    SetBgColor(DisplayArea,couleur); // Définir la couleur de fond pour le texte
    DrawText(text, xT, y + 35); // Dessiner le texte à la position spécifiée
    }
    SetBgColor(DisplayArea, white); // Réinitialiser la couleur de fond à blanc
}

/*
 * Rôle : dessiner une case vide avec les paramètres de couleur et de texte appropriés

 * Antecedent : les paramètres de couleur, position, mot, et indice 
 * - Widget w : le widget sur lequel dessiner
 * - int couleur1 : composante rouge de la couleur
 * - int xB : position x de la boîte
 * - int xT : position x du texte
 * - int y : position y de la boîte 
 * - char* mot : le mot à afficher
 * - int i : indice de la lettre dans le mot
 */
static void dessinerCaseVide(Widget w, int couleur1, int xB, int xT, int y, const char* mot, int i) {



    char text[2]; // Chaine de caractère pour stocker le caractère à dessiner
    SetColor(Get_RGBColor(0,0,0)); // Définir la couleur de la bordure
    DrawBox(xB, y, TAILLEBOX, TAILLEBOX); // Dessiner une boîte vide


    text[0] = mot[i]; // Stocker le caractère dans l'indice 0 de la chaine de caractères
    text[1] = '\0';  // fermer la chaine de caractères 

    DrawText(text, xT, y + 35); // Dessiner le texte à la position spécifiée
}

/*
 * Rôle : dessiner le mot flouté sur l'interface graphique

 * Antecedent : les paramètres de  position, mot, et indice 
 * - Widget w : le widget sur lequel dessiner
 * - int xB : position x de la boîte
 * - int xT : position x du texte
 * - int y : position y de la boîte 
 * - char* mot : le mot à afficher
 * - int i : indice de la lettre dans le mot
 * - void *data : les données de l'application

 */


static void dessinerCaseMotFloute(Widget w,int xB,int xT,int y,int i,void* data){

    if (i == 0) {dessinerReponseCase(w, 255, 0, 0, xB, xT, y, ReturnMotFloute(data), i,0);} // Dessiner la première lettre en rouge
    else {dessinerCaseVide(w, 0, xB, xT, y, ReturnMotFloute(data), i);} // Dessiner les cases vides pour les autres lettres

}


/*
 * Rôle : dessiner une case en fonction de la lettre dans le mot caché

 * Antecedent : les paramètres de position, mot, mot caché, et indice 
 * 
 * - Widget w : le widget sur lequel dessiner
 * - int xBox : position x de la boîte
 * - int xText : position x du texte
 * - int y : position y de la boîte 
 * - char* mot : le mot à afficher
 * - char* motCachee : le mot caché indiquant la couleur des cases
 * - int i : indice de la lettre dans le mot
 */
static void SwitchCaseLettre(Widget w, int xBox, int xText, int y, const char* mot, const char* motCachee, int i) {
    switch(motCachee[i]) {
    
        case 'x':
            dessinerReponseCase(w, 255, 0, 0, xBox, xText, y, mot, i,0); // Case rouge
            break;
        case 'O':
            dessinerReponseCase(w, 0, 0, 255, xBox, xText, y, mot, i,1); // Case jaune
            break;
        case '-':
            dessinerReponseCase(w, 0, 0, 255, xBox, xText, y, mot, i,0); // Case bleue
            break;
        default:
            dessinerReponseCase(w, 255, 0, 0, xBox, xText, y, mot, i,0); // Case rouge par défaut
            break;
    }
}

/*
 * Rôle : Créer la zone de dessin sur l'interface graphique et afficher le message du début

 * Antecedent : les paramètres de widget, largeur, hauteur et données 
 * - Widget w : le widget sur lequel redessiner
 * - int width : largeur de la zone de dessin
 * - int height : hauteur de la zone de dessin
 * - void *data : pointeur sur la structure partagée
 */
void redisplay(Widget w, int width, int height, void *data) {
    SyncDisplay();
    //Déclaration du message à afficher au début du jeu
    char text1[]="Bienvenue dans le jeu motus cree par Redha ABDERRAHMANE et Fouad BOULOUIZ:";
    char text2[]="          -Pour savoir les regles du jeu, veuillez appuyer sur le bouton help";
    char text3[]="          -Pour commencer la partie, veuillez appuyer sur le bouton start";
    //Dessiner le texte sur l'interface graphique dans la zone à dessin 
    DrawText(text1,50,50);
    DrawText(text2,50,50+18);
    DrawText(text3,50,50+35);
    //On bloque l'accés au bouton enter car le jeu n'a pas encore commencer
    SetWidgetState(BEnter, FALSE);  
    // Implémentation de la redéfinition de l'affichage
}

/*
 * Rôle : démarrer le jeu et initialiser les composants de la structure partagée

 * Antecedent : les paramètres de widget et de données 
 * - Widget w : le widget qui a déclenché l'événement
 * - void *data : pointeur sur la structure partagée
 */
void start(Widget w, void *data) {

    ClearDrawArea(); // Effacer la zone de dessin
    SetWidgetState(BEnter, TRUE);// Activer l'accès au bouton Enter car le jeu a commencé



    initialise_Mots(data); // Initialiser les mots
    initialise_Taille(data); // Initialiser la taille du mot
    initialiseTentative(data); // Initialiser le nombre de tentatives
    afficherInfoTentatives(ZoneTentative, ReturnTentative(data)); // Afficher le nombre de tentatives restantes
    afficherInfoTaille(ZoneTailleMot, ReturnTaille(data)); // Afficher la taille du mot
    afficherInfoMotPrec(ZoneMotPrec,data," ");// Initialiser l'affichage du mot précédent

    //printMotOriginal(data); // Afficher le mot original
    //printMotFloute(data); // Afficher le mot flouté

    int xBox = 0, xText = 30, y = 50; // Variables de position pour dessiner les cases
    int longueurMot = ReturnTaille(data); // Récupérer la longueur du mot
    SetColor(Get_RGBColor(0, 0, 0)); // Définir la couleur noire

    for (int i = 0; i < longueurMot; i++) { // Boucle pour dessiner chaque lettre du mot
        dessinerCaseMotFloute(w, xBox,xText,y,i,data);

        xText += TAILLEBOX + 10; // Mettre à jour la position du texte
        xBox += 80; // Mettre à jour la position de la boîte
    }
}


/*
 * Rôle : gérer l'entrée de l'utilisateur et mettre à jour l'affichage

 * Antecedent : les paramètres de widget et de données 
 * - Widget w : le widget qui a déclenché l'événement
 * - void *data : pointeur sur la structure partagée
 */
void enter(Widget w, void* data) {
    
    short indicesTab[8]; // Tableau pour stocker les indices de vérification des lettres

    //printf("\nmotOriginal  (%s)    motFloute  (%s)                    motProp  (%s)             motPrec     (%s)\n",ReturnMotOriginal(data),ReturnMotFloute(data),ReturnMotProp(data),ReturnMotPrec(data));

    int y = 50 + 90 * (7 - ReturnTentative(data)); // Calculer la position verticale
    int xBox = 0, xText = 30; // Variables de position pour dessiner les cases


    char* motCachee = ReturnMotFloute(data); // Récupérer le mot flouté


    if (RecevoirMot(data, GetStringEntry(ZoneSaisie))) { // Vérifier si le mot est valide
        verifierOccurence(data, indicesTab); // Vérifier les occurrences des lettres

        SetmotPrec(data, ReturnMotProp(data)); // Mettre à jour le mot précédent avec le mot proposé valide

        motCachee = ReturnMotFloute(data); // Récupérer le mot flouté

        for (int i = 0; i < ReturnTaille(data); i++) { // Boucle pour dessiner chaque lettre

            SwitchCaseLettre(w, xBox, xText, y, ReturnMotProp(data), motCachee, i); // Dessiner la case correspondante
            xBox += 80; // Mettre à jour la position de la boîte
            xText += TAILLEBOX + 10; // Mettre à jour la position du texte
        }
    } 
    else {
        afficherInfoMotPrec(ZoneMotPrec,data,ReturnMotPrec(data));// Mettre à jour le mot précédent


        if(!strcmp(ReturnMotPrec(data),motCachee)){

            for (int i = 0; i < ReturnTaille(data); i++) { // Boucle pour dessiner chaque lettre du mot

                dessinerCaseMotFloute(w, xBox,xText,y,i,data);  

                xText += TAILLEBOX + 10; // Mettre à jour la position du texte
                xBox += 80; // Mettre à jour la position de la boîte

            }

        }
        else{
            for (int i = 0; i < ReturnTaille(data); i++) { // Boucle pour dessiner chaque lettre
                SwitchCaseLettre(w, xBox, xText, y, ReturnMotPrec(data), motCachee, i); // Dessiner la case correspondante
                xBox += 80; // Mettre à jour la position de la boîte
                xText += TAILLEBOX + 10; // Mettre à jour la position du texte
            }

        }
    }

    if ((ReturnTentative(data) == 0) || gagnant(data)) { // Vérifier si le jeu est terminé
        afficherMotADeviner(ZoneSaisie, data);// Afficher le mot à  deviner dans la zone de saisie à la fin de la partie
        freeDonnees(data); // Libérer les données
        if (GetYesNo("Voulez-vous recommencer la partie ?")) { // Demander si l'utilisateur veut recommencer
            ClearDrawArea(); // Effacer la zone de dessin
            start(w, data); // Recommencer la partie
        } else {
            CloseWindow(); // Fermer la fenêtre
            exit(EXIT_SUCCESS); // Terminer le programme avec un code de succès
        }
        ShowDisplay(); // Afficher la fenêtre
    }
    afficherInfoTentatives(ZoneTentative, ReturnTentative(data)); // Mettre à jour le nombre de tentatives restantes
    

    

    SetStringEntry(ZoneSaisie,"");// Effacer l'ancienne saisie de l'utilisateur dans la zone de saisie
    
}
