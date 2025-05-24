#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ComandaOnline ComandaOnline;

struct ComandaOnline {
	int id;
	char* produs;
	float pret;
	char* status;
};

typedef struct Nod Nod;

struct Nod {
	ComandaOnline info;
	Nod* next;
	Nod* prev;
};

typedef struct ListaDubla ListaDubla;

struct ListaDubla {
	Nod* head;
	Nod* tail;
};

void afisareComanda(ComandaOnline c)
{
	printf("ID comanda: %d\n", c.id);
	printf("Produs: %s\n", c.produs);
	printf("Pret: %.2f\n", c.pret);
	printf("Status: %s\n\n", c.status);
}

ComandaOnline initializareComanda(int id, const char* produs, float pret,
	const char* status)
{
	ComandaOnline c;
	
	c.id = id;
	
	c.produs = (char*)malloc(sizeof(char) * (strlen(produs) + 1));
	strcpy_s(c.produs, strlen(produs) + 1, produs);

	c.pret = pret;

	c.status = (char*)malloc(sizeof(char) * (strlen(status) + 1));
	strcpy_s(c.status, strlen(status) + 1, status);

	return c;
}

void inserareLaFinal(ListaDubla* lista, ComandaOnline c)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = c;
	nou->next = NULL;
	nou->prev = lista->tail;

	if (!lista->head)
	{
		lista->head = nou;
	}
	else
	{
		lista->tail->next = nou;
	}
	lista->tail = nou;
}

void afisareLista(ListaDubla lista)
{
	Nod* nou = lista.head;

	while (nou)
	{
		afisareComanda(nou->info);
		nou = nou->next;
	}
}

void afisareDupaStatus(ListaDubla lista, const char* statusDat)
{
	Nod* nou = lista.head;

	while (nou)
	{
		if (strcmp(nou->info.status, statusDat) == 0)
		{
			afisareComanda(nou->info);
		}
		nou = nou->next;
	}
}

void dezalocareLista(ListaDubla* lista)
{
	Nod* temp = lista->head;

	while (temp->next)
	{
		free(temp->info.produs);
		free(temp->info.status);
		temp = temp->next;

		free(temp->prev);
	}

	free(temp->info.produs);
	free(temp->info.status);
	free(temp);

	lista->head = lista->tail = NULL;
}

void stergereComandaDupaStatus(ListaDubla* lista, const char* statusDat)
{
	Nod* temp = lista->head;

	while (temp)
	{
		Nod* urmator = temp->next;

		if (strcmp(temp->info.status, statusDat) == 0)
		{
			if (temp->prev)
			{
				temp->prev->next = temp->next;
			}
			else
			{
				lista->head = temp->next;
			}

			if (temp->next)
			{
				temp->next->prev = temp->prev;
			}
			else
			{
				lista->tail = temp->prev;
			}

			free(temp->info.produs);
			free(temp->info.status);
			free(temp);
		
		temp = urmator;
	}
}


int main()
{
	ListaDubla lista;
	lista.head = NULL;
	lista.tail = NULL;

	ComandaOnline c1 = initializareComanda(1, "Telefon", 1500, "livrata");
	ComandaOnline c2 = initializareComanda(2, "Televizor", 3000, "anulata");
	ComandaOnline c3 = initializareComanda(3, "PS5", 2800, "livrata");
	ComandaOnline c4 = initializareComanda(4, "Tricou", 49.99, "anulata");
	ComandaOnline c5 = initializareComanda(5, "Blender", 300, "livrata");

	inserareLaFinal(&lista, c1);
	inserareLaFinal(&lista, c2);
	inserareLaFinal(&lista, c3);
	inserareLaFinal(&lista, c4);
	inserareLaFinal(&lista, c5);

	afisareLista(lista);

	printf("\n--------------\n");
	printf("Afisare dupa status: \n\n");
	afisareDupaStatus(lista, "livrata");

	printf("\n--------------\n");
	printf("Afisare dupa status: \n\n");
	afisareDupaStatus(lista, "anulata");

	printf("\n--------------\n");
	printf("Dupa stergere: \n\n");
	stergereComandaDupaStatus(&lista, "anulata");
	afisareLista(lista);

	dezalocareLista(&lista);
}