
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("Emulador_MR.res");
USEFORM("Principal.cpp", frmPrincipal);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "V32 - JÚLIO DE NORONHA - MR";
                 Application->CreateForm(__classid(TfrmPrincipal), &frmPrincipal);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
