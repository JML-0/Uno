#include "pile.h"
#include <stdlib.h>
#include <time.h>
#include <assert.h>

/*! \brief indice indiquant le haut de la pile. */
static int _haut = -1;
/*! \brief tableau static utilis´e pour le stockage de la pile. */
static Carte _pile[PILE_MAX];

/*!\brief Empiler la valeur \a v dans la pile.
* \param v la valeur `a empiler */
void push(Carte v) {
    _pile[++_haut] = v;
}

/*!\brief d´epiler et renvoyer la valeur de l’´el´ement en haut de la pile.
* \return la valeur en haut de la pile. */
Carte pop(void) {
    return _pile[_haut--];
}

/*!\brief Indique si la pile est vide.
* \return vrai si la pile est vide, faux sinon. */
int empty(void) {
    return _haut < 0;
}

/*
 * Mélange la pile à chaque appel
 */
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