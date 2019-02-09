#include <iostream>
#include <cmath>

using namespace std;

class Complex{
    double modul;
    double arg;
public:
    Complex(double m, double argument){//аргумент в градусах
        modul = m;
        arg = argument * 3.14 / 180;//преобразование в радианы
    }
    Complex(){
        modul = 0;
        arg = 0;
    }
    void setModul(double x){
        modul = x;
    }
    void setArg(double x){
        arg = x;
    }
    void show(){
        cout << '(' << modul * cos(arg) << ',' << modul * sin(arg) << ")\n";
    }
    Complex operator * (Complex z){
        Complex res(0,0);
        res.setModul(modul * z.modul);
        res.setArg(arg + z.arg);
        return res;
    }
    Complex operator / (Complex z){
        Complex res(0,0);
        res.setModul(modul / z.modul);
        res.setArg(arg - z.arg);
        return res;
    }
    void operator = (Complex z){
        modul = z.modul;
        arg = z.arg;
    }
};

int main(){
    Complex a(0,0), b(2, 45), c (4, 30);
    a = b * c;
    a.show();
    return 0;
}
