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
    void push_back(const T& value){//value es una referencia a algo de tipo T que no va a ser modificada dentro del pushback, value es una direccion en memoria, de la forma &var
        if(sz >= capacity) { 
            resize();        
        }
        storage[sz] = value;//value no se copia en el stack, se almacena la referencia y no usa notacion de puntero
        sz++;              
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
        cout<<"copy constructor called"<<endl;
    }
    ~vector(){//destructor 
        delete[] storage;
        cout<<"destructor called"<<endl;
    }
    unsigned int size() const{//const indica que no se va a modificar ningun atributo de la clase/objeto, aplica para todos los constructores de esta clase
        return sz;//se llama de la forma v.size()
    }
    void pop_back(){
        if(sz > 0) {
            sz--;
        }
    }
    void push_back(const vector<T> &other){//sobrecarga de push_back para que pueda agregar otro vector del mismo tipo T
        reserve(sz + other.size());//se reserva el espacio necesario para agregar el otro vector
        for(unsigned int i = 0; i < other.size(); i++) {
            push_back(other.storage[i]);//se usa el push_back ya definido para agregar cada elemento del otro vector
        }//se usa other.size() porque size es un metodo const y no modifica el otro vector
    }//se llama de la forma v.push_back(u); juan.mendez1

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
    void print() const {
        for(unsigned int i = 0; i < sz; i++) {
            cout << storage[i] << " ";
        }
        cout << endl;
    }
};

class point{
    private:
    double x;
    double y;

    public:
    point(double x=0, double y=0){
        this->x = x;
        this->y = y;       
    }
};


int main() {

    vector<point> u(15, 1.5);
    vector<point> *v = new vector<point>();//llama un nuevo vetor en el heap
                                           //v esta en el stack y contiene una direccion del heap
    for(int i=0; i<15; i++){
        point p(i*1.0, i*2.0);
        u.push_back(p);
    };
    u.shrink_to_fit();
    delete v;//libera la memoria del heap que ocupa v
   
    vector<int> x;
    for(int i=0; i<15; i++){
        x.push_back(i);
    };
    x.print();
    vector<int> p(x);//llama al constructor de copia
    p.print();
    system("pause");

    return 0;
}