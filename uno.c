#include "pile.h"
#include "rules.h"
#include <stdio.h>
#include <stdlib.h>

void jouer();
void creerLeDeck(Carte* deck, int* taille);

void main() {
    generatePile();

    jouer();
}

void jouer() {
    int joueurActuel = 1; //1 = Joueur 1 et 2 = Joeuur 2
    Carte* cartesUn[109], cartesDeux[109]; //Le deck des deux joueurs
    int cartesUnTaille = 0, cartesDeuxTaille = 0; //La nombres de cartes dans chaque deck
    Carte* carteActuelle; //La carte dernièrement posé

    creerLeDeck(cartesUn, &cartesUnTaille);
    creerLeDeck(cartesDeux, &cartesDeuxTaille);

    while(1) {
        printf("C'est au joueur %d de jouer !\n", joueurActuel);

        int choix = 0, tailleActuelle;

        if(joueurActuel == 1)
            tailleActuelle = cartesUnTaille;
        else
            tailleActuelle = cartesDeuxTaille;

        do {
            printf("Ecrire -1 pour piocher une carte\n");
            printf("Ou alors selectionner une carte en écrivant son numéro\n");

            scanf("%d", &choix);
        } while(choix >= -1 && choix <= tailleActuelle);

        if(joueurActuel == 1)
            joueurActuel = 2;
        else
            joueurActuel = 1;
    }
}

void creerLeDeck(Carte* deck, int* taille) {
    for(int i = 0; i < 7; i++) {
        deck[i] = pop();
    }

    *taille = 7;
}