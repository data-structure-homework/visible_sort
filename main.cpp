#include <iostream>
#include <cstdio>
#include <time.h>       //时间
#include <thread>       //线程暂停
#include <chrono>
#include <windows.h>    //cmd命令库
using namespace std;
int arr[100];
int compare_count;      //比较计数器
int exchange_count;     //交换计数器

void display(int number_count){
    for(int i=30;i>0;i--){
        printf("\r"); 
        for(int j=0;j<number_count;j++){
            if(arr[j]<i)
                printf(" ");
            else
                printf("O");
        }
        cout<<endl;
    }
    cout<<"当前比较总数:"<<compare_count<<endl;
    cout<<"当前交换总数:"<<exchange_count<<endl;
}

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

    compare_count=0;
    exchange_count=0;
}

void arr_inin(int count){
    system("cls");
    cin.clear(); 
    for(int i=0;i<count;i++){
        arr[i]=rand()%31+1;
    }
    compare_count=0;
    exchange_count=0;

    display(100);
    cout<<"随机数组已经生成完成，请按任意键继续......";
    getchar(); getchar();
    system("cls");
}

void gotoxy(short x, short y) {     //光标复位
	COORD pos = {x,y};
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}

void insertion_sort(int len)  //插入排序
{
    for(int i=1;i<len;++i)
    {
        int key=arr[i];
        int j=i-1;
        while((j>=0) && (key<arr[j]))
        {
            compare_count++;
            exchange_count++;
            arr[j+1]=arr[j];
            j--;
        }
        gotoxy(0,0);
        display(len);
        exchange_count++;
        arr[j+1]=key;
        //this_thread::sleep_for(chrono::milliseconds(100)); 
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
        while(arr[right_pointer]>=base_number && left_pointer<right_pointer){
            compare_count++;
            right_pointer--;
        }

        while(arr[left_pointer]<=base_number && left_pointer<right_pointer){
            compare_count++;
            left_pointer++;
        }

        if(left_pointer<right_pointer){
            exchange_count++;

            temp=arr[left_pointer];
            arr[left_pointer]=arr[right_pointer];
            arr[right_pointer]=temp;
            gotoxy(0,0);
            display(len);
        }
    }
    exchange_count++;

    arr[start]=arr[left_pointer];
    arr[left_pointer]=base_number;
    gotoxy(0,0);
    display(len);

    quick_sort(100,start,left_pointer-1);
    quick_sort(100,left_pointer+1,end);
}

void bubble_sort(int len){
    int temp=0;
    for(int i=0;i<len;i++){
        for(int j=0;j<len-1;j++){
            compare_count++;
            if(arr[j]>arr[j+1]){
                exchange_count++;
                temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
        gotoxy(0,0);
        display(len);
    }
}

void merge_sort(int start,int end){   //归并排序主函数
    void merge(int start,int mid,int end);
    if(start>=end){
        compare_count++;
        return;
    }

    int mid=(start+end)/2;
    merge_sort(start,mid);
    merge_sort(mid+1,end);
    merge(start,mid,end);
}

void merge(int start,int mid,int end){
    int left=start;
    int right=mid+1;
    int temp=0;
    int *merge_sort_temp=new int[end-start+1];   //归并排序用临时数组

    while(left<=mid && right<=end){
        if(arr[left]<=arr[right]){
            compare_count++;
            merge_sort_temp[temp++]=arr[left++];
        }
        else{
            compare_count++;
            exchange_count++;
            merge_sort_temp[temp++]=arr[right++];
        }
    }

    while(left<=mid){
        merge_sort_temp[temp++]=arr[left++];
    }
    while(right<=end){
        merge_sort_temp[temp++]=arr[right++];
    }

    for(int i=start,n=0;i<=end;i++,n++){
        arr[i]=merge_sort_temp[n];
    }

    gotoxy(0,0);
    display(100);

    delete []merge_sort_temp;
}

void menu(){
    system("cls");
    cout<<"可视化排序算法v1.2"<<endl;
    cout<<"1.插入排序"<<endl;
    cout<<"2.快速排序"<<endl;
    cout<<"3.冒泡排序"<<endl;
    cout<<"4.归并排序"<<endl;
    cout<<"0.退出"<<endl;
    cout<<"请输入你的选择:";
}

int main(int argc, char* argv[])
{
    const int count=100;
    init();
    srand((unsigned)time(NULL));
    int choose=3;
    while(choose!=0){
        menu();
        cin>>choose;
        if(choose==1){
            arr_inin(count);
            insertion_sort(100);
            cout<<"随机数组已经排序完成，请按任意键继续......";
            getchar(); 
        }
        if(choose==2){
            arr_inin(count);
            quick_sort(100,0,99);
            cout<<"随机数组已经排序完成，请按任意键继续......";
            getchar();
        }
        if(choose==3){
            arr_inin(count);
            bubble_sort(100);
            cout<<"随机数组已经排序完成，请按任意键继续......";
            getchar();
        }
        if(choose==4){
            arr_inin(count);
            merge_sort(0,99);
            cout<<"随机数组已经排序完成，请按任意键继续......";
            getchar();
        }
    }
    return 0;
}