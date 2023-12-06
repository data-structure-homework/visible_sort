#include <iostream>
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
int main(int argc, char* argv[])
{
    srand(time(nullptr));
    int number[30];
    for(int i=0;i<30;i++){
        number[i]=rand()%31+1;
    }
    display(number,30);
    getchar();
    return 0;
}