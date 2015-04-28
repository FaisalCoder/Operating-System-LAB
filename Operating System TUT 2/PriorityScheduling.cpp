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
    vector<process> priority;
    int choice,length=0;
    string name;
    int at,pt,prior;

    do{
            cout << "Press 1 to enter data" << endl;
            cout << "Press 0 to execute " << endl;

            cin >> choice ;

                if ( choice != 1) break;

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

                priority.push_back(insert);

                cout << endl;

            }while( true );


            if ( priority.size() == 0)
            {cout << "No process to execute" << endl;return 2;}

        cout << "\t\t" << "GANTT CHART OF PRIORITY SCHEDULING :" << endl;
        float waiting_time=0,turn_around=0;

        process temp;
        int key,j;
        for( int i=0; i< priority.size() ; i++)
        {
            key = priority[i].arr_t;
            temp = priority[i];
            j = i-1;
            while( j >= 0 && priority[j].arr_t > key )
            {
                priority[j+1] = priority[j];
                j--;
            }
            priority[j+1] = temp;
        }

       vector<process> t(priority);
       vector<process>::iterator it;
       int curr=0,i=0,min =2349239 ,index;


       while( t.size() != 0 )
        {
            if ( t[i].arr_t > curr )
            {curr++;cout << "empty" ;}

            else
            {
                for ( int k=0; k< t.size(); k++)
                {
                    if ( min > t[k].priority && t[k].arr_t <= curr ) {min = t[k].priority;index=k;}
                }

             waiting_time += curr- t[index].arr_t;
             turn_around += curr + t[index].exe_t - t[index].arr_t;

             cout << curr << " " << t[index].name <<  " " << curr+t[index].exe_t << " Priority : " << t[index].priority << endl;
             curr += t[index].exe_t;
             min=2349239;
             it = t.begin();
             t.erase(it+index);
            }
        }

        float avg_wt = waiting_time/priority.size();
        float avg_tt = turn_around/priority.size();

        cout << "AVG WAITING TIME : " << avg_wt << endl;
        cout << "AVG TURN-AROUND TIME : " << avg_tt << endl;

        return 0;
}
