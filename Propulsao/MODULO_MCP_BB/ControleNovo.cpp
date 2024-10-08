//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ControleNovo.h"
#include "Principal.h"
#include "ModBusDriverLib\TModBusTCPDriver.cpp"

extern float  X_LOAD_1;
extern float  Y_LOAD_1;
extern float  X_LOAD_2;
extern float  Y_LOAD_2;
extern float  X_LOAD_3;
extern float  Y_LOAD_3;
extern float  X_LOAD_4;
extern float  Y_LOAD_4;
extern float  CARGA;
extern float  CREMALHEIRA;
extern float  MCR;
extern String PC_SA_ECS_CARGA;
extern String PC_HA_RTU_CARGAMCP;
extern String PC_SA_ECS_POSICREMALPRINC;
extern String PC_SA_ECS_POSICREMALSEC;
extern String PC_SA_ECS_COMBCREMALPOS;
extern String PC_HA_RTU_POSICREMAL;
extern String PC_SA_ECS_MCRATUAL;
extern TModBusTCPDriver CLP;

extern float  CARGA_RPM_1;
extern float  CARGA1_RPM1;
extern float  CARGA2_RPM1;
extern float  CARGA3_RPM1;
extern float  CARGA4_RPM1;
extern float  CGMCR1_RPM1;
extern float  CGMCR2_RPM1;
extern float  CGMCR3_RPM1;
extern float  CGMCR4_RPM1;

extern float  CARGA_RPM_2;
extern float  CARGA1_RPM2;
extern float  CARGA2_RPM2;
extern float  CARGA3_RPM2;
extern float  CARGA4_RPM2;
extern float  CGMCR1_RPM2;
extern float  CGMCR2_RPM2;
extern float  CGMCR3_RPM2;
extern float  CGMCR4_RPM2;

extern float  CARGA_RPM_3;
extern float  CARGA1_RPM3;
extern float  CARGA2_RPM3;
extern float  CARGA3_RPM3;
extern float  CARGA4_RPM3;
extern float  CGMCR1_RPM3;
extern float  CGMCR2_RPM3;
extern float  CGMCR3_RPM3;
extern float  CGMCR4_RPM3;

