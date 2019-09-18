#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>
#include <math.h>

#include "dsaLib.h"
#include "dbLib.h"
#include "processData.h"

using namespace std;

int main() {
    Initialization();

    void*   pData = nullptr;
    void*   pOutput = nullptr;
    int     N;
    LoadData(pData);
    TDataset* p = static_cast<TDataset*>(pData);
    size_t a = p->getCity().getSize();
	assert(pData != nullptr);
    cout << fixed << setprecision(8);
	//ifstream in("requests.txt");
    string req;
    //clock_t nhap = clock();
    while (true) {
    
        req = "";
        getline(cin, req);
        if (cin.bad()) {
            cin.clear();
            cin.ignore(1024, '\n');
            continue;
        }
    
        if (req == "Exit") {
            break;
        }
        ProcessRequest(req.data(), pData, pOutput, N);
        PrintReqOutput<int>(req.data(), (int*)pOutput, N);
        delete [] (int*)pOutput;
        pOutput = nullptr;
    }
    //clock_t xong = clock();
    a = p->getCity().getSize();
    ReleaseData(pData);
    Finalization();
    return 0;
}