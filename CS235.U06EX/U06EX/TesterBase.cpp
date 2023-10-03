#include "TesterBase.h"

// C++ Library includes
#include <iostream>
#include <iomanip>
#include <cstdlib>

// Project includes
//#include "../Utilities/StringUtil.h"
//#include "../Utilities/Menu.h"

#include "Functions.h"

namespace cuTest
{

TesterBase::TesterBase()
{
    Open( "test_result.html" );
}

TesterBase::TesterBase( std::string outputPath )
{
    Open( outputPath );
}

TesterBase::~TesterBase()
{
    Close();
}

void TesterBase::Open( std::string outputPath )
{
    m_outputPath = outputPath;
    m_totalTestCount = 0;
    m_totalTestPass = 0;
    m_totalTestFail = 0;

//    std::cout << "* TEST LOG WILL BE WRITTEN OUT TO:" << std::endl;
//    Utility::Menu::PrintPwd();

    m_output.open( outputPath );

    OutputHeader();

    m_closed = false;
}

void TesterBase::Close()
{
    if ( m_closed ) { return; }

    OutputFooter();
    m_output.close();

    m_closed = true;
}

void TesterBase::OutputHeader()
{
    std::string pageTitle = "";//Utility::StringUtil::Replace( m_outputPath, "test_result_", "" );
//    pageTitle = Utility::StringUtil::Replace( pageTitle, ".html", "" );
//    pageTitle = Utility::StringUtil::Replace( pageTitle, "_", " " );
    pageTitle += " test result";

    m_output << "<!DOCTYPE html>" << std::endl;
    m_output << "<html>" << std::endl;
    m_output << "    <head>" << std::endl;
    m_output << "        <title>" << pageTitle << "</title>" << std::endl;

    m_output << "        <style type='text/css'>" << std::endl;
    m_output << "            body { font-family: sans-serif; font-size: 12pt; }" << std::endl;
    m_output << "            .warning { padding: 20px; background: #ffed24; font-size: 12pt; text-align: center; }" << std::endl;
    m_output << "            .result-success { background: #24ff24; font-size: 20px; text-align: center; }" << std::endl;
    m_output << "            .result-failure { background: #ff7095; font-size: 20px; text-align: center; }" << std::endl;

    m_output << "            h2 { font-size: 14pt; font-weight: bold; }" << std::endl;
    m_output << "            h3 { font-size: 12pt; font-weight: bold; }" << std::endl;

    m_output << "            table { background: #ffffff; width: 100%; font-size: 10pt; }" << std::endl;
    m_output << "            table tr.pass { background: #ccffcc; }" << std::endl;
    m_output << "            table tr.fail { background: #ffcccc; }" << std::endl;

    m_output << "            table tr             { font-size: 12pt; border: solid 1px #000066; }" << std::endl;
    m_output << "            table tr td          { padding: 10px; border: solid 1px #000033; }" << std::endl;
    m_output << "            table tr td ul li, "
             << "            table tr td ol li    { margin: 10px 0; }" << std::endl;
    m_output << "            table tr td ol       { list-style-type: upper-latin; }" << std::endl;
    m_output << "            table tr .test-set   { font-size: 10pt; }" << std::endl;
    m_output << "            table tr .test       { font-size: 10pt; }" << std::endl;
    m_output << "            table tr .prereq     {  }" << std::endl;
    m_output << "            table tr .result     { text-align: center; font-size: 10pt; font-weight: bold; }" << std::endl;
    m_output << "            table tr .expected   { font-family: monospace; font-size: 10pt; }" << std::endl;
    m_output << "            table tr .actual     { font-family: monospace; font-size: 10pt; }" << std::endl;
    m_output << "            table tr .comments   { font-size: 10pt; }" << std::endl;
    m_output << "            table .prereqs { font-size: 8pt; }" << std::endl;
    m_output << "            table .prereqs ul li { margin: 0; }" << std::endl;
    m_output << "            table .prereqs ul { margin: 0; }" << std::endl;

    m_output << "            table tr.summary { background: #000000; color: #ffffff; }" << std::endl;

    m_output << "            table tr.descriptions { font-size: 8pt; text-align: center; }" << std::endl;
    m_output << "            table .spacer { height: 20px; }" << std::endl;
    m_output << "        </style>" << std::endl;
    m_output << "    </head>" << std::endl;

    m_output << "    <body>" << std::endl;
    m_output << "    <div class='warning'>Warning: Make sure to check if all tests finish (there will be a message at the end of the file) - <br>" << std::endl;
    m_output << "    It is possible for your program to crash early, but still show that tests have passed because it hasn't gone through everything.</div>" << std::endl;
}

void TesterBase::OutputFooter()
{
    m_output << "    </table>" << std::endl;

    if ( m_subtest_totalPasses == m_subtest_totalTests )
    {
        m_output << "    <div class='result-success'>" << m_totalTestCount << " testsets ran; " << m_totalTestPass << " testsets passed</div>" << std::endl;
    }
    else
    {
        m_output << "    <div class='result-failure '>" << m_totalTestCount << " testsets ran; " << m_totalTestPass << " testsets passed</div>" << std::endl;
    }

    m_output << "    </body>" << std::endl;
    m_output << "</html>" << std::endl;
}

void TesterBase::WriteoutSummary()
{
    m_output << "<tr class='summary'>" << std::endl;
    m_output << "<td colspan='7' class='summary'>" << std::endl;
    m_output << "<strong>SUMMARY FOR " << col_testSet << ":</strong>" << std::endl;
    m_output << m_subtest_totalPasses << " out of " << m_subtest_totalTests << " tests passed" << std::endl;
    m_output << "</td>" << std::endl;
    m_output << "</tr>" << std::endl;
    m_output << "<tr class='spacer'></tr>" << std::endl;
}


void TesterBase::WriteoutRow()
{
    if ( col_result == "passed" )
        m_output << "<tr class='pass'>" << std::endl;
    else
        m_output << "<tr class='fail'>" << std::endl;

    m_output << "<td class='test-set'>      " << col_testSet <<         " <br>";

    if ( col_prerequisites != "" )
    {
        m_output << "<div class='prereqs'>Prerequisite functions: <ul>" << col_prerequisites << "</ul></div>      " << std::endl;
    }
    m_output << "</td>" << std::endl;
    m_output << "<td class='test'>          " << col_testName <<        "       </td>" << std::endl;
    m_output << "<td class='result'>        " << col_result <<          "       </td>" << std::endl;
    m_output << "<td class='expected'> <ol> " << col_expectedOutput <<  " </ol> </td>" << std::endl;
    m_output << "<td class='actual'>   <ol> " << col_actualOutput <<    " </ol> </td>" << std::endl;
    m_output << "<td class='comments'> <ul> " << col_comments <<        " </ul> </td>" << std::endl;
    m_output << "</tr>" << std::endl;
}

void TesterBase::Start()
{
//  MainMenu();
    TestAll();
}

void TesterBase::BeginTable()
{
    m_output << "    <table>" << std::endl;
    m_output << "        <tr>" << std::endl;
    m_output << "            <th class='col_set'> Test set </th>" << std::endl;
    m_output << "            <th class='col_test'> Test </th>" << std::endl;
//    m_output << "            <th class='col_prereq'> Prerequisite <br> functions </th>" << std::endl;
    m_output << "            <th class='col_result'> Pass/fail </th>" << std::endl;
    m_output << "            <th class='col_expected'> Expected <br> output </th>" << std::endl;
    m_output << "            <th class='col_actual'> Actual <br> output </th>" << std::endl;
    m_output << "            <th class='col_comments'> Comments </th>" << std::endl;
    m_output << "        </tr>" << std::endl;
}

void TesterBase::EndTable()
{
    m_output << "    </table>" << std::endl;
}

void TesterBase::TestAll()
{
    m_output << "<div id='test-list'><h2>Test list:</h2>\n" << std::endl;

    bool first = true;
    for ( auto& test : m_tests )
    {
        if ( first ) { first = false; }
        else { m_output << " | "; }
        m_output << "<a href='#" << test.name << "'>" << test.name << "</a>";
    }

    m_output << "</div>\n" << std::endl;

    m_output << "<h2>Results:</h2>" << std::endl;

    int counter = 1;
    std::cout << std::endl;
    for ( auto& test : m_tests )
    {
        if ( test.testAggregate == false )
        {
            m_output << "<a name='" << test.name << "' href='#" << test.name << "'><h3>" << test.name << "</h3></a>" << std::endl;

            BeginTable();
            std::cout << "Running testset " << counter << " out of " << m_totalTestCount << ": \t"
                << test.name << std::endl;
            int result = test.callFunction();
            if ( result == 1 )
            {
                m_totalTestPass++;
            }
            EndTable();
        }
        counter++;
    }

    std::cout << "- RESULTS ------------------------------------------------------------" << std::endl;
    std::cout << "- Total tests:           " << m_totalTestCount << std::endl;
    std::cout << "- Total tests passing:   " << m_totalTestPass << std::endl;
    std::cout << "- Total tests failing:   " << m_totalTestFail << std::endl;
    std::cout << "- " << std::endl;
    std::cout << "- NOTE: CHECK \"" << m_outputPath << "\" in the directory --" << std::endl;
    std::cout << "- ";
//    Utility::Menu::PrintPwd();
    std::cout << "- for full information on test results," << std::endl;
    std::cout << "- including expected output vs. actual output and notes." << std::endl;
    std::cout << "----------------------------------------------------------------------" << std::endl;
}

void TesterBase::AddTest( const TestListItem& test )
{
    m_tests.push_back( test );
    m_totalTestCount++;
}

void TesterBase::StartTestSet( std::string name, const std::vector<std::string>& prereqs )
{
    Set_TestSet( name );
    m_subtest_totalTests = 0;
    m_subtest_totalPasses = 0;
    Set_TestPrerequisites( prereqs );
}

void TesterBase::StartTest( std::string description )
{
    Set_TestName( description );
    m_subtest_totalTests++;
    col_actualOutput = "";
    col_expectedOutput = "";
    col_comments = "";
}

void TesterBase::DisplayTestInfo()
{
    const int DESC_LENGTH = 70;
    std::string shortDescription = col_testName;
    if ( shortDescription.size() > DESC_LENGTH )
    {
        shortDescription = shortDescription.substr( 0, DESC_LENGTH-3 ) + "...";
    }

    std::cout << shortDescription << std::endl;
}

void TesterBase::TestFail()
{
    std::cout << "[FAIL] ";
    DisplayTestInfo();
    Set_Result( false );
}

void TesterBase::TestFail( std::string message )
{
    std::cout << "[FAIL] ";
    DisplayTestInfo();
    Set_Comments( message );
    Set_Result( false );
}

void TesterBase::TestPass()
{
    std::cout << "[PASS] ";
    DisplayTestInfo();
    Set_Result( true );
    m_subtest_totalPasses++;
}

int TesterBase::TestResult()
{
    return ( m_subtest_totalPasses == m_subtest_totalTests );
}

void TesterBase::PrereqTest_Success( std::string functionName )
{
    Set_ActualOutput( functionName, std::string( "Implemented" ) );
    TestPass();
    FinishTest();
}

int TesterBase::PrereqTest_Abort( std::string functionName )
{
    Set_ActualOutput( functionName, std::string( "Not implemented" ) );
    TestFail();
    FinishTest();
    FinishTestSet();
    return TestResult();
}

void TesterBase::FinishTest()
{
    WriteoutRow();
}

void TesterBase::FinishTestSet()
{
    WriteoutSummary();
    std::cout << std::endl;
}

void TesterBase::Set_TestSet( std::string value )
{
    col_testSet = value;
}

void TesterBase::Set_TestName( std::string value )
{
    col_testName = value;
}

void TesterBase::Set_TestPrerequisites( const std::vector<std::string>& prereqs )
{
    col_prerequisites = "";
    for ( unsigned int i = 0; i < prereqs.size(); i++ )
    {
        col_prerequisites += "<li>" + prereqs[i] + "</li>";
    }
}

void TesterBase::Set_Result( bool passed )
{
    col_result = ( passed ) ? "passed" : "FAILED";
}

void TesterBase::Set_ExpectedOutput( std::string variable )
{
    col_expectedOutput += "<li>" + variable + "</li>";
}

void TesterBase::Set_ExpectedOutput( std::string variable, std::string value, bool stringQuotes /* = true */ )
{
    col_expectedOutput += "<li>" + variable + " = ";

    if ( stringQuotes )
    {
        col_expectedOutput += "\"" + value + "\"";
    }
    else
    {
        col_expectedOutput += value;
    }

    col_expectedOutput += "</li>";
}

void TesterBase::Set_ExpectedOutput( std::string variable, int value )
{
    Set_ExpectedOutput( variable, ToString( value ), false );
}

void TesterBase::Set_ExpectedOutput( std::string variable, char value )
{
    std::string blah = "'";
    blah += value;
    blah += "'";
    Set_ExpectedOutput( variable, blah, false );
}

void TesterBase::Set_ExpectedOutput( std::string variable, bool value )
{
    Set_ExpectedOutput( variable, value ? "true" : "false", false );
}

void TesterBase::Set_ActualOutput( std::string variable )
{
    col_actualOutput += "<li>" + variable + "</li>";
}

void TesterBase::Set_ActualOutput( std::string variable, std::string value, bool stringQuotes /* = true */ )
{
    col_actualOutput += "<li>" + variable + " = ";

    if ( stringQuotes )
    {
        col_actualOutput += "\"" + value + "\"";
    }
    else
    {
        col_actualOutput += value;
    }

    col_actualOutput += "</li>";
}

void TesterBase::Set_ActualOutput( std::string variable, int value )
{
    Set_ActualOutput( variable, ToString( value ), false );
}

void TesterBase::Set_ActualOutput( std::string variable, char value )
{
    std::string blah = "'";
    blah += value;
    blah += "'";
    Set_ActualOutput( variable, blah, false );
}

void TesterBase::Set_ActualOutput( std::string variable, bool value )
{
    Set_ActualOutput( variable, value ? "true" : "false", false );
}

bool TesterBase::Set_Outputs( std::string label, std::string expected, std::string actual, bool stringQuotes /* = true */ )
{
    Set_ExpectedOutput( label, expected, stringQuotes );
    Set_ActualOutput( label, actual, stringQuotes );
    return ( expected == actual );
}

bool TesterBase::Set_Outputs( std::string label, int expected, int actual )
{
    Set_ExpectedOutput( label, expected );
    Set_ActualOutput( label, actual );
    return ( expected == actual );
}

bool TesterBase::Set_Outputs( std::string label, char expected, char actual )
{
    std::string ex = "'";
    ex += expected;
    ex += "'";
    std::string ac = "'";
    ac += actual;
    ac += "'";
    return Set_Outputs( label, ex, ac, false );
}

bool TesterBase::Set_Outputs( std::string label, bool expected, bool actual )
{
    Set_ExpectedOutput( label, expected );
    Set_ActualOutput( label, actual );
    return ( expected == actual );
}


void TesterBase::Set_Comments( std::string value )
{
    col_comments += "<li>" + value + "</li>";
}

} // End of namespace
