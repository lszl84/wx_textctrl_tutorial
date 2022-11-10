#pragma once

#include <wx/wx.h>

class ValidatorWithLabelOut : public wxValidator
{
public:
    ValidatorWithLabelOut(wxStaticText *msgLabel, wxString *val = nullptr)
        : value(val), validationMsgLabel(msgLabel)
    {
        SetupEvents();
    }

    ValidatorWithLabelOut(const ValidatorWithLabelOut &validator)
        : wxValidator(validator)
    {
        value = validator.value;
        validationMsgLabel = validator.validationMsgLabel;

        SetupEvents(); // this is why we need copy constructor
    }

    virtual ~ValidatorWithLabelOut() {}

    virtual wxObject *Clone() const override = 0;

    bool TransferFromWindow() override
    {
        if (value)
        {
            wxTextEntry *const text = GetTextEntry();
            *value = text->GetValue();
        }

        return true;
    }

    bool TransferToWindow() override
    {
        if (value)
        {
            wxTextEntry *const text = GetTextEntry();
            text->SetValue(*value);
        }

        return true;
    }

    virtual bool Validate(wxWindow *parent) override
    {
        const auto &[valid, _] = CheckValidity(GetTextEntry()->GetValue());
        return valid;
    }

    void UpdateValidationLabel()
    {
        auto [valid, text] = CheckValidity(GetTextEntry()->GetValue());

        validationMsgLabel->SetLabel(text);
        validationMsgLabel->SetForegroundColour(
            valid ? wxColor(100, 200, 100) : wxColor(200, 100, 100));

        validationMsgLabel->Refresh(); // needed for Windows to update the color
    }

protected:
    virtual std::pair<bool, wxString> CheckValidity(const wxString &str) const = 0;

    virtual void SetupEvents() { Bind(wxEVT_TEXT, &ValidatorWithLabelOut::OnText, this); }
    virtual void OnText(wxCommandEvent &e)
    {
        UpdateValidationLabel();
        e.Skip();
    }

    wxTextEntry *GetTextEntry() const { return dynamic_cast<wxTextEntry *>(GetWindow()); }

private:
    wxStaticText *validationMsgLabel;
    wxString *value;
};
