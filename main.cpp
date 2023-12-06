#include <iostream>
#include <cstdio>
#include <time.h>       //时间
#include <thread>       //线程暂停
#include <chrono>
#include <windows.h>    //cmd命令库
using namespace std;
int arr[100];

void init(){
    SetConsoleOutputCP(65001);//设置CMD为UTF8

    HANDLE hOut;
    COORD bufferSize;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    bufferSize.X = 100;
    bufferSize.Y = 60;
    SetConsoleScreenBufferSize(hOut, bufferSize);//调整CMD缓冲区大小

    TCHAR title[256];
    HWND hWnd;
    GetConsoleTitle(title, 256);
    hWnd = FindWindow(0, title);
    MoveWindow(hWnd,20,26,1280,720,true);//调整CMD窗口大小
}

void display(int number_count){
    for(int i=30;i>0;i--){
        for(int j=0;j<number_count;j++){
            if(arr[j]<i)
                printf(" ");
            else
                printf("O");
        }
        cout<<endl;
    }
}


void insertion_sort(int len)  //插入排序
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
        cout<<"\033c";
        display(len);
        arr[j+1]=key;
        this_thread::sleep_for(chrono::milliseconds(100)); // 0.02s
    }
}

void quick_sort(int len,int start,int end){       //快速排序
    int left_pointer,right_pointer;
    int base_number,temp;
    if(start>end)
        return;

    left_pointer=start;
    right_pointer=end;
    base_number=arr[start];
    while(left_pointer!=right_pointer){
        while(arr[right_pointer]>=base_number && left_pointer<right_pointer)
            right_pointer--;

        while(arr[left_pointer]<=base_number && left_pointer<right_pointer)
            left_pointer++;

        if(left_pointer<right_pointer){
            temp=arr[left_pointer];
            arr[left_pointer]=arr[right_pointer];
            arr[right_pointer]=temp;
            cout<<"\033c";
            display(len);
        }
    }
    arr[start]=arr[left_pointer];
    arr[left_pointer]=base_number;
    cout<<"\033c";
    display(len);

    quick_sort(100,start,left_pointer-1);
    quick_sort(100,left_pointer+1,end);
}

int main(int argc, char* argv[])
{
    init();
    srand((unsigned)time(NULL));
    // for(int i=0;i<130;i++){
    //     arr[i]=rand()%31+1;
    // }
    // display(130);
    // getchar();
    // insertion_sort(130);
    // getchar();
    for(int i=0;i<100;i++){
        arr[i]=rand()%31+1;
    }
    //getchar();
    display(100);
    getchar();
    quick_sort(100,0,99);
    getchar();
    //display(arr,30);
    return 0;
}