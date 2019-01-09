#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ObjectManager.h"


//types
typedef struct NODE Node;
struct NODE{
  Ref id;
  int refCount;
  int size;
  int address;
  Node *next;
};


//prototypes of helper functions
void compact();
void insertList(ulong size);


//static variables
Node * head;
Node * tail;
uchar buffer1[MEMORY_SIZE];
uchar buffer2[MEMORY_SIZE];
Ref id;
int freeptr;
uchar * active;
uchar * inactive;


void initPool()
{
    head = NULL;
    tail = NULL;
    id = 1;
    freeptr = 0;
    active = buffer1;
    inactive = buffer2;
}//initPool


void destroyPool()
{
    Node* prev = NULL;
    Node* curr = head;
    while(curr!=NULL)
    {
        prev = curr;
        curr = curr->next;
        free(prev);
    }
    head = NULL;

}//destroyPool


Ref insertObject( ulong size )
{
    Ref referenceId = NULL_REF;

    if (freeptr+size >= MEMORY_SIZE)
        compact();

    if(freeptr+size < MEMORY_SIZE)
    {
        insertList(size);
        referenceId = tail->id;
        tail->address = freeptr;
        freeptr += size;
    }//if
    return referenceId;
}//insertObject


void *retrieveObject( Ref ref )
{
	void * object = NULL_REF;
    Node* curr = head;
    while (curr != NULL && (curr->id)<ref)
        curr = curr->next;
    if (curr != NULL && curr->id==ref)
        object = (void *) (active +(curr->address));

    return object;
}//retrieveObject


void addReference( Ref ref )
{
    Node* curr = head;
    while (curr != NULL  && ((curr->id)<ref))
        curr = curr->next;

	if (curr != NULL && curr->id==ref)
        curr->refCount++;
    else
        printf("Could not add the reference!!\n");
}//addReference


void dropReference( Ref ref )
{
    Node* prev = NULL;
    Node* curr = head;
    while (curr != NULL && (curr->id)<ref)
    {
        prev = curr;
        curr = curr->next;
    }

    if (curr != NULL && curr->id==ref)
    {
        curr->refCount--;
        if (curr->refCount==0)
        {
            if (prev!=NULL)  //removing a node in between
                prev->next=curr->next;

            else   //removing the first node
                head = head->next;

            if (tail == curr) //if deleting the last node
                tail = prev; //then set the prev to tail
        }//delete this node
    }//if found
    else
        printf("Could not drop the reference!!\n");
}//dropReference


void dumpPool()
{
    Node* curr = head;
    while (curr!= NULL)
    {
        printf("Id = %lu\n", curr->id);
        printf("Address = %d\n", curr->address);
        printf("Size = %d\n", curr->size);
        printf("Reference Count = %d\n", curr->refCount);
        curr = curr->next;
    }//while

}//dumpPool


void compact()
{
    Node* curr = head;
    int i;
    int byteUsed = freeptr;
    freeptr = 0;
    uchar * temp = active;
    active = inactive;
    inactive = temp;
    int count = 0;
    while (curr!= NULL)
    {
        count++;
        for (i=freeptr; i<(freeptr+curr->size); i++)
            *active = inactive[i];
        freeptr+= curr->size;
        curr = curr->next;
    }//while
    int byteRecovered = byteUsed-freeptr;
    printf("There are %d object(s)\n", count);
    printf("%d bytes are used\n", freeptr);
    printf("%d bytes have been recovered\n", byteRecovered);

}//compact


void insertList(ulong size)
{
    Node * newNode = malloc(sizeof(Node));
    newNode->id = id++;
    newNode->size = size;
    newNode->refCount = 1;
    newNode->next = NULL;
    if (tail != NULL)
        tail->next = newNode;
    tail = newNode;
    if (head == NULL)
        head = newNode;
}//insertList
