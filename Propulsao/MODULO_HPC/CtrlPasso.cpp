//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Principal.h"
#include "CtrlPasso.h"

extern float PASSO_BE_DIF_AV_1;
extern float PASSO_BE_INC_AV_1;
extern float PASSO_BE_DIF_AV_2;
extern float PASSO_BE_INC_AV_2;
extern float PASSO_BE_DIF_AV_3;
extern float PASSO_BE_INC_AV_3;

extern float PASSO_BE_DIF_AR_1;
extern float PASSO_BE_INC_AR_1;
extern float PASSO_BE_DIF_AR_2;
extern float PASSO_BE_INC_AR_2;
extern float PASSO_BE_DIF_AR_3;
extern float PASSO_BE_INC_AR_3;

extern float PASSO_BB_DIF_AV_1;
extern float PASSO_BB_INC_AV_1;
extern float PASSO_BB_DIF_AV_2;
extern float PASSO_BB_INC_AV_2;
extern float PASSO_BB_DIF_AV_3;
extern float PASSO_BB_INC_AV_3;

extern float PASSO_BB_DIF_AR_1;
extern float PASSO_BB_INC_AR_1;
extern float PASSO_BB_DIF_AR_2;
extern float PASSO_BB_INC_AR_2;
extern float PASSO_BB_DIF_AR_3;
extern float PASSO_BB_INC_AR_3;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmCtrlPasso *frmCtrlPasso;
//---------------------------------------------------------------------------
__fastcall TfrmCtrlPasso::TfrmCtrlPasso(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfrmCtrlPasso::btnAjustar_BBClick(TObject *Sender)
{
        PASSO_BB_DIF_AV_1 = txtPASSO_BB_DIF_AV_1->Text.ToDouble();
        PASSO_BB_DIF_AV_2 = txtPASSO_BB_DIF_AV_2->Text.ToDouble();
        PASSO_BB_DIF_AV_3 = txtPASSO_BB_DIF_AV_3->Text.ToDouble();

        PASSO_BB_INC_AV_1 = txtPASSO_BB_INC_AV_1->Text.ToDouble();
        PASSO_BB_INC_AV_2 = txtPASSO_BB_INC_AV_2->Text.ToDouble();
        PASSO_BB_INC_AV_3 = txtPASSO_BB_INC_AV_3->Text.ToDouble();

        PASSO_BB_DIF_AR_1 = txtPASSO_BB_DIF_AR_1->Text.ToDouble();
        PASSO_BB_DIF_AR_2 = txtPASSO_BB_DIF_AR_2->Text.ToDouble();
        PASSO_BB_DIF_AR_3 = txtPASSO_BB_DIF_AR_3->Text.ToDouble();

        PASSO_BB_INC_AR_1 = txtPASSO_BB_INC_AR_1->Text.ToDouble();
        PASSO_BB_INC_AR_2 = txtPASSO_BB_INC_AR_2->Text.ToDouble();
        PASSO_BB_INC_AR_3 = txtPASSO_BB_INC_AR_3->Text.ToDouble();

        frmPrincipal->tmrPassoBB->Interval =  txtTempoBB->Text.ToInt();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCtrlPasso::btnValoresOriginais_BBClick(TObject *Sender)
{

        PASSO_BB_DIF_AV_1 = 5;
        txtPASSO_BB_DIF_AV_1->Text = 5;
        PASSO_BB_DIF_AV_2 = 1;
        txtPASSO_BB_DIF_AV_2->Text = 1;
        PASSO_BB_DIF_AV_3 = 0.01;
        txtPASSO_BB_DIF_AV_3->Text = 0.01;

        PASSO_BB_INC_AV_1 = 4;
        txtPASSO_BB_INC_AV_1->Text = 4;
        PASSO_BB_INC_AV_2 = 2;
        txtPASSO_BB_INC_AV_2->Text = 2;
        PASSO_BB_INC_AV_3 = 0.5;
        txtPASSO_BB_INC_AV_3->Text = 0.5;

        PASSO_BB_DIF_AR_1 = 5;
        txtPASSO_BB_DIF_AR_1->Text = 5;
        PASSO_BB_DIF_AR_2 = 1;
        txtPASSO_BB_DIF_AR_2->Text = 1;
        PASSO_BB_DIF_AR_3 = 0.01;
        txtPASSO_BB_DIF_AR_3->Text = 0.01;

        PASSO_BB_INC_AR_1 = 4;
        txtPASSO_BB_INC_AR_1->Text = 4;
        PASSO_BB_INC_AR_2 = 2;
        txtPASSO_BB_INC_AR_2->Text = 2;
        PASSO_BB_INC_AR_3 = 0.5;
        txtPASSO_BB_INC_AR_3->Text = 0.5;

        frmPrincipal->tmrPassoBB->Interval =  150;
        txtTempoBB->Text = 150;

}
//---------------------------------------------------------------------------
void __fastcall TfrmCtrlPasso::btnAjustar_BEClick(TObject *Sender)
{
        PASSO_BE_DIF_AV_1 = txtPASSO_BE_DIF_AV_1->Text.ToDouble();
        PASSO_BE_DIF_AV_2 = txtPASSO_BE_DIF_AV_2->Text.ToDouble();
        PASSO_BE_DIF_AV_3 = txtPASSO_BE_DIF_AV_3->Text.ToDouble();

        PASSO_BE_INC_AV_1 = txtPASSO_BE_INC_AV_1->Text.ToDouble();
        PASSO_BE_INC_AV_2 = txtPASSO_BE_INC_AV_2->Text.ToDouble();
        PASSO_BE_INC_AV_3 = txtPASSO_BE_INC_AV_3->Text.ToDouble();

        PASSO_BE_DIF_AR_1 = txtPASSO_BE_DIF_AR_1->Text.ToDouble();
        PASSO_BE_DIF_AR_2 = txtPASSO_BE_DIF_AR_2->Text.ToDouble();
        PASSO_BE_DIF_AR_3 = txtPASSO_BE_DIF_AR_3->Text.ToDouble();

        PASSO_BE_INC_AR_1 = txtPASSO_BE_INC_AR_1->Text.ToDouble();
        PASSO_BE_INC_AR_2 = txtPASSO_BE_INC_AR_2->Text.ToDouble();
        PASSO_BE_INC_AR_3 = txtPASSO_BE_INC_AR_3->Text.ToDouble();

        frmPrincipal->tmrPassoBE->Interval =  txtTempoBE->Text.ToInt();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCtrlPasso::btnValoresOriginais_BEClick(TObject *Sender)
{
        PASSO_BE_DIF_AV_1 = 5;
        txtPASSO_BE_DIF_AV_1->Text = 5;
        PASSO_BE_DIF_AV_2 = 1;
        txtPASSO_BE_DIF_AV_2->Text = 1;
        PASSO_BE_DIF_AV_3 = 0.01;
        txtPASSO_BE_DIF_AV_3->Text = 0.01;

        PASSO_BE_INC_AV_1 = 4;
        txtPASSO_BE_INC_AV_1->Text = 4;
        PASSO_BE_INC_AV_2 = 2;
        txtPASSO_BE_INC_AV_2->Text = 2;
        PASSO_BE_INC_AV_3 = 0.5;
        txtPASSO_BE_INC_AV_3->Text = 0.5;

        PASSO_BE_DIF_AR_1 = 5;
        txtPASSO_BE_DIF_AR_1->Text = 5;
        PASSO_BE_DIF_AR_2 = 1;
        txtPASSO_BE_DIF_AR_2->Text = 1;
        PASSO_BE_DIF_AR_3 = 0.01;
        txtPASSO_BE_DIF_AR_3->Text = 0.01;

        PASSO_BE_INC_AR_1 = 4;
        txtPASSO_BE_INC_AR_1->Text = 4;
        PASSO_BE_INC_AR_2 = 2;
        txtPASSO_BE_INC_AR_2->Text = 2;
        PASSO_BE_INC_AR_3 = 0.5;
        txtPASSO_BE_INC_AR_3->Text = 0.5;

        frmPrincipal->tmrPassoBE->Interval =  150;
        txtTempoBE->Text = 150;        
}
//---------------------------------------------------------------------------
void __fastcall TfrmCtrlPasso::btnFecharClick(TObject *Sender)
{
        frmCtrlPasso->Close();
}
//---------------------------------------------------------------------------

