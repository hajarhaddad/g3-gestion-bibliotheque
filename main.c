#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"

int main() {
    Livre livres[200];
    int nbLivres = 0;
    int choix, add;
    char nom[20];

    // Demander le nom de l'utilisateur
    do {
        printf("Entrez votre nom : ");
        scanf("%s", nom);
    } while (strlen(nom) == 0);

    // Demander si l'utilisateur est admin (0) ou client (1)
    do {
        printf("Vous étes admin : 0 ou client : 1 : ");
        scanf("%d", &add);
    } while (add != 0 && add != 1);

    // Boucle infinie pour le menu
    while (1) {
        if (add == 0) {  // Si l'utilisateur est un admin
            afficherMenuadmin();  // Afficher le menu admin
            scanf("%d", &choix);  // Lire le choix de l'admin
        }
        else if (add == 1) {  // Si l'utilisateur est un client
            afficherMenuclient();  // Afficher le menu client
            scanf("%d", &choix);  // Lire le choix du client
        }

        // Exécution des choix en fonction de l'entrée
        switch (choix) {
            case 1:  // Ajouter un livre
                if (add == 0) {
                    Livre nouveauLivre;
                    // Demander les informations du livre é ajouter
                    printf("Entrez l'ID du livre : ");
                    scanf("%d", &nouveauLivre.id);  // L'ID est un nombre entier

                    // Utilisation de fgets pour lire des chaénes avec des espaces
                    printf("Entrez le titre du livre : ");
                    fgetc(stdin);  // Cette ligne permet de vider le buffer de l'input
                    fgets(nouveauLivre.titre, sizeof(nouveauLivre.titre), stdin);


                    printf("Entrez l'auteur du livre : ");
                    fgets(nouveauLivre.auteur, sizeof(nouveauLivre.auteur), stdin);

                    printf("Entrez la description du livre : ");
                    fgets(nouveauLivre.description, sizeof(nouveauLivre.description), stdin);

                    printf("Entrez l'utilisateur : ");
                    fgets(nouveauLivre.utilisateur, sizeof(nouveauLivre.utilisateur), stdin);

                    printf("Entrez categorie : ");
                    fgets(nouveauLivre.categorie, sizeof(nouveauLivre.categorie), stdin);

                    printf("Entrez le prix du livre : ");
                    scanf("%f", &nouveauLivre.prix);

                    printf("Entrez la disponibilité du livre (1 pour disponible, 0 pour non disponible) : ");
                    scanf("%d", &nouveauLivre.dispo);  // La disponibilité est un nombre entier

                    ajouter(nouveauLivre);  // Appel é la fonction d'ajout
                } else {
                    printf("Action non autorisée pour un client.\n");
                }
                break;
            case 2:  // Modifier un livre
                if (add == 0) {
                    Livre livreModifie;
                    // Demander l'ID du livre é modifier
                    printf("Entrez l'ID du livre é modifier : ");
                    scanf("%d", &livreModifie.id);  // L'ID est un nombre entier

                    // Demander les autres informations é modifier
                    printf("Entrez le nouveau titre du livre : ");
                    fgetc(stdin);  // Cette ligne permet de vider le buffer de l'input
                    fgets(livreModifie.titre, sizeof(livreModifie.titre), stdin);

                    printf("Entrez le nouvel auteur du livre : ");
                    fgets(livreModifie.auteur, sizeof(livreModifie.auteur), stdin);

                    printf("Entrez la nouvelle description du livre : ");
                    fgets(livreModifie.description, sizeof(livreModifie.description), stdin);

                    printf("Entrez le nouvel utilisateur : ");
                    fgets(livreModifie.utilisateur, sizeof(livreModifie.utilisateur), stdin);
                    livreModifie.utilisateur[strcspn(livreModifie.utilisateur, "\n")] = 0;

                    printf("Entrez le nouvel categorie : ");
                    fgets(livreModifie.categorie, sizeof(livreModifie.categorie), stdin);

                    printf("Entrez le nouveau prix du livre : ");
                    scanf("%f", &livreModifie.prix);

                    printf("Entrez la nouvelle disponibilité du livre (1 pour disponible, 0 pour non disponible) : ");
                    scanf("%d", &livreModifie.dispo);

                    modifier(livreModifie);  // Appel é la fonction de modification
                } else {
                    printf("Action non autorisée pour un client.\n");
                }
                break;
            case 3:  // Supprimer un livre
                if (add == 0) {
                    char idSupprimer[20];
                    // Demander l'ID du livre é supprimer
                    printf("Entrez l'ID du livre é supprimer : ");
                    scanf("%s", idSupprimer);
                    supprimer(idSupprimer);  // Appel é la fonction de suppression
                } else {
                    printf("Action non autorisée pour un client.\n");
                }
                break;
            case 4:  // Afficher les livres
                afficher();  // Appel é la fonction pour afficher tous les livres
                break;
            case 5:  // Rechercher un livre
                {
                    int R;
                    char titre[50],auteur[25];
                    do{
                    printf("recherche par titre(1) ou par auteur(2) : ");
                    scanf("%d", &R);
                     } while (R != 1&& R != 2);
                     if (R == 1) {
                    printf("entrer titre : ");
                    scanf("%s", titre);
                    recherchertitre(titre);
                      // Appel é la fonction de recherchepar titre
                     }
                     if(R==2){
                         printf("entrer auteur : ");
                         scanf("%s", auteur);
                         rechercherauteur(auteur);  // Appel é la fonction de recherchepar auteur
                     }
                }
                break;
            case 6:  // Trier les livres
               {
                    int R;

                    do{
                    printf("recherche par titre(1) ou par categorie(2) : ");
                    scanf("%d", &R);
                     } while (R != 1&& R != 2);
                     tri(R);

                }
                break;
            case 0:
                printf("Au revoir !\n");
                return 0;  // Quitter le programme
            default:
                printf("Choix invalide. Essayez encore.\n");
        }
    }

    return 0;
}
