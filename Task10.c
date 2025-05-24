//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//
//typedef struct Carte Carte;
//
//struct Carte {
//	int id;
//	char* titlu;
//	char* autor;
//	int anPublicare;
//	float recenzie;
//};
//
//typedef struct Nod Nod;
//
//struct Nod {
//	Carte info;
//	Nod* st;
//	Nod* dr;
//};
//
//Carte initializareCarte(int id, const char* titlu, const char* autor, int anPublicare, float recenzie) {
//	Carte c;
//
//	c.id = id;
//
//	c.titlu = (char*)malloc(sizeof(char) * (strlen(titlu) + 1));
//	strcpy_s(c.titlu, strlen(titlu) + 1, titlu);
//
//	c.autor = (char*)malloc(sizeof(char) * (strlen(autor) + 1));
//	strcpy_s(c.autor, strlen(autor) + 1, autor);
//
//	c.anPublicare = anPublicare;
//	c.recenzie = recenzie;
//
//	return c;
//}
//
//void afisareCarte(Carte c) {
//	printf("Id: %d\n", c.id);
//	printf("Titlu: %s\n", c.titlu);
//	printf("Autor: %s\n", c.autor);
//	printf("An publicare: %d\n", c.anPublicare);
//	printf("Recenzie: %.2f\n\n", c.recenzie);
//}
//
//void adaugaInArbore(Nod** rad, Carte c) {
//	if (!(*rad))
//	{
//		Nod* nou = (Nod*)malloc(sizeof(Nod));
//		nou->info = c;
//		nou->st = NULL;
//		nou->dr = NULL;
//		(*rad) = nou;
//	}
//	else
//	{
//		if ((*rad)->info.id > c.id)
//			adaugaInArbore(&((*rad)->st), c);
//		else if ((*rad)->info.id < c.id)
//			adaugaInArbore(&((*rad)->dr), c);
//	}
//}
//
//void afisareInOrdine(Nod* rad) {
//	if (rad)
//	{
//		afisareInOrdine(rad->st);
//		afisareCarte(rad->info);
//		afisareInOrdine(rad->dr);
//	}
//}
//
//void stergereCarteDupaId(Nod** rad, int id) {
//	if ((*rad)->info.id > id)
//		stergereCarteDupaId(&(*rad)->st, id);
//	else if ((*rad)->info.id < id)
//		stergereCarteDupaId(&(*rad)->dr, id);
//	else {
//		Nod* temp = *rad;
//		if ((*rad)->st == NULL && (*rad)->dr == NULL)
//			*rad = NULL;
//		else if ((*rad)->st == NULL)
//			*rad = (*rad)->dr;
//		else if ((*rad)->dr == NULL)
//			*rad = (*rad)->st;
//		else {
//			Nod* nou = (*rad)->dr;
//			while (nou->st)
//				nou = nou->st;
//
//			free((*rad)->info.titlu);
//			free((*rad)->info.autor);
//
//			(*rad)->info.id = nou->info.id;
//
//			(*rad)->info.titlu = (char*)malloc(strlen(nou->info.titlu) + 1);
//			strcpy_s((*rad)->info.titlu, strlen(nou->info.titlu) + 1, nou->info.titlu);
//
//			(*rad)->info.autor = (char*)malloc(strlen(nou->info.autor) + 1);
//			strcpy_s((*rad)->info.autor, strlen(nou->info.autor) + 1, nou->info.autor);
//
//			(*rad)->info.anPublicare = nou->info.anPublicare;
//			(*rad)->info.recenzie = nou->info.recenzie;
//
//			stergereCarteDupaId(&(*rad)->dr, nou->info.id);
//			return;
//		}
//		free(temp->info.titlu);
//		free(temp->info.autor);
//		free(temp);
//	}
//}
//
//int inaltime(Nod* rad) {
//	if (!rad) return 0;
//	int hSt = inaltime(rad->st);
//	int hDr = inaltime(rad->dr);
//	return 1 + (hSt > hDr ? hSt : hDr);
//}
//
//Nod* subarboreInalt(Nod* rad) {
//	if (inaltime(rad->st) > inaltime(rad->dr))
//		return rad->st;
//	else
//		return rad->dr;
//}
//
//int nrNoduriSubordine(Nod* rad) {
//	if (!rad)
//		return 0;
//	int st = nrNoduriSubordine(rad->st);
//	int dr = nrNoduriSubordine(rad->dr);
//	return st + dr;
//}
//
//Nod* subarboreCuDescendenti(Nod* rad) {
//	if (nrNoduriSubordine(rad->st) > nrNoduriSubordine(rad->dr))
//		return rad->st;
//	else
//		return rad->dr;
//}
//
//void dezalocareArbore(Nod** rad) {
//	if ((*rad)) {
//		dezalocareArbore(&((*rad)->st));
//		dezalocareArbore(&((*rad)->dr));
//
//		free((*rad)->info.titlu);
//		free((*rad)->info.autor);
//		free((*rad));
//
//		(*rad) = NULL;
//	}
//}
//
//int main() {
//	Nod* rad = NULL;
//
//	Carte c1 = initializareCarte(1, "Baltagul", "Sadoveanu", 1917, 7.65);
//	Carte c2 = initializareCarte(2, "Hamlet", "Shakespeare", 1700, 9);
//	Carte c3 = initializareCarte(3, "Ultima noapte", "Petrescu", 1940, 8.75);
//	Carte c4 = initializareCarte(4, "Morometii", "Preda", 1890, 9.2);
//	Carte c5 = initializareCarte(5, "Iona", "Sorescu", 1955, 6);
//
//	adaugaInArbore(&rad, c1);
//	adaugaInArbore(&rad, c2);
//	adaugaInArbore(&rad, c3);
//	adaugaInArbore(&rad, c4);
//	adaugaInArbore(&rad, c5);
//
//	afisareInOrdine(rad);
//
//	printf("\n---------STERGERE DUPA ID----------------\n");
//
//	stergereCarteDupaId(&rad, 2);
//	afisareInOrdine(rad);
//
//	printf("\n---------SUBARBORE INALT----------------\n");
//
//	Nod* nou = subarboreInalt(rad);
//
//	afisareInOrdine(nou);
//
//	printf("\n---------NODURI IN SUBORDINE----------------\n");
//
//	printf("%d\n", nrNoduriSubordine(rad));
//
//	printf("\n---------RADACINA CU MAI MULTE NODURI IN SUBORDINE----------------\n");
//
//	Nod* subarbore = subarboreCuDescendenti(rad);
//	afisareInOrdine(subarbore);
//
//	dezalocareArbore(&rad);
//}