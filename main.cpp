//GPL 3.0 LINCENCE
//排序函数规范:     sort_example(int arr[],int len (可选int start,int end)  )
//请使用最新版本的mingw64-g++编译;      编译命令:g++ -Wall -o output ./main.cpp
//请双击打开程序，否则会出现初始化错误的问题

#include <iostream>
#include <stdio.h>
#include <time.h>       //时间
#include <thread>       //线程暂停
#include <chrono>
#include <windows.h>    //cmd命令库
#include <fstream>      //文件读写
#include <string.h>
#include <ios>
#include <string>
#include <sstream>
#define setcolor(a) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a);    
    //定义控制台调色函数 用法:a=两位十六进制数(0xAB)    A=背景色    B=字体色
#define sleep_mircosecends(a) this_thread::sleep_for(chrono::milliseconds(a));      
    //定义线程暂停函数   用法:sleep_mircosecends(a)     a=毫秒
using namespace std;
int arr30[30];          //以下为不同大小的待排序数组
int arr100[100];
int arr1000[1000];
int arr5000[5000];
int arr10000[10000];
int f_color_arr[9]={0x1,0x0,0x8,0x9,0xA,0xC,0xD,0xE,0xF};
int bg_olor_arr[9]={0x1,0x0,0x80,0x90,0xA0,0xC0,0xD0,0xE0,0xF0};
    //颜色从下标一开始有效，顺序是黑色，灰色，淡蓝色，淡绿色，淡红色，淡紫色，淡黄色，白色
int compare_count;      //比较计数器
int exchange_count;     //交换计数器
int array_size=2;       
    //数组大小  1.30   2.100   3.1000   4.5000   5.10000
int sort_1=0;           
    //多排序比较-排序类型1      排序类型  0=undefined 1=插入排序 2=快速排序 3=冒泡排序 4=归并排序         未实现:5=希尔排序 6=选择排序 7=堆排序
int sort_2=0;           //多排序比较-排序类型2
bool display_switch=true;  //设置是否显示可视化
bool display_color_switch=false; //设置是否显示颜色

int background_color=0xf0;
int font_color=0x0;

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
    else if(array_size==3){
        return arr1000;
    }
    else if(array_size==4){
        return arr5000;
    }
    else if(array_size==5){
        return arr10000;
    }
    else
        return arr100;
}

void get_sort_name(int sort){ 
    if(sort==1){
        cout<<"插入排序";
    }
    else if(sort==2){
        cout<<"快速排序";
    }
    else if(sort==3){
        cout<<"冒泡排序";
    }
    else if(sort==4){
        cout<<"归并排序";
    }
    else if(sort==5){
        cout<<"希尔排序";
    }
    else if(sort==6){
        cout<<"选择排序";
    }
    else if(sort==7){
        cout<<"堆排序";
    }
}

void gotoxy(short x, short y) {     //光标复位
	COORD pos = {x,y};
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}

void display(int arr[],int number_count,int sort){   //可视化显示函数
    gotoxy(0,0);        //光标复位
    setcolor(background_color+font_color);
    if(display_switch){
        if(display_color_switch){
            for(int i=30;i>0;i--){      //颜色显示
                printf("\r"); 
                for(int j=0;j<number_count;j++){
                    if(arr[j]<i)
                        printf(" ");
                    else{
                        if(arr[j]<=3){
                            setcolor(background_color+0xd);
                            printf("■");
                        }
                        else if(arr[j]<=6){
                            setcolor(background_color+0x1);
                            printf("■");
                        }
                        else if(arr[j]<=9){
                            setcolor(background_color+0x9);
                            printf("■");
                        }
                        else if(arr[j]<=12){
                            setcolor(background_color+0x3);
                            printf("■");
                        }
                        else if(arr[j]<=15){
                            setcolor(background_color+0xb);
                            printf("■");
                        }
                        else if(arr[j]<=18){
                            setcolor(background_color+0x2);
                            printf("■");
                        }
                        else if(arr[j]<=21){
                            setcolor(background_color+0xa);
                            printf("■");
                        }
                        else if(arr[j]<=24){
                            setcolor(background_color+0x6);
                            printf("■");
                        }
                        else if(arr[j]<=27){
                            setcolor(background_color+0x4);
                            printf("■");
                        }
                        else if(arr[j]<=30){
                            setcolor(background_color+0xc);
                            printf("■");
                        }
                    }
                }
                cout<<endl;
            }
        }
        else{           //黑白显示
            SetConsoleOutputCP(65001);
            wchar_t buf[100] = {' '};
            HANDLE hOutputHandle;
            hOutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
            DWORD n;
            for(int i=30;i>0;i--){
                printf("\r"); 
                for(int j=0;j<number_count;j++){
                    if(arr[j]>=i)
                        buf[j]=L'@';//■
                    else
                        buf[j]=' ';
                }
                gotoxy(0,30-i);
                WriteConsole(hOutputHandle, buf, sizeof(buf), &n, 0);
            }
            gotoxy(0,31);
        }
    }
    setcolor(background_color+font_color);
    if(sort!=0){
        cout<<"当前排序:";
        get_sort_name(sort);
        cout<<endl;
    }
    cout<<"当前比较总数:"<<compare_count<<endl;
    cout<<"当前交换总数:"<<exchange_count<<endl;
}

