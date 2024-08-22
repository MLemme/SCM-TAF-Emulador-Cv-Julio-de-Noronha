//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("MODULO_ER.res");
USEFORM("Principal.cpp", frmPrincipal);
USEFORM("Mancais.cpp", frmMancal);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "V32 - ENGRENAGEM REDUTORA";
                 Application->CreateForm(__classid(TfrmPrincipal), &frmPrincipal);
                 Application->CreateForm(__classid(TfrmMancal), &frmMancal);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
