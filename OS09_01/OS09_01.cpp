#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>

using namespace std;

bool printFileInfo(LPWSTR FileName) 
{
    try
    {
        HANDLE hf = CreateFile(FileName, GENERIC_WRITE | GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        char* fn = (char*)malloc(100);
        wcstombs(fn, FileName, 100);
        LPBY_HANDLE_FILE_INFORMATION file = new _BY_HANDLE_FILE_INFORMATION();
        GetFileInformationByHandle(hf, file);



        SYSTEMTIME stCreate, stUpdate, stCreateLP, stUpdateLP;
        FileTimeToSystemTime(&file->ftCreationTime, &stCreate);
        FileTimeToSystemTime(&file->ftLastWriteTime, &stUpdate);
        SystemTimeToTzSpecificLocalTime(NULL, &stCreate, &stCreateLP);
        SystemTimeToTzSpecificLocalTime(NULL, &stUpdate, &stUpdateLP);


        cout << "\n��� �����: " << fn << endl;
            switch ((GetFileType(hf)))
            {
            case FILE_TYPE_UNKNOWN:
                cout << "��� �����: unknown file" << endl;
                break;

            case FILE_TYPE_DISK:
                cout << "��� �����: disk file" << endl;
                break;

            case FILE_TYPE_CHAR:
                cout << "��� �����: char file" << endl;
                break;

            case FILE_TYPE_PIPE:
                cout << "��� �����: pipe file" << endl;
                break;

            case FILE_TYPE_REMOTE:
                cout << "��� �����: remote file" << endl;
                break;

            default:
                break;
            }
        
        cout << "������ �����: " << GetFileSize(hf, NULL) << " ����" << endl;
        cout << "���� � ����� ��������: " << stCreateLP.wDay << "." << stCreateLP.wMonth << "." << stCreateLP.wYear
            << " - " << stCreateLP.wHour << ":" << stCreateLP.wMinute << ":" << stCreateLP.wSecond << endl;
        cout << "���� � ����� ����������: " << stUpdateLP.wDay << "." << stUpdateLP.wMonth << "." << stUpdateLP.wYear
            << " - " << stUpdateLP.wHour << ":" << stUpdateLP.wMinute << ":" << stUpdateLP.wSecond << endl;

        CloseHandle(hf);
        return true;
    }
    catch (const char* err)
    {
        cout << "---Error: " << err << endl;
        return false;
    }
}

bool printFileTxt(LPWSTR FileName) 
{
    try
    {
        HANDLE hf = CreateFile(FileName, GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        DWORD n = 300;
        char buf[300];
        ZeroMemory(buf, sizeof(buf));
        ReadFile(hf, &buf, 300, &n, NULL);
        cout << "\n���������� �����:\n" << buf << endl;

        CloseHandle(hf);
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

    wchar_t a[] = L"D:\\1\\1\\OS09_01.txt";

    printFileInfo(a);

    printFileTxt(a);

    system("pause");
}