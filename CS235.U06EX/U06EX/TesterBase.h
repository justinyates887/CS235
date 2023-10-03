#ifndef _TESTER_BASE_HPP
#define _TESTER_BASE_HPP

// C++ Library includes
#include <string>
#include <list>
#include <vector>
#include <functional>
#include <fstream>

namespace cuTest
{

struct TestListItem;

//! The base class for unit tests
class TesterBase
{
    public:
    TesterBase();
    TesterBase( std::string outputPath );
    virtual ~TesterBase();

    void Open( std::string outputPath );
    void Close();

    void Start();
    void AddTest( const TestListItem& test );

    protected:
    void OutputHeader();
    void OutputFooter();
    void TestAll();

    std::list<TestListItem> m_tests;
    int m_totalTestCount;
    int m_totalTestPass;
    int m_totalTestFail;

    // Per test...:
    void StartTestSet( std::string name, const std::vector<std::string>& prereqs );
    void FinishTestSet();
    void FinishTest();
    void StartTest( std::string description );
    void TestFail();
    void TestFail( std::string message );
    void TestPass();
    void DisplayTestInfo();
    int TestResult();
    void PrereqTest_Success( std::string functionName );
    int PrereqTest_Abort( std::string functionName );

    int m_subtest_totalTests;
    int m_subtest_totalPasses;
    std::string m_subtest_name;


    // For the HTML write-out...
    void WriteoutRow();
    void WriteoutSummary();
    void BeginTable();
    void EndTable();

    void Set_TestSet( std::string value );
    void Set_TestName( std::string value );
    void Set_TestPrerequisites( const std::vector<std::string>& prereqs );
    void Set_Result( bool passed );
    void Set_ExpectedOutput( std::string variable);
    void Set_ExpectedOutput( std::string variable, std::string value, bool stringQuotes = true );
    void Set_ExpectedOutput( std::string variable, int value );
    void Set_ExpectedOutput( std::string variable, char value );
    void Set_ExpectedOutput( std::string variable, bool value );
    void Set_ActualOutput( std::string variable );
    void Set_ActualOutput( std::string variable, std::string value, bool stringQuotes = true );
    void Set_ActualOutput( std::string variable, int value );
    void Set_ActualOutput( std::string variable, char value );
    void Set_ActualOutput( std::string variable, bool value );
    bool Set_Outputs( std::string label, std::string expected, std::string actual, bool stringQuotes = true );
    bool Set_Outputs( std::string label, int expected, int actual );
    bool Set_Outputs( std::string label, char expected, char actual );
    bool Set_Outputs( std::string label, bool expected, bool actual );
    void Set_Comments( std::string value );

    std::string col_testSet;
    std::string col_testName;
    std::string col_prerequisites;
    std::string col_result;
    std::string col_expectedOutput;
    std::string col_actualOutput;
    std::string col_comments;

    std::ofstream m_output;

    std::ifstream m_header;
    std::ifstream m_footer;

    std::string m_outputPath;

    bool m_closed;
};

//! A structure that contains test data
struct TestListItem
{
        std::string name;
        bool testAggregate;
        std::function<int()> callFunction;

        TestListItem()
        {
        testAggregate = false;
        }

        TestListItem( const std::string name, std::function<int()> callFunction, bool testAggregate = false )
        {
                Setup( name, callFunction, testAggregate );
        }

        void Setup( const std::string& name, std::function<int()> callFunction, bool testAggregate = false )
        {
                this->name = name;
                this->callFunction = callFunction;
                this->testAggregate = testAggregate;
        }
};

} // End of namespace

#endif
