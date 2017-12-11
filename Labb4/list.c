#include "list.h"
#include <stdlib.h>
#include <assert.h>

/*Hjalpfunktion till add
  Allokerar minne for en ny nod
  om allokeringen lyckades initieras data samt pekare (pekare initieras till NULL).
  Den nya noden (eller NULL) returneras.*/
static struct node* createListNode(const Data data)
{
	// Skapara en temp-pekare och allokerar minne för den
	List nodePtr;
	nodePtr = malloc(sizeof(struct node));
	if (nodePtr != NULL)
	{
		// Om det fungerade läggs data in och pekaren returneras
		(*nodePtr).data = data;
		return nodePtr;
	}
	else
		printf("\n\tAllocation failed\n\t");
}

/*Returnera en tom lista - funktionen ar fardig*/
List createEmptyList(void)
{
	return NULL;
}


/*Ar listan tom?
	Returnerar 1 om den Šr tom, annars 0*/
int isEmpty(const List list)
{
	// Om head pekar på null är listan tom
	if (list == NULL)
		return 1;
	else
		return 0;
}

/*Lagg till nod forst i listan
	Precondition: Det nya datat ligger forst i listan (testa med assert)*/
void addFirst(List *list, const Data data)
{
	if (*list != NULL)
	{
		// det list pekar på sparas som tempvärde
		struct List *tempPtr = *list;

		// Skapar en ny nod och lägger in data
		*list = createListNode(data);
		if (*list != NULL)
		{
			// Om det lyckades sätts list next till det list pekade på innan
			(*list)->next = tempPtr;
		}
	}
	else
	{
		//Anropar createListNode for att skapa den första noden och lägga in data
		*list = createListNode(data);
		if (*list != NULL)
		{
			(*list)->next = NULL;
		}
	}
}

/*Lagg till nod sist i listan
	Tips, nar du hittat ratt plats kan du anvanda funktionen addFirst for att lagga till*/
void addLast(List *list, const Data data)
{
	// Om list pekar på null anropas add first
	if (*list == NULL)
	{
		addFirst(list, data);
	}

	// Itererar rekursivt tills sista noden hittats
	else if ((*list)->next != NULL)
	{
		addLast(&((*list)->next), data);
	}

	// När sista noden är nådd kallas add first med list->next för att skapa en ny sist i listan
	else
	{
		addFirst(&((*list)->next), data);
	}
}

/*Ta bort forsta noden i listan
  Precondition: listan ar inte tom (testa med assert)
  Noden ska lankas ur och minnet frigoras, resten av listan ska finnas kvar*/
void removeFirst(List *list)
{
	assert(*list != NULL);

	// Kopierar adressen till nästa nod i en tempvariabel, om värdet är NULL uppstår inget problem
	struct node *tempNode = (*list)->next;

	// Frigör minnet för den första noden
	free(*list);

	// Sätter tempvariabelns värde som värde på head
	*list = tempNode;


	//Glom inte att frigora minnet for den nod som lankas ur listan.
	//Tank pa att listans huvud efter bortlankningen maste peka pa den nod som nu ar forst.
}

/*Ta bort sista noden i listan
  Precondition: listan ar inte tom (testa med assert)t*/
void removeLast(List *list)
{
	assert(*list != NULL);
	
	// Om list-next pekar på NULL ska vi ta bort elementet
	if ((*list)->next == NULL)
	{
		free(*list);
		*list = NULL;
	}

	// Om list->next inte pekar på NULL skickar vi den som argument till removeLast
	else if ((*list)->next != NULL)
	{
		removeLast(&(*list)->next);
	}

    //Glom inte att frigora minnet for den nod som lankas ur listan.
    //Tank pa att den nod som nu ar sist inte pekar nagonstans, dess pekare maste nollstallas
}

/*Ta bort data ur listan (forsta forekomsten)
  Returnera 1 om datat finns, annars 0
  Tips, nar du hittar ratt nod kan du anvanda en av de ovanstaende funktionerna for att ta bort noden*/
int removeElement(List *list, const Data data)
{
	// Testar om list->data innehåller det vi letar efter och kallar remove first så att nuvarande ersätts med nästa och returnerar 1
	if ((*list)->data == data)
	{
		removeFirst(list,data);
		return 1;
	}
	else
	{
		// Om list next är NULL har vi nått slutet av listan utan att hitta en match och returnerar 0
		if ((*list)->next == NULL)
		{
			return 0;
		}

		// Kallar removeElement med list->next för att iterera vidare
		else
		{
			return removeElement((&(*list)->next), data);
		}
	}
}

/*Finns data i listan?
  Om datat finns returneras 1, annars 0
  Tank pa att listan kan vara tom*/
int search(const List list, const Data data)
{
	// Om list är null har vi nått slutet och inte hittat en match
	if (list == NULL)
	{
		return 0;
	}
	
	// om datat stämmer returneras 1
	else if (list->data == data)
	{
		return 1;
	}

	// itererar till list->next och skickar med data
	else
	{
		search(list->next, data);
	}
}

/*Returnera antalet noder i listan*/
int numberOfNodesInList(const List list)
{
	// Static int för att spara värdet för nodeAmount
	static int nodeAmount = 0;
	int nodeNum;
	if (list != NULL)
	{
		// ökar på nodeAmount varje gång list inte är NULL
		nodeAmount++;
		nodeNum = numberOfNodesInList(list->next);	
	}
	else
	{
		nodeNum = nodeAmount;
		nodeAmount = 0;
	}
	return nodeNum;
}

/*Ta bort alla noder ur listan
  Glom inte att frigora minnet
  Postcondition: Listan ar tom, *list Šr NULL (testa med assert)*/
void clearList(List *list)
{
	if (isEmpty(*list))
		return;
	// kalla clear list och rekursivt tills list->next pekar på NULL, då kallas remove last för varje kallat varv med sista först
	if ((*list)->next != NULL)
	{
		clearList(&((*list)->next));
	}
	removeLast(&(*list));
    
	assert(isEmpty(*list));
	//Alla noder maste tas avallokeras en och en, det racker inte att endast frigora list.
}

/*Skriv ut listan
  Vid anropet kan man ange stdout som argument 2 for att skriva ut pŒ skarmen.
  Anvanda fprintf for att skriva ut.
  Den har typen av utskriftfunktion blir mer generell da man kan valja att skriva ut till skarmen eller till fil.*/
void printList(const List list, FILE *textfile)
{
	// Skriver ut data och kallar sedan printlist med nästa nod tills det pekar på NULL
	if (list != NULL)
	{
		fprintf(textfile, "%d", (list)->data);
		printList(list->next, stdout);
	}
}

/*Returnera forsta datat i listan
  Precondition: listan ar inte tom (testa med assert)*/
Data getFirstElement(const List list)
{
	assert(list != NULL);
	
	// Returnerar list->data
	return list->data;
}

/*Returnera sista datat i listan
  Precondition: listan ar inte tom (testa med assert)*/
Data getLastElement(const List list)
{
	assert(list != NULL);

	// Kallar rekursivt till list->next pekar på NULL, då skrivs list->data ut
	if (list->next != NULL)
	{
		getLastElement(list->next);
	}
	else
	{
		return list->data; //Ersatt med ratt returvarde
	}
}