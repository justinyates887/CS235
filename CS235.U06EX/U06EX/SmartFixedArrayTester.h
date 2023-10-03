#ifndef _SMART_FIXED_ARRAY_TESTER_HPP
#define _SMART_FIXED_ARRAY_TESTER_HPP

// C++ Library includes
#include <iostream>
#include <string>
#include <stdexcept>

// Project includes
#include "SmartFixedArray.h"
#include "TesterBase.h"
//#include "../../Exceptions/NotImplementedException.h"
//#include "../../Exceptions/StructureFullException.h"
//#include "../../Exceptions/InvalidIndexException.h"
//#include "../../Exceptions/NullptrException.h"

//! TESTER for the SmartFixedArray
class SmartFixedArrayTester : public cuTest::TesterBase
{
public:
    SmartFixedArrayTester()
        : TesterBase( "test_result_smart_fixed_array.html" )
    {
        AddTest(cuTest::TestListItem("Constructor()",       std::bind(&SmartFixedArrayTester::Test_Constructor, this)));
        AddTest(cuTest::TestListItem("PopBack()",           std::bind(&SmartFixedArrayTester::Test_PopBack, this)));
        AddTest(cuTest::TestListItem("GetAt()",             std::bind(&SmartFixedArrayTester::Test_GetAt, this)));
        AddTest(cuTest::TestListItem("IsFull()",            std::bind(&SmartFixedArrayTester::Test_IsFull, this)));
        AddTest(cuTest::TestListItem("IsEmpty()",           std::bind(&SmartFixedArrayTester::Test_IsEmpty, this)));
        AddTest(cuTest::TestListItem("PushBack()",          std::bind(&SmartFixedArrayTester::Test_PushBack, this)));
    }

    virtual ~SmartFixedArrayTester() { }

private:
    int Test_Constructor();
    int Test_PushBack();
    int Test_PopBack();
    int Test_GetAt();
    int Test_IsFull();
    int Test_IsEmpty();
};

