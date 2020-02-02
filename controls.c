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