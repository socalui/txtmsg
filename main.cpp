#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{

    string line;
    ifstream msgfile;
    msgfile.open ("examplemsg.xml");
    if (msgfile.is_open())
    {
        cout << "File opened." << endl;

        while ( getline(msgfile, line) )
        {
            //cout << line << "\n";

            /*
             */




        }

        msgfile.close();
    }
    else cout << "Unable to open file" << endl;









    return 0;
}


/*
 * Open file for reading
 *
 * Function to recognize XML tags, etc
 *
 * Function to recognize url formatting stuff
 *
 * Function to convert url formatting to 'real characters'
 *
 *
 */
