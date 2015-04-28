#include<iostream>
#include<vector>
using namespace std;

struct entry
{
    int pgnos;
    int count;
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
        temp.count = 0;

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
        temp.count = 0;

        mainstorage.push_back(temp);
    }


    //size of input
    while( true )
    {
        cout << endl;
        bool found = false;
        int pnos;
        cout << "Available pages are : " << endl;

        for( int i=0; i< mainstorage.size();i++)
        cout << "PAGE " << i+1 << endl;

        cout << "Enter the page number to be accessed" << endl;
        cout << "Enter -1 to exit" << endl;
        cin >> pnos;


        if ( pnos == -1)break;

        for( int i=0; i<pageTableSize;i++)
        {
            if ( pagetable[i].pgnos == pnos )
            {
                pagetable[i].count++;

                char response;
                cout << "Page hit.No page fault!!" << endl;
                cout << "This page has been referenced " << pagetable[i].count << " times" << endl;
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
        cout << endl;
        if ( found == true) continue;

        entry temp ;
        temp.pgnos = pnos;
        temp.modified_bit = 0;
        temp.reference_bit = 1;
        temp.count = 1;

        for( int i=0; i< pageTableSize; i++)
        {
            if ( pagetable[i].pgnos == -1)
            {
                //simply erase
                cout << "No page fault" << endl;
                pagetable[i] = temp;
                found = true;
                break;
            }
        }

        if ( found == true) continue;

        //we have to replace

        int min = 901232, place = -1;   //finding the minimum
        for( int i=0; i< pageTableSize; i++)
        {
           if ( min >= pagetable[i].count)
           {
               min = pagetable[i].count;
               place = i;
           }
        }



            cout << "Page fault. Page " << pagetable[place].pgnos << " is replaced" << endl;
            cout << "This page has been referenced " << pagetable[place].count << " times" << endl;

            if ( pagetable[place].modified_bit == 1)
            cout << "Page " << pagetable[place].pgnos << " is modified in memory" << endl;

            else
            cout << "Page " << pagetable[place].pgnos << " is not modified in memory" << endl;

            pagetable[place] = temp;

    }

    cout << endl;

    return 0;
}
