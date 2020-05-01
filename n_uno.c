/*
 * PSEUDO CODE, NON TESTÉ
 * Vous pouvez soit le continuer, soit vous en inspirer ou soit attendre les autres push.
 * L'idée est d'utiliser au maximum la liste chaînée "Players".
 * 
 * Le but est également d'optimiser au maximum le code afin de le fractionner
 * et d'y mettre les 3/4 des fonctions dans le fichier rules.c, pour le moment
 * tout est ici.
*/

#include "rules.h"
#include "pile.h"
#include "controls.h"
#include <stdio.h>
#include <assert.h>

#define checkChoice(a, b)   (a >= 0 && a <= b ? 1 : 0)
#define validCard(a, b)     (a.color == b.color || a.num == b.num ? 1 : 0)
#define skip(a)             (a = a->next)

void play()
{
    int nbPlayers       = 3;
    int nbRankedPlys    = 0;
    int malusPass       = 0;
    int indexCard       = 0;
    int choice          = 0;
    int *ranking        = malloc(sizeof(int) * nbPlayers); assert(ranking);
    Color color         = NULL;
    Players P           = NULL;
    Carte Pioche        = getCard();
    Carte C;

    for (int i = 0; i < nbPlayers; i++) // ajout de x joueurs
        P = addPlayer(P);

    while (nbPlayers > 1)
    {
        /* Affichage des cartes du joueur */
        printf("C'est au tour du joueur %d !\n", P->player->id);
        showCardsPlayer(P->player);

        /* Affichage de la carte actuelle */
        printf("\n\nCarte actuelle : "); showCard(Pioche);

        /* On demande la carte à selectionner */
        indexCard = selectIndexCard(P->player);
        C = P->player->cartes[indexCard];

        /* Si le joueur ne peut pas poser une carte ou souhaite passer */
        if (indexCard == -1)
        {
            skip(P);
            continue;
        }

        /* On verifie si la carte selectionnee est valide */
        while (!validCard(Pioche, C))
        {
            printf("Impossible de jouer cette carte !\n");
            indexCard = selectIndexCard(P->player);
        }

        /* On remet la carte dans la pioche et on supprime */
        deleteCard(P->player, C.num);
        --P->player->totalCard;
        push(C);    // C'est une solution temporaire, plus tard une fonction
        shuffle();  // mettra la carte à la fin de la pile

        /* On vérifie si le joueur n'a plus de carte */
        if (!P->player->totalCard)
        {
            ranking[nbRankedPlys++] = P->player->id;
            removePlayer(P, P->player);
            --nbPlayers;
        }

        /* On applique l'effet de la carte si présent */
        applyEffect(C, P, &color);

        /* Joueur suivant */
        skip(P);
    }

    /* Il reste plus qu'un joueur */
    // affichage des gagnants (par ordre)
    for (int i = 0; i < nbRankedPlys; i++)
    {
        printf("Classement des joueurs : \n\n");
        printf("%d - Le joueur %d\n", i + 1, ranking[i]);
    }
    
    printf("FIN DE LA PARTIE\n");

    free(ranking);
}

void applyEffect(Carte C, Players P, Color *color)
{
    switch (C.num)
    {
    case 10: //passe le tour
        printf("Le joueur %d passe son tour.\n", P->next->player->id);
        skip(P);
        break;
    case 11: //change de sens
        changeDirection(P);
        break;
    case 12: //+2
        plusX(P->next->player, 2);
        skip(P);
        break;
    case 13: //changement de couleur
        *color = choiceColor();
        break;
    case 14: //+4
        *color = choiceColor();
        plusX(P->next->player, 4);
        skip(P);
        break;
    default:
        break;
    }
}

void changeDirection(Players P)
{
    Players prev    = NULL; 
    Players current = P; 
    Players next    = NULL; 

    while (current != NULL) 
    { 
        next            = current->next; 
        current->next   = prev;
        prev            = current; 
        current         = next; 
    } 

    P = prev; 
}

Carte getCard()
{
    Carte C = pop(), tmp;
    while (C.num == 10 || C.num == 11 || C.num == 12 || C.num == 13 || C.num == 14)
    {
        tmp = C;
        C = pop();
        push(tmp);
        shuffle();
    }
    return C;
}

Color choiceColor()
{
    Color choice = NULL;

    do
    {
        printf("Quelle couleur souhaitez-vous ? (0:bleu / 1:rouge / 2:vert / 3:jaune) "); scanf("%s", &choice);
    } while (choice != B || choice != R || choice != G || choice != Y);
    
    return choice;
}


int selectIndexCard(Player P)
{
    int choice = 0, take = 0;

    do
    {
        if (take)
        {
            printf("Pour passer votre tour, tapez -1, sinon le numéro de la carte que vous voulez jouer.\n");
            scanf("%d", &choice);

            if (choice == -1) return -1;
        }
        else
        {
            printf("\n\nPour piocher une carte, tapez -1, sinon le numéro de la carte que vous voulez jouer.\n");
            scanf("%d", &choice);

            if (choice == -1) //pioche
            {
                takeCard(P);
                ++choice;
                ++take;
            }
        }
    } while (checkChoise(choice, P->totalCard));

    return choice;
}

void showCardsPlayer(Player P)
{
    for (int i = 0; i < P->totalCard; i++)
    {
        printf("%d - ", i); showCard(P->cartes[i]);
    }    
}

void showCard(Carte C)
{
    char* color;

        switch(C.color) {
            case B:
            color = "Bleu";
            break;

            case R:
            color = "Rouge";
            break;

            case G:
            color = "Vert";
            break;

            case Y:
            color = "Jaune";
            break;
        }

        switch(C.num) {
            case 10:
            printf("(%s) Carte passe ton tour\n", color);
            break;

            case 11:
            printf("(%s) Carte changement de sens\n", color);
            break;

            case 12:
            printf("(%s) Carte +2\n", color);
            break;

            case 13:
            printf("Carte changement de couleur\n");
            break;

            case 14:
            printf("Carte +4\n");
            break;

            default:
            printf("(%s) %d\n", C.num, color);
            break;
        }
}