extern float  CARGA_PAS_1;
extern float  CARGA_PAS_2;
extern float  CARGA_PAS_3;
extern float  CARGA_PAS_4;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmControlesNovo *frmControlesNovo;
//---------------------------------------------------------------------------
__fastcall TfrmControlesNovo::TfrmControlesNovo(TComponent* Owner)
        : TForm(Owner)
{
        String tmplbl = "";

        chtBaixaRotacao->OpenDataEx(COD_VALUES,3,4);
        chtBaixaRotacao->ThisSerie = 0;
        chtBaixaRotacao->Value[0] = CARGA1_RPM1;
        chtBaixaRotacao->Value[1] = CARGA2_RPM1;
        chtBaixaRotacao->Value[2] = CARGA3_RPM1;
        chtBaixaRotacao->Value[3] = CARGA4_RPM1;

        tmplbl = CARGA_RPM_1;
        chtBaixaRotacao->SerLeg[0] = tmplbl;

        chtBaixaRotacao->ThisSerie = 1;
        chtBaixaRotacao->Value[0] = CARGA1_RPM2;
        chtBaixaRotacao->Value[1] = CARGA2_RPM2;
        chtBaixaRotacao->Value[2] = CARGA3_RPM2;
        chtBaixaRotacao->Value[3] = CARGA4_RPM2;

        tmplbl = CARGA_RPM_2;
        chtBaixaRotacao->SerLeg[1] = tmplbl;

        chtBaixaRotacao->ThisSerie = 2;
        chtBaixaRotacao->Value[0] = CARGA1_RPM3;
        chtBaixaRotacao->Value[1] = CARGA2_RPM3;
        chtBaixaRotacao->Value[2] = CARGA3_RPM3;
        chtBaixaRotacao->Value[3] = CARGA4_RPM3;

        tmplbl = CARGA_RPM_3;
        chtBaixaRotacao->SerLeg[2] = tmplbl;

        chtBaixaRotacao->CloseData(COD_VALUES);

        chtBaixaRotacao->Legend[0] = (String) CARGA_PAS_1;
        chtBaixaRotacao->Legend[1] = (String) CARGA_PAS_2;
        chtBaixaRotacao->Legend[2] = (String) CARGA_PAS_3;
        chtBaixaRotacao->Legend[3] = (String) CARGA_PAS_4;

        chtBaixaRotacao->Title[CHART_LEFTTIT] = "Carga";
        chtBaixaRotacao->Title[CHART_BOTTOMTIT] = "Passo";

        chtBaixaRotacao->Chart3D = false;

        cht1400->OpenDataEx(COD_VALUES,1,4);
        cht1400->ThisSerie = 0;
        cht1400->Value[0] = X_LOAD_1;
        cht1400->Value[1] = X_LOAD_2;
        cht1400->Value[2] = X_LOAD_3;
        cht1400->Value[3] = X_LOAD_4;

        cht1400->SerLeg[0] = "1400+";

        cht1400->CloseData(COD_VALUES);

        cht1400->Legend[0] = (String) Y_LOAD_1;
        cht1400->Legend[1] = (String) Y_LOAD_2;
        cht1400->Legend[2] = (String) Y_LOAD_3;
        cht1400->Legend[3] = (String) Y_LOAD_4;

        cht1400->Title[CHART_LEFTTIT] = "Carga";
        cht1400->Title[CHART_BOTTOMTIT] = "Passo";

        cht1400->Chart3D = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmControlesNovo::Button1Click(TObject *Sender)
{
        X_LOAD_1 = -15;
        Y_LOAD_1 = 0;
        X_LOAD_2 = -5;
        Y_LOAD_2 = 85;
        X_LOAD_3 = 0;
        Y_LOAD_3 = 90;
        X_LOAD_4 = 5;
        Y_LOAD_4 = 100;

        //CURVA 705
        CARGA_RPM_1  = 705;
        CARGA1_RPM1  = -20;
        CARGA2_RPM1  = -15;
        CARGA3_RPM1  = -10;
        CARGA4_RPM1  = -5;
        CGMCR1_RPM1  = 50;
        CGMCR2_RPM1  = 50;
        CGMCR3_RPM1  = 65;
        CGMCR4_RPM1  = 75;
        //CURVA 950
        CARGA_RPM_2  = 950;
        CARGA1_RPM2  = -15;
        CARGA2_RPM2  = -13;
        CARGA3_RPM2  = -7;
        CARGA4_RPM2  = -2;
        CGMCR1_RPM2  = 50;
        CGMCR2_RPM2  = 65;
        CGMCR3_RPM2  = 80;
        CGMCR4_RPM2  = 85;
        //CURVA 1200
        CARGA_RPM_3  = 1200;
        CARGA1_RPM3  = -15;
        CARGA2_RPM3  = -10;
        CARGA3_RPM3  = -5;
        CARGA4_RPM3  = 0;
        CGMCR1_RPM3  = 50;
        CGMCR2_RPM3  = 70;
        CGMCR3_RPM3  = 85;
        CGMCR4_RPM3  = 90;
        //PASSO BASE PARA ACIMA DE 1400
        CARGA_PAS_1 = 0;
        CARGA_PAS_2 = 85;
        CARGA_PAS_3 = 90;
        CARGA_PAS_4 = 100;

        txtRPM1->Text = CARGA_RPM_1;
        txtRPM2->Text = CARGA_RPM_2;
        txtRPM3->Text = CARGA_RPM_3;

        //CURVA 705
        txtCARGA1_RPM1->Text = CARGA1_RPM1;
        txtCARGA2_RPM1->Text = CARGA2_RPM1;
        txtCARGA3_RPM1->Text = CARGA3_RPM1;
        txtCARGA4_RPM1->Text = CARGA4_RPM1;
        txtCGMCR1_RPM1->Text = CGMCR1_RPM1;
        txtCGMCR2_RPM1->Text = CGMCR2_RPM1;
        txtCGMCR3_RPM1->Text = CGMCR3_RPM1;
        txtCGMCR4_RPM1->Text = CGMCR4_RPM1;
        //CURVA 950
        txtCARGA1_RPM2->Text = CARGA1_RPM2;
        txtCARGA2_RPM2->Text = CARGA2_RPM2;
        txtCARGA3_RPM2->Text = CARGA3_RPM2;
        txtCARGA4_RPM2->Text = CARGA4_RPM2;
        txtCGMCR1_RPM2->Text = CGMCR1_RPM2;
        txtCGMCR2_RPM2->Text = CGMCR2_RPM2;
        txtCGMCR3_RPM2->Text = CGMCR3_RPM2;
        txtCGMCR4_RPM2->Text = CGMCR4_RPM2;
        //CURVA 1200
        txtCARGA1_RPM3->Text = CARGA1_RPM3;
        txtCARGA2_RPM3->Text = CARGA2_RPM3;
        txtCARGA3_RPM3->Text = CARGA3_RPM3;
        txtCARGA4_RPM3->Text = CARGA4_RPM3;
        txtCGMCR1_RPM3->Text = CGMCR1_RPM3;
        txtCGMCR2_RPM3->Text = CGMCR2_RPM3;
        txtCGMCR3_RPM3->Text = CGMCR3_RPM3;
        txtCGMCR4_RPM3->Text = CGMCR4_RPM3;
        //PASSO BASE PARA ACIMA DE 1400
        txtPASSO1->Text = CARGA_PAS_1;
        txtPASSO22->Text = CARGA_PAS_2;
        txtPASSO23->Text = CARGA_PAS_3;
        txtPASSO24->Text = CARGA_PAS_4;

        txtX_LOAD_1->Text = X_LOAD_1;
        txtY_LOAD_1->Text = Y_LOAD_1;
        txtX_LOAD_2->Text = X_LOAD_2;
        txtY_LOAD_2->Text = Y_LOAD_2;
        txtX_LOAD_3->Text = X_LOAD_3;
        txtY_LOAD_3->Text = Y_LOAD_3;
        txtX_LOAD_4->Text = X_LOAD_4;
        txtY_LOAD_4->Text = Y_LOAD_4;

        CARGA = X_LOAD_1;
        MCR = CGMCR1_RPM1;
        CREMALHEIRA = MCR + CARGA;

        if (FormatFloat( "##0.#", CLP.RD(PC_SA_ECS_CARGA)) != FormatFloat( "##0.#", CARGA)){
                CLP.WR(PC_SA_ECS_CARGA     , CARGA);
                CLP.WR(PC_HA_RTU_CARGAMCP  , CARGA);
        }
        if (FormatFloat( "##0.#", CLP.RD(PC_SA_ECS_POSICREMALPRINC)) != FormatFloat( "##0.#", CREMALHEIRA)){
                CLP.WR(PC_SA_ECS_POSICREMALPRINC, CREMALHEIRA);
                CLP.WR(PC_SA_ECS_POSICREMALSEC  , CREMALHEIRA);
                CLP.WR(PC_SA_ECS_COMBCREMALPOS  , CREMALHEIRA);
                CLP.WR(PC_HA_RTU_POSICREMAL     , CREMALHEIRA);
        }
        if (FormatFloat( "##0.#", CLP.RD(PC_SA_ECS_MCRATUAL)) != FormatFloat( "##0.#", MCR)){
                CLP.WR(PC_SA_ECS_MCRATUAL, MCR);
        }

        String tmplbl = "";

        chtBaixaRotacao->OpenDataEx(COD_VALUES,3,4);
        chtBaixaRotacao->ThisSerie = 0;
        chtBaixaRotacao->Value[0] = CARGA1_RPM1;
        chtBaixaRotacao->Value[1] = CARGA2_RPM1;
        chtBaixaRotacao->Value[2] = CARGA3_RPM1;
        chtBaixaRotacao->Value[3] = CARGA4_RPM1;

        tmplbl = CARGA_RPM_1;
        chtBaixaRotacao->SerLeg[0] = tmplbl;

        chtBaixaRotacao->ThisSerie = 1;
        chtBaixaRotacao->Value[0] = CARGA1_RPM2;
        chtBaixaRotacao->Value[1] = CARGA2_RPM2;
        chtBaixaRotacao->Value[2] = CARGA3_RPM2;
        chtBaixaRotacao->Value[3] = CARGA4_RPM2;

        tmplbl = CARGA_RPM_2;
        chtBaixaRotacao->SerLeg[1] = tmplbl;

        chtBaixaRotacao->ThisSerie = 2;
        chtBaixaRotacao->Value[0] = CARGA1_RPM3;
        chtBaixaRotacao->Value[1] = CARGA2_RPM3;
        chtBaixaRotacao->Value[2] = CARGA3_RPM3;
        chtBaixaRotacao->Value[3] = CARGA4_RPM3;

        tmplbl = CARGA_RPM_3;
        chtBaixaRotacao->SerLeg[2] = tmplbl;

        chtBaixaRotacao->CloseData(COD_VALUES);

        chtBaixaRotacao->Legend[0] = (String) CARGA_PAS_1;
        chtBaixaRotacao->Legend[1] = (String) CARGA_PAS_2;
        chtBaixaRotacao->Legend[2] = (String) CARGA_PAS_3;
        chtBaixaRotacao->Legend[3] = (String) CARGA_PAS_4;

        cht1400->OpenDataEx(COD_VALUES,1,4);
        cht1400->ThisSerie = 0;
        cht1400->Value[0] = X_LOAD_1;
        cht1400->Value[1] = X_LOAD_2;
        cht1400->Value[2] = X_LOAD_3;
        cht1400->Value[3] = X_LOAD_4;
        cht1400->CloseData(COD_VALUES);

        cht1400->Legend[0] = (String) Y_LOAD_1;
        cht1400->Legend[1] = (String) Y_LOAD_2;
        cht1400->Legend[2] = (String) Y_LOAD_3;
        cht1400->Legend[3] = (String) Y_LOAD_4;
}
//---------------------------------------------------------------------------
void __fastcall TfrmControlesNovo::btnParametrizarClick(TObject *Sender)
{
        //CURVA 1400
        X_LOAD_1 = txtX_LOAD_1->Text.ToDouble();
        Y_LOAD_1 = txtY_LOAD_1->Text.ToDouble();
        X_LOAD_2 = txtX_LOAD_2->Text.ToDouble();
        Y_LOAD_2 = txtY_LOAD_2->Text.ToDouble();
        X_LOAD_3 = txtX_LOAD_3->Text.ToDouble();
        Y_LOAD_3 = txtY_LOAD_3->Text.ToDouble();
        X_LOAD_4 = txtX_LOAD_4->Text.ToDouble();
        Y_LOAD_4 = txtY_LOAD_4->Text.ToDouble();
        //CURVA 705
        CARGA_RPM_1  = txtRPM1->Text.ToDouble();
        CARGA1_RPM1  = txtCARGA1_RPM1->Text.ToDouble();
        CARGA2_RPM1  = txtCARGA2_RPM1->Text.ToDouble();
        CARGA3_RPM1  = txtCARGA3_RPM1->Text.ToDouble();
        CARGA4_RPM1  = txtCARGA4_RPM1->Text.ToDouble();
        CGMCR1_RPM1  = txtCGMCR1_RPM1->Text.ToDouble();
        CGMCR2_RPM1  = txtCGMCR2_RPM1->Text.ToDouble();
        CGMCR3_RPM1  = txtCGMCR3_RPM1->Text.ToDouble();
        CGMCR4_RPM1  = txtCGMCR4_RPM1->Text.ToDouble();
        //CURVA 950
        CARGA_RPM_2  = txtRPM2->Text.ToDouble();
        CARGA1_RPM2  = txtCARGA1_RPM2->Text.ToDouble();
        CARGA2_RPM2  = txtCARGA2_RPM2->Text.ToDouble();
        CARGA3_RPM2  = txtCARGA3_RPM2->Text.ToDouble();
        CARGA4_RPM2  = txtCARGA4_RPM2->Text.ToDouble();
        CGMCR1_RPM2  = txtCGMCR1_RPM2->Text.ToDouble();
        CGMCR2_RPM2  = txtCGMCR2_RPM2->Text.ToDouble();
        CGMCR3_RPM2  = txtCGMCR3_RPM2->Text.ToDouble();
        CGMCR4_RPM2  = txtCGMCR4_RPM2->Text.ToDouble();
        //CURVA 1200
        CARGA_RPM_3  = txtRPM3->Text.ToDouble();
        CARGA1_RPM3  = txtCARGA1_RPM3->Text.ToDouble();
        CARGA2_RPM3  = txtCARGA2_RPM3->Text.ToDouble();
        CARGA3_RPM3  = txtCARGA3_RPM3->Text.ToDouble();
        CARGA4_RPM3  = txtCARGA4_RPM3->Text.ToDouble();
        CGMCR1_RPM3  = txtCGMCR1_RPM3->Text.ToDouble();
        CGMCR2_RPM3  = txtCGMCR2_RPM3->Text.ToDouble();
        CGMCR3_RPM3  = txtCGMCR3_RPM3->Text.ToDouble();
        CGMCR4_RPM3  = txtCGMCR4_RPM3->Text.ToDouble();
        //PASSO BASE PARA ACIMA DE 1400
        CARGA_PAS_1 = txtPASSO1->Text.ToDouble();
        CARGA_PAS_2 = txtPASSO22->Text.ToDouble();
        CARGA_PAS_3 = txtPASSO23->Text.ToDouble();
        CARGA_PAS_4 = txtPASSO24->Text.ToDouble();

        CARGA = X_LOAD_1;
        MCR = CGMCR1_RPM1;
        CREMALHEIRA = MCR + CARGA;

        if (FormatFloat( "##0.#", CLP.RD(PC_SA_ECS_CARGA)) != FormatFloat( "##0.#", CARGA)){
                CLP.WR(PC_SA_ECS_CARGA     , CARGA);
                CLP.WR(PC_HA_RTU_CARGAMCP  , CARGA);
        }
        if (FormatFloat( "##0.#", CLP.RD(PC_SA_ECS_POSICREMALPRINC)) != FormatFloat( "##0.#", CREMALHEIRA)){
                CLP.WR(PC_SA_ECS_POSICREMALPRINC, CREMALHEIRA);
                CLP.WR(PC_SA_ECS_POSICREMALSEC  , CREMALHEIRA);
                CLP.WR(PC_SA_ECS_COMBCREMALPOS  , CREMALHEIRA);
                CLP.WR(PC_HA_RTU_POSICREMAL     , CREMALHEIRA);
        }
        if (FormatFloat( "##0.#", CLP.RD(PC_SA_ECS_MCRATUAL)) != FormatFloat( "##0.#", MCR)){
                CLP.WR(PC_SA_ECS_MCRATUAL, MCR);
        }

        String tmplbl = "";

        chtBaixaRotacao->OpenDataEx(COD_VALUES,3,4);
        chtBaixaRotacao->ThisSerie = 0;
        chtBaixaRotacao->Value[0] = CARGA1_RPM1;
        chtBaixaRotacao->Value[1] = CARGA2_RPM1;
        chtBaixaRotacao->Value[2] = CARGA3_RPM1;
        chtBaixaRotacao->Value[3] = CARGA4_RPM1;

        tmplbl = CARGA_RPM_1;
        chtBaixaRotacao->SerLeg[0] = tmplbl;

        chtBaixaRotacao->ThisSerie = 1;
        chtBaixaRotacao->Value[0] = CARGA1_RPM2;
        chtBaixaRotacao->Value[1] = CARGA2_RPM2;
        chtBaixaRotacao->Value[2] = CARGA3_RPM2;
        chtBaixaRotacao->Value[3] = CARGA4_RPM2;

        tmplbl = CARGA_RPM_2;
        chtBaixaRotacao->SerLeg[1] = tmplbl;

        chtBaixaRotacao->ThisSerie = 2;
        chtBaixaRotacao->Value[0] = CARGA1_RPM3;
        chtBaixaRotacao->Value[1] = CARGA2_RPM3;
        chtBaixaRotacao->Value[2] = CARGA3_RPM3;
        chtBaixaRotacao->Value[3] = CARGA4_RPM3;

        tmplbl = CARGA_RPM_3;
        chtBaixaRotacao->SerLeg[2] = tmplbl;

        chtBaixaRotacao->CloseData(COD_VALUES);

        chtBaixaRotacao->Legend[0] = (String) CARGA_PAS_1;
        chtBaixaRotacao->Legend[1] = (String) CARGA_PAS_2;
        chtBaixaRotacao->Legend[2] = (String) CARGA_PAS_3;
        chtBaixaRotacao->Legend[3] = (String) CARGA_PAS_4;

        cht1400->OpenDataEx(COD_VALUES,1,4);
        cht1400->ThisSerie = 0;
        cht1400->Value[0] = X_LOAD_1;
        cht1400->Value[1] = X_LOAD_2;
        cht1400->Value[2] = X_LOAD_3;
        cht1400->Value[3] = X_LOAD_4;
        cht1400->CloseData(COD_VALUES);

        cht1400->Legend[0] = (String) Y_LOAD_1;
        cht1400->Legend[1] = (String) Y_LOAD_2;
        cht1400->Legend[2] = (String) Y_LOAD_3;
        cht1400->Legend[3] = (String) Y_LOAD_4;
}
//---------------------------------------------------------------------------
void __fastcall TfrmControlesNovo::btnFecharClick(TObject *Sender)
{
   frmControlesNovo->Close();          
}
//---------------------------------------------------------------------------

