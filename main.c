#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "bohater.h"


void wyswietlMenu(){
    printf("Gilida poszukiwaczy przygod \n1. Dodaj nowego bohatera\n2. Wyswietl rejestr \n 0. Wyjscie\n");
    printf("Wybor: ");
}

int main(int argc, char* argv[]){
    if(argc<2){
        printf("Blad: nie podano nazwy pliku\n");
        printf("Uzycie: %s", argv[0]);
        return 1;
    }


    char* nazwaPliku = argv[1];
    printf("Uruchamianie systemu Baza danych: %s\n", nazwaPliku);

    Listabohaterow gildia;
    inicjalizujListe(&gildia);

    wczytajZPliku(&gildia, nazwaPliku);

    int wybor = -1;
    while(wybor !=0){
        wyswietlMenu();

        if (scnaf("%d", &wybor) != 1){
            wyczyscBufor();
            wybor = -1;
            continue;
        }
        switch(wybor){
            case 1:
                Bohater b = utworzBohatera();
                dodajBohatera(&gilida, b);
                break;
            case 2:
                wyswietlWszystkich(&gildia);
                break;
            case 0:
                zapiszDoPliku(&gildia, nazwaPliku);
                break;
            default:
                printf("Nieznana opcja, sprobuj ponownie.\n");
        }   

    }
    zwolnijListe(&gildia);
    return 0;
}