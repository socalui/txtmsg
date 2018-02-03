#include "message.h"
#include <iostream>
#include <string>
#include <time.h>

using namespace std;


message::message(QObject *parent) : QObject(parent)
{
//    cout << "Enter name of the phone's owner: ";
//    getline(cin, nameOP);
//    cout << "\nEnter name of other person: ";
//    getline(cin, nameOther);

    nameOP = "phone owner";
    nameOther = "other person";

    body = "";
    isSenderOP = 0;
    date = 0;
}

// clear before starting
void message::clearMessage()
{
    body.clear();
    date = 0;
}


// print the message
// BROKEN.  easily fixed but not important
void message::printMessage()
{
    if(getIsSenderOP()) { cout << nameOP << " says:" << endl; }
    else { cout << nameOther << " says:" << endl; }
    cout << body << endl;
    cout << ctime(&date) << endl;
    cout << "==================================================" << endl;
}

// strip xml tags
bool message::stripXML(string* p_tag, string* p_body)
{
    // construct begin tag
    string match = {"<"};
    match.append(*p_tag);
    match.append(">");

    // check for begin tag
    size_t begin = p_body->find(match);
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
        match.append(*p_tag);
        match.append(">");

        // check for end tag
        size_t end = p_body->find(match);
        if (end == string::npos)
        {
            cout << "ERROR: " << match << " tag not found" << endl;
            return false;
        }

        // begin & end found.  Erase tags
        else
        {
            p_body->erase(end);
            p_body->erase(0, begin + p_tag->length() + 2);

            return true;
        }
    }
}

// Set functions /////////////////////////////////////////////
// Format body of message
// URL Decoding credit to tominko
// https://stackoverflow.com/questions/154536/encode-decode-urls-in-c
void message::setBody(string line)
{
    // set data member
    body = line;

    // if the proper XML tags exist, strip them
    string tagName = "body";

    if(stripXML(&tagName, &body))
    {
        string ret;
        char ch;
        unsigned long i;
        int ii;
        for (i=0; i<body.length(); i++) {

            // URL DEncode
            if (int(body[i])==37)
            {
                sscanf(body.substr(i+1,2).c_str(), "%x", &ii);
                ch=static_cast<char>(ii);
                ret+=ch;
                i=i+2;
            }

            // replace '+'
            else if(int(body[i])==43)
            { ret+=" "; }
            //{ ret.replace(i, 1, " "); }  // old way

            else { ret+=body[i]; }
        }

        // replace
        body = ret;

        // diagnostic
        //cout << body << endl;
    }

    else { cout << "xml body tags incomplete" << endl; }
}


// convert string to unix time
void message::setDate(string line)
{
    string tagName = "date";

    // if the proper xml tags exist, strip them
    if( stripXML(&tagName, &line) )
    {
        // milliseconds to seconds
        line.erase(line.length() - 3);
        // convert to time_t
        time_t msgDate = stol(line);

        // set data member
        date = msgDate;
    }

    else { cout << "xml date tags incomplete" << endl; }
}


// is sender of message owner of phone
void message::setIsSenderOP(string type)
{
    // if the proper xml tags exist, strip them
    string tagName = "type";
    if( stripXML(&tagName, &type) )
    {

        if(stoi(type) == 1) // other person
        { isSenderOP = false; }

        else if(stoi(type) == 2) // owner of phone
        { isSenderOP = true; }

        else
        {
            cout << "Error: sender type out of range: " << type << endl;
        }


    }

    else { cout << "type xml tags incomplete. (isSenderOP)" << endl; }


    // diagnostic
    //cout << "isSenderOP: " << isSenderOP << endl;
}


// Get functions /////////////////////////////////////////////
string* message::getBody()
{ return &body; }

bool message::getIsSenderOP()
{ return isSenderOP; }

time_t message::getDate()
{ return date; }
