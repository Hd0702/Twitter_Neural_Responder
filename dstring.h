#ifndef DSTRING
#define DSTRING

#include <cstring>
#include <iostream>
class DString{
                //This is my string class, youll see it is very similar to the handour
    private:    //the most important thing i added was a < operator I used to sort vectors
     char * Name;

    public:

        DString();  //These constructors/destrctors handle memory allocation
        DString(const char*);
        DString(const DString&);
        ~DString();

        bool operator <(const DString&) const;  //Less than operator I used to sort vectors
        DString& operator= (const char*) ;       //Overloaded operators for multiple types of character containers
        DString& operator= (const DString&);
        DString operator+ (const DString&) ;
        bool operator== (const char*) const;
        bool operator== (const DString&) const;
        bool operator> (const DString&) const;
        char& operator[] (const int) const;

 //       void SetName(char*) ;  //If one wanted to change the name of the string
        int getLength() const;
        DString substring(int start, int numChars) const;  //retunrs a part of a string where we index the start and end by Numchars
        char* c_str() const;   //Returns char pointer for c-string methods

        friend std::ostream& operator<< (std::ostream&, const DString&);  //Overloaded stream operators
        friend std::istream& operator >>(std::istream&, DString&);
};


#endif
