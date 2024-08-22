//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("MODULO_MCP_BB.res");
USEFORM("Principal.cpp", frmPrincipal);
USEFORM("Analogicas.cpp", frmAnalogicas);
USEFORM("Controles.cpp", frmControles);
USEFORM("BBAELPN.cpp", frmBBAELPN);
USEFORM("ControleNovo.cpp", frmControlesNovo);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "V32 - MOTOR DE COMBUSTÃO PRINCIPAL - MCP BB";
                 Application->CreateForm(__classid(TfrmPrincipal), &frmPrincipal);
                 Application->CreateForm(__classid(TfrmAnalogicas), &frmAnalogicas);
                 Application->CreateForm(__classid(TfrmControles), &frmControles);
                 Application->CreateForm(__classid(TfrmBBAELPN), &frmBBAELPN);
                 Application->CreateForm(__classid(TfrmControlesNovo), &frmControlesNovo);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
