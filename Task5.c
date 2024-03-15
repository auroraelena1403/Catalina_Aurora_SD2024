//Obiectele pe car ele cititi dintr-un fisier le salvati intr-o lista simplu inlantuita.
// functie care sterge un nod de pe o pozitie data ca parametru. Daca lista are mai putine noduri decat index-ul dat, nu se realizeaza stergerea.
//functie care sa insereze elementele in cadrul listei simplu inlantuite astfel incat acestea a fie sortate crescator dupa un camp la alegerea voastra.
//functie care salveaza intr-un vector toate obiectele care indeplinesc o conditie stabilita de voi. Realizati deep copy, astfel incat elementele din vector sa fie diferentiate de cele din lista. Aveti grija la alocarea de spatiu, deoarece trebuie sa stabiliti pentru cate elemente veti aloca spatiu.
//functie care primeste lista si doua pozitii. In cadrul functiei trebuie sa interschimbati elementele de pe cele doua pozitii din lista primita.
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

struct Student {
	char* nume;
	int varsta;
	int greutate;
	
};

//initializare student
struct Student initializeazStudent(const char* nume, int varsta, int greutate) {
	struct Student copie;
	copie.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(copie.nume, nume);
	copie.varsta = varsta;
	copie.greutate = greutate;
	return copie;

}

//lista
struct Node {
	struct Student info;
	struct Node* next;
};

typedef struct Node Node;
typedef struct Student Student;

//inserare lista
Node* inserareLista(Node* cap, Student student) {
	Node* nou = (Node*)malloc(sizeof(Node));
	nou->info = student;
	nou->next = cap;
	return nou;
}

//citire din fisier
Node*  studentiFisier(const char* numeFisier, Node* lista) {
	if (numeFisier != NULL && strlen(numeFisier) > 0) {
		printf("\n----------------------Dupa inserare din fisier: ---------------------\n");
		FILE* file = fopen(numeFisier, "r");
		if (file != NULL) {
			
			char buffer[100];
			char delimitator[] = ",\n";
			
			while (fgets(buffer, 100, file)!=NULL) {
				Student student;
				char* token;
				token= strtok(buffer, delimitator);
				student.nume = (char*)malloc(strlen(token) + 1);
				strcpy(student.nume, token);
				token = strtok(NULL, delimitator);
				student.varsta = atoi(token);
				token = strtok(NULL, delimitator);
				student.greutate = atoi(token);
				
				
				lista=inserareLista(lista, student);
				
			}
			
		}
		fclose(file);
	}
	return lista;
}
void afisareStudent(Student s) {
	printf("Studentul %s are varsta %d  si greutatea de %d kg\n", s.nume, s.varsta, s.greutate);
}

void afisareLista(Node* cap) {
	while (cap != NULL) {
		afisareStudent(cap->info);
		cap = cap->next;
	}
}
//stergere nod de pe o pozitie data ca parametru.
Node* stegereElDupaPozitie(Node* capLista, int pozitie) {
	int index = 0;
	Node* aux=NULL;
	//cazuri
		//daca pozitia este primul element din lista
	if (pozitie == 1) {
		aux = capLista;
		capLista = capLista->next;
	}
		//daca pozitia este diferita de 1
	if (pozitie > 1) {
		Node* pIndex = capLista;
		while (pIndex && index++ < pozitie - 1) {
			pIndex = pIndex->next;
		}
		if (pIndex&& pIndex->next) {
			aux = pIndex->next;
			pIndex->next = aux->next;
		}
	}
	if (aux) {
		free(aux->info.nume);
		
		free(aux);
	}
	return capLista;
}

