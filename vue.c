
/*
  Author: Redha.ABDERRAHMANE  
  Creation date: 17-Apr-2024 16:14
  Last file update: 7-July-2024 13:30
*/



#include "data.h"
#include "callbacks.h"
#include "vue.h"

#define TAILLEZONEAFFICHAGE 255 // Définition d'une constante pour la taille de la zone d'affichage
#define WIDTH 800 //Variable globale pour définir la largeur de la zone de dessin
#define HEIGHT 680//Variable globale pour définir la hauteur de la zone de dessin



/*
 * Rôle : afficher l'aide et les règles du jeu

 * Antecedent : les paramètres de widget et de données 

 * - Widget w : le widget qui a déclenché l'événement
 * - void *data : pointeur sur la structure partagée
 */
void help(Widget w, void* data) {
    MakeWindow("Help", NULL, 1); // Créer une nouvelle fenêtre d'aide   

    // Créer les widgets de texte pour les règles du jeu
    Widget text1 = MakeLabel("Regles du jeu:");
    Widget text2 = MakeLabel("Motus est un jeu de lettres ou les joueurs doivent deviner des mots entre 8");
    Widget text3 = MakeLabel("et 10 lettres en un maximum de six tentatives. Chaque tentative consiste en une");
    Widget text4 = MakeLabel("proposition de mot, et pour chaque lettre correctement placee, un carre");
    Widget text5 = MakeLabel("rouge est attribuee, tandis qu'un carre  jaune indique une lettre correcte");
    Widget text6 = MakeLabel("mais mal placee. Si une lettre n'apparait pas du tout dans le mot a deviner");
    Widget text7 = MakeLabel("un carre bleu est attribue.");

    // Créer les widgets de texte pour l'utilisation de l'application
    Widget text11 = MakeLabel("\n\nUtilisation de l'application :");
    Widget text12 = MakeLabel("- Le bouton 'quit' vous permet de quitter l'application.");
    Widget text13 = MakeLabel("- Le bouton 'start' permet de demarrer la partie.");
    Widget text14 = MakeLabel("- Le bouton 'enter' permet de valider votre tentative dans la zone de saisie.");

    // Disposer les widgets
    SetWidgetPos(text2, PLACE_UNDER, text1, NO_CARE, NULL);
    SetWidgetPos(text3, PLACE_UNDER, text2, NO_CARE, NULL);
    SetWidgetPos(text4, PLACE_UNDER, text3, NO_CARE, NULL);
    SetWidgetPos(text5, PLACE_UNDER, text4, NO_CARE, NULL);
    SetWidgetPos(text6, PLACE_UNDER, text5, NO_CARE, NULL);
    SetWidgetPos(text7, PLACE_UNDER, text6, NO_CARE, NULL);
    SetWidgetPos(text11, PLACE_UNDER, text7, NO_CARE, NULL);
    SetWidgetPos(text12, PLACE_UNDER, text11, NO_CARE, NULL);
    SetWidgetPos(text13, PLACE_UNDER, text12, NO_CARE, NULL);
    SetWidgetPos(text14, PLACE_UNDER, text13, NO_CARE, NULL);

    GetStandardColors(); // Récupérer les couleurs standard
    ShowDisplay(); // Afficher la fenêtre d'aide
}




/*
 * Rôle: création et assemblage des widgets
 * Antecedent :
 * - int argc: Nombre d'arguments de la ligne de commande
 * - char* argv[] Tableau des arguments de la ligne de commande
 * - void *data : pointeur sur la structure partagée
 *
 */
