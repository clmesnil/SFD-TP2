// ConsoleApplication1.cpp : fichier projet principal.

#include "stdafx.h"
#include "form_main.h"

using namespace System;
using namespace System::Windows::Forms;

int main(array<System::String ^> ^args)
{
	Console::WriteLine(L"Hello World");



	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	ConsoleApplication1::form_main main_form;
	Application::Run(%main_form);



	return 0;
}

