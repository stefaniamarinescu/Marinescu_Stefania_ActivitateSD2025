#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMasina {
    int id;
    int nrUsi;
    float pret;
    char* model;
    char* numeSofer;
    unsigned char serie;
};

typedef struct StructuraMasina Masina;
typedef struct Nod Nod;

struct Nod {
    Masina info;
    Nod* next;
};

Masina citireMasinaDinFisier(FILE* file) {
    char buffer[100];
    char sep[3] = ",\n";
    if (!fgets(buffer, 100, file)) return (Masina) { 0 };
    char* aux;
    Masina m1 = { 0 };
    aux = strtok(buffer, sep);
    m1.id = atoi(aux);
    m1.nrUsi = atoi(strtok(NULL, sep));
    m1.pret = atof(strtok(NULL, sep));
    aux = strtok(NULL, sep);
    m1.model = malloc(strlen(aux) + 1);
    strcpy(m1.model, aux);
    aux = strtok(NULL, sep);
    m1.numeSofer = malloc(strlen(aux) + 1);
    strcpy(m1.numeSofer, aux);
    m1.serie = *strtok(NULL, sep);
    return m1;
}

void afisareMasina(Masina masina) {
    printf("Id: %d\n", masina.id);
    printf("Nr. usi : %d\n", masina.nrUsi);
    printf("Pret: %.2f\n", masina.pret);
    printf("Model: %s\n", masina.model);
    printf("Nume sofer: %s\n", masina.numeSofer);
    printf("Serie: %c\n\n", masina.serie);
}

void afisareListaMasini(Nod* cap) {
    while (cap) {
        afisareMasina(cap->info);
        cap = cap->next;
    }
}

void adaugaMasinaInLista(Nod** cap, Masina masinaNoua) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = masinaNoua;
    nou->next = NULL;
    if (*cap == NULL) {
        *cap = nou;
    }
    else {
        Nod* temp = *cap;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = nou;
    }
}

Nod* citireListaMasiniDinFisier(const char* numeFisier) {
    FILE* f = fopen(numeFisier, "r");
    Nod* cap = NULL;
    while (!feof(f)) {
        Masina m = citireMasinaDinFisier(f);
        if (m.model && m.numeSofer)
            adaugaMasinaInLista(&cap, m);
    }
    fclose(f);
    return cap;
}

void dezalocareListaMasini(Nod** cap) {
    while (*cap) {
        Nod* p = (*cap);
        (*cap) = (*cap)->next;
        free(p->info.model);
        free(p->info.numeSofer);
        free(p);
    }
}

void stergeNodDupaPozitie(Nod** cap, int pozitie) {
    if (*cap == NULL || pozitie < 0) return;
    Nod* temp = *cap;
    if (pozitie == 0) {
        *cap = temp->next;
        free(temp->info.model);
        free(temp->info.numeSofer);
        free(temp);
        return;
    }
    for (int i = 0; temp != NULL && i < pozitie - 1; i++) {
        temp = temp->next;
    }
    if (temp == NULL || temp->next == NULL) return;
    Nod* p = temp->next;
    temp->next = p->next;
    free(p->info.model);
    free(p->info.numeSofer);
    free(p);
}

void inserareSortataDupaPret(Nod** cap, Masina masinaNoua) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = masinaNoua;
    nou->next = NULL;

    if (*cap == NULL || (*cap)->info.pret > masinaNoua.pret) {
        nou->next = *cap;
        *cap = nou;
        return;
    }
    Nod* temp = *cap;

    while (temp->next && temp->next->info.pret < masinaNoua.pret) {
        temp = temp->next;
    }

    nou->next = temp->next;
    temp->next = nou;
}

Masina* extrageMasiniPestePret(Nod* cap, float prag, int* dimVector) {
    *dimVector = 0;
    Nod* temp = cap;
    while (temp) {
        if (temp->info.pret > prag)
            (*dimVector)++;
        temp = temp->next;
    }
    if (*dimVector == 0)
    {
        return NULL;
    }

    Masina* vector = malloc(sizeof(Masina) * (*dimVector));
    int index = 0;
    temp = cap;

    while (temp) {
        if (temp->info.pret > prag) {
            vector[index].id = temp->info.id;
            vector[index].nrUsi = temp->info.nrUsi;
            vector[index].pret = temp->info.pret;
            vector[index].model = _strdup(temp->info.model);
            vector[index].numeSofer = _strdup(temp->info.numeSofer);
            vector[index].serie = temp->info.serie;
            index++;
        }
        temp = temp->next;
    }
    return vector;
}

void interschimbaElemente(Nod* cap, int poz1, int poz2) {
    if (poz1 == poz2 || cap == NULL) return;
    Nod* nod1 = (Nod*)malloc(sizeof(Nod));
    Nod* nod2 = (Nod*)malloc(sizeof(Nod));
    int index = 0;
    while (cap) {
        if (index == poz1)
        {
            nod1 = cap;
        }

        if (index == poz2)
        {
            nod2 = cap;
        }

        cap = cap->next;
        index++;
    }
    if (nod1 && nod2) {
        Masina temp = nod1->info;
        nod1->info = nod2->info;
        nod2->info = temp;
    }
}

int main() {
    Nod* masini = citireListaMasiniDinFisier("masini.txt");

    afisareListaMasini(masini);

    printf("--------------------\n");
    stergeNodDupaPozitie(&masini, 2);
    printf("Dupa stergere la pozitia 2: \n");
    afisareListaMasini(masini);

    printf("--------------------\n");
    Masina noua = { 15, 4, 18500, _strdup("Mokka"), _strdup("Mihai"), 'Z' };
    inserareSortataDupaPret(&masini, noua);
    printf("Dupa inserare sortata dupa pret: \n");
    afisareListaMasini(masini);

    printf("--------------------\n");
    int dim = 0;
    Masina* vector = extrageMasiniPestePret(masini, 10000, &dim);
    for (int i = 0; i < dim; i++) {
        afisareMasina(vector[i]);
        free(vector[i].model);
        free(vector[i].numeSofer);
    }
    free(vector);

    printf("--------------------\n");
    interschimbaElemente(masini, 0, 1);
    afisareListaMasini(masini);

    dezalocareListaMasini(&masini);
    return 0;
}
