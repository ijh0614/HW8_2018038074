/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

	do{
		printf("--------[2018038074]-----------------------[임종훈]-------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;//헤드노드의 링크가 다 나를 가르키도록 한다.
	(*h)->llink = *h;
	(*h)->key = -9999;//헤드 노드에 값은 저장하지 않는다
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){
	listNode* p = h->rlink;//첫번째 노드의 주소
	listNode* next_node = NULL;//다음 노드 임시저장

	while(next_node != h){//헤드의 주소가 나올 때 까지
		next_node = p->rlink;//다음 노드의 주소 임시저장
		free(p);
	}
	//마지막에 헤드노드 해제
	free(h);
	return 0;
}



void printList(listNode* h) {//연결리스트의 노드 출력 함수
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {//헤드 노드도 없을 때 전처리
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {//먼저 노드를 출력
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);//노드의 갯수 출력


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);//헤드 노드의 주소와 헤드 노드가 저장하고 있는 주소 출력

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {//노드의 주소와 링크마다 저장하고 있는 주소 출력
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {


	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	listNode* r_node;//삽입할 위치의 오른쪽 노드

	node->key = key;//값 저장
	r_node = h->rlink;

	if(r_node = h){//헤드노드 외에 아무런 노드도 없을 때
		node->rlink = h;//노드의 끝의 표현은 헤드노드를 가르키는 것이다.
		node->llink = h;
		h->rlink = node;//첫 노드를 가르킴
		h->llink = node;//마지막 노드를 가르킴
	}

	node->rlink = h->rlink;
	node->llink = h;//첫 노드의 의미
	h->rlink = node;
	r_node->llink = node;//두번째가 된 노드가 가르키도록


	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {


	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {


	return 0;
}



/**
 *  리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 
 **/
int insertNode(listNode* h, int key) {

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

	return 0;
}