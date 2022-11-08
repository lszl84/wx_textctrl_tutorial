#include <wx/wx.h>
#include <vector>

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
    auto centeringSizer = new wxBoxSizer(wxHORIZONTAL);

    auto panel = new wxPanel(this);
    auto panelSizer = new wxBoxSizer(wxVERTICAL);

    auto nameLabel = new wxStaticText(panel, wxID_ANY, "Full Name:");
    userNameField = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(FromDIP(300), wxDefaultSize.GetHeight()));

    auto emailLabel = new wxStaticText(panel, wxID_ANY, "Email:");
    emailField = new wxTextCtrl(panel, wxID_ANY);

    std::vector<wxWindow *> formItems{
        nameLabel,
        userNameField,
        emailLabel,
        emailField};

    for (auto item : formItems)
    {
        panelSizer->Add(item, 0, wxEXPAND | wxALL, FromDIP(3));
    }

    panel->SetSizerAndFit(panelSizer);

    centeringSizer->Add(panel, 1, wxALIGN_CENTER | wxALL, FromDIP(10));
    sizer->Add(centeringSizer, 1, wxEXPAND);

    SetSizerAndFit(sizer);
}