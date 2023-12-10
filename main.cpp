//GPL 3.0 LINCENCE
//排序函数规范:     sort_example(int arr[],int count  (可选int start,int end)  )
//请使用最新版本的mingw64-g++编译;      编译命令:g++ -Wall -o output ./main.cpp
//请双击打开程序，否则会出现初始化错误的问题

#include <iostream>
#include <cstdio>
#include <time.h>       //时间
#include <thread>       //线程暂停
#include <chrono>
#include <windows.h>    //cmd命令库
#define setcolor(a) SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE),a);    //定义控制台调色函数 用法:a=两位十六进制数(0xAB)    A=背景色    B=字体色
#define sleep_mircosecends(a) this_thread::sleep_for(chrono::milliseconds(a));      //定义线程暂停函数   用法:sleep_mircosecends(a)     a=毫秒
using namespace std;
int arr30[30];          //以下为不同大小的待排序数组
int arr100[100];
int arr1000[1000];
int arr5000[5000];
int arr10000[10000];
int compare_count;      //比较计数器
int exchange_count;     //交换计数器
int array_size=2;       //数组大小  1.30   2.100   3.1000   4.5000   5.10000
int sort_1=0;           //多排序比较-排序类型1      排序类型  0=undefined 1=插入排序 2=快速排序 3=冒泡排序 4=归并排序         未实现:5=希尔排序 6=选择排序 7=堆排序
int sort_2=0;           //多排序比较-排序类型2
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

void display(int arr[],int number_count){   //可视化显示函数
    gotoxy(0,0);        //光标复位

    if(display_switch){
        if(display_color_switch){
            for(int i=30;i>0;i--){      //颜色显示
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
        else{           //黑白显示
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

void init(){    //程序初始化
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
    system("cls");      //清屏
    cin.clear();        //清空cin缓冲区
    for(int i=0;i<count;i++){       //待排序数组赋值随机数
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

void bubble_sort(int arr[],int len){        //冒泡排序
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

void merge(int arr[],int start,int mid,int end){        //归并排序  
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

void main_menu(){       //主菜单
    system("cls");
    cout<<"可视化排序算法v1.3.1"<<endl;
    cout<<"当前选择数组大小:";
    cout<<get_length()<<endl;
    cout<<"1.单排序可视化演示"<<endl;
    cout<<"2.双排序效率对比"<<endl;
    cout<<endl;
    cout<<"8.切换排序数组大小(只有规模100可用可视化)"<<endl;
    cout<<"9.设置(beta)"<<endl;
    cout<<"0.退出"<<endl;
    cout<<"请输入你的选择:";
}

void visible_menu(){        //可视化选择菜单
    system("cls"); 
    cout<<"可视化排序选择菜单"<<endl;
    cout<<"当前选择数组大小:";
    cout<<get_length()<<endl;
    cout<<"1.插入排序"<<endl;
    cout<<"2.快速排序"<<endl;
    cout<<"3.冒泡排序"<<endl;
    cout<<"4.归并排序"<<endl;
    cout<<endl;
    cout<<"0.退出"<<endl;
    cout<<"请输入你的选择:";
}

void compare_menu(){
    system("cls"); 
    cout<<"双排序比较选择菜单"<<endl;
    cout<<"当前选择数组大小:";
    cout<<get_length()<<endl;
    cout<<"请选择第";
    cout<<"个排序"<<endl;
    cout<<"1.插入排序"<<endl;
    cout<<"2.快速排序"<<endl;
    cout<<"3.冒泡排序"<<endl;
    cout<<"4.归并排序"<<endl;
    cout<<endl;
    cout<<"0.退出"<<endl;
    cout<<"请输入你的选择:";
}

void array_size_menu(){     //数组大小选择菜单
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

void setting_menu(){    //设置菜单
    system("cls");
    cout<<"设置(beta)"<<endl;
    cout<<"1.图形化排序颜色开/关(禁用它以优化绘制性能)"<<endl;
    cout<<"0.退出"<<endl;
    cout<<"请输入你的选择:";
}

void setting_function(){    //设置选项选择功能
    int setting_choose=1;
    char confirm='o';
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

void visible_menu_function(){   //可视化菜单选项选择功能
    int choose=1;
    while(choose!=0){
        visible_menu();
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
        if(choose==9){
            setting_function();
        }
    }
}

void compare_menu_function(){
    display_switch=false;
    int choose=1;
    int current_select=1;   //当前选择序号  1=第一个 2=第二个 3=已选完
    int compare_count_temp=0;    //比较计数器缓存
    int exchange_count_temp=0;  //交换计数器缓存
    while(choose!=0){
        compare_menu();
        cout<<"current:"<<current_select<<endl;
        cin>>choose;
        if(current_select==1 && choose>=1 && choose<=7){
            if(choose==1){
                sort_1=1;
            }
            if(choose==2){
                sort_1=2;
            }
            if(choose==3){
                sort_1=3;
            }
            if(choose==4){
                sort_1=4;
            }
            current_select++;
        }
        else if(current_select==2 && choose>=1 && choose<=7){
            if(choose==1){
                sort_2=1;
            }
            if(choose==2){
                sort_2=2;
            }
            if(choose==3){
                sort_2=3;
            }
            if(choose==4){
                sort_2=4;
            }
            current_select++;
            break;
        }
    }
    if(current_select==3){
        if(sort_1==1){
            arr_init(get_array(),get_length());
            insertion_sort(get_array(),get_length());
            cout<<"随机数组已经排序完成，请按任意键继续......";
            getchar(); 
        }
        compare_count_temp=compare_count;
        exchange_count_temp=exchange_count;
        if(sort_2==1){
            arr_init(get_array(),get_length());
            insertion_sort(get_array(),get_length());
            cout<<"随机数组已经排序完成，请按任意键继续......";
            getchar(); 
        }
        cout<<"sort-1:com:"<<compare_count_temp<<"ex:"<<exchange_count_temp<<endl;
        cout<<"sort-2:com:"<<compare_count<<"ex:"<<exchange_count<<endl;
        getchar();getchar();
        display_switch=true;
    }
}

int main(int argc, char* argv[])
{
    init();
    srand((unsigned)time(NULL));
    int choose=3;
    int size_choose=1;
    while(choose!=0){
        main_menu();
        cin>>choose;
        if(choose==1){
            visible_menu_function();
        }
        if(choose==2){
            compare_menu_function();
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
    }
    return 0;
}