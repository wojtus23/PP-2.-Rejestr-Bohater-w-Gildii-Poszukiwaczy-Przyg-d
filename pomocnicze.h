#ifndef POMOCNICZE_H
#define POMOCNICZE_H

void oddzielacz();
void wyczyscBufor();
int wczytajInt(const char* komunikat);
int wczytajIntZZakresu(const char* komunikat, int min, int max);
void wczytajTekst(const char* komunikat, char* bufor, int rozmiar);


#endif