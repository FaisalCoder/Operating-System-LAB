#include<iostream>
#include<vector>
using namespace std;

struct entry
{
    int pgnos;
    bool modified_bit,reference_bit;
};

int main()
{
     int pageTableSize = 4;

    vector<entry> mainstorage;
    vector<entry> pagetable;

    //initialising page table
    for( int i=0; i<pageTableSize; i++)
    {
        entry temp ;
        temp.pgnos = -1;
        temp.modified_bit = 0;
        temp.reference_bit = 0;

        pagetable.push_back(temp);
    }

    //entering data in main storage
    while(true)
    {
        int pgnos;
        cout << "Enter the page number " << endl ;
        cout << "Press -1 to exit" << endl;
        cin >> pgnos;

        if ( pgnos == -1)break;

        entry temp ;
        temp.pgnos = pgnos;
        temp.modified_bit = 0;
        temp.reference_bit = 0;

        mainstorage.push_back(temp);
    }

    int current = 0;
    //size of input
    while( true )
    {
        bool found = false;
        int pnos;
        cout << "Available pages are : " << endl;

        for( int i=0; i< mainstorage.size();i++)
        cout << "PAGE " << i+1 << endl;

        cout << "Enter the page number to be accessed" << endl;
        cout << "Enter -1 to exit" << endl;
        cin >> pnos;

        if ( pnos == -1)break;

        //implement circular loop here
        for( int i=0; i<pageTableSize;i++)
        {
            if ( pagetable[i].pgnos == pnos )
            {
                char response;
                cout << "Page hit.No page fault!!" << endl;
                cout << "Do you want to modify the page. Y/N ?" << endl;
                cin >> response;

                if ( response == 'Y')
                pagetable[i].modified_bit = 1;

                else
                pagetable[i].modified_bit = 0;

                pagetable[i].reference_bit = 1;
                found = true;
                break;
            }
        }

        if ( found == true) continue;

        //entering if not found
        entry temp;
        temp.pgnos = pnos;
        temp.modified_bit = 0;
        temp.reference_bit = 1;



            if ( pagetable[current].pgnos == -1 )
            {
                //simply erase initially filling
                cout << "No page fault" << endl;
                pagetable[current] = temp;
                current++;
                current = current%pageTableSize;

            }

            //pagetable is filled
            else
            {
                 while(true)
                 {
                    if ( pagetable[current].reference_bit == 0)  //replace this page
                    {
                        cout << "Page fault. Page " << pagetable[current].pgnos << " is replaced" << endl;

                        if ( pagetable[current].modified_bit == 1)
                        cout << "Page " << pagetable[current].pgnos << " is modified in memory" << endl;

                        else
                        cout << "Page " << pagetable[current].pgnos << " is not modified in memory" << endl;

                        pagetable[current] = temp;
                        break;
                    }

                    else
                    pagetable[current].reference_bit = 0;  //given second chance

                    current++;
                    current = current%pageTableSize;

                 }

            }
    }

    return 0;
}
