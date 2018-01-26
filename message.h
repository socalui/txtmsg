#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
#include <time.h>

using namespace std;


class message
{
public:
    message();

    // clear
    void clearMessage();

    // print
    void printMessage();

    // set
    void setBody(string line);
    void setDate(string dateString);
    void setIsSenderOP(string type);

    // get
    string* getBody();
    bool getIsSenderOP();
    time_t getDate();

private:
    // data members
    string body;
    bool isSenderOP;  // work on this.  how is set/get different than isSenderOP()?
    time_t date;

    string nameOP;
    string nameOther;


    // strip xml tags
    static bool stripXML(string* tag, string* p_line);


};

#endif // MESSAGE_H