//inserare element in lista astfel incat sa fie sortata crescator dupa un camp la alegere
void inserareSiSortareDupaGreutate(Node* capLista, Student student) {
	capLista = inserareLista(capLista,student);
	
	if (capLista != NULL) {
		//Un nod auziliar care va pastra adresa primului nod
		Node* aux = NULL;
		//parcurgere folosing ca inceput adresa nodului auxiliar
		for (aux = capLista; aux; aux = aux->next) {
			//incepand de la adresa primului element
			for (Node* elUrmator = aux; elUrmator; elUrmator = elUrmator->next) {
				//comparam cu elementul cu adresa urmatoare fata de elementul de mai sus
				if (aux->info.greutate > elUrmator->info.greutate) {
					//daca primul element este pus gresit interchimbam folosing var. temporala
					Student temp = aux->info;
					aux->info = elUrmator->info;
					elUrmator->info = temp;
					//schimbam doar informatia din noduri, nu si adresa in sine
				}
			}
		}
	}
	
}
//salvare intr-un vector : obiectele care indeplinesc o conditie stabilita
Student* adaugaInVector(Node* cap, int varsta) {
	int numar=0;
	Node* aux = cap;
	while (aux->next) {
		if (aux->info.varsta > 18) {
			
			numar++;
		}
		aux = aux->next;
	}
	if (aux->info.varsta > 18) numar += 1;
	printf("%d", numar);
	Student* vector =(Student*) malloc(sizeof(Student) * numar);
	Student student;
	for (int i = 0; i < numar; i++) {
		while (cap->next) {
			if (cap->info.varsta > 18) {
				student.nume = (char*)malloc(sizeof(char) * (strlen(cap->info.nume) + 1));
				strcpy(student.nume, cap->info.nume);
				student = initializeazStudent(cap->info.nume, cap->info.varsta, cap->info.greutate);
				/*afisareStudent(student);*/
				vector[i] = student;
				printf("ceva");
				i++;
			}
			cap = cap->next;
			
			
		}
		if (cap->info.varsta > 18) {
			student.nume = (char*)malloc(sizeof(char) * (strlen(cap->info.nume) + 1));
			strcpy(student.nume, cap->info.nume);
			student = initializeazStudent(cap->info.nume, cap->info.varsta, cap->info.greutate);
			vector[i] = cap->info;
		}
		
	}
	return vector;
}
void afisareVector(struct Student* vector, int nr) {
		if (vector != NULL) {
			for (int i = 0; i < nr; i++) {
				afisareStudent(vector[i]);
			}
		}
}

void interschimbareElemente(Node* cap, int pozitie1, int pozitie2) {
	int numarElemente=0;
	Node* contor = cap;
	while (contor) {
		numarElemente++;
		contor = contor->next;
	}
	if (pozitie1 < 0 || pozitie2 < 0 ||pozitie1>numarElemente ||pozitie2>numarElemente) {
		printf("Pozitiile nu exista");
	}
	//nu schimb adresele, doar continutul din noduri
	//imi trebuie pointeri care sa indice catre nodurile de la pozitiile specificate
	Node* temp = cap;
	Node* adresaPoz1 = NULL;
	Node* adresaPoz2 = NULL;
	
		
		for (int i = 0; i < numarElemente-1; i++) {
			while (temp) {
				if (pozitie1 == i) {

					adresaPoz1 = temp;
				}
				if ((pozitie2 - 1) == i) {
					adresaPoz2 = temp->next;
				}
				temp = temp->next;
				i++;
			}
		}
	
	if (adresaPoz1 && adresaPoz2) {
		Student temp = adresaPoz1->info;
		adresaPoz1->info = adresaPoz2->info;
		adresaPoz2->info = temp;
	}
	

}

void main() {
	Student s = initializeazStudent("fghjk", 13, 56);

	Node* listaCap=NULL;
	listaCap = inserareLista(listaCap, s);
	listaCap = studentiFisier("studenti.txt", listaCap);
	afisareLista(listaCap);

	/*printf("\n----------------------Dupa stergere din lista - pozitia 2 : ---------------------\n");
	listaCap = stegereElDupaPozitie(listaCap, 2);
	afisareLista(listaCap);*/

	Student s2 = initializeazStudent("jhabkdjdnakldandkl", 23, 86);
	printf("\n----------------------Dupa inserare in lista si sortare: ---------------------\n");
	inserareSiSortareDupaGreutate(listaCap, s2);
	afisareLista(listaCap);

	Student* studenti = NULL;
	int * dim = 0;
	printf("\n----------------------Dupa criteriu: ---------------------\n");
	studenti=adaugaInVector(listaCap, 18);
	afisareVector(studenti, 5);

	
	printf("\n----------------------Dupa interschimbare in : ---------------------\n");
	interschimbareElemente(listaCap, 1, 3);
	afisareLista(listaCap);
	

}
