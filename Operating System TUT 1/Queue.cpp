#include<iostream>
#include<new>
#include<string>
using namespace std;

struct node
{
   int pid;
   string status;
   bool io_required;
   node* next;
};

class Queue
{
   private:
   node* head,*tail;

   public:
   static int ID;

   Queue(){head = tail = NULL;}

   void enqueue( int id, string status2,bool io)
   {
      // enter required data
      node* newnode = new node;
      newnode->pid = id;
      newnode->status = status2;
      newnode->next = NULL;
      newnode->io_required = io;

      if( head == NULL)
      head = tail = newnode;

      else
      {
         tail->next = newnode;
         tail = tail->next;
      }
    }

    void dequeue()
    {
       node* ptr1 = head;
       node* ptr2 = tail;

       if ( ptr1 == NULL)
       cout << "\t\tQUEUE IS EMPTY" << endl;

       else
       {
         if( tail == head)
         tail = NULL;

         head = head->next;
         delete ptr1;
       }
    }

    void add_anywhere(int index, int id2, string status2,bool io2)
    {
       node* p1 = head;
       node* p2 = tail;

       if( index < 0 )
       cout << "Enter valid index" << endl;

       else
       {
          // enter required data
	     node* newnode = new node;
	     newnode->pid = id2;
	     newnode->status = status2;
	     newnode->io_required = io2;

             int counter=0;

             while( p1 != NULL && index>counter)
             {
               p1 = p1->next;
               counter++;
             }

             if ( index == counter)
             {
                if( p1 == head )
                enqueue(id2,status2,io2);

                else
                {
                  newnode->next = p1->next;
                  p1->next = newnode;
                }
             }

             else
             cout << "Enter valid index" << endl;
       }
}
       void del_anywhere( int index)
       {
          if ( index < 0)
          cout << "Enter valid index" << endl;

          int counter=0;
          node* p1 = head,*prev;

          while( p1 != NULL && index>counter)
          {
             prev = p1;
             p1 = p1->next;
             counter++;
          }

          if ( index == counter)
          {
             if( index == 0)
             dequeue();

             else
             {
               prev->next = p1->next;
               delete p1;
             }
          }

          else
          cout << "Enter valid index" << endl;
       }

	void display()
	{
	   node* p1 = head;
	   while( p1 != tail)
	   {
	     cout << "PROCESS ID : " << p1->pid << endl;
	     cout << "STATUS : " << p1->status << endl;

	     if(p1->io_required == true)
	     cout << "I/O REQUIRED : YES" << endl;

	     else
	     cout << "I/O REQUIRED : NO"  << endl;

	     p1 = p1->next;
	     cout << endl;
	   }

	   if( tail != NULL)
	   {
	     cout << "PROCESS ID : " << p1->pid << endl;
	     cout << "STATUS : " << p1->status << endl;

	     if(p1->io_required == true)
	     cout << "I/O REQUIRED : YES" << endl;

	     else
	     cout << "I/O REQUIRED : NO"  << endl;

	     p1 = p1->next;
	     cout << endl;
	   }

	   else
	   cout << "\t\tQUEUE IS EMPTY" << endl;
       cout << endl;
	}

    friend void copy_all( Queue & ,Queue &  );
    friend void transfer_one( Queue & , node*);
    friend void execute_one( Queue & , Queue &, Queue& );

    node* return_head()
    {
        return head;
    }
};

void copy_all( Queue & a,Queue & b )
{
    node* p1 = a.head;

    while( p1 != NULL)
    {
        b.enqueue(p1->pid,p1->status,p1->io_required);
        a.dequeue();
        p1 = a.head;
    }
}

