#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
#include <time.h>

#include <QObject>

using namespace std;


class message : public QObject
{
public:
    // what is this?  constructor?
    // from Pokenoya01
    explicit message(QObject *parent = nullptr);

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
    // pokenoya01
    Q_OBJECT    // Qt macro
    //Q_Property(int count )


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
