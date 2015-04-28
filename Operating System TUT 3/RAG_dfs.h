#ifndef RAG_DFS_H_INCLUDED
#define RAG_DFS_H_INCLUDED
#include<iostream>
#include<new>
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

#endif // RAG_DFS_H_INCLUDED
