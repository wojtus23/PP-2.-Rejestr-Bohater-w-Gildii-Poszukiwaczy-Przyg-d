#ifndef LISTA_H
#define LISTA_H

#include "bohater.h"

typedef struct Node{
    Bohater dane;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct{
    Node* head;
    Node* tail;
    int rozmiar;
} Listabohaterow;

void inicjalizujListe(Listabohaterow* lista);
void dodajBohatera(Listabohaterow* lista, Bohater b);
void wyswietlWszystkich(const Listabohaterow* lista);
void zwolnijListe(Listabohaterow* lista);

void zapiszDoPliku(const Listabohaterow* lista, const char* nazwaPliku);
void wczytajZPliku(Listabohaterow* lista, const char* nazwaPliku);

Node* znajdzBohatera(const Listabohaterow* lista, const char* imie);
int usunBohatera(Listabohaterow* lista, const char* imie);

#endif