string oct_to_hex(int oct){    //十进制转换为 单位数 字符串 十六进制
    if(oct<=9){
        ostringstream ss;
        ss<<oct;
        string r=ss.str();
        return r;
    }
    else if(oct==10)
        return "A";
    else if(oct==11)
        return "B";
    else if(oct==12)
        return "C";
    else if(oct==13)
        return "D";
    else if(oct==14)
        return "E";
    else if(oct==15)
        return "F";
    else
        return "ERROR";
}

void create_setting(){
    ofstream file("setfiles.txt");

    ofstream write_setfiles;
    write_setfiles.open("setfiles.txt", ios::out);
    write_setfiles<<"setting.profile"<<endl;
    write_setfiles<<"display_color_switch=0"<<endl;
    write_setfiles<<"array_size=2"<<endl;
    write_setfiles<<"background_color=F"<<endl;
    write_setfiles<<"font_color=0"<<endl;
}

void write_setting(){       //写入配置文件
    ifstream setfiles;

	setfiles.open("setfiles.txt",ios::in);
	if (!setfiles.is_open())
	{
		cout <<"配置文件打开失败,将创建新默认配置文件"<<endl;
        cout<<"请按任意键继续...";
        getchar();
        create_setting();
	}

    std::ofstream write_setfiles("setfiles.txt",ios::ate);
    write_setfiles<<"setting.profile"<<endl;
    write_setfiles<<"display_color_switch=";
    if(display_color_switch){
        write_setfiles<<"1"<<endl;
    }
    else{
        write_setfiles<<"0"<<endl;
    }

    write_setfiles<<"array_size=";
    write_setfiles<<array_size<<endl;

    write_setfiles<<"background_color=";
    int bg_color_temp=0;
    bg_color_temp=background_color/16;
    write_setfiles<<oct_to_hex(background_color/16)<<endl;

    write_setfiles<<"font_color=";
    write_setfiles<<oct_to_hex(font_color)<<endl;

    getchar();
}

void read_setting(){
    ifstream setfiles;

	setfiles.open("setfiles.txt",ios::in);
	if (!setfiles.is_open())
	{
		cout <<"配置文件打开失败,将创建新默认配置文件"<<endl;
        cout<<"请按任意键继续...";
        getchar();
	}

    string buffer;
	while (getline(setfiles, buffer)) {
        string dis_color="display_color_switch=";
        string arr_size="array_size=";
        string bg_color="background_color=";
        string f_color="font_color=";

        size_t result=buffer.find(dis_color);
        if (result!=std::string::npos) {
            cout<<"颜色开关已设置为 ";
            if(buffer[21]=='0'){
                display_color_switch=false;
                cout<<"关闭!"<<endl;
            }
            else if(buffer[21]=='1'){
                display_color_switch=true;
                cout<<"开启!"<<endl;
            }
        } 

        result=buffer.find(arr_size);
        if (result!=std::string::npos) {
            array_size=int(buffer[11])-48;
            cout<<"数组大小已设置为 ";
            cout<<get_length()<<endl;
        } 

        result=buffer.find(bg_color);
        if (result!=std::string::npos) {
            if(int(buffer[19])>=48 && int(buffer[17])<=57)
                background_color=int(buffer[17])-48;
            else
                background_color=int(buffer[17])-55;

            background_color*=16;
            cout<<"背景颜色="<<background_color<<endl;
        } 

        result=buffer.find(f_color);
        if (result!=std::string::npos) {
            if(int(buffer[19])>=48 && int(buffer[11])<=57)
                font_color=int(buffer[11])-48;
            else
                font_color=int(buffer[11])-55;

            cout<<"字体颜色="<<font_color<<endl;
        } 
	}
    setcolor(background_color+font_color);
    cout<<"读取完成!"<<endl;

    setfiles.close();
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
    MoveWindow(hWnd,20,20,1280,900,true);//调整CMD窗口大小

    setcolor(background_color+font_color);

    compare_count=0;
    exchange_count=0;

    read_setting();
}

