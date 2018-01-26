#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include "message.h"

// This is just a little project to prove that I can code in C++
// It reads an XML file exported by the default Samsung Messages app

using namespace std;

int main()
{
    message myObject;   // holds a single message
    string line;        // line pulled off XML
    ifstream msgfile;   // file stream object

    // Open XML File
    msgfile.open ("examplemsg.xml");
    if (msgfile.is_open())
    {
        cout << "File opened.\n-----------------------------" << endl;

        // ////////////////////////////////////////////
        // Parse XML file
        // make switch with while() loop
        // send tag to matching function

        int counter = 0;

        while ( getline(msgfile, line) )
        {
            if (counter == 0) {
            if (line.find("<message") != string::npos)    // fix with escape character?
            { myObject.clearMessage(); }
            counter++;
            }

            if (counter == 1) {
            if (line.find("<body>") != string::npos)
            { myObject.setBody(line); }
            counter++;
            }

            if (counter == 2) {
            if (line.find("<date>") != string::npos)
            { myObject.setDate(line); }
            counter++;
            }

            if (counter == 3) {
            if (line.find("<type>") != string::npos)
            { myObject.setIsSenderOP(line); }
            counter++;
            }


            if (counter == 4) {
            if (line.find("</message>") != string::npos)
            { myObject.printMessage(); }
            counter = 0;
            }

            else { }

        } // end file checking loop
        // end Drunk Coding
        // ///////////////////////////////////////////////

        msgfile.close();
    }

    else {cout << "Unable to open file" << endl;}

    return 0;
} // end main
