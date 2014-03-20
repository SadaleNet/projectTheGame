#include "messageBox.h"
#include "../project.h"
#include <Windows.h>

void showMessage(std::string message, std::string title){
	MessageBoxA(hWnd, &message[0], &title[0], MB_OK);
}