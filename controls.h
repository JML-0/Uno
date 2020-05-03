#ifndef _CONTROLS_H
#define _CONTROLS_H

#ifdef __cplusplus
extern "C" {
#endif

/// Structure des couleurs. B: Bleu, R: Rouge, G: Vert, Y: Jaune, M: x2, M4: x4.
typedef enum Color
{
  B, R, G, Y, M, M4
} Color;
  
/// Structure d'une carte. Contient une couleur et un numéro.
typedef struct Carte
{
  enum Color color;
  int num;
} Carte;


/// Structure d'un joueur. Contient un id, le nombre total de cartes du joueur, et un tableau de cartes.
typedef struct Player
{
    /// Id du joueur
    int id;
    /// Nombre de cartes du joueur
    int totalCard;
    /// Tableau contenant les cartes du joueur
    struct Carte *cartes;
} *Player;


/// Structure de la liste des joueurs. Contient un pointeur vers le premier joueur de la liste et un pointeur vers le joueur suivant.
typedef struct Players
{
    /// Pointeur vers un joueur
    struct Player *player;
    /// Pointeur vers le joueur suivant
    struct Players *next;
} *Players;

/// Génération de la pile de cartes.
extern void generatePile(void);
/// Ajoute un joueur à la liste des joueurs.
extern Players addPlayer(Players P);
/// Affiche la liste des joueurs.
extern void showPlayers(Players P);
/// Ajoute une carte au joueur passé en argument.
extern void takeCard(Player P);
/// Renvoie le joueur correspondant à l'ID en argument.
extern Player getPlayer(Players P, int id);
/// Supprime un joueur de la liste des joueurs.
extern Players removePlayer(Players P, Player N);
/// Supprime une carte de la main d'un joueur.
extern void deleteCard(Player P, int card);
/// Renvoie le joueur situé à l'index passée en argument.
extern Player getPlayerFromPosition(Players P, int pos);

#ifdef __cplusplus
}
#endif

#endif
