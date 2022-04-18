//mark-sweep method
#include<stdio.h>
#include<stdlib.h>

typedef struct node_tag{
    int data;
    int count;                  //for ref. count
    int bit;                    //for mark-sweap
    struct node_tag *ptr1;
    struct node_tag *ptr2;
    struct node_tag *ptr3; 
}node;
typedef struct root_tag{
    node *ptr;

}root;

node *adj[11];
root root1;
root root2;
node *create_node(int val){
    node* n = (node*)malloc(sizeof(node));
    n->data = val;
    n->count = 0;
    n->bit = 0;
    n->ptr1 = NULL;
    n->ptr2 = NULL;
    n->ptr3 = NULL;
    return n; 
}

void display_node(node *temp)
{
    printf(" %d", temp->data);
    if (temp->ptr1 != NULL || temp->ptr2 != NULL || temp->ptr3 != NULL)
    {
        printf("->(");
        if (temp->ptr1)
            display_node(temp->ptr1);
        if (temp->ptr2)
            display_node(temp->ptr2);
        if (temp->ptr3)
            display_node(temp->ptr3);
        printf(")");
    }
}
void display_heap(){
    for(int i=0 ; i<11 ; i++){
        if(adj[i]!=NULL){
            display_node(adj[i]);
            printf("\n");
        }
    }
}
void display_root(){
    printf("\n\tRoot1->");
    display_node(root1.ptr);
    printf("\n\tRoot2->");
    display_node(root2.ptr);
    printf("\n");
}
void create_schema(){
    //Creating nodes of value mentioned in heap schema
    for(int i=0;i<11 ; i++){
        if(i==0 || i==4 || i==6){
            adj[i]=NULL;
        }
        else{
            node *newnode = create_node(i);
            adj[i]= newnode;
        }
    }
    //creating links and incrementing count varible
    root1.ptr = adj[5];      adj[5]->count++;   //root1---->5
    root2.ptr = adj[1];      adj[1]->count++;   //root2---->1
    adj[5]->ptr1=adj[1];     adj[1]->count++;   //5-------->1
    adj[7]->ptr1=adj[1];     adj[1]->count++;   //7-------->1
    adj[7]->ptr2=adj[8];     adj[8]->count++;   //7-------->8
    adj[3]->ptr1=adj[8];     adj[8]->count++;   //3-------->8
    adj[3]->ptr2=adj[10];    adj[10]->count++;  //3-------->10
    adj[1]->ptr1=adj[2];     adj[2]->count++;   //1-------->2
    adj[1]->ptr2=adj[9];     adj[9]->count++;   //1-------->9
    adj[1]->ptr3=adj[10];    adj[10]->count++;  //1-------->10
    adj[8]->ptr1=adj[9];     adj[9]->count++;   //8-------->9

}

void mark(node* temp){
    if (temp==NULL){
        return;
    }
    else{
        if (temp->bit==0){
         temp->bit=1;
         printf("\n\tNode(memory)with data %d marked", temp->data);
         if(temp->ptr1) mark(temp->ptr1);
         if(temp->ptr2) mark(temp->ptr2);
         if(temp->ptr3) mark(temp->ptr3);               
        }
        
    }
}
void sweep(){
    for(int i = 0 ; i<11 ; i++){
        if (adj[i]!=NULL)
        {
            if (adj[i]->bit==0)
            {
                printf("\tNode(memory)with data %d sweeped\n",adj[i]->data);
                adj[i]->ptr1 = NULL;
                adj[i]->ptr2 = NULL;
                adj[i]->ptr3 = NULL;
                free(adj[i]);
                adj[i]=NULL;
            }
            else{
                adj[i]->bit=0;
            }
            
        }
        
    }
}
void garbage_collector(){
    printf("Mark phase started :\n");
    mark(root1.ptr);
    mark(root2.ptr);
    printf("\n\nSweep phase started :\n\n");
    sweep();
}
int main(){
    create_schema();
    printf("\nUSEFUL HEAP :");
    display_root();
    printf("\nTOTAL HEAP :\n");
    display_heap();
    printf("\nGarbage collector (mark-sweep) is called\n\n");
    garbage_collector();
    printf("\nTotal heap after garbage collection (mark-sweep method) :\n");
    display_heap();
    return 0;
}