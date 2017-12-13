#define _CRT_SECURE_NO_WARNINGS // Behovs for vissa funktioner i visual studio
#include "HashTable.h"
#include "Bucket.h"
#include<assert.h>
#include<stdlib.h>
#include<stdio.h>
#include "list.h"

#define UNUSED 0	// Anvands for att markera en ledig plats i Hashtabellen


/* Denna funktion tar en nyckel och returnerar ett hash-index
dvs ett index till arrayen som Šr Hashtabellen */
static int hash(Key key, int tablesize)
{
	return key%tablesize;
}

HashTable createHashTable(unsigned int size)
{
	// Dessa tva rader ar bara till for att labskelettet ska kompilera. Ta bort dessa nar du skriver funktionen.
	HashTable htable;
	htable.table = calloc(size, sizeof(struct node));
	htable.size = size;
	for (int i = 0; i < size; i++)
	{
		htable.table[i] = createEmptyList();
	}
	return htable;
}

/* Satter in paret {key,data} i Hashtabellen, om en nyckel redan finns ska vardet uppdateras */
void insertElement(HashTable* htable, const Key key, const Value value)
{
	int index = hash(key, htable->size);
	Data data;
	data.key = key;
	data.value = value;
	if (htable->table[index] != NULL)
	{
		addFirst(&htable->table[index], data);
	}
	else
	{
		addLast(&htable->table[index], data);
	}
	// Postcondition: det finns ett element for key i tabellen (anvand lookup() for att verifiera)
}

/* Tar bort datat med nyckel "key" */
void deleteElement(HashTable* htable, const Key key)
{
	int index = hash(key, htable->size);
	Data data;
	data.key = key;
	removeElement(&htable->table[index], data);

	// Postcondition: inget element med key finns i tabellen (anvand loookup() for att verifiera)
}

/* Returnerar en pekare till vardet som key ar associerat med eller NULL om ingen sadan nyckel finns */
const Value* lookup(const HashTable* htable, const Key key)
{
	int index = hash(key, htable->size);
	Data data;
	data.key = key;
	return search(htable->table[index], data);
}


/* Tommer Hashtabellen */
void freeHashTable(HashTable* htable)
{
	for (int index = 0; index < htable->size; index++)
	{
		clearList(&htable->table[index]);
	}
	htable->size = 0;
	// Postcondition: hashtabellen har storlek 0
}

/* Ger storleken av Hashtabellen */
unsigned int getSize(const HashTable* htable)
{
	return (*htable).size;
}

/* Denna for att ni enkelt ska kunna visualisera en Hashtabell */
void printHashTable(const HashTable* htable)
{
	for (int index = 0; index < htable->size; index++)
	{
		List ptr = htable->table[index];
		while (ptr != NULL)
		{
			printPerson(&ptr->data.value);
			printf("\n");
			ptr = ptr->next;
		}
	}
	// Tips: anvand printPerson() i Person.h for att skriva ut en person
}