int SmartFixedArrayTester::Test_Constructor()
{
    StartTestSet( "Test_Constructor", { } );
    std::ostringstream oss;

    StartTest( "0a. Check if functions are implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( "Prerequisite functions", std::string( "Implemented" ) );

        try                           {   SmartFixedArray<int> arr;             }
        catch( runtime_error& ex )    {   prereqsImplemented = false;    }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( "Prerequisite functions" ); }
        else                        { return PrereqTest_Abort( "Prerequisite functions" ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "1. Check initial member variable values" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        Set_Comments( "When a new SmartFixedArray is created, m_itemCount and should be 0 and ARRAY_SIZE should be 100." );

        SmartFixedArray<int> arr;

        if      ( !Set_Outputs( "ARRAY_SIZE", 100, arr.ARRAY_SIZE ) )   { TestFail(); }
        else if ( !Set_Outputs( "m_itemCount", 0, arr.m_itemCount ) )   { TestFail(); }
        else                                                            { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    FinishTestSet();
    return TestResult();
}

int SmartFixedArrayTester::Test_PushBack()
{
    std::string functionName = "PushBack";
    StartTestSet( "Test_" + functionName, { functionName, "Resize" } );

    StartTest( "0a. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, std::string( "Implemented" ) );

        try                           {   SmartFixedArray<int> arr;     /**/ arr.PushBack( 5 ); /**/   }
        catch( runtime_error& ex )    {   Set_Comments( ex.what() );      prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "1. Add three items, check they're in the correct position" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        std::string values[] = { "a", "b", "c" };
        int expectedItemCount = 3;

        SmartFixedArray<std::string> arr;
        for ( int i = 0; i < 3; i++ )   { arr.PushBack( values[i] ); }

        Set_ExpectedOutput( "m_array", std::string( "not nullptr" ) );
        for ( int i = 0; i < 3; i++ )   { Set_ExpectedOutput( "m_array[" + ToString( i ) + "]", values[i] ); }

        std::ostringstream oss;
        oss << arr.m_array;
        Set_ActualOutput    ( "m_array", oss.str() );

        if      ( arr.m_array == nullptr )                                              { TestFail(); }
        else if ( !Set_Outputs( "m_itemCount", expectedItemCount, arr.m_itemCount ) )   { TestFail(); }
        else if ( !Set_Outputs( "m_array[0]", values[0], arr.m_array[0] ) )             { TestFail(); }
        else if ( !Set_Outputs( "m_array[1]", values[1], arr.m_array[1] ) )             { TestFail(); }
        else if ( !Set_Outputs( "m_array[2]", values[2], arr.m_array[2] ) )             { TestFail(); }
        else                                                                            { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "2. ERROR CHECK: Check if StructureFullException is thrown if array is full" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool exceptionThrown = false;

        try                                     {   SmartFixedArray<int> arr;     arr.m_itemCount = arr.ARRAY_SIZE;      arr.PushBack( 2 );       }
        catch( runtime_error& ex )              {   exceptionThrown = true;      }
        catch( ... ) { }

        Set_Outputs( std::string( "Exception is thrown" ), "true", exceptionThrown );
        if  ( exceptionThrown )     { TestPass(); }
        else                        { TestFail(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    FinishTestSet();
    return TestResult();
}

int SmartFixedArrayTester::Test_PopBack()
{
    std::string functionName = "PopBack";
    StartTestSet( "Test_" + functionName, { functionName } );
    std::ostringstream oss;

    StartTest( "0. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, std::string( "Implemented" ) );

        try                           {   SmartFixedArray<int> arr;   arr.m_itemCount=5;  arr.PopBack();            }
        catch( runtime_error& ex )    {   prereqsImplemented = false;      }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "1. Set up array, remove back" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        SmartFixedArray<std::string> arr;
        arr.m_array[0] = "a";
        arr.m_array[1] = "b";
        arr.m_array[2] = "c";
        arr.m_itemCount = 3;

        arr.PopBack();

        if      ( arr.m_array == nullptr )                                              { TestFail(); }
        else if ( !Set_Outputs( "m_itemCount", 2, arr.m_itemCount ) )                   { TestFail(); }
        else if ( !Set_Outputs( "m_array[0]", std::string( "a" ), arr.m_array[0] ) )         { TestFail(); }
        else if ( !Set_Outputs( "m_array[1]", std::string( "b" ), arr.m_array[1] ) )         { TestFail(); }
        else                                                                            { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "2. ERROR CHECK: Check for exception with empty array" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        Set_Comments( "Array is empty, calling PopBack()." );
        SmartFixedArray<std::string> arr;

        bool exceptionOccurred = false;

        try
        {
            arr.PopBack();
        }
        catch( ... )
        {
            exceptionOccurred = true;
        }

        if      ( !Set_Outputs( "Exception occurred", true, exceptionOccurred ) )        { TestFail(); }
        else                                                                             { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    FinishTestSet();
    return TestResult();
}

int SmartFixedArrayTester::Test_GetAt()
{
    std::string functionName = "GetAt";
    StartTestSet( "Test_" + functionName, { functionName } );
    std::ostringstream oss;

    StartTest( "0. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, std::string( "Implemented" ) );

        try                           {   SmartFixedArray<int> arr; arr.m_itemCount=6; arr.GetAt( 5 );            }
        catch( runtime_error& ex )    {   prereqsImplemented = false;      }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "1. Set up array, get at 1" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        SmartFixedArray<std::string> arr;
        arr.m_array[0] = "a";
        arr.m_array[1] = "b";
        arr.m_array[2] = "c";
        arr.m_itemCount = 3;

        if      ( !Set_Outputs( "GetAt( 1 )", std::string( "b" ), arr.GetAt( 1 ) ) )         { TestFail(); }
        else                                                                            { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "2. ERROR CHECK: Check for exception with invalid index" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        Set_Comments( "ARRAY_SIZE is 100. Calling GetAt( 250 )." );
        SmartFixedArray<std::string> arr;
        arr.m_itemCount = 3;

        bool exceptionOccurred = false;

        try
        {
            arr.GetAt( 250 );
        }
        catch( ... )
        {
            exceptionOccurred = true;
        }

        if      ( !Set_Outputs( "Exception occurred", true, exceptionOccurred ) )        { TestFail(); }
        else                                                                             { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "3. ERROR CHECK: Check for exception when array is empty" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        Set_Comments( "Array is empty. Calling GetAt( 0 )." );
        SmartFixedArray<std::string> arr;

        bool exceptionOccurred = false;

        try
        {
            arr.GetAt( 0 );
        }
        catch( ... )
        {
            exceptionOccurred = true;
        }

        if      ( !Set_Outputs( "Exception occurred", true, exceptionOccurred ) )        { TestFail(); }
        else                                                                             { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    FinishTestSet();
    return TestResult();
}

int SmartFixedArrayTester::Test_IsFull()
{
    std::string functionName = "IsFull";
    StartTestSet( "Test_" + functionName, { functionName } );
    std::ostringstream oss;

    StartTest( "0. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, std::string( "Implemented" ) );

        try                                     {   SmartFixedArray<int> arr;     arr.IsFull();            }
        catch( runtime_error& ex )    {   prereqsImplemented = false;   }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "1. Check if IsFull returns true when full" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        SmartFixedArray<std::string> arr;
        arr.m_itemCount = 100;
        if      ( !Set_Outputs( "IsFull()", true, arr.IsFull() ) )         { TestFail(); }
        else                                                               { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "2. Check if IsFull returns false when not full" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        SmartFixedArray<std::string> arr;
        arr.m_itemCount = 3;
        if      ( !Set_Outputs( "IsFull()", false, arr.IsFull() ) )         { TestFail(); }
        else                                                                { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    FinishTestSet();
    return TestResult();
}

int SmartFixedArrayTester::Test_IsEmpty()
{
    std::string functionName = "IsEmpty";
    StartTestSet( "Test_" + functionName, { functionName } );
    std::ostringstream oss;

    StartTest( "0. Check if function " + functionName + " is implemented" ); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    {
        bool prereqsImplemented = true;
        Set_ExpectedOutput( functionName, std::string( "Implemented" ) );

        try                                     {   SmartFixedArray<int> arr;     arr.IsEmpty();            }
        catch( runtime_error& ex )    {   prereqsImplemented = false;     }
        catch( ... ) { }

        if  ( prereqsImplemented )  { PrereqTest_Success( functionName ); }
        else                        { return PrereqTest_Abort( functionName ); }
    } /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "1. Check if " + functionName + " returns false when an item is in the array" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        SmartFixedArray<std::string> arr;
        arr.m_itemCount = 100;
        if      ( !Set_Outputs( functionName, false, arr.IsEmpty() ) )     { TestFail(); }
        else                                                               { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    StartTest( "2. Check if " + functionName + " returns true when empty" ); { /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
        SmartFixedArray<std::string> arr;
        arr.m_itemCount = 0;
        if      ( !Set_Outputs( functionName, true, arr.IsEmpty() ) )       { TestFail(); }
        else                                                                { TestPass(); }
    } FinishTest(); /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

    FinishTestSet();
    return TestResult();
}

#endif
