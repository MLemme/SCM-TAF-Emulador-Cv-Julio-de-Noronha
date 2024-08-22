//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Permissivos.h"
#include "Principal.h"
#include "ModBusDriverLib\TModBusTCPDriver.cpp"

extern String PC_HL_AOLTG_TQDREN_NIVELALTO;//(N�VEL BAIXO TQ DRENOS MANFOLD)
extern String PC_SL_TBGAS_ATLAS_PERMPTDATLASOK;// BLQ MANUAL PTDA N�O ATIVADO (CHAVE NO CCM)
extern String PC_SL_TBGAS_ATLAS_PERMPTDOLNVOK;// N�VEL OL TQ MOD. LUB. NORMAL
extern String PC_SL_TBGAS_ATLAS_PERMPTDLUBOK;// (TEMPERATURAS OL NORMAIS ( POCETOS E MOD. LUBRIF.)
extern String PC_SL_TBGAS_ATLAS_ABVFEC;// V SANGRIA AR FECHADA)
extern String PC_SL_TBGAS_ATLAS_ABVABT;
extern String PC_SL_TBGAS_ATLAS_PERMPTDODPOK;// PRESS�O SUPRIMENTO COMBUST�VEL OK (0.34 A 0.45 BAR)
extern String PC_SL_TBGAS_ATLAS_PERMPTDODTOK;// TEMP SUPRIMENTO COMBUST�VEL OK (0�C A 70�C)
extern String PC_SL_TBGAS_ATLAS_PLAEMIDLE;// PLA NO MINIMO
extern String PC_SL_TBGAS_ATLAS_LIMPLAATUANDO;// PLA LIMITADO AO MINIMO (CTRL)
extern String PC_SL_TBGAS_ATLAS_PERMPTDIGNOK;// (IGNI��O SEM FALHAS)
extern String PC_SL_TBGAS_ATLAS_PERMPTDNGGBX;// NGG < 300 RPM
extern String PC_SL_TBGAS_ATLAS_VVEXTODFECH;// VV EXT COMB FECHADA (VOD 116)
extern String PC_SL_TBGAS_ATLAS_VVEXTODABT;
extern String PC_SL_TBGAS_ATLAS_ASOVFECH;// V�LVULA DE AR DE PARTIDA FECHADA
extern String PC_SL_TBGAS_ATLAS_ARRANQUEOK;// STARTER FRIO
extern String PC_SL_TBGAS_ATLAS_PERMPTDSPNTPBX;// SET POINT DE NTP BAIXO
extern TModBusTCPDriver CLP;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmPermissivos *frmPermissivos;
//---------------------------------------------------------------------------
__fastcall TfrmPermissivos::TfrmPermissivos(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfrmPermissivos::btnTQDREN_NIVELALTOClick(TObject *Sender)
{
        if (btnTQDREN_NIVELALTO->Caption == "TQ DREN N�O NV ALTO"){
                CLP.WR(PC_HL_AOLTG_TQDREN_NIVELALTO, 0);
        }
        else{
                if (btnTQDREN_NIVELALTO->Caption == "TQ DREN NV ALTO"){
                        CLP.WR(PC_HL_AOLTG_TQDREN_NIVELALTO, 1);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPermissivos::btnPERMPTDATLASOKClick(TObject *Sender)
{
        if (btnPERMPTDATLASOK->Caption == "BLQ INATIVO"){
                CLP.WR(PC_SL_TBGAS_ATLAS_PERMPTDATLASOK, 0);
        }
        else{
                if (btnPERMPTDATLASOK->Caption == "BLQ ATIVO"){
                        CLP.WR(PC_SL_TBGAS_ATLAS_PERMPTDATLASOK, 1);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPermissivos::btnPERMPTDOLNVOKClick(TObject *Sender)
{
        if (btnPERMPTDOLNVOK->Caption == "MOD. LUB. NV. OK"){
                CLP.WR(PC_SL_TBGAS_ATLAS_PERMPTDOLNVOK, 0);
        }
        else{
                if (btnPERMPTDOLNVOK->Caption == "MOD. LUB. NV. N�O OK"){
                        CLP.WR(PC_SL_TBGAS_ATLAS_PERMPTDOLNVOK, 1);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPermissivos::btnPERMPTDLUBOKClick(TObject *Sender)
{
        if (btnPERMPTDLUBOK->Caption == "MOD. LUB. TEMP. OK"){
                CLP.WR(PC_SL_TBGAS_ATLAS_PERMPTDLUBOK, 0);
        }
        else{
                if (btnPERMPTDLUBOK->Caption == "MOD. LUB. TEMP. N�O OK"){
                        CLP.WR(PC_SL_TBGAS_ATLAS_PERMPTDLUBOK, 1);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPermissivos::shpABVClick(TObject *Sender)
{
        if (shpABV->Caption == "ABV FECHADA"){
                CLP.WR(PC_SL_TBGAS_ATLAS_ABVFEC, 0);
                CLP.WR(PC_SL_TBGAS_ATLAS_ABVABT, 1);
        }
        else{
                if (shpABV->Caption == "ABV ABERTA" || shpABV->Caption == "ABV INDEFINIDA"){
                        CLP.WR(PC_SL_TBGAS_ATLAS_ABVABT, 0);
                        CLP.WR(PC_SL_TBGAS_ATLAS_ABVFEC, 1);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPermissivos::btnPERMPTDODPOKClick(TObject *Sender)
{
        if (btnPERMPTDODPOK->Caption == "PRESS. OD. OK"){
                CLP.WR(PC_SL_TBGAS_ATLAS_PERMPTDODPOK, 0);
        }
        else{
                if (btnPERMPTDODPOK->Caption == "PRESS. OD. N�O OK"){
                        CLP.WR(PC_SL_TBGAS_ATLAS_PERMPTDODPOK, 1);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPermissivos::btnPERMPTDODTOKClick(TObject *Sender)
{
        if (btnPERMPTDODTOK->Caption == "TEMP. OD. OK"){
                CLP.WR(PC_SL_TBGAS_ATLAS_PERMPTDODTOK, 0);
        }
        else{
                if (btnPERMPTDODTOK->Caption == "TEMP. OD. N�O OK"){
                        CLP.WR(PC_SL_TBGAS_ATLAS_PERMPTDODTOK, 1);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPermissivos::btnPLAEMIDLEClick(TObject *Sender)
{
        if (btnPLAEMIDLE->Caption == "PLA NO M�NIMO"){
                CLP.WR(PC_SL_TBGAS_ATLAS_PLAEMIDLE, 0);
        }
        else{
                if (btnPLAEMIDLE->Caption == "N�O PLA NO M�NIMO"){
                        CLP.WR(PC_SL_TBGAS_ATLAS_PLAEMIDLE, 1);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPermissivos::btnLIMPLAATUANDOClick(TObject *Sender)
{
        if (btnLIMPLAATUANDO->Caption == "PLA LIM. M�NIMO"){
                CLP.WR(PC_SL_TBGAS_ATLAS_LIMPLAATUANDO, 0);
        }
        else{
                if (btnLIMPLAATUANDO->Caption == "N�O PLA LIM. M�NIMO"){
                        CLP.WR(PC_SL_TBGAS_ATLAS_LIMPLAATUANDO, 1);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPermissivos::btnPERMPTDIGNOKClick(TObject *Sender)
{
        if (btnPERMPTDIGNOK->Caption == "IGN��O OK"){
                CLP.WR(PC_SL_TBGAS_ATLAS_PERMPTDIGNOK, 0);
        }
        else{
                if (btnPERMPTDIGNOK->Caption == "IGN��O N�O OK"){
                        CLP.WR(PC_SL_TBGAS_ATLAS_PERMPTDIGNOK, 1);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPermissivos::btnPERMPTDNGGBXClick(TObject *Sender)
{
        if (btnPERMPTDNGGBX->Caption == "NGG BX (< 300 RPM)"){
                CLP.WR(PC_SL_TBGAS_ATLAS_PERMPTDNGGBX, 0);
        }
        else{
                if (btnPERMPTDNGGBX->Caption == "NGG N�O BX (> 300 RPM)"){
                        CLP.WR(PC_SL_TBGAS_ATLAS_PERMPTDNGGBX, 1);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPermissivos::btnVVEXTODClick(TObject *Sender)
{
        if (btnVVEXTOD->Caption == "VV EXT OD FECHADA"){
                CLP.WR(PC_SL_TBGAS_ATLAS_VVEXTODFECH, 0);
                CLP.WR(PC_SL_TBGAS_ATLAS_VVEXTODABT, 1);
        }
        else{
                if (btnVVEXTOD->Caption == "VV EXT OD ABERTA" || btnVVEXTOD->Caption == "VV EXT OD INDEFINIDA"){
                        CLP.WR(PC_SL_TBGAS_ATLAS_VVEXTODABT, 0);
                        CLP.WR(PC_SL_TBGAS_ATLAS_VVEXTODFECH, 1);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPermissivos::btnASOVFECHClick(TObject *Sender)
{
        if (btnASOVFECH->Caption == "ASOV FECHADA"){
                CLP.WR(PC_SL_TBGAS_ATLAS_ASOVFECH, 0);
        }
        else{
                if (btnASOVFECH->Caption == "ASOV ABERTA"){
                        CLP.WR(PC_SL_TBGAS_ATLAS_ASOVFECH, 1);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPermissivos::btnARRANQUEOKClick(TObject *Sender)
{
        if (btnARRANQUEOK->Caption == "ARRANQUE OK"){
                CLP.WR(PC_SL_TBGAS_ATLAS_ARRANQUEOK, 0);
        }
        else{
                if (btnARRANQUEOK->Caption == "ARRANQUE N�O OK"){
                        CLP.WR(PC_SL_TBGAS_ATLAS_ARRANQUEOK, 1);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPermissivos::btnPERMPTDSPNTPBXClick(TObject *Sender)
{
        if (btnPERMPTDSPNTPBX->Caption == "SP NTP BAIXO"){
                CLP.WR(PC_SL_TBGAS_ATLAS_PERMPTDSPNTPBX, 0);
        }
        else{
                if (btnPERMPTDSPNTPBX->Caption == "SP NTP N�O BAIXO"){
                        CLP.WR(PC_SL_TBGAS_ATLAS_PERMPTDSPNTPBX, 1);
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TfrmPermissivos::btnFecharClick(TObject *Sender)
{
        frmPermissivos->Close();
}
//---------------------------------------------------------------------------

