#include <iostream>
#include "complex_io.cpp"
using namespace std;


class List
{
protected:
	my_complex* ptr;
	int num;
	int capacity;
public:
	int Number() {return num;}
	int Capacity() {return capacity;}
	List(int Capacity) 
	{
		capacity = Capacity;
		ptr = new my_complex[capacity];
		num = 0;
	}
	List() 
	{
		capacity = 10;
		ptr = new my_complex[capacity];
		num = 0;
	}
	List(List& L) 
	{
		capacity = L.Capacity();
		ptr = new my_complex[capacity];
		num = L.Number();
		for(int i=0;i<num;i++)
		{
			ptr[i] = L[i];
		}
	}
	my_complex& operator[](int i) {return ptr[i];}
	~List()
	{
		if(ptr!=NULL) delete[] ptr;
	}
    friend ostream& operator << (ostream& stream, List& L){
       for (size_t i = 0; i < L.Number(); ++i)
          stream << L[i] << endl;
       return stream;
    } 
};

class Queue: public List
{
public:
	Queue():List(){}
	Queue(int Capacity):List(Capacity) {}

	void operator+(my_complex a)
	{
		if(num<capacity-1)
		{
			ptr[num] = a;
			num++;
		}
	}

	void operator-(int count)
	{   
        for(size_t i = 0; i < count; ++i){
		if(num==0)
			return;
		for(int i=1;i<num;i++)
		{ptr[i-1] = ptr[i];}
		num--;
        }
	}
};

int main(){
    Queue Q;
    my_complex a(3, 4);
    my_complex b(4, 5);
    Q + a;
    Q + b;
    cout << Q;
    Q - 1;
    cout << Q;
    return 0;
}
