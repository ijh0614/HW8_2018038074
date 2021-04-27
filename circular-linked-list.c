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
//기본적으로 이중연결리스트와 유사. 양 끝이 헤드노드를 가르켜야학고, 헤드 노드가 양끝을 가르켜야한다는 것 주의.
int initialize(listNode** h);//초기화. 헤더노드를 만들어준다. 여태까지와 다르게 헤더 노드의 타입이 listNode이다.
int freeList(listNode* h);//헤드노드가 나올때까지 반복해서 해제 후 헤드노드까지 해제
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);//값의 크기 비교
int deleteNode(listNode* h, int key);//값을 찾아서 삭제

void printList(listNode* h);



int main()
{
	char command;//메뉴 선택
	int key;//사용자로부터 값 입력받음
	listNode* headnode=NULL;//listNode로 헤드노드를 선언했기 때문에 다른 노드들이 헤드 노드를 가르킬 수 있다.

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
			freeList(headnode);//해제하고 종료
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

	while(p != h){//헤드의 주소가 나올 때 까지
		p = p->rlink;//다음 노드의 주소 임시저장
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
	if(h->rlink == h){//전처리. 저장되어있는 노드가 없을 경우
		insertFirst(h, key);
		return 0;
	}

	listNode* node = (listNode*)malloc(sizeof(listNode));//노드 생성

	node->key = key;
	node->rlink = h;//맨 끝이므로 h의 주소가 rlink이다
	node->llink = h->llink;//맨 끝의 노드의 주소를 node의 llink에 넣어준다
	h->llink->rlink = node;
	h->llink = node;//양쪽 노드의 링크가 node를 가르키도록 한다.

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
	if(h->rlink == h){//노드 삭제 전처리
		printf("There is no node to delete.\n\n");
		return 0;
	}

	listNode* del_node = h->llink;//지울 노드 주소 저장
	
	h->llink = del_node->llink;//삭제하는 양 옆 노드의 링크 변환
	del_node->llink->rlink = h;//노드가 하나만 존재해도 성립

	free(del_node);//노드 해제

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	listNode* r_node;//삽입할 위치의 오른쪽 노드

	node->key = key;//값 저장
	r_node = h->rlink;//아무 노드도 없을 때는 head의 주소가 들어감

	node->rlink = h->rlink;//헤드 노드만 있을때도 성립함
	node->llink = h;//첫 노드의 의미
	h->rlink = node;
	r_node->llink = node;//두번째가 된 노드가 가르키도록 or 헤드노드만 있을때는 헤드노드가 노드를 가르키도록

	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {
	if(h->rlink == h){//노드 삭제 전처리
		printf("There is no node to delete.\n\n");
		return 0;
	}
	
	listNode* del_node;//지워줄 노드 임시저장
	del_node = h->rlink;

	h->rlink = del_node->rlink;//노드가 하나만 있어도 성립하는 코드.
	del_node->rlink->llink = h;//두번째 노드의 왼쪽 링크가 헤드 노드를 가르켜야 함
	free(del_node);
	return 1;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {

	listNode* temp_node = h->rlink;
	listNode* next_node = temp_node->rlink;

	//전처리기
	if(temp_node == h){//저장되어 있는 노드가 없거나
		printf("\nPlease input two nodes.\n");
		return 0;
	}
	else if(temp_node->rlink == h){//노드가 하나만 있는 경우
		printf("\nAt least two nodes are required for the program to work.\n");
		return 0;
	}

	temp_node = h->rlink;
	h->rlink = h->llink;//헤드노드가 가르키는 시작을 끝으로 옮기기
	h->llink = temp_node;//헤드 노드가 가르키는 끝을 시작으로 옮기기

	while(temp_node != h){//다음 노드가 헤더라는 건 끝까지 돌았다는 뜻
		next_node = temp_node->rlink;
		
		temp_node->rlink = temp_node->llink;//다음 노드 링크에 이전노드 주소 저장
		temp_node->llink = next_node;//이전 노드 주소에 다음 노드 주소 저장

		temp_node = next_node;//다음 노드로 이동
	}


	return 0;
}



/**
 *  리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 
 **/
int insertNode(listNode* h, int key) {
	if(h->rlink == h){//전처리. 저장되어있는 노드가 없을 경우
		insertFirst(h, key);
		return 0;
	}
	
	listNode* node = (listNode*)malloc(sizeof(listNode));//새 노드 동적할당
	listNode* next_node = h->rlink;

	node->key = key;

	while(next_node != h){
		if(next_node->key >= key){//입력한 key보다 큰 값을 저장하고 있는 노드를 찾으면
			node->llink = next_node->llink;
			node->rlink = next_node;//노드의 링크 할당
			next_node->llink->rlink = node;
			next_node->llink = node;//양쪽에 있는 노드가 새로운 노드를 가르키도록
			return 0;
		}
		next_node = next_node->rlink;//다음 노드로 이동
	}
//입력한 key보다 큰 값을 저장하고 있는 노드가 없으면
	node->rlink = h;
	node->llink = h->llink;
	h->llink->rlink = node;//기존에 마지막 노드였던 노드가 새로운 노드를 가르킨다.
	h->llink = node;//헤더노드의 llink는 끝을 가르킨다.
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
	if(h->rlink == h){//노드 삭제 전처리
		printf("There is no node to delete.\n\n");
		return 0;
	}

	listNode* del_node = h->rlink;//지울 노드 저장

	while(del_node != h){//못 찾고 끝까지 다 돌면 탈출
		if(del_node->key == key){//만약에 key값을 찾으면
			del_node->llink->rlink = del_node->rlink;
			del_node->rlink->llink = del_node->llink;//지울 노드를 건너 뛰게하고

			free(del_node);//노드 해제
			return 0;
		}
		del_node = del_node->rlink;
	}

	printf("There is no node to delete.\n\n");//지울 노드를 찾을 수 없다.
	return 0;
}