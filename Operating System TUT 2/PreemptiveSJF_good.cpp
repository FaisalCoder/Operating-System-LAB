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

         cout << "\t\t" << "GANTT CHART OF PREMPTIVE SJF :" << endl;
        float waiting_time=0,turn_around=0;

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

        int curr=0,i=0,min =2349239 ,index,prev=0,time=0,time_f=1,initial=0,m=0;
        vector<process> t(p_sjf);
        vector<process>::iterator it;
        process p;
        vector<process> q;



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


//                 cout << curr << " " << t[index].name <<  " " << curr+1 << endl;


                 if ( q.size() == 0)
                 {
                     p.name = t[index].name;
                     p.arr_t = curr;
                     p.exe_t = curr+1;
                     p.priority = 1;
                      q.push_back(p);
                 }

                 else if (  q[m].name == t[index].name )
                 {
                     q[m].exe_t++;
                 }

                 else
                 {
                     m++;
                     p.name = t[index].name;
                     p.arr_t = curr;
                     p.exe_t = curr+1;
                     p.priority = 1;
                     q.push_back(p);
                 }



                 it = t.begin();
                 t[index].exe_t -= 1;
                 if ( t[index].exe_t == 0) t.erase(it+index);

                 curr += 1;
                 min=2349239;
                 prev = index;
            }
        }

        //wt calculatio
        multimap<string,cal> M;
        multimap<string,cal>::iterator it3;
        cal temp1;


        for( int i=0 ; i<q.size();i++)
        {   int t;
            for( int i=p_sjf.size()-1; i>= 0 ; i--)
            {
                if ( p_sjf[i].name == q[i].name)
                t = q[i].arr_t;
            }

           // waiting_time += q[i].arr_t - q[i].exe_t;


            cout << q[i].arr_t << " " << q[i].name <<  " " << q[i].exe_t << endl;
           //modification

            temp1.ar = q[i].arr_t;
            temp1.ex = q[i].exe_t;
            M.insert(pair<string,cal>(q[i].name,temp1));
        }

        //
        int index2;
        for( int k=0; k<p_sjf.size(); k++)
        {
            for( int l=q.size()-1; l >=0 ;l--)
            {
                if (  p_sjf[k].name == q[l].name )
                {
                    index2 = l;
                    break;
                }
            }
            turn_around += q[index2].exe_t- p_sjf[k].arr_t;

        }


        //calculating avg_wt
       float wt=0;
       for( int i=0; i<p_sjf.size(); i++)
       {
           float prev=0;
           it3 = M.find(p_sjf[i].name);

           float temp = 0;int coun = 0;

           while( it3 != M.end() && (it3->first) == p_sjf[i].name)
           {
               if( coun == 0)
               {
                   temp += (it3->second).ar - p_sjf[i].arr_t;
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


        float avg_wt = wt/p_sjf.size();
        float avg_tt = turn_around/p_sjf.size();

        cout << "AVG WAITING TIME : " << avg_wt << endl;
        cout << "AVG TURN-AROUND TIME : " << avg_tt << endl;

        return 0;
}
