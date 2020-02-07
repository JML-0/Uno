#include "rules.h"
#ifndef _CONTROLS_H
#define _CONTROLS_H

#ifdef __cplusplus
extern "C" {
#endif

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