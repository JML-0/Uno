#include "pile.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int ID = 0;
Players add(Players P)
{
    Player newPlayer;
    
    newPlayer.id = ID++;
    newPlayer.cartes = malloc(sizeof(struct Carte) * NBCARTES); assert(newPlayer.cartes);
    for (int i = 0; i < 7; i++)
        newPlayer.cartes[i] = pop();

    Players p = malloc(sizeof(struct Players)); assert(p);
    p->player = newPlayer;
    p->next = P;

    return p;
}

void showPlayers(Players P)
{
    Players tmp = P;
    while (tmp != NULL)
    {
        Player p = tmp->player;
        printf("ID : %d \nCartes:\n", p.id);
        for (int i = 0; i < 7; i++)
            printf("%d\n", p.cartes[i].num);
        
        tmp= tmp->next;
    }
}