#include <iostream>
#include <ctime>
using namespace std;

int fib(int f)
{
    if (f <= 1)                     // if f<=1 ...
        return f;                   // ... return the value of f
    return fib(f - 1) + fib(f - 2); // else add the last number to the second last number
}

int main(){
    int sum = 0;                                                            // added integer tot to calculate the sequence added together
    clock_t t1 = clock();                                                   // get the time at this point
    for (int ct = 0; ct <= 29; ct++) {                                      // for ct 0-29 ...
        cout << "Fibonacci " << ct << " is " << fib(ct) << endl;            // ... prints out fibonacci numbers one at a time
        sum += fib(ct);                                                     // ... add the most recent number to tot
    }
    clock_t t2 = clock();                                                   // take time at this point
    cout << "All of these fibonacci numbers add to " << sum << endl;        // display sum of all fibonacci numbers so far
    cout << "Time taken for recursive fibonacci sequence is " << t2 - t1;   // displays the time taken for the recursive part of the code to run
    
}
