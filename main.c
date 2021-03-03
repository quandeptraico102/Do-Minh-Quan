#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Address{
    char place[40];
    int hour;
    int minute;
}Address;

struct LinkedList{
    Address data;
    struct LinkedList* next;
};

typedef struct LinkedList *node;

node Initialize(Address value){
    node temp=(node)(malloc(sizeof(struct LinkedList)));
    temp->data=value;
    temp->next=NULL;
    return temp;
}

node AddHead(node head,Address value) {
    node temp = Initialize(value);
    if (head == NULL) head = temp;
    else {
        temp->next = head;
        head=temp;
    }
    return head;
}

node AddTail(node head, Address value){
    node temp=Initialize(value);
    node p=(node)(malloc(sizeof(struct LinkedList)));
    if (head == NULL) head = temp;
    else{
        p=head;
        while (p->next!=NULL){
            p=p->next;
        }
        p->next=temp;
    }
    return head;
}

void PrintList(node head){
    node p=(node)malloc(sizeof(struct LinkedList));
    p=head;
    int dem=0;
    printf("\n%-50s %-10s %-10s\n","Dia diem","Gio","Phut");
    while(p!=NULL){
        printf("%-50s %-10d %-10d\n",p->data.place,p->data.hour,p->data.minute);
        dem++;
        p=p->next;
    }
}

void FreeList(node head){
    node temp=head;
    while (head!=NULL)
    {
        head=head->next;
        free(temp);
        temp= head;
    }
}

void FindByPlace(node head){
    node p=(node)malloc(sizeof(struct LinkedList));
    p=head;
    int dem=0;
    fflush(stdin);
    char place[50];
    printf("Dia diem can tim kiem:\n");
    gets(place);
    while (p!=NULL)
    {
        if(strcmp(p->data.place,place)==0) {
            dem=1;
            printf(" %d:%d,",p->data.hour,p->data.minute);
        }
        p=p->next;
    }
    if(dem==0) printf("Ban chua toi dia diem do!\n");
}

void FindByTime(node head){
    node p=(node)malloc(sizeof(struct LinkedList));
    node temp=(node)malloc(sizeof(struct LinkedList));
    p=head;
    temp=head;
    aa:
    fflush(stdin);
    int hour, minute;
    printf("Thoi gian can tim kiem:\n");
    scanf("%d %d",&hour, &minute);
    if (hour<0 || hour>=24 || minute < 0 || minute >= 60) goto aa;
    
    if(hour==p->data.hour){
        if (minute < p->data.minute)
        printf("Khong tim thay lich su di chuyen\n");
    }
    if (hour<p->data.hour) printf("Khong tim thay lich su di chuyen\n");
    
    while (p!=NULL)
    {
        if(p->data.hour==hour){
            if (minute == p->data.minute)
            {
                printf("%s",p->data.place);
                break;
            }
            else if (minute < p->data.minute)
            {
                while (!(temp->next->data.hour == p->data.hour && temp->next->data.minute == p->data.minute))
                {
                    temp=temp->next;
                }
                printf("%s",temp->data.place);
                break;
            }
            else if (minute > p->data.minute)
            {
                if (p->next->data.hour == hour && minute > p->next->data.minute)
                {
                    printf("%s",p->next->data.place);
                    break;
                }
                else {
                    printf("%s",p->data.place);
                    break;
                }
            }
        }
        p=p->next;
    }
}

void CheckCovid(node head){
    Address temp;
    node p=(node)malloc(sizeof(struct LinkedList));
    node prev=(node)malloc(sizeof(struct LinkedList));
    p=head;
    prev=head;
    printf("Nhap thoi gian va dia diem:\n");
    fflush(stdin);
    fscanf(stdin,"%s %d %d",temp.place,&temp.hour,&temp.minute);
    while (p!=NULL)
    {
        if(strcmp(p->data.place,temp.place)==0){
            if (temp.hour >= p->data.hour && temp.hour <= p->next->data.hour)
            {
                if (temp.hour == p->data.hour && temp.minute >= p->data.minute)
                {
                    printf("Ban co kha nang bi lay COVID, can khai bao y te!\n");
                    break;
                }
                if(temp.hour == p->next->data.hour && temp.minute <= p->next->data.minute )
                {
                    printf("Ban co kha nang bi lay COVID, can khai bao y te!\n");
                    break;
                }
                if (temp.hour > p->data.hour && temp.hour < p->next->data.hour)
                {
                    printf("Ban co kha nang bi lay COVID, can khai bao y te!\n");
                    break;
                }
                else
                {
                    printf("Lich su di chuyen OK!\n");
                    break;
                }
            }
            else printf("Lich su di chuyen OK!\n");
        }
        p=p->next;
    }
}

void PrintMenu(){
    printf("\nCHUONG TRINH TRUY VET COVID19");
    printf("\n1.Nap file log lich su di chuyen");
    printf("\n2.In ra lich su di chuyen");
    printf("\n3.Tim kiem lich su theo dia diem");
    printf("\n4.Tim kiem lich su theo thoi gian");
    printf("\n5.Kiem tra truy vet moi nhat");
    printf("\n6.Thoat");
    printf("\nLua chon?");
}

int main(){
    FILE* fin=fopen("log.txt","r");
    int menu;
    Address temp;
    node head=NULL;
    do
    {
        PrintMenu();
        fflush(stdin);
        scanf("%d",&menu);
        switch (menu)
        {
        case 1:
            while (!feof(fin))
            {
                fscanf(fin,"%s %d %d",temp.place,&temp.hour,&temp.minute);
                head=AddTail(head,temp);
            }
            fclose(fin);
            break;
        case 2:
            PrintList(head);
            break;
        case 3:
            FindByPlace(head);
            break;
        case 4:
            FindByTime(head);
            break;
        case 5:
            CheckCovid(head);
            break;
        case 6:
            FreeList(head);
            return 0;
        default:
            printf("Lua chon sai!\n");
            break;
        }
    } while (menu!=6);
    
}