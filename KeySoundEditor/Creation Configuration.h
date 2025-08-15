#pragma once

namespace KeySoundEditor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de CreationConfiguration
	/// </summary>
	public ref class CreationConfiguration : public System::Windows::Forms::Form
	{
	public:
		CreationConfiguration(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~CreationConfiguration()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ Box_Name;
	protected:

	protected:
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ BTN_ACCEPT;
	private: System::Windows::Forms::Button^ BTN_CANCEL;
	public: System::String^ name;

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->Box_Name = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->BTN_ACCEPT = (gcnew System::Windows::Forms::Button());
			this->BTN_CANCEL = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// Box_Name
			// 
			this->Box_Name->Location = System::Drawing::Point(60, 99);
			this->Box_Name->Name = L"Box_Name";
			this->Box_Name->Size = System::Drawing::Size(359, 26);
			this->Box_Name->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(210, 51);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(59, 20);
			this->label1->TabIndex = 1;
			this->label1->Text = L"NAME:";
			// 
			// BTN_ACCEPT
			// 
			this->BTN_ACCEPT->Location = System::Drawing::Point(314, 163);
			this->BTN_ACCEPT->Name = L"BTN_ACCEPT";
			this->BTN_ACCEPT->Size = System::Drawing::Size(105, 45);
			this->BTN_ACCEPT->TabIndex = 2;
			this->BTN_ACCEPT->Text = L"ACCEPT";
			this->BTN_ACCEPT->UseVisualStyleBackColor = true;
			this->BTN_ACCEPT->Click += gcnew System::EventHandler(this, &CreationConfiguration::BTN_ACCEPT_Click);
			// 
			// BTN_CANCEL
			// 
			this->BTN_CANCEL->Location = System::Drawing::Point(60, 163);
			this->BTN_CANCEL->Name = L"BTN_CANCEL";
			this->BTN_CANCEL->Size = System::Drawing::Size(105, 45);
			this->BTN_CANCEL->TabIndex = 3;
			this->BTN_CANCEL->Text = L"CANCEL";
			this->BTN_CANCEL->UseVisualStyleBackColor = true;
			this->BTN_CANCEL->Click += gcnew System::EventHandler(this, &CreationConfiguration::BTN_CANCEL_Click);
			// 
			// CreationConfiguration
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(488, 244);
			this->Controls->Add(this->BTN_CANCEL);
			this->Controls->Add(this->BTN_ACCEPT);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->Box_Name);
			this->Name = L"CreationConfiguration";
			this->Text = L"CreationConfiguration";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void BTN_CANCEL_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
		this->Close();
	}
	private: System::Void BTN_ACCEPT_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		name = Box_Name->Text;
		this->DialogResult = System::Windows::Forms::DialogResult::OK;
		this->Close();
	}
};
}
