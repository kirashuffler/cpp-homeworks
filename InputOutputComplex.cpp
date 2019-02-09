#include <math.h>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

class Complex
{
private:
	double real;
	double image;
public:
	
	Complex() {real = image = 0;}
	Complex(double re) {real = re;}
	Complex(double re, double im) {real = re; image = im;}
	Complex(Complex& C) {real = C.real; image = C.image;}

	double Real() {return real;}
	double Image() {return image;}

	void SetReal(double value) {real = value;}
	void SetImage(double value) {image = value;}

	void store(ofstream& ustream)
	{
		ustream << real <<endl; 
		ustream << image <<endl;
	}

	void retreive(ifstream& ustream)
	{
		ustream >> real; 
		ustream >> image;
	}

	Complex operator+(Complex& C)
	{
		Complex res(*this);
		res.image+=C.image;
		res.real+=C.real;
		return res;
	}

	Complex operator+(double d)
	{
		Complex res(*this);
		res.real+=d;
		return res;
	}

	Complex operator+()
	{
		Complex res(*this);
		res.real = res.real<0? -res.real:res.real;
		res.image = res.image<0? -res.image:res.image;
		return res;
	}

	Complex operator-(Complex& C)
	{
		Complex res(real, image);
		res.image-=C.image;
		res.real-=C.real;
		return res;
	}

	Complex operator-(double d)
	{
		Complex res(real, image);
		res.image-=d;
		return res;
	}

	Complex operator=(Complex& C)
	{
		real = C.real;
		image = C.image;
		return *this;
	}

	Complex operator=(double d)
	{
		real = d;
		image = 0;
		return *this;
	}

	Complex operator*(Complex& C)
	{
		Complex res;
		res.real = real*C.real - image*C.image;
		res.image = real*C.image-image*C.real;
		return res;
	}

	Complex operator*(double d)
	{
		Complex res(*this);
		res.real *= d;
		res.image *= d;
		return res;
	}

	double Argument()
	{
		if(real==0)
			return 0;
		return atan(image/real);
	}

	double Modulus()
	{
		return sqrt(real*real+image*image);
	}

	void print();

	friend ostream &operator << (ostream &ustream, Complex obj);
	friend istream &operator >> (istream &ustream, Complex& obj);

};

ostream &my_manip(ostream &ustream)
{
	ustream.fill('%');
    ustream.width(10);
    ustream.precision(10);

	return ustream;
}

ostream &operator << (ostream &ustream, Complex obj)
{
        //ustream<<my_manip;

        if(obj.Real()==0.0)
        {
            if(obj.Image()!=0.0)
                ustream<<"\n"<<obj.Image()<<"i"; 
            else
                ustream<<"\n0.0";                
        }
        else
        {            
            if(obj.Image()>0.0)
                ustream<<"\n"<<obj.Real()<<" + "<<obj.Image()<<"i";
            if(obj.Image()<0.0)
                ustream<<"\n"<<obj.Real()<<" - "<<-obj.Image()<<"i"; 
            if(obj.Image()==0.0)
                ustream<<"\n"<<obj.Real();    
        }
		
        return ustream;
}
                
istream &operator >> (istream &ustream, Complex &obj)
{
        double a, b;
        ustream>>a;
        obj.SetReal(a);
        ustream>>b;
        obj.SetImage(b);  
        return ustream;      
}

void Complex::print()
{
	//функция печати внутри структуры Complex
		if(image==0)
		{
			std::cout<<real;
			return;
		}
		if(real==0)
		{
			std::cout<<"\n"<<image<<"i";
			return;
		}
		if(image>0)
			std::cout<<"\n"<<real<<" + "<<image<<"i";
		else
			std::cout<<"\n"<<real<<" - "<<-image<<"i";
}

int main()
{
	Complex z(1,2);
	cout<<"\n"<<my_manip<<z;
	cout<<"\n"; cin>>z;
	cout<<"\n"<<z;
	//ofstream fout("test.txt");
	ofstream fout; fout.open("test.txt", ios::out);
	if(fout)
	{
		z.store(fout);
		//fout<<z;
		fout.close();
	}
	ifstream fin("test.txt");
	if(fin)
	{
		z.retreive(fin);
		//fin>>z;
		fin.close();
		cout<<"\n"<<z;
	}
	char c; cin>>c;
	return 0;
}

