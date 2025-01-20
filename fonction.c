#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fonction.h"
void afficherMenuadmin(){
    printf("\n--- Menu de Gestion des Livres ---\n");
    printf("1. Ajouter un livre\n");
    printf("2. Modifier un livre\n");
    printf("3. Supprimer un livre\n");
    printf("4. Afficher un livre\n");
    printf("5. Rechercher un livre\n");
    printf("6. Trier les livres\n");
    printf("0. Quitter\n");
    printf("Entrez votre choix: ");
}

// Affiche le menu client
void afficherMenuclient() {
    printf("\n--- Menu de Gestion des Livres ---\n");
    printf("4. Afficher un livre\n");
    printf("5. Rechercher un livre\n");
    printf("6. Trier les livres\n");
    printf("0. Quitter\n");
    printf("Entrez votre choix: ");
}


// Fonction pour ajouter un livre dans le "livre.csv binaire
void ajouter(Livre L) {
    FILE *f = fopen("livre.csv", "ab");  // Ouvre le "livre.csv" en mode ajout binaire
    if (f == NULL) {
        printf("Erreur d'ouverture du (livre.csv).\n");
        exit(1);
    }
    fwrite(&L, sizeof(Livre), 1, f);  // �crit un livre dans le "livre.csv"
    fclose(f);
    printf("Livre ajout� avec succ�s!\n");
}

// Fonction pour afficher les livres depuis le "livre.csv binaire
void afficher() {
    FILE *f = fopen("livre.csv", "rb");  // Ouvre le "livre.csv" en mode lecture binaire
    if (f == NULL) {
        printf("Erreur d'ouverture du livre.csv.\n");
       exit(1);
    }

    Livre L;
    while (fread(&L, sizeof(Livre), 1, f)) {
        printf("ID: %s\n", L.id);
        printf("Titre: %s\n", L.titre);
        printf("Auteur: %s\n", L.auteur);
        printf("Description: %s\n", L.description);
         printf("Utilisateur: %s\n", L.utilisateur);
         printf("categorie: %s\n", L.categorie);
        printf("Prix: %.2f\n", L.prix);
        printf("Disponibilite: %s\n", L.dispo == 1 ? "Disponible" : "Non disponible");
        printf("--------------------------------------------\n");
    }
    fclose(f);
}

