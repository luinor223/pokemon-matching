#include "resources.h"

int main()
{
    fstream file("save\\sample.bin", ios::in | ios::binary);
    savefile account;

    file.seekg(0, ios::end);
    int size = file.tellg();
    cout <<endl;
    cout << "sample.bin size: " << size << " bytes." << endl;
    cout << "savefile struct size: " << sizeof(account) << " bytes." << endl;

    
}