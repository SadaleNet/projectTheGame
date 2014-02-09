#include <windows.h>
#include <wininet.h>
#pragma comment (lib,"Wininet.lib")

#include "RemoteDb.h"
#include <stdexcept>

int RemoteDb::HttpGetRequest(const std::string& url, std::string& responseBody) const{
	//initialize request
	responseBody = "";
	int httpStatusCode;
	char strHeaders[] = "Content-Type: application/x-www-form-urlencoded";
	LPCSTR accept[2]={"*/*", NULL};
	
	std::string resourceLocation; //e.g. www.example.com
	std::string resourceName; //e.g. /gamedb/login.php
	std::string formData; //e.g. foo=bar&baz=qux

	if( url.find('?') == std::string::npos ){
		resourceLocation = url.substr(0, url.find('/'));
		resourceName = url.substr(url.find('/'));
	}else{
		resourceLocation = url.substr(0, url.find('/'));
		resourceName = url.substr(url.find('/'), url.find('?')-url.find('/'));
		formData = url.substr(url.find('?')+1); //Query string of GET request
	}

	//send the request
	HINTERNET hSession = InternetOpen(L"", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	HINTERNET hConnect = InternetConnectA(hSession, resourceLocation.data(), INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 1 );
	HINTERNET hRequest = HttpOpenRequestA(hConnect, "POST", resourceName.data(), NULL, NULL, accept, 0, 1);

	if( HttpSendRequestA(hRequest, strHeaders, strlen(strHeaders), (formData.size()==0?NULL:&formData[0]), formData.size()) != TRUE ){
		responseBody = "Error on sending request: "+std::to_string((long long)GetLastError());
		throw std::runtime_error(responseBody);
	}

	//store the status code
	char statusCodeBuffer[64];
	DWORD statusCodeSize = sizeof(statusCodeBuffer);
	if( HttpQueryInfoA(hRequest, HTTP_QUERY_STATUS_CODE, &statusCodeBuffer, &statusCodeSize, 0) != TRUE ){
		responseBody = "Error on getting status code: "+std::to_string((long long)GetLastError());
		throw std::runtime_error(responseBody);
	}
	httpStatusCode = atoi(statusCodeBuffer);

	//get the respond body
	const size_t RESPONSE_BUFFER_SIZE = 1024*1024;
	char* responseBodyTemp = new char[RESPONSE_BUFFER_SIZE];
	DWORD sizeRead;
	if( InternetReadFile(hRequest, responseBodyTemp, RESPONSE_BUFFER_SIZE, &sizeRead) != TRUE ){
		responseBody = "Error on reading internet file: "+std::to_string((long long)GetLastError());
		throw std::runtime_error(responseBody);
	}
	responseBodyTemp[sizeRead] = '\0';
	responseBody = responseBodyTemp;
	delete[] responseBodyTemp;

	//close stuffs
	InternetCloseHandle(hSession);
	InternetCloseHandle(hConnect);
	InternetCloseHandle(hRequest);

	return httpStatusCode;

}