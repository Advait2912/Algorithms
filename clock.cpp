#include<iostream>
#include<chrono>
#include<thread>
using namespace std;
void heavy(){
    this_thread::sleep_for(chrono::milliseconds(200));
}
int main(){
    auto start=chrono::steady_clock::now();
    heavy();
    auto end=chrono::steady_clock::now();
    auto duration_ms=chrono::duration_cast<chrono::milliseconds>(end-start);
    chrono::duration<double> duration_sec=end-start;
    cout<<duration_ms.count()<<endl;
    cout<<duration_sec.count()<<endl;
    return 0;
}
