#include <stdio.h>
#include <string.h>
#include "bohater.h"
#include "pomocnicze.h"




Bohater utworzBohatera(){
    Bohater b;

    wczytajTekst("Podaj imie bohatera: ", b.imie, 100);
   
    printf("Wybierz rase: \n0-Czlowiek \n1-Elf \n2-Krasnolud\n3-Ork\n4-TIEFLING\n");
    int r = wczytajIntZZakresu("Wybor: ", 0, 4);
    b.rasa = r;

    printf("Wybierz klase: \n0-WOJOWNIK \n1-MAG \n2-KAPLAN\n3-KAPLAN\n4-LOTRZYK\n5-LOWCA\n6-DRUID\n");
    scanf("%d", &k);
    b.klasa = k;

    b.poziom = wczytajIntZZakresu("Podaj poziom (1-100): ", 1, 100);

    b.reputacja = 50;
    b.status = AKTYWNY;

    return b;

}

const char* rasaNaString(Rasa r){
    switch(r){
        case CZLOWIEK:
            return "CZLOWIEK";
        case ELF:
            return "ELF";
        case KRASNOLUD:
            return "KRASNOLUD";
        case ORK:
            return "ORK";
        case TIEFLING:
            return "TIEFLING";
        default: 
            return"Nieznany";
    }

}
const char* klasaNaString(Klasa k){
    switch(k){
        case WOJOWNIK:
            return "WOJOWNIK";
        case MAG:
            return "MAG";
        case KAPLAN:
            return "KAPLAN";
        case LOTRZYK:
            return "LOTRZYK";
        case LOWCA:
            return "LOWCA";
        case DRUID:
            return "DRUID";
        default: 
            return"Nieznany";
    }

}
const char* statusNaString(Status s){
    switch(s){
        case AKTYWNY:
            return "Aktywny";
        case NA_MISJI:
            return "Na misji";
        case RANNY:
            return "Ranny";
        case ZAGINIONY:
            return "Zaginiony";
        default: 
            return"Nieznany";
    }
}

void wypiszBohatera(Bohater b){
    printf("[Bohater: %s] Rasa: %s, Klasa: %s, Poz: %d , Rep: %d, Status: %s\n", b.imie,b.rasa,b.klasa, b.poziom, b.reputacja, b.status );
}