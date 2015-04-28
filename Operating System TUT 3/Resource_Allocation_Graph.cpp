#include<iostream>
#include<new>
using namespace std;

void DFS( int i, string type, bool & cyc,int & act, int & count,string p_array[],int no_resources,string r_array[]
         ,int no_process,string** arr,int instance_resource[])
{
    if ( type == "process")
    {
        if( p_array[i] == "white")    //not visited
        {
            p_array[i] = "black";
            for( int j=0; j<no_resources;j++)
            {
               if( arr[i][j] == "R" || "C")
               {
                   DFS(j,"resource",cyc,act,count,p_array,no_resources,r_array,no_process,arr,instance_resource);
               }
            }
        }

        else                         //visited
        {
            cyc = true;
            return;
        }
    }

    else
    {
        if (r_array[i] == "white")      //not visited the resource
        act += instance_resource[i];    //increment by total no resources

        r_array[i] == "black";

        for( int k=0; k < no_process; k++)
        {
            if( arr[k][i] == "A")
            {
               /* bool decrement = false;
                for( int l=0; l<no_resources;l++)
                {
                    if( arr[k][l] == "R" || "C")
                    decrement = true;
                }

                if( decrement == true)
                count++;
                */

                DFS(k,"process",cyc,act,count,p_array,no_resources,r_array,no_process,arr,instance_resource);
            }
        }
    }
}

int main()
{
    int actual = 0, counter = 0,no_process,no_resources;

    cout << "Enter number of processes : ";
    cin >> no_process;
    cout << "Enter number of resources : ";
    cin >> no_resources;

    cout << endl;

    //instances of resources
    int* instance_resource = new int[no_resources];
    for( int i=0 ; i<no_resources; i++)
    {
       // cout << "Enter number of instances of Resource " << i+1 << " : ";
       // cin >>  instance_resource[i];
       instance_resource[i] = 1;

    }


    string ** arr = new string*[no_process];
    for( int i=0; i<no_process; i++)
    {
        arr[i] = new string[no_resources];
    }

    //resource can have only one request edge

    for( int i=0; i<no_process; i++)
    {
        cout << endl;
        cout << "\t\tProcess " << i+1 << " :" << endl ;
        cout << "Enter R for requested resources\n" ;
        cout << "Enter A for allocated resources\n";
        cout << "Enter C for claim resources\n" ;
        cout << "Else enter N\n\n";

        for( int j=0; j<no_resources; j++)
        {
            cout << "Resource " << j+1 << "  : " ;
            cin >> arr[i][j];
        }
    }

    //arrays storing colors of resources and processes
    string * p_array = new string[no_process];
    for( int i = 0; i< no_process; i++)
    {
        p_array[i] = "white";
    }

    string * r_array = new string[no_resources];
    for( int i = 0; i< no_resources; i++)
    {
        r_array[i] = "white";
    }

    bool cycle = false;
    //main part

    for( int i=0; i<no_process; i++)
    {
        if ( p_array[i] == "white")
        {
            DFS(i,"process",cycle,actual,counter,p_array,no_resources,r_array,no_process,arr,instance_resource);
        }
    }

    cout << endl;
   // if( cycle == true && actual == counter)    // this is for multiple instances
    if ( cycle == true)
    cout << "Deadlock has occured" << endl;

    else
    cout << "No deadlock occurs" << endl;

    return 0;

}
