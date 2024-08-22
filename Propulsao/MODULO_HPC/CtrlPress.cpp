//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CtrlPress.h"
#include "Principal.h"

extern float vlr_press_auto_bb;
extern float vlr_press_auto_be;
extern float vlr_press_alar_bb;
extern float vlr_press_alar_be;
extern float vlr_press_atua_bb;
extern float vlr_press_atua_be;
extern float vlr_press_oper_bb;
extern float vlr_press_oper_be;
extern float valor_min_rpm_eixo_bb;
extern float valor_min_rpm_eixo_be;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmCtrlParamAuto *frmCtrlParamAuto;
//---------------------------------------------------------------------------
__fastcall TfrmCtrlParamAuto::TfrmCtrlParamAuto(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmCtrlParamAuto::FormShow(TObject *Sender)
{
        tmrAtualiza->Enabled = true;

        txtRotMin_BB->Text = valor_min_rpm_eixo_bb;
        txtPressMin_BB->Text = vlr_press_auto_bb;
        txtPressAlm_BB->Text = vlr_press_alar_bb;
        txtPressLib_BB->Text = vlr_press_atua_bb;
        txtPressOpe_BB->Text = vlr_press_oper_bb;

        txtRotMin_BE->Text = valor_min_rpm_eixo_be;
        txtPressMin_BE->Text = vlr_press_auto_be;
        txtPressAlm_BE->Text = vlr_press_alar_be;
        txtPressLib_BE->Text = vlr_press_atua_be;
        txtPressOpe_BE->Text = vlr_press_oper_be;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCtrlParamAuto::FormClose(TObject *Sender,
      TCloseAction &Action)
{
        tmrAtualiza->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCtrlParamAuto::tmrAtualizaTimer(TObject *Sender)
{
        lblRotMin_BB->Caption = valor_min_rpm_eixo_be;
        lblPressMin_BB->Caption = vlr_press_auto_be;
        lblPressAlm_BB->Caption = vlr_press_alar_be;
        lblPressLib_BB->Caption = vlr_press_atua_be;
        lblPressOpe_BB->Caption = vlr_press_oper_be;

        lblRotMin_BE->Caption = valor_min_rpm_eixo_be;
        lblPressMin_BE->Caption = vlr_press_auto_be;
        lblPressAlm_BE->Caption = vlr_press_alar_be;
        lblPressLib_BE->Caption = vlr_press_atua_be;
        lblPressOpe_BE->Caption = vlr_press_oper_be;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCtrlParamAuto::btnAlterarClick(TObject *Sender)
{
        valor_min_rpm_eixo_bb = txtRotMin_BB->Text.ToDouble();
        vlr_press_auto_bb = txtPressMin_BB->Text.ToDouble();
        vlr_press_alar_bb = txtPressAlm_BB->Text.ToDouble();
        vlr_press_atua_bb = txtPressLib_BB->Text.ToDouble();
        vlr_press_oper_bb = txtPressOpe_BB->Text.ToDouble();

        valor_min_rpm_eixo_be = txtRotMin_BE->Text.ToDouble();
        vlr_press_auto_be = txtPressMin_BE->Text.ToDouble();
        vlr_press_alar_be = txtPressAlm_BE->Text.ToDouble();
        vlr_press_atua_be = txtPressLib_BE->Text.ToDouble();
        vlr_press_oper_be = txtPressOpe_BE->Text.ToDouble();

}
//---------------------------------------------------------------------------
void __fastcall TfrmCtrlParamAuto::btnFECHARClick(TObject *Sender)
{
        frmCtrlParamAuto->Close();                
}
//---------------------------------------------------------------------------

