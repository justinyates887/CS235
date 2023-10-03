#ifndef _LOG
#define _LOG

#include "Functions.h"

#include <fstream>
#include <iostream>
using namespace std;

class Log
{
    public:
    void Open( string filename );
    void Close();

    template <typename T>
    void Out( string name, T value );

    private:
    ofstream m_log;
};

void Log::Open( string filename )
{
    m_log.open( filename );
}

void Log::Close()
{
    m_log.close();
}

template <typename T>
void Log::Out( string name, T value )
{
    m_log << value << std::endl;
}

void Test_Log()
{
    cout << endl << string( 20 , '-' ) << " Test_Log " << string( 20, '-') << endl;
    { // test begin
        int data1 = 3;
        float data2 = 3.14;
        string data3 = "cheese";

        Log log;
        log.Open( "test1.txt" );
        log.Out( "data1", data1 );
        log.Out( "data2", data2 );
        log.Out( "data3", data3 );
        log.Close();

        ifstream input( "test1.txt" );
        string buffer1, buffer2, buffer3;

        string test_name = "Log variable values and check results";
        string result = "[PASS] ";

        getline( input, buffer1 );
        if      ( buffer1.find( "data1" ) == string::npos )           { result = "[FAIL] "; }
        else if ( buffer1.find( ToString( data1 ) ) == string::npos ) { result = "[FAIL] "; }

        getline( input, buffer2 );
        if      ( buffer2.find( "data2" ) == string::npos )           { result = "[FAIL] "; }
        else if ( buffer2.find( ToString( data2 ) ) == string::npos ) { result = "[FAIL] "; }

        getline( input, buffer3 );
        if      ( buffer3.find( "data3" ) == string::npos )           { result = "[FAIL] "; }
        else if ( buffer3.find( data3 ) == string::npos )             { result = "[FAIL] "; }

        cout << result << test_name << endl;
        cout << "Input data:" << endl;
        cout << "* data1          = " << data1 << endl;
        cout << "* data2          = " << data2 << endl;
        cout << "* data3          = " << data3 << endl;
        cout << "File contents:" << endl;
        cout << "* buffer1        = " << buffer1 << endl;
        cout << "* buffer2        = " << buffer2 << endl;
        cout << "* buffer3        = " << buffer3 << endl;
        cout << endl;
    } // test end
}

#endif
