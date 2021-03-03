#include<stdio.h>
#include<stdlib.h>
#include"headers.h"

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

node DelHead(node head){
    head=head->next;
    return head;
}

node DelTail(node head){
    node p=head;
    while (p->next->next!=NULL){
        p=p->next;
    }
    p->next=NULL;
    return head;
}

int GetLength(node head){
    node p=head;
    int count=0;
    while (p!=NULL){
        p=p->next;
        count++;
    }
    return count;
}

void PrintList(node head){
    node p=(node)malloc(sizeof(struct LinkedList));
    p=head;
    int dem=0;
    while(p!=NULL){
        printf("Node %d's value: %d\n",dem,p->data);
        dem++;
        p=p->next;
    }
}

//Queue
void MakeNULLQueue(Queue *Q){
    Q->Front=NULL;
    Q->Rear=NULL;
}

int is_empty_queue(Queue *Q){
    return (Q->Front==NULL);
}

void EnQueue(Queue *Q, Address data){
    node temp=(node)malloc(sizeof(struct LinkedList));
    temp->next=NULL;
    temp->data=data;
    if(is_empty_queue(Q)){
        Q->Front=temp;
        Q->Rear=temp;
    } else {
        Q->Rear->next=temp;
        Q->Rear=Q->Rear->next;
    }
    printf("Data EnQueued: %d\n",temp->data);
}

void DeQueue(Queue *Q, Address *data){
    if(!is_empty_queue(Q)){
        node temp;
        *data=Q->Front->data;
        temp=Q->Front;
        Q->Front=Q->Front->next;
        free(temp);
        printf("Data DeQueued: %d\n",*data);
    }
    else printf("Queue is empty!\n");
}


//Stack
node push(node top,Address value) {
    node temp = Initialize(value);
    if (top == NULL) top = temp;
    else {
        temp->next = top;
        top=temp;
    }
    return top;
}

node pop(node top,Address *value){
    node temp=(node)(malloc(sizeof(struct LinkedList)));
    if (top==NULL) {
        printf("Nothing to pop!\n");
    }
    *value = (top->data);
    temp=top;
    top=top->next;
    free(temp);
    printf("Data poped: %d\n",*value);
    return top;
}

int is_empty_stack(node top){
    return top==NULL;
}


//BST
int empty_tree(treenode n){
    return n==NULL;
}

treenode createnode(Address c){
    treenode T=(treenode)malloc(sizeof(node));
    T->value=c;
    T->right=NULL;
    T->left=NULL;
    return T;
}

int is_leaf(treenode n){
    if(n!=NULL) return (n->right==NULL&&n->left==NULL);
    else return -1;
}

int nb_of_nodes(treenode n){
    if(empty_tree(n)) return 0;
    else return (1+nb_of_nodes(n->right)+nb_of_nodes(n->left));
}

treenode InsertToTree(treenode n,Address data){
    if(n==NULL) {
        treenode p=createnode(data);
        return p;
    }
    if(data<n->value) n->left= InsertToTree(n->left,data);
    else if(data > n->value) n->right=InsertToTree(n->right,data);
    return n;
}

void InOrder(treenode n){
    if(n==NULL) return;
    InOrder(n->left);
    printf("%d ",n->value);
    InOrder(n->right);
}

int count_leaf(treenode n){
    int leaf=1;
    if(n==NULL) return 0;
    if (is_leaf(n)) return 1;
    else return count_leaf(n->right)+count_leaf(n->left);
}

int height(treenode n){
    if(n==NULL) return 0;
    else if(is_leaf(n))
        return 1;

    int l=height(n->left);
    int r=height(n->right);
    return l<r ? (r+1):(l+1);
}