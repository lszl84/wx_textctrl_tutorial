#include <wx/wx.h>
#include <vector>
#include <iostream>

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};
class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
    virtual ~MyFrame() {}

private:
    void SetupMenuBar();
    void SetupForm();

    wxTextCtrl *userNameField, *emailField, *passwordField, *passwordRepeatField, *notesField;

    wxStaticText *passwordHint, *passwordRepeatHint;

    wxString name, email, password, notes;

    void OnSubmit(wxCommandEvent &);
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("Hello World", wxDefaultPosition, wxDefaultSize);
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");
    SetupMenuBar();

    SetupForm();
}

void MyFrame::SetupMenuBar()
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(wxID_EXIT);

    wxMenu *editMenu = new wxMenu();
    editMenu->Append(wxID_COPY);
    editMenu->Append(wxID_CUT);
    editMenu->Append(wxID_PASTE);

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar *menuBar = new wxMenuBar;

    menuBar->Append(menuFile, "&File");
    menuBar->Append(editMenu, "Edit");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);
}

void MyFrame::SetupForm()
{
    auto sizer = new wxBoxSizer(wxVERTICAL);
    auto centeringSizer = new wxBoxSizer(wxHORIZONTAL);

    auto panel = new wxPanel(this);
    auto panelSizer = new wxBoxSizer(wxVERTICAL);

    // fix for Windows
    SetBackgroundColour(panel->GetBackgroundColour());

    auto nameLabel = new wxStaticText(panel, wxID_ANY, "Full Name:");
    userNameField = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(FromDIP(300), wxDefaultSize.GetHeight()));

    auto emailLabel = new wxStaticText(panel, wxID_ANY, "Email:");
    emailField = new wxTextCtrl(panel, wxID_ANY);

    auto passwordLabel = new wxStaticText(panel, wxID_ANY, "Password:");
    passwordField = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);

    passwordHint = new wxStaticText(panel, wxID_ANY, "Password must contain letters and numbers.");
    passwordHint->SetFont(wxFont(wxNORMAL_FONT->GetPointSize() - 2, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    auto passwordRepeatLabel = new wxStaticText(panel, wxID_ANY, "Repeat Password:");
    passwordRepeatField = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);

    passwordRepeatHint = new wxStaticText(panel, wxID_ANY, "");
    passwordRepeatHint->SetFont(passwordHint->GetFont());

    auto notesLabel = new wxStaticText(panel, wxID_ANY, "How did you learn about us?");
    notesField = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition,
                                wxSize(wxDefaultSize.GetWidth(), FromDIP(150)), wxTE_MULTILINE);

    auto submitButton = new wxButton(panel, wxID_ANY, "Submit");

    std::vector<wxWindow *> formItems{
        nameLabel,
        userNameField,
        emailLabel,
        emailField,
        passwordLabel,
        passwordField,
        passwordHint,
        passwordRepeatLabel,
        passwordRepeatField,
        passwordRepeatHint,
        notesLabel,
        notesField,
        submitButton};

    for (auto item : formItems)
    {
        panelSizer->Add(item, 0, wxEXPAND | wxALL, FromDIP(3));
    }

    panel->SetSizerAndFit(panelSizer);

    centeringSizer->Add(panel, 1, wxALIGN_CENTER | wxALL, FromDIP(10));
    sizer->Add(centeringSizer, 1, wxEXPAND);

    SetSizerAndFit(sizer);

    submitButton->Bind(wxEVT_BUTTON, &MyFrame::OnSubmit, this);

    userNameField->SetValidator(wxTextValidator(wxFILTER_NONE, &name));
    emailField->SetValidator(wxTextValidator(wxFILTER_NONE, &email));
    passwordField->SetValidator(wxTextValidator(wxFILTER_NONE, &password));
    passwordRepeatField->SetValidator(wxTextValidator(wxFILTER_NONE));
    notesField->SetValidator(wxTextValidator(wxFILTER_NONE, &notes));

    name = "John Doe";
    TransferDataToWindow();
}

void MyFrame::OnSubmit(wxCommandEvent &e)
{
    TransferDataFromWindow();

    if (name.Length() == 0 || email.Length() == 0 || password.Length() == 0)
    {
        wxMessageBox("Please fill in the empty fields.", "Error", wxICON_ERROR);
    }
    else if (!Validate())
    {
        wxMessageBox("There were errors. Check the form and try again.", "Error", wxICON_ERROR);
    }
    else
    {
        std::cout << name << std::endl
                  << email << std::endl
                  << password << std::endl
                  << notes << std::endl;
    }
}