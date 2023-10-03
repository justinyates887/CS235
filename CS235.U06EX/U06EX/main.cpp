#include "Functions.h"
#include "Log.h"
#include "SmartFixedArrayTester.h"

int main()
{
    cout << string( 60, '\n' );
    cout << endl << "TEMPLATE EXERCISE" << endl << endl;
    string a;

    Test_Add(); // Call this once you've implemented it
    cout << "\n Press ENTER to continue..."; getline( cin, a ); cout << string( 60, '\n' );

    Test_Display();

    cout << "\n Press ENTER to continue..."; getline( cin, a ); cout << string( 60, '\n' );
    Test_Log();

    cout << "\n Press ENTER to continue..."; getline( cin, a ); cout << string( 60, '\n' );
    SmartFixedArrayTester sfaTester;
    sfaTester.Start();

    return 0;
}
