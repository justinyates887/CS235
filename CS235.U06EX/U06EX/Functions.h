#ifndef _FUNCTIONS
#define _FUNCTIONS

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

template <typename T>
void Display( const vector<string>& header, const vector<vector<T>>& data )
{
    int col_width = 80 / header.size();
    cout << left << fixed << setprecision( 2 );
    for ( auto& head : header )
    {
        cout << setw( col_width ) << head;
    }
    cout << endl << string( 80, '-' ) << endl;
    for ( auto& row : data )
    {
        for ( auto& col : row )
        {
            cout << setw( col_width ) << col;
        }
        cout << endl;
    }
}

void Test_Display();

template <typename T>
string ToString( const T& value )
{
    stringstream ss;
    ss << value;
    return ss.str();
}

// TODO: Create templated Add function
// and created a tester function.
template <typename T>
T Add(const T& valueOne, T&valueTwo){
    return valueOne + valueTwo;
}
void Test_Add();
#endif
