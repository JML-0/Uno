#ifndef _CONTROLS_H
#define _CONTROLS_H

#ifdef __cplusplus
extern "C" {
#endif

int ID = 0;

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
extern Players addPlayer(Players);
extern void showPlayers(Players);
extern void takeCard(Player);
extern Player getPlayer(Players, int);
extern Players removePlayer(Players, Player);
extern void deleteCard(Player, int);
extern Player getPlayerFromPosition(Players P, int pos);

#ifdef __cplusplus
}
#endif

#endif