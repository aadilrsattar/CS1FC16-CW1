#include <iostream>    
#include <ctime>
using namespace std;

int fibi(int ct) {                  // source : https://www.tutorialspoint.com/cplusplus-program-to-find-fibonacci-numbers-using-iteration
    int a = 0, b = 1, c = 0;        //sets out the each of the numbers needed for the calculation
    for (int i = 0; i < ct; i++) {  // for i until it reaches ct ...
        c = a + b;                  // ... add a and b to get c
        a = b;                      // ... make a = b, this prevents us overwriting anything we need
        b = c;                      // ... finally b = c, to be used later
    }                           
    return a;                       // a is passed on to the user to be shown as the next fibonacci number 
}

int main() {
    int sum = 0;                                                            // added integer tot to calculate the sequence added together
    clock_t t1 = clock();                                                   // get the time at this point
    for (int ct = 0; ct <= 29; ct++) {                                      // for ct 0-29 ...
        cout << "Fibonacci " << ct << " is " << fibi(ct) << endl;            // ... prints out fibonacci numbers one at a time
        sum += fibi(ct);                                                     // ... add the most recent number to tot
    }
    clock_t t2 = clock();                                                   // take time at this point
    cout << "All of these fibonacci numbers add to " << sum << endl;        // display sum of all fibonacci numbers so far
    cout << "Time taken for recursive fibonacci sequence is " << t2 - t1;   // displays the time taken for the recursive part of the code to run
}



