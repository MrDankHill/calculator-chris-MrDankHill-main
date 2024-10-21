#ifndef BUTTON_FACTORY_H
#define BUTTON_FACTORY_H

#include <wx/wx.h>

class ButtonFactory 
{
public:
    static wxButton* CreateNumberButton(wxPanel* parent, int number);
    static wxButton* CreateAddButton(wxPanel* parent);
    static wxButton* CreateSubtractButton(wxPanel* parent);
    static wxButton* CreateMultiplyButton(wxPanel* parent);
    static wxButton* CreateDivideButton(wxPanel* parent);
    static wxButton* CreateModuloButton(wxPanel* parent);
    static wxButton* CreateEqualButton(wxPanel* parent);
    static wxButton* CreateClearButton(wxPanel* parent);
    static wxButton* CreateBackspaceButton(wxPanel* parent);
    static wxButton* CreateDecimalButton(wxPanel* parent);
    static wxButton* CreateNegativeButton(wxPanel* parent);

    // New methods for trigonometric buttons
    static wxButton* CreateSinButton(wxPanel* parent);
    static wxButton* CreateCosButton(wxPanel* parent);
    static wxButton* CreateTanButton(wxPanel* parent);
};

#endif
