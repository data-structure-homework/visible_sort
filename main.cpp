#include <iostream>
#include <cstdio>
#include <time.h>       //时间
#include <thread>       //线程暂停
#include <chrono>
#include <windows.h>    //cmd命令库

#define setcolor(a) SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE),a);
using namespace std;
//int arr[100];
int arr30[30];
int arr100[100];
int arr1000[1000];
int arr5000[5000];
int arr10000[10000];
int compare_count;      //比较计数器
int exchange_count;     //交换计数器
int array_size=2;       //数组大小  1.30   2.100   3.1000   4.5000   5.10000
bool display_switch=true;   //设置是否显示可视化
bool display_color_switch=true; //设置是否显示颜色

int get_length(){      //返回当前选择的数组长度
    if(array_size==1){
        return 30;
    }
    else if(array_size==2){
        return 100;
    }
    else if(array_size==3){
        return 1000;
    }
    else if(array_size==4){
        return 5000;
    }
    else if(array_size==5){
        return 10000;
    }
    else
        return 100;
}

int * get_array(){  //返回当前选择的数组指针
    if(array_size==1){
        return arr30;
    }
    else if(array_size==2){
        return arr100;
    }
    else if(array_size==2){
        return arr1000;
    }
    else if(array_size==2){
        return arr5000;
    }
    else if(array_size==2){
        return arr10000;
    }
    else
        return arr100;
}

void gotoxy(short x, short y) {     //光标复位
	COORD pos = {x,y};
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}

void display(int arr[],int number_count){   //显示函数
    gotoxy(0,0);

    if(display_switch){
        if(display_color_switch){
            for(int i=30;i>0;i--){
                printf("\r"); 
                for(int j=0;j<number_count;j++){
                    if(arr[j]<i)
                        printf(" ");
                    else{
                        if(arr[j]<=3){
                            setcolor(0xfd);
                            printf("■");
                        }
                        else if(arr[j]<=6){
                            setcolor(0xf1);
                            printf("■");
                        }
                        else if(arr[j]<=9){
                            setcolor(0xf9);
                            printf("■");
                        }
                        else if(arr[j]<=12){
                            setcolor(0xf3);
                            printf("■");
                        }
                        else if(arr[j]<=15){
                            setcolor(0xfb);
                            printf("■");
                        }
                        else if(arr[j]<=18){
                            setcolor(0xf2);
                            printf("■");
                        }
                        else if(arr[j]<=21){
                            setcolor(0xfa);
                            printf("■");
                        }
                        else if(arr[j]<=24){
                            setcolor(0xf6);
                            printf("■");
                        }
                        else if(arr[j]<=27){
                            setcolor(0xf4);
                            printf("■");
                        }
                        else if(arr[j]<=30){
                            setcolor(0xfc);
                            printf("■");
                        }
                    }
                }
                cout<<endl;
            }
        }
        else{
            for(int i=30;i>0;i--){
                printf("\r"); 
                for(int j=0;j<number_count;j++){
                    if(arr[j]<i)
                        printf(" ");
                    else
                        printf("■");
                }
                cout<<endl;
            }
        }
    }
    setcolor(0xf0);
    cout<<"当前比较总数:"<<compare_count<<endl;
    cout<<"当前交换总数:"<<exchange_count<<endl;
}

void init(){    //初始化程序
    SetConsoleOutputCP(65001);//设置CMD为UTF8

    HANDLE hOut;
    COORD bufferSize;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    bufferSize.X = 100;
    bufferSize.Y = 60;
    SetConsoleScreenBufferSize(hOut, bufferSize);//调整CMD缓冲区大小

    TCHAR title[256];
    HWND hWnd;
    GetConsoleTitle(title, 246);
    hWnd = FindWindow(0, title);
    MoveWindow(hWnd,200,200,1280,720,true);//调整CMD窗口大小

    system("color f0");

    compare_count=0;
    exchange_count=0;
}

void arr_init(int arr[],int count){     //初始化数组
    system("cls");
    cin.clear(); 
    for(int i=0;i<count;i++){
        arr[i]=rand()%31+1;
    }
    compare_count=0;
    exchange_count=0;

    display(get_array(),get_length());
    cout<<"随机数组已经生成完成，请按任意键继续......";
    getchar(); getchar();
    system("cls");
}

void insertion_sort(int arr[],int len)  //插入排序
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
        display(get_array(),len);
        exchange_count++;
        arr[j+1]=key;
        //this_thread::sleep_for(chrono::milliseconds(100)); 
    }
}

