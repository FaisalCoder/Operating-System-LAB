#include<iostream>
using namespace std;
#include<vector>

struct process
{
    string name;
    int tick;
};

vector<process> input;
typedef int semaphore;
semaphore mutex = 1, customers = 0 , barbers = 0;
int numberOfFreeWRSeats = 5;
bool halt = false;

void wait ( semaphore s )
{
    s--;
    halt = true;
}

void signal ( semaphore s )
{
    s++;
    halt = false;
}


void barber()
{
    while (input.empty()!= true)
    {
        wait(customers);            // # Try to acquire a customer - if none is available, go to sleep.
        wait(mutex) ;       // # Awake - try to get access to modify # of available seats, otherwise sleep.
        numberOfFreeWRSeats += 1;    //# One waiting room chair becomes free.
        signal(barbers)  ;      // # I am ready to cut.
        signal(mutex) ;     // # Don't need the lock on the chairs anymore.
      //  # (Cut hair here.)
        cout << "Process" << input[0].name << endl;
        input.erase(input.begin());
    }                // # Run in an infinite loop.

}

void customer()
{

  while (input.empty()!= true)
  {
      wait(mutex);           //# Try to get access to the waiting room chairs.
      if (numberOfFreeWRSeats > 0)
      {

          numberOfFreeWRSeats -= 1; //#   sit down in a chair
          signal(customers);         //#   notify the barber, who's waiting until there is a customer
          signal(mutex);     //#   don't need to lock the chairs anymore
          wait(barbers);
          cout << "Process" << input[0].name << endl;
          input.erase(input.begin());

      }
    //  # (Have hair cut here.)

      else                     // # otherwise, there are no free seats; tough luck --
      signal(mutex);     //#   but don't forget to release the lock on the seats!
     // # (Leave without a haircut.)
  }                   //# Run in an infinite loop to simulate multiple customers.

}

int main()
{
    int choice;
    do
    {
        cout << "Press 1 to create new process" << endl;
        cout << "Press 2 to exit" << endl;
        cin >> choice;

        if ( choice == 1)
        {
           process p;
            cout << "Enter name" << endl;
            cin >> p.name;
            cout << "Enter ticks" << endl;
            cin >> p.tick;
            input.push_back(p);
        }




    } while( choice != 2);

    barber();
    cout << "Complete" << endl;

    return 0;
}
