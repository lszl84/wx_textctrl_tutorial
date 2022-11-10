#pragma once

#include <wx/wx.h>
#include "validatorwithlabelout.h"

class PasswordMatchValidator : public ValidatorWithLabelOut
{
public:
    PasswordMatchValidator(wxStaticText *msgLabel, wxTextCtrl *matchSourceCtrl)
        : ValidatorWithLabelOut(msgLabel), sourceCtrl(matchSourceCtrl) {}
    PasswordMatchValidator(const PasswordMatchValidator &validator)
        : ValidatorWithLabelOut(validator) { sourceCtrl = validator.sourceCtrl; }

    virtual wxObject *Clone() const override { return new PasswordMatchValidator(*this); }

private:
    std::pair<bool, wxString> CheckValidity(const wxString &) const override
    {
        wxString source = sourceCtrl->GetValue();
        wxString repeat = GetTextEntry()->GetValue();

        if (sourceCtrl->GetValidator() && !sourceCtrl->GetValidator()->Validate(nullptr))
        {
            return {false, ""};
        }
        else if (source != repeat)
        {
            return {false, "Passwords do not match."};
        }
        else
        {
            return {true, "Passwords match."};
        }
    }

    wxTextCtrl *sourceCtrl;
};
