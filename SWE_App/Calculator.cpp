#include <wx/wx.h>
#include <wx/grid.h>
#include <stack>
#include <cmath>
#include <stdexcept>
#include <wx/tokenzr.h>

class CalculatorApp : public wxApp
{
public:
    virtual bool OnInit();
};

class CalculatorFrame : public wxFrame
{
public:
    CalculatorFrame(const wxString& title);

private:
    wxTextCtrl* display;

    // Event handlers
    void OnButtonClicked(wxCommandEvent& event);
    void OnEqualButtonClicked(wxCommandEvent& event);
    void OnClearButtonClicked(wxCommandEvent& event);
    void OnBackspaceButtonClicked(wxCommandEvent& event);
    void OnNegativeButtonClicked(wxCommandEvent& event);

    void EvaluateExpression();
    bool HasPrecedence(const wxString& op1, const wxString& op2);
    double ApplyOperation(const wxString& op, double left, double right);

    wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(CalculatorFrame, wxFrame)
// Numbers
EVT_BUTTON(1000, CalculatorFrame::OnButtonClicked)
EVT_BUTTON(1001, CalculatorFrame::OnButtonClicked)
EVT_BUTTON(1002, CalculatorFrame::OnButtonClicked)
EVT_BUTTON(1003, CalculatorFrame::OnButtonClicked)
EVT_BUTTON(1004, CalculatorFrame::OnButtonClicked)
EVT_BUTTON(1005, CalculatorFrame::OnButtonClicked)
EVT_BUTTON(1006, CalculatorFrame::OnButtonClicked)
EVT_BUTTON(1007, CalculatorFrame::OnButtonClicked)
EVT_BUTTON(1008, CalculatorFrame::OnButtonClicked)
EVT_BUTTON(1009, CalculatorFrame::OnButtonClicked)

// Decimal and Operations
EVT_BUTTON(1010, CalculatorFrame::OnButtonClicked)  // Decimal
EVT_BUTTON(1011, CalculatorFrame::OnButtonClicked)  // Addition
EVT_BUTTON(1012, CalculatorFrame::OnButtonClicked)  // Subtraction
EVT_BUTTON(1013, CalculatorFrame::OnButtonClicked)  // Multiplication
EVT_BUTTON(1014, CalculatorFrame::OnButtonClicked)  // Division
EVT_BUTTON(1017, CalculatorFrame::OnButtonClicked)  // Modulo %

// Unary Operators (sin, cos, tan)
EVT_BUTTON(1018, CalculatorFrame::OnButtonClicked)  // sin
EVT_BUTTON(1019, CalculatorFrame::OnButtonClicked)  // cos
EVT_BUTTON(1020, CalculatorFrame::OnButtonClicked)  // tan

// Equals, Clear, Backspace, Negative
EVT_BUTTON(1015, CalculatorFrame::OnEqualButtonClicked)  // Equals
EVT_BUTTON(1016, CalculatorFrame::OnClearButtonClicked)  // Clear
EVT_BUTTON(1021, CalculatorFrame::OnBackspaceButtonClicked)  // Backspace
EVT_BUTTON(1022, CalculatorFrame::OnNegativeButtonClicked)  // Negative
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(CalculatorApp);

bool CalculatorApp::OnInit()
{
    CalculatorFrame* frame = new CalculatorFrame(wxT("Calculator"));
    frame->Show(true);
    return true;
}

CalculatorFrame::CalculatorFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(300, 500))
{
    wxPanel* panel = new wxPanel(this, wxID_ANY);
    display = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(-1, -1), wxSize(280, 50), wxTE_RIGHT);

    wxGridSizer* gridSizer = new wxGridSizer(6, 4, 5, 5);  // 6 rows, 4 columns

    // Number Buttons 0-9
    for (int i = 1; i <= 9; ++i)
    {
        gridSizer->Add(new wxButton(panel, 1000 + i, wxString::Format(wxT("%d"), i)));
    }
    gridSizer->Add(new wxButton(panel, 1000 + 0, "0"));
    gridSizer->Add(new wxButton(panel, 1010, "."));  // Decimal point

    // Binary Operation Buttons
    gridSizer->Add(new wxButton(panel, 1011, "+"));
    gridSizer->Add(new wxButton(panel, 1012, "-"));
    gridSizer->Add(new wxButton(panel, 1013, "*"));
    gridSizer->Add(new wxButton(panel, 1014, "/"));
    gridSizer->Add(new wxButton(panel, 1017, "%"));  // Modulo

    // Unary Operation Buttons
    gridSizer->Add(new wxButton(panel, 1018, "sin"));
    gridSizer->Add(new wxButton(panel, 1019, "cos"));
    gridSizer->Add(new wxButton(panel, 1020, "tan"));

    // Special Buttons
    gridSizer->Add(new wxButton(panel, 1015, "="));  // Equals
    gridSizer->Add(new wxButton(panel, 1016, "C"));  // Clear
    gridSizer->Add(new wxButton(panel, 1021, "<-"));  // Backspace
    gridSizer->Add(new wxButton(panel, 1022, "-/+"));  // Negative

    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
    vbox->Add(display, 0, wxEXPAND | wxALL, 10);
    vbox->Add(gridSizer, 1, wxEXPAND | wxALL, 10);

    panel->SetSizer(vbox);
}

