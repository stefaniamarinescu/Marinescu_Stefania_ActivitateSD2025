#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Vrajitor Vrajitor;

struct Vrajitor {
	char* nume;
	int nivelPutere;
	int varsta;
	char* putere;
};

typedef struct Nod Nod;

struct Nod {
	Vrajitor info;
	Nod* next;
};

void afisareVrajitor(Vrajitor v)
{
	printf("Nume: %s\n", v.nume);
	printf("Nivel putere: %d\n", v.nivelPutere);
	printf("Varsta: %d\n", v.varsta);
	printf("Putere: %s\n\n", v.putere);
}

Vrajitor initializareVrajitor(const char* nume, int nivelPutere, int varsta, const char* putere)
{
	Vrajitor v;

	v.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy_s(v.nume, strlen(nume) + 1, nume);

	v.nivelPutere = nivelPutere;
	v.varsta = varsta;

	v.putere = (char*)malloc(sizeof(char) * (strlen(putere) + 1));
	strcpy_s(v.putere, strlen(putere) + 1, putere);

	return v;
}

void afiseazaLista(Nod* cap)
{
	while (cap)
	{
		afisareVrajitor(cap->info);
		cap = cap->next;
	}
}

void inserareLaFinal(Nod** cap, Vrajitor v)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = v;
	nou->next = NULL;

	if (*cap == NULL)
	{
		*cap = nou;
	}
	else
	{
		Nod* temp = *cap;

		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = nou;
	}
}

void dezalocareLista(Nod** cap)
{
	while (*cap)
	{
		Nod* temp = *cap;
		(*cap) = (*cap)->next;

		free(temp->info.nume);
		free(temp->info.putere);
		free(temp);
	}
}

Vrajitor vrajitorPutereMare(Nod* cap)
{
	int putereMaxima = 0;
	Vrajitor v;

	while (cap)
	{
		if (cap->info.nivelPutere > putereMaxima)
		{
			v = initializareVrajitor(cap->info.nume, cap->info.nivelPutere,
				cap->info.varsta, cap->info.putere);
			putereMaxima = cap->info.nivelPutere;
		}
		cap = cap->next;
	}
	return v;
}

void stergeVrajitorDupaNume(Nod** cap, const char* numeCautat)
{
	while (*cap && strcmp((*cap)->info.nume, numeCautat) == 0)
	{
			Nod* temp = *cap;
			(*cap) = (*cap)->next;

			free(temp->info.nume);
			free(temp->info.putere);
			free(temp);
		
	}
	Nod* curent = *cap;

	while (curent && curent->next)
	{
		if (strcmp(curent->next->info.nume, numeCautat) == 0)
		{
			Nod* temp = curent->next;
			curent->next = curent->next->next;

			free(temp->info.nume);
			free(temp->info.putere);
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
	Nod* lista = NULL;

	Vrajitor v1 = initializareVrajitor("Gandalf", 95, 60, "foc");
	Vrajitor v2 = initializareVrajitor("Sauron", 20, 30, "aer");
	Vrajitor v3 = initializareVrajitor("Smeagol", 99, 100, "apa");
	Vrajitor v4 = initializareVrajitor("Frodo", 15, 20, "pamant");
	Vrajitor v5 = initializareVrajitor("Merlin", 84, 250, "apa");

	inserareLaFinal(&lista, v1);
	inserareLaFinal(&lista, v2);
	inserareLaFinal(&lista, v3);
	inserareLaFinal(&lista, v4);
	inserareLaFinal(&lista, v5);

	afiseazaLista(lista);

	printf("\n-----------\n");
	Vrajitor vrajitorPuternic = vrajitorPutereMare(lista);
	printf("Vrajitorul cu cea mai mare putere: \n");
	afisareVrajitor(vrajitorPuternic);

	printf("\n-----------\n");
	stergeVrajitorDupaNume(&lista, "Frodo");
	printf("Dupa stergere: \n");
	afiseazaLista(lista); 

	dezalocareLista(&lista);
	free(vrajitorPuternic.nume);
	free(vrajitorPuternic.putere);
}