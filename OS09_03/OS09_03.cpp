#include <Windows.h>
#include <iostream>

using namespace std;

bool printFileTxt(LPWSTR FileName)
{
    try
    {
        HANDLE hf = CreateFile(FileName, GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        DWORD n = 1000;
        char buf[1000];
        ZeroMemory(buf, sizeof(buf));
        ReadFile(hf, &buf, 1000, &n, NULL);
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

bool insRowFileTxt(LPWSTR FileName, const char* str, DWORD row) {
    
    
    try
    {
        Sleep(1000);
        HANDLE hf;
        hf = CreateFile(FileName, GENERIC_WRITE | GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

        DWORD n = NULL;
        int rowCount;
        if (row == 0)
        {
            rowCount = 0;
        }
        else
        {
            rowCount = 1;
        }
        char buf[1000];
        char newBuf[1000];
        int lenNewBuf = 0;
        ZeroMemory(buf, sizeof(buf));
        ZeroMemory(newBuf, sizeof(newBuf));
        ReadFile(hf, &buf, 1000, &n, NULL);
        CloseHandle(hf);
        for (int i = 0; i < strlen(buf); i++) 
        {
            if (rowCount == row)
            {
                 for (int j = 0; j < strlen(str); j++)
                 {
                      newBuf[lenNewBuf] = str[j];
                      lenNewBuf++;

                 }
                 newBuf[lenNewBuf] = '\n';
                 lenNewBuf++;
                 rowCount++;
            }
            if (buf[i] == '\n') { rowCount++; }
            newBuf[lenNewBuf] = buf[i];
            lenNewBuf++;
        }
        if (row == -1)
        {
            for (int j = 0; j < strlen(str); j++)
            {
                newBuf[lenNewBuf] = str[j];
                lenNewBuf++;

            }
            newBuf[lenNewBuf] = '\n';
            lenNewBuf++;
            rowCount++;
        }
        HANDLE hf1;
        hf1 = CreateFile(FileName, GENERIC_WRITE | GENERIC_READ, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        UnlockFile(FileName,0,0,0,1024);
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
    wchar_t a[] = L"D:\\1\\1\\OS09_03.txt";
    int rows[4] = { -1, 0, 5, 7 };
    printFileTxt(a);
    for (int i = 0; i < 4; i++)
    {
        insRowFileTxt(a, "New row", rows[i]);
        printFileTxt(a);
    }
    system("pause");
}