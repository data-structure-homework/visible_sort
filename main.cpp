#include <iostream>
#include <time.h>       //时间
#include <thread>       //线程暂停
#include <chrono>
#include <windows.h>    //cmd命令库
using namespace std;

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
        cout<<"\033c";
        int key=arr[i];
        int j=i-1;
        while((j>=0) && (key<arr[j]))
        {
            arr[j+1]=arr[j];
            j--;
        }
        display(arr,len);
        arr[j+1]=key;
        //this_thread::sleep_for(chrono::milliseconds(50)); // 0.2s
    }
}

int main(int argc, char* argv[])
{
    init();
    srand((unsigned)time(NULL));
    int number[130];
    for(int i=0;i<130;i++){
        number[i]=rand()%31+1;
    }
    display(number,130);
    getchar();
    insertion_sort(number,130);
    getchar();
    //display(arr,30);
    return 0;
}