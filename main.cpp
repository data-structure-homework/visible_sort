#include <iostream>
#include <time.h>
using namespace std;
void display(int number[],int number_count){
    for(int i=30;i>0;i--){
        for(int j=0;j<number_count;j++){
            if(number[j]<i)
                cout<<" ";
            else
                cout<<"O";
        }
        cout<<endl;
    }
}


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

int main(int argc, char* argv[])
{
    srand(time(nullptr));
    int number[70];
    for(int i=0;i<70;i++){
        number[i]=rand()%31+1;
    }
    display(number,70);
    getchar();
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