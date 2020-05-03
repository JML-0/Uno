#include "controls.h"
#include "pile.h"
#include "rules.h"
#include "uno.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

/** l.46 - 60: Initialisation de la liste des joueurs et ajout des joueurs dans celle-ci; initialisation du tableau de classement, du joueur actuel, 
               du nombre de joueurs actuel, du sens de jeu, des malus, de la dernière carte posée.
			   
    l.62 - 63: On ne veut pas que la première carte posée automatiquement soit un changement de couleur ou un +4, alors on repioche jusqu'à avoir une carte valide.
	
	l.65: début de la boucle de jeu.
	
	l.66 - 68: On teste si le joueur actuel appartient au tableau de classement. Si c'est le cas, alors il a déjà gagné, 
	           on cherche donc le joueur suivant tant que le joueur actuel a déjà gagné.
			   
	l.70 - 79: S'il n'y a plus qu'un joueur, on l'ajoute au classement, on affiche ce dernier, on supprime la mémoire allouée et on sort de la boucle de jeu.
	
	l.86 - 102: Application des malus (+2, +4, passer le tour).
	
	l.109 - 205: Choix de la carte à jouer ou piocher une carte.
	
	l.207-212: Si le joueur n'a plus de cartes, alors il a gagné, on l'ajoute donc on tableau des gagnants.
	
	l.215: Changement de joueur pour le tour suivant.
*/
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
            afficherLeDeck(tempPlayer);
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
                
				// Jouer changement de couleur ou +4
                if(tempCarte.num == 13 || tempCarte.num == 14) {
                    int okColor = 1, choixCouleur = 0; int tmpNum;
                    if(tempCarte.num == 13){
                        tmpNum = 13;
                    } else {
                        tmpNum = 14;
                    }
					// choix couleur
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
                    
					// si le joueur joue +4
                    if(tempCarte.num == 14) {
                        printf("\n\nLe prochain joueur prend 4 cartes\n\n");
                        malusPlus = 4; // le prochain joueur piochera 4 cartes
                    }
                    push(tempCarte);
                    shuffle();
                    deleteCard(tempPlayer, tempCarte.num);
                    ok = 0;
				// Jouer autre chose que changement de couleur ou +4
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
    free(winTab);
}

/** On parcourt le tableau de cartes et on affiche chaque carte.
*/
void afficherLeDeck(Player P) 
{
    for(int i = 0; i < P->totalCard; i++) {
        printf("%d) ", i);
        afficherCarte(P->cartes[i]);
    }
}

/** Comme pour afficherLeDeck, on récupère la couleur et le numéro de la carte afin d'afficher la bonne carte.
*/
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

            default:
            couleur = "";
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

/** On parcourt le tableau passé en paramètre, et on teste pour chaque élément s'il est égal à l'id passé en paramètre. 
    Si oui, retourne 1. Sinon, teste avec l'élément suivant, et si aucun des éléments n'est égal à l'id, retourne 0.
*/
int appartientTab(int * tab, int taille, int id){
    for(int i=0;i<taille;i++){
        if(tab[i] == id)
            return 1;
    }
    return 0;
}

/** Parcourt le tableau passé en paramètre en le remplissant de -1.
*/
void remplirTab(int * tab, int taille){
    for(int i=0;i<taille;i++){
        tab[i] = -1;
    }
}

/** Si on joue dans le sens normal (du joueur 0 à nbJoueurs-1): si le joueur qui a joué (joueurActuel) est le dernier joueur(nbJoueurs-1),
    alors le prochain joueur est le joueur 0; sinon le prochain joueur est joueurActuel + 1.
	
	Si on ne joue pas dans le sens normal (du joueur nbJoueurs-1 à 0): si le joueur qui a joué est le joueur 0, 
	alors le prochain joueur est le dernier (nbJoueurs-1); sinon, le prochain joueur est joueurActuel - 1.
	On retoune ainsi joueurActuel qui est maintenant le prochain joueur.
*/
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
