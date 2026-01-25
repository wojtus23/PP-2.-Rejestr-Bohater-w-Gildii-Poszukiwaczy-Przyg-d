#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    printf("Rejestr gildi ilosc wpisow: %d \n", lista->rozmiar);
    Node* current = lista->head;
    while(current != NULL){
        wypiszBohatera(current->dane);
        current = current ->next;
    }
    printf("-----------------------------------------\n");

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
        printf("Blad otwarcia pliku do zapisu");
        return;
        }
    Node* current = lista->head;
    while(current != NULL)
    {
        Bohater b = current->dane;
        fprintf(plik,"%s;%d;%d;%d;%d;%d\n",b.imie,b.rasa,b.klasa, b.poziom, b.reputacja, b.status);

        current = current -> next;
    }
    fclose(plik);
    printf("Zapisano\n");
}

void wczytajZPliku(Listabohaterow* lista, const char* nazwaPlik){
    FILE* plik = fopen(nazwaPlik, "r");

    if(plik==NULL){
        printf("Info: Plik '%s' nie istnieje. Baza zostanie utworzona przy zapisie.\n", nazwaPlik);
        return;
    }
    
    Bohater b;
    int r, k, s;
    int licznik = 0;
    
    while (fscanf(plik, " %100[^;];%d;%d;%d;%d;%d", b.imie,&r,&k, &b.poziom, &b.reputacja, &s)==6){

        if (b.poziom < 1) b.poziom = 1;
        if (b.poziom > 100) b.poziom = 100;

        if (b.reputacja < 0) b.reputacja = 0;
        if (b.reputacja > 100) b.reputacja = 100;

        b.rasa = r;
        b.klasa = k;
        b.status = s;

        if(znajdzBohateraDokladnie(lista, b.imie) == NULL) {
            dodajBohatera(lista, b);
            licznik++;
        }
    }
    fclose(plik);
    printf("Wczytano %d bohaterow z pliku.\n", licznik);

    
}

