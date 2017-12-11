#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Bucket.h"
#include "List.h" // Avkommentera denna rad ifall du vill implementera Hashtabellen med lankade listor

typedef struct 
{
	// Steg 1: Avkommentera exakt en av dessa rader
	
	//struct Bucket* table; // Avkommentera denna ifall ni vill implementera Hashtabellen med oppen adresering
	List* table;   // Avkommentera denna ifall ni vill implemenetera Hashtabellen som en array lankade listor
	
	unsigned int size; // Storleken på Hashtabellen
} HashTable;


HashTable createHashTable(unsigned int size);

/* Satter in paret {key,data} i Hashtabellen, om en nyckel redan finns ska vardet modifieras */
void insertElement(HashTable* htable, const Key key, const Value value);

/* Tar bort datat med nyckel "key" */
void deleteElement(HashTable* htable, const Key key);

/* Returnerar en pekare till vardet som key ar associerat med eller NULL om ingen sadan nyckel finns */
const Value* lookup(const HashTable* htable, const Key key);

/* Tommer Hashtabellen */
void freeHashTable(HashTable* htable);

/* Ger storleken av Hashtabellen */
unsigned int getSize(const HashTable* htable);

/* Denna for att ni enkelt ska kunna visualisera en Hashtabell */
void printHashTable(const HashTable* htable); 

#endif