void execute_one( Queue & a, Queue & b,Queue& c)
{
    node*p = a.head;
    int ch3;
    cout << "Process ID : " << p->pid << endl;

    if( p->io_required == true)
    {
        cout << "Press 0 to skip " << endl;
        cout << "Press any other number to enter input " << endl;
        cout << "Input : ";
        cin >> ch3;

        if( ch3 == 0 )
        {
            p->status = "Waiting I/O";
            transfer_one(b,p);
            cout << "Process moved to I/O queue" << endl;
        }

        else
        {
            p->status = "Completed";
            transfer_one(c,p);
            cout << "Process completed!!" << endl;
        }
    }

    else
    {
        p->status = "Completed";
        transfer_one(c,p);
        cout << "Process completed!!" << endl;
    }

    a.dequeue();

}

void transfer_one( Queue & a, node*p)
{
    a.enqueue(p->pid,p->status,p->io_required);
}

int main()
{
   Queue job,ready,wait,executed;

   int ch1 = 1;

   while( ch1 == 1)
   {
       cout << "Press 1 to add new process" << endl;
       cout << "Press 2 to execute all processes" << endl;
       cout << "Input : ";
       cin >> ch1;

       if(ch1 != 1)
       break;

       int id2;
       string status2="Incomplete";
       bool io2;
       cout << "Enter Process ID : ";
       cin >> id2;
       cout << "Enter whether I/O required in the process : (YES = 1/NO = 0) ";
       cin >> io2;

       job.enqueue(id2,status2,io2);
       cout << endl;
   }

   cout << "\t\tPROCESSES IN JOB QUEUE " << endl;
   cout << endl;
   job.display();

   copy_all( job, ready );

   cout << "\t\tPROCESSES IN READY QUEUE " << endl;
   cout << endl;
   ready.display();

   int ch2,ch4 ;
   node* p = ready.return_head();

   while( p != NULL)
   {
       cout << "Press 1 to execute all the process in the ready queue" << endl;
       cout << "Press 2 to create an interrupt " << endl;
       cout << "Input : ";
       cin >> ch2;
       cout << endl;

       if( ch2 == 1)
       {
           execute_one(ready,wait,executed);
       }

       else
       {
           int id;
           string status = "Incomplete";
           bool io ;

           cout << "Enter process ID : " ;
           cin >> id;
           cout << "Enter whether I/O required in the process : (YES = 1/NO = 0) ";
           cin >> io;

           node* newnode = new node;
           newnode->pid = id;
           newnode->status = status;
           newnode->io_required = io;


           if ( io == false)
           {
               newnode->status = "Completed";
               transfer_one( executed,newnode);
           }

           else
           {
               cout << "Press 0 to skip " << endl;
               cout << "Press any other number to enter input " << endl;
               cout << "Input : ";
               cin >> ch4;

               if(ch4 == 0)
               {
                   newnode->status = "Waiting I/O";
                   transfer_one(wait,newnode);
               }

               else
               {
                   newnode->status = "Completed";
                   transfer_one(executed,newnode);
               }
            }
           }

           p = ready.return_head();
           cout << endl;
       }

   cout << "\t\tPROCESSES IN READY QUEUE " << endl << endl;
   ready.display();

   cout << "\t\tPROCESSES IN WAITING QUEUE " << endl << endl;
   wait.display();


   //process in waiting queue
    p = wait.return_head();
   int ch5;

   while( p != NULL)
   {
       cout << "Process ID : " << p->pid << endl << endl;
       cout << "Press 1 to skip" << endl;
       cout << "Press 2 to enter I/O" << endl;
       cin >> ch5;
       cout << endl;

       if( ch5 == 2)
       {
           string dummy;
           cout << "Enter I/O data : ";
           cin >> dummy;
           p->status = "Completed";
           cout << "Process completed!!" << endl;
           transfer_one(executed,p);
           wait.dequeue();
       }

       else
       {
           wait.enqueue(p->pid,p->status,p->io_required);
           wait.dequeue();
       }

       p = wait.return_head();
       cout << endl;
   }
   cout << endl;

   cout << "\t\tALL PROCESSES COMPLETED SUCCESSFULLY" << endl << endl;
   executed.display();

   return 0;
}