Node* znajdzBohatera(const Listabohaterow* lista, const char* imie) {
    if(imie ==NULL) return NULL;

    Node* current = lista->head;
    size_t dlugoscSzukana = strlen(imie); 
    if (dlugoscSzukana == 0) return NULL;

    while (current != NULL) {
        if (strncmp(current->dane.imie, imie, dlugoscSzukana) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL; 
}

int usunBohatera(Listabohaterow* lista, const char* imie) {
    Node* wezel = znajdzBohateraDokladnie(lista, imie);
    
    if (wezel == NULL) {
        printf("Blad: Nie znaleziono bohatera o dokladnym imieniu '%s'.\n", imie);
        return 1;
    }
    if (wezel->dane.status == NA_MISJI) {
        printf("Blad: Bohater '%s' jest NA MISJI! Nie mozna go usunac.\n", imie);
        return 1;
    }
    if (wezel->prev != NULL) {
        wezel->prev->next = wezel->next;
    } 
    else {
        
        lista->head = wezel->next;
    }
    if (wezel->next != NULL) {
        wezel->next->prev = wezel->prev;
    } 
    else {
        
        lista->tail = wezel->prev;
    }

    free(wezel);
    lista->rozmiar--;
    
    printf("Usunieto bohatera '%s'.\n", imie);
    return 0;
}


int usunWszystkichOStatusie(Listabohaterow* lista, Status statusDoUsuniecia) {
    if (statusDoUsuniecia == NA_MISJI) {
        printf("Blad: Nie mozna grupowo usuwac bohaterow NA MISJI.\n");
        return 0;
    }

    Node* current = lista->head;
    int licznik = 0;
    while (current != NULL) {
        Node* nastepny = current->next;
        if (current->dane.status == statusDoUsuniecia) {
            if (current->prev != NULL) current->prev->next = current->next;
            else lista->head = current->next;

            if (current->next != NULL) current->next->prev = current->prev;
            else lista->tail = current->prev;

            free(current);
            lista->rozmiar--;
            licznik++;
        }
        current = nastepny;
    }
    printf("Usunieto %d bohaterow o statusie %d.\n", licznik, statusDoUsuniecia);
    return licznik;
}

int usunWszystkichORasie(Listabohaterow* lista, Rasa rasaDoUsuniecia) {
    Node* current = lista->head;
    int licznik = 0;
    while (current != NULL) {
        Node* nastepny = current->next;
        if (current->dane.rasa == rasaDoUsuniecia && current->dane.status != NA_MISJI) {
            if (current->prev != NULL) current->prev->next = current->next;
            else lista->head = current->next;

            if (current->next != NULL) current->next->prev = current->prev;
            else lista->tail = current->prev;

            free(current);
            lista->rozmiar--;
            licznik++;
        }
        current = nastepny;
    }
    printf("Usunieto %d bohaterow wybranej rasy.\n", licznik);
    return licznik;
}

int usunWszystkichOKlasie(Listabohaterow* lista, Klasa klasaDoUsuniecia) {
    Node* current = lista->head;
    int licznik = 0;
    while (current != NULL) {
        Node* nastepny = current->next;
        if (current->dane.klasa == klasaDoUsuniecia && current->dane.status != NA_MISJI) {
            if (current->prev != NULL) current->prev->next = current->next;
            else lista->head = current->next;

            if (current->next != NULL) current->next->prev = current->prev;
            else lista->tail = current->prev;

            free(current);
            lista->rozmiar--;
            licznik++;
        }
        current = nastepny;
    }
    printf("Usunieto %d bohaterow wybranej klasy.\n", licznik);
    return licznik;
}

int usunWszystkichPonizejPoziomu(Listabohaterow* lista, int progPoziomu) {
    Node* current = lista->head;
    int licznik = 0;
    while (current != NULL) {
        Node* nastepny = current->next;
        if (current->dane.poziom < progPoziomu && current->dane.status != NA_MISJI) {
            if (current->prev != NULL) current->prev->next = current->next;
            else lista->head = current->next;

            if (current->next != NULL) current->next->prev = current->prev;
            else lista->tail = current->prev;

            free(current);
            lista->rozmiar--;
            licznik++;
        }
        current = nastepny;
    }
    printf("Usunieto %d slabych bohaterow (poziom < %d).\n", licznik, progPoziomu);
    return licznik;
}

int usunWszystkichPonizejReputacji(Listabohaterow* lista, int progReputacji) {
    Node* current = lista->head;
    int licznik = 0;
    while (current != NULL) {
        Node* nastepny = current->next;
        if (current->dane.reputacja < progReputacji && current->dane.status != NA_MISJI) {
            if (current->prev != NULL) current->prev->next = current->next;
            else lista->head = current->next;

            if (current->next != NULL) current->next->prev = current->prev;
            else lista->tail = current->prev;

            free(current);
            lista->rozmiar--;
            licznik++;
        }
        current = nastepny;
    }
    printf("Usunieto %d bohaterow ze zla reputacja (< %d).\n", licznik, progReputacji);
    return licznik;
}

static void ZamianaDanych(Node* a, Node* b){
    Bohater temp = a->dane;
    a->dane = b->dane;
    b->dane = temp;
}

void sortujBohaterow(Listabohaterow * lista, KryteriumSortowania kryterium)
{
    if(lista->head ==NULL || lista->head->next == NULL){
        return;
    }

    int zamiana;
    Node* pwsk;
    Node* owsk = NULL;

    do {
        zamiana = 0;
        pwsk = lista->head;

        while (pwsk->next != owsk) {
            int trzebaZamienic = 0;
            Bohater b1 = pwsk->dane;
            Bohater b2 = pwsk->next->dane;

            switch (kryterium) {
                case SORT_IMIE_ROS:
                    if (strcmp(b1.imie, b2.imie) > 0) trzebaZamienic = 1;
                    break;
                case SORT_IMIE_MAL:
                    if (strcmp(b1.imie, b2.imie) < 0) trzebaZamienic = 1;
                    break;
                case SORT_POZIOM_ROS:
                    if (b1.poziom > b2.poziom) trzebaZamienic = 1;
                    break;
                case SORT_POZIOM_MAL:
                    if (b1.poziom < b2.poziom) trzebaZamienic = 1;
                    break;
                case SORT_REPUTACJA_ROS:
                    if (b1.reputacja > b2.reputacja) trzebaZamienic = 1;
                    break;
                case SORT_REPUTACJA_MAL:
                    if (b1.reputacja < b2.reputacja) trzebaZamienic = 1;
                    break;
            }

            if (trzebaZamienic) {
                ZamianaDanych(pwsk, pwsk->next);
                zamiana = 1;
            }
            pwsk = pwsk->next;
        }
        owsk = pwsk;
    } while (zamiana);
    
}

void wyswietlPoKlasie(const Listabohaterow* lista, Klasa szukanaKlasa) {
    printf("\nWYNIKI FILTROWANIA (Klasa: %s)\n", klasaNaString(szukanaKlasa));
    int znaleziono = 0;
    Node* current = lista->head;
    while(current != NULL) {
        if (current->dane.klasa == szukanaKlasa) {
            wypiszBohatera(current->dane);
            znaleziono++;
        }
        current = current->next;
    }
    if (znaleziono == 0) printf("Brak bohaterow tej klasy.\n");
}

void wyswietlPoPoziomie(const Listabohaterow* lista, int szukanyPoziom) {
    printf("\n--- WYNIKI WYSZUKIWANIA (Poziom: %d) ---\n", szukanyPoziom);
    int znaleziono = 0;
    Node* current = lista->head;
    while(current != NULL) {
        if (current->dane.poziom == szukanyPoziom) {
            wypiszBohatera(current->dane);
            znaleziono++;
        }
        current = current->next;
    }
    if (znaleziono == 0) printf("Brak bohaterow o tym poziomie.\n");
}

Node* znajdzBohateraDokladnie(const Listabohaterow* lista, const char* imie) {
    if(imie == NULL) return NULL;

    Node* current = lista->head;
    while (current != NULL) {
        if (strcmp(current->dane.imie, imie) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL; 
}

int wyswietlPasujacychPrefiks(const Listabohaterow* lista, const char* prefiks) {
    if (prefiks == NULL || strlen(prefiks) == 0) return 0;
    
    Node* current = lista->head;
    int licznik = 0;
    size_t len = strlen(prefiks);

    printf("\n--- WYNIKI WYSZUKIWANIA DLA '%s' ---\n", prefiks);
    
    while (current != NULL) {
        
        if (strncmp(current->dane.imie, prefiks, len) == 0) {
            wypiszBohatera(current->dane);
            licznik++;
        }
        current = current->next;
    }
    
    if (licznik == 0) {
        printf("Nie znaleziono zadnych pasujacych bohaterow.\n");
    } 
    else {
        printf("Znaleziono lacznie: %d\n", licznik);
    }
    return licznik;
}