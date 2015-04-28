#include<iostream>
#include<string>
#include<list>
#include<vector>
using namespace std;

struct process
{
    string name;
    int arr_t,exe_t,priority;
    string status;
};

int main()
{
    vector<process> p_sjf;
    int choice,length=0;
    string name;
    int at,pt,prior;

       do{
            cout << "Press 1 to enter data" << endl;
            cout << "Press 0 to execute " << endl;

            cin >> choice ;

                if ( choice != 1) break;
                length++;

                cout << "Enter name of the process " << endl;
                cin >> name;
                cout << "Enter arrival time of the process " << endl;
                cin >> at;
                cout << "Enter processing of the process " << endl;
                cin >> pt;
                cout << "Enter priority of the process " << endl;
                cin >> prior;

                process insert;
                insert.arr_t = at;
                insert.priority = prior;
                insert.exe_t = pt;
                insert.name = name;
                insert.status = "done";

                p_sjf.push_back(insert);

                cout << endl;


        }while( true );

        if ( p_sjf.size() == 0)
        {cout << "No process to execute" << endl;return 2;}

        //processing
        int key;process temp;int j;
      //  process* p_sjf = new process[length];

        for( int i=0; i< p_sjf.size() ; i++)
        {
            key = p_sjf[i].arr_t;
            temp = p_sjf[i];
            j = i-1;
            while( j >= 0 && p_sjf[j].arr_t > key )
            {
                p_sjf[j+1] = p_sjf[j];
                j--;
            }
            p_sjf[j+1] = temp;
        }

        int curr=0,i=0,min =2349239 ,index,prev;
        vector<process> t(p_sjf);
        vector<process>::iterator it;

        while( t.size() != 0 )
        {
            if ( t[i].arr_t > curr )
            {curr++;cout << "empty" ;}

            else
            {
                for ( int k=0; k< t.size(); k++)
                {
                    if ( min > t[k].exe_t && t[k].arr_t <= curr ) {min = t[k].exe_t;index=k;}
                }

               // if ( prev != index && )

             cout << curr << " " << t[index].name <<  " " << curr+1 << endl;

             it = t.begin();
             t[index].exe_t -= 1;
             if ( t[index].exe_t == 0)t.erase(it+index);

             curr += 1;
             min=2349239;
             prev = index;
        }
        }

        return 0;
}
