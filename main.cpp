#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>

using namespace std;

bool executeFIFO(int pages);
bool executeLRU(int pages);
bool executeCLOCK(int pages);

int getLeastRecentlyUsed(pair<int,int>arr[], int n);
int checkInArray(pair<int,int> arr [], int n, int element);
void printLine(pair<int,int> arr [],int length, int element,bool boolean);

/******************************************************************
    M   A   I   N       -       F   U   N   C   T   I   O   N
    ---------------------------------------------------------
    Scanning number of pages in a frame & Algorithm we want to
    use.
******************************************************************/

int main()
{
    int pages;
    cin >> pages;
    string algorithm;
    cin >> algorithm;
    if(algorithm == "FIFO")
        executeFIFO(pages);
    else if(algorithm == "LRU")
        executeLRU(pages);
    else if(algorithm == "CLOCK")
        executeCLOCK(pages);
    return 0;
}

/******************************************************************
        F   I   F   O   -   F   U   N   C   T   I   O   N
    ---------------------------------------------------------
    make an array of pairs (int,int) by default it's the same
    data structure used all over the program, we will use the
    .first attribute only in our array of pairs, so we can change
    it to an array.
******************************************************************/

bool executeFIFO(int pages)
{
    int element = 0, numberOfErrors = 0, iter = 0, ret = 0, escape = 0;
    cin >> element; //Scanning each element.
    pair<int,int> arr[pages];
    std::fill(&arr[0],&arr[0] + pages,std::make_pair(-1,-1));
    printf("Replacement Policy = FIFO\n-------------------------------------\nPage   Content of Frames\n----   -----------------\n");
    while(element != -1)
    {
        ret = checkInArray(arr,pages,element);
        if(ret > -1)
            printLine(arr,pages,element,true);
        else
        {
            arr[iter].first = element; //If not found, save it in our pair.
            if(escape < pages) /* This is used to not marking intialize values as fault'F' */
                printLine(arr,pages,element,true);
            else
            {
                printLine(arr,pages,element,false);
                numberOfErrors++; /*Fault is occured, add to the counter */
            }
            iter++;
            iter %= pages; /* For always keep the indexed value < pair.size() */
            escape++;
        }
        cin >> element;
    }
    printf("-------------------------------------\nNumber of page faults = %d",numberOfErrors);
    return false;
}

/******************************************************************
            L   R   U   -   F   U   N   C   T   I   O   N
    ---------------------------------------------------------
    make an array of pairs (int,int) we will use the .first
    column to store the page number (element) and the .second
    column to store in wich iteration was this (element) last
    visited to keep track of when we visited all our elements
    in the pair.
******************************************************************/

bool executeLRU(int pages)
{
    int element = 0, numberOfErrors = 0,escape = 0, ret, counter = 1;
    cin >> element;
    pair<int,int> arr [pages];
    std::fill(&arr[0], &arr[0] + pages, std::make_pair(-1, 0));
    printf("Replacement Policy = LRU\n-------------------------------------\nPage   Content of Frames\n----   -----------------\n");
    while(element != -1)
    {
        ret = checkInArray(arr,pages,element);
        if(ret > -1)
        {
            arr[ret].second = counter; /*Save the i-th iteration we're in*/
            printLine(arr,pages,element,true); //Printing Line by Line
        }
        else
        {
            /* If element is not in the pair, we have to get LRU and replace it */
            ret = getLeastRecentlyUsed(arr,pages);
            arr[ret].first = element;
            arr[ret].second = counter;
            if(escape < pages)
                printLine(arr,pages,element,true);
            else
            {
                printLine(arr,pages,element,false);
                numberOfErrors++;
            }
            escape++;
        }
        /* Keep iterating */
        counter++;
        cin >> element;
    }
    printf("-------------------------------------\nNumber of page faults = %d",numberOfErrors);
    return true;

}

/******************************************************************
            L   R   U   -   F   U   N   C   T   I   O   N
    ---------------------------------------------------------
    make an array of pairs (int,int) we will use the .first
    column to store the page number (element) and the .second
    column to store in the pointer 0,1 to indicate if we can
    give this page another chance to not be replaced yet.
******************************************************************/

bool executeCLOCK(int pages)
{
    int element = 0, numberOfErrors = 0,escape = 0, ret = 0, iter = 0;
    cin >> element;
    pair<int,int> arr [pages];
    std::fill(&arr[0], &arr[0] + pages, std::make_pair(-1, 0));
    printf("Replacement Policy = CLOCK\n-------------------------------------\nPage   Content of Frames\n----   -----------------\n");
    while(element != -1)
    {
        ret = checkInArray(arr,pages,element);
        if(ret > -1)
        {
            arr[ret].second = 1;
            printLine(arr,pages,element,true);
        }
        else
        {
            while(arr[iter].second != 0)
            {
                /* We have to remove one now, Let's looking which element has its pointer = 0*/
                arr[iter].second = 0;
                iter++;
                iter %= pages;
            }
            /* Replacing */
            arr[iter].first = element;
            arr[iter].second = 1;
            if(escape < pages)
                printLine(arr,pages,element,true);
            else
            {
                printLine(arr,pages,element,false);
                numberOfErrors++;
            }
            iter++;
            iter %= pages;
            escape++;
        }
        cin >> element;
    }
    printf("-------------------------------------\nNumber of page faults = %d",numberOfErrors);
    return false;
}

/*Implemented search in array, and return the index*/
int checkInArray( pair<int,int> arr [], int n, int element)
{
    for(int i = 0; i < n; i++)
        if(arr[i].first == element)
            return i;

    return -1;
}
void printLine(pair<int,int> arr [],int length, int element,bool boolean)
{
    printf("%02d ",element);
    boolean == true ? printf("    ") : printf("F   ");
    for(int i = 0; i < length; i++)
        /* If there's not a value yet print spaces, else padding the page number to a 2-digit number */
        arr[i].first == -1 ? printf("   ") : printf("%02d ",arr[i].first);
    printf("\n");
}

int getLeastRecentlyUsed(pair<int,int> arr[], int n)
{
    int idx = 0;
    for(int i = 0; i < n; i++)
        if(arr[i].second < arr[idx].second && arr[idx].second != -1)
            idx = i;
    return idx;
}
