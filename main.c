#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "bohater.h"


void wyswietlMenu(){
    printf("Gilida poszukiwaczy przygod \n1. Dodaj nowego bohatera\n2. Wyswietl rejestr \n 0. Wyjscie\n");
    printf("3. Zanjdz i edytuj bohatera \n");
    printf("4. Usun bohatera\n");
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
            case 3:
                char szukane[100];
                printf("Podaj imie bohatera do edycji: ");
                int c; 
                while ((c = getchar()) != '\n');
                fgets(szukane, 100, stdin);
                szukane[strcspn(szukane, "\n")] = 0;

                Node* wynik = znajdzBohatera(&gildia, szukane);
                if (wynik != NULL) {
                    printf("Znaleziono!\n");
                    wypiszBohatera(wynik->dane);
                    
                    printf("\nCo chcesz zmienic?\n");
                    printf("1. Poziom\n2. Reputacje\n3. Status\nWybor: ");
                    int opcjaEdycji;
                    scanf("%d", &opcjaEdycji);
                    
                    if (opcjaEdycji == 1) {
                        printf("Nowy poziom: ");
                        scanf("%d", &wynik->dane.poziom);
                    } else if (opcjaEdycji == 2) {
                        printf("Nowa reputacja (0-100): ");
                        scanf("%d", &wynik->dane.reputacja);
                    } else if (opcjaEdycji == 3) {
                        printf("Nowy status (0-Aktywny, 1-Misja, 2-Ranny, 3-Zaginiony): ");
                        int s;
                        scanf("%d", &s);
                        wynik->dane.status = s;
                    }
                    printf("Dane zaktualizowane.\n");
                } 
                else{
                    printf("Nie znaleziono takiego bohatera.\n");
                }
                break;
            case 4:
                char doUsuniecia[100];
                printf("Podaj imie bohatera do usuniecia: ");
                int c; 
                while ((c = getchar()) != '\n');
                fgets(doUsuniecia, 100, stdin);
                doUsuniecia[strcspn(doUsuniecia, "\n")] = 1;

                usunBohatera(&gildia, doUsuniecia);
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