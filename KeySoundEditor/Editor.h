#pragma once
#include "LoadMusicWrapper.h"
#include "WrapperDIR.h"
#include "SavedWrapper.h"
#include <string>

namespace KeySoundEditor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de Editor
	/// </summary>
	public ref class Editor : public System::Windows::Forms::Form
	{
	public:
		Editor(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
			InitializeClass();
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~Editor()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ListBox^ ListMusic;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ BTN_SAVED;
	private: System::Windows::Forms::Button^ BTN_ACCEPT;
	private: System::Windows::Forms::Button^ BTN_RF;
	private: System::Windows::Forms::Button^ BTN_ADD;
	private: System::Windows::Forms::Button^ BTN_DELETE;
	private: System::Windows::Forms::Button^ BTN_MODIFY;
	private: System::Windows::Forms::ComboBox^ Configs;
	private: System::Windows::Forms::Button^ BTN_ADDCO;
	private: System::Windows::Forms::Button^ BTN_DELCON;
	private: System::Windows::Forms::Timer^ loadTimer;
	private: System::Windows::Forms::Timer^ SavedTimer;
	private: System::Windows::Forms::OpenFileDialog^ SearchSound;

	//protected:

	//protected:

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>
		System::ComponentModel::Container ^components;
		LoadMusicWrapper^ loadMusicWrapper;
		WrapperDIR^ wrapperDir;
		SavedWrapper^ savedMusicWrapper;
		System::String^ dllPath = gcnew System::String("SoundLibrary.dll");;
		
	private:
		void InitializeClass()
		{
			loadMusicWrapper = gcnew LoadMusicWrapper(dllPath);
			savedMusicWrapper = gcnew SavedWrapper(dllPath);
			wrapperDir = gcnew WrapperDIR(dllPath);
		}

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SearchSound = (gcnew System::Windows::Forms::OpenFileDialog());
			this->ListMusic = (gcnew System::Windows::Forms::ListBox());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->BTN_SAVED = (gcnew System::Windows::Forms::Button());
			this->BTN_ACCEPT = (gcnew System::Windows::Forms::Button());
			this->BTN_RF = (gcnew System::Windows::Forms::Button());
			this->BTN_ADD = (gcnew System::Windows::Forms::Button());
			this->BTN_DELETE = (gcnew System::Windows::Forms::Button());
			this->BTN_MODIFY = (gcnew System::Windows::Forms::Button());
			this->Configs = (gcnew System::Windows::Forms::ComboBox());
			this->BTN_ADDCO = (gcnew System::Windows::Forms::Button());
			this->BTN_DELCON = (gcnew System::Windows::Forms::Button());
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// ListMusic
			// 
			this->ListMusic->AllowDrop = true;
			this->ListMusic->BackColor = System::Drawing::Color::MidnightBlue;
			this->ListMusic->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->ListMusic->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ListMusic->ForeColor = System::Drawing::Color::White;
			this->ListMusic->FormattingEnabled = true;
			this->ListMusic->ItemHeight = 27;
			this->ListMusic->Location = System::Drawing::Point(181, 257);
			this->ListMusic->Name = L"ListMusic";
			this->ListMusic->Size = System::Drawing::Size(799, 488);
			this->ListMusic->TabIndex = 0;
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::RoyalBlue;
			this->panel1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->panel1->Controls->Add(this->label1);
			this->panel1->ForeColor = System::Drawing::Color::White;
			this->panel1->Location = System::Drawing::Point(0, 30);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(980, 100);
			this->panel1->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Impact", 16, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::Lime;
			this->label1->Location = System::Drawing::Point(355, 36);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(266, 39);
			this->label1->TabIndex = 0;
			this->label1->Text = L"KEY SOUND EDITOR";
			// 
			// BTN_SAVED
			// 
			this->BTN_SAVED->BackColor = System::Drawing::Color::RoyalBlue;
			this->BTN_SAVED->Font = (gcnew System::Drawing::Font(L"Impact", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->BTN_SAVED->Location = System::Drawing::Point(860, 161);
			this->BTN_SAVED->Name = L"BTN_SAVED";
			this->BTN_SAVED->Size = System::Drawing::Size(120, 60);
			this->BTN_SAVED->TabIndex = 2;
			this->BTN_SAVED->Text = L"SAVED";
			this->BTN_SAVED->UseVisualStyleBackColor = false;
			this->BTN_SAVED->Click += gcnew System::EventHandler(this, &Editor::BTN_SAVED_Click);
			// 
			// BTN_ACCEPT
			// 
			this->BTN_ACCEPT->BackColor = System::Drawing::Color::RoyalBlue;
			this->BTN_ACCEPT->Font = (gcnew System::Drawing::Font(L"Impact", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->BTN_ACCEPT->Location = System::Drawing::Point(666, 161);
			this->BTN_ACCEPT->Name = L"BTN_ACCEPT";
			this->BTN_ACCEPT->Size = System::Drawing::Size(120, 60);
			this->BTN_ACCEPT->TabIndex = 3;
			this->BTN_ACCEPT->Text = L"ACCEPT";
			this->BTN_ACCEPT->UseVisualStyleBackColor = false;
			this->BTN_ACCEPT->Click += gcnew System::EventHandler(this, &Editor::BTN_ACCEPT_Click);
			// 
			// BTN_RF
			// 
			this->BTN_RF->BackColor = System::Drawing::Color::RoyalBlue;
			this->BTN_RF->Font = (gcnew System::Drawing::Font(L"Impact", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->BTN_RF->Location = System::Drawing::Point(12, 157);
			this->BTN_RF->Name = L"BTN_RF";
			this->BTN_RF->Size = System::Drawing::Size(120, 60);
			this->BTN_RF->TabIndex = 4;
			this->BTN_RF->Text = L"READ FOLDER";
			this->BTN_RF->UseVisualStyleBackColor = false;
			this->BTN_RF->Click += gcnew System::EventHandler(this, &Editor::BTN_RF_Click);
			// 
			// BTN_ADD
			// 
			this->BTN_ADD->BackColor = System::Drawing::Color::RoyalBlue;
			this->BTN_ADD->Font = (gcnew System::Drawing::Font(L"Impact", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->BTN_ADD->Location = System::Drawing::Point(12, 291);
			this->BTN_ADD->Name = L"BTN_ADD";
			this->BTN_ADD->Size = System::Drawing::Size(120, 60);
			this->BTN_ADD->TabIndex = 5;
			this->BTN_ADD->Text = L"ADD";
			this->BTN_ADD->UseVisualStyleBackColor = false;
			this->BTN_ADD->Click += gcnew System::EventHandler(this, &Editor::BTN_ADD_Click);
			// 
			// BTN_DELETE
			// 
			this->BTN_DELETE->BackColor = System::Drawing::Color::RoyalBlue;
			this->BTN_DELETE->Font = (gcnew System::Drawing::Font(L"Impact", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->BTN_DELETE->Location = System::Drawing::Point(12, 453);
			this->BTN_DELETE->Name = L"BTN_DELETE";
			this->BTN_DELETE->Size = System::Drawing::Size(120, 60);
			this->BTN_DELETE->TabIndex = 6;
			this->BTN_DELETE->Text = L"DELETE";
			this->BTN_DELETE->UseVisualStyleBackColor = false;
			this->BTN_DELETE->Click += gcnew System::EventHandler(this, &Editor::BTN_DELETE_Click);
			// 
			// BTN_MODIFY
			// 
			this->BTN_MODIFY->BackColor = System::Drawing::Color::RoyalBlue;
			this->BTN_MODIFY->Font = (gcnew System::Drawing::Font(L"Impact", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->BTN_MODIFY->Location = System::Drawing::Point(12, 607);
			this->BTN_MODIFY->Name = L"BTN_MODIFY";
			this->BTN_MODIFY->Size = System::Drawing::Size(120, 60);
			this->BTN_MODIFY->TabIndex = 7;
			this->BTN_MODIFY->Text = L"MODIFY";
			this->BTN_MODIFY->UseVisualStyleBackColor = false;
			this->BTN_MODIFY->Click += gcnew System::EventHandler(this, &Editor::BTN_MODIFY_Click);
			// 
			// Configs
			// 
			this->Configs->BackColor = System::Drawing::Color::Navy;
			this->Configs->ForeColor = System::Drawing::Color::White;
			this->Configs->FormattingEnabled = true;
			this->Configs->Location = System::Drawing::Point(456, 157);
			this->Configs->Name = L"Configs";
			this->Configs->Size = System::Drawing::Size(165, 28);
			this->Configs->TabIndex = 8;
			this->Configs->Text = L"config1";
			this->Configs->SelectedIndexChanged += gcnew System::EventHandler(this, &Editor::Configs_SelectedIndexChanged);
			// 
			// BTN_ADDCO
			// 
			this->BTN_ADDCO->BackColor = System::Drawing::Color::RoyalBlue;
			this->BTN_ADDCO->Location = System::Drawing::Point(280, 136);
			this->BTN_ADDCO->Name = L"BTN_ADDCO";
			this->BTN_ADDCO->Size = System::Drawing::Size(124, 49);
			this->BTN_ADDCO->TabIndex = 9;
			this->BTN_ADDCO->Text = L"ADD CONFIG";
			this->BTN_ADDCO->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->BTN_ADDCO->UseVisualStyleBackColor = false;
			this->BTN_ADDCO->Click += gcnew System::EventHandler(this, &Editor::BTN_ADDCO_Click);
			// 
			// BTN_DELCON
			// 
			this->BTN_DELCON->BackColor = System::Drawing::Color::RoyalBlue;
			this->BTN_DELCON->Location = System::Drawing::Point(280, 191);
			this->BTN_DELCON->Name = L"BTN_DELCON";
			this->BTN_DELCON->Size = System::Drawing::Size(124, 40);
			this->BTN_DELCON->TabIndex = 10;
			this->BTN_DELCON->Text = L"DEL CONFIG";
			this->BTN_DELCON->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->BTN_DELCON->UseVisualStyleBackColor = false;
			this->BTN_DELCON->Click += gcnew System::EventHandler(this, &Editor::BTN_DELCON_Click);
			// 
			// Editor
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::MidnightBlue;
			this->ClientSize = System::Drawing::Size(978, 744);
			this->Controls->Add(this->BTN_DELCON);
			this->Controls->Add(this->BTN_ADDCO);
			this->Controls->Add(this->Configs);
			this->Controls->Add(this->BTN_MODIFY);
			this->Controls->Add(this->BTN_DELETE);
			this->Controls->Add(this->BTN_ADD);
			this->Controls->Add(this->BTN_RF);
			this->Controls->Add(this->BTN_ACCEPT);
			this->Controls->Add(this->BTN_SAVED);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->ListMusic);
			this->Name = L"Editor";
			this->Text = L"Editor";
			this->Load += gcnew System::EventHandler(this, &Editor::Editor_Load);
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->ResumeLayout(false);
			//
			//OFN
			//
			SearchSound->Filter = "sound file (*.wav)|*.wav";
			SearchSound->FilterIndex = 1;
			SearchSound->RestoreDirectory = true;

		}
#pragma endregion

			//Buttons
		private: System::Void BTN_SAVED_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			int timeSleep = 50;
			SavedTimer = gcnew System::Windows::Forms::Timer();
			SavedTimer->Interval = timeSleep; // milisegundos (0.5 seg)
			SavedTimer->Tick += gcnew System::EventHandler(this, &Editor::OnSavedTick);
			SavedTimer->Start();
		}

		private: System::Void BTN_ACCEPT_Click(System::Object^ sender, System::EventArgs^ e) {
		}

		private: System::Void BTN_RF_Click(System::Object^ sender, System::EventArgs^ e)
		{
		}
		private: System::Void BTN_ADD_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			System::String^ file = OFN();
			ListMusic->Items->Add(file);
		}

		private: System::Void BTN_DELETE_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			System::String^ itemName = ListMusic->SelectedItem->ToString();

			if (IsRemove(System::String::Format("Do you want to delete {0} ? ", itemName)) == NULL)return;
		}

		private: System::Void BTN_MODIFY_Click(System::Object^ sender, System::EventArgs^ e)
		{
			System::String^ itemName = ListMusic->SelectedItem->ToString();
			
			int index = IsRemove(System::String::Format("Do you want to modify {0} ? ", itemName));

			if (index == NULL)return;

			System::String^ file = OFN();

			ListMusic->Items->Insert(index, file);
		}
		private: System::Void BTN_ADDCO_Click(System::Object^ sender, System::EventArgs^ e) {
		}
		private: System::Void BTN_DELCON_Click(System::Object^ sender, System::EventArgs^ e) {
		}

			   //Combobox
		private: System::Void Configs_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) 
		{
			
		}
			   //Editor

		private: System::Void Editor_Load(System::Object^ sender, System::EventArgs^ e) 
		{
			int timeSleep = 50;
			loadTimer = gcnew System::Windows::Forms::Timer();
			loadTimer->Interval = timeSleep; // milisegundos (0.5 seg)
			loadTimer->Tick += gcnew System::EventHandler(this, &Editor::OnLoadTick);
			loadTimer->Start();
			loadMusicWrapper->StartAsyncLoad();
		}

	   private: System::Void OnLoadTick(System::Object^ sender, System::EventArgs^ e)
	   {
		   loadMusicWrapper->UpdateAsyncLoad();

		   if (loadMusicWrapper->IsLoadDone())
		   {
			   LoadInListBox();
			   loadTimer->Stop();
		   }
	   }

		private: System::Void OnSavedTick(System::Object^ sender, System::EventArgs^ e)
		{
			wrapperDir->SetMusicList(ListMusic->Items);

			savedMusicWrapper->StartAsyncSaved();
			savedMusicWrapper->UpdateAsyncSaved();


			if (savedMusicWrapper->IsSavedDone())
			{
				MessageBox::Show("saved sounds");
				SavedTimer->Stop();
			}

		}


			  //Funciones del Editor
		private: System::Void LoadInListBox()
		{
			if (wrapperDir->isEmpty())return;

			System::Collections::Generic::List<DIR_IMPORT^>^ list = wrapperDir->GetMusicList();
			
			
			for (int i = 0; i < wrapperDir->Count(); i++)
			{
				ListMusic->Items->Add(list->ToArray()[0]->dir);
			}
		}

		private: System::String^ OFN()
		{
			System::String^ file = gcnew System::String("");
			if (SearchSound->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				file = SearchSound->FileName;
			}
			return file;
		}

		private: int IsRemove(System::String^ message)
		{
			System::String^ itemName = ListMusic->SelectedItem->ToString();

			System::Windows::Forms::DialogResult result = System::Windows::Forms::MessageBox::Show
			(
				message,
				"Warning",
				System::Windows::Forms::MessageBoxButtons::YesNo,
				System::Windows::Forms::MessageBoxIcon::Warning
			);
			if (result == System::Windows::Forms::DialogResult::No)return NULL;

			int index = ListMusic->SelectedIndex;

			ListMusic->Items->RemoveAt(index);

			return index;
		}

		private: System::String^ WStringToSysString(const std::wstring& wstr)
		{
			 return gcnew System::String(wstr.c_str());
		}

		public: static std::wstring SysStringToWString(System::String^ s)
		{
			using namespace System::Runtime::InteropServices;
			const wchar_t* chars = (const wchar_t*)(Marshal::StringToHGlobalUni(s)).ToPointer();
			std::wstring wstr(chars);
			Marshal::FreeHGlobal(System::IntPtr((void*)chars));
			return wstr;
		}

};

}
