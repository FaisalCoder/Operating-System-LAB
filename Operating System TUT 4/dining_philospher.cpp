/*
 * dining_philospher.cpp
 *
 *  Created on: Oct 15, 2013
 *      Author: user
 */
#include<iostream>
#include<ctime>
#include<list>
using namespace std;
bool running = false;

void timechecker( float, int);

struct other
{
	int time,p_nos;
};

list<other> l;
int count = 0;

void caller()
{
	int choice;
	float input_time;
	cout << "Enter 1 to read " << endl;
	cout << "Enter 2 to write " << endl;
	cout << "Enter 3 to exit" << endl;
	cin >> choice;
	// read input from

	if (choice == 3)
		return ;

	count++;    //process number
	cout << "Enter time of the process " << count ;
	cin >> input_time;

	if ( choice == 1)
	{
		if(running == true)
		{
			other temp ;
			temp.p_nos = count;
			temp.time = input_time;
			l.push_back(temp);
		}

		else
		{
			cout << "Process " << count << "running " << endl;
			timechecker(input_time,count);
		}
	}

	if ( choice == 2)
	{
			if(running == true)
			{
				other temp ;
				temp.p_nos = count;
				temp.time = input_time;
				l.push_back(temp);
			}

			else
			{
				cout << "Process " << count << "running " << endl;
				timechecker(input_time,count);
			}
	}
}

void caller_with_input(int time, int process_n)
{
		cout << "Process " << process_n << "running " << endl;
		timechecker(time,process_n);
		cout << "Process " << process_n << "ended " << endl;

}

void timechecker( float time , int process_number)
{
	clock_t t1,t2;
	t1 = clock();
	t2 = t1;
	float t3 = time;
	cout << "Initial time of process " << process_number << " " << t1 << endl;
	running = true;

	do
	{
		t1 = t2;
		t1 = clock() - t1;

		if ( float(t1)/CLOCKS_PER_SEC == t3 )
		{
			break;
		}

		else
		{
			caller();
		}

	}while( float(t1)/CLOCKS_PER_SEC < t3 );
    running = false;

    cout << "Final time of the process " << process_number << " " << float(clock())/CLOCKS_PER_SEC <<  endl;

    if ( l.empty() == false)
    {
    	other temp = l.front();
    	l.pop_front();
    	caller_with_input(temp.time,temp.p_nos);
    }

}

int main()
{
	caller();
	return 0;
}

