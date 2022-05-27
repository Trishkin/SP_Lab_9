#include <Windows.h>
#include <iostream>

using namespace std;

int rowCount(LPWSTR FileName)
{
    try
    {
        Sleep(100);
        HANDLE hf;
        hf = CreateFile(FileName, GENERIC_WRITE | GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        DWORD n = NULL;
        char buf[300];
        int row = 0;
        ZeroMemory(buf, sizeof(buf));
        ReadFile(hf, &buf, 300, &n, NULL);
        CloseHandle(hf);
        for (int i = 0; i < strlen(buf); i++)
        {
            if (buf[i] == '\n')
            {
                row++;
            }
        }
        return row;
    }
    catch (const char* err)
    {
        cout << "---Error: " << err << endl;
        return -1;
    }
}



bool printWatchRowFileTxt(LPWSTR FileName, DWORD mlsec)
{
    try
    {
        HANDLE dwChangeHandle;
        DWORD dwWaitStatus;
        wstring dir(FileName);
        dir = dir.substr(0,dir.find_last_of('\\'));
        cout << "Row count in file = " << rowCount(FileName) << endl;
        cout << "Begin" << endl;
        clock_t t2;
        clock_t t1 = clock();
        while (true)
        {
             t2 = clock();
            if ((t2 - t1) <= mlsec)
            {
                dwChangeHandle = FindFirstChangeNotification(dir.c_str(), false, FILE_NOTIFY_CHANGE_SIZE);
                dwWaitStatus = WaitForSingleObject(dwChangeHandle, mlsec);
                
                if (dwWaitStatus == WAIT_OBJECT_0)
                {
                    FindCloseChangeNotification(dwChangeHandle);
                    cout << "Find some change: " << (float)(t2 - t1) / 1000 << " sec" << endl;
                    

                }
                cout << "Row count in file = " << rowCount(FileName) << endl;
            }
            else
            {
                break;
            }
        }
        
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
    if (!printWatchRowFileTxt(a, 60000))
    {
        cout << "Nothing changed " << endl;
    }

    system("pause");
}
