//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("MODULO_COM_SERIAL_MCP.res");
USEFORM("Principal.cpp", frmPrincipal);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
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
