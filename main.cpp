
//main.cpp


#include "list.h"


int main ()
{
	list_t list = {};

	ListCtor (&list);

	ListInsert (&list, 0, 10); 
	ListInsert (&list, 1, 11); 
	ListInsert (&list, 2, 12); 
	ListDelete (&list, 1);

//LinealList (&list);


	GraphDumpList (&list, 10);

	return 0;
}