void init_display(int argc, char *argv[], void* data) // Déclaration de la fonction init_display avec les paramètres argc, argv et data
{
    Widget // Déclaration de widgets pour les composants de l'interface utilisateur
        
        BQuit, // Widget pour le bouton "Quit"
        Label, // Widget pour le label
        LabelSpace, // Widget pour le labelSpace qui permet d'espacer entre les widgets
        BHelp; // Widget pour le bouton "Help"

    // créer les composants graphiques
    BStart = MakeButton("Start", start, data); // Création du bouton "Start" avec le callback start
    BQuit = MakeButton("Quit", quit, data); // Création du bouton "Quit" avec le callback quit
    BEnter = MakeButton("Enter", enter, data); // Création du bouton "Enter" avec le callback enter
    BHelp = MakeButton("Help", help, data); // Création du bouton "Help" avec le callback help
    
    Label = MakeLabel("Veuillez saisir un mot: "); // Création du label
    LabelSpace= MakeLabel("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");// Création du label d'espacement vertical 
    DisplayArea = MakeDrawArea(WIDTH, HEIGHT, redisplay, data); // Création de la zone de dessin avec les dimensions spécifiées
    ZoneSaisie = MakeStringEntry(NULL, TAILLEZONEAFFICHAGE, NULL, NULL); // Création de la zone de saisie avec une taille définie
    ZoneTailleMot = MakeStringEntry("La taille du mot a trouver: ", TAILLEZONEAFFICHAGE, NULL, NULL); // Création de la zone d'affichage pour la taille du mot
    ZoneTentative = MakeStringEntry("Nombre de tentatives restant: ", TAILLEZONEAFFICHAGE, NULL, NULL); // Création de la zone d'affichage pour le nombre de tentatives restantes
    ZoneMotPrec = MakeStringEntry("Mot precedent: ", TAILLEZONEAFFICHAGE, NULL, NULL); // Création de la zone d'affichage pour le nombre de tentatives restantes
    // assemblage des widgets
    XFont police = GetFont("8x16"); // Récupération de la police
    SetWidgetFont(DisplayArea, police); // Définition de la police pour la zone de dessin

    SetWidgetPos(DisplayArea,NO_CARE,NULL,NO_CARE,NULL); // Positionnement de la zone de dessin 

    SetWidgetPos(LabelSpace, PLACE_RIGHT, DisplayArea, NO_CARE, NULL); // Positionnement du label qui permet l'espacement vertical
    SetWidgetPos(ZoneTentative, PLACE_UNDER, LabelSpace, PLACE_RIGHT, DisplayArea); // Positionnement de la zone de tentative en dessous du label d'espacement
    SetWidgetPos(ZoneTailleMot, PLACE_UNDER, ZoneTentative, PLACE_RIGHT, DisplayArea); // Positionnement de la zone de taille du mot en dessous de la zone de tentative
    SetWidgetPos(ZoneMotPrec, PLACE_UNDER, ZoneTailleMot, PLACE_RIGHT, DisplayArea); // Positionnement de la zone du mot précédent en dessous de la zone de taille mot
    
    
    SetWidgetPos(BQuit, PLACE_UNDER, DisplayArea, NO_CARE, NULL); // Positionnement du bouton "Quit" sous la zone de dessin
    SetWidgetPos(BStart, PLACE_UNDER, DisplayArea, PLACE_RIGHT, BQuit); // Positionnement du bouton "Start" à droite du bouton "Quit" sous la zone de dessin
    SetWidgetPos(Label, PLACE_UNDER, DisplayArea, PLACE_RIGHT, BStart); // Positionnement du label à droite du bouton "Start" sous la zone de dessin

    SetWidgetPos(ZoneSaisie, PLACE_UNDER, DisplayArea, PLACE_RIGHT, Label); // Positionnement de la zone de saisie à droite du label sous la zone de dessin
    SetWidgetPos(BEnter, PLACE_UNDER, DisplayArea, PLACE_RIGHT, ZoneSaisie); // Positionnement du bouton "Enter" à droite de la zone de saisie sous la zone de dessin
    SetWidgetPos(BHelp, PLACE_UNDER, DisplayArea, PLACE_RIGHT, BEnter); // Positionnement du bouton "Help" à droite du bouton "Enter" sous la zone de dessin

    // pour gérer les couleurs
    GetStandardColors(); // Récupération des couleurs standard

    // pour afficher l'interface 
    ShowDisplay(); // Affichage de l'interface
}