void arr_init(int arr[],int count){     //初始化数组
    system("cls");                      //清屏
    cin.clear();                        //清空cin缓冲区
    for(int i=0;i<count;i++){           //待排序数组赋值随机数
        arr[i]=rand()%31+1;
    }
    compare_count=0;
    exchange_count=0;

    display(get_array(),get_length(),0);
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
        display(arr,len,1);

        if(!display_color_switch)
            sleep_mircosecends(50);

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
            display(arr,len,2);
            if(!display_color_switch)
                sleep_mircosecends(30);
        }
    }
    exchange_count++;

    arr[start]=arr[left_pointer];
    arr[left_pointer]=base_number;
    display(arr,len,2);

    if(!display_color_switch)
        sleep_mircosecends(30);

    quick_sort(arr,get_length(),start,left_pointer-1);
    quick_sort(arr,get_length(),left_pointer+1,end);
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
        display(arr,len,3);

        if(!display_color_switch)
            sleep_mircosecends(50);
    }
}

void merge_sort(int arr[],int start,int end){   //归并排序主函数
    void merge(int arr[],int start,int mid,int end);
    if(start>=end){
        compare_count++;
        return;
    }

    int mid=(start+end)/2;
    merge_sort(arr,start,mid);
    merge_sort(arr,mid+1,end);
    merge(arr,start,mid,end);
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

    display(arr,get_length(),4);

    if(!display_color_switch)
        sleep_mircosecends(50);

    delete []merge_sort_temp;
}

void Shell_sort(int arr[],int len){             //希尔排序
    int gap=len;
    while(gap>1)
    {
        gap=gap/2;
        for(int i=0;i<len-gap;++i)
        {
            int end=i;
            int tem=arr[end+gap];
            while(end>=0)
            {
                compare_count++;
                if(tem<arr[end])
                {
                    arr[end+gap]=arr[end];
                    end-=gap;
                    display(arr,len,5);

                    if(!display_color_switch)
                        sleep_mircosecends(10);
                }
                else 
                {
                    break;
                }
            }
            exchange_count++;
            arr[end+gap]=tem;
        }
        display(arr,len,5);

        if(!display_color_switch)
            sleep_mircosecends(10);
    }
}

void Select_sort(int arr[],int len){  //选择排序.
	for(int i = 0;i<len-1;i++){
		int left = i;
		int right = len-1;	
		int imin = i;
		int imax = i;
		for(int j = i+1;j<len;j++){
			if(arr[j]<arr[imin]){
				imin = j;
			}
			if(arr[j]>arr[imax]){
				imax = j;
			}
            compare_count+=2;
		}
		if(imin!=i){
            swap(arr[imin],arr[left]);
            exchange_count++;
            display(arr,len,6);
            
            if(!display_color_switch)
                sleep_mircosecends(50);
        }
		if(imax == left)imax = imin;
		if(imax!=right){
            swap(arr[imax],arr[right]);
            exchange_count++;
            display(arr,len,6);

            if(!display_color_switch)
                sleep_mircosecends(50);
        }
		left++;
		right--;
	}
}

void heat_adjust(int arr[],int index,int len){  //生成大根堆
    int left=index*2+1;
    int right=index*2+2;
    int max_index=index;

    if(arr[left]>arr[max_index] && left<len){
        max_index=left;
    }
    if(arr[right]>arr[max_index] && right<len){
        max_index=right;
    }
    compare_count+=2;

    if(max_index!=index){
        swap(arr[index],arr[max_index]);
        exchange_count++;
        display(arr,len,7);

        if(!display_color_switch)
            sleep_mircosecends(10);

        heat_adjust(arr,max_index,len);
    }
}

