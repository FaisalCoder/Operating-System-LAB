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
    vector<process> fcfs;
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

                fcfs.push_back(insert);

                cout << endl;


        }while( true );

        if ( fcfs.size() == 0)
        {cout << "No process to execute" << endl;return 2;}

        cout << "\t\t" << "GANTT CHART OF FCFS :" << endl;

        int curr = fcfs[0].arr_t;
        float waiting_time=0,turn_around=0;
        for( int i=0; i< fcfs.size() ; i++)
        {
            while ( fcfs[i].arr_t > curr)
            {
                cout << "empty" ;
                curr++;
            }


                waiting_time += curr - fcfs[i].arr_t;
                turn_around += curr+fcfs[i].exe_t - fcfs[i].arr_t;
                cout << curr << " " << fcfs[i].name << " " << curr+fcfs[i].exe_t << endl;
                curr += fcfs[i].exe_t;


        }

        float avg_wt = waiting_time/fcfs.size();
        float avg_tt = turn_around/fcfs.size();

        cout << "AVG WAITING TIME : " << avg_wt << endl;
        cout << "AVG TURN-AROUND TIME : " << avg_tt << endl;


        return 0;
}
