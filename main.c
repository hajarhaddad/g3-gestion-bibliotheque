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
        printf("Vous êtes admin : 0 ou client : 1 : ");
        scanf("%d", &add);
    } while (add != 0 && add != 1);  // S'assurer que l'utilisateur entre une valeur valide (0 ou 1)

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
                    // Demander les informations du livre à ajouter
                    printf("Entrez l'ID du livre : ");
                    scanf("%d", &nouveauLivre.id);  // L'ID est un nombre entier

                    // Utilisation de fgets pour lire des chaînes avec des espaces
                    printf("Entrez le titre du livre : ");
                    fgetc(stdin);  // Cette ligne permet de vider le buffer de l'input
                    fgets(nouveauLivre.titre, sizeof(nouveauLivre.titre), stdin);
                    nouveauLivre.titre[strcspn(nouveauLivre.titre, "\n")] = 0;  // Supprime le saut de ligne

                    printf("Entrez l'auteur du livre : ");
                    fgets(nouveauLivre.auteur, sizeof(nouveauLivre.auteur), stdin);
                    nouveauLivre.auteur[strcspn(nouveauLivre.auteur, "\n")] = 0;  // Supprime le saut de ligne

                    printf("Entrez la description du livre : ");
                    fgets(nouveauLivre.description, sizeof(nouveauLivre.description), stdin);
                    nouveauLivre.description[strcspn(nouveauLivre.description, "\n")] = 0;  // Supprime le saut de ligne

                    printf("Entrez l'utilisateur : ");
                    fgets(nouveauLivre.utilisateur, sizeof(nouveauLivre.utilisateur), stdin);
                    nouveauLivre.utilisateur[strcspn(nouveauLivre.utilisateur, "\n")] = 0;  // Supprime le saut de ligne

                    printf("Entrez le prix du livre : ");
                    scanf("%f", &nouveauLivre.prix);  // Le prix est un nombre flottant

                    printf("Entrez la disponibilité du livre (1 pour disponible, 0 pour non disponible) : ");
                    scanf("%d", &nouveauLivre.dispo);  // La disponibilité est un nombre entier

                    ajouter(nouveauLivre);  // Appel à la fonction d'ajout
                } else {
                    printf("Action non autorisée pour un client.\n");
                }
                break;
            case 2:  // Modifier un livre
                if (add == 0) {
                    Livre livreModifie;
                    // Demander l'ID du livre à modifier
                    printf("Entrez l'ID du livre à modifier : ");
                    scanf("%d", &livreModifie.id);  // L'ID est un nombre entier

                    // Demander les autres informations à modifier
                    printf("Entrez le nouveau titre du livre : ");
                    fgetc(stdin);  // Cette ligne permet de vider le buffer de l'input
                    fgets(livreModifie.titre, sizeof(livreModifie.titre), stdin);
                    livreModifie.titre[strcspn(livreModifie.titre, "\n")] = 0;  // Supprime le saut de ligne

                    printf("Entrez le nouvel auteur du livre : ");
                    fgets(livreModifie.auteur, sizeof(livreModifie.auteur), stdin);
                    livreModifie.auteur[strcspn(livreModifie.auteur, "\n")] = 0;

                    printf("Entrez la nouvelle description du livre : ");
                    fgets(livreModifie.description, sizeof(livreModifie.description), stdin);
                    livreModifie.description[strcspn(livreModifie.description, "\n")] = 0;

                    printf("Entrez le nouvel utilisateur : ");
                    fgets(livreModifie.utilisateur, sizeof(livreModifie.utilisateur), stdin);
                    livreModifie.utilisateur[strcspn(livreModifie.utilisateur, "\n")] = 0;

                    printf("Entrez le nouveau prix du livre : ");
                    scanf("%f", &livreModifie.prix);

                    printf("Entrez la nouvelle disponibilité du livre (1 pour disponible, 0 pour non disponible) : ");
                    scanf("%d", &livreModifie.dispo);

                    modifier(livreModifie);  // Appel à la fonction de modification
                } else {
                    printf("Action non autorisée pour un client.\n");
                }
                break;
            case 3:  // Supprimer un livre
                if (add == 0) {
                    char idSupprimer[20];
                    // Demander l'ID du livre à supprimer
                    printf("Entrez l'ID du livre à supprimer : ");
                    scanf("%s", idSupprimer);
                    supprimer(idSupprimer);  // Appel à la fonction de suppression
                } else {
                    printf("Action non autorisée pour un client.\n");
                }
                break;
            case 4:  // Afficher les livres
                afficher();  // Appel à la fonction pour afficher tous les livres
                break;
            case 5:  // Rechercher un livre
                {
                    char idRecherche[20];
                    // Demander l'ID du livre à rechercher
                    printf("Entrez l'ID du livre à rechercher : ");
                    scanf("%s", idRecherche);
                    rechercher(idRecherche);  // Appel à la fonction de recherche
                }
                break;
            case 6:  // Trier les livres
                tri(livres, nbLivres);  // Passer le tableau de livres et le nombre de livres
                break;
            case 0:  // Quitter et enregistrer les livres
                printf("Au revoir !\n");
                return 0;  // Quitter le programme
            default:
                printf("Choix invalide. Essayez encore.\n");
        }
    }

    return 0;
}
