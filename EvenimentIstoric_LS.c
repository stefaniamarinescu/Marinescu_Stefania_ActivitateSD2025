//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//typedef struct Eveniment Eveniment;
//
//struct Eveniment {
//	char* nume;
//	int an;
//	char* locatie;
//	unsigned char importanta;
//};
//
//typedef struct Nod Nod;
//
//struct Nod {
//	Eveniment info;
//	Nod* next;
//};
//
//void afisareEveniment(Eveniment e)
//{
//	printf("Nume: %s\n", e.nume);
//	printf("An: %d\n", e.an);
//	printf("Locatie: %s\n", e.locatie);
//	printf("Importanta: %c\n\n", e.importanta);
//}
//
//Eveniment initializareEveniment(const char* nume, int an, const char* locatie,
//	unsigned char importanta)
//{
//	Eveniment e;
//
//	e.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
//	strcpy_s(e.nume, strlen(nume) + 1, nume);
//
//	e.an = an;
//
//	e.locatie = (char*)malloc(sizeof(char) * (strlen(locatie) + 1));
//	strcpy_s(e.locatie, strlen(locatie) + 1, locatie);
//
//	e.importanta = importanta;
//
//	return e;
//}
//
//void afisareLista(Nod* cap)
//{
//	while (cap)
//	{
//		afisareEveniment(cap->info);
//		cap = cap->next;
//	}
//}
//
//void inserareLaInceput(Nod** cap, Eveniment e)
//{
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = e;
//	nou->next = *cap;
//	*cap = nou;
//}
//
//void dezalocareLista(Nod** cap)
//{
//	while (*cap)
//	{
//		Nod* temp = (*cap);
//		(*cap) = (*cap)->next;
//
//		free(temp->info.nume);
//		free(temp->info.locatie);
//		free(temp);
//	}
//}
//
//void afisareEvenimenteImportante(Nod* cap)
//{
//	while (cap)
//	{
//		if (cap->info.importanta == 'A')
//		{
//			afisareEveniment(cap->info);
//		}
//		cap = cap->next;
//	}
//}
//
//Eveniment evenimentRecent(Nod* cap)
//{
//	int maxim = 0;
//	Eveniment e;
//
//	while (cap)
//	{
//		if (cap->info.an > maxim)
//		{
//			e = initializareEveniment(cap->info.nume, cap->info.an,
//				cap->info.locatie, cap->info.importanta);
//			maxim = cap->info.an;
//		}
//		cap = cap->next;
//	}
//	return e;
//}
//
//void stergereEvenimenteLocatie(Nod** cap, const char* locatieData)
//{
//	while (*cap && strcmp((*cap)->info.locatie, locatieData) == 0)
//	{
//		Nod* temp = (*cap);
//		(*cap) = (*cap)->next; 
//
//		free(temp->info.nume); 
//		free(temp->info.locatie); 
//		free(temp); 
//	}
//
//	Nod* curent = *cap;
//
//	while (curent && curent->next)
//	{
//		if (strcmp(curent->next->info.locatie, locatieData) == 0)
//		{
//			Nod* temp = curent->next;
//			curent->next = curent->next->next;
//
//			free(temp->info.nume);
//			free(temp->info.locatie);
//			free(temp);
//		}
//		else
//		{
//			curent = curent->next;
//		}
//	}
//}
//
//int main()
//{
//	Nod* lista = NULL;
//	Eveniment e1 = initializareEveniment("Batalie", 1440, "Urziceni", 'A');
//	Eveniment e2 = initializareEveniment("Lupta", 1500, "Suceava", 'B');
//	Eveniment e3 = initializareEveniment("Razboi", 2022, "Ucraina", 'A');
//	Eveniment e4 = initializareEveniment("Lupta", 1600, "Suceava", 'C');
//	Eveniment e5 = initializareEveniment("Conflict", 1960, "Ploiesti", 'C');
//
//	inserareLaInceput(&lista, e1);
//	inserareLaInceput(&lista, e2);
//	inserareLaInceput(&lista, e3);
//	inserareLaInceput(&lista, e4);
//	inserareLaInceput(&lista, e5);
//	afisareLista(lista);
//
//	printf("\n-------------\n");
//	printf("Evenimente importante:\n");
//	afisareEvenimenteImportante(lista);
//
//	printf("\n-------------\n");
//	Eveniment evRecent = evenimentRecent(lista);
//	printf("Cel mai recent eveniment:\n");
//	afisareEveniment(evRecent);
//	printf("\n-------------\n");
//	stergereEvenimenteLocatie(&lista, "Suceava");
//	printf("Dupa stergere:\n");
//	afisareLista(lista);
//	
//
//	dezalocareLista(&lista);
//	free(evRecent.nume);
//	free(evRecent.locatie);
//}