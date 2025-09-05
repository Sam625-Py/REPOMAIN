#include <iostream>
using namespace std;

 // A simple singly-linked list implementation.
 
 //T Type of elements stored in the list.
 
template <typename T>
class List{
private:
   //clase nodo dentro de la clase lista representando cada elemento de la lista

    class Node{
    private:
        T data;     ///< Value stored in the node.
        Node *next; ///< Pointer to the next node.
    public:
        // Default constructor. Initializes data and next pointer.
         
        Node() : data(), next(nullptr) {
            first = nullptr;
            last = nullptr; 
            sz = 0;

        }

         // Constructor with value.
         //v Value to store in the node.
         
        Node(const T &v) : data(v), next(nullptr) {
            first = nullptr;
            last = nullptr; 
            sz = 0;
        }

        // Get the next node pointer.
        // Pointer to the next node.
        Node *getNext() const
        {
            Node *n = first;
            while (n != nullptr && n->data != data)
            {
                n = n->next;
            }
            return n->next;
        }

        
         // Set the next node pointer.
         // n Pointer to the next node.
        
        void setNext(Node *n) {
           next = n;
       }
    };

private:
    Node *first;     ///< Pointer to the first node in the list.
    Node *last;      ///< Pointer to the last node in the list.
    unsigned int sz; ///< Number of elements in the list.

public:
    //Default constructor. Initializes an empty list.
    List() : first(nullptr), last(nullptr), sz(0) {}

    //Destructor. Deletes all nodes in the list.
    ~List()
    {
        Node *temp = first;
        while (first != nullptr)
        {
            temp = first;
            first = first->getNext();
            delete temp;
        }
        last = nullptr;
        sz = 0;
    }

     //Check if the list is empty.
     //true if the list is empty, false otherwise.
    bool empty() const
    {
        return first == nullptr && last == nullptr;
    }

    //Add an element to the end of the list.
    //val Value to add.
    void push_back(const T &val){
        Node *newNode = new Node(val);
        if (!empty())
        {
            last->setNext(newNode);
            last = newNode;
        }
        else
        {
            first = newNode;
            last = newNode;
        }
        sz++;
    }
    void print() const{
        Node *temp = first;
        while (temp != nullptr)
        {
            cout << temp->data << " ";
            temp = temp->getNext();
        }
        cout << endl;
    }

public:
    void pop_back()
    {
        /** your implementation here */
    }
    void push_front(const T &val)
    {
        /** your implementation here */
    }
    void pop_front()
    {
        /** your implementation here */
    }
    T &front()
    {
        /** your implementation here */
    }
    const T &front() const
    {
        /** your implementation here */
    }
    T &back()
    {
        /** your implementation here */
    }
    const T &back() const
    {
        /** your implementation here */
    }
    unsigned int size() const
    {
        /** your implementation here */
    }
    void clear()
    {
        /** your implementation here */
    }
    const T &at(unsigned int index) const
    {
        /** your implementation here */
    }
    T &at(unsigned int index)
    {
        /** your implementation here */
    }
    const T &operator[](unsigned int index) const
    {
        /** your implementation here */
    }
    T &operator[](unsigned int index)
    {
        /** your implementation here */
    }
    void insert(unsigned int index, const T &val)
    {
        /** your implementation here */
    }
    void erase(unsigned int index)
    {
        /** your implementation here */
    }
    void reverse()
    {
        /** your implementation here */
    }
    List(const List &other)
    {
        /** your implementation here */
    }
    void push_back(const List &other)
    {
        /** your implementation here */
    }
    void push_front(const List &other)
    {
        /** your implementation here */
    }
};


int main()
{
    List<int> l;
    l.push_back(10);
    l.push_back(20);
    l.push_back(30);
    return 0;
}