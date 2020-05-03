
#include "controls.h"
#include "pile.h"
#include "rules.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int ID = 0;
/** Génère toutes les cartes du UNO dans la pile et mélange la pile. Les numéros de 0 à 9 correspondent aux cartes chiffres de 0 à 9, et celles de 10 à 14 aux malus.
     
	10 : passer le tour du prochain joueur.
	
	11: changement de sens de jeu.
	
	12: +2 (le prochain joueur pioche 2 cartes).
	
	13: changement de couleur.
	
	14: +4 (le joueur choisit une nouvelle couleur et le prochain joueur pioche 4 cartes).
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

/**
 Prend une liste de joueurs en paramètre.
 Crée un nouveau joueur et l'initialise avec un ID unique, un nombre de cartes défini, et une main aléatoire.
 Le joueur créé est ajouté à la liste des joueurs. prout.
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

/**
 Prend la liste des joueurs et un joueur à supprimer en paramètres.
 Si le joueur courant dans la liste est le joueur à supprimer, libère la mémoire allouée au joueur
 et renvoie la nouvelle liste des joueurs, sinon parcourt la liste des joueurs jusqu'à trouver le joueur
 à supprimer. Renvoie la liste des joueurs inchangée si le joueur à supprimer n'est pas trouvé.
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

/** 
 Prend la liste des joueurs en paramètre. 
 Tant que le joueur courant ne vaut pas NULL, affiche son ID, son nombre de cartes et ses cartes, 
 et passe au joueur suivant.
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

/** Prend en paramètre un joueur.
   Permet de faire piocher une carte au joueur passé en paramètre.
   Réalloue de la mémoire pour les cartes du joueur, et y ajoute la carte du dessus de la pioche.
 */ 
void takeCard(Player P)
{
    P->cartes = realloc(P->cartes, sizeof(struct Carte) * (P->totalCard + 1)); assert(P->cartes);
    P->cartes[P->totalCard++] = pop();
}

/** Prend la liste des joueur et un id en paramètres.
   Retourne le joueur dont l'ID est passé en paramètre.
   Parcourt la liste des joueurs. Si l'ID passé en paramètre correspond à celui du joueur courant, retourne ce joueur, sinon passe au joueur suivant.
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

/** Prend en paramètre la liste des joueurs et un entier représentant une position.
   Retourne un joueur depuis sa position dans la structure.
   Parcourt la liste des joueurs en icrémentant au fur et à mesure une variable i jusqu'à pos, et retourne le joueur actuel lorque i vaut pos.
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

/** Retourne 1 si le joueur n'a plus de cartes, 0 sinon.
 */ 
int zeroCard(Player P)
{
    return P->totalCard < 1;
}

/** Fait piocher X carte(s) au joueur P.
   n : carte à piocher en fonction de plusieurs +2 / +4 posés.
   Initialise i à 0. Tant que i est différent de n, fait piocher une carte au joueur P et incrément i.
 */ 
void plusX(Player P, int n)
{
    int i = 0;
    while (i != n) { takeCard(P); i++; }
    printf("Le joueur %d pioche %d cartes.\n", P->id, n);
}

/** Supprime une carte du joueur P.
   card : numéro de carte à supprimer.
   Alloue de la mémoire pour un nouveau tableau de cartes plus petit de 1 carte.
   Parcourt les cartes du joueur P, si le numéro de la carte actuelle n'est pas égal à card, ajoute la carte au nouveau tableau.
   Enfin, change l'ancien tableau de cartes pour le nouveau, et décrémente le nombre total de cartes de P.
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
