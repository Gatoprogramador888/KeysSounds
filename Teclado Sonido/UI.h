#pragma once
#include"Header.h"


class IUI
{
protected:
    HWND hObject = nullptr;
public:
    virtual void SethObject(HWND hwnd) final;
};

class UIListBox : public IUI
{
private:
    UIListBox() = default;

public:
    static UIListBox& Instance()
    {
        static UIListBox instance;
        return instance;
    }

    int GetItemSelect();

    void SetItem(DIR directory);

    void DeleteItem(int index);

    void Load();

    UIListBox(const UIListBox&) = delete;
    UIListBox& operator=(const UIListBox&) = delete;
};


class UIButtonSaved : public IUI
{
private:
    UIButtonSaved() = default;
public:
    static UIButtonSaved& Instance()
    {
        static UIButtonSaved instance;
        return instance;
    }
    UIButtonSaved(const UIButtonSaved&) = delete;
    UIButtonSaved& operator=(const UIButtonSaved&) = delete;


private:


public:

    void SetButtonNotSaved();

    void SetButtonYesSaved();
};