void heapsort(int arr[],int len){   //堆排序主函数
    for(int i=len/2-1;i>=0;i--){
        heat_adjust(arr,i,len);
    }

    for(int i=len-1;i>=1;i--){
        display(arr,len,7);

        if(!display_color_switch)
            sleep_mircosecends(10);
        
        swap(arr[i],arr[0]);
        exchange_count++;
        heat_adjust(arr,0,i);
    }
}

void main_menu(){       //主菜单
    system("cls");
    cout<<"________________________________________________"<<endl;
    cout<<"|可视化排序算法v1.6.2                           |"<<endl;
    cout<<"|当前数组大小:";
    cout<<get_length()<<"\t\t\t\t|"<<endl;
    cout<<"|                                               |"<<endl;
    cout<<"|1.单排序可视化演示(将自动切换数组大小至100)    |"<<endl;
    cout<<"|2.双排序效率对比                               |"<<endl;
    cout<<"|                                               |"<<endl;
    cout<<"|4.切换排序数组大小                             |"<<endl;
    cout<<"|5.设置                                         |"<<endl;
    cout<<"|6.从本地读取配置文件                           |"<<endl;
    cout<<"|7.关于本程序                                   |"<<endl;
    cout<<"|                                               |"<<endl;
    cout<<"|0.退出                                         |"<<endl;
    cout<<"-------------------------------------------------"<<endl<<endl;
    cout<<"请输入你的选择:";
}

void visible_menu(){        //可视化选择菜单
    system("cls"); 
    cout<<"________________________"<<endl;
    cout<<"|可视化排序选择菜单     |"<<endl;
    cout<<"|1.插入排序             |"<<endl;
    cout<<"|2.快速排序             |"<<endl;
    cout<<"|3.冒泡排序             |"<<endl;
    cout<<"|4.归并排序             |"<<endl;
    cout<<"|5.希尔排序             |"<<endl;
    cout<<"|6.选择排序             |"<<endl;
    cout<<"|7.堆排序               |"<<endl;
    cout<<"|                       |"<<endl;
    cout<<"|0.退出                 |"<<endl;
    cout<<"-------------------------"<<endl<<endl;
    cout<<"请输入你的选择:";
}

void compare_menu(int current){
    system("cls"); 
    cout<<"________________________"<<endl;
    cout<<"|双排序比较选择菜单     |"<<endl;
    cout<<"|当前选择数组大小:";
    cout<<get_length()<<"\t|"<<endl;
    cout<<"|1.插入排序             |"<<endl;
    cout<<"|2.快速排序             |"<<endl;
    cout<<"|3.冒泡排序             |"<<endl;
    cout<<"|4.归并排序             |"<<endl;
    cout<<"|5.希尔排序             |"<<endl;
    cout<<"|6.选择排序             |"<<endl;
    cout<<"|7.堆排序               |"<<endl;
    cout<<"|                       |"<<endl;
    cout<<"|0.退出                 |"<<endl;
    cout<<"------------------------"<<endl<<endl;
    cout<<"请选择第";
    cout<<current;
    cout<<"个排序:";
}

void array_size_menu(){     //数组大小选择菜单
    system("cls");
    cout<<"_________________"<<endl;
    cout<<"|请选择数组大小 |"<<endl;
    cout<<"|1.30           |"<<endl;
    cout<<"|2.100          |"<<endl;
    cout<<"|3.1000         |"<<endl;
    cout<<"|4.5000         |"<<endl;
    cout<<"|5.10000        |"<<endl;
    cout<<"|               |"<<endl;
    cout<<"|0.退出         |"<<endl;
    cout<<"-----------------"<<endl<<endl;
    cout<<"请输入你的选择:";
}

void setting_menu(){    //设置菜单
    system("cls");
    cout<<"______________________________________________"<<endl;
    cout<<"|设置                                        |"<<endl;
    cout<<"|1.图形化排序颜色开/关(禁用它以优化绘制性能) |"<<endl;
    cout<<"|2.主题设置(beta)                            |"<<endl;
    cout<<"|3.恢复默认设置                              |"<<endl;
    cout<<"|                                            |"<<endl;
    cout<<"|0.退出                                      |"<<endl;
    cout<<"----------------------------------------------"<<endl<<endl;
    cout<<"请输入你的选择:";
}

