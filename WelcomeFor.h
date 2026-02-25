#pragma once
#include "BMICalculator.h" 

namespace BMICalculator {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class WelcomeFor : public System::Windows::Forms::Form
	{
	public:
		WelcomeFor(void)
		{
			InitializeComponent();
		}

	private:
		Label^ labelTitle;
		Label^ labelName;
		Label^ labelGender;
		Label^ labelAge;
		TextBox^ textBoxName;
		TextBox^ textBoxAge;
		ComboBox^ comboBoxGender;
		Button^ buttonProceed;

		void InitializeComponent(void)
		{
			this->SuspendLayout();

			// Form
			this->ClientSize = System::Drawing::Size(400, 300);
			this->Name = L"WelcomeFor";
			this->Text = L"Welcome";
			this->BackColor = Color::FromArgb(230, 220, 250); // Soft purple background

			// Title Label
			labelTitle = gcnew Label();
			labelTitle->Text = L"Welcome to the BMI Calculator";
			labelTitle->Font = gcnew Drawing::Font(L"Segoe UI", 14, FontStyle::Bold);
			labelTitle->ForeColor = Color::Purple;
			labelTitle->Location = Point(60, 20);
			labelTitle->AutoSize = true;
			this->Controls->Add(labelTitle);

			// Name Label
			labelName = gcnew Label();
			labelName->Text = L"Name:";
			labelName->Location = Point(50, 80);
			labelName->Size = Drawing::Size(100, 20);
			this->Controls->Add(labelName);

			// Name TextBox
			textBoxName = gcnew TextBox();
			textBoxName->Location = Point(150, 80);
			textBoxName->Size = Drawing::Size(180, 20);
			this->Controls->Add(textBoxName);

			// Age Label
			labelAge = gcnew Label();
			labelAge->Text = L"Age:";
			labelAge->Location = Point(50, 120);
			labelAge->Size = Drawing::Size(100, 20);
			this->Controls->Add(labelAge);

			// Age TextBox
			textBoxAge = gcnew TextBox();
			textBoxAge->Location = Point(150, 120);
			textBoxAge->Size = Drawing::Size(180, 20);
			this->Controls->Add(textBoxAge);

			// Gender Label
			labelGender = gcnew Label();
			labelGender->Text = L"Gender:";
			labelGender->Location = Point(50, 160);
			labelGender->Size = Drawing::Size(100, 20);
			this->Controls->Add(labelGender);

			// Gender ComboBox
			comboBoxGender = gcnew ComboBox();
			comboBoxGender->Location = Point(150, 160);
			comboBoxGender->Size = Drawing::Size(180, 20);
			comboBoxGender->DropDownStyle = ComboBoxStyle::DropDownList;
			comboBoxGender->Items->AddRange(gcnew array<Object^> { "Male", "Female", "Other" });
			this->Controls->Add(comboBoxGender);

			// Proceed Button
			buttonProceed = gcnew Button();
			buttonProceed->Text = L"Proceed";
			buttonProceed->Location = Point(150, 210);
			buttonProceed->Size = Drawing::Size(100, 30);
			buttonProceed->BackColor = Color::MediumPurple;
			buttonProceed->ForeColor = Color::White;
			buttonProceed->FlatStyle = FlatStyle::Flat;
			this->buttonProceed->Font = gcnew System::Drawing::Font(L"Segoe UI", 10, FontStyle::Bold);
			buttonProceed->Click += gcnew EventHandler(this, &WelcomeFor::ProceedToCalculator);
			this->Controls->Add(buttonProceed);

			this->Load += gcnew System::EventHandler(this, &WelcomeFor::WelcomeFor_Load);
			this->ResumeLayout(false);
		}

		void ProceedToCalculator(Object^ sender, EventArgs^ e)
		{
			String^ name = textBoxName->Text;
			String^ ageText = textBoxAge->Text;
			String^ gender = comboBoxGender->Text;

			if (String::IsNullOrWhiteSpace(name) || String::IsNullOrWhiteSpace(ageText) || String::IsNullOrWhiteSpace(gender)) {
				MessageBox::Show("Please fill in all the fields (Name, Age, Gender).", "Input Required", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			int age;
			if (!Int32::TryParse(ageText, age) || age <= 0) {
				MessageBox::Show("Please enter a valid numeric age.", "Invalid Age", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			this->Hide();
			BMICalculatorForm^ bmiForm = gcnew BMICalculatorForm(name, gender); // Extend if you want to pass age
			bmiForm->ShowDialog();
			this->Close();
		}

	private: System::Void WelcomeFor_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}
