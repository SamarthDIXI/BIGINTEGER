#include<stdio.h>
#include<stdlib.h>
struct node
{
    int data;
    struct node *next;
};
int length(struct node *head)
{
    int l=0;
    while(head)
    {
        head=head->next;
        l++;
    }
    return l;
}
int compare(struct node *head1, struct node *head2)
{
    while(head1 && head2)
    {
        if(head1->data>head2->data)
            return 1;
        if(head1->data<head2->data)
            return -1;
        head1=head1->next;
        head2=head2->next;
    }
    return 0;
}
int greater(struct node*head1,struct node* head2)
{
    if(length(head1)>length(head2))
      {
          return 1;
      }
      else if(length(head1)<length(head2))
      {
          return -1;
      }
      else
      {
          if(compare(head1,head2)==1)
          {
              return 1;
          }
          else if(compare(head1,head2)==-1)
          {
              return -1;
          }
          else
          {
            return 0;
          }
      }
}
void Head(struct node **head,int val)//adding at the head
{
  struct node* temp=(struct node*)malloc(sizeof(struct node));
  if(temp==NULL)
  {
    printf("Memory Allocation Failed!!\n");
    return;
  }
  temp->data=val;
  if((*head)==NULL)
  {
    (*head)=temp;
    temp->next=NULL;
    return;
  }
  temp->next=(*head);
  (*head)=temp;
}
void Tail(struct node **head,int val)//adding at the tail
{
  struct node* temp=(struct node*)malloc(sizeof(struct node));
  if(temp==NULL)
  {
    printf("Memory Allocation Failed!!\n");
    return;
  }
  temp->data=val;
  temp->next=NULL;
  if((*head)==NULL)
  {
    (*head)=temp;
    return;
  }
  struct node *itr=(*head);
  while(itr->next!=NULL)
    {
      itr=itr->next;
    }
  itr->next=temp;
}
struct node *createLL(char a[])
{
    struct node *head=NULL;
  int i=0;
  int v=0;
  while(a[i]!='\0')
  {
    v=(int)a[i]-48;
    Tail(&head,v);
    i++;
  }
  return head;
}
void deletefromtail(struct node **head)
{
    struct node *temp=NULL;
    if(!(*head))                                               //no node present
    {
    return;
    }
    if(!(*head)->next)                                         //one node present
    {
        temp=*head;
        *head=NULL;
        free(temp);
        return;
    }
    struct node *itr=*head;
    while(itr->next->next!=NULL)
    {
        itr=itr->next;
    }
    temp=itr->next;
    itr->next=NULL;
    free(temp);
}
void deletefromhead(struct node **head)
{
    struct node *temp=(*head);
    if(!(*head))
        return;
    (*head)=(*head)->next;
    free(temp);
}
void DisplayLL(struct node *head)//displaying as a linked list
{
  while(head!=NULL)
    {
      printf("%d->",head->data);
      head=head->next;
    }
  printf("NULL\n");
}
void DisplayNum(struct node *head)//displaying as a number
{
  if(head==NULL)
  {
    return;
  }
  printf("%d",head->data);
  DisplayNum(head->next);
}
void reverseLL(struct node **head)//reversing the linked list
{
  struct node *current=NULL;
  struct node *next= (*head)->next;
  (*head)->next=NULL;

  while(next!=NULL)
    {
      current=next;
      next=next->next;
      current->next=(*head);
      (*head)=current;
    }
}
struct node *Addition(char a[],char b[]) {
  struct node *head1=createLL(a);
  struct node *head2=createLL(b);\
  if(head1==NULL)
    return head2;
  else if(head2==NULL)
    return head1;
  reverseLL(&head1);
  reverseLL(&head2);
  struct node *h1 = head1;
  struct node *h2 = head2;
  struct node *add = NULL;
  int sum = 0;
  int carry = 0;
  while (head1 || head2) {
    sum = 0;
    if (head1)
      sum += head1->data;
    if (head2)
      sum += head2->data;
    sum += carry;
    carry = sum / 10;
    sum = sum % 10;
    Head(&add, sum);
    if (head1)
      head1 = head1->next;
    if (head2)
      head2 = head2->next;
  }
  if (carry)
    Head(&add, carry);
  reverseLL(&h1);
  reverseLL(&h2);
  return add;
}
struct node* Subtraction(struct node *head1,struct node *head2)//we are assuming that first number is always bigger than second one
{
  reverseLL(&head1);
  reverseLL(&head2);
  struct node *h1 = head1;
  struct node *h2 = head2;
  struct node *subtract=NULL;
  int diff=0;
  int borrow=0;
  while(head1||head2)
    {
      diff=0;
      if(head1)
        diff+=head1->data;
      if(head2)
        diff-=head2->data;
      diff-=borrow;
      if(diff<0)
      {
        diff+=10;
        borrow=1;
      }
      Head(&subtract,diff );
      if(head1)
        head1=head1->next;
      if(head2)
        head2=head2->next;
    }
    reverseLL(&h1);
  reverseLL(&h2);
  return subtract;
}
struct node* sub(char a[],char b[])
{
    struct node *head1=createLL(a);
    struct node *head2=createLL(b);
    struct node *subtract;
    if(length(head1)>length(head2))
            {
                subtract = Subtraction(head1, head2);
            }
            else if(length(head1)<length(head2))
            {
                subtract = Subtraction(head2, head1);
                subtract->data=-subtract->data;
            }
            else
            {
                if(compare(head1,head2)==1)
                {
                    subtract = Subtraction(head1, head2);
                }
                else if(compare(head1,head2)==-1)
                {
                    subtract = Subtraction(head2, head1);
                    subtract->data=-subtract->data;
                }
                else
                {
                    subtract = (struct node*)malloc(sizeof(struct node));
                    subtract->data=0;
                    subtract->next=NULL;
                }
            }
            return subtract;
}
struct node* Multiplication(char a[],char b[])
{
    struct node *head1=createLL(a);
    struct node *head2=createLL(b);
  reverseLL(&head1);
  reverseLL(&head2);
  struct node *h1=head1;
  struct node *h2=head2;
  struct node *itr=head1;
  struct node *add=NULL;
  struct node *add2=(struct node*)malloc(sizeof(struct node));
  add2->data=0;
  add2->next=NULL;
  struct node *add3=NULL;
  int i=0;
  int sum=0;
  int carry=0;
  while(head2)
    {
      while(itr)
      {
        sum=0;
        sum+=itr->data;
        sum*=head2->data;
        sum+=carry;
        carry=sum/10;
        sum=sum%10;

        Head(&add,sum);
        itr=itr->next;
      }
      if(carry)
      Head(&add,carry);
      int n=i;

      while(n--)
        {
          Tail(&add,0);
        }
      add2=Addition(add,add2);
      add=NULL;
      itr=head1;
      head2=head2->next;
      i++;
    }
    reverseLL(&h1);
    reverseLL(&h2);
  return add2;
}
struct node* division(char a[],char b[])
{
    struct node *head1=createLL(a);
    struct node *head2=createLL(b);
    int i=length(head1)-length(head2);
                        //printf("difference between numbers length:%d\n",i);
    struct node *div=NULL;
    int count=0;
    if(compare(head1,head2)==-1)
        i-=1;
                      // printf("difference after compare:%d\n",i);
    for(int k=0;k<i;k++)
    {
        Tail(&head2,0);
    }
                      //  printf("after adding zeros:");
                      //DisplayLL(head2);
    while(i>-1)
    {
        i--;
        while(greater(head1,head2)==1 || greater(head1,head2)==0)
        {
            head1=Subtraction(head1,head2);

        if(head1->data==0)
            {
                deletefromhead(&head1);
            }
            count++;
                        //printf("after deleting zero:");
                        //DisplayLL(head1);
        }

                        //printf("%d\n",count%10);
                        int c=count%10;
        Tail(&div,c);
        deletefromtail(&head2);
                        //printf("after delete from tail:");
                        //DisplayLL(head2);
        count=0;
    }
    return div;
}
int main()
{
  char n1[2000],n2[2000];
  printf("***************CALCULATOR***************\n");
  printf("Enter the first number:");
  gets(n1);

  printf("Enter the second number:");
  gets(n2);

  char choice;
  do
  {
      char ch;
    printf("ENTER THE OPERATOR (+,-,*,/,%) \n");
    printf("Operator:");
    scanf(" %c",&ch);// Note the space before %c to consume any whitespace characters
    switch(ch)
    {
        case '+':
            printf("*****ADDITION*****\n");
            struct node *add = Addition(n1, n2);
            DisplayNum(add);
            printf("\n");
            break;

        case '-':
            printf("******SUBTRACTION*****\n");
            struct node *subtract=sub(n1,n2);
            DisplayNum(subtract);
            printf("\n");
            break;

        case '*':
            printf("*****MULTIPLICATION*****\n");
            struct node *m = Multiplication(n1,n2);
            DisplayNum(m);
            printf("\n");
            break;

        case '/':
            printf("*****DIVISION*****\n");
            struct node *d = division(n1,n2);
            DisplayNum(d);
            printf("\n");
            break;
            default:
                printf("******INVALID CHOICE***** \nNOTE=please enter the choice carefully next time:)\n\n");
    }
    printf("Do you want to perform the another operation??(y/n):");
    scanf(" %c",&choice);// Note the space before %c to consume any whitespace characters
  }while(choice=='y' || choice=='y');
  printf("Goodbye!  Thank you for using the calculator.\n");
  return 0;
}
