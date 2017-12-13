#define _CRT_SECURE_NO_WARNINGS // Behovs i Visual studio for att tillata vissa funktioner
#include "HashTable.h"

#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "Person.h"


static int addRandomPersonToTable(HashTable* htable);
void test(unsigned int tableSize);

int main(void)
{
	unsigned int size;
	do
	{
		printf("Hashtabellens storlek (minst 50): ");
		scanf("%u", &size); //det ar onskvart att lata storleken vara ett primtal
	} while (size < 50);

	test(size);

	// Fšr att pausa
	getch();

	return 0;
}

static int addRandomPersonToTable(HashTable* htable)
{
    Person person = getRandomPerson();
    insertElement(htable, person.personalNumber, person);
    assert(lookup(htable, person.personalNumber)->personalNumber == person.personalNumber); // Se till att personnummret returnerar namnet
    return person.personalNumber;
}

void test(unsigned int tableSize)
{
    assert(tableSize >= 50); // Vi ska lagga till 50 personer sa vi maste minst ha 50 platser
    
	HashTable htable = createHashTable(tableSize);
	int personalNumbers[50];
    srand((unsigned int)time(0));
	
	assert(getSize(&htable) == tableSize);
	
	int i;
	for (i = 0; i < 50; i++)
    {
        int personalNumber = addRandomPersonToTable(&htable);
        personalNumbers[i] = personalNumber;
    }
    
    // Ta bort nagra existerande personer fran tabellen
    for (i = 0; i < 10; i++)
    {
        deleteElement(&htable, personalNumbers[i]);
        assert(lookup(&htable, personalNumbers[i]) == NULL); // Det borttagna ska inte langre finnas i tabellen
    }
    
    // Slutligen lagger vi till nŒgra till
    for (i = 0; i < 10; i++)
    {
        addRandomPersonToTable(&htable);
    }
    
    printHashTable(&htable);
    
    freeHashTable(&htable);
    assert(getSize(&htable) == 0); 
}
