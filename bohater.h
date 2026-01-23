#ifndef BOHATER_H
#define BOHATER_H

#include <stdio.h>

typedef enum{
    CZLOWIEK,
    ELF,
    KRASNOLUD,
    ORK,
    TIEFLING
} Rasa;

typedef enum{
    WOJOWNIK,
    MAG,
    KAPLAN,
    LOTRZYK,
    LOWCA,
    DRUID
} Klasa;

typedef enum{
    AKTYWNY,
    NA_MISJI,
    RANNY,
    ZAGINIONY,
    ZAWIESZONY
} Status;

typedef struct{
    char imie[101];
    Rasa rasa;
    Klasa klasa;
    int poziom;
    int reputacja;
    Status status;
} Bohater;

Bohater utworzBohatera();
void wypiszBohatera(Bohater b);
void wyczyscBufor();

const char* rasaNaString(Rasa r);
const char* klasaNaString(Klasa k);
const char* statusNaString(Status s);


#endif