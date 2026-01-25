#ifndef LISTA_H
#define LISTA_H

#include "bohater.h"

typedef struct Node{
    Bohater dane;
    struct Node* next;
    struct Node* prev;
} Node;

typedef enum{
    SORT_IMIE_ROS,
    SORT_IMIE_MAL,
    SORT_POZIOM_ROS,
    SORT_POZIOM_MAL,
    SORT_REPUTACJA_ROS,
    SORT_REPUTACJA_MAL
} KryteriumSortowania;

typedef struct{
    Node* head;
    Node* tail;
    int rozmiar;
} Listabohaterow;


void inicjalizujListe(Listabohaterow* lista);
void dodajBohatera(Listabohaterow* lista, Bohater b);
void wyswietlWszystkich(const Listabohaterow* lista);
int wyswietlPasujacychPrefiks(const Listabohaterow* lista, const char* prefiks);
void zwolnijListe(Listabohaterow* lista);

void zapiszDoPliku(const Listabohaterow* lista, const char* nazwaPliku);
void wczytajZPliku(Listabohaterow* lista, const char* nazwaPliku);

Node* znajdzBohatera(const Listabohaterow* lista, const char* imie);

Node* znajdzBohateraDokladnie(const Listabohaterow* lista, const char* imie);

int usunBohatera(Listabohaterow* lista, const char* imie);
int usunWszystkichOStatusie(Listabohaterow* lista, Status statusDoUsuniecia);
int usunWszystkichORasie(Listabohaterow* lista, Rasa rasaDoUsuniecia);
int usunWszystkichOKlasie(Listabohaterow* lista, Klasa klasaDoUsuniecia);
int usunWszystkichPonizejPoziomu(Listabohaterow* lista, int progPoziomu);
int usunWszystkichPonizejReputacji(Listabohaterow* lista, int progReputacji);


void sortujBohaterow(Listabohaterow* lista, KryteriumSortowania kryterium);

void wyswietlPoKlasie(const Listabohaterow* lista, Klasa szukanaKlasa);
void wyswietlPoPoziomie(const Listabohaterow* lista, int szukanyPoziom);

#endif