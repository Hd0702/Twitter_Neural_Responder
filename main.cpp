#define CATCH_CONFIG_RUNNER
#include "dstring.h"
#include <fstream>
#include "reader.h"
#include "classification.h"
#include "catch.hpp"
using namespace std;
int main(int argc, char * argv[])
{
    if (argc > 1 && strcmp(argv[1], "-t") == 0)
       {
        //Running tests
        return Catch::Session().run();
       }
       else if (argc > 1 && strcmp(argv[1], "-c") == 0)
       {
        //Runing Classification
        cout <<"Creating Tweet Classification File. \n This should around a minute" << endl;
        classification create(argv[2],argv[3],argv[4]);
       }
       else if (argc > 1 && strcmp(argv[1], "-r") == 0)
       {
        //running trainer
        cout <<"Creating File for Tweet Classification. \n  This will take about a minute" << endl;
        Reader out(argv[2], argv[3]);
        out.write(4);
        out.write(0);
        out.CreateEndFile(argv[4]);
       }
       else
       {
           cout << "Invalid flag, check arguments" << endl;
           return 1;
    }
    return 0;
}
