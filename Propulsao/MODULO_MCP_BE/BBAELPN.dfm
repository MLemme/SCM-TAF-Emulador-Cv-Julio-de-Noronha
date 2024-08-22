object frmBBAELPN: TfrmBBAELPN
  Left = 323
  Top = 231
  Width = 497
  Height = 351
  Caption = 'frmBBAELPN'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnHide = FormHide
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object shpPartirBBAOLETH1: TShape
    Left = 48
    Top = 46
    Width = 17
    Height = 17
    Shape = stCircle
  end
  object Label25: TLabel
    Left = 41
    Top = 24
    Width = 24
    Height = 13
    Caption = 'Partir'
  end
  object shpPararBBAOLETH1: TShape
    Left = 88
    Top = 46
    Width = 17
    Height = 17
    Shape = stCircle
  end
  object Label27: TLabel
    Left = 80
    Top = 24
    Width = 25
    Height = 13
    Caption = 'Parar'
  end
  object Label1: TLabel
    Left = 177
    Top = 24
    Width = 35
    Height = 13
    Caption = 'Manual'
  end
  object Label2: TLabel
    Left = 232
    Top = 24
    Width = 53
    Height = 13
    Caption = 'Automático'
  end
  object tmrPosicao: TTimer
    Enabled = False
    OnTimer = tmrPosicaoTimer
    Left = 8
    Top = 288
  end
end
