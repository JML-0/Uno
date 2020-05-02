#ifndef _UNO_H
#define _UNO_H

#ifdef __cplusplus
extern "C" {
#endif

/// Fonction principale de jeu, prend en paramètre le nombre de joueurs.
void jouer(int nbJoueurs);
/// Prend en paramètre un joueur et affiche ses cartes.
void afficherLeDeck(Player P);
/// Prend une carte en paramètre et l'affiche.
void afficherCarte(Carte carte);
/// Menu du jeu qui demande le nombre de joueurs et lance la fonction jouer.
void menu();
/// Fonction qui remplit le tableau entrée en parametre de "-1" pour dire qu'il est vide.
void remplirTab(int * tab, int taille);
/// A supprimer ?
void afficherTab(int * tab, int taille);
/// Fonction qui return 1 si l'id entrée en parametre apartient au tableau entrée en parametre sinon return 0.
int appartientTab(int * tab, int taille, int id);
/// Prend en paramètre le joueur qui a joué, le sens de jeu et le nombre de joueurs. Renvoie l'id du prochain joueur on fonction du sens.
int tour(int joueurActuel,int sensNormal, int nbJoueurs);

#ifdef __cplusplus
}
#endif

#endif
