typedef int Address;

struct LinkedList{
    Address data;
    struct LinkedList* next;
};

typedef struct LinkedList *node;

typedef struct{
    node Front,Rear;
}Queue;

struct TNode{
    Address value;
    struct TNode* right;
    struct TNode* left;
};

typedef struct TNode *treenode;

node Initialize(Address value);
node AddHead(node head,Address value);
node AddTail(node head, Address value);
node DelHead(node head);
node DelTail(node head);
int GetLength(node head);
void PrintList(node head);

void MakeNULLQueue(Queue *Q);
int is_empty_queue(Queue *Q);
void EnQueue(Queue *Q, Address data);
void DeQueue(Queue *Q, Address *data);

node push(node top,Address value);
node pop(node top,Address *value);
int is_empty_stack(node top);


int empty_tree(treenode n);
treenode createnode(Address c);
int is_leaf(treenode n);
int nb_of_nodes(treenode n);
treenode InsertToTree(treenode n,Address data);
void InOrder(treenode n);
int count_leaf(treenode n);
int height(treenode n);