#include "rules.h"
#include "pile.h"
#include "controls.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
 * Génère aléatoirement toutes les cartes du UNO
 */ 
void generatePile()
{
    int i = 0, j = 0;
    Carte cR, cB, cG, cY, cM, cM4;
    cR.color = R; cB.color = B; cG.color = G; cY.color = Y; cM.color = M; cM.color = M4;

    while (i != PILE_MAX)
    {
        if (j <= 14)
        {
            if (j < 13)
            {
                cR.Num = cB.Num = cG.Num = cY.Num = j;
                push(cR); push(cB); push(cG); push(cY);
                if (j > 0) { push(cR); push(cB); push(cG); push(cY); }
            }
            else
            {
                cM.Num = j; cM4.Num = j;
                push(cM); push(cM); push(cM4); push(cM4);
            }
        }
        i++; j++;
    } shuffle(); //mélange
}

/*int main()
{
    generatePile();

    while(!empty())
    {
        Carte c = pop();
        printf("%d\n", c.Num);
        //if (c.Num == 12) { Rr++; }
    }
    return 0;*/
}