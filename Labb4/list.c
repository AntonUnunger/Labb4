#include "list.h"
#include <stdlib.h>
#include <assert.h>

/*Hjalpfunktion till add
  Allokerar minne for en ny nod
  om allokeringen lyckades initieras data samt pekare (pekare initieras till NULL).
  Den nya noden (eller NULL) returneras.*/
static struct node* createListNode(const Data data)
{
	// Skapara en temp-pekare och allokerar minne f�r den
	List nodePtr;
	nodePtr = malloc(sizeof(struct node));
	if (nodePtr != NULL)
	{
		// Om det fungerade l�ggs data in och pekaren returneras
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
	Returnerar 1 om den �r tom, annars 0*/
int isEmpty(const List list)
{
	// Om head pekar p� null �r listan tom
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
		// det list pekar p� sparas som tempv�rde
		struct List *tempPtr = *list;

		// Skapar en ny nod och l�gger in data
		*list = createListNode(data);
		if (*list != NULL)
		{
			// Om det lyckades s�tts list next till det list pekade p� innan
			(*list)->next = tempPtr;
		}
	}
	else
	{
		//Anropar createListNode for att skapa den f�rsta noden och l�gga in data
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
	// Om list pekar p� null anropas add first
	if (*list == NULL)
	{
		addFirst(list, data);
	}

	// Itererar rekursivt tills sista noden hittats
	else if ((*list)->next != NULL)
	{
		addLast(&((*list)->next), data);
	}

	// N�r sista noden �r n�dd kallas add first med list->next f�r att skapa en ny sist i listan
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

	// Kopierar adressen till n�sta nod i en tempvariabel, om v�rdet �r NULL uppst�r inget problem
	struct node *tempNode = (*list)->next;

	// Frig�r minnet f�r den f�rsta noden
	free(*list);

	// S�tter tempvariabelns v�rde som v�rde p� head
	*list = tempNode;


	//Glom inte att frigora minnet for den nod som lankas ur listan.
	//Tank pa att listans huvud efter bortlankningen maste peka pa den nod som nu ar forst.
}

/*Ta bort sista noden i listan
  Precondition: listan ar inte tom (testa med assert)t*/
void removeLast(List *list)
{
	assert(*list != NULL);
	
	// Om list-next pekar p� NULL ska vi ta bort elementet
	if ((*list)->next == NULL)
	{
		free(*list);
		*list = NULL;
	}

	// Om list->next inte pekar p� NULL skickar vi den som argument till removeLast
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
	// Testar om list->data inneh�ller det vi letar efter och kallar remove first s� att nuvarande ers�tts med n�sta och returnerar 1
	if ((*list)->data.key == data.key)
	{
		removeFirst(list,data);
		return 1;
	}
	else
	{
		// Om list next �r NULL har vi n�tt slutet av listan utan att hitta en match och returnerar 0
		if ((*list)->next == NULL)
		{
			return 0;
		}

		// Kallar removeElement med list->next f�r att iterera vidare
		else
		{
			return removeElement((&(*list)->next), data);
		}
	}
}

/*Finns data i listan?
  Om datat finns returneras 1, annars 0
  Tank pa att listan kan vara tom*/
Value* search(const List list, const Data data)
{
	// Om list �r null har vi n�tt slutet och inte hittat en match
	if (list == NULL)
	{
		return NULL;
	}
	
	// om datat st�mmer returneras 1
	else if (list->data.key == data.key)
	{
		return &list->data.key;
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
	// Static int f�r att spara v�rdet f�r nodeAmount
	static int nodeAmount = 0;
	int nodeNum;
	if (list != NULL)
	{
		// �kar p� nodeAmount varje g�ng list inte �r NULL
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
  Postcondition: Listan ar tom, *list �r NULL (testa med assert)*/
void clearList(List *list)
{
	if (isEmpty(*list))
		return;
	// kalla clear list och rekursivt tills list->next pekar p� NULL, d� kallas remove last f�r varje kallat varv med sista f�rst
	if ((*list)->next != NULL)
	{
		clearList(&((*list)->next));
	}
	removeLast(&(*list));
    
	assert(isEmpty(*list));
	//Alla noder maste tas avallokeras en och en, det racker inte att endast frigora list.
}

/*Skriv ut listan
  Vid anropet kan man ange stdout som argument 2 for att skriva ut p� skarmen.
  Anvanda fprintf for att skriva ut.
  Den har typen av utskriftfunktion blir mer generell da man kan valja att skriva ut till skarmen eller till fil.*/
void printList(const List list, FILE *textfile)
{
	// Skriver ut data och kallar sedan printlist med n�sta nod tills det pekar p� NULL
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

	// Kallar rekursivt till list->next pekar p� NULL, d� skrivs list->data ut
	if (list->next != NULL)
	{
		getLastElement(list->next);
	}
	else
	{
		return list->data; //Ersatt med ratt returvarde
	}
}