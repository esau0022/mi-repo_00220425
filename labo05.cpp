#include <iostream>
using namespace std;
int main()
{
    int n = 0, n2;
    cout << "TABLA DE MULTIPLICAR DEL 1 AL 20 " << endl;
    cout << "Ingrese un numero entero" << endl;
    cin >> n;
    for (int i = 1; i <= 20; i++)
    {
        n2 = n * i;
        cout << n <<"x"<<i<<"="<<n2<<endl; 
    }
    return 0;
}