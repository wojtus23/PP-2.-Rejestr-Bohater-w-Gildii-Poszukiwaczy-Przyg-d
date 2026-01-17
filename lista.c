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