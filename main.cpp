#include <iostream>
using namespace std;

void insertion_sort(int arr[],int len)
{
    for(int i=1;i<len;++i)
    {
        int key=arr[i];
        int j=i-1;
        while((j>=0) && (key<arr[j]))
        {
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=key;
    }
}

void display(int arr[],int len)
{
    for(int i=0;i<len;++i)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

int main(int argc, char* argv[])
{
    int arr[30];
    srand((unsigned)time(NULL));
    for(int i=0;i<30;++i)
    {
        arr[i]=rand()%31+1;
    }
    
    insertion_sort(arr,30);

    display(arr,30);
    return 0;
}