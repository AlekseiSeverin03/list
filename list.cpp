
// list.cpp


#include "list.h"

// TODO  Verificator as asserts
// TODO  flag-linealisation :)

static FILE *file_out = NULL;

//---------------------------------------------------------
int ListCtor (list_t *list)
{
	assert (list != NULL);

//	memset (list, 0, sizeof (list));

	DATA(1) = POISON;
	NEXT(1) = -2;	

	int count;
	for (count = 2; count < MAX_N_ELEM - 1; count++)
	{
		DATA(count) = POISON;
		NEXT(count) = -(count + 1);
		PREV(count) = -(count - 1);
	}

	DATA(MAX_N_ELEM - 1) = POISON;
	PREV(MAX_N_ELEM - 1) = -(count - 1);

	FREE = 1;
	HEAD = 0;
	TAIL = 0;
	SIZE = 0;

	PREV(0) = 0;
	DATA(0) = 0;
	NEXT(0) = 0;

	return 0;
}


//---------------------------------------------------------
int ListDtor (list_t *list)
{
	assert (list != NULL);

	FREE = POISON;
	HEAD = POISON;
	TAIL = POISON;
	
	return 0;
}


//---------------------------------------------------------
// If you insert fisrt element into list, its index will be
// equal 1 (for any mean "pos_after").
//---------------------------------------------------------

int ListInsert (list_t *list, int pos_after, elem_t data)
{
	assert (list != NULL);
	assert (pos_after >= 0);	

	int temp = abs(NEXT(FREE));

	if (NEXT(pos_after) >= 0)
	{

		PREV(NEXT(pos_after)) = FREE;

		DATA(FREE) = data;
		NEXT(FREE) = NEXT(pos_after);
		PREV(FREE) = pos_after;

		NEXT(pos_after) = FREE;
	}
	else
	{
		printf ("!!! Error !!!");
	}

	HEAD = NEXT(0);
	TAIL = PREV(0);

	LAST_INSERT = abs (FREE);
	FREE = temp;
	PREV(FREE) = 0;

	SIZE++;

	return 0;
}


//---------------------------------------------------------
int ListDelete (list_t *list, int pos)
{
	assert (list != NULL);
	assert (pos  > 0);

	if (pos == HEAD)
	{
		HEAD = NEXT(pos);
	}
	else if (pos == TAIL)
	{
		TAIL = PREV(pos);
	}

	NEXT(PREV(pos)) = NEXT(pos);
	PREV(NEXT(pos)) = PREV(pos);

	PREV(FREE) = -pos;

	DATA(pos) = POISON;
	NEXT(pos) = -FREE;
	PREV(pos) = 0;	

	FREE = pos;

	SIZE--;

	return 0;
}


//---------------------------------------------------------
int LinealList (list_t *list)
{
	assert (list != NULL);

	int cur_elem = 0;

	list->buffer[0].prev = PREV(0);
	list->buffer[0].data = DATA(0);
	list->buffer[0].next = NEXT(0);	

	int count;
	for (count = 0; count < SIZE; count++)
	{
		list->buffer[count + 1].prev = PREV(NEXT(cur_elem));
		list->buffer[count + 1].data = DATA(NEXT(cur_elem));
		list->buffer[count + 1].next = NEXT(NEXT(cur_elem));
		
		cur_elem = NEXT(cur_elem);
	}

	int cur_free = FREE;
	int cur_pos = SIZE + 1;
	while (1)
	{
//printf ("\t%d\t%d\n", cur_pos, cur_free);
		if (cur_free == cur_pos)
		{
			break;
		}

		list->buffer[cur_pos].prev = PREV(cur_free);
		list->buffer[cur_pos].data = DATA(cur_free);
		list->buffer[cur_pos].next = NEXT(cur_free);
	
		cur_free = abs (NEXT(cur_free));
		cur_pos++;
	}

	for (count = 0; count < cur_pos; count++)
	{
		PREV(count) = list->buffer[count].prev;
		DATA(count) = list->buffer[count].data;
		NEXT(count) = list->buffer[count].next;
	}
	
	for (int count = 0; count < 10; count++)
	{
		printf ("\t%d) prev = %d, data = %d, next = %d.\n", count,
				PREV(count), DATA(count), NEXT(count));
	}
 

//	for (int count = 0; count < 10; count++)
//	{
//		printf ("\t%d) prev = %d, data = %d, next = %d.\n", count,
//				list->buffer[count].prev,list->buffer[count].data,list->buffer[count].next);
//	}

	return 0;
}

//---------------------------------------------------------
int DumpList (list_t *list, int n_elem_dp)
{
	assert (list != NULL);
	assert (n_elem_dp > 0);

	printf ("FREE = %d\tHEAD = %d\tTAIL = %d\n", 
			 FREE, HEAD, TAIL);
	printf ("\n");
	printf (" index DATA NEXT PREV\n");

	int count;
	for (count = 1; count <= n_elem_dp; count++)
	{
		printf (" %5d %4d %4d %4d\n", count,
				 DATA(count), NEXT(count), PREV(count));
	}
	
	printf ("\n");

	return 0;
}


//---------------------------------------------------------
int GraphDumpList (list_t *list, int n_elem_dp)
{
	assert (list != NULL);
	assert (n_elem_dp > 0);

	Start_Dot_File ("dump.dot");

	MakeInfoList (list);

	Make_All ();

	int count;
	for (count = 0; count <= n_elem_dp; count++)
	{
		Make_Node_ID (count, DATA(count), NEXT(count), PREV(count), "lightgrey");
	}
	
	for (count = 0; count <= n_elem_dp; count++)
	{
		Make_Connection_ID (count, abs(NEXT(count)), "red", "lightgrey", "\0");
		Make_Connection_ID (count, abs(PREV(count)), "grey", "lightgrey", "\0");
	}

	End_Dot_File ("dump.dot");

	return 0;
}


//---------------------------------------------------------
int MakeInfoList (list_t *list)
{
	assert (list != NULL);

	Make_Info_List (HEAD, TAIL, SIZE, FREE);

	return 0;
}
