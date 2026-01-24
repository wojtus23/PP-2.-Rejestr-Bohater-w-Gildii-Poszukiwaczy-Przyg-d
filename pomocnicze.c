#include <stdio.h>
#include <string.h>
#include "pomocnicze.h"

void oddzielacz()
{
    printf("\n<><><><><><><><><><><><><><><><><><>\n");
}


void wyczyscBufor() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int wczytajInt(const char* komunikat) {
    int liczba;
    printf("%s", komunikat);
    
    
    while (scanf("%d", &liczba) != 1) {
        wyczyscBufor(); 
        printf("Blad! To nie jest liczba. Sprobuj ponownie.\n");
        printf("%s", komunikat); 
    }
    
    wyczyscBufor(); 
    return liczba;
}

int wczytajIntZZakresu(const char* komunikat, int min, int max) {
    int liczba;
    do {
        
        liczba = wczytajInt(komunikat);
        
        if (liczba < min || liczba > max) {
            printf("Blad: Wartosc musi byc z przedzialu %d-%d!\n", min, max);
        }
    } while (liczba < min || liczba > max);
    
    return liczba;
}

void wczytajTekst(const char* komunikat, char* bufor, int rozmiar) {
    printf("%s", komunikat);
    if (fgets(bufor, rozmiar, stdin) != NULL) {
        bufor[strcspn(bufor, "\n")] = 0; 
    } 
    else {
        wyczyscBufor(); 
    }
}

