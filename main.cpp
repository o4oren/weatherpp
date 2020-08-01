#include <string>
#include <getopt.h>
#include <iostream>

using namespace std;

static void showHelp(char* name)
{
    std::cerr << "Usage: " << name << " [option(s)] [LOCATION]"
              << "Options:\n"
              << "\t-h,--help\t\tShow this help message\n"
              << "\t-p,--provider PROVIDER\tSpecify the weather provider name"
              << std::endl;
}

int main(int argc, char* argv[])
{
    int opt;
    string location, weatherServiceName, apiKey;

    while ((opt = getopt(argc,argv,"hp:d")) != EOF)
        switch(opt)
        {
            case 'h':
                showHelp(argv[0]);
                break;
            case 'p':
                weatherServiceName = optarg;
                cout << "Selected weather provider is"<< optarg <<endl;
                break;
            default: cout << endl; abort();
        }

    exit(EXIT_SUCCESS);
}
