#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AplicatieMobila AplicatieMobila;

struct AplicatieMobila {
	char* denumire;
	float marimeMB;
	int nrDescarcari;
	int anLansare;
};

typedef struct Nod Nod;

struct Nod {
	AplicatieMobila info;
	Nod* next;
};

void afisareAplicatieMobila(AplicatieMobila apl) {
	printf("Denumire: %s\n", apl.denumire);
	printf("Marime (MB): %.2f\n", apl.marimeMB);
	printf("Numar descarcari: %d\n", apl.nrDescarcari);
	printf("An lansare: %d\n\n", apl.anLansare);
}

AplicatieMobila initializareAplicatie(const char* denumire, float marimeMB,
	int nrDescarcari, int anLansare) {
	AplicatieMobila apl;

	apl.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
	strcpy_s(apl.denumire, strlen(denumire) + 1, denumire);
	apl.marimeMB = marimeMB;
	apl.nrDescarcari = nrDescarcari;
	apl.anLansare = anLansare;

	return apl;
}

void afisareListaAplicatii(Nod* cap) {
	while (cap)
	{
		afisareAplicatieMobila(cap->info);
		cap = cap->next;
	}
}

void inserareLaInceput(Nod** cap, AplicatieMobila apl) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = apl;
	nou->next = *cap;
	*cap = nou;
}

void dezalocareLista(Nod** cap)
{
	while (*cap) {
		Nod* aux = (*cap);
		(*cap) = (*cap)->next;

		free(aux->info.denumire);
		free(aux);
	}
}

AplicatieMobila aplicatieCuSpatiuMic(Nod* cap)
{
	Nod* p = cap;
	float minim = p->info.marimeMB;
	AplicatieMobila apl;

	while (cap)
	{
		if (cap->info.marimeMB < minim)
		{
			apl.denumire = (char*)malloc(sizeof(char) * 
				(strlen(cap->info.denumire) + 1));
			strcpy_s(apl.denumire, strlen(cap->info.denumire) + 1, 
				cap->info.denumire);
			minim = cap->info.marimeMB;
			apl.marimeMB = cap->info.marimeMB;
			apl.nrDescarcari = cap->info.nrDescarcari;
			apl.anLansare = cap->info.anLansare;
		}
		cap = cap->next;
	}
	return apl;
}

void stergereAplicatieDupaDenumire(Nod** cap, const char* denumire)
{
	while (*cap && strcmp((*cap)->info.denumire, denumire) == 0)
	{
		Nod* temp = *cap;
		*cap = (*cap)->next;

		free(temp->info.denumire);
		free(temp);
	}

	Nod* curent = *cap;

	while (curent && curent->next)
	{
		if (strcmp(curent->next->info.denumire, denumire) == 0)
		{
			Nod* temp = curent->next;
			curent->next = curent->next->next;

			free(temp->info.denumire);
			free(temp);
		}
		else
		{
			curent = curent->next;
		}
	}
}

int main()
{
	Nod* listaAplicatii = NULL;

	AplicatieMobila app1 = initializareAplicatie("WhatsApp", 200.35, 3800, 2017);
	AplicatieMobila app2 = initializareAplicatie("Glovo", 150, 2000, 2014);
	AplicatieMobila app3 = initializareAplicatie("Bolt", 80.5, 1750, 2019);
	AplicatieMobila app4 = initializareAplicatie("Netflix", 175, 9000, 2011);
	AplicatieMobila app5 = initializareAplicatie("Facebook", 345.78, 9976, 1998);
	inserareLaInceput(&listaAplicatii, app1);
	inserareLaInceput(&listaAplicatii, app2);
	inserareLaInceput(&listaAplicatii, app3);
	inserareLaInceput(&listaAplicatii, app4);
	inserareLaInceput(&listaAplicatii, app5);

	afisareListaAplicatii(listaAplicatii);
	printf("\n-----------------\n");
	printf("Aplicatia cu cel mai putin spatiu este: \n");
	AplicatieMobila appMica = aplicatieCuSpatiuMic(listaAplicatii);
	afisareAplicatieMobila(appMica);

	printf("\n-----------------\n");
	stergereAplicatieDupaDenumire(&listaAplicatii, "WhatsApp");
	printf("Dupa stergere: \n");
	afisareListaAplicatii(listaAplicatii);

	dezalocareLista(&listaAplicatii);
	free(appMica.denumire);
}