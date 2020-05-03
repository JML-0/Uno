#include "controls.h"
#include "pile.h"
#include "rules.h"
#include "uno.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("== TESTS UNITAIRE==\n\n\n=> Fichier controls.c\n\n");

    /*
    *   => Controls.c
    */

    printf("1) Génération d'une pile de cartes avec generatePile()\n");
    generatePile();
    printf("-- OK --\n\n");

    printf("2) Création d'une structure Players et création d'un nouveau joueur avec addPlayer()\n");
    Players P = NULL;
    P = addPlayer(P);
    printf("-- OK --\n\n");

    printf("3) Cherche le premier joueur dans la structure Players avec getPlayer(), ajout d'une carte au joueur avec takeCard() et montre les joeurs de la structure avec showPlayers() \n");
    printf("-> getplayer()\n");
    Player player = getPlayer(P, 0);
    printf("-> AVANT (ajout d'une carte)\n");
    showPlayers(P);
    printf("-> APRES (ajout d'une carte)\n");
    takeCard(player);
    showPlayers(P);
    printf("-- OK --\n\n");
    
    printf("4) Selection avec getPlayerFromPosition(), suppresion de la première carte du deck avec deleteCard() et montre les joeurs de la structure avec showPlayers()\n");
    printf("-> getPlayerFromPosition() -> première position\n");
    player = getPlayerFromPosition(P, 0);
    printf("-> AVANT (suppresion de la carte)\n");
    showPlayers(P);
    printf("-> APRES (suppresion de la carte)\n");
    deleteCard(player, player->cartes->num);
    showPlayers(P);
    printf("-- OK --\n\n");

    printf("5) Ajout d'un joueur avec addPlayer(), selection avec getPlayer(), suppresion d'un joueur avec removePlayer() et montre les joeurs de la structure avec showPlayers()\n");
    printf("-> addPlayer()\n");
    P = addPlayer(P);
    printf("-> getplayer()\n");
    player = getPlayer(P, 0);
    printf("-> AVANT (suppresion du joueur)\n");
    showPlayers(P);
    printf("-> APRES (suppresion du joueur)\n");
    P = removePlayer(P, player);
    showPlayers(P);
    printf("-- OK --\n\n");

    /*
    *   => pile.c
    */
    printf("\n=> Fichier pile.c\n\n");

    printf("1) Met aléatoirement les éléments dans la pile avec shuffle() \n");
    shuffle();
    printf("-- OK --\n\n");

    printf("2) Enlève une carte de la pile avec pop() \n");
    Carte carte = pop();
    printf("-- OK --\n\n");

    printf("3) Ajoute une carte enlevé précedement avec push() \n");
    push(carte);
    printf("-- OK --\n\n");
   
   printf("\n== FIN DU TEST ==\n");
}