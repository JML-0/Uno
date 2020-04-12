#ifndef _CONTROLS_H
#define _CONTROLS_H

#ifdef __cplusplus
extern "C" {
#endif


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
extern Players addPlayer(Players P);
extern void showPlayers(Players P);
extern void takeCard(Player P);
extern Player getPlayer(Players P, int id);
extern Players removePlayer(Players P, Player N);
extern void deleteCard(Player P, int card);
extern Player getPlayerFromPosition(Players P, int pos);

#ifdef __cplusplus
}
#endif

#endif