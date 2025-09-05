#include<iostream>
using namespace std;
void fibonacci(int n){
    int a = 0, b = 1, c;
    for(int i = 0; i < n; i++){
        cout << a << " ";
        c = a + b;
        a = b;
        b = c;
    }
    cout << endl;
    
}
int main(
){
    int x = 0;
    cout << "Ingrese un numero: ";
    cin >> x;
   fibonacci(x);
    



   system("pause");
    return 0;
}









