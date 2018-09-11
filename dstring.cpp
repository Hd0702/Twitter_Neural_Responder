#include "dstring.h"
DString::DString() {
    Name = nullptr;  //Making sure we dont have a segfault, assign NO memory;
}
DString::DString(const char* NewStr) {
    Name = new char[strlen(NewStr)+1];   //Copy constructor for char*
    strcpy(Name, NewStr);
}
DString::DString(const DString& CpyString){ //Copy constructor for Strings
    Name = new char[strlen(CpyString.Name)+1];
    strcpy(Name, CpyString.Name);
}
DString::~DString() {   //Destructor for memory handling
    delete [] Name;
    Name = nullptr;
}

DString& DString::operator= (const char* Compr)  {   //assigning string to equal a char
    delete[] Name;
    Name = new char[strlen(Compr)+1];
    strcpy(Name, Compr);
    return *this;
}
DString& DString::operator= (const DString& FinStr)  { //assigning string to equal a string
    delete[] Name;
    Name= new char[strlen(FinStr.Name)+1];
    strcpy(Name, FinStr.Name);
    return *this;
}
//void DString::SetName(char * replace)  {  //This changes the name to something different, similar to =
//    delete [] Name;
//    Name = new char [strlen(replace) +1];
//    strcpy(Name, replace);
//}

DString DString::operator+ (const DString& addst) {  //Adding strings together
    char *temp = Name;
    Name = new char[strlen(Name) + addst.getLength() + 1];  //want to properly allocate enough memory to new Name char
    strcpy(Name, temp);    //temp prevents memory leaks
    strcat(Name, addst.Name);
    if (strlen(Name) != 0)
            delete [] temp;
    return *this;
}
bool DString::operator== (const char* EqCh) const{    //comparing string and char returning true if theyre equal
    if (strcmp(Name, EqCh) == 0) {
        return true;
    }
    else {
        return false;
    }
}
bool DString::operator== (const DString& comp) const{  //Comparing string to another string returning true
    if (strcmp(Name, comp.Name) == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool DString::operator> (const DString& Scmp) const{  //If one string is indexed higher than another return true
    if (strcmp(Name, Scmp.Name) > 0) {
        return true;
    }
    else {
        return false;
    }
}
char& DString::operator[] (const int index) const{
    //this is for indexing
    //we use this operator to find a certain character
    return Name[index];

}
int DString::getLength() const{
    return strlen(Name);
}
DString DString::substring(int start, int numChars) const{ // using start and end point to change string
    char * ret;
    if(start == 0) {                      //this handles case if start is = 0, so we dont get segfaults
         ret = new char[numChars-start+1];
         strncpy(ret, (Name + start), numChars-start);
    }
    else if (start > 0) {               //similar case but if start is greater than 0 so no segfaults
         ret = new char[numChars-start+2];
         strncpy(ret, (Name + start), numChars-start+1);
         ret[numChars-start+1] = '\0';
    }
    DString Let(ret);      //We are returning the new string
    return Let;
}
char* DString::c_str() const{
    return Name;
}

std::ostream& operator<< (std::ostream& output, const DString& object) {
    if(object.Name != nullptr) {
         output << object.Name;            //This handles printing of a string
    }
   return output;
}
std::istream& operator >> (std::istream& input, DString& obj) {
    delete []obj.Name;              //this prevents memory leaks
    char * temp = new char [256];
    input.getline(temp, 256, '\n');       //insert user input into temp
    obj.Name = new char[strlen(temp)+1];  //name equals temp now and then we delete it for no mem leaks
    strcpy(obj.Name, temp);
    delete [] temp;
    return input;
}
bool DString::operator <(const DString & D2) const{
    if (strcmp(Name, D2.Name) < 0) {    //This returns true if Name is indexed lower
        return true;
    }
    else
       return false;
}
