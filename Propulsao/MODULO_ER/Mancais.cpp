//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Mancais.h"
#include "Principal.h"
#include "ModBusDriverLib\TModBusTCPDriver.cpp"

//--------------------------- MODPRI ---------------------------
extern String PC_HA_ERPBC_MODPRI_TEMPMANCAL10;
extern String PC_HA_ERPBC_MODPRI_TEMPMANCAL9;
extern String PC_HA_ERPBC_MODPRI_TEMPMANCAL8;
extern String PC_HA_ERPBC_MODPRI_TEMPMANCAL7;
extern String PC_HA_ERPBC_MODPRI_TEMPMANCAL6;
extern String PC_HA_ERPBC_MODPRI_TEMPMANCAL5;
extern String PC_HA_ERPBC_MODPRI_TEMPMANCAL4;
extern String PC_HA_ERPBC_MODPRI_TEMPMANCAL3;
extern String PC_HA_ERPBC_MODPRI_TEMPMANCAL2;
extern String PC_HA_ERPBC_MODPRI_TEMPMANCAL1;

//--------------------------- MODSBB ---------------------------
extern String PC_HA_ERSBB_MODSBB_TEMPMANCAL8;
extern String PC_HA_ERSBB_MODSBB_TEMPMANCAL7;
extern String PC_HA_ERSBB_MODSBB_TEMPMANCAL6;
extern String PC_HA_ERSBB_MODSBB_TEMPMANCAL5;
extern String PC_HA_ERSBB_MODSBB_TEMPMANCAL4;
extern String PC_HA_ERSBB_MODSBB_TEMPMANCAL3;
extern String PC_HA_ERSBB_MODSBB_TEMPMANCAL2;
extern String PC_HA_ERSBB_MODSBB_TEMPMANCAL1;

//--------------------------- MODSBE ---------------------------
extern String PC_HA_ERSBE_MODSBE_TEMPMANCAL8;
extern String PC_HA_ERSBE_MODSBE_TEMPMANCAL7;
extern String PC_HA_ERSBE_MODSBE_TEMPMANCAL6;
extern String PC_HA_ERSBE_MODSBE_TEMPMANCAL5;
extern String PC_HA_ERSBE_MODSBE_TEMPMANCAL4;
extern String PC_HA_ERSBE_MODSBE_TEMPMANCAL3;
extern String PC_HA_ERSBE_MODSBE_TEMPMANCAL2;
extern String PC_HA_ERSBE_MODSBE_TEMPMANCAL1;

//--------------------------- MLEAR ---------------------------
extern String PC_HA_ERSBB_MLEAR_TEMP;
extern String PC_HA_ERSBE_MLEAR_TEMP;

//--------------------------- MLEAV ---------------------------
extern String PC_HA_ERSBB_MLEAV_TEMP;
extern String PC_HA_ERSBE_MLEAV_TEMP;

