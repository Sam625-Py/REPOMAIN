#include <iostream>
using namespace std;

int main() {
    char x;
    int *h;
    
for(int i=0; i < (1024 * 1024); i++){
    h = new int[1024*1024];
    cout<<"ciclo "<<i<<endl;
    delete[]h;
}
    system("pause");

    return 0;
}