#include "dstring.h"
DString::DString() {
    Name = nullptr;  //Making sure we dont have a segfault, assign NO memory;
}
//Copy constructor for char*
DString::DString(const char* NewStr) {
    Name = new char[strlen(NewStr)+1];
    strcpy(Name, NewStr);
}
//Copy constructor for Strings
DString::DString(const DString& CpyString){
    if(CpyString.Name == nullptr)
        Name = nullptr;
    else {
    Name = new char[strlen(CpyString.Name)+1];
    strcpy(Name, CpyString.Name);
    }
}
//Destructor for memory handling
DString::~DString() {
    delete [] Name;
    Name = nullptr;
}
 //assigning string to equal a char
DString& DString::operator= (const char* Compr)  {
    delete[] Name;
    Name = new char[strlen(Compr)+1];
    strcpy(Name, Compr);
    return *this;
}
 //assigning string to equal a string
DString& DString::operator= (const DString& FinStr)  {
    delete[] Name;
    Name= new char[strlen(FinStr.Name)+1];
    strcpy(Name, FinStr.Name);
    return *this;
}
//Adding strings together
DString DString::operator+ (const DString& addst) {
    char *temp = Name;
    Name = new char[strlen(Name) + addst.getLength() + 1];  //want to properly allocate enough memory to new Name char
    strcpy(Name, temp);    //temp prevents memory leaks
    strcat(Name, addst.Name);
    if (strlen(Name) != 0)
            delete [] temp;
    return *this;
}
//comparing string and char returning true if theyre equal
bool DString::operator== (const char* EqCh) const{
    if (strcmp(Name, EqCh) == 0) {
        return true;
    }
    else {
        return false;
    }
}
//Comparing string to another string returning true
bool DString::operator== (const DString& comp) const{
    if(comp.Name != nullptr) {
        if (strcmp(Name, comp.Name) == 0) {
            return true;
        }
         else {
            return false;
         }
    }
    if(Name == nullptr)
        return true;
    else
        return false;
}
//If one string is indexed higher than another return true
bool DString::operator> (const DString& Scmp) const{
    if (strcmp(Name, Scmp.Name) > 0) {
        return true;
    }
    else {
        return false;
    }
}
//this is for indexing
//we use this operator to find a certain character
char& DString::operator[] (const int index) const{
    return Name[index];

}
int DString::getLength() const{
    return strlen(Name);
}
// using start and end point to change string
DString DString::substring(int start, int numChars) const{
    char * ret;
    if(start == 0) {                      //this handles case if start is = 0, so we dont get segfaults
         ret = new char[numChars-start+1];
         strncpy(ret, (Name + start), numChars-start);
    }
    else if (start > 0) {               //similar case but if start is greater than 0
         ret = new char[numChars-start+2];
         strncpy(ret, (Name + start), numChars-start+1);
         ret[numChars-start+1] = '\0';
    }
    DString Let(ret);
    return Let;
}
char* DString::c_str() const{
    return Name;
}
//This handles printing of a string
std::ostream& operator<< (std::ostream& output, const DString& object) {
    if(object.Name != nullptr) {
         output << object.Name;
    }
   return output;
}
std::istream& operator >> (std::istream& input, DString& obj) {
    delete []obj.Name;
    char * temp = new char [256];
    input.getline(temp, 256, '\n');
    obj.Name = new char[strlen(temp)+1];  //name equals temp now and then we delete it for no mem leaks
    strcpy(obj.Name, temp);
    delete [] temp;
    return input;
}
//This returns true if Name is indexed lower
bool DString::operator <(const DString & D2) const{
         if (strcmp(Name, D2.Name) < 0) {
           return true;
          }
         else
          return false;
}
