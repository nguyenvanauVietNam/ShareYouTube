#include "MyForm.h"
using namespace System;
using namespace System::IO;
using namespace System::Windows::Forms;


[STAThread]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Do_an_monhoc::MyForm form;
	Application::Run(%form);
}