void CalculatorFrame::OnButtonClicked(wxCommandEvent& event)
{
    wxString label = ((wxButton*)event.GetEventObject())->GetLabel();
    display->AppendText(label);  // Append the button text to the display
}

void CalculatorFrame::OnEqualButtonClicked(wxCommandEvent& event)
{
    EvaluateExpression();
}

void CalculatorFrame::OnClearButtonClicked(wxCommandEvent& event)
{
    display->Clear();
}

void CalculatorFrame::OnBackspaceButtonClicked(wxCommandEvent& event)
{
    wxString currentText = display->GetValue();
    if (!currentText.IsEmpty())
    {
        currentText.RemoveLast();
        display->SetValue(currentText);
    }
}

void CalculatorFrame::OnNegativeButtonClicked(wxCommandEvent& event)
{
    wxString currentText = display->GetValue();
    if (!currentText.IsEmpty())
    {
        if (currentText.StartsWith("-"))
        {
            currentText.Remove(0, 1);  // Remove negative sign
        }
        else
        {
            currentText.Prepend("-");
        }
        display->SetValue(currentText);
    }
}

void CalculatorFrame::EvaluateExpression()
{
    wxString expression = display->GetValue();
    std::stack<double> values;
    std::stack<wxString> operators;

    wxString number;
    for (size_t i = 0; i < expression.Length(); ++i)
    {
        wxChar c = expression[i];

        if (wxIsdigit(c) || c == '.')
        {
            number += c;
        }
        else
        {
            if (!number.IsEmpty())
            {
                double value;
                if (number.ToDouble(&value))
                {
                    values.push(value);
                }
                number.Clear();
            }

            wxString op(1, c);
            if (op == "+" || op == "-" || op == "*" || op == "/" || op == "%")
            {
                while (!operators.empty() && HasPrecedence(op, operators.top()))
                {
                    if (values.size() < 2)
                    {
                        display->SetValue("Error");
                        return;
                    }
                    double right = values.top(); values.pop();
                    double left = values.top(); values.pop();
                    wxString operatorTop = operators.top(); operators.pop();
                    values.push(ApplyOperation(operatorTop, left, right));
                }
                operators.push(op);
            }
        }
    }

    if (!number.IsEmpty())
    {
        double value;
        if (number.ToDouble(&value))
        {
            values.push(value);
        }
    }

    while (!operators.empty())
    {
        if (values.size() < 2)
        {
            display->SetValue("Error");
            return;
        }
        double right = values.top(); values.pop();
        double left = values.top(); values.pop();
        wxString op = operators.top(); operators.pop();
        values.push(ApplyOperation(op, left, right));
    }

    if (!values.empty())
    {
        display->SetValue(wxString::Format("%f", values.top()));
    }
    else
    {
        display->SetValue("Error");
    }
}

bool CalculatorFrame::HasPrecedence(const wxString& op1, const wxString& op2)
{
    if ((op1 == "*" || op1 == "/" || op1 == "%") && (op2 == "+" || op2 == "-"))
        return false;
    return true;
}

double CalculatorFrame::ApplyOperation(const wxString& op, double left, double right)
{
    if (op == "+") return left + right;
    if (op == "-") return left - right;
    if (op == "*") return left * right;
    if (op == "/")
    {
        if (right == 0) throw std::runtime_error("Division by zero");
        return left / right;
    }
    if (op == "%")
    {
        if (right == 0) throw std::runtime_error("Division by zero");
        return std::fmod(left, right);  // Use fmod for floating point modulo
    }
    throw std::runtime_error("Unknown operator");
}
