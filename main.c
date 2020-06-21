#include <stdio.h>
#include "LinkList.h"

int main(void)
{
	LinkList L = NULL, K = NULL;
	ElemType e = 0;
	/* 初始化链表和插入测试 */
	printf("初始化链表和插入测试:\n");
	InitList(&L);
	while (1) {
		scanf("%d", &e);
		if (e == -1) {
			break;
		}
		ListInsert(&L, ListLength(L)+1, e);
	}
	PrintList(L);
	ListLength(L);
	int i = 0, j = 0;
	/* GetElem测试 */
	printf("查找位指定位置上的元素值测试:\n");
	while (i < 3) {
		scanf("%d", &j);
		GetElem(L, j, &e);
		i++;
	}

	/* ListDelete测试 */
	printf("删除结点测试:\n");
	i = 0;
	while (i < 3) {
		scanf("%d", &j);
		if (ListDelete(&L, j, &e)) {
			PrintList(L);
		}
		i++;
	}

	/* ClearList测试 */
	printf("清空链表测试");
	ClearList(&K);
	ClearList(&L);

	/* LocateElem测试 */
	i = 0;
	printf("查找元素所在位置测试:\n");
	while (i < 3) {
		scanf("%d", &e);
		LocateElem(L, e);
		i++;
	}

	return 0;
}
