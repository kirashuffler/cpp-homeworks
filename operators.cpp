#include<iostream>
#include<math.h>
#include<fstream>

using namespace std;
const double PI = 3.14;


class my_complex
{
      private:
              double real;
              double image;
              void SetModule();
              void SetArgument();
			  
      public:
               double module;
               double argument;
               void SetReal(double);
               void SetImage(double);
               double Real();
               double Image();
               
               my_complex(double, double);
               ~my_complex();
               
               my_complex Sopr();
               
               void print();
               
               my_complex& operator()() 
               {real = image = argument = module = 0; return *this;}
               my_complex& operator()(double a) 
               {real = image = a; SetModule(); SetArgument(); return *this;}
               my_complex& operator()(double r, double im) 
               {real = r; image = im; SetModule(); SetArgument(); return *this;}
               
               my_complex operator , (my_complex c);
               
               my_complex *operator->() {return this;}
               
               my_complex operator * (my_complex z);
               my_complex operator * (double x);
               friend my_complex operator * (double x, my_complex z);
               
               my_complex operator + ();
               
               my_complex operator =(my_complex);
               int operator ==(my_complex);
               int operator !=(my_complex);
               
               my_complex operator ++ ();
               my_complex operator ++ (int notused);    
               
                friend ostream &operator << (ostream &ustream, my_complex obj)
                {
                     ustream.fill('%');
                     ustream.width(10);
                     ustream.precision(10);
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
                
                /*friend ostream &operator << (ostream &ustream, my_complex obj)
                {
                        
                        ustream << obj.Real()<<endl; 
                		ustream <<obj.Image()<<endl;
                        return ustream;
                }*/
                
                friend ostream &to_file (ostream &ustream, my_complex obj)
                {
                        
                        ustream << obj.Real()<<endl; 
                		ustream << obj.Image()<<endl;
                        return ustream;
                }
                
                friend istream &operator >> (istream &ustream, my_complex &obj)
                {
                       double a;
                       ustream>>a;
                       obj.SetReal(a);
                       ustream>>a;
                       obj.SetImage(a);  
                       return ustream;      
                }
                my_complex operator + (my_complex a){
                    my_complex res(0, 0);
                    res.SetReal(real + a.Real());
                    res.SetImage(image + a.Image());
                    return res;
                }
                my_complex operator + (double a){
                    my_complex res(0,0);
                    res.SetReal(real + a);
                    res.SetImage(image);
                    return res;

                }
                friend my_complex operator + (double a, my_complex b){
                    my_complex res(0,0);
                    res.SetReal(b.Real() + a);
                    res.SetImage(b.Image());
                    return res;
                }
                
};

double my_complex::Real()
{return real;}

double my_complex::Image()
{return image;}

my_complex my_complex::operator =(my_complex c)
{
      real = c.Real();
      image = c.Image();
      SetModule();
      SetArgument();
      
      return *this;           
}

int my_complex::operator ==(my_complex c)
{
      return real==c.Real() && image==c.Image();         
}

int my_complex::operator !=(my_complex c)
{
      return !(real==c.Real()) || !(image==c.Image());         
}

my_complex my_complex::operator ++()
{
      real++;
      image++;
      return *this;           
}

my_complex my_complex::operator ++(int notused)
{
      real++;
      //image++;
      return *this;           
}

my_complex::my_complex(double re = 0.0, double im = 0.0)
{
      real = re;
      image = im;
      module = real*real+image*image;
      module = sqrt(module);
      if(im==0.0 && re>=0.0)
      {
            argument = 0;
            return;     
      }
      if(im==0.0 && re<0.0)
      {
            argument = PI;
            return;           
      }
      argument = (double)atan(re/im);                             
}

my_complex my_complex::operator * (my_complex z)
{
      my_complex C(0, 0);
      C.SetReal(real*z.Real() - image*z.Image());
      C.SetImage(real*z.Image() + image*z.Real());
      return C;           
}

my_complex operator * (double x, my_complex z)
{
       my_complex C(0, 0);
       C.SetReal(x * z.Real());
       C.SetImage(x * z.Image());
       return C;                         
}  

my_complex my_complex::operator * (double x)
{
       my_complex C(0, 0);
       C.SetReal(x * real);
       C.SetImage(x * image);
       return C;           
}

my_complex my_complex::operator + ()
{
       my_complex a(0, 0);    
       a.SetReal(real<0?-real:real);
       a.SetImage(image<0?-image:image);
       a.SetArgument(); a.SetModule();
       return a;
}
my_complex::~my_complex()
{
                         
}

void my_complex::SetImage(double im)
{
     image = im;
     SetModule();
     SetArgument();                            
}

void my_complex::SetReal(double re)
{
     real = re;
     SetModule();
     SetArgument();                           
}

void my_complex::SetModule()
{
     module = sqrt(real*real+image*image);                  
}

void my_complex::SetArgument()
{
      if(real==0.0 && image>0.0)
      {
            argument = PI/2;
            return;     
      }
      if(real==0.0 && image<0.0)
      {
            argument = -PI/2;
            return;           
      }
      if(real==0.0 && image==0.0)
      {
            argument = 0.0;
            return;                           
      }
      argument = (double)atan(image/real);    
}

my_complex my_complex::Sopr()
{
      my_complex C;
      C.SetReal(real);
      C.SetImage(-image);
      return C;           
}

my_complex my_complex::operator , (my_complex c)
{
      my_complex temp(0, 0);
      temp.SetReal(c.Real());
      temp.SetImage(c.Image());
      temp.SetModule(); temp.SetArgument(); 
      return temp;          
}

void my_complex::print()
{
     if(real==0.0)
     {
         if(image!=0.0)
                cout<<"\n"<<image<<"i"; 
         else
                cout<<"\n0.0";                
     }
     else
     {            
         if(image>0.0)
                cout<<"\n"<<real<<" + "<<image<<"i";
         if(image<0.0)
                cout<<"\n"<<real<<" - "<<-image<<"i"; 
         if(image==0.0)
                cout<<"\n"<<real;    
     }
}

int main()
{
 my_complex c(2, 3);  
 my_complex z(1,2);
 my_complex b = 3 + c;
 cout << b;
 return 0;
}
