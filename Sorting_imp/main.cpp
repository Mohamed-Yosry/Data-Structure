#include <iostream>

using namespace std;

void selectionsort(int arr[],int n)
{
    int minidex;
    for(int i=0;i<n-1;i++)
    {
        minidex=i;
        for(int j=i+1;j<n;j++)
        {
            if(arr[minidex]>arr[j])
                minidex=j;
        }
        swap(arr[minidex],arr[i]);
    }
}

/////////////////////////////////////////////
//////////////bubble sort///////////////////
void bubblesort(int arr[],int n)
{
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(arr[i]>arr[i+1])
                swap(arr[i],arr[i+1]);
        }
    }
}
////////////////////////////////////////////////
//////////////insertion sort///////////////////
void insertionsort(int arr[],int n)
{
    for(int i=1;i<n;i++)
    {
        int key=arr[i];
        int j=i-1;
        while(j>-1 && arr[j]>key)
        {
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=key;
    }
}


int main()
{
    int arr[6]={60,40,50,10,30,20};

    selectionsort(arr,6);
    cout<<"Selection sort: ";
    for(int i=0;i<6;i++)
        cout<<arr[i]<<" ";
    cout<<endl;

    cout<<"Bubble sort: ";
    bubblesort(arr,6);
    for(int i=0;i<6;i++)
        cout<<arr[i]<<" ";
    cout<<endl;

    cout<<"Insertion sort: ";
    insertionsort(arr,6);
    for(int i=0;i<6;i++)
        cout<<arr[i]<<" ";
    cout<<endl;



    return 0;
}
