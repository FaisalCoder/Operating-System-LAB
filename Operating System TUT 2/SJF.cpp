

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
    vector<process> sjf;
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

                sjf.push_back(insert);

                cout << endl;


        }while( true );

        if ( sjf.size() == 0)
        {cout << "No process to execute" << endl;return 2;}

        cout << "\t\t" << "GANTT CHART OF SJF :" << endl;
        //processing
        int key;process temp;int j;
      //  process* sjf = new process[length];

        for( int i=0; i< sjf.size() ; i++)
        {
            key = sjf[i].arr_t;
            temp = sjf[i];
            j = i-1;
            while( j >= 0 && sjf[j].arr_t > key )
            {
                sjf[j+1] = sjf[j];
                j--;
            }
            sjf[j+1] = temp;
        }

        int curr=0;
        vector<process> t(sjf);
        vector<process>::iterator it;

        int i=0;int min=2349239,index=0;


        float waiting_time=0,turn_around=0;

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


             waiting_time += curr- t[index].arr_t;
             turn_around += curr+min - t[index].arr_t;

             cout << curr << " " << t[index].name <<  " " << curr+min << endl;
             curr += min;
             min=2349239;
             it = t.begin();
             t.erase(it+index);
            }
        }

        float avg_wt = waiting_time/sjf.size();
        float avg_tt = turn_around/sjf.size();

        cout << "AVG WAITING TIME : " << avg_wt << endl;
        cout << "AVG TURN-AROUND TIME : " << avg_tt << endl;

    return 0;
}


