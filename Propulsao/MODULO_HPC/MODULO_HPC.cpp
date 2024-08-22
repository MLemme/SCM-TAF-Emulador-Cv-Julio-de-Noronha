//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("MODULO_HPC.res");
USEFORM("Principal.cpp", frmPrincipal);
USEFORM("CtrlPasso.cpp", frmCtrlPasso);
USEFORM("CtrlPress.cpp", frmCtrlParamAuto);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "V32 - H�LICE PASSO CONTROLAV�L";
                 Application->CreateForm(__classid(TfrmPrincipal), &frmPrincipal);
                 Application->CreateForm(__classid(TfrmCtrlPasso), &frmCtrlPasso);
                 Application->CreateForm(__classid(TfrmCtrlParamAuto), &frmCtrlParamAuto);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
