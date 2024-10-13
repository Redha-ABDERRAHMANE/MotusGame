
/*
  Author: Redha.ABDERRAHMANE  
  Creation date: 17-Apr-2024 16:14
  Last file update: 7-June-2024 18:03
*/

#include "data.h"
#include "vue.h"

int main(int argc, char *argv[]) { 

  Donnees d;                      // Déclaration d'une variable de type Donnees 
  

  if (OpenDisplay(argc, argv) == 0) {    // Vérification de l'ouverture de l'affichage graphique avec OpenDisplay
    fprintf(stderr,"Can't open display\n");  // Si l'ouverture échoue, affiche un message d'erreur
    return EXIT_FAILURE;                     // Retourne un code d'échec et termine le programme
  }
  // créer l'IG et l'afficher à l'écran
  init_display(argc, argv, &d);  // Initialise l'affichage graphique avec init_display (définie dans vue.h)
  MainLoop();                    // Entre dans la boucle principale de l'interface graphique
  return EXIT_SUCCESS;           // Retourne un code de succès et termine le programme
}

