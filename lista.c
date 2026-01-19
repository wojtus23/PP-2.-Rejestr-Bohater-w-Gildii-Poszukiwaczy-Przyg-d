#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void inicjalizujListe(Listabohaterow* lista){
    lista->head = NULL;
    lista->tail = NULL;
    lista->rozmiar = 0;
}

void dodajBohatera(Listabohaterow* lista, Bohater b){
    Node* nowy = (Node*)malloc(sizeof(Node));
    if(!nowy){
        fprintf(stderr, "Blad : brak pamieci RAM\n");
        return;
    }

    nowy->dane = b;
    nowy->next = NULL;

    if(lista->head ==NULL){
        nowy->prev = NULL;
        lista->head = nowy;
        lista->tail = nowy;
    
    }
    else{
        nowy->prev = lista ->tail;
        lista->tail->next = nowy;
        lista->tail = nowy;
    }
    lista->rozmiar++;
}
void wyswietlWszystkich(const Listabohaterow* lista){
    if(lista->head ==NULL){
        printf("Rejest bohaterow jest pusty\n");
        return;
    }

    printf("Rejestr bohaterow ilosc wpisow: %d", lista->rozmiar);
    Node* current = lista->head;
    while(current != NULL){
        wypiszBohatera(current->dane);
        current = current ->next;
    }

}
void zwolnijListe(Listabohaterow* lista){
    Node* current = lista->head;
    while(current != NULL){
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    lista->head =NULL;
    lista-> tail=NULL;
    lista->rozmiar = 0;
    printf("pamiec listy zwolniona\n");
}

void zapiszDoPliku(const Listabohaterow* lista, const char* nazwaPliku){
    FILE* plik = fopen(nazwaPliku, "w");

    if(plik==NULL){
        return;
        }
    Node* current = lista->head;
    while(current != NULL)
    {
        Bohater b = current->dane;
        fprintf(plik,"%s;%s;%s;%d;%d;%s",b.imie,b.rasa,b.klasa, b.poziom, b.reputacja, b.status);

        current = current -> next;
    }
    fclose(plik);
    printf("Zapisano");
}

void wczytajZPliku(Listabohaterow* lista, const char* nazwaPlik){
    FILE* plik = fopen(nazwaPlik, "r");

    if(plik==NULL){
        return;
    }
    
    Bohater b;
    
    while (scanf(plik, "%100[^;];%d;%d;%d;%d;%d", b.imie,&b.rasa,&b.klasa, &b.poziom, &b.reputacja, &b.status)==6){
        dodajBohatera(lista,b);
    }
    fclose(plik);
    printf("Wczystano");

    
}