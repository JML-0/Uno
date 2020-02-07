#include "pile.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int ID = 0;
/*
 * Ajoute un joueur
 */ 
Players addPlayer(Players P)
{
    Player newPlayer = malloc(sizeof(Player)); assert(newPlayer);
    
    newPlayer->id = ID++;
    newPlayer->totalCard = NBCARTES;
    newPlayer->cartes = malloc(sizeof(struct Carte) * NBCARTES); assert(newPlayer->cartes);
    for (int i = 0; i < NBCARTES; i++)
        newPlayer->cartes[i] = pop();

    Players p = malloc(sizeof(struct Players)); assert(p);
    p->player = newPlayer;
    p->next = P;

    return p;
}

/*
 * Supprime un joueur
 */ 
Players removePlayer(Players P, Player N)
{
    if (P->player == N)
    {
        Players r = P->next;
        free(P->player->cartes); free(P);
        return r;
    }
    Players courant = P, prec = P;
    while (courant != NULL)
    {
        if (courant->player == N)
        {
            prec->next = courant->next;
            free(courant->player->cartes); free(courant);
            return P;
        }
        prec = courant;
        courant = courant->next;
    }
    return P;
}

/*
 * Affiche les joueurs et leurs infos
 */ 
void showPlayers(Players P)
{
    Players tmp = P;
    while (tmp != NULL)
    {
        Player p = tmp->player;
        printf("ID : %d \nCartes:\n", p->id);
        printf("total -> %d\n", p->totalCard);
        
        for (int i = 0; i < p->totalCard; i++)
            printf("%d\n", p->cartes[i].num);
        
        tmp= tmp->next; printf("\n");
    }
}

/*
 * Fait piocher une carte à un joueur
 */ 
void takeCard(Player P)
{
    P->cartes = realloc(P->cartes, sizeof(struct Carte) * (P->totalCard + 1)); assert(P->cartes);
    P->cartes[P->totalCard++] = pop();
}

/*
 * Retourne un joueur
 */ 
Player getPlayer(Players P, int id)
{
    Players tmp = P; Player p;
    while (tmp != NULL)
    {
        p = tmp->player;
        if (p->id == id) break;

        tmp = tmp->next;
    }
    return p;
}

/*
 * Retourne un joueur depuis sa position dans la structure
 */ 
Player getPlayerFromPosition(Players P, int pos)
{
    Players tmp = P; Player p;
    int i = 0;
    while (tmp != NULL)
    {
        p = tmp->player;
        if (i == pos) break;

        tmp = tmp->next;
        i++;
    }
    return p;
}

/*
 * Retourne 1 si le joueur n'a plus de carte, sinon 0
 */ 
int zeroCard(Player P)
{
    if (P->totalCard) return 0;
    return 1;
}

/*
 * Fait piocher X carte(s) au joueur P
 * n : carte à piocher en fonction de plusieurs +2 / +4 posés
 */ 
void plusX(Player P, int n)
{
    int i = 0;
    while (i != n) { takeCard(P); i++; }
}

/*
 * Supprime une carte du joueur P
 * card : numéro de carte à supprimer
 */ 
void deleteCard(Player P, int card)
{
    Carte *newCard = malloc(sizeof(struct Carte) * (P->totalCard - 1)); assert(newCard);

    for (int i = 0, j = 0, v = 0; i < P->totalCard; i++)
    {
        if (P->cartes[i].num != card)
            newCard[j++] = P->cartes[i];
        else
            if (v) newCard[j++] = P->cartes[i];
            else v++;
    }
    free(P->cartes);
    P->cartes = newCard;
    P->totalCard--;
}