void about(){
    system("cls"); 
    cout<<"--------关于本程序--------"<<endl;
    cout<<"本程序代码遵循GPL3.0协议"<<endl;
    cout<<"数据结构作业-可视化排序"<<endl;
    cout<<"构建者:kulib-程序架构设计,主要构建者"<<endl;
    cout<<"       xvan1234-插入排序和希尔排序"<<endl;
    cout<<"       Reyes-选择排序"<<endl<<endl;
    cout<<"copyright@HZU计算机学院  2023/12/14"<<endl;
    cout<<"感谢所有支持我的人!"<<endl<<endl;
    cout<<"请按任意键继续...";
    getchar();getchar();
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
        if(setting_choose==2){
            int color_setting=1;
            while(color_setting!=0){
                setcolor(background_color+font_color);
                system("cls");
                cout<<"主题选择"<<endl;
                cout<<"1.黑色主题"<<endl;
                cout<<"2.白色主题"<<endl;
                cout<<"3.自定义"<<endl<<endl;
                cout<<"0.退出"<<endl;
                cout<<"请输入你的选择:";
                
                cin>>color_setting;
                if(color_setting==1){
                    background_color=0x00;
                    font_color=0xf;
                }
                if(color_setting==2){
                    background_color=0xf0;
                    font_color=0x0;
                }
                if(color_setting==3){
                    int current_bg_color=100;
                    int current_f_color=100;
                    while(current_bg_color<0 || current_bg_color>8){
                        system("cls");
                        cout<<"请选择背景颜色"<<endl;
                        cout<<"1.黑色"<<endl;
                        cout<<"2.灰色"<<endl;
                        cout<<"3.淡蓝色"<<endl;
                        cout<<"4.淡绿色"<<endl;
                        cout<<"5.淡红色"<<endl;
                        cout<<"6.淡紫色"<<endl;
                        cout<<"7.淡黄色"<<endl;
                        cout<<"8.白色"<<endl<<endl;
                        cout<<"请输入你的选择:";
                        cin>>current_bg_color;
                    }
                    while(current_f_color<0 || current_f_color>8 || current_f_color==current_bg_color){
                        if(current_f_color==current_bg_color){
                            system("cls");
                            cout<<"字体和背景颜色不能相同!"<<endl;
                            sleep_mircosecends(1000);
                        }
                        system("cls");
                        cout<<"请选择字体颜色"<<endl;
                        cout<<"1.黑色"<<endl;
                        cout<<"2.灰色"<<endl;
                        cout<<"3.淡蓝色"<<endl;
                        cout<<"4.淡绿色"<<endl;
                        cout<<"5.淡红色"<<endl;
                        cout<<"6.淡紫色"<<endl;
                        cout<<"7.淡黄色"<<endl;
                        cout<<"8.白色"<<endl<<endl;
                        cout<<"请输入你的选择:";
                        cin>>current_f_color;
                    }

                    background_color=bg_olor_arr[current_bg_color];

                    font_color=f_color_arr[current_f_color];

                    setcolor(background_color+font_color);
                }
            }
        }
        if(setting_choose==3){
            while(1){
                system("cls");
                cout<<"是否真的要恢复默认设置?"<<endl;
                cout<<"请选择:Y/N:";
                cin>>confirm;
                if(confirm=='Y' || confirm=='y'){
                    create_setting();
                    read_setting();
                    system("cls");
                    cout<<"重置成功!";
                    sleep_mircosecends(1000);
                    break;
                }
                if(confirm=='N' || confirm=='n')
                    break;
            }
        }
        write_setting();
    }
}

void visible_menu_function(){   //可视化菜单选项选择功能
    array_size=2;
    display_switch=true;
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
            merge_sort(get_array(),0,get_length()-1);
            cout<<"随机数组已经排序完成，请按任意键继续......";
            getchar();
        }
        if(choose==5){
            arr_init(get_array(),get_length());
            Shell_sort(get_array(),get_length()-1);
            cout<<"随机数组已经排序完成，请按任意键继续......";
            getchar();
        }
        if(choose==6){
            arr_init(get_array(),get_length());
            Select_sort(get_array(),get_length());
            cout<<"随机数组已经排序完成，请按任意键继续......";
            getchar();
        }
        if(choose==7){
            arr_init(get_array(),get_length());
            heapsort(get_array(),get_length());
            display(get_array(),get_length(),7);
            cout<<"随机数组已经排序完成，请按任意键继续......";
            getchar();
        }
    }
}

