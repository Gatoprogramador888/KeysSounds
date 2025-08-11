#include "UI.h"
#include "resource1.h"


void IUI::SethObject(HWND hwnd)
{
	hObject = hwnd;
}


int UIListBox::GetItemSelect()
{
	LRESULT index = SendMessage(hObject, LB_GETCURSEL, NULL, NULL);
	LRESULT indexData = SendMessage(hObject, LB_GETITEMDATA, (WPARAM)index, NULL);

	return indexData;
}

void UIListBox::SetItem(DIR directory)
{
	SendMessageW(hObject, LB_ADDSTRING, NULL, (LPARAM)directory.dir.c_str());
	SendMessageA(hObject, LB_SETITEMDATA, (WPARAM)directory.index, (LPARAM)directory.index);
}

void UIListBox::DeleteItem(int index)
{
	SendMessage(hObject, LB_DELETESTRING, (WPARAM)index, NULL);
}

void UIListBox::Load()
{
	for (size_t i = 0; i < listMusic.size(); i++)
	{
		try
		{
			SetItem(listMusic.at(i));
		}
		catch (const std::out_of_range& error)
		{
			std::cerr << error.what() << std::endl;
		}
	}
}

void UIButtonSaved::SetButtonNotSaved()
{
	SetWindowText(hObject, "SAVE*");
}

void UIButtonSaved::SetButtonYesSaved()
{
	SetWindowText(hObject, "SAVE");
}
