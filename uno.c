#include "controls.h"
#include "pile.h"
#include "rules.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void jouer(int nbJoueurs);
void afficherLeDeck(Carte* deck, int taille);
void afficherCarte(Carte carte);
void menu();
void remplirTab(int * tab, int taille);
void afficherTab(int * tab, int taille);
int appartientTab(int * tab, int taille, int id);
int tour(int joueurActuel,int sensNormal, int nbJoueurs);


int main() {
    generatePile();
    menu();
}

//  Le menu du jeu 
void menu(){
    int nbjoueur = 0;
    printf("\nNombre de joueurs : ");
    scanf("%d",&nbjoueur);
    //clearScreen();
    jouer(nbjoueur);
}


// permet de clear pour avoir un terminal plus propre

void jouer(int nbJoueurs) {
    Players P = NULL;

    for (int i = 0; i < nbJoueurs; i++) //crée x joueurs
        P = addPlayer(P);

    int iWin = 0;
    int * winTab = malloc(nbJoueurs * sizeof(int));
    remplirTab(winTab,nbJoueurs);
    int joueurActuel = 0; //ID du joueur actuel
    int nbJoueursActuelle = nbJoueurs;
    int sensNormal = 1; //Sens du jeu
    int malusPlus = 0, malusPasseTonTour = 0; //Les malus à executer au prochain joueur

    Carte carteActuelle = pop(); //La carte dernièrement posé
    Player tempPlayer;
    //Si la carte pioché par défaut est "changement de couleur" ou "carte +4", alors il faut repiocher jusqu'à avoir une autre carte
    while(carteActuelle.num == 13 || carteActuelle.num == 14)
        carteActuelle = pop();

    while(1) {
        while(appartientTab(winTab,nbJoueurs,joueurActuel)){
            joueurActuel = tour(joueurActuel,sensNormal,nbJoueurs);
        }
        
        tempPlayer = getPlayer(P, joueurActuel);
        if(nbJoueursActuelle == 1) {
                int i;
                winTab[iWin] = tempPlayer->id;
                printf("\nClassement des joueurs: \n");
                for(int i=0, j=1;i<nbJoueurs;i++,j++)
                    printf("%d : Joueur %d\n",j,winTab[i]);
                free(winTab);
                break;
            }

        

        int choix = 0, ok = 1, tailleActuelle = tempPlayer->totalCard;

        //Application des malus
        if(malusPlus > 0) {
            printf("\n\nRajout de %d cartes au joueur %d !\n\n", malusPlus, tempPlayer->id);
            plusX(tempPlayer, malusPlus);
            ok = 0;
            tailleActuelle = tempPlayer->totalCard;
        }

        if(malusPasseTonTour) {
            printf("\n\nLe tour du joueur %d est bloque !\n\n",tempPlayer->id);
            ok = 0;
            
        }

        if(malusPlus || malusPasseTonTour){
            malusPasseTonTour = 0;
            malusPlus = 0;
        } else {
            printf("C'est au joueur %d de jouer !\n", tempPlayer->id);
            afficherLeDeck(tempPlayer->cartes, tailleActuelle);
            printf("\n\nDerniere carte jouer : ");
            afficherCarte(carteActuelle);
        }
        //Choix de la carte ou alors piocher une carte
        while(ok) {
            printf("\nEcrire -1 pour piocher une carte\n");
            printf("Ou alors selectionner une carte de 0 a %d en ecrivant son numero\n\nChoix : ", tailleActuelle - 1);

            scanf("%d", &choix);

            if(choix == -1) {
                takeCard(tempPlayer);
                ok = 0;
                
            } else if(choix >= 0 && choix <= tailleActuelle) {
                //Jouer une carte
                Carte tempCarte = tempPlayer->cartes[choix];
                afficherCarte(tempCarte);
                
                if(tempCarte.num == 13 || tempCarte.num == 14) {
                    int okColor = 1, choixCouleur = 0; int tmpNum;
                    if(tempCarte.num == 13){
                        tmpNum = 13;
                    } else {
                        tmpNum = 14;
                    }
                    do {
                        printf("Tu souhaite quelle couleur ? (0 = Rouge, 1 = Bleu, 2 = Vert, 3 = Jaune): ");
                        scanf("%d", &choixCouleur);

                        switch(choixCouleur) {
                            case 0:
                            carteActuelle.color = R;
                            carteActuelle.num = tmpNum;
                            okColor = 0;
                            break;

                            case 1:
                            carteActuelle.color = B;
                            carteActuelle.num = tmpNum;
                            okColor = 0;
                            break;

                            case 2:
                            carteActuelle.color = G;
                            carteActuelle.num = tmpNum;
                            okColor = 0;
                            break;

                            case 3:
                            carteActuelle.color = Y;
                            carteActuelle.num = tmpNum;
                            okColor = 0;
                            break;
                        }
                    } while(okColor);
                    
                    if(tempCarte.num == 14) {
                        printf("\n\nLe prochain joueur prend 4 cartes\n\n");
                        malusPlus = 4;
                    }
                    push(tempCarte);
                    shuffle();
                    deleteCard(tempPlayer, tempCarte.num);
                    ok = 0;
                } else {
                    if(tempCarte.color == carteActuelle.color || tempCarte.num == carteActuelle.num) {

                        switch(tempCarte.num) {
                            case 10:
                            printf("\n\nLe tour du prochain joueur saute.\n\n");
                            malusPasseTonTour = 1;
                            break;

                            case 11:
                            printf("\n\nChangement de sens.\n\n");
                            sensNormal = !sensNormal;
                            break;

                            case 12:
                            printf("\n\nLe prochain joueur prend 2 cartes.\n\n");
                            malusPlus = 2;
                            break;
                        }

                        carteActuelle = tempCarte;
                        push(tempCarte);
                        shuffle();
                        deleteCard(tempPlayer, tempCarte.num);

                        ok = 0;
                    }

                }

            }
        }
        //Voir s'il y a un des deux joueurs qui a gagné
        if(zeroCard(tempPlayer)) {
            printf("Bravo joueur %d, tu as fini !\n", tempPlayer->id);
            winTab[iWin++] = tempPlayer->id;
            nbJoueursActuelle--;
            P = removePlayer(P, tempPlayer);
                
        }
        //Changement de joueur pour le tour suivant
        
        joueurActuel = tour(joueurActuel,sensNormal,nbJoueurs);
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

        switch(deck[i].num) {
            case 10:
            printf("\n(%d) Carte passe ton tour - %s", i, couleur);
            break;

            case 11:
            printf("\n(%d) Carte changement de sens - %s", i, couleur);
            break;

            case 12:
            printf("\n(%d) Carte +2 - %s", i, couleur);
            break;

            case 13:
            printf("\n(%d) Carte changement de couleur", i);
            break;

            case 14:
            printf("\n(%d) Carte +4", i);
            break;

            default:
            printf("\n(%d) %d - %s", i, deck[i].num, couleur);
            break;
        }
        
    }
}

