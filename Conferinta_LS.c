//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//typedef struct Conferinta Conferinta;
//
//struct Conferinta {
//	char* titlu;
//	char* domeniu;
//	int anDesfasurare;
//	int nrParticipanti;
//};
//
//typedef struct Nod Nod;
//
//struct Nod {
//	Conferinta info;
//	Nod* next;
//};
//
//void afisareConferinta(Conferinta c)
//{
//	printf("Titlu: %s\n", c.titlu);
//	printf("Domeniu: %s\n", c.domeniu);
//	printf("An desfasurare: %d\n", c.anDesfasurare);
//	printf("Nr participanti: %d\n\n", c.nrParticipanti);
//}
//
//Conferinta initializareConferinta(const char* titlu, const char* domeniu,
//	int anDesfasurare, int nrParticipanti)
//{
//	Conferinta c;
//	c.titlu = (char*)malloc(sizeof(char) * (strlen(titlu) + 1));
//	strcpy_s(c.titlu, strlen(titlu) + 1, titlu);
//
//	c.domeniu = (char*)malloc(sizeof(char) * (strlen(domeniu) + 1));
//	strcpy_s(c.domeniu, strlen(domeniu) + 1, domeniu);
//
//	c.anDesfasurare = anDesfasurare;
//	c.nrParticipanti = nrParticipanti;
//
//	return c;
//}
//
//void afisareListaConferinte(Nod* cap)
//{
//	while (cap)
//	{
//		afisareConferinta(cap->info);
//		cap = cap->next;
//	}
//}
//
//void inserareLaSfarsit(Nod** cap, Conferinta c)
//{
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = c;
//	nou->next = NULL;
//
//	if (*cap == NULL)
//	{
//		*cap = nou;
//	}
//	else
//	{
//		Nod* temp = *cap;
//
//		while (temp->next)
//		{
//			temp = temp->next;
//		}
//		temp->next = nou;
//	}
//}
//
//void dezalocareLista(Nod** cap)
//{
//	while (*cap)
//	{
//		Nod* temp = *cap;
//		(*cap) = (*cap)->next;
//
//		free(temp->info.titlu);
//		free(temp->info.domeniu);
//		free(temp);
//	}
//}
//
//void afisareConferinteDinDomeniu(Nod* cap, const char* domeniuDat)
//{
//	while (cap)
//	{
//		if (strcmp(cap->info.domeniu, domeniuDat) == 0)
//		{
//			afisareConferinta(cap->info);
//		}
//		cap = cap->next;
//	}
//}
//
//Conferinta conferintaCuMultiParticipanti(Nod* cap)
//{
//	int maxim = 0;
//	Conferinta c;
//
//	while (cap)
//	{
//		if (cap->info.nrParticipanti > maxim)
//		{
//			c = initializareConferinta(cap->info.titlu, cap->info.domeniu,
//				cap->info.anDesfasurare, cap->info.nrParticipanti);
//			maxim = cap->info.nrParticipanti;
//		}
//		cap = cap->next;
//	}
//
//	return c;
//}
//
//void stergereConferinteVechi(Nod** cap)
//{
//	while (*cap && (*cap)->info.anDesfasurare < 2024)
//	{
//		Nod* temp = *cap;
//		(*cap) = (*cap)->next;
//
//		free(temp->info.titlu);
//		free(temp->info.domeniu);
//		free(temp);
//	}
//
//	Nod* curent = *cap;
//
//	while (curent && curent->next)
//	{
//		if (curent->next->info.anDesfasurare < 2024)
//		{
//			Nod* temp = curent->next;
//			curent->next = curent->next->next;
//
//			free(temp->info.titlu);
//			free(temp->info.domeniu);
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
//	Conferinta c1 = initializareConferinta("Brand minds", "inteligenta artificiala", 2023, 1500);
//	Conferinta c2 = initializareConferinta("Comic con", "jocuri", 2025, 4000);
//	Conferinta c3 = initializareConferinta("Spring IT", "IT", 2024, 50);
//	Conferinta c4 = initializareConferinta("AI", "inteligenta artificiala", 2023, 2500);
//	Conferinta c5 = initializareConferinta("MTC", "job hub", 2025, 120);
//
//	inserareLaSfarsit(&lista, c1);
//	inserareLaSfarsit(&lista, c2);
//	inserareLaSfarsit(&lista, c3);
//	inserareLaSfarsit(&lista, c4);
//	inserareLaSfarsit(&lista, c5);
//
//	afisareListaConferinte(lista);
//
//	printf("\n-----------------\n");
//	printf("Conferinte din domeniu:\n\n");
//	afisareConferinteDinDomeniu(lista, "inteligenta artificiala");
//	printf("\n-----------------\n");
//
//	Conferinta conferintaMare = conferintaCuMultiParticipanti(lista);
//	printf("Conferinta cu cei mai multi participanti:\n\n");
//	afisareConferinta(conferintaMare);
//	printf("\n-----------------\n");
//
//	stergereConferinteVechi(&lista);
//	printf("Dupa stergere conferinte vechi:\n\n");
//	afisareListaConferinte(lista);
//
//	dezalocareLista(&lista);
//	free(conferintaMare.titlu);
//	free(conferintaMare.domeniu);
//}