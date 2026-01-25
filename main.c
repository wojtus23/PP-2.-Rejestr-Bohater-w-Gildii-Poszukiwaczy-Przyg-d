#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "bohater.h"
#include "pomocnicze.h"

void wyswietlMenu(){
    oddzielacz();
    printf("     GILDIA POSZUKIWACZY PRZYGOD      \n");
    oddzielacz();
    printf("1. Dodaj nowego bohatera\n");
    printf("2. Wyswietl rejestr\n");
    printf("3. Znajdz bohatera\n"); 
    printf("4. Edytuj bohatera\n");            
    printf("5. Usun bohatera\n");              
    printf("6. Sortuj liste\n");               
    printf("7. Filtruj liste\n");              
    printf("0. Wyjscie\n");
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

        wybor = wczytajInt("Wybor: ");

        switch(wybor){
            case 1: {
                Bohater b = utworzBohatera();
                dodajBohatera(&gildia, b);
                break;

            }
            case 2: {

            }
                wyswietlWszystkich(&gildia);
                break;
            case 3:{
                char szukane[100];
                wczytajTekst("Podaj imie bohatera: ", szukane, 100);

                Node* wynik = znajdzBohatera(&gildia, szukane);
                if (wynik != NULL) {
                    printf("Znaleziono!\n");
                    wypiszBohatera(wynik->dane);
                } else {
                    printf("Nie znaleziono bohatera.\n");
                }
                break;
            }   
            case 4: {
                char szukane[100];
                wczytajTekst("Podaj imie bohatera do edycji: ", szukane, 100);

                Node* wynik = znajdzBohatera(&gildia, szukane);
                if (wynik != NULL) {
                    printf("Znaleziono!\n");
                    wypiszBohatera(wynik->dane);
                    
                    printf("\nCo chcesz zmienic?\n");
                    printf("1. Poziom\n2. Reputacje\n3. Status\nWybor: ");
                    int opcjaEdycji = wczytajIntZZakresu("Wybor: ", 1, 3);
                    
                    if (opcjaEdycji == 1) {
                        wynik->dane.poziom = wczytajIntZZakresu("Nowy poziom (1-100): ", 1, 100);
                    } else if (opcjaEdycji == 2) {
                        wynik->dane.reputacja = wczytajIntZZakresu("Nowa reputacja (0-100): ", 0, 100);
                    } else if (opcjaEdycji == 3) {
                        int s = wczytajIntZZakresu("Podaj status: ", 0, 3);
                        wynik->dane.status = s;
                    }
                    printf("Dane zaktualizowane.\n");
                } 
                else{
                    printf("Nie znaleziono takiego bohatera.\n");
                }
                break;
            }
            case 5: {
                char doUsuniecia[100];
                wczytajTekst("Podaj imie bohatera do usuniecia: ", doUsuniecia, 100);
                

                usunBohatera(&gildia, doUsuniecia);
                break;

            }
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