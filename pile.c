#include "controls.h"
#include "pile.h"
#include "rules.h"
#include <stdlib.h>
#include <time.h>
#include <assert.h>

/// indice indiquant le haut de la pile.
static int _haut = -1;
/// tableau statique utilisé pour le stockage de la pile. 
static Carte _pile[PILE_MAX];

/// Empiler la carte v dans la pile.
void push(Carte v) {
    _pile[++_haut] = v;
}

/// Dépiler et renvoyer la valeur de l’élément en haut de la pile. Retourne la valeur en haut de la pile.
Carte pop(void) {
    return _pile[_haut--];
}

/// Indique si la pile est vide. Retourne 1 si la pile est vide, 0 sinon. 
int empty(void) {
    return _haut < 0;
}

/// Mélange la pile à chaque appel.
void shuffle()
{
    srand(time(NULL));
    if (PILE_MAX > 1) 
    {
        size_t i;
        for (i = 0; i < PILE_MAX - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (PILE_MAX - i) + 1);
          Carte t = _pile[j];
          _pile[j] = _pile[i];
          _pile[i] = t;
        }
    } 
}
