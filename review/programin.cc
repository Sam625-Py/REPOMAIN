#include <iostream>
using namespace std;
template<typename T>
class vector{
    private:
    T *storage;//almacena los elementos del vector
    unsigned int sz;//numero actual de elementos en el vector
    unsigned int capacity;//capacidad de storage, es decir, el numero maximo de elementos que puede almacenar
    float policy;//le permite al usuario elegir como va a crecer el vector de la forma vector v(n, policy);

    public:     
    vector(){
        storage = new T[5];
        sz=0;
        capacity=5;
        policy=1.7;
    }
    vector(unsigned int c, float p=1.7){
        storage = new T[c];
        sz = 0;
        capacity = c;
        policy = p;
    }
    vector(const vector<T> &other){//constructor de copia, recibe una referencia a otro vector del mismo tipo T que no va a ser modificado
        sz = other.size();//si size() no fuera const no se podria usar
        capacity = other.capacity;
        policy = other.policy;
        storage = new T[capacity];
        for(unsigned int i = 0; i < sz; i++) {
            storage[i] = other.storage[i];
        }
      
    }
    ~vector(){//destructor 
        delete[] storage;
    }

    void push_back(const T& value){//value es una referencia a algo de tipo T que no va a ser modificada dentro del pushback, value es una direccion en memoria, de la forma &var
        if(sz >= capacity) { 
            resize();        
        }
        storage[sz] = value;//value no se copia en el stack, se almacena la referencia y no usa notacion de puntero
        sz++;              
    }
    void push_back(const vector<T> &other){//sobrecarga de push_back para que pueda agregar otro vector del mismo tipo T
        reserve(sz + other.size());//se reserva el espacio necesario para agregar el otro vector
        for(unsigned int i = 0; i < other.size(); i++) {
            push_back(other.storage[i]);//se usa el push_back ya definido para agregar cada elemento del otro vector
        }//se usa other.size() porque size es un metodo const y no modifica el otro vector
    }//se llama de la forma v.push_back(u);

    unsigned int size() const{//const indica que no se va a modificar ningun atributo de la clase/objeto, aplica para todos los constructores de esta clase
        return sz;//se llama de la forma v.size()
    }
    void pop_back(){
        if(sz > 0) {
            sz--;
        }
    }
    
    private:
    void resize(){//se creo porque mi vector se quedo sin espacio y nesecito almacenar mas elementos
        capacity *= policy;
        T *new_storage = new T[capacity];
        for(unsigned int i = 0; i < sz; i++) {
            new_storage[i] = storage[i];
        }
        delete[] storage;//storage almacena una direccion que tiene el arreglo creado el deleto no borra la direccion sino lo que almaacena esta direccion
        storage = new_storage;//se creo el nuevo arreglo ampliado y su direccion que esta en new storage se almacena en storage
    }
    void reserve(unsigned int new_capacity){
        if(new_capacity > capacity) {
            T *new_storage = new T[new_capacity];
            for(unsigned int i = 0; i < sz; i++) {
                new_storage[i] = storage[i];
            }
            delete[] storage;
            storage = new_storage;
            capacity = new_capacity;
        }
    }
    public:
    void shrink_to_fit(){
        if(sz < capacity) {
            capacity = sz;
            T *new_storage = new T[capacity];
            for(unsigned int i = 0; i < sz; i++) {
                new_storage[i] = storage[i];
            }
            delete[] storage;
            storage = new_storage;
        }
    }
   void printvector(const vector<T> &v) {//metodo para imprimir los elementos del vector, recibe una referencia a un vector del mismo tipo T que no va a ser modificado
        for(unsigned int i = 0; i < v.size(); i++) {
            cout << v.storage[i] << " ";
        }
        cout << endl;//se llama de la forma v.printvector();
    }
    T& operator[](unsigned int index) {//sobrecarga del operador [] para acceder a los elementos del vector
        if(index >= sz) {
            throw out_of_range("Index out of range");
        }
        return storage[index];//se llama de la forma v[i]
    }
    const T& operator[](unsigned int index) const {//sobrecarga del operador [] para acceder a los elementos del vector en un objeto const
        if(index >= sz) {
            throw out_of_range("Index out of range");
        }
        return storage[index];
    }
    T& at(unsigned int index) {//metodo at para acceder a los elementos del vector con verificacion de rango
        if(index >= sz) {
            throw out_of_range("Index out of range");
        }
        return storage[index];//se llama de la forma v.at(i)
    }
    const T& at(unsigned int index) const {//metodo at para acceder a los elementos del vector en un objeto const con verificacion de rango
        if(index >= sz) {
            throw out_of_range("Index out of range");
        }
        return storage[index];
    }
};

int suma_vector(const vector<int> &v){//funcion que recibe una referencia a un vector de enteros y devuelve la suma de sus elementos
    int suma=0;
    for(unsigned int i=0; i<v.size(); i++){
        suma+=v[i];
    }
    return suma;
}
void reverse_vector(vector<int> &v) {
    unsigned int left = 0;
    unsigned int right = v.size() - 1;
    while(left < right) {
        swap(v[left], v[right]);
        left++;
        right--;
    }
}

int main() {

    /*ejercicios de vectores*/
    //SUMA DE ELEMENTOS INTERNOS ENTEROS
    vector<int> y;
    for(int i=0; i<10; i++){
        y.push_back(i*2);
    };
    cout << "Elementos del vector y: ";
    y.printvector(y);
   int suma = suma_vector(y);
   cout << "La suma de los elementos del vector y es: " << suma << endl;


   //REVERSE_VECTOR
   reverse_vector(y);
   cout << "Elementos del vector despues de invertirlo: ";
   y.printvector(y);

    system("pause");

    return 0;
}