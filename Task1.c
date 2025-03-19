//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//
//struct Campus {
//	int id;
//	char* universitate;
//	int nrCladiri;
//};
//
//struct Campus initializare(int id, const char* universitate, int nrCladiri)
//{
//	struct Campus c;
//	/*printf("Introduceti ID: \n");
//	scanf("%d", &id);*/
//	c.id = id;
//	c.universitate = (char*)malloc(strlen(universitate) + 1);
//	strcpy_s(c.universitate, strlen(universitate) + 1, universitate);
//	c.nrCladiri = nrCladiri;
//
//	return c;
//}
//
//void afisare(struct Campus c)
//{
//	printf("ID: %d\n", c.id);
//	printf("Universitate: %s\n", c.universitate);
//	printf("Numar cladiri: %d\n", c.nrCladiri);
//
//}
//
//void dezalocare(struct Campus* c)
//{
//	if (c->universitate != NULL)
//	{
//		free(c->universitate);
//		c->universitate = NULL;
//	}
//}
//
//int main()
//{
//	struct Campus c;
//	c = initializare(1, "ASE", 10);
//	afisare(c);
//
//	dezalocare(&c);
//	return 0;
//}