void quick_sort(int arr[],int len,int start,int end){       //快速排序
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
            display(get_array(),len);
        }
    }
    exchange_count++;

    arr[start]=arr[left_pointer];
    arr[left_pointer]=base_number;
    display(get_array(),len);

    quick_sort(get_array(),get_length(),start,left_pointer-1);
    quick_sort(get_array(),get_length(),left_pointer+1,end);
}

void bubble_sort(int arr[],int len){
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
        display(get_array(),len);
    }
}

void merge_sort(int start,int end){   //归并排序主函数
    void merge(int arr[],int start,int mid,int end);
    if(start>=end){
        compare_count++;
        return;
    }

    int mid=(start+end)/2;
    merge_sort(start,mid);
    merge_sort(mid+1,end);
    merge(get_array(),start,mid,end);
}

void merge(int arr[],int start,int mid,int end){
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

    display(get_array(),get_length());

    delete []merge_sort_temp;
}

void menu(){
    system("cls");
    cout<<"可视化排序算法v1.3"<<endl;
    cout<<"当前选择数组大小:";
    cout<<get_length()<<endl;
    cout<<"1.插入排序"<<endl;
    cout<<"2.快速排序"<<endl;
    cout<<"3.冒泡排序"<<endl;
    cout<<"4.归并排序"<<endl;
    cout<<endl;
    cout<<"8.切换排序数组大小(只有规模100可用可视化)"<<endl;
    cout<<"9.设置(beta)"<<endl;
    cout<<"0.退出"<<endl;
    cout<<"请输入你的选择:";
}

void array_size_menu(){
    system("cls");
    cout<<"选择数组大小"<<endl;
    cout<<"1.30"<<endl;
    cout<<"2.100"<<endl;
    cout<<"3.1000"<<endl;
    cout<<"4.5000"<<endl;
    cout<<"5.10000"<<endl;
    cout<<"0.退出"<<endl;
    cout<<"请输入你的选择:";
}

void setting_menu(){
    system("cls");
    cout<<"设置(beta)"<<endl;
    cout<<"1.图形化排序颜色开/关(禁用它以优化绘制性能)"<<endl;
    cout<<"0.退出"<<endl;
    cout<<"请输入你的选择:";
}

int main(int argc, char* argv[])
{
    //const int count=100;
    init();
    srand((unsigned)time(NULL));
    int choose=3;
    int size_choose=1;
    int setting_choose=1;
    char confirm='o';
    while(choose!=0){
        menu();
        cin>>choose;
        if(choose==1){
            arr_init(get_array(),get_length());
            insertion_sort(get_array(),get_length());
            cout<<"随机数组已经排序完成，请按任意键继续......";
            getchar(); 
        }
        if(choose==2){
            arr_init(get_array(),get_length());
            quick_sort(get_array(),get_length(),0,get_length()-1);
            cout<<"随机数组已经排序完成，请按任意键继续......";
            getchar();
        }
        if(choose==3){
            arr_init(get_array(),get_length());
            bubble_sort(get_array(),get_length());
            cout<<"随机数组已经排序完成，请按任意键继续......";
            getchar();
        }
        if(choose==4){
            arr_init(get_array(),get_length());
            merge_sort(0,get_length()-1);
            cout<<"随机数组已经排序完成，请按任意键继续......";
            getchar();
        }
        if(choose==8){
            while(size_choose!=0){
                array_size_menu();
                cin>>size_choose;
                if(size_choose>=1 && size_choose<=5){
                    array_size=size_choose;
                    if(array_size!=2)
                        display_switch=false;
                    else
                        display_switch=true;

                    break;
                }
            }
        }
        if(choose==9){
            while(setting_choose!=0){
                setting_menu();
                cin>>setting_choose;
                if(setting_choose==1){
                    while(1){
                        system("cls");
                        cout<<"图形化排序颜色开/关(禁用它以优化绘制性能)"<<endl;
                        cout<<"当前:";
                        if(display_color_switch==true)
                            cout<<"开"<<endl;
                        else
                            cout<<"关"<<endl;
                        
                        cout<<"请选择:Y/N:";
                        cin>>confirm;
                        if(confirm=='Y' || confirm=='y'){
                            display_color_switch=true;
                            break;
                        }
                        if(confirm=='N' || confirm=='n'){
                            display_color_switch=false;
                            break;
                        }
                    }
                }
            }
        }
    }
    return 0;
}