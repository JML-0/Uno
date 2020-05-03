
#include "controls.h"
#include "pile.h"
#include "rules.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int ID = 0;
/*
 * Génère aléatoirement toutes les cartes du UNO
 */ 
void generatePile()
{
    int i = 0, j = 0;
    Carte cR, cB, cG, cY, cM, cM4;
    cR.color = R; cB.color = B; cG.color = G; cY.color = Y; cM.color = M; cM.color = M4;

    while (i != PILE_MAX)
    {
        if (j <= 14)
        {
            if (j < 13)
            {
                cR.num = cB.num = cG.num = cY.num = j;
                push(cR); push(cB); push(cG); push(cY);
                if (j > 0) { push(cR); push(cB); push(cG); push(cY); }
            }
            else
            {
                cM.num = j; cM4.num = j;
                push(cM); push(cM); push(cM4); push(cM4);
            }
        }
        i++; j++;
    } shuffle(); //mélange
}

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
        free(P->player->cartes); free(N); free(P);
        return r;
    }
    Players courant = P, prec = P;
    while (courant != NULL)
    {
        if (courant->player == N)
        {
            prec->next = courant->next;
            free(courant->player->cartes); free(N); free(courant);
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
        if (p->id == id) return p;

        tmp = tmp->next;
    }
    return NULL;
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
        if (i == pos) return p;

        tmp = tmp->next;
        i++;
    }
    return NULL;
}

/*
 * Retourne 1 si le joueur n'a plus de carte, sinon 0
 */ 
int zeroCard(Player P)
{
    return P->totalCard < 1;
}

/*
 * Fait piocher X carte(s) au joueur P
 * n : carte à piocher en fonction de plusieurs +2 / +4 posés
 */ 
void plusX(Player P, int n)
{
    int i = 0;
    while (i != n) { takeCard(P); i++; }
    printf("Le joueur %d pioche %d cartes.\n", P->id, n);
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
