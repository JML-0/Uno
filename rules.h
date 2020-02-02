#ifndef _RULES_H
#define _RULES_H

#define LENGTH 8
#define WIDTH 8

typedef enum Color
{
  B, R, G, Y, M, M4
} Color;

typedef struct Carte
{
  Color color;
  int Num;
} Carte;

extern void generatePile(void);

#endif