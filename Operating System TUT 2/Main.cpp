//#include<iostream>
#include"SJF.cpp"



//using namespace std;




    vector<process> main;
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

                main.push_back(insert);

                cout << endl;

            }while( true );
            int ch;
            do
            {
                cout << "Press 1 for FCFS " << endl;
                cout << "Press 2 for SJF " << endl;
                cout << "Press 3 for Preemptive SJF " << endl;
                cout << "Press 4 for Round Robin " << endl;
                cout << "Press 5 for Priority Scheduling " << endl;
                cout << "Press 0 to exit " << endl;

                cin >> ch;

                switch( ch )
                case 1 : ;

            }while ( ch != 0);


    return 0;
}
