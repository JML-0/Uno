#include "pile.h"
#include "rules.h"
#include "controls.h"
#include <stdio.h>
#include <stdlib.h>

void jouer();
void creerLeDeck(Carte* deck, int* taille);
void afficherLeDeck(Carte* deck, int taille);

int main() {
    generatePile();

    Players P = add(NULL); //J1
    for (int i = 0; i < 5; i++) //crée 4 joueurs
        P = add(P);
    
    showPlayers(P);

    //jouer();
}

void jouer() {
    int joueurActuel = 1; //1 = Joueur 1 et 2 = Joeuur 2
    Carte cartesUn[109], cartesDeux[109]; //Le deck des deux joueurs
    int cartesUnTaille = 0, cartesDeuxTaille = 0; //La nombres de cartes dans chaque deck
    Carte* carteActuelle; //La carte dernièrement posé

    creerLeDeck(cartesUn, &cartesUnTaille);
    creerLeDeck(cartesDeux, &cartesDeuxTaille);

    while(1) {
        printf("C'est au joueur %d de jouer !\n", joueurActuel);

        int choix = 0, tailleActuelle;

        if(joueurActuel == 1) {
            tailleActuelle = cartesUnTaille;
            afficherLeDeck(cartesUn, tailleActuelle);
        } else {
            tailleActuelle = cartesDeuxTaille;
            afficherLeDeck(cartesDeux, tailleActuelle);
        }

        //Choix de la carte ou alors piocher une carte
        do {
            printf("\n\nEcrire -1 pour piocher une carte\n");
            printf("Ou alors selectionner une carte de 0 à %d en écrivant son numéro\n\nChoix : ", tailleActuelle - 1);

            scanf("%d", &choix);
        } while(choix <= -1 && choix >= tailleActuelle);

        if(choix == -1) {
            //Piocher une carte
            if(joueurActuel == 1) {
                cartesUn[cartesUnTaille++] = pop();
            } else {
                cartesDeux[cartesDeuxTaille++] = pop();
            }
        } else {
            //Jouer une carte
        }

        //Changement de joueur pour le tour suivant
        if(joueurActuel == 1)
            joueurActuel = 2;
        else
            joueurActuel = 1;

        //Voir s'il y a un des deux joueurs qui a gagné
        if(cartesUnTaille == 0) {
            printf("Bravo joueur 1, tu as gagné !\n");
            break;
        }

        if(cartesDeuxTaille == 0) {
            printf("Bravo joueur 2, tu as gagné !\n");
            break;
        }
    }
}

void afficherLeDeck(Carte* deck, int taille) {
    for(int i = 0; i < taille; i++) {
        char* couleur;

        switch(deck[i].color) {
            case B:
            couleur = "Bleu";
            break;

            case R:
            couleur = "Rouge";
            break;

            case G:
            couleur = "Vert";
            break;

            case Y:
            couleur = "Jaune";
            break;
        }

        printf("\n(%d) %d - %s", i, deck[i].num, couleur);
    }
}

void creerLeDeck(Carte* deck, int* taille) {
    for(int i = 0; i < 7; i++) {
        deck[i] = pop();
    }

    *taille = 7;
}