void compare_funcion(int sort,int *using_arr){  //调用比较功能函数
        if(sort==1){
            insertion_sort(using_arr,get_length());
            cout<<"随机数组已经排序完成，请按任意键继续......";
            getchar(); 
        }
        else if(sort==2){
            quick_sort(using_arr,get_length(),0,get_length()-1);
            cout<<"随机数组已经排序完成，请按任意键继续......";
            getchar();
        }
        else if(sort==3){
            bubble_sort(using_arr,get_length());
            cout<<"随机数组已经排序完成，请按任意键继续......";
            getchar();
        }
        else if(sort==4){
            merge_sort(using_arr,0,get_length()-1);
            cout<<"随机数组已经排序完成，请按任意键继续......";
            getchar();
        }
        else if(sort==5){
            Shell_sort(using_arr,get_length()-1);
            cout<<"随机数组已经排序完成，请按任意键继续......";
            getchar();
        }
        else if(sort==6){
            Select_sort(using_arr,get_length());
            cout<<"随机数组已经排序完成，请按任意键继续......";
            getchar();
        }
        else if(sort==7){
            heapsort(using_arr,get_length());
            cout<<"随机数组已经排序完成，请按任意键继续......";
            getchar();
        }
}

void compare_menu_function(){
    display_switch=false;
    int choose=1;
    int current_select=1;   //当前选择序号  1=第一个 2=第二个 3=已选完
    int compare_count_temp=0;    //比较计数器缓存
    int exchange_count_temp=0;  //交换计数器缓存
    while(choose!=0){
        compare_menu(current_select);
        cin>>choose;
        if(current_select==1 && choose>=1 && choose<=7){
            sort_1=choose;
            current_select++;
        }
        else if(current_select==2 && choose>=1 && choose<=7){
            sort_2=choose;
            current_select++;
            break;
        }
    }
    if(current_select==3){
        display_switch=false;
        cin.clear();        //清空cin缓冲区
        for(int i=0;i<get_length();i++){       //待排序数组赋值随机数
            get_array()[i]=rand()%31+1;
        }
        compare_count=0;
        exchange_count=0;

        int *used_arr=get_array();

        int len=get_length();
        int *copy_arr=new int[len*2];
        for(int i=0;i<get_length();i++){
            copy_arr[i]=used_arr[i];
        }

        system("cls");
        display(get_array(),get_length(),0);
        cout<<"排序1:";
        get_sort_name(sort_1);
        cout<<endl<<"随机数组已经生成完成，请按任意键继续......";
        getchar();getchar();
        system("cls");

        compare_funcion(sort_1,used_arr);
        compare_count_temp=compare_count;
        exchange_count_temp=exchange_count;

        system("cls");      //清屏
        cin.clear();        //清空cin缓冲区

        compare_count=0;
        exchange_count=0;

        display(get_array(),get_length(),0);
        cout<<"排序2:";
        get_sort_name(sort_2);
        cout<<endl<<"随机数组已经生成完成，请按任意键继续......";
        getchar();
        system("cls");

        compare_funcion(sort_2,copy_arr);
        system("cls");
        cout<<"_________________"<<endl;
        cout<<endl<<"|数组大小:"<<get_length()<<"\t|"<<endl;
        cout<<"-----------------"<<endl;
        cout<<"|排序1:";
        get_sort_name(sort_1);
        cout<<"\t|"<<endl;
        cout<<"|比较总数:"<<compare_count_temp<<"\t|"<<endl;
        cout<<"|交换总数:"<<exchange_count_temp<<"\t|"<<endl;
        cout<<"-----------------"<<endl;
        cout<<"|排序2:";
        get_sort_name(sort_2);
        cout<<"\t|"<<endl;
        cout<<"|比较总数:"<<compare_count<<"\t|"<<endl;
        cout<<"|交换总数:"<<exchange_count<<"\t|"<<endl;
        cout<<"-----------------"<<endl;
        cout<<endl<<"请按任意键继续...";
        getchar();
        display_switch=true;
        delete []copy_arr;
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
        if(choose==4){
            while(size_choose!=0){
                array_size_menu();
                cin>>size_choose;
                if(size_choose>=1 && size_choose<=5){
                    array_size=size_choose;
                    write_setting();
                    break;
                }
            }
        }
        if(choose==5){
            setting_function();
        }
        if(choose==6){
            system("cls");
            read_setting();
            cout<<endl<<"请按任意键继续....";
            getchar();getchar();
        }
        if(choose==7){
           about();
        }
    }
    return 0;
}