extern TModBusTCPDriver CLP;


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMancal *frmMancal;
//---------------------------------------------------------------------------
__fastcall TfrmMancal::TfrmMancal(TComponent* Owner)
        : TForm(Owner)
{

        lblInit1->Caption = "Incializando";
        lblInit2->Caption = "Incializando";
        lblInit3->Caption = "Incializando";
        lblInit4->Caption = "Incializando";
        lblInit5->Caption = "Incializando";

}
//---------------------------------------------------------------------------
void __fastcall TfrmMancal::btnMODSBB_TEMPMANCAL1Click(TObject *Sender)
{
        CLP.WR( PC_HA_ERSBB_MODSBB_TEMPMANCAL1, txtMODSBB_TEMPMANCAL1->Text.ToDouble() );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMancal::btnMODSBB_TEMPMANCAL2Click(TObject *Sender)
{
        CLP.WR( PC_HA_ERSBB_MODSBB_TEMPMANCAL2, txtMODSBB_TEMPMANCAL2->Text.ToDouble() );        
}
//---------------------------------------------------------------------------

void __fastcall TfrmMancal::btnMODSBB_TEMPMANCAL3Click(TObject *Sender)
{
        CLP.WR( PC_HA_ERSBB_MODSBB_TEMPMANCAL3, txtMODSBB_TEMPMANCAL3->Text.ToDouble() );        
}
//---------------------------------------------------------------------------

void __fastcall TfrmMancal::btnMODSBB_TEMPMANCAL4Click(TObject *Sender)
{
        CLP.WR( PC_HA_ERSBB_MODSBB_TEMPMANCAL4, txtMODSBB_TEMPMANCAL4->Text.ToDouble() );        
}
//---------------------------------------------------------------------------

void __fastcall TfrmMancal::btnMODSBB_TEMPMANCAL5Click(TObject *Sender)
{
        CLP.WR( PC_HA_ERSBB_MODSBB_TEMPMANCAL5, txtMODSBB_TEMPMANCAL5->Text.ToDouble() );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMancal::btnMODSBB_TEMPMANCAL6Click(TObject *Sender)
{
        CLP.WR( PC_HA_ERSBB_MODSBB_TEMPMANCAL6, txtMODSBB_TEMPMANCAL6->Text.ToDouble() );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMancal::btnMODSBB_TEMPMANCAL7Click(TObject *Sender)
{
        CLP.WR( PC_HA_ERSBB_MODSBB_TEMPMANCAL7, txtMODSBB_TEMPMANCAL7->Text.ToDouble() );        
}
//---------------------------------------------------------------------------

void __fastcall TfrmMancal::btnMODSBB_TEMPMANCAL8Click(TObject *Sender)
{
        CLP.WR( PC_HA_ERSBB_MODSBB_TEMPMANCAL8, txtMODSBB_TEMPMANCAL8->Text.ToDouble() );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMancal::btnMODPRI_TEMPMANCAL1Click(TObject *Sender)
{
        CLP.WR( PC_HA_ERPBC_MODPRI_TEMPMANCAL1, txtMODPRI_TEMPMANCAL1->Text.ToDouble() );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMancal::btnMODPRI_TEMPMANCAL2Click(TObject *Sender)
{
        CLP.WR( PC_HA_ERPBC_MODPRI_TEMPMANCAL2, txtMODPRI_TEMPMANCAL2->Text.ToDouble() );        
}
//---------------------------------------------------------------------------

void __fastcall TfrmMancal::btnMODPRI_TEMPMANCAL3Click(TObject *Sender)
{
        CLP.WR( PC_HA_ERPBC_MODPRI_TEMPMANCAL3, txtMODPRI_TEMPMANCAL3->Text.ToDouble() );        
}
//---------------------------------------------------------------------------

void __fastcall TfrmMancal::btnMODPRI_TEMPMANCAL4Click(TObject *Sender)
{
        CLP.WR( PC_HA_ERPBC_MODPRI_TEMPMANCAL4, txtMODPRI_TEMPMANCAL4->Text.ToDouble() );        
}
//---------------------------------------------------------------------------

void __fastcall TfrmMancal::btnMODPRI_TEMPMANCAL5Click(TObject *Sender)
{
        CLP.WR( PC_HA_ERPBC_MODPRI_TEMPMANCAL5, txtMODPRI_TEMPMANCAL5->Text.ToDouble() );        
}
//---------------------------------------------------------------------------

void __fastcall TfrmMancal::btnMODPRI_TEMPMANCAL6Click(TObject *Sender)
{
        CLP.WR( PC_HA_ERPBC_MODPRI_TEMPMANCAL6, txtMODPRI_TEMPMANCAL6->Text.ToDouble() );        
}
//---------------------------------------------------------------------------

void __fastcall TfrmMancal::btnMODPRI_TEMPMANCAL7Click(TObject *Sender)
{
        CLP.WR( PC_HA_ERPBC_MODPRI_TEMPMANCAL7, txtMODPRI_TEMPMANCAL7->Text.ToDouble() );        
}
//---------------------------------------------------------------------------

void __fastcall TfrmMancal::btnMODPRI_TEMPMANCAL8Click(TObject *Sender)
{
        CLP.WR( PC_HA_ERPBC_MODPRI_TEMPMANCAL8, txtMODPRI_TEMPMANCAL8->Text.ToDouble() );        
}
//---------------------------------------------------------------------------

void __fastcall TfrmMancal::btnMODPRI_TEMPMANCAL9Click(TObject *Sender)
{
        CLP.WR( PC_HA_ERPBC_MODPRI_TEMPMANCAL9, txtMODPRI_TEMPMANCAL9->Text.ToDouble() );        
}
//---------------------------------------------------------------------------

void __fastcall TfrmMancal::btnMODPRI_TEMPMANCAL10Click(TObject *Sender)
{
        CLP.WR( PC_HA_ERPBC_MODPRI_TEMPMANCAL10, txtMODPRI_TEMPMANCAL10->Text.ToDouble() );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMancal::btnMODSBE_TEMPMANCAL1Click(TObject *Sender)
{
        CLP.WR( PC_HA_ERSBE_MODSBE_TEMPMANCAL1, txtMODSBE_TEMPMANCAL1->Text.ToDouble() );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMancal::btnMODSBE_TEMPMANCAL2Click(TObject *Sender)
{
        CLP.WR( PC_HA_ERSBE_MODSBE_TEMPMANCAL2, txtMODSBE_TEMPMANCAL2->Text.ToDouble() );        
}
//---------------------------------------------------------------------------

void __fastcall TfrmMancal::btnMODSBE_TEMPMANCAL3Click(TObject *Sender)
{
        CLP.WR( PC_HA_ERSBE_MODSBE_TEMPMANCAL3, txtMODSBE_TEMPMANCAL3->Text.ToDouble() );        
}
//---------------------------------------------------------------------------

void __fastcall TfrmMancal::btnMODSBE_TEMPMANCAL4Click(TObject *Sender)
{
        CLP.WR( PC_HA_ERSBE_MODSBE_TEMPMANCAL4, txtMODSBE_TEMPMANCAL4->Text.ToDouble() );        
}
//---------------------------------------------------------------------------

void __fastcall TfrmMancal::btnMODSBE_TEMPMANCAL5Click(TObject *Sender)
{
        CLP.WR( PC_HA_ERSBE_MODSBE_TEMPMANCAL5, txtMODSBE_TEMPMANCAL5->Text.ToDouble() );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMancal::btnMODSBE_TEMPMANCAL6Click(TObject *Sender)
{
        CLP.WR( PC_HA_ERSBE_MODSBE_TEMPMANCAL6, txtMODSBE_TEMPMANCAL6->Text.ToDouble() );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMancal::btnMODSBE_TEMPMANCAL7Click(TObject *Sender)
{
        CLP.WR( PC_HA_ERSBE_MODSBE_TEMPMANCAL7, txtMODSBE_TEMPMANCAL7->Text.ToDouble() );        
}
//---------------------------------------------------------------------------

void __fastcall TfrmMancal::btnMODSBE_TEMPMANCAL8Click(TObject *Sender)
{
        CLP.WR( PC_HA_ERSBE_MODSBE_TEMPMANCAL8, txtMODSBE_TEMPMANCAL8->Text.ToDouble() );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMancal::btnBB_MLEAV_TEMPClick(TObject *Sender)
{
        CLP.WR( PC_HA_ERSBB_MLEAV_TEMP, txtBB_MLEAV_TEMP->Text.ToDouble() );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMancal::btnBB_MLEAR_TEMPClick(TObject *Sender)
{
        CLP.WR( PC_HA_ERSBB_MLEAR_TEMP, txtBB_MLEAR_TEMP->Text.ToDouble() );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMancal::btnBE_MLEAV_TEMPClick(TObject *Sender)
{
        CLP.WR( PC_HA_ERSBE_MLEAV_TEMP, txtBE_MLEAV_TEMP->Text.ToDouble() );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMancal::btnBE_MLEAR_TEMPClick(TObject *Sender)
{
        CLP.WR( PC_HA_ERSBE_MLEAR_TEMP, txtBE_MLEAR_TEMP->Text.ToDouble() );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMancal::btnMODSBBClick(TObject *Sender)
{
        pnlMODSBB->Visible = true;
        pnlMODSBE->Visible = false;
        pnlMODPRI->Visible = false;
        pnlEixos->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMancal::btnMODPRIClick(TObject *Sender)
{
        pnlMODSBB->Visible = false;
        pnlMODSBE->Visible = false;
        pnlMODPRI->Visible = true;
        pnlEixos->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMancal::btnEIXOSClick(TObject *Sender)
{
        pnlMODSBB->Visible = false;
        pnlMODSBE->Visible = false;
        pnlMODPRI->Visible = false;
        pnlEixos->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMancal::btnMODSBEClick(TObject *Sender)
{
        pnlMODSBB->Visible = false;
        pnlMODSBE->Visible = true;
        pnlMODPRI->Visible = false;
        pnlEixos->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMancal::btnFecharClick(TObject *Sender)
{
        frmMancal->Close();        
}
//---------------------------------------------------------------------------

