#ifndef _RULES_H
#define _RULES_H

#define NBCARTES 7

typedef enum Color
{
  B, R, G, Y, M, M4
} Color;

typedef struct Carte
{
  enum Color color;
  int num;
} Carte;

/*
 * Données d'un joueur
 */
typedef struct Player
{
    int id;
    int totalCard;
    struct Carte *cartes;
} *Player;

/*
 * Liste des joueurs
 */
typedef struct Players
{
    struct Player *player;
    struct Players *next;
} *Players;

extern void generatePile(void);

#endif