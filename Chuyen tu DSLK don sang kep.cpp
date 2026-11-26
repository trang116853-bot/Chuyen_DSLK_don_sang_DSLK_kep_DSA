#include<stdio.h>
#include<stdlib.h>
typedef struct {
	char hoten[30];
	int masv;
	float d1, d2, d3;
}Data;

typedef struct tagNode {
	Data infor;
	struct tagNode *next, *prev;
}Node;
typedef struct {
	Node *pHead;
	Node *pTail;
	int spt;
}DList;
/////////////////////////////////////
void initList(DList *L)
{
	L->pHead = NULL;
	L->pTail = NULL;
	L->spt = 0;
}
/////////////////////////////////////
int emptyList(DList L)
{
	return (L.spt == 0);
}
/////////////////////////////////////
void insert_Head(DList *L, Data x)
{
	Node *pp;
	pp = (Node*) malloc(sizeof(Node));
	pp->infor = x;
	pp->next = NULL;
	pp->prev = NULL;
	if (emptyList(*L)){
		L->pHead = pp;
		L->pTail = pp;
	}
	else{
		L->pHead->prev = pp;
		pp->next = L->pHead;
		L->pHead = pp;
	}
	L->spt++;
}

void insert_Tail(DList *L, Data x){
	Node *pp;
	pp = (Node*) malloc(sizeof(Node));
	pp->infor = x;
	pp->next = NULL;
	pp->prev = NULL;
	if(emptyList(*L)){
		L->pHead = pp;
		L->pTail = pp;
	}
	else {
		L->pTail->next = pp;
		pp->prev = L->pTail;
		L->pTail = pp;
	}
	L->spt++;
}

void insert_After(DList *L, Node *q, Data x){
	Node *pp;
	if(NULL == q) return;
	else {
		pp = (Node*) malloc(sizeof(Node));
		pp->infor = x;
		pp->next = q->next;
		q->next->prev = pp;
		q->next = pp;
		pp->prev = q;
		if(q == L->pTail) L->pTail = pp;
		L->spt++;
	}
}
///////////////////////////////////////

Node* search(DList L, int ma) {
    Node *pp = L.pHead;
    while (pp != NULL && pp->infor.masv != ma) {
        pp = pp->next;
    }
    return pp;
}
///////////////////////////////////////

void del_Head (DList *L){
	Node *pp;
	if( emptyList(*L)) return;
	else{
		pp = L->pHead;
		L->pHead = pp->next;
		if(L->pHead != NULL) L->pHead->prev = NULL;
		free(pp);
		L->spt--;
		if(L->pHead == NULL) L->pTail == NULL;
	}
}

void del_Tail(DList *L) {
	Node *pp;
    if (emptyList(*L)) return;
    pp = L->pTail;
    L->pTail = pp->prev;
    if (L->pTail == NULL) {
        L->pHead = NULL;
    } 
	else {
        L->pTail->next = NULL;
    }
    free(pp);
    L->spt--;

}

void del_After(DList *L, Node *q){
	Node *pp;
	if( NULL == q) return;
	else{
		pp = q->next;
		q->next = pp->next;
		if (pp->next != NULL) pp->next->prev = q;
		free(pp);
		L->spt--;
		if(NULL == L->pTail || pp == L->pTail)
			L->pTail = q;
	}
}

void del_K(DList *L, int k) {
    Node *p = search(*L, k);
    if (p == NULL) return;
    if (p == L->pHead) del_Head(L);
	else if 
		(p == L->pTail) del_Tail(L);
    else {
        p->prev->next = p->next;
        p->next->prev = p->prev;
        free(p);
        L->spt--;
    }
}
///////////////////////////////////////
void nhap(Data *x){
	printf("Nhap ma sv: ");
	scanf("%d", &(x->masv));
	if(x->masv > 0){
	printf("Nhap ho ten sv: ");
	scanf("%s", (x->hoten));
	printf("Nhap diem mon 1: ");
	scanf("%f", &(x->d1));
	printf("Nhap diem mon 2: ");
	scanf("%f", &(x->d2));
	printf("Nhap diem mon 3: ");
	scanf("%f", &(x->d3));
}
}
void in(Data x){
	printf("Ten: %s, Ma: %d, Diem 1: %.2f, Diem 2: %.2f, Diem 2: %.2f\n",
	x.hoten, x.masv, x.d1, x.d2, x.d3);
}
void processList(DList L){
	if (emptyList(L)) return;
	Node *pp = L.pHead;
	while (pp != NULL) {
        in(pp->infor);
        pp = pp->next;
	}
}

void processListReverse(DList L) {
    if (emptyList(L)) return;
    Node *pp = L.pTail;
    while (pp != NULL) {
        in(pp->infor);
        pp = pp->prev;
    }
}

/////////////////////////////////////////

int main(){
	DList L;
	int kt = 0;
	Data x;
	int ma;
	Node *q;
	initList(&L);
	do{
		printf("\nChuong trinh lam viec voi DSLK don SV\n");
		printf("\n1: Them nut vao dau danh sach");
		printf("\n2: Them nut vao cuoi danh sach");
		printf("\n3: Them nut vao sau mot nut khac trong danh sach");
		printf("\n4: Xoa nut o dau danh sach");
		printf("\n5: Xoa nut o cuoi danh sach");
		printf("\n6: Xoa nut o sau mot nut khac trong danh sach");
		printf("\n7: Xoa nut co khoa K trong danh sach");
		printf("\n8: Duyet nguoc ds (tu duoi len tren)");
		printf("\n9: Duyet xuoi ds (tu tren xuong duoi)");
		printf("\n0: Thoat");
		printf("\nMoi ban chon: ");
		int chon;
		scanf("%d", &chon);
		switch(chon){
			case 1:
				printf("Nhap so thong tin sv can them\n");
				nhap(&x);
				if(x.masv > 0)
					insert_Head(&L, x);
				break;
			case 2:
				printf("Nhap so thong tin sv can them\n");
				nhap(&x);
				if(x.masv > 0)
					insert_Tail(&L, x);
				break;
			case 3:
				printf("Nhap ma sv cua nut dung truoc: ");
                scanf("%d", &ma);
                q = search(L, ma);
                if (q != NULL) {
                    printf("Nhap thong tin sv can chen\n");
                    nhap(&x);
                    if (x.masv > 0)
                        insert_After(&L, q, x);
                } else {
                    printf("Khong tim thay ma sv %d!\n", ma);
                }
				break;
			case 4:
				del_Head(&L);
				break;
			case 5:
				del_Tail(&L);
				break;
			case 6:
				printf("Nhap ma sv cua nut q: ");
                scanf("%d", &ma);
                q = search(L, ma);
                if (q != NULL) {
                    if (q->next == NULL) {
                        printf("Nut nay dang o cuoi ds, khong co phan tu nao phia sau de xoa!\n");
                    } else {
                        del_After(&L, q);
                    }
                } else {
                    printf("Khong tim thay ma sinh vien %d!\n", ma);
                }
                break;
            case 7:
            	printf("Nhap ma sv can xoa: ");
                scanf("%d", &ma);
                del_K(&L, ma);
                break;
            case 8:
            	processListReverse(L);
                break;
			case 9:
				processList(L);
				break;
			case 0:
				printf("Bye bye\n");
				kt = 1;
				break;
		}
	}
	while(kt==0);
	return 0;
}


