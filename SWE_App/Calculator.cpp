
#include "CalculatorProcessor.h"
#include "ButtonFactory.h"
#include <wx/wx.h>

class CalculatorFrame : public wxFrame 
{
public:
    CalculatorFrame(const wxString& title);

private:
    wxTextCtrl* display;
    wxString expression;

    void OnButtonClicked(wxCommandEvent& event);
    void OnEqualButtonClicked(wxCommandEvent& event);
    void OnClearButtonClicked(wxCommandEvent& event);
    void OnBackspaceButtonClicked(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(CalculatorFrame, wxFrame)
EVT_BUTTON(wxID_ANY, CalculatorFrame::OnButtonClicked)
wxEND_EVENT_TABLE()

CalculatorFrame::CalculatorFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(300, 500)) 
{
    wxPanel* panel = new wxPanel(this, wxID_ANY);
    display = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(-1, -1), wxSize(280, 50), wxTE_RIGHT);

    wxGridSizer* gridSizer = new wxGridSizer(6, 4, 5, 5);

    // Number Buttons 0-9
    for (int i = 0; i <= 9; ++i) 
    {
        gridSizer->Add(ButtonFactory::CreateNumberButton(panel, i));
    }

    // Decimal point button
    gridSizer->Add(ButtonFactory::CreateDecimalButton(panel));

    // Binary Operation Buttons
    gridSizer->Add(ButtonFactory::CreateAddButton(panel));
    gridSizer->Add(ButtonFactory::CreateSubtractButton(panel));
    gridSizer->Add(ButtonFactory::CreateMultiplyButton(panel));
    gridSizer->Add(ButtonFactory::CreateDivideButton(panel));
    gridSizer->Add(ButtonFactory::CreateModuloButton(panel));

    // Trigonometric Buttons
    gridSizer->Add(ButtonFactory::CreateSinButton(panel));
    gridSizer->Add(ButtonFactory::CreateCosButton(panel));
    gridSizer->Add(ButtonFactory::CreateTanButton(panel));

    // Special Buttons
    wxButton* equalButton = ButtonFactory::CreateEqualButton(panel);  // Equals
    gridSizer->Add(equalButton);
    gridSizer->Add(ButtonFactory::CreateClearButton(panel));  // Clear
    gridSizer->Add(ButtonFactory::CreateBackspaceButton(panel));  // Backspace
    gridSizer->Add(ButtonFactory::CreateNegativeButton(panel));  // Negative

    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
    vbox->Add(display, 0, wxEXPAND | wxALL, 10);
    vbox->Add(gridSizer, 1, wxEXPAND | wxALL, 10);

    panel->SetSizer(vbox);

    // Bind the equals button to the OnEqualButtonClicked event handler
    Bind(wxEVT_BUTTON, &CalculatorFrame::OnEqualButtonClicked, this, equalButton->GetId());

}

void CalculatorFrame::OnButtonClicked(wxCommandEvent& event) 
{
    wxButton* button = dynamic_cast<wxButton*>(event.GetEventObject());
    if (button) {
        // Trying to fix "C" (Clear) always showinf in next formula
        if (button->GetLabel() != "C") 
        {
            expression += button->GetLabel();
            display->SetValue(expression);  // Update the display with the current expression
        }
    }
}

void CalculatorFrame::OnEqualButtonClicked(wxCommandEvent& event) 
{
    try 
    {
        double result = CalculatorProcessor::GetInstance()->Calculate(std::string(expression.mb_str()));
        display->SetValue(wxString::Format("%f", result));
        expression.clear();
    }
    catch (std::runtime_error& e) 
    {
        wxMessageBox("Error in calculation!", "Error", wxICON_ERROR);
    }
}

void CalculatorFrame::OnClearButtonClicked(wxCommandEvent& event) 
{
    expression.clear();
    display->Clear();
}

void CalculatorFrame::OnBackspaceButtonClicked(wxCommandEvent& event) 
{
    if (!expression.IsEmpty()) 
    {
        expression.RemoveLast();
        display->SetValue(expression);
    }
}

class CalculatorApp : public wxApp 
{
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(CalculatorApp);

bool CalculatorApp::OnInit()
{
    CalculatorFrame* frame = new CalculatorFrame("Calculator");
    frame->Show(true);
    return true;
}
