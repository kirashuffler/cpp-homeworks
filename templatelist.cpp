#include <iostream>

#define SIZE 100

using namespace std;
template <class T>
void quickSortR(T* a, unsigned N) {
    long i = 0, j = N-1; 	
    T temp, p;
    p = a[ N >> 1 ];
    do {
        while ( a[i] < p ) i++;
        while ( a[j] > p ) j--;
        if (i <= j) {
            temp = a[i]; a[i] = a[j]; a[j] = temp;
            i++; j--;
        }
    } while ( i <= j );
    if ( j > 0 ) quickSortR(a, j);
    if ( N > i ) quickSortR(a + i, N - i);
}

//шаблон списка
template <class X> class List
{
	protected:
	//массив произвольных элементов, количество элементов, добавленных в него, максимальная вместимость
	X* arr;
	int count;
	int capacity;
public:
	//добавить элемент в список. Что делать, если массив заполнен: count=capacity ?
	virtual void push(X N)
	{
		if(count<capacity)
		{
			arr[count] = N;
			count++;
		}
	}
    void Delete(){
        if (count == 0)
            return;
        count--;
    }
	//вытащить элемент из массива и вернуть его
	//распечатать содержимое
	virtual void print()
	{
		cout<<"\n";
		for(int i=0;i<count;i++)
		{
			cout<<arr[i]<<"\t";
		}
	}
    void quicksort(){
        quickSortR(arr, count);
    }

	List()
	{
		cout<<"\nList constructor 0";
		arr = new X[10];
		capacity = 10;
		count = 0;
	}
	List(int Capacity)
	{
		cout<<"\nList constructor 1";
		arr = new X[Capacity];
		capacity = Capacity;
		count = 0;
	}
	
	List(X* Arr, int Number)
	{
		cout<<"\nList constructor 2";
		arr = new X[Number];
		capacity = Number;
		count = Number;
		for(int i=0;i<Number;i++)
		{
			arr[i] = Arr[i];
		}
	}
	List(List& L)
	{
		cout<<"\nList copy constructor";
		count = L.count;
		capacity = L.capacity;
		arr = new X[count];
		for(int i=0;i<count;i++)
		{
			arr[i] = L[i];
		}
	}
	//деструктор
	~List()
	{
		cout<<"\nList destructor is working";
		if(arr!=NULL)
			delete[] arr;
		arr = NULL;
		count = 0;
	}

	//индексация
	virtual X& operator[] (int i) {return arr[i];}
};

int main(){
    List <string> L(7);
    L.push("zz");
    L.push("xs");
    L.push("cr");
    L.push("yf");
    L.push("it");
    L.push("aa");
    L.quicksort();

    cout << L[0] << ' ' << L[1];
    return 0;
}
