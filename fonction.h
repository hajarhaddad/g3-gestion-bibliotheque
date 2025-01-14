#ifndef FONCTION_H
#define FONCTION_H


    // D�finition de la structure Livre
typedef struct {
    char id[20];  // ID comme chaîne de caractères
    char titre[200];
    char auteur[200];
    char description[200];
    char utilisateur[200];
    float prix;
    int dispo;  // 1 pour disponible, 0 pour non disponible
} Livre;
  // Prototypes des fonctions
     // Fonctions pour afficher les menus
void afficherMenuadmin();
void afficherMenuclient();
    // Fonctions pour gérer les livres
void ajouter(Livre L);
void modifier(Livre L);
void supprimer(char *id);
    // Fonctions pour  afficher les livres

void afficher();
   // Fonction pour rechercher un livre et trier les livres
void rechercher(char *idRecherche);
void tri();

#endif

