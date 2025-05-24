//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//typedef struct CarteTarot CarteTarot;
//
//struct CarteTarot {
//	char* nume;
//	int tipArcana;
//	char* simbol;
//	float energie;
//};
//
//typedef struct Nod Nod;
//
//struct Nod {
//	CarteTarot info;
//	Nod* next;
//	Nod* prev;
//};
//
//typedef struct ListaDubla ListaDubla;
//
//struct ListaDubla {
//	Nod* head;
//	Nod* tail;
//};
//
//void afisareCarteTarot(CarteTarot ct)
//{
//	printf("Nume: %s\n", ct.nume);
//	printf("Tip arcana: %d\n", ct.tipArcana);
//	printf("Simbol: %s\n", ct.simbol);
//	printf("Energie: %.2f\n\n", ct.energie);
//}
//
//CarteTarot initializareCarteTarot(const char* nume, int tipArcana,
//	const char* simbol, float energie)
//{
//	CarteTarot ct;
//
//	ct.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
//	strcpy_s(ct.nume, strlen(nume) + 1, nume);
//
//	ct.tipArcana = tipArcana;
//
//	ct.simbol = (char*)malloc(sizeof(char) * (strlen(simbol) + 1));
//	strcpy_s(ct.simbol, strlen(simbol) + 1, simbol);
//
//	ct.energie = energie;
//
//	return ct;
//}
//
//void afisareListaDeLaInceput(ListaDubla lista)
//{
//	Nod* nou = lista.head;
//
//	while (nou)
//	{
//		afisareCarteTarot(nou->info);
//		nou = nou->next;
//	}
//}
//
//void afisareListaDeLaFinal(ListaDubla lista)
//{
//	Nod* nou = lista.tail;
//
//	while (nou)
//	{
//		afisareCarteTarot(nou->info);
//		nou = nou->prev;
//	}
//}
//
//void inserareLaFinal(ListaDubla* lista, CarteTarot ct)
//{
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//
//	nou->info = ct;
//	nou->next = NULL;
//	nou->prev = lista->tail;
//
//	if (!lista->head)
//	{
//		lista->head = nou;
//	}
//	else
//	{
//		lista->tail->next = nou;
//	}
//	lista->tail = nou;
//}
//
//void inserareLaInceput(ListaDubla* lista, CarteTarot ct)
//{
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	
//	nou->info = ct;
//	nou->prev = NULL;
//	nou->next = lista->head;
//
//	if (!lista->tail)
//	{
//		lista->tail = nou;
//	}
//	else
//	{
//		lista->head->prev = nou;
//	}
//	lista->head = nou;
//}
//
//CarteTarot carteCuEnergieMare(ListaDubla lista)
//{
//	int energieMaxima = 0;
//	CarteTarot ct;
//	Nod* nou = lista.head;
//
//	while (nou)
//	{
//		if (nou->info.energie > energieMaxima)
//		{
//			ct = initializareCarteTarot(nou->info.nume, nou->info.tipArcana,
//				nou->info.simbol, nou->info.energie);
//			energieMaxima = nou->info.energie;
//		}
//		nou = nou->next;
//	}
//	return ct;
//}
//
//void dezalocareListaDubla(ListaDubla* lista)
//{
//	Nod* nou = lista->head;
//
//	while (nou->next)
//	{
//		free(nou->info.nume);
//		free(nou->info.simbol);
//
//		nou = nou->next;
//
//		free(nou->prev);
//	}
//	free(nou->info.nume); 
//	free(nou->info.simbol); 
//	free(nou); 
//	
//	lista->head = lista->tail = NULL;
//}
//
//void stergereCartiDupaSimbol(ListaDubla* lista, const char* simbolDat)
//{
//	Nod* temp = lista->head;
//
//	while (temp)
//	{
//		if (strcmp(temp->info.simbol, simbolDat) == 0)
//		{
//			if (temp->prev)
//			{
//				temp->prev->next = temp->next;
//			}
//
//			else
//			{
//				lista->head = temp->next;
//			}
//
//			if (temp->next)
//			{
//				temp->next->prev = temp->prev;
//			}
//			else
//			{
//				lista->tail = temp->prev;
//			}
//
//			free(temp->info.nume);
//			free(temp->info.simbol);
//			free(temp);
//			return;
//		}
//		temp = temp->next;
//	}
//}
//
//int main()
//{
//	ListaDubla lista;
//	lista.head = NULL;
//	lista.tail = NULL;
//
//	CarteTarot ct1 = initializareCarteTarot("The fool", 1, "caine", 20.3);
//	CarteTarot ct2 = initializareCarteTarot("The tower", 1, "turn", 60);
//	CarteTarot ct3 = initializareCarteTarot("The lovers", 1, "inima", 57.53);
//	CarteTarot ct4 = initializareCarteTarot("Three of swords", 0, "sabie", 17);
//	CarteTarot ct5 = initializareCarteTarot("Two of cups", 0, "turn", 43);
//
//	inserareLaFinal(&lista, ct1);
//	inserareLaFinal(&lista, ct2);
//	inserareLaFinal(&lista, ct3);
//	inserareLaFinal(&lista, ct4);
//	inserareLaFinal(&lista, ct5);
//
//	afisareListaDeLaInceput(lista);
//
//	printf("\n------------\n");
//	CarteTarot carteMare = carteCuEnergieMare(lista);
//	printf("Cartea cu cea mai mare energie: \n");
//	afisareCarteTarot(carteMare);
//	printf("\n------------\n");
//	stergereCartiDupaSimbol(&lista, "turn");
//	printf("Dupa stergere: \n");
//	afisareListaDeLaInceput(lista);
//
//	dezalocareListaDubla(&lista);
//	free(carteMare.nume);
//	free(carteMare.simbol);
//}