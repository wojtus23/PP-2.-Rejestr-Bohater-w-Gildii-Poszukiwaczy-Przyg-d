#include <stdio.h>
#include <string.h>
#include "bohater.h"

void wyczyscBufor(){
    int c;
    while ((c=getchar()) != '\n');
}


Bohater utworzBohatera(){
    Bohater b;

    printf("Podaj imie bohatera: ");
    fgets(b.imie, 100, stdin);
    b.imie[strcspn(b.imie, "\n")] = 0;

    int r, k;
    printf("Wybierz rase: \n0-Czlowiek \n1-Elf \n2-Krasnolud\n3-Ork\n4-TIEFLING\n");
    scanf("%d", &r);
    b.rasa = r;

    printf("Wybierz klase: \n0-Wojownik\n1-Mag\n2-Kaplan\n3-Lotrzyk\n4-Lowca\n5-Druid\n");
    scanf("%d", &k);
    b.klasa = k;

    printf("Podaj poziom (1-100): ");
    scanf("%d", &b.poziom);

    b.reputacja = 50;
    b.status = AKTYWNY;


    wyczyscBufor();
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