// Fonction pour rechercher un livre par son titre
void recherchertitre(char *titre) {
    FILE *f = fopen("livre.csv", "rb");  // Ouvre le "livre.csv" en mode lecture binaire
    if (f == NULL) {
        printf("Erreur d'ouverture du livre.csv.\n");
        exit(1);
    }

    Livre L;
    int found = 0;
    while (fread(&L, sizeof(Livre), 1, f)) {
        if (strcmp(L.titre, titre) == 0) {
            printf("Livre trouvé:\n");
            printf("ID: %s\n", L.id);
            printf("Titre: %s\n", L.titre);
            printf("Auteur: %s\n", L.auteur);
            printf("Description: %s\n", L.description);
            printf("Utilisateur: %s\n", L.utilisateur);
            printf("categorie: %s\n", L.categorie);
            printf("Prix: %.2f\n", L.prix);
            printf("Disponibilité: %s\n", L.dispo == 1 ? "Disponible" : "Non disponible");
             printf("****************************");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Livre avec titre %s non trouv�.\n", titre);
    }

    fclose(f);
}
// Fonction pour rechercher un livre par son auteur
void rechercherauteur(char *auteur) {
    FILE *f = fopen("livre.csv", "rb");  // Ouvre le "livre.csv" en mode lecture binaire
    if (f == NULL) {
        printf("Erreur d'ouverture du livre.csv.\n");
        exit(1);
    }

    Livre L;
    int found = 0;
    while (fread(&L, sizeof(Livre), 1, f)) {
        if (strcmp(L.auteur, auteur) == 0) {
            printf("Livre trouvé:\n");
            printf("ID: %s\n", L.id);
            printf("Titre: %s\n", L.titre);
            printf("Auteur: %s\n", L.auteur);
            printf("Description: %s\n", L.description);
            printf("Utilisateur: %s\n", L.utilisateur);
            printf("categorie: %s\n", L.categorie);
            printf("Prix: %.2f\n", L.prix);
            printf("Disponibilité: %s\n", L.dispo == 1 ? "Disponible" : "Non disponible");
            printf("****************************");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Livre avec auteur  %s non trouv�.\n", auteur);
    }

    fclose(f);
}

// Fonction pour modifier un livre

void modifier(Livre L) {
    FILE *f = fopen("livre.csv", "r+b");  // Ouvre le "livre.csv" en mode lecture et ecriture binaire
    if (f == NULL) {
        printf("Erreur d'ouverture du livre.csv.\n");
        exit(1);
    }

    Livre temp;
    int found = 0;
    while (fread(&temp, sizeof(Livre), 1, f)) {
        if (strcmp(temp.id, L.id) == 0) {
            fseek(f, -sizeof(Livre), SEEK_CUR);  // D�place le pointeur de "livre.csv"pour remplacer le livre
            fwrite(&L, sizeof(Livre), 1, f);
            printf("Livre modifié avec succés!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Livre avec l'ID %s non trouvé.\n", L.id);
    }

    fclose(f);
}

// Fonction pour supprimer un livre
void supprimer(char *id) {
    FILE *f = fopen("livre.csv", "rb");  // Ouvre le "livre.csv" en mode lecture binaire
    if (f == NULL) {
        printf("Erreur d'ouverture du livre.csv.\n");
        exit(1);
    }

    FILE *ftemp = fopen("temp.csv", "wb");  // "livre.csv" temporaire pour sauvegarder les livres
    if (ftemp == NULL) {
        printf("Erreur d'ouverture du fichier temp .\n");
        fclose(f);
       exit(1);
    }

    Livre L;
    int found = 0;
    while (fread(&L, sizeof(Livre), 1, f)) {
        if (strcmp(L.id, id) != 0) {
            fwrite(&L, sizeof(Livre), 1, ftemp);
            found = 1;
        }
    }

    fclose(f);
    fclose(ftemp);

    if (found) {
        remove("livre.csv");  // Supprime le "livre.csv"original
        rename("temp.csv", "livre.csv");  // Renomme le "livre.csv"temporaire pour le "livre.csv"original
        printf("Livre supprimé avec succés!\n");
    } else {
        printf("Livre avec l'ID %s non trouvé.\n", id);
    }
}

// Fonction pour trier les livres par titre
void tri(int R){
    FILE *f = fopen("livre.csv", "r+b");  // Ouvre le "livre.csv" en mode lecture et �criture binaire
    if (f == NULL) {
        printf("Erreur d'ouverture du livre.csv.\n");
        exit(1);
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);   // Obtenir la taille du "livre.csv"
    rewind(f);

    int nbLivres = size / sizeof(Livre);  // Calcul du nombre de livres dans le "livre.csv"
    Livre L[nbLivres],l;
    int i,j;
    fread(&L, sizeof(Livre), nbLivres, f);  // Lire tous les livres dans le tableau

    if (R == 1) {
        // Tri par titre
        for (i = 0; i < nbLivres - 1; i++) {
            for (j = i + 1; j < nbLivres; j++) {
                if (strcmp(L[i].titre, L[j].titre) > 0) {
                    Livre temp = L[i];
                    L[i] = L[j];
                    L[j] = temp;
                }
            }
        }
    } else if (R == 2) {
        // Tri par catégorie
        for (i = 0; i < nbLivres - 1; i++) {
            for (j = i + 1; j < nbLivres; j++) {
                if (strcmp(L[i].categorie, L[j].categorie) > 0) {
                    Livre temp = L[i];
                    L[i] = L[j];
                    L[j] = temp;
                }
            }
        }
    } else {
        printf("Choix invalide.\n");
        fclose(f);
        return;
    }


    // Réecrire les livres triés dans le "livre.csv"
    fseek(f, 0, SEEK_SET);  // Retour au début du "livre.csv" pour écriture
    fwrite(&L, sizeof(Livre), nbLivres, f);
// Affichage des livres triés
    printf("Livres triés :\n");
    for (i = 0; i < nbLivres; i++) {
         printf("ID: %s\n", l.id);
            printf("Titre: %s\n", l.titre);
            printf("Auteur: %s\n", l.auteur);
            printf("Description: %s\n",l.description);
            printf("Utilisateur: %s\n", l.utilisateur);
            printf("categorie: %s\n", l.categorie);
            printf("Prix: %.2f\n", l.prix);
            printf("Disponibilité: %s\n", l.dispo == 1 ? "Disponible" : "Non disponible");
        printf("-----------------------------\n");
    }

    fclose(f);

    printf("Livres triés avec succés!\n");
}

