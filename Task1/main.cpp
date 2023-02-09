#include <iostream>
#include <Windows.h>
#include <string>
#include <algorithm>
#pragma comment(lib, "urlmon.lib")


int main(int argc, char* argv[])
{
    //check parameters count
    if (argc < 3) {
        std::cout <<"Error: Too few arguments" << std::endl;
        return 0;
    }
    else if (argc > 4) {
        std::cout << "Error: Too much arguments" << std::endl;
        return 0;
    }
    
    //get input parameters 
    std::string fPath(argv[2]);
    std::string fURL(argv[1]);
    std::string sFlag = "open";
    std::string fName(fURL.substr(fURL.rfind("/")));
    fPath += fName;

    //convert UTF-8(ASCII) strings to UTF-16(UNICODE)
    std::wstring wUrl = std::wstring(fURL.begin(), fURL.end());
    std::wstring wPath = std::wstring(fPath.begin(), fPath.end());
    std::wstring wFlag = std::wstring(sFlag.begin(), sFlag.end());


    // try to get bites from given URL to given path
    if (S_OK == URLDownloadToFile(NULL, wUrl.c_str(), wPath.c_str(), 0, NULL)) {
        std::cout << fName + "\tSuccessfully downloaded" << std::endl;
        if (argc == 4) {
            std::cout << argv[3] << std::endl;
            if (strcmp(argv[3], "-x") == 0) {
                std::cout << " Opening " + fName << std::endl;
                ShellExecute(NULL, wFlag.c_str(), wPath.c_str(), NULL, NULL, SW_SHOWDEFAULT);
            }
            else {
                std::cout << "Error: Unknown flag" << std::endl;
            }
        }
    }
    else {
        std::cout << fName +  "\tDownload failed" << std::endl;
    }

    return 0;
}
