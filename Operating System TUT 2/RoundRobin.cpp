#include<iostream>
#include<string>
#include<map>
#include<vector>
using namespace std;

struct process
{
    string name;
    int arr_t,exe_t,priority;
    string status;
};

struct cal
{
    int ar,ex;
};

int main()
{
    vector<process> rr;
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

                rr.push_back(insert);

                cout << endl;

            }while( true );


            if ( rr.size() == 0)
            {cout << "No process to execute" << endl;return 2;}

          cout << "\t\t" << "GANTT CHART OF ROUND-ROBIN :" << endl;
        float waiting_time=0,turn_around=0;

        //sorting
        process temp;
        int key,j;
        for( int i=0; i< rr.size() ; i++)
        {
            key = rr[i].arr_t;
            temp = rr[i];
            j = i-1;
            while( j >= 0 && rr[j].arr_t > key )
            {
                rr[j+1] = rr[j];
                j--;
            }
            rr[j+1] = temp;
        }

       vector<process> t(rr);
       //moification
       multimap<string,cal> m;
       multimap<string,cal>::iterator it3;
       cal temp1;
       //
       vector<process>::iterator it;
       int curr=0,i=0;
       int quantum = 2,pseudoARRIVAL=0;

       while( t.size() != 0)
       {
           if ( curr < t[i].arr_t)
           {
               if ( i == 0)
               {
                  cout << "empty" << endl;
                  curr++;
               }
               else
               i=0;
           }

           else
           {
               if ( t[i].exe_t <= quantum)
               {
                  //  waiting_time += curr- t[i].arr_t;// wrong
                    turn_around += curr+t[i].exe_t - t[i].arr_t;//right

                   cout << curr << "  " << t[i].name << " " << curr+t[i].exe_t << endl;
                  // adding to map
                   temp1.ar = curr;
                   temp1.ex = curr+t[i].exe_t;


                   m.insert(pair<string,cal>(t[i].name,temp1));
                   //
                   curr += t[i].exe_t;
                   t.erase(t.begin()+i);

                   if ( i== t.size())i=0;// if last element deleted
               }

               else
               {
                   cout << curr << "  " << t[i].name << " " << curr+quantum << endl;

                   //adding to map
                   temp1.ar = curr;
                   temp1.ex = curr+quantum;


                   m.insert(pair<string,cal>(t[i].name,temp1));

                   //
                   curr += quantum;
                   pseudoARRIVAL  = curr;//
                   t[i].exe_t -= quantum;

                   i++;
                   i = i%t.size();
               }
           }
       }

      //calculating avg_wt
       float wt=0;
       for( int i=0; i<rr.size(); i++)
       {
           float prev=0;
           it3 = m.find(rr[i].name);

           float temp = 0;int coun = 0;

           while( it3 != m.end() && (it3->first) == rr[i].name)
           {
               if( coun == 0)
               {
                   temp += (it3->second).ar - rr[i].arr_t;
                 //  cout << temp << endl;
                 //  cout << (it3->second).ar << "  " << it3->first << "  "   <<  (it3->second).ex << endl;
               }

               else
               {
                   temp += (it3->second).ar - prev;
                  // cout << temp << endl;
                   //cout << (it3->second).ar << "  " << it3->first << "  "   <<  (it3->second).ex << endl;
               }

               prev = (it3->second).ex;
               it3++;
               coun++;
           }

           wt += temp;
         //  cout << "next" << endl;
       }


       //

        float avg_wt = wt/rr.size();
        float avg_tt = turn_around/rr.size();

        cout << "AVG WAITING TIME : " << avg_wt << endl;
        cout << "AVG TURN-AROUND TIME : " << avg_tt << endl;

//    system("pause");
    return 0;
}
