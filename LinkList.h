#ifndef _LINKLIST_H_
#define _LINKLIST_H_

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;
typedef int ElemType;
typedef struct Node
{
	ElemType data;
	struct Node *next;
} Node;
typedef struct Node *LinkList;

Status GetElem(LinkList L, int i, ElemType *e);
Status ListInsert(LinkList *L, int i, ElemType e);
Status ListDelete(LinkList *L, int i, ElemType *e);
Status CreateListHead(LinkList *L, int n);
Status CreateListTail(LinkList *L, int n);
Status ClearList(LinkList *L);
Status PrintList(LinkList L);
int ListLength(LinkList L);
int LocateElem(LinkList L, ElemType e);
Status ListEmpty(LinkList L);
Status InitList(LinkList *L);
Status InvalidLinkList(LinkList L);

#endif
