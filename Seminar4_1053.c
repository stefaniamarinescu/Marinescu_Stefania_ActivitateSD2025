//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct StructuraMasina {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//
//typedef struct StructuraMasina Masina;
//typedef struct Nod Nod;
//
//struct Nod{
//	Masina info;
//	Nod* next;
//};
//Masina citireMasinaDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Masina m1;
//	aux = strtok(buffer, sep);
//	m1.id = atoi(aux);
//	m1.nrUsi = atoi(strtok(NULL, sep));
//	m1.pret = atof(strtok(NULL, sep));
//	aux = strtok(NULL, sep);
//	m1.model = malloc(strlen(aux) + 1);
//	strcpy_s(m1.model, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, sep);
//	m1.numeSofer = malloc(strlen(aux) + 1);
//	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);
//
//	m1.serie = *strtok(NULL, sep);
//	return m1;
//}
//
//void afisareMasina(Masina masina) {
//	printf("Id: %d\n", masina.id);
//	printf("Nr. usi : %d\n", masina.nrUsi);
//	printf("Pret: %.2f\n", masina.pret);
//	printf("Model: %s\n", masina.model);
//	printf("Nume sofer: %s\n", masina.numeSofer);
//	printf("Serie: %c\n\n", masina.serie);
//}
//
//void afisareListaMasini(Nod* cap) {
//	while (cap)
//	{
//		afisareMasina(cap->info);
//		cap = cap->next;
//	}
//}
//
//void adaugaMasinaInLista(Nod** cap, Masina masinaNoua) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = masinaNoua; //o dezalocam- nu; facem shallow copy;
//	nou->next = NULL; // verificam nodul nextator
//
//	if (!*cap)
//	{
//		*cap = nou;
//
//	}
//	else //daca ne deplasam cu cap nu mai putem accesa cele din lista trecuta(ant), facem un nod care se misca, cap ramane tot acolo
//	{
//		Nod* p = *cap;
//		while (p->next)
//		{
//			p = p->next; //adresa nodului nextator, cat timp exista p next ma pot deplasa 
//		}
//		p->next = nou; //gen ma gandesc ca vreau sa merg la nextatorul, nu la null-ul ramas cum ar veni 
//	}
//}
//
//void adaugaLaInceputInLista(Nod** cap, Masina masinaNoua) {
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = masinaNoua;
//	nou->next = *cap;
//	*cap = nou;
//}
//
//Nod* citireListaMasiniDinFisier(const char* numeFisier) {
//	FILE* f = fopen(numeFisier, "r");
//	Nod* lista = NULL;
//	while (!feof(f))
//	{
//		adaugaLaInceputInLista(&lista, citireMasinaDinFisier(f));
//	}
//
//	fclose(f);
//	return lista;
//}
//
//void dezalocareListaMasini(Nod** cap) {
//	while (*cap)
//	{
//		Nod* aux = (*cap);
//		*cap = (*cap)->next;
//		free(aux->info.numeSofer);
//		free(aux->info.model);
//		free(aux);
//	}
//}
//
//float calculeazaPretMediu(Nod* lista) {
//	int count = 0; //cate elem avem in lista 
//	float sum = 0;
//	while (lista) //putem parcurge cu litsa ca e doar o copie
//	{
//		sum += lista->info.pret;
//		count++;
//		lista = lista->next;
//	}
//	return (count > 0) ? sum / count : 0;
//}
//
//void stergeMasiniDinSeria(Nod** listaSimpla, char serieCautata) {
//	while (*listaSimpla && (*listaSimpla)->info.serie == serieCautata) {
//		Nod* temp = *listaSimpla;
//		*listaSimpla = (*listaSimpla)->next;
//		free(temp->info.model);
//		free(temp->info.numeSofer);
//		free(temp);
//	}
//	Nod* curent = *listaSimpla;
//	while (curent && curent->next) {
//		if (curent->next->info.serie == serieCautata) {
//			Nod* temp = curent->next;
//			curent->next = curent->next->next;
//			free(temp->info.model);
//			free(temp->info.numeSofer);
//			free(temp);
//		}
//		else {
//			curent = curent->next;
//		}
//	}
//}
//
//float calculeazaPretulMasinilorUnuiSofer(Nod* lista, const char* numeSofer) {
//	float s = 0;
//	while (lista)
//	{
//
//		if (strcmp(numeSofer, lista->info.numeSofer) == 0)
//		{
//			s += lista->info.pret;
//		}
//		lista = lista->next;
//	}
//	return s;
//}
//
//char* getCeaMaiScumpaMasina(Nod* lista)
//{
//	float pretulMax = 0;
//	float pretulCelMaiMare = 0;
//	char* modelScump = NULL;
//	while (lista)
//	{
//		if (lista->info.pret > pretulMax)
//		{
//			pretulMax = lista->info.pret;
//			modelScump = lista->info.model;
//
//		}
//		lista = lista->next;
//
//	}
//	if (pretulMax > 0)
//	{
//		//luam alt pointer la char
//		char* nou = malloc(strlen(modelScump) + 1);
//		strcpy_s(nou, strlen(modelScump) + 1, modelScump);
//		return nou;
//	}
//}
//
//int main() {
//	Nod* cap = NULL;
//	cap = citireListaMasiniDinFisier("masini.txt");
//	afisareListaMasini(cap);
//	printf("%.2f \n\n", calculeazaPretMediu(cap));
//	printf("%.2f", calculeazaPretulMasinilorUnuiSofer(cap, "Ionescu"));
//	printf("%s", getCeaMaiScumpaMasina(cap));
//	dezalocareListaMasini(&cap);
//	return 0;
//}