#include <wx/wx.h>

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

    wxTextCtrl *userNameField, *emailField;
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

    auto nameLabel = new wxStaticText(this, wxID_ANY, "Full Name:");
    userNameField = new wxTextCtrl(this, wxID_ANY);

    auto emailLabel = new wxStaticText(this, wxID_ANY, "Email:");
    emailField = new wxTextCtrl(this, wxID_ANY);

    sizer->Add(nameLabel);
    sizer->Add(userNameField);
    sizer->Add(emailLabel);
    sizer->Add(emailField);

    this->SetSizer(sizer);
}