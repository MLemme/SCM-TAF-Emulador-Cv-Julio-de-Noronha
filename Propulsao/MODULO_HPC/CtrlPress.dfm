object frmCtrlParamAuto: TfrmCtrlParamAuto
  Left = 869
  Top = 260
  BorderStyle = bsToolWindow
  Caption = 'PARÂMETROS DAS BBAS P1'
  ClientHeight = 361
  ClientWidth = 634
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Shape1: TShape
    Left = 322
    Top = 2
    Width = 303
    Height = 303
    Brush.Style = bsClear
    Pen.Color = clGreen
    Pen.Width = 3
  end
  object Shape20: TShape
    Left = 10
    Top = 2
    Width = 303
    Height = 303
    Brush.Style = bsClear
    Pen.Color = clNavy
    Pen.Width = 3
  end
  object lblRPMEIXOBB: TLabel
    Left = 122
    Top = 280
    Width = 40
    Height = 17
    AutoSize = False
    Caption = 'lblRPMEIXOBB'
    Color = clWhite
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
  end
  object Label1: TLabel
    Left = 72
    Top = 24
    Width = 191
    Height = 13
    Caption = 'Valor de Rotação no Eixo Mínima'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 16
    Top = 8
    Width = 46
    Height = 13
    Caption = 'HPC BB'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label5: TLabel
    Left = 16
    Top = 48
    Width = 24
    Height = 13
    Caption = 'Atual'
  end
  object lblRotMin_BB: TLabel
    Left = 48
    Top = 48
    Width = 40
    Height = 17
    AutoSize = False
    Caption = 'lblRotMin'
    Color = clWhite
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
  end
  object Label6: TLabel
    Left = 56
    Top = 72
    Width = 219
    Height = 13
    Caption = 'Valor de Pressão para atuar a P1 Auto'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label7: TLabel
    Left = 16
    Top = 96
    Width = 24
    Height = 13
    Caption = 'Atual'
  end
  object lblPressMin_BB: TLabel
    Left = 48
    Top = 96
    Width = 40
    Height = 17
    AutoSize = False
    Caption = 'lblPressMin'
    Color = clWhite
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
  end
  object Label8: TLabel
    Left = 80
    Top = 120
    Width = 172
    Height = 13
    Caption = 'Valor de Pressão para Alarmar'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label9: TLabel
    Left = 24
    Top = 168
    Width = 273
    Height = 13
    Caption = 'Valor de Pressão para atuar respsosta de Passo'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label10: TLabel
    Left = 80
    Top = 216
    Width = 169
    Height = 13
    Caption = 'Valor de Pressão Operacional'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label3: TLabel
    Left = 16
    Top = 144
    Width = 24
    Height = 13
    Caption = 'Atual'
  end
  object Label4: TLabel
    Left = 16
    Top = 192
    Width = 24
    Height = 13
    Caption = 'Atual'
  end
  object Label11: TLabel
    Left = 16
    Top = 240
    Width = 24
    Height = 13
    Caption = 'Atual'
  end
  object Label12: TLabel
    Left = 16
    Top = 280
    Width = 95
    Height = 13
    Caption = 'Rotação no Eixo'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object lblPressAlm_BB: TLabel
    Left = 48
    Top = 144
    Width = 40
    Height = 17
    AutoSize = False
    Caption = 'lblPressAlm'
    Color = clWhite
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
  end
  object lblPressLib_BB: TLabel
    Left = 48
    Top = 192
    Width = 40
    Height = 17
    AutoSize = False
    Caption = 'lblPressLib'
    Color = clWhite
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
  end
  object lblPressOpe_BB: TLabel
    Left = 48
    Top = 240
    Width = 40
    Height = 17
    AutoSize = False
    Caption = 'lblPressOpe'
    Color = clWhite
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
  end
  object Label13: TLabel
    Left = 184
    Top = 48
    Width = 26
    Height = 13
    Caption = 'Novo'
  end
  object Label14: TLabel
    Left = 184
    Top = 96
    Width = 26
    Height = 13
    Caption = 'Novo'
  end
  object Label15: TLabel
    Left = 184
    Top = 144
    Width = 26
    Height = 13
    Caption = 'Novo'
  end
  object Label16: TLabel
    Left = 184
    Top = 192
    Width = 26
    Height = 13
    Caption = 'Novo'
  end
  object Label17: TLabel
    Left = 184
    Top = 240
    Width = 26
    Height = 13
    Caption = 'Novo'
  end
  object Label18: TLabel
    Left = 96
    Top = 240
    Width = 19
    Height = 13
    Caption = 'bar'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label19: TLabel
    Left = 272
    Top = 240
    Width = 19
    Height = 13
    Caption = 'bar'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label20: TLabel
    Left = 96
    Top = 192
    Width = 19
    Height = 13
    Caption = 'bar'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label21: TLabel
    Left = 96
    Top = 144
    Width = 19
    Height = 13
    Caption = 'bar'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label22: TLabel
    Left = 96
    Top = 96
    Width = 19
    Height = 13
    Caption = 'bar'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label23: TLabel
    Left = 96
    Top = 48
    Width = 28
    Height = 13
    Caption = 'RPM'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label24: TLabel
    Left = 272
    Top = 96
    Width = 19
    Height = 13
    Caption = 'bar'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label25: TLabel
    Left = 272
    Top = 144
    Width = 19
    Height = 13
    Caption = 'bar'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label26: TLabel
    Left = 272
    Top = 192
    Width = 19
    Height = 13
    Caption = 'bar'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label27: TLabel
    Left = 272
    Top = 48
    Width = 28
    Height = 13
    Caption = 'RPM'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object lblRPMEIXOBE: TLabel
    Left = 434
    Top = 280
    Width = 40
    Height = 17
    AutoSize = False
    Caption = 'lblRPMEIXOBB'
    Color = clWhite
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
  end
  object Label29: TLabel
    Left = 384
    Top = 24
    Width = 191
    Height = 13
    Caption = 'Valor de Rotação no Eixo Mínima'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label30: TLabel
    Left = 328
    Top = 8
    Width = 46
    Height = 13
    Caption = 'HPC BE'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label31: TLabel
    Left = 328
    Top = 48
    Width = 24
    Height = 13
    Caption = 'Atual'
  end
  object lblRotMin_BE: TLabel
    Left = 360
    Top = 48
    Width = 40
    Height = 17
    AutoSize = False
    Caption = 'lblRotMin'
    Color = clWhite
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
  end
  object Label33: TLabel
    Left = 368
    Top = 72
    Width = 219
    Height = 13
    Caption = 'Valor de Pressão para atuar a P1 Auto'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label34: TLabel
    Left = 328
    Top = 96
    Width = 24
    Height = 13
    Caption = 'Atual'
  end
  object lblPressMin_BE: TLabel
    Left = 360
    Top = 96
    Width = 40
    Height = 17
    AutoSize = False
    Caption = 'lblPressMin'
    Color = clWhite
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
  end
  object Label36: TLabel
    Left = 392
    Top = 120
    Width = 172
    Height = 13
    Caption = 'Valor de Pressão para Alarmar'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label37: TLabel
    Left = 336
    Top = 168
    Width = 273
    Height = 13
    Caption = 'Valor de Pressão para atuar respsosta de Passo'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label38: TLabel
    Left = 392
    Top = 216
    Width = 169
    Height = 13
    Caption = 'Valor de Pressão Operacional'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label39: TLabel
    Left = 328
    Top = 144
    Width = 24
    Height = 13
    Caption = 'Atual'
  end
  object Label40: TLabel
    Left = 328
    Top = 192
    Width = 24
    Height = 13
    Caption = 'Atual'
  end
  object Label41: TLabel
    Left = 328
    Top = 240
    Width = 24
    Height = 13
    Caption = 'Atual'
  end
  object Label42: TLabel
    Left = 328
    Top = 280
    Width = 95
    Height = 13
    Caption = 'Rotação no Eixo'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object lblPressAlm_BE: TLabel
    Left = 360
    Top = 144
    Width = 40
    Height = 17
    AutoSize = False
    Caption = 'lblPressAlm'
    Color = clWhite
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
  end
  object lblPressLib_BE: TLabel
    Left = 360
    Top = 192
    Width = 40
    Height = 17
    AutoSize = False
    Caption = 'lblPressLib'
    Color = clWhite
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
  end
  object lblPressOpe_BE: TLabel
    Left = 360
    Top = 240
    Width = 40
    Height = 17
    AutoSize = False
    Caption = 'lblPressOpe'
    Color = clWhite
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
  end
  object Label46: TLabel
    Left = 496
    Top = 48
    Width = 26
    Height = 13
    Caption = 'Novo'
  end
  object Label47: TLabel
    Left = 496
    Top = 96
    Width = 26
    Height = 13
    Caption = 'Novo'
  end
  object Label48: TLabel
    Left = 496
    Top = 144
    Width = 26
    Height = 13
    Caption = 'Novo'
  end
  object Label49: TLabel
    Left = 496
    Top = 192
    Width = 26
    Height = 13
    Caption = 'Novo'
  end
  object Label50: TLabel
    Left = 496
    Top = 240
    Width = 26
    Height = 13
    Caption = 'Novo'
  end
  object Label51: TLabel
    Left = 408
    Top = 240
    Width = 19
    Height = 13
    Caption = 'bar'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label52: TLabel
    Left = 584
    Top = 240
    Width = 19
    Height = 13
    Caption = 'bar'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label53: TLabel
    Left = 408
    Top = 192
    Width = 19
    Height = 13
    Caption = 'bar'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label54: TLabel
    Left = 408
    Top = 144
    Width = 19
    Height = 13
    Caption = 'bar'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label55: TLabel
    Left = 408
    Top = 96
    Width = 19
    Height = 13
    Caption = 'bar'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label56: TLabel
    Left = 408
    Top = 48
    Width = 28
    Height = 13
    Caption = 'RPM'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label57: TLabel
    Left = 584
    Top = 96
    Width = 19
    Height = 13
    Caption = 'bar'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label58: TLabel
    Left = 584
    Top = 144
    Width = 19
    Height = 13
    Caption = 'bar'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label59: TLabel
    Left = 584
    Top = 192
    Width = 19
    Height = 13
    Caption = 'bar'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label60: TLabel
    Left = 584
    Top = 48
    Width = 28
    Height = 13
    Caption = 'RPM'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object txtRotMin_BB: TEdit
    Left = 216
    Top = 48
    Width = 49
    Height = 21
    TabOrder = 0
    Text = 'txtRotMin'
  end
  object txtPressMin_BB: TEdit
    Left = 216
    Top = 96
    Width = 49
    Height = 21
    TabOrder = 1
    Text = 'txtPressMin_BB'
  end
  object txtPressAlm_BB: TEdit
    Left = 216
    Top = 144
    Width = 49
    Height = 21
    TabOrder = 2
    Text = 'txtPressAlm'
  end
  object txtPressLib_BB: TEdit
    Left = 216
    Top = 192
    Width = 49
    Height = 21
    TabOrder = 3
    Text = 'txtPressLib'
  end
  object txtPressOpe_BB: TEdit
    Left = 216
    Top = 240
    Width = 49
    Height = 21
    TabOrder = 4
    Text = 'txtPressOpe'
  end
  object txtRotMin_BE: TEdit
    Left = 528
    Top = 48
    Width = 49
    Height = 21
    TabOrder = 5
    Text = 'txtRotMin'
  end
  object txtPressMin_BE: TEdit
    Left = 528
    Top = 96
    Width = 49
    Height = 21
    TabOrder = 6
    Text = 'txtPressMin_BB'
  end
  object txtPressAlm_BE: TEdit
    Left = 528
    Top = 144
    Width = 49
    Height = 21
    TabOrder = 7
    Text = 'txtPressAlm'
  end
  object txtPressLib_BE: TEdit
    Left = 528
    Top = 192
    Width = 49
    Height = 21
    TabOrder = 8
    Text = 'txtPressLib'
  end
  object txtPressOpe_BE: TEdit
    Left = 528
    Top = 240
    Width = 49
    Height = 21
    TabOrder = 9
    Text = 'txtPressOpe'
  end
  object btnAlterar: TButton
    Left = 208
    Top = 312
    Width = 105
    Height = 41
    Caption = 'ALTERAR'
    TabOrder = 10
    OnClick = btnAlterarClick
  end
  object btnFECHAR: TButton
    Left = 320
    Top = 312
    Width = 105
    Height = 41
    Caption = 'FECHAR'
    TabOrder = 11
    OnClick = btnFECHARClick
  end
  object tmrAtualiza: TTimer
    Enabled = False
    Interval = 200
    OnTimer = tmrAtualizaTimer
    Left = 96
    Top = 312
  end
end
