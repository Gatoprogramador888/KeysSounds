#pragma once
#include "LoadMusicWrapper.h"
#include "WrapperDIR.h"
#include "SavedWrapper.h"
#include "WrapperSettings.h"
#include "Creation Configuration.h"
#include <string>
#include <filesystem>
#include <vector>

namespace KeySoundEditor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	namespace fs = std::filesystem;

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
	private: System::Windows::Forms::Timer^ savedTimer;
	private: System::Windows::Forms::OpenFileDialog^ searchSound;
	private: System::Windows::Forms::FolderBrowserDialog^ searchFolder;

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
		WrapperSettings^ wrapperSettings;
		System::String^ dllPath = gcnew System::String("SoundLibrary.dll");
		String^ previous_selection;
		String^ DEFAULT = gcnew String(L"");
		int timeSleep = 16;
		
	private:
		void InitializeClass()
		{
			loadMusicWrapper = gcnew LoadMusicWrapper(dllPath);
			savedMusicWrapper = gcnew SavedWrapper(dllPath);
			wrapperDir = gcnew WrapperDIR(dllPath);
			wrapperSettings = gcnew WrapperSettings(dllPath);
			//
			//OFN
			//
			searchSound->Filter = "sound file (*.wav)|*.wav";
			searchSound->FilterIndex = 1;
			searchSound->RestoreDirectory = true;
			//
			//FBD
			//
			searchFolder = gcnew System::Windows::Forms::FolderBrowserDialog();
			searchFolder->Description = "sounds folder";
			searchFolder->ShowNewFolderButton = false;

		}

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->searchSound = (gcnew System::Windows::Forms::OpenFileDialog());
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
			this->Configs->Text = L"";
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


		}
