#include "Functions.h"

void Test_Display()
{
    cout << endl << string( 20 , '-' ) << " Test_Display (Manual tests) " << string( 20, '-') << endl;
    { // test begin
        cout << "Test 1 - Classes" << endl;
        vector<string> header = { "Class 1", "Class 2", "Class 3", "Class 4" };
        vector<vector<string>> data = {
            { "CS 134", "CS 200", "CS 235", "CS 250" },
            { "ASL 120", "ASL 122", "ASL 135", "ASL 145" }
        };

        Display( header, data );
    } // test end

    cout << endl << endl;

    { // test begin
        cout << "Test 2 - Minimum wage vs. Median monthly rent" << endl;
        vector<string> header = { "2010", "2000", "1990", "1980", "1970", "1960", "1950" };
        vector<vector<float>> data = {
            { 7.25, 5.15, 3.80, 3.10, 1.60, 1.00, 0.75 },
            { 841,  602,  447,  243,  108,  71,   42  },
        };

        Display( header, data );
    } // test end
}

void Test_Add() {
    //Arrange
    float input_a = 2.5;
    float input_b = 3.3;
    float expected_result_a = 5.8;

    int input_c = 2;
    int input_d = 5;
    int expected_result_b = 7;

    string test_name = "Test Add with Float and Int";
    string result = "";

    //Act
    float actual_result_a = Add(input_a, input_b);
    float actual_result_b = Add(input_c, input_d);

    //Assert
    if (actual_result_a != expected_result_a) { result = "[FAIL] "; }
    else if (actual_result_b != expected_result_b) { result = "[FAIL] "; }
    else { result = "[PASS] "; }

    //Display
    std::cout << "Test" << "\tInput(s)" << "\tExpected Output" << "\tActual Output" << std::endl;
    std::cout << "1" << "\t" << input_a << ", " << input_b << "\t" << expected_result_a << "\t" << actual_result_a << std::endl;
    std::cout << "2" << "\t" << input_c << ", " << input_d << "\t" << expected_result_b << "\t" << actual_result_b << std::endl;
    std::cout << std::endl;
}

