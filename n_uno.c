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

#define checkChoice(a, b)   (a >= 0 && a <= b ? 1 : 0)
#define validCard(a, b)     (a.color == b.color || a.num == b.num ? 1 : 0)
#define skip(a)             (a = a->next)

void play()
{
    int nbPlayers   = 3;
    int plus2       = 0;
    int plus4       = 0;
    int malusPass   = 0;
    int indexCard   = 0;
    int choice      = 0;
    Players P       = NULL;
    Carte Pioche    = getCard();
    Carte C;

    for (int i = 0; i < nbPlayers; i++) // ajout de x joueurs
        P = addPlayer(P);

    while (nbPlayers > 1)
    {
        /* Affichage des cartes du joueur */
        showCardsPlayer(P->player);

        /* Affichage de la carte actuelle */
        printf("\n\nCarte actuelle : "); showCard(Pioche);

        /* On applique le malus, sauf si le joueur possède également le meme */
        if (plus2)
        {
            printf("%d +2 posé(s), souhaitez-vous jouer le votre ? (1:Y/0:N)", (plus2 / 2)); scanf("%d", &choice);
            if (choice)
            {
                indexCard = selectIndexCard(P->player);
                C = P->player->cartes[indexCard];

                while (C.num != 12)
                {
                    printf("Vous devez mettre un +2 !\n");
                    indexCard = selectIndexCard(P->player);
                    C = P->player->cartes[indexCard];
                }
            }
            else
            {
                plusX(P->player, plus2);
                skip(P);
                continue;
            }
        }
        else if (plus4)
        {
            printf("%d +4 posé(s), souhaitez-vous jouer le votre ? (1:Y/0:N)", (plus4 / 4)); scanf("%d", &choice);
            if (choice)
            {
                indexCard = selectIndexCard(P->player);
                C = P->player->cartes[indexCard];

                while (C.num != 14)
                {
                    printf("Vous devez mettre un +4 !\n");
                    indexCard = selectIndexCard(P->player);
                    C = P->player->cartes[indexCard];
                }
            }
            else
            {
                plusX(P->player, plus4);
                skip(P);
                continue;
            }
        }

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

        /* On remet la carte dans la pioche */
        // ...

        /* On vérifie si le joueur n'a plus de carte */
        // ...
        // --nbPlayers

        /* On applique l'effet de la carte si présent */
        applyEffect(C, P, &plus2, &plus4);

        /* Joueur suivant */
        skip(P);
    }

    /* Il reste plus qu'un joueur */
    // affichage des gagnants (par ordre)
    // ...
}

void applyEffect(Carte C, Players P, int *plus2, int *plus4)
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
        if (checkCardExist(P->next->player, C)) //si le prochain joueur a un +2
            *plus2 += 2;
        else
        {
            plusX(P->next->player, *plus2);
            skip(P);
        }
        break;
    case 13: //changement de couleur
        break;
    case 14: //+4
        if (checkCardExist(P->next->player, C)) //si le prochain joueur a un +4
            *plus4 += 4;
        else
        {
            plusX(P->next->player, *plus4);
            skip(P);
        }
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

int checkCardExist(Player P, Carte C)
{
    for (int i = 0; i < P->totalCard; i++)
        if (P->cartes[i].num == C.num)
            return 1;
    return 0;
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