#pragma endregion

			//Buttons
		private: System::Void BTN_SAVED_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			savedTimer = gcnew System::Windows::Forms::Timer();
			savedTimer->Interval = timeSleep; // milisegundos (0.5 seg)
			savedTimer->Tick += gcnew System::EventHandler(this, &Editor::OnSavedTick);
			wrapperDir->SetMusicList(ListMusic->Items);
			savedMusicWrapper->StartAsyncSaved();
			savedTimer->Start();
		}

		private: System::Void BTN_ACCEPT_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			String^ seleccion = Configs->Text;
			wrapperSettings->SetMainConfiguration(seleccion);
		}

		private: System::Void BTN_RF_Click(System::Object^ sender, System::EventArgs^ e)
		{
			ReadFolderConvertToWav();
			MessageBox::Show("Reading of the folder is finished");
			BTN_SAVED->Text = "SAVED*";
		}

		private: System::Void BTN_ADD_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			System::String^ file = OFN();

			if (FolderOrSoundIsEmpty(file))return;

			ListMusic->Items->Add(file);
			BTN_SAVED->Text = "SAVED*";
		}

		private: System::Void BTN_DELETE_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			if (IsRemove("Do you want to delete?") == -1)return;
		}

		private: System::Void BTN_MODIFY_Click(System::Object^ sender, System::EventArgs^ e)
		{
			
			int index = IsRemove("Do you want to modify?");

			if (index == -1)return;

			System::String^ file = OFN();

			if (FolderOrSoundIsEmpty(file))return;
			
			ListMusic->Items->Insert(index, file);
		}

		private: System::Void BTN_ADDCO_Click(System::Object^ sender, System::EventArgs^ e)
		{
			CreationConfiguration^ formName = gcnew CreationConfiguration();
			if (formName->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				String^ name = formName->name;
				Configs->Items->Add(name);
				wrapperSettings->AddConfiguration(name);
			}
		}

		private: System::Void BTN_DELCON_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			int select = Configs->SelectedIndex;
			String^ setting = Configs->Text;
			wrapperSettings->DeleteConfiguration(setting);
			Configs->Items->RemoveAt(select);
			Configs->SelectedIndex = select - 1;
			Configs->Update();
		}

			   //Combobox
		private: System::Void Configs_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) 
		{
			std::wstring configuration = SysStringToWString(Configs->Text);
			wrapperSettings->SetCurrentConfiguration(configuration);
			if (previous_selection != DEFAULT)
			{
				ListMusic->Items->Clear();
				StartLoadTimer();
			}
		}
			   //Editor

		private: System::Void Editor_Load(System::Object^ sender, System::EventArgs^ e) 
		{
			int count = wrapperSettings->GetSettings()->Count;
			for (int i = 0; i < count; i++)
			{
				System::String^ item = wrapperSettings->GetSettings()->ToArray()[i];
				Configs->Items->Insert(i, item);
			}
			previous_selection = Configs->Text;
			Configs->Text = wrapperSettings->MainConfiguration();

			StartLoadTimer();
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
			savedMusicWrapper->UpdateAsyncSaved();


			if (savedMusicWrapper->IsSavedDone())
			{
				savedTimer->Stop();
				MessageBox::Show("saved sounds");
				BTN_SAVED->Text = "SAVED";
			}

		}


			  //Funciones del Editor
		private: System::Void LoadInListBox()
		{
			if (wrapperDir->isEmpty()) { 
				return;
			}

			System::Collections::Generic::List<DIR_IMPORT^>^ list = wrapperDir->GetMusicList();
			
			size_t count = wrapperDir->Count();
			for (int i = 0; i < count; i++)
			{
				ListMusic->Items->Add(list->ToArray()[i]->dir);
			}
		}

		private: System::String^ OFN()
		{
			System::String^ file = gcnew System::String("");
			if (searchSound->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				file = searchSound->FileName;
			}
			return file;
		}

		private: System::String^ FBD()//Folder browse dialog
		{
			System::String^ folder = gcnew System::String("");
			if (searchFolder->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				folder = searchFolder->SelectedPath;
			}
			return folder;
		}

		private: int IsRemove(System::String^ message)
		{
			const int noRetuns = -1;

			System::Object^ objectItem = ListMusic->SelectedItem;

			if (objectItem == nullptr)
			{
				System::Windows::Forms::MessageBox::Show
				(
					"Select an item",
					"Info",
					System::Windows::Forms::MessageBoxButtons::OK,
					System::Windows::Forms::MessageBoxIcon::Information
				);
				return noRetuns;
			}

			System::String^ itemName = objectItem->ToString();

			System::Windows::Forms::DialogResult result = System::Windows::Forms::MessageBox::Show
			(
				message,
				"Warning",
				System::Windows::Forms::MessageBoxButtons::YesNo,
				System::Windows::Forms::MessageBoxIcon::Warning
			);
			if (result == System::Windows::Forms::DialogResult::No)return noRetuns;

			int index = ListMusic->SelectedIndex;

			ListMusic->Items->RemoveAt(index);

			BTN_SAVED->Text = "SAVED*";


			return index;
		}

		private: System::Void ReadFolderConvertToWav()
		{
			ListMusic->Items->Clear();
			System::String^ folder = FBD();
			if (FolderOrSoundIsEmpty(folder))return;

			std::wstring wfolder = SysStringToWString(folder);
			std::vector<std::wstring> files;



			for (const auto& entry : fs::directory_iterator(wfolder))
			{
				if (entry.is_regular_file())
				{
					std::wstring file = entry.path().wstring();
					files.push_back(file);
				}
			}
			

			for (size_t i = 0; i < files.size(); i++)
			{
				size_t index = files[i].find(L".wav");
				if (index != std::wstring::npos)
				{	
					ListMusic->Items->Add(gcnew System::String(files[i].c_str()));
				}
			}

		}
		
		private: bool FolderOrSoundIsEmpty(System::String^ folderOrSound)
		{
			bool IsNull = (System::String::IsNullOrEmpty(folderOrSound) || System::String::IsNullOrWhiteSpace(folderOrSound));
			if (IsNull)
			{
				System::Windows::Forms::MessageBox::Show
				(
					"Select a sound or folder",
					"Info",
					System::Windows::Forms::MessageBoxButtons::OK,
					System::Windows::Forms::MessageBoxIcon::Information
				);
			}
			return IsNull;
		}

		private: System::String^ WStringToSysString(const std::wstring& wstr)
		{
			 return gcnew System::String(wstr.c_str());
		}

		private: Void StartLoadTimer()
		{
			previous_selection = Configs->Text;
			loadTimer = gcnew System::Windows::Forms::Timer();
			loadTimer->Interval = timeSleep; // milisegundos (0.5 seg)
			loadTimer->Tick += gcnew System::EventHandler(this, &Editor::OnLoadTick);
			loadTimer->Start();
			loadMusicWrapper->StartAsyncLoad();
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
