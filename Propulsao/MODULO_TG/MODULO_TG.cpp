
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("MODULO_TG.res");
USEFORM("Principal.cpp", frmPrincipal);
USEFORM("Permissivos.cpp", frmPermissivos);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "V32 - TURBINA À GÁS - TG";
                 Application->CreateForm(__classid(TfrmPrincipal), &frmPrincipal);
                 Application->CreateForm(__classid(TfrmPermissivos), &frmPermissivos);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
