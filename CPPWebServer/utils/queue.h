#include<stdlib.h>

struct node
{
struct node * next;
int *client_socket;
};

struct node* head = NULL; 
struct node* tail = NULL;

int * dequeue()
{
if(head == NULL) 
{ 
return NULL;
} 
else 
{ 
int *result = head->client_socket; 
struct node *temp = head;
head = head->next;
if (head == NULL) 
{
tail = NULL;
} 
free (temp); 
return result;
}
}

void enqueue (int * client_socket)
{
struct node *newnode = (struct node*)malloc(sizeof(struct node));
newnode->client_socket = client_socket;
newnode->next = NULL; 
if(tail == NULL) 
{ 
head = newnode; 
} 
else 
{ 
tail->next = newnode;
}
tail = newnode;
}
