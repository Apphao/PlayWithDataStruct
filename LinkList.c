#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "LinkList.h"

/*
 * 函数名: GetElem
 * 功能: 获取第i个位置上的元素
 * 参数1: L 链表头指针
 * 参数2: i 位置索引
 * 参数3: *e 返回值保存地址
 * 返回值: Status 成功返回OK，失败返回ERROR
 */
Status GetElem(LinkList L, int i, ElemType *e)
{
	printf("获取第%d个位置的元素: ", i);
	/* 1.检查输入的链表头指针是否合法 */
	if (InvalidLinkList(L)) {
		return ERROR;
	}
	/* 2.判断查找的位置索引i是否合法 */
	if (i > ListLength(L)) {
		printf("失败!输入的位置索引%d大于链表长度%d.\n", i, ListLength(L));
		return ERROR;
	} else if (i < 1) {
		printf("失败!输入的位置索引%d小于1.\n", i);
		return ERROR;
	}
	/* 3.工作指针后移,找到位置索引i上的元素 */
	int j = 1;				//计数器
	LinkList p = L->next;	//工作指针,j=1时,p指向第一个结点
	while (j < i) {			//j小于i时,工作指针p后移,找到的是第i个结点
		p = p->next;
		j++;
	}
	*e = p->data;			//此时j=i,p已指向位置索引为i的结点,获取该结点的值
	printf("%d\n", *e);
	return OK;
}

/*
 * 函数名: ListInsert
 * 功能: 在第i个位置上插入元素值为e的结点
 * 参数1: *L 链表头指针的地址
 * 参数2: i 位置索引
 * 参数3: e 插入元素的值
 * 返回值: Status 成功返回OK，失败返回ERROR
 */
Status ListInsert(LinkList *L, int i, ElemType e)
{
	printf("将%d插入到第%d个位置: ", e, i);
	/* 1.检查输入的链表头指针是否合法 */
	if (InvalidLinkList(*L)) {
		return ERROR;
	}
	/* 2.判断插入的位置索引i是否合法 */
	if (i > ListLength(*L) + 1) {
		printf("失败!输入的位置索引%d大于可插入位置的最大值%d.\n", i, ListLength(*L)+1);
		return ERROR;
	} else if (i < 1) {
		printf("失败!输入的位置索引%d小于1.\n", i);
		return ERROR;
	}
	/* 3.工作指针后移,找到第i-1个结点 */
	int j = 1;			//计数器
	LinkList p = *L;	//工作指针,j=1时,p指向头结点
	LinkList s;			//插入的结点指针
	while (j < i) {		//j小于i时,工作指针后移,找到的是第i-1个结点
		p = p->next;
		j++;
	}
	/* 4.链表插入常规操作 */
	s = (LinkList)malloc(sizeof(Node));
	s->data = e;
	s->next = p->next;
	p->next = s;
	(*L)->data++;
	printf("成功!\n");
	return OK;
}

/*
 * 函数名: ListDelete
 * 功能: 删除第i个位置结点,并保存被删除结点的元素值
 * 参数1: *L 链表头指针的地址
 * 参数2: i 位置索引
 * 参数3: *e 保存被删除结点的元素值
 * 返回值: Status 成功返回OK，失败返回ERROR
 */
Status ListDelete(LinkList *L, int i, ElemType *e)
{
	printf("删除第%d个位置的元素: ", i);
	/* 1.检查输入的链表头指针是否合法 */
	if (InvalidLinkList(*L)) {
		return ERROR;
	}
	/* 2.判断删除的位置索引i是否合法 */
	if (i > ListLength(*L)) {
		printf("失败!输入的位置索引%d大于可删除位置的最大值%d.\n", i, ListLength(*L));
		return ERROR;
	} else if (i < 1) {
		printf("失败!输入的位置索引%d小于1.\n", i);
		return ERROR;
	}
	/* 3.工作指针后移,找到第i-1个结点 */
	int j = 1;			//计数器
	LinkList p = *L;	//工作指针,j=1时,p指向头结点
	LinkList q;			//用于保存要删除的结点,以便free函数释放内存
	while (j < i) {		//j<i时,工作指针后移,找到的是第i-1个结点
		p = p->next;
		j++;
	}
	/* 3.链表删除的常规操作 */
	q = p->next;
	p->next = q->next;
	*e = q->data;
	free(q);
	(*L)->data--;
	printf("成功!删除的元素值为%d\n", *e);
	return OK;
}

/*
 * 函数名: CreateListHead
 * 功能: 用头插法创建n个有随机值结点的链表
 * 参数1: *L 链表头指针的地址,该地址必须为空,否则将创建失败
 * 参数2: n 结点的个数
 * 返回值: Status 成功返回OK，失败返回ERROR
 */
Status CreateListHead(LinkList *L, int n)
{
	printf("头插法创建链表,插入%d个随机元素!\n", n);
	/* 1.初始化一个空链表,如果失败则返回ERROR */
	if (!InitList(L)) {
		return ERROR;
	}
	/* 2.使用头插法插入结点 */
	LinkList p;		//用于malloc申请内存的结点指针
	int i;			//循环变量
	srand(time(0));	//初始化随机数种子
	for (i = 0; i < n; i++) {	//循环申请结点空间,并插入到第1个位置
		p = (LinkList)malloc(sizeof(Node));
		p->data = rand()%100 + 1;
		p->next = (*L)->next;
		(*L)->next = p;
	}
	(*L)->data = n;
	return OK;
}

/*
 * 函数名: CreateListTail
 * 功能: 用尾插法创建n个有随机值结点的链表
 * 参数1: *L 链表头指针的地址,该地址必须为空,否则将创建失败
 * 参数2: n 结点的个数
 * 返回值: Status 成功返回OK，失败返回ERROR
 */
