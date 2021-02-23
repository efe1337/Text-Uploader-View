#include <Windows.h>
#include <string>
#include <iostream>
#include <Wininet.h>
#include <fstream>
#include <limits>
#include <string>
#include <vector>
#pragma comment(lib, "wininet.lib")
using namespace std;
string replaceAll(string subject, const string& search,
	const string& replace) {
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return subject;
}

string DownloadString(string URL) {
	HINTERNET interwebs = InternetOpenA("Mozilla/5.0", 1, NULL, NULL, NULL);
	HINTERNET urlFile;
	string rtn;
	if (interwebs) {
		urlFile = InternetOpenUrlA(interwebs, URL.c_str(), NULL, NULL, NULL, NULL);
		if (urlFile) {
			char buffer[2000];
			DWORD bytesRead;
			do {
				InternetReadFile(urlFile, buffer, 2000, &bytesRead);
				rtn.append(buffer, bytesRead);
				memset(buffer, 0, 2000);
			} while (bytesRead);
			InternetCloseHandle(interwebs);
			InternetCloseHandle(urlFile);
			string p = replaceAll(rtn, "|n", "\r\n");
			return p;
		}
	}
	InternetCloseHandle(interwebs);
	string p = replaceAll(rtn, "|n", "\r\n");
	return p;
}

int main()
{
	SetConsoleTitleW(L"Text Uploader Hit Generator");
	cout << "TextUploader Url: ";
	string url;	
	cin >> url;
	cout << endl << "How many views do you want?(numbers only): ";
	int tryy;
	cin >> tryy;
	cout << endl;
	system("cls");
	for (size_t i = 0; i < tryy; i++)
	{
		string Content = DownloadString(url);
	}
	system("cls");
	cout << "Done thanks for use!\nPress any key to exit.";
	cin.ignore();
}