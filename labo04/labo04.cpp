#include <iostream>
using namespace std;
int main(void)
{
    int n = 0, n1 = 30;
    cout << "ADIVINA EL NUMERO SECRETO!!" << endl;
    do
    {
        cout << "Ingrese un numero entero" << endl;
        cin >> n;
        if (n < n1)
        {
            cout << "Su numero es muy bajo" << endl;
            
        }
        else
        {
           
            cout << "Su numero es muy alto" << endl;
            
        }
    } while (n < n1 || n > n1);
    cout << "ADIVINASTE EL NUMERO!!" << endl;

    return 0;
}