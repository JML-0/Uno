#include "controls.h"
#include "pile.h"
#include "rules.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void jouer(int nbJoueur);
void afficherLeDeck(Carte* deck, int taille);
void afficherCarte(Carte carte);
void reverse(int * list , int nb);
void menu();

int main() {
    generatePile();

    /*Players P = addPlayer(NULL); //J1
    for (int i = 0; i < 2; i++) //crée 4 joueurs
        P = addPlayer(P);
    showPlayers(P);

    printf("------ PIOCHE ------\n");
    Player p1 = getPlayer(P, 0);
    takeCard(p1);
    showPlayers(P);

    printf("------ DELETE CARD ------\n");
    deleteCard(p1, 3);
    showPlayers(P);*/

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
    int winTab[nbJoueurs];

    int joueurActuel = 0; //ID du joueur actuel
    int joueurCompteur = 0;
    int sensNormal = 1; //Sens du jeu
    int malusPlus = 0, malusPasseTonTour = 0; //Les malus à executer au prochain joueur

    Carte carteActuelle = pop(); //La carte dernièrement posé
    Player tempPlayer;
    //Si la carte pioché par défaut est "changement de couleur" ou "carte +4", alors il faut repiocher jusqu'à avoir une autre carte
    while(carteActuelle.num == 13 || carteActuelle.num == 14)
        carteActuelle = pop();

    while(1) {
        //showPlayers(P);
        tempPlayer = getPlayer(P, joueurActuel);
        if(nbJoueurs == 1) {
                int i;
                winTab[iWin++] = tempPlayer->id;
                printf("\n\n=== FIN DE PARTIE ===\n");
                for(i = 0; i < iWin; i++)
                    printf("    %d - Joueur %d\n", i+1, winTab[i]);
                printf("\n");
                break;
            }

        printf("C'est au joueur %d de jouer !\n", tempPlayer->id);

        int choix = 0, ok = 1, tailleActuelle = tempPlayer->totalCard;

        //Application des malus
        if(malusPlus > 0) {
            printf("\n\nRajout de %d cartes dans ton deck\n\n", malusPlus);
            plusX(tempPlayer, malusPlus);
            ok = 0;
            tailleActuelle = tempPlayer->totalCard;
        }

        if(malusPasseTonTour) {
            printf("\n\nDéso pas déso, ton tour saute\n\n");
            ok = 0;
            
        }

        if(malusPlus || malusPasseTonTour){
            malusPasseTonTour = 0;
            malusPlus = 0;
        } else {
            afficherLeDeck(tempPlayer->cartes, tailleActuelle);
            printf("\n\nDernière carte jouer : ");
            afficherCarte(carteActuelle);
        }
        //Choix de la carte ou alors piocher une carte
        while(ok) {
            printf("\nEcrire -1 pour piocher une carte\n");
            printf("Ou alors selectionner une carte de 0 à %d en écrivant son numéro\n\nChoix : ", tailleActuelle - 1);

            scanf("%d", &choix);

            if(choix == -1) {
                takeCard(tempPlayer);
                ok = 0;
                joueurCompteur++;
            } else if(choix >= 0 && choix <= tailleActuelle) {
                //Jouer une carte
                Carte tempCarte = tempPlayer->cartes[choix];
                joueurCompteur++;
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
                    printf("La +4");
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
            nbJoueurs--;
            printf("Bravo joueur %d, tu as gagné !\n", tempPlayer->id);
            winTab[iWin++] = tempPlayer->id;
            
            removePlayer(P, tempPlayer);
                
        }
        //Changement de joueur pour le tour suivant
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

void reverse(int * list , int nb){
   int *tmpList;
   tmpList = (int*)malloc(sizeof(int)*nb);
   if(tmpList == NULL)
        exit(EXIT_FAILURE);
   for (int i = nb - 1, j = 0 ; i >= 0 ; i--, j++)
        tmpList[j] = list[i];
   for (int i = 0 ; i < nb ; i++)
        list[i] = tmpList[i];
   free(tmpList);
}