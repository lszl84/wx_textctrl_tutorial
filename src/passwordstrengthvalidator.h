#pragma once

#include <wx/wx.h>
#include "validatorwithlabelout.h"

class PasswordStrengthValidator : public ValidatorWithLabelOut
{
public:
    PasswordStrengthValidator(wxStaticText *msgLabel, wxString *val = nullptr)
        : ValidatorWithLabelOut(msgLabel, val) {}
    PasswordStrengthValidator(const PasswordStrengthValidator &validator)
        : ValidatorWithLabelOut(validator) {}

    virtual wxObject *Clone() const override { return new PasswordStrengthValidator(*this); }

    const unsigned MinLength = 10;

private:
    std::pair<bool, wxString> CheckValidity(const wxString &str) const override
    {
        wxString error = "";

        auto s = str.ToStdString();

        bool hasLetter = std::any_of(std::begin(s), std::end(s), [](unsigned char c)
                                     { return std::isalpha(c); });
        bool hasDigit = std::any_of(std::begin(s), std::end(s), [](unsigned char c)
                                    { return std::isdigit(c); });

        if (!hasLetter || !hasDigit)
        {
            return {false, "Password must contain letters and numbers."};
        }
        else if (str.length() < MinLength)
        {
            return {false, wxString::Format("Minimum password length is %d.", MinLength)};
        }
        else
        {
            return {true, "Strong password."};
        }
    }
};