Status CreateListTail(LinkList *L, int n)
{
	printf("尾插法创建链表,插入%d个随机值元素!\n", n);
	/* 1.初始化一个空链表,如果失败则返回ERROR */
	if (!InitList(L)) {
		return ERROR;
	}
	/* 2.使用尾插法插入结点 */
	LinkList p, r;	//p是用于malloc申请内存的结点指针,r是指向尾部结点
	int i;			//循环变量
	srand(time(0));	//初始化随机数种子
	for (i = 0; i < n; i++) {	//循环申请结点空间,并插入到最后一个位置
		p = (LinkList)malloc(sizeof(Node));
		p->data = rand()%100 + 1;
		r->next = p;
		r = p;
	}
	r->next = NULL;
	(*L)->data = n;
	return OK;
}

/*
 * 函数名: ClearList
 * 功能: 将链表中的结点清空
 * 参数: *L 链表头指针的地址
 * 返回值: Status 成功返回OK，失败返回ERROR
 */
Status ClearList(LinkList *L)
{
	printf("清空链表: ");
	/* 1.检查链表头指针是否为空,以及链表长度是否为0 */
	if (InvalidLinkList(*L)) {
		return ERROR;
	} else if (ListEmpty(*L)) {
		printf("链表已经为空,不需要清空!\n");
		return OK;
	}
	/* 2.使用2个结点指针配合的方式释放掉链表内所有结点的内存 */
	LinkList p, q;		//p用于free,q用于指向p的下一个结点
	p = (*L)->next;		//p指向第一个结点
	while (p) {			//当p不为空时,释放该结点
		q = p->next;	
		free(p);
		p = q;
	}
	(*L)->next = NULL;
	(*L)->data = 0;
	printf("成功!\n");
	return OK;
}

/*
 * 函数名: PrintList
 * 功能: 打印输出链表中所有结点的元素值
 * 参数: L 链表头指针,不能为空
 * 返回值: 空
 */
Status PrintList(LinkList L)
{
	printf("打印链表: \n");
	/* 1.如果头指针为空或者链表为空,则直接返回 */
	if (InvalidLinkList(L)) {
		return ERROR;
	} else if (ListEmpty(L)) {
		return OK;
	}
	/* 2.循环打印输出所有结点的元素值 */
	LinkList p = L->next;		//工作指针,指向第一个结点
	while (p) {					//如果结点不为空,则打印输出
		printf("%d  ", p->data);
		p = p->next;			//工作指针后移
	}
	printf("\n");
	return OK;
}

/*
 * 函数名: ListLength
 * 功能: 获取链表的长度
 * 参数: L 链表头指针,不能为空
 * 返回值: int 链表的长度
 */
int ListLength(LinkList L)
{
	/* 1.检查头指针 */
	if (InvalidLinkList(L)) {
		return ERROR;
	}
	/* 2.输出链表长度 */
	//printf("链表长度为: %d\n", L->data);
	return L->data;
}

/*
 * 函数名: LocateElem
 * 功能: 查找元素值为e的结点所在的位置
 * 参数1: L 链表头指针,不能为空
 * 参数2: e 要查找的元素值
 * 返回值: int 元素值为e的结点所在的位置
 */
int LocateElem(LinkList L, ElemType e)
{
	printf("查找元素值为%d所在的位置: ", e);
	/* 1.检查头指针 */
	if (InvalidLinkList(L)) {
		return ERROR;
	}
	/* 2.检查链表是否为空 */
	if (ListEmpty(L)) {
		return ERROR;
	}
	/* 3.遍历链表查找元素值等于e的结点位置 */
	int j = 1;				//初始化计数器
	LinkList p = L->next;	//工作指针指向第一个结点
	while (p) {				//p不为空则继续
		if (p->data == e) {		//找到元素值等于e的结点
			printf("%d\n", j);	//输出该结点所在的位置
			return j;			//返回该结点所在的位置
		}
		p = p->next;		//工作指针后移
		j++;				//计数器加1
	}
	if (!p) {				//遍历完链表,没有找到
		printf("没有值为%d的元素.\n", e);
		return FALSE;
	}
}

/*
 * 函数名: ListEmpty
 * 功能: 检查链表是否为空
 * 参数: 链表头指针,不能为空
 * 返回值: 若链表为空则返回TRUE,反之则返回FALSE
 */
Status ListEmpty(LinkList L)
{
	/* 1.检查头指针 */
	if (InvalidLinkList(L)) {
		return ERROR;
	}
	/* 2.检查链表的长度是否为0 */
	if (L->data == 0) {
		printf("链表为空!\n");
		return TRUE;
	} else {
		return FALSE;
	}
}

/*
 * 函数名: InitList
 * 功能: 初始化一个空链表
 * 参数: *L 链表头指针地址,必须为空,否则可能会覆盖别的链表头指针
 * 返回值: 成功则返回OK,失败则返回ERROR
 */
Status InitList(LinkList *L)
{
	printf("初始化空链表: ");
	/* 1.检查头指针 */
	if ((*L) == NULL) {
		*L = (LinkList)malloc(sizeof(Node));
		(*L)->next = NULL;
		printf("成功!\n");
		return OK;
	} else {
		printf("失败,传入的链表指针非空,可能是其他已有的链表头指针.\n");
		return ERROR;
	}
}

/*
 * 函数名: InvalidLinkList
 * 功能: 检查输入的链表是否被初始化过
 * 参数: L 链表头指针
 * 返回值: Status 如果没有被初始化过则返回TRUE,反之则返回TRUE
 */
Status InvalidLinkList(LinkList L)
{
	if (L == NULL) {
		printf("传入的头指针为NULL,不是一个合法的链表头指针!\n");
		return TRUE;
	} else {
		return FALSE;
	}
}
