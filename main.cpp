#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

string urlDecode(string &SRC);
bool stripXML(string tag, string* line);

int main()
{
    string line;
    ifstream msgfile;
    msgfile.open ("examplemsg.xml");
    if (msgfile.is_open())
    {
        cout << "File opened.\n-----------------------------" << endl;

        // loop while file exists
        while ( getline(msgfile, line) )
        {
            //===============================================================
            // find XML tags <body>
            size_t bBegin = line.find("<body>");
            //if (bBegin!=string::npos) { cout << "bBegin: " << bBegin << '\n'; }
            size_t bEnd = line.find("</body>");
            //if (bEnd!=string::npos) { cout << "end: " << bEnd << '\n'; }

            // body exists.  format & output
            if (bEnd!=string::npos)
            {
                // erase XML tags <body>
                line.erase(bEnd);
                line.erase(0, bBegin + 6);

                // ------- BODY specific -------
                // find and replace + with " "
                for (size_t i = 0; i < line.length(); i++)
                {
                    if(!line.compare(i, 1, "+"))
                    {
                        line.replace(i, 1, " ");
                    }
                }

                // remove % encoding
                line.assign(urlDecode(line));

                // output body
                cout << line << endl;
            }

            //===============================================================
            // find XML tags <date>
            size_t beginDate = line.find("<date>");
            size_t endDate = line.find("</date>");

            // date exists.  format & output
            if (endDate!=string::npos)
            {
                // erase XML tags <date>
                line.erase(endDate);
                line.erase(0, beginDate + 6);

                // ------- DATE specific -------
                // truncate last 3 chars (equivalent to divide by 1000)
                line.erase(line.length() - 3);
                // convert to time_t
                //long intTime = stol(line); // do I need this temporary long int?
                //time_t msgDate = intTime;
                time_t msgDate = stol(line); // new, cuts out long int
                char* msgDateOutput = ctime(&msgDate);  // do I need a new string?
                // output date
                cout << msgDateOutput;

            }

            //===============================================================
            // find XML tags <type>
            size_t beginType = line.find("<type>");
            size_t endType = line.find("</type>");

            // type exists.  format & output
            if (endType!=string::npos)
            {
                // erase XML tags <type>
                line.erase(endType);
                line.erase(0, beginType + 6);

                // ------- TYPE specific -------
                if (stoi(line) == 1) { cout << "A message" << endl; }
                else { cout << "C message" << endl; }

                // formatting for next message
                // has to be here, otherwise it's triggered for each line
                cout << "\n-----------------------------" << endl;
            }
            //===============================================================





        } // end file checking loop

        msgfile.close();
    }
    else cout << "Unable to open file" << endl;

    cout << "\n---- stripXML testing ----" << endl;
    string testing123 = "      <body>Okay.++I+was+just+letting+you+know.</body>";
    if (stripXML("body", &testing123))
    {
        cout << testing123 << endl;
    }
    else { cout << "stripXML fail" << endl;}


    return 0;
}

// % Decoding (URL Decoding)
// credit to tominko.  Jan 28 '11 at 0:52
// https://stackoverflow.com/questions/154536/encode-decode-urls-in-c
string urlDecode(string &SRC) {
    string ret;
    char ch;
    int i, ii;
    for (i=0; i<SRC.length(); i++) {
        if (int(SRC[i])==37) {
            sscanf(SRC.substr(i+1,2).c_str(), "%x", &ii);
            ch=static_cast<char>(ii);
            ret+=ch;
            i=i+2;
        } else {
            ret+=SRC[i];
        }
    }
    return (ret);
}

// strip xml tags and other stuff from line
bool stripXML(string tag, string* line)
{
    // construct begin tag
    string match = {"<"};
    match.append(tag);
    match.append(">");

    // check for begin tag
    size_t begin = line->find(match);
    if (begin == string::npos)
    {
        cout << "ERROR: " << match << " tag not found" << endl;
        return false;
    }

    else
    {
        // construct end tag
        match.erase();
        match = "</";
        match.append(tag);
        match.append(">");

        // check for end tag
        size_t end = line->find(match);
        if (end == string::npos)
        {
            cout << "ERROR: " << match << " tag not found" << endl;
            return false;
        }

        // begin & end found.  Erase cruft
        else
        {
            line->erase(end);
            line->erase(0, begin + 6);

            return true;
        }
    }
}
