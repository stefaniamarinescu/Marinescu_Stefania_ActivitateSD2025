#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Carte Carte;

struct Carte {
	int id;
	char* titlu;
	char* autor;
	int anPublicare;
	float recenzie;
};

typedef struct Nod Nod;

struct Nod {
	Carte info;
	Nod* next;
	Nod* prev;
};

typedef struct ListaDubla ListaDubla;

struct ListaDubla {
	Nod* head;
	Nod* tail;
};


typedef struct NodLS NodLS;

typedef struct NodLS {
	Carte info;
	NodLS* next;
};


Carte initializareCarte(int id, const char* titlu, const char* autor, int anPublicare, float recenzie) {
	Carte c;

	c.id = id;

	c.titlu = (char*)malloc(sizeof(char) * (strlen(titlu) + 1));
	strcpy_s(c.titlu, strlen(titlu) + 1, titlu);

	c.autor = (char*)malloc(sizeof(char) * (strlen(autor) + 1));
	strcpy_s(c.autor, strlen(autor) + 1, autor);

	c.anPublicare = anPublicare;
	c.recenzie = recenzie;

	return c;
}

void afisareCarte(Carte c) {
	printf("Id: %d\n", c.id);
	printf("Titlu: %s\n", c.titlu);
	printf("Autor: %s\n", c.autor);
	printf("An publicare: %d\n", c.anPublicare);
	printf("Recenzie: %.2f\n\n", c.recenzie);
}

void afisareListaDeLaInceput(ListaDubla lista)
{
	Nod* nou = lista.head;

	while (nou)
	{
		afisareCarte(nou->info);
		nou = nou->next;
	}
}

void afisareListaDeLaFinal(ListaDubla lista)
{
	Nod* nou = lista.tail;

	while (nou)
	{
		afisareCarte(nou->info);
		nou = nou->prev;
	}
}

void inserareCuSortare(ListaDubla* lista, Carte c) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->next = NULL;
	nou->prev = NULL;

	if (!lista->head) {
		lista->head = lista->tail = nou;
		return;
	}

	Nod* p = lista->head;
	while (p && p->info.anPublicare < c.anPublicare)
		p = p->next;

	if (!p) {

		nou->prev = lista->tail;
		lista->tail->next = nou;
		lista->tail = nou;
	}
	else if (p == lista->head) { 

		nou->next = lista->head;
		lista->head->prev = nou;
		lista->head = nou;
	}
	else {

		nou->prev = p->prev;
		nou->next = p;
		p->prev->next = nou;
		p->prev = nou;
	}
}


void inserareLaInceput(ListaDubla* lista, Carte c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));

	nou->info = c;
	nou->prev = NULL;
	nou->next = lista->head;

	if (!lista->tail)
	{
		lista->tail = nou;
	}
	else
	{
		lista->head->prev = nou;
	}
	lista->head = nou;
}

void stergereDupaPozitie(ListaDubla* lista, int poz) {
	Nod* p = lista->head;

	for (int i = 1; i < poz; i++)
		p = p->next;

	if (p->prev)
		p->prev->next = p->next;
	else
		lista->head = p->next;

	if (p->next)
		p->next->prev = p->prev;
	else
		lista->tail = p->prev;

	free(p->info.titlu);
	free(p->info.autor);
	free(p);
}

NodLS* cartiDupaRecenzie(ListaDubla lista) {
	Nod* p = lista.head;
	NodLS* cap = NULL;
	NodLS* ultim = NULL;

	while (p) {
		if (p->info.recenzie > 8) {
			Carte copie = initializareCarte(p->info.id, p->info.titlu, p->info.autor, p->info.anPublicare,
				p->info.recenzie);

			NodLS* nou = (NodLS*)malloc(sizeof(NodLS));
			nou->info = copie;
			nou->next = NULL;

			if (!cap) {
				cap = ultim = nou;
			}
			else {
				ultim->next = nou;
				ultim = nou;
			}
		}
		p = p->next;
	}

	return cap;
}

void afisareListaSimpla(NodLS* cap) {
	while (cap) {
		afisareCarte(cap->info);
		cap = cap->next;
	}
}

void interschimbarePozitii(ListaDubla* lista, int poz1, int poz2) {
	if (poz1 == poz2) return;

	Nod* p1 = lista->head;
	Nod* p2 = lista->head;

	for (int i = 0; i < poz1; i++)
		p1 = p1->next;

	for (int i = 0; i < poz2; i++)
		p2 = p2->next;

	Carte temp = p1->info;
	p1->info = p2->info;
	p2->info = temp;
}


void dezalocare(ListaDubla* lista) {
	Nod* nou = lista->head;

	while (nou->next)
	{
		free(nou->info.titlu);
		free(nou->info.autor);
		nou = nou->next;
		free(nou->prev);
	}
	free(nou->info.titlu);
	free(nou->info.autor);
	free(nou);

	lista->head = lista->tail = NULL;
}

void dezalocareListaSimpla(NodLS* cap) {
	while (cap) {

		NodLS* temp = cap;

		free(cap->info.titlu);
		free(cap->info.autor);

		cap = cap->next;
		free(temp);
	}
}


int main() {
	ListaDubla lista;
	lista.head = NULL;
	lista.tail = NULL;

	Carte c1 = initializareCarte(1, "Baltagul", "Sadoveanu", 1917, 7.65);
	Carte c2 = initializareCarte(2, "Hamlet", "Shakespeare", 1700, 9);
	Carte c3 = initializareCarte(3, "Ultima noapte", "Petrescu", 1940, 8.75);
	Carte c4 = initializareCarte(4, "Morometii", "Preda", 1890, 9.2);
	Carte c5 = initializareCarte(5, "Iona", "Sorescu", 1955, 6);

	printf("\n-----------------CERINTA 2-----------------------\n");

	inserareCuSortare(&lista, c1);
	inserareCuSortare(&lista, c2);
	inserareCuSortare(&lista, c3);
	inserareCuSortare(&lista, c4);
	inserareCuSortare(&lista, c5);

	afisareListaDeLaInceput(lista);

	printf("\n-----------------CERINTA 1------------------------\n");

	stergereDupaPozitie(&lista, 2);
	afisareListaDeLaInceput(lista);

	printf("\n-----------------CERINTA 4-----------------------\n");

	NodLS* listaSimpla = cartiDupaRecenzie(lista);

	afisareListaSimpla(listaSimpla);

	printf("\n-----------------CERINTA 5-----------------------\n");

	interschimbarePozitii(&lista, 0, 2);
	afisareListaDeLaInceput(lista);


	dezalocareListaSimpla(listaSimpla);
	dezalocare(&lista);
}