void afficherCarte(Carte carte) {
    char* couleur;

        switch(carte.color) {
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

        switch(carte.num) {
            case 10:
            printf("Carte passe ton tour - %s\n", couleur);
            break;

            case 11:
            printf("Carte changement de sens - %s\n", couleur);
            break;

            case 12:
            printf("Carte +2 - %s\n", couleur);
            break;

            case 13:
            printf("Carte changement de couleur - %s\n",couleur);
            break;

            case 14:
            printf("Carte +4 - %s\n",couleur);
            break;

            default:
            printf("%d - %s\n", carte.num, couleur);
            break;
        }
}
//Fonction qui return 1 si l'id entrée en parametre apartient au tableau entrée en parametre sinon return 0.
int appartientTab(int * tab, int taille, int id){
    for(int i=0;i<taille;i++){
        if(tab[i] == id)
            return 1;
    }
    return 0;
}
//Fonction qui remplit le tableau entrée en parametre de "-1" pour dire qu'il est vide.
void remplirTab(int * tab, int taille){
    for(int i=0;i<taille;i++){
        tab[i] = -1;
    }
}

//Fonction renvoie l'id du prochain joueur on fonction du sens.
int tour(int joueurActuel,int sensNormal, int nbJoueurs){
    if(sensNormal) {
            if(joueurActuel == nbJoueurs-1)
                joueurActuel = 0;
            else
                joueurActuel++;
        } else {    
            if(joueurActuel == 0)
                joueurActuel = nbJoueurs-1;
            else
                joueurActuel--;
    }
    return joueurActuel;
}