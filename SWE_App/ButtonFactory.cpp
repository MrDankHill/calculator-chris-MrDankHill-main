#include "ButtonFactory.h"

wxButton* ButtonFactory::CreateNumberButton(wxPanel* parent, int number) 
{
    return new wxButton(parent, wxID_ANY, std::to_string(number), wxDefaultPosition, wxSize(50, 50));
}

wxButton* ButtonFactory::CreateAddButton(wxPanel* parent) 
{
    return new wxButton(parent, wxID_ANY, "+", wxDefaultPosition, wxSize(50, 50));
}

wxButton* ButtonFactory::CreateSubtractButton(wxPanel* parent)
{
    return new wxButton(parent, wxID_ANY, "-", wxDefaultPosition, wxSize(50, 50));
}

wxButton* ButtonFactory::CreateMultiplyButton(wxPanel* parent) 
{
    return new wxButton(parent, wxID_ANY, "*", wxDefaultPosition, wxSize(50, 50));
}

wxButton* ButtonFactory::CreateDivideButton(wxPanel* parent) 
{
    return new wxButton(parent, wxID_ANY, "/", wxDefaultPosition, wxSize(50, 50));
}

wxButton* ButtonFactory::CreateModuloButton(wxPanel* parent) 
{
    return new wxButton(parent, wxID_ANY, "%", wxDefaultPosition, wxSize(50, 50));
}

wxButton* ButtonFactory::CreateEqualButton(wxPanel* parent) 
{
    return new wxButton(parent, wxID_ANY, "=", wxDefaultPosition, wxSize(50, 50));
}

wxButton* ButtonFactory::CreateClearButton(wxPanel* parent) 
{
    return new wxButton(parent, wxID_ANY, "C", wxDefaultPosition, wxSize(50, 50));
}

wxButton* ButtonFactory::CreateBackspaceButton(wxPanel* parent)
{
    return new wxButton(parent, wxID_ANY, "?", wxDefaultPosition, wxSize(50, 50));
}

wxButton* ButtonFactory::CreateDecimalButton(wxPanel* parent)
{
    return new wxButton(parent, wxID_ANY, ".", wxDefaultPosition, wxSize(50, 50));
}

wxButton* ButtonFactory::CreateNegativeButton(wxPanel* parent) 
{
    return new wxButton(parent, wxID_ANY, "+/-", wxDefaultPosition, wxSize(50, 50));
}

// New methods for trigonometric buttons
wxButton* ButtonFactory::CreateSinButton(wxPanel* parent)
{
    return new wxButton(parent, wxID_ANY, "sin", wxDefaultPosition, wxSize(50, 50));
}

wxButton* ButtonFactory::CreateCosButton(wxPanel* parent) 
{
    return new wxButton(parent, wxID_ANY, "cos", wxDefaultPosition, wxSize(50, 50));
}

wxButton* ButtonFactory::CreateTanButton(wxPanel* parent)
{
    return new wxButton(parent, wxID_ANY, "tan", wxDefaultPosition, wxSize(50, 50));
}
