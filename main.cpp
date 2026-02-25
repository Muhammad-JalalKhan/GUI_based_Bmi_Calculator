#include "WelcomeFor.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	// Show Welcome Form first
	BMICalculator::WelcomeFor^ welcomeFor = gcnew BMICalculator::WelcomeFor();
	Application::Run(welcomeFor);

	return 0;
}


