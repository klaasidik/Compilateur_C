#ifndef FCHAINE_H_INCLUDED
#define FCHAINE_H_INCLUDED
#define size 200
struct tabch
{
    char tabc[size][200];
};
typedef struct tabch TABC;

struct matricech
{
    TABC tab[size];
};
typedef struct matricech MATC;


#endif // FCHAINE_H_INCLUDED
