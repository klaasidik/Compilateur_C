#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilePRIM.h"
PILE Empiler(char item[],PILE p) {
  if (p.top >= 200 - 1)
       return p;
  p.top++;
  strcpy(p.tab[p.top], item);
  return p;
}
PILE Depiler(PILE p,char item[]) {
  if (p.top == -1)
    return p;
   strcpy(item , p.tab[p.top]);
   p.top--;
   return p;
}
void afficher(PILE p) {
   int i;
   if (p.top == -1)
      printf("\nLa pile est vide!");
   else {
      for (i = p.top; i >= 0; i--)
         printf( p.tab[i]);
   }
}
