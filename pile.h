#include "rules.h"
#ifndef _PILE_H
#define _PILE_H
/*!\brief taille de la pile (statique) */
#define PILE_MAX 108

#ifdef __cplusplus
extern "C" {
#endif

extern void push(Carte v);
extern Carte pop(void);
extern int empty(void);
extern void shuffle(void);

#ifdef __cplusplus
}
#endif

#endif