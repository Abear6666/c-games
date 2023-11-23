#include <stdio.h>
#include <stdlib.h>
struct  node 
{
    int data;
    struct  node *next;
};

//创建节点函数 
struct  node*CreateNode(int data)
{
    struct  node  *new_node = malloc(sizeof( struct  node )); 
    new_node->data = data; 
    new_node->next = NULL;

    return  new_node;
}

//插入数据 
void InsertNode(struct  node *head,int data)
{
    //1.创建节点 
    struct  node *new_node = CreateNode(data); 

    //2.插入 
    new_node->next = head->next; 
    head->next = new_node; 
}
//头插节点
void Top_Insert(struct  node *head,struct  node *new_node)
{
    //2.插入 
    new_node->next = head->next; 
    head->next = new_node; 
}

//遍历节点 
void TraverseNodes(struct  node *head)
{
   struct  node *pos = head->next; 

   while (pos!=NULL)
   {
      printf("%d\n",pos->data);
      pos = pos->next;
   }
   printf("_____________________\n");
}


//链表翻转
void Revers_List(struct  node *head)
{
    //创建一个临时的头节点 
    struct  node *tmp_head = CreateNode(0);

    while (head->next != NULL)  //不断提取一个链表的节点，直到他为NULL 
    {
        ///把提取到的节点用pos 指向 
        struct  node *pos = head->next; 
        head->next = pos->next; 
        pos->next  = NULL;

        //2.插入新的链表 头插进去数据 
        Top_Insert(tmp_head,pos);
    }
    

    //重新利用第一个头节点 
    head->next = tmp_head->next; 

    free(tmp_head);

}


int main()
{

    //1.创建头节点 
    struct  node *head = CreateNode(0);
   


    InsertNode(head,10);
    InsertNode(head,20);
    InsertNode(head,30);
    InsertNode(head,40);
    InsertNode(head,50);
    TraverseNodes(head);

    //翻转链表
    Revers_List(head); 

    TraverseNodes(head);
     //翻转链表
    Revers_List(head); 
    TraverseNodes(head);
}
