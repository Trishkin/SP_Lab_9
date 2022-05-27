#include <Windows.h>
#include <iostream>

using namespace std;

bool printFileTxt(LPWSTR FileName) 
{
    try
    {
        HANDLE hf = CreateFile(FileName, GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hf == INVALID_HANDLE_VALUE) throw "open file failed";
        DWORD n = 300;
        char buf[300];
        ZeroMemory(buf, sizeof(buf));
        BOOL b = ReadFile(hf, &buf, 300, &n, NULL);
        if (!b) throw "read file failed";
        cout << "\nСодержимое файла:\n" << buf << endl;

        CloseHandle(hf);
        return true;
    }
    catch (const char* err)
    {
        cout << "---Error: " << err << endl;
        return false;
    }
}

bool delRowFileTxt(LPWSTR FileName, DWORD row) {
    try
    {
        HANDLE hf;
        hf = CreateFile(FileName, GENERIC_WRITE | GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        int rowCount = 1;
        DWORD n = NULL;
        char buf[300];
        char newBuf[300];
        int lenNewBuf = 0;
        ZeroMemory(buf, sizeof(buf));
        ZeroMemory(newBuf, sizeof(newBuf));
        ReadFile(hf, &buf, 300, &n, NULL);
        CloseHandle(hf);

        for (int i = 0; i < strlen(buf); i++) 
        {
            if (rowCount != row) 
            { 
                newBuf[lenNewBuf] = buf[i]; lenNewBuf++; 
            }
            if (buf[i] == ' ') 
            { 
                rowCount++;
            }
        }

        HANDLE hf1;
        hf1 = CreateFile(FileName, GENERIC_WRITE | GENERIC_READ, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

        WriteFile(hf1, newBuf, strlen(newBuf), &n, NULL);
        CloseHandle(hf1);
        return true;
    }
    catch (const char* err)
    {
        cout << "---Error: " << err << endl;
        return false;
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    wchar_t a[] = L"D:\\1\\1\\OS09_02.txt";

    int rows[4] = { 1, 3, 8, 10 };

    printFileTxt(a);

    for (int i = 0; i < 4; i++)
    {
        delRowFileTxt(a, rows[i]);
        printFileTxt(a);
    }
    system("pause");
}