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
        return;
    }
    fwrite(&L, sizeof(Livre), 1, f);  // Écrit un livre dans le "livre.csv"
    fclose(f);
    printf("Livre ajouté avec succès!\n");
}

// Fonction pour afficher les livres depuis le "livre.csv binaire
void afficher() {
    FILE *f = fopen("livre.csv", "rb");  // Ouvre le "livre.csv" en mode lecture binaire
    if (f == NULL) {
        printf("Erreur d'ouverture du livre.csv.\n");
        return;
    }

    Livre L;
    while (fread(&L, sizeof(Livre), 1, f)) {
        printf("ID: %s\n", L.id);
        printf("Titre: %s\n", L.titre);
        printf("Auteur: %s\n", L.auteur);
        printf("Description: %s\n", L.description);
        printf("Utilisateur: %s\n", L.utilisateur);
        printf("Prix: %.2f\n", L.prix);
        printf("Disponibilité: %s\n", L.dispo == 1 ? "Disponible" : "Non disponible");
        printf("--------------------------------------------\n");
    }
    fclose(f);
}

// Fonction pour rechercher un livre par son ID
void rechercher(char *idRecherche) {
    FILE *f = fopen("livre.csv", "rb");  // Ouvre le "livre.csv" en mode lecture binaire
    if (f == NULL) {
        printf("Erreur d'ouverture du livre.csv.\n");
        return;
    }

    Livre L;
    int found = 0;
    while (fread(&L, sizeof(Livre), 1, f)) {
        if (strcmp(L.id, idRecherche) == 0) {
            printf("Livre trouvé:\n");
            printf("ID: %s\n", L.id);
            printf("Titre: %s\n", L.titre);
            printf("Auteur: %s\n", L.auteur);
            printf("Description: %s\n", L.description);
            printf("Utilisateur: %s\n", L.utilisateur);
            printf("Prix: %.2f\n", L.prix);
            printf("Disponibilité: %s\n", L.dispo == 1 ? "Disponible" : "Non disponible");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Livre avec l'ID %s non trouvé.\n", idRecherche);
    }

    fclose(f);
}

// Fonction pour modifier un livre

void modifier(Livre L) {
    FILE *f = fopen("livre.csv", "r+b");  // Ouvre le "livre.csv" en mode lecture et écriture binaire
    if (f == NULL) {
        printf("Erreur d'ouverture du livre.cs.\n");
        return;
    }

    Livre temp;
    int found = 0;
    while (fread(&temp, sizeof(Livre), 1, f)) {
        if (strcmp(temp.id, L.id) == 0) {
            fseek(f, -sizeof(Livre), SEEK_CUR);  // Déplace le pointeur de "livre.csv"pour remplacer le livre
            fwrite(&L, sizeof(Livre), 1, f);
            printf("Livre modifié avec succès!\n");
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
        return;
    }

    FILE *ftemp = fopen("temp.csv", "wb");  // "livre.csv" temporaire pour sauvegarder les livres
    if (ftemp == NULL) {
        printf("Erreur d'ouverture du fichier temp .\n");
        fclose(f);
        return;
    }

    Livre L;
    int found = 0;
    while (fread(&L, sizeof(Livre), 1, f)) {
        if (strcmp(L.id, id) != 0) {
            fwrite(&L, sizeof(Livre), 1, ftemp);  // Écrit les livres qui ne sont pas à supprimer
        } else {
            found = 1;
        }
    }

    fclose(f);
    fclose(ftemp);

    if (found) {
        remove("livre.csv");  // Supprime le "livre.csv"original
        rename("temp.csv", "livre.csv");  // Renomme le "livre.csv"temporaire pour le "livre.csv"original
        printf("Livre supprimé avec succès!\n");
    } else {
        printf("Livre avec l'ID %s non trouvé.\n", id);
    }
}

// Fonction pour trier les livres par titre
void tri() {
    FILE *f = fopen("livre.csv", "r+b");  // Ouvre le "livre.csv" en mode lecture et écriture binaire
    if (f == NULL) {
        printf("Erreur d'ouverture du livre.csv.\n");
        return;
    }

    fseek(f, 0, SEEK_END);  // Déplace le pointeur de "livre.csv" à la fin
    long size = ftell(f);   // Obtenir la taille du "livre.csv"
    rewind(f);              // Rewind pour revenir au début

    int nbLivres = size / sizeof(Livre);  // Calcul du nombre de livres dans le "livre.csv"
    Livre *livres = (Livre *)malloc(size); // Allocation dynamique pour lire tous les livres

    fread(livres, sizeof(Livre), nbLivres, f);  // Lire tous les livres dans le tableau

    // Tri des livres par titre
    for (int i = 0; i < nbLivres - 1; i++) {
        for (int j = i + 1; j < nbLivres; j++) {
            if (strcmp(livres[i].titre, livres[j].titre) > 0) {
                Livre temp = livres[i];
                livres[i] = livres[j];
                livres[j] = temp;
            }
        }
    }

    // Réécrire les livres triés dans le "livre.csv"
    fseek(f, 0, SEEK_SET);  // Retour au début du "livre.csv" pour écriture
    fwrite(livres, sizeof(Livre), nbLivres, f);

    free(livres);  // Libération de la mémoire allouée
    fclose(f);

    printf("Livres triés avec succès!\n");
}

