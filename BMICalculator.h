#pragma once

namespace BMICalculator {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::IO;

    public ref class BMICalculatorForm : public System::Windows::Forms::Form
    {
    private:
        String^ userName;
        String^ userGender;
        String^ recordsFilePath;

    public:
        BMICalculatorForm(String^ name, String^ gender)
        {
            userName = name;
            userGender = gender;
            recordsFilePath = Path::Combine(Application::StartupPath, "BMI_Records.txt");
            InitializeComponent();
        }

    private:
        Label^ labelGreeting;
        Label^ labelHeight;
        Label^ labelWeight;
        Label^ labelBMI;
        Label^ labelCategory;
        TextBox^ textBoxHeight;
        TextBox^ textBoxWeight;
        Label^ resultBMI;
        Label^ resultCategory;
        Button^ buttonCalculate;
        Button^ resetButton;
        Button^ viewHistoryButton;

        void InitializeComponent(void)
        {
            this->SuspendLayout();

            this->ClientSize = System::Drawing::Size(500, 450);
            this->Name = L"BMICalculatorForm";
            this->Text = L"BMI Calculator";
            this->BackColor = Color::FromArgb(240, 235, 255);

            // Greeting label
            labelGreeting = gcnew Label();
            labelGreeting->Text = "Welcome, " + userName + " (" + userGender + ")";
            labelGreeting->Font = gcnew Drawing::Font(L"Segoe UI", 14, FontStyle::Bold);
            labelGreeting->ForeColor = Color::Purple;
            labelGreeting->Location = Point(100, 20);
            labelGreeting->AutoSize = true;
            this->Controls->Add(labelGreeting);

            // Height label
            labelHeight = gcnew Label();
            labelHeight->Text = L"Height (cm):";
            labelHeight->Location = Point(100, 80);
            labelHeight->Size = Drawing::Size(120, 25);
            this->Controls->Add(labelHeight);

            // Height textbox
            textBoxHeight = gcnew TextBox();
            textBoxHeight->Location = Point(220, 80);
            textBoxHeight->Size = Drawing::Size(150, 25);
            this->Controls->Add(textBoxHeight);

            // Weight label
            labelWeight = gcnew Label();
            labelWeight->Text = L"Weight (kg):";
            labelWeight->Location = Point(100, 120);
            labelWeight->Size = Drawing::Size(120, 25);
            this->Controls->Add(labelWeight);

            // Weight textbox
            textBoxWeight = gcnew TextBox();
            textBoxWeight->Location = Point(220, 120);
            textBoxWeight->Size = Drawing::Size(150, 25);
            this->Controls->Add(textBoxWeight);

            // Calculate button
            buttonCalculate = gcnew Button();
            buttonCalculate->Text = L"Calculate BMI";
            buttonCalculate->Location = Point(180, 170);
            buttonCalculate->Size = Drawing::Size(100, 40);
            buttonCalculate->BackColor = Color::MediumPurple;
            buttonCalculate->ForeColor = Color::White;
            buttonCalculate->FlatStyle = FlatStyle::Flat;
            buttonCalculate->Click += gcnew EventHandler(this, &BMICalculatorForm::CalculateBMI);
            buttonCalculate->Font = gcnew Drawing::Font(L"Segoe UI", 10, FontStyle::Bold);
            this->Controls->Add(buttonCalculate);

            // Reset button
            resetButton = gcnew Button();
            resetButton->Text = L"Reset";
            resetButton->Location = Point(300, 170);
            resetButton->Size = Drawing::Size(100, 40);
            resetButton->BackColor = Color::MediumPurple;
            resetButton->ForeColor = Color::White;
            resetButton->FlatStyle = FlatStyle::Flat;
            resetButton->Click += gcnew EventHandler(this, &BMICalculatorForm::resetButton_Click);
            resetButton->Font = gcnew Drawing::Font(L"Segoe UI", 10, FontStyle::Bold);
            this->Controls->Add(resetButton);

            // View History button
            viewHistoryButton = gcnew Button();
            viewHistoryButton->Text = L"View History";
            viewHistoryButton->Location = Point(180, 220);
            viewHistoryButton->Size = Drawing::Size(220, 40);
            viewHistoryButton->BackColor = Color::MediumPurple;
            viewHistoryButton->ForeColor = Color::White;
            viewHistoryButton->FlatStyle = FlatStyle::Flat;
            viewHistoryButton->Click += gcnew EventHandler(this, &BMICalculatorForm::viewHistoryButton_Click);
            viewHistoryButton->Font = gcnew Drawing::Font(L"Segoe UI", 10, FontStyle::Bold);
            this->Controls->Add(viewHistoryButton);

            // BMI label
            labelBMI = gcnew Label();
            labelBMI->Text = L"BMI:";
            labelBMI->Location = Point(100, 280);
            labelBMI->Size = Drawing::Size(80, 25);
            labelBMI->Font = gcnew Drawing::Font(L"Segoe UI", 10, FontStyle::Bold);
            this->Controls->Add(labelBMI);

            // Category label
            labelCategory = gcnew Label();
            labelCategory->Text = L"Category:";
            labelCategory->Location = Point(100, 320);
            labelCategory->Size = Drawing::Size(100, 25);
            labelCategory->Font = gcnew Drawing::Font(L"Segoe UI", 10, FontStyle::Bold);
            this->Controls->Add(labelCategory);

            // BMI Value Display
            resultBMI = gcnew Label();
            resultBMI->Text = L"";
            resultBMI->Location = Point(200, 280);
            resultBMI->Size = Drawing::Size(150, 25);
            resultBMI->Font = gcnew Drawing::Font("Arial", 12, FontStyle::Bold);
            resultBMI->ForeColor = Color::FromArgb(59, 89, 152);
            this->Controls->Add(resultBMI);

            // Category Display
            resultCategory = gcnew Label();
            resultCategory->Text = L"";
            resultCategory->Location = Point(200, 320);
            resultCategory->Size = Drawing::Size(200, 25);
            resultCategory->Font = gcnew Drawing::Font("Arial", 12, FontStyle::Bold);
            this->Controls->Add(resultCategory);

            this->ResumeLayout(false);
        }

        void CalculateBMI(Object^ sender, EventArgs^ e)
        {
            double height, weight, bmi;

            if (!Double::TryParse(textBoxHeight->Text, height) || height <= 0) {
                MessageBox::Show("Please enter a valid height in cm.", "Invalid Input", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            if (!Double::TryParse(textBoxWeight->Text, weight) || weight <= 0) {
                MessageBox::Show("Please enter a valid weight in kg.", "Invalid Input", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            // Convert height to meters and calculate BMI
            height /= 100.0;
            bmi = weight / (height * height);
            bmi = Math::Round(bmi, 1);

            // Determine category and color
            String^ category;
            Color categoryColor;

            if (bmi < 18.5) {
                category = "Underweight";
                categoryColor = Color::DodgerBlue;
            }
            else if (bmi < 25) {
                category = "Healthy";
                categoryColor = Color::ForestGreen;
            }
            else if (bmi < 30) {
                category = "Overweight";
                categoryColor = Color::Orange;
            }
            else {
                category = "Obese";
                categoryColor = Color::Red;
            }

            // Update display
            resultBMI->Text = bmi.ToString();
            resultCategory->Text = category;
            resultCategory->ForeColor = categoryColor;

            // Save to file
            SaveBMIRecord(height * 100, weight, bmi, category);
        }

        void SaveBMIRecord(double height, double weight, double bmi, String^ category)
        {
            try {
                StreamWriter^ sw = gcnew StreamWriter(recordsFilePath, true);
                String^ record = String::Format("[{0}] {1} ({2}) - Height: {3}cm, Weight: {4}kg, BMI: {5}, Category: {6}",
                    DateTime::Now.ToString("yyyy-MM-dd HH:mm:ss"),
                    userName,
                    userGender,
                    height.ToString(),
                    weight.ToString(),
                    bmi.ToString(),
                    category);

                sw->WriteLine(record);
                sw->Close();
            }
            catch (Exception^ e) {
                MessageBox::Show("Error saving record: " + e->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        void resetButton_Click(Object^ sender, EventArgs^ e) {
            // Clear input fields
            textBoxHeight->Clear();
            textBoxWeight->Clear();

            // Clear results
            resultBMI->Text = "";
            resultCategory->Text = "";
        }

        void viewHistoryButton_Click(Object^ sender, EventArgs^ e) {
            try {
                if (File::Exists(recordsFilePath)) {
                    String^ historyContent = File::ReadAllText(recordsFilePath);
                    MessageBox::Show(historyContent, "BMI Calculation History", MessageBoxButtons::OK, MessageBoxIcon::Information);
                }
                else {
                    MessageBox::Show("No records found.", "BMI Calculation History", MessageBoxButtons::OK, MessageBoxIcon::Information);
                }
            }
            catch (Exception^ e) {
                MessageBox::Show("Error reading history: " + e->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }
    };
}