#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

class List
{
protected:
	double* ptr;
	int num;
	int capacity;
public:
	int& Number() {return num;}
	int& Capacity() {return capacity;}
	List(int Capacity) 
	{
		capacity = Capacity;
		ptr = new double[capacity];
		num = 0;
	}
	List() 
	{
		capacity = 10;
		ptr = new double[capacity];
		num = 0;
	}
	List(List& L) 
	{
		capacity = L.Capacity();
		ptr = new double[capacity];
		num = L.Number();
		for(int i=0;i<num;i++)
		{
			ptr[i] = L[i];
		}
	}
	double& operator[](int i) {return ptr[i];}

	virtual void push(double a) = 0;
	virtual double pop() = 0;

	~List()
	{
		if(ptr!=NULL) delete[] ptr;
	}
};

ostream& set_oct(ostream& o_stream){
    o_stream.setf(ios::scientific);
    o_stream.setf(ios::showbase);
    o_stream.setf(ios::oct, ios::basefield);
    return o_stream;
}

ostream& reset_oct(ostream& o_stream){
    o_stream.unsetf(ios::oct);
    o_stream.unsetf(ios::showbase);
    o_stream.unsetf(ios::scientific);
    return o_stream;
}

class Queue: public List
{
public:
	Queue():List(){}
	Queue(int Capacity):List(Capacity) {}

	virtual void push(double a)
	{
		if(num<capacity-1)
		{
			ptr[num] = a;
			num++;
		}
	}

	virtual double pop()
	{
		if(num==0)
			return -1;
		double res = ptr[0];
		for(int i=1;i<num;i++)
		{ptr[i-1] = ptr[i];}
		num--;
		return res;
	}
    friend ostream& operator << (ostream& o_stream, Queue L){
        unsigned N = L.Number();
        //o_stream << my_manip;
        for (size_t i = 0; i < N - 1; ++i)
            o_stream << set_oct << L[i] << ' ';
        return o_stream;
    }
    friend ofstream& operator << (ofstream& stream, Queue L){
        unsigned N = L.Number();
        stream << N << ' ' << endl;
        for (size_t i = 0; i < N; ++i)
            stream << set_oct << L[i] << ' ';
        return stream;
    }
    friend ifstream& operator >> (ifstream& stream, Queue& L){
        unsigned N;
        stream >> N;
        for (size_t i = 0; i < N; ++i){
            double in;
            stream >> in;
            L.push(in);
        }
        return stream;
    }
};
int main(){
    Queue L(6);
    ofstream fout;
    L.push(8); L.push(1.23);L.push(34.8); L.push(2.1);
    fout.open("/home/kirashuffler/Projects/samostoyalki/SR5_.txt");
    fout << L;
    cout << set_oct << 17;
    cout << endl;
    ifstream fin("/home/kirashuffler/Projects/samostoyalki/SR5_.txt");
    fin >> L;
    cout << L;
    return 0;
}
