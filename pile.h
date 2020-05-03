#ifndef _PILE_H
#define _PILE_H

#ifdef __cplusplus
extern "C" {
#endif
  
/// Ajoute une carte à la pile.
extern void push(Carte v);
/// Retourne la carte au-dessus de la pile, et la retire.
extern Carte pop(void);
/// Retourne 1 si la pile est vide, 0 sinon.
extern int empty(void);
/// Mélange la pile.
extern void shuffle(void);
  
#ifdef __cplusplus
}
#endif

#endif
