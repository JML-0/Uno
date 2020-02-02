#include "rules.h"
#include "pile.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void GenerateDeck()
{
    int i = 0;
    for (i = 0; i < 13; i++) //Rouge
    {
        Carte carte;
        carte.color = R;
        carte.Num = i;
        
        push(carte);
        if (i > 0)
            push(carte);
    }

    for (int j = 0; j < 13; j++, i++) //Bleu
    {
        Carte carte;
        carte.color = B;
        carte.Num = j;

        push(carte);
        if (j > 0)
            push(carte);
    }

    for (int j = 0; j < 13; j++, i++) //Jaune
    {
        Carte carte;
        carte.color = Y;
        carte.Num = j;

        push(carte);
        if (j > 0)
            push(carte);
    }

    for (int j = 0; j < 13; j++, i++) //Vert
    {
        Carte carte;
        carte.color = G;
        carte.Num = j;

        push(carte);
        if (j > 0)
            push(carte);
    }

    for (int j = 0; j < 5; j++, i++) //Multi
    {
        Carte carte;
        carte.color = M;
        carte.Num = 13;

        push(carte);
    }

    for (int j = 0; j < 5; j++, i++) //+4
    {
        Carte carte;
        carte.color = M4;
        carte.Num = 14;

        push(carte);
    }
}

int main()
{
    GenerateDeck();
    int Rr = 0;
    while(!empty())
    {
        Carte c = pop();
        //printf("%d\n", c.Num);
        if (c.Num == 0) { Rr++; }
    }

    printf("%d\n", Rr);
    
    return 0;
}