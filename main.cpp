#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>

using namespace std;

bool executeFIFO(int pages);
bool executeLRU(int pages);
bool executeCLOCK(int pages);

bool checkInArray(int arr [], int n, int element);
int checkInArrayLRU(pair<int,int> arr [], int n, int element);

void printLine(int arr [],int length, int element,bool boolean);
void printLineLRU(pair<int,int> arr [],int length, int element,bool boolean);

int getLeastRecentlyUsed(pair<int,int>arr[], int n);



int main()
{
    /**Scanning pages, algorithm used and sequence of page references*/
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
bool executeLRU(int pages)
{
    int element = 0, numberOfErrors = 0,escape = 0, ret, counter = 1;
    cin >> element;
    pair<int,int> arr [pages];
    std::fill(&arr[0], &arr[0] + pages, std::make_pair(0, 0));
    printf("Replacement Policy = LRU\n-------------------------------------\nPage   Content of Frames\n----   -----------------\n");
    while(element != -1)
    {
        ret = checkInArrayLRU(arr,pages,element);
        if(ret > -1)
        {
            arr[ret].second = counter;
            printLineLRU(arr,pages,element,true);
        }
        else
        {
            ret = getLeastRecentlyUsed(arr,pages);
            arr[ret].first = element;
            arr[ret].second = counter;
            if(escape < pages)
                printLineLRU(arr,pages,element,true);
            else
            {
                printLineLRU(arr,pages,element,false);
                numberOfErrors++;
            }
            escape++;
        }
        counter++;
        cin >> element;
    }
    printf("-------------------------------------\nNumber of page faults = %d",numberOfErrors);
    return false;

}
bool executeCLOCK(int pages)
{}
bool executeFIFO(int pages)
{
    int element = 0, numberOfErrors = 0, iter = 0, escape = 0;
    cin >> element;
    int arr[pages] = {0};
    printf("Replacement Policy = FIFO\n-------------------------------------\nPage   Content of Frames\n----   -----------------\n");
    while(element != -1)
    {
        if(checkInArray(arr,pages,element))
            printLine(arr,pages,element,true);
        else
        {
            arr[iter] = element;
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

bool checkInArray(int arr [], int n, int element)
{
    for(int i = 0; i < n; i++)
        if(arr[i] == element)
            return true;

    return false;
}

int checkInArrayLRU( pair<int,int> arr [], int n, int element)
{
    for(int i = 0; i < n; i++)
        if(arr[i].first == element)
            return i;

    return -1;
}

void printLine(int arr [],int length, int element,bool boolean)
{
    printf("%02d ",element);
    boolean == true ? printf("    ") : printf("F   ");
    for(int i = 0; i < length; i++)
        arr[i] == 0 ? printf("   ") : printf("%02d ",arr[i]);
    printf("\n");
}

void printLineLRU(pair<int,int> arr [],int length, int element,bool boolean)
{
    printf("%02d ",element);
    boolean == true ? printf("    ") : printf("F   ");
    for(int i = 0; i < length; i++)
        arr[i].first == 0 ? printf("   ") : printf("%02d ",arr[i].first);
    printf("\n");
}

int getLeastRecentlyUsed(pair<int,int> arr[], int n)
{
    int idx = 0;
    for(int i = 0; i < n; i++)
        if(arr[i].second < arr[idx].second && arr[idx].second != 0)
            idx = i;
    return idx;
}
