object frmMancal: TfrmMancal
  Left = 824
  Top = 193
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'ER - Temperaturas dos Mancais'
  ClientHeight = 523
  ClientWidth = 618
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object pnlMODPRI: TPanel
    Left = 10
    Top = 10
    Width = 600
    Height = 450
    Caption = 'pnlMODPRI'
    TabOrder = 2
    object Shape3: TShape
      Left = 3
      Top = 8
      Width = 361
      Height = 385
      Brush.Style = bsClear
      Pen.Color = clNavy
      Pen.Width = 3
    end
    object Label14: TLabel
      Left = 11
      Top = 32
      Width = 83
      Height = 13
      Caption = 'Temp. Mancal 01'
    end
    object lblMODPRI_TEMPMANCAL1: TLabel
      Left = 155
      Top = 32
      Width = 12
      Height = 13
      Alignment = taRightJustify
      Caption = '50'
    end
    object lblInit1: TLabel
      Left = 11
      Top = 16
      Width = 40
      Height = 13
      Caption = 'lblInitX'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label22: TLabel
      Left = 11
      Top = 104
      Width = 83
      Height = 13
      Caption = 'Temp. Mancal 03'
    end
    object lblMODPRI_TEMPMANCAL3: TLabel
      Left = 155
      Top = 104
      Width = 12
      Height = 13
      Alignment = taRightJustify
      Caption = '50'
    end
    object Label24: TLabel
      Left = 11
      Top = 176
      Width = 83
      Height = 13
      Caption = 'Temp. Mancal 05'
    end
    object lblMODPRI_TEMPMANCAL5: TLabel
      Left = 155
      Top = 176
      Width = 12
      Height = 13
      Alignment = taRightJustify
      Caption = '50'
    end
    object Label26: TLabel
      Left = 11
      Top = 248
      Width = 83
      Height = 13
      Caption = 'Temp. Mancal 07'
    end
    object lblMODPRI_TEMPMANCAL7: TLabel
      Left = 155
      Top = 248
      Width = 12
      Height = 13
      Alignment = taRightJustify
      Caption = '50'
    end
    object Label29: TLabel
      Left = 195
      Top = 32
      Width = 83
      Height = 13
      Caption = 'Temp. Mancal 02'
    end
    object lblMODPRI_TEMPMANCAL2: TLabel
      Left = 344
      Top = 32
      Width = 12
      Height = 13
      Alignment = taRightJustify
      Caption = '50'
    end
    object Label31: TLabel
      Left = 195
      Top = 104
      Width = 83
      Height = 13
      Caption = 'Temp. Mancal 04'
    end
    object lblMODPRI_TEMPMANCAL4: TLabel
      Left = 344
      Top = 104
      Width = 12
      Height = 13
      Alignment = taRightJustify
      Caption = '50'
    end
    object Label33: TLabel
      Left = 195
      Top = 176
      Width = 83
      Height = 13
      Caption = 'Temp. Mancal 06'
    end
    object lblMODPRI_TEMPMANCAL6: TLabel
      Left = 344
      Top = 176
      Width = 12
      Height = 13
      Alignment = taRightJustify
      Caption = '50'
    end
    object Label35: TLabel
      Left = 195
      Top = 248
      Width = 83
      Height = 13
      Caption = 'Temp. Mancal 08'
    end
    object lblMODPRI_TEMPMANCAL8: TLabel
      Left = 344
      Top = 248
      Width = 12
      Height = 13
      Alignment = taRightJustify
      Caption = '50'
    end
    object Label1: TLabel
      Left = 11
      Top = 320
      Width = 83
      Height = 13
      Caption = 'Temp. Mancal 09'
    end
    object lblMODPRI_TEMPMANCAL9: TLabel
      Left = 155
      Top = 320
      Width = 12
      Height = 13
      Alignment = taRightJustify
      Caption = '50'
    end
    object Label3: TLabel
      Left = 195
      Top = 320
      Width = 83
      Height = 13
      Caption = 'Temp. Mancal 10'
    end
    object lblMODPRI_TEMPMANCAL10: TLabel
      Left = 344
      Top = 320
      Width = 12
      Height = 13
      Alignment = taRightJustify
      Caption = '50'
    end
    object prbMODPRI_TEMPMANCAL1: TProgressBar
      Left = 11
      Top = 48
      Width = 161
      Height = 17
      Min = 0
      Max = 100
      Step = 1
      TabOrder = 0
    end
    object txtMODPRI_TEMPMANCAL1: TEdit
      Left = 11
      Top = 72
      Width = 49
      Height = 21
      TabOrder = 1
      Text = '0'
    end
    object btnMODPRI_TEMPMANCAL1: TButton
      Left = 67
      Top = 72
      Width = 106
      Height = 17
      Caption = 'Escrever Nível'
      TabOrder = 2
      OnClick = btnMODPRI_TEMPMANCAL1Click
    end
    object prbMODPRI_TEMPMANCAL3: TProgressBar
      Left = 11
      Top = 120
      Width = 161
      Height = 17
      Min = 0
      Max = 100
      Step = 1
      TabOrder = 3
    end
    object txtMODPRI_TEMPMANCAL3: TEdit
      Left = 11
      Top = 144
      Width = 49
      Height = 21
      TabOrder = 4
      Text = '0'
    end
    object btnMODPRI_TEMPMANCAL3: TButton
      Left = 67
      Top = 144
      Width = 106
      Height = 17
      Caption = 'Escrever Nível'
      TabOrder = 5
      OnClick = btnMODPRI_TEMPMANCAL3Click
    end
    object prbMODPRI_TEMPMANCAL5: TProgressBar
      Left = 11
      Top = 192
      Width = 161
      Height = 17
      Min = 0
      Max = 100
      Step = 1
      TabOrder = 6
    end
    object txtMODPRI_TEMPMANCAL5: TEdit
      Left = 11
      Top = 216
      Width = 49
      Height = 21
      TabOrder = 7
      Text = '0'
    end
    object btnMODPRI_TEMPMANCAL5: TButton
      Left = 67
      Top = 216
      Width = 106
      Height = 17
      Caption = 'Escrever Nível'
      TabOrder = 8
      OnClick = btnMODPRI_TEMPMANCAL5Click
    end
    object prbMODPRI_TEMPMANCAL7: TProgressBar
      Left = 11
      Top = 264
      Width = 161
      Height = 17
      Min = 0
      Max = 100
      Step = 1
      TabOrder = 9
    end
    object txtMODPRI_TEMPMANCAL7: TEdit
      Left = 11
      Top = 288
      Width = 49
      Height = 21
      TabOrder = 10
      Text = '0'
    end
    object btnMODPRI_TEMPMANCAL7: TButton
      Left = 67
      Top = 288
      Width = 106
      Height = 17
      Caption = 'Escrever Nível'
      TabOrder = 11
      OnClick = btnMODPRI_TEMPMANCAL7Click
    end
    object prbMODPRI_TEMPMANCAL2: TProgressBar
      Left = 195
      Top = 48
      Width = 161
      Height = 17
      Min = 0
      Max = 100
      Step = 1
      TabOrder = 12
    end
    object txtMODPRI_TEMPMANCAL2: TEdit
      Left = 195
      Top = 72
      Width = 49
      Height = 21
      TabOrder = 13
      Text = '0'
    end
    object btnMODPRI_TEMPMANCAL2: TButton
      Left = 250
      Top = 72
      Width = 106
      Height = 17
      Caption = 'Escrever Nível'
      TabOrder = 14
      OnClick = btnMODPRI_TEMPMANCAL2Click
    end
    object prbMODPRI_TEMPMANCAL4: TProgressBar
      Left = 195
      Top = 120
      Width = 161
      Height = 17
      Min = 0
      Max = 100
      Step = 1
      TabOrder = 15
    end
    object txtMODPRI_TEMPMANCAL4: TEdit
      Left = 195
      Top = 144
      Width = 49
      Height = 21
      TabOrder = 16
      Text = '0'
    end
    object btnMODPRI_TEMPMANCAL4: TButton
      Left = 250
      Top = 144
      Width = 106
      Height = 17
      Caption = 'Escrever Nível'
      TabOrder = 17
      OnClick = btnMODPRI_TEMPMANCAL4Click
    end
    object prbMODPRI_TEMPMANCAL6: TProgressBar
      Left = 195
      Top = 192
      Width = 161
      Height = 17
      Min = 0
      Max = 100
      Step = 1
      TabOrder = 18
    end
    object txtMODPRI_TEMPMANCAL6: TEdit
      Left = 195
      Top = 216
      Width = 49
      Height = 21
      TabOrder = 19
      Text = '0'
    end
    object btnMODPRI_TEMPMANCAL6: TButton
      Left = 250
      Top = 216
      Width = 106
      Height = 17
      Caption = 'Escrever Nível'
      TabOrder = 20
      OnClick = btnMODPRI_TEMPMANCAL6Click
    end
    object prbMODPRI_TEMPMANCAL8: TProgressBar
      Left = 195
      Top = 264
      Width = 161
      Height = 17
      Min = 0
      Max = 100
      Step = 1
      TabOrder = 21
    end
    object txtMODPRI_TEMPMANCAL8: TEdit
      Left = 195
      Top = 288
      Width = 49
      Height = 21
      TabOrder = 22
      Text = '0'
    end
    object btnMODPRI_TEMPMANCAL8: TButton
      Left = 250
      Top = 288
      Width = 106
      Height = 17
      Caption = 'Escrever Nível'
      TabOrder = 23
      OnClick = btnMODPRI_TEMPMANCAL8Click
    end
    object prbMODPRI_TEMPMANCAL9: TProgressBar
      Left = 11
      Top = 336
      Width = 161
      Height = 17
      Min = 0
      Max = 100
      Step = 1
      TabOrder = 24
    end
    object txtMODPRI_TEMPMANCAL9: TEdit
      Left = 11
      Top = 360
      Width = 49
      Height = 21
      TabOrder = 25
      Text = '0'
    end
    object btnMODPRI_TEMPMANCAL9: TButton
      Left = 67
      Top = 360
      Width = 106
      Height = 17
      Caption = 'Escrever Nível'
      TabOrder = 26
      OnClick = btnMODPRI_TEMPMANCAL9Click
    end
    object prbMODPRI_TEMPMANCAL10: TProgressBar
      Left = 195
      Top = 336
      Width = 161
      Height = 17
      Min = 0
      Max = 100
      Step = 1
      TabOrder = 27
    end
    object txtMODPRI_TEMPMANCAL10: TEdit
      Left = 195
      Top = 360
      Width = 49
      Height = 21
      TabOrder = 28
      Text = '0'
    end
    object btnMODPRI_TEMPMANCAL10: TButton
      Left = 250
      Top = 360
      Width = 106
      Height = 17
      Caption = 'Escrever Nível'
      TabOrder = 29
      OnClick = btnMODPRI_TEMPMANCAL10Click
    end
  end
  object pnlMODSBE: TPanel
    Left = 10
    Top = 10
    Width = 600
    Height = 450
    Caption = 'pnlMODSBE'
    TabOrder = 1
    object Shape2: TShape
      Left = 3
      Top = 8
      Width = 361
      Height = 313
      Brush.Style = bsClear
      Pen.Color = clNavy
      Pen.Width = 3
    end
    object Label39: TLabel
      Left = 8
      Top = 32
      Width = 83
      Height = 13
      Caption = 'Temp. Mancal 01'
    end
    object lblMODSBE_TEMPMANCAL1: TLabel
      Left = 152
      Top = 32
      Width = 12
      Height = 13
      Alignment = taRightJustify
      Caption = '50'
    end
    object lblInit3: TLabel
      Left = 8
      Top = 16
      Width = 40
      Height = 13
      Caption = 'lblInitX'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label42: TLabel
      Left = 8
      Top = 104
      Width = 83
      Height = 13
      Caption = 'Temp. Mancal 03'
    end
    object lblMODSBE_TEMPMANCAL3: TLabel
      Left = 152
      Top = 104
      Width = 12
      Height = 13
      Alignment = taRightJustify
      Caption = '50'
    end
    object Label44: TLabel
      Left = 8
      Top = 176
      Width = 83
      Height = 13
      Caption = 'Temp. Mancal 05'
    end
    object lblMODSBE_TEMPMANCAL5: TLabel
      Left = 152
      Top = 176
      Width = 12
      Height = 13
      Alignment = taRightJustify
      Caption = '50'
    end
    object Label46: TLabel
      Left = 8
      Top = 248
      Width = 83
      Height = 13
      Caption = 'Temp. Mancal 07'
    end
    object lblMODSBE_TEMPMANCAL7: TLabel
      Left = 152
      Top = 248
      Width = 12
      Height = 13
      Alignment = taRightJustify
      Caption = '50'
    end
    object Label48: TLabel
      Left = 192
      Top = 32
      Width = 83
      Height = 13
      Caption = 'Temp. Mancal 02'
    end
    object lblMODSBE_TEMPMANCAL2: TLabel
      Left = 344
      Top = 32
      Width = 12
      Height = 13
      Alignment = taRightJustify
      Caption = '50'
    end
    object Label50: TLabel
      Left = 192
      Top = 104
      Width = 83
      Height = 13
      Caption = 'Temp. Mancal 04'
    end
    object lblMODSBE_TEMPMANCAL4: TLabel
      Left = 344
      Top = 104
      Width = 12
      Height = 13
      Alignment = taRightJustify
      Caption = '50'
    end
    object Label52: TLabel
      Left = 192
      Top = 176
      Width = 83
      Height = 13
      Caption = 'Temp. Mancal 06'
    end
    object lblMODSBE_TEMPMANCAL6: TLabel
      Left = 344
      Top = 176
      Width = 12
      Height = 13
      Alignment = taRightJustify
      Caption = '50'
    end
    object Label54: TLabel
      Left = 192
      Top = 248
      Width = 83
      Height = 13
      Caption = 'Temp. Mancal 08'
    end
    object lblMODSBE_TEMPMANCAL8: TLabel
      Left = 344
      Top = 248
      Width = 12
      Height = 13
      Alignment = taRightJustify
      Caption = '50'
    end
    object prbMODSBE_TEMPMANCAL1: TProgressBar
      Left = 8
      Top = 48
      Width = 161
      Height = 17
      Min = 0
      Max = 100
      Step = 1
      TabOrder = 0
    end
    object txtMODSBE_TEMPMANCAL1: TEdit
      Left = 8
      Top = 72
      Width = 49
      Height = 21
      TabOrder = 1
      Text = '0'
    end
    object btnMODSBE_TEMPMANCAL1: TButton
      Left = 64
      Top = 72
      Width = 106
      Height = 17
      Caption = 'Escrever Nível'
      TabOrder = 2
      OnClick = btnMODSBE_TEMPMANCAL1Click
    end
    object prbMODSBE_TEMPMANCAL3: TProgressBar
      Left = 8
      Top = 120
      Width = 161
      Height = 17
      Min = 0
      Max = 100
      Step = 1
      TabOrder = 3
    end
    object txtMODSBE_TEMPMANCAL3: TEdit
      Left = 8
      Top = 144
      Width = 49
      Height = 21
      TabOrder = 4
      Text = '0'
    end
    object btnMODSBE_TEMPMANCAL3: TButton
      Left = 64
      Top = 144
      Width = 106
      Height = 17
      Caption = 'Escrever Nível'
      TabOrder = 5
      OnClick = btnMODSBE_TEMPMANCAL3Click
    end
    object prbMODSBE_TEMPMANCAL5: TProgressBar
      Left = 8
      Top = 192
      Width = 161
      Height = 17
      Min = 0
      Max = 100
      Step = 1
      TabOrder = 6
    end
    object txtMODSBE_TEMPMANCAL5: TEdit
      Left = 8
      Top = 216
      Width = 49
      Height = 21
      TabOrder = 7
      Text = '0'
    end
    object btnMODSBE_TEMPMANCAL5: TButton
      Left = 64
      Top = 216
      Width = 106
      Height = 17
      Caption = 'Escrever Nível'
      TabOrder = 8
      OnClick = btnMODSBE_TEMPMANCAL5Click
    end
    object prbMODSBE_TEMPMANCAL7: TProgressBar
      Left = 8
      Top = 264
      Width = 161
      Height = 17
      Min = 0
      Max = 100
      Step = 1
      TabOrder = 9
    end
    object txtMODSBE_TEMPMANCAL7: TEdit
      Left = 8
      Top = 288
      Width = 49
      Height = 21
      TabOrder = 10
      Text = '0'
    end
    object btnMODSBE_TEMPMANCAL7: TButton
      Left = 64
      Top = 288
      Width = 106
      Height = 17
      Caption = 'Escrever Nível'
      TabOrder = 11
      OnClick = btnMODSBE_TEMPMANCAL7Click
    end
    object prbMODSBE_TEMPMANCAL2: TProgressBar
      Left = 195
      Top = 48
      Width = 161
      Height = 17
      Min = 0
      Max = 100
      Step = 1
      TabOrder = 12
    end
    object txtMODSBE_TEMPMANCAL2: TEdit
      Left = 192
      Top = 72
      Width = 49
      Height = 21
      TabOrder = 13
      Text = '0'
    end
    object btnMODSBE_TEMPMANCAL2: TButton
      Left = 250
      Top = 72
      Width = 106
      Height = 17
      Caption = 'Escrever Nível'
      TabOrder = 14
      OnClick = btnMODSBE_TEMPMANCAL2Click
    end
    object prbMODSBE_TEMPMANCAL4: TProgressBar
      Left = 195
      Top = 120
      Width = 161
      Height = 17
      Min = 0
      Max = 100
      Step = 1
      TabOrder = 15
    end
    object txtMODSBE_TEMPMANCAL4: TEdit
      Left = 192
      Top = 144
      Width = 49
      Height = 21
      TabOrder = 16
      Text = '0'
    end
    object btnMODSBE_TEMPMANCAL4: TButton
      Left = 250
      Top = 144
      Width = 106
      Height = 17
      Caption = 'Escrever Nível'
      TabOrder = 17
      OnClick = btnMODSBE_TEMPMANCAL4Click
    end
    object prbMODSBE_TEMPMANCAL6: TProgressBar
      Left = 195
      Top = 192
      Width = 161
      Height = 17
      Min = 0
      Max = 100
      Step = 1
      TabOrder = 18
    end
    object txtMODSBE_TEMPMANCAL6: TEdit
      Left = 192
      Top = 216
      Width = 49
      Height = 21
      TabOrder = 19
      Text = '0'
    end
    object btnMODSBE_TEMPMANCAL6: TButton
      Left = 250
      Top = 216
      Width = 106
      Height = 17
      Caption = 'Escrever Nível'
      TabOrder = 20
      OnClick = btnMODSBE_TEMPMANCAL6Click
    end
    object prbMODSBE_TEMPMANCAL8: TProgressBar
      Left = 195
      Top = 264
      Width = 161
      Height = 17
      Min = 0
      Max = 100
      Step = 1
      TabOrder = 21
    end
    object txtMODSBE_TEMPMANCAL8: TEdit
      Left = 192
      Top = 288
      Width = 49
      Height = 21
      TabOrder = 22
      Text = '0'
    end
    object btnMODSBE_TEMPMANCAL8: TButton
      Left = 250
      Top = 288
      Width = 106
      Height = 17
      Caption = 'Escrever Nível'
      TabOrder = 23
      OnClick = btnMODSBE_TEMPMANCAL8Click
    end
  end
  object pnlMODSBB: TPanel
    Left = 10
    Top = 10
    Width = 600
    Height = 450
    Caption = 'pnlMODSBB'
    TabOrder = 0
    object Shape1: TShape
      Left = 3
      Top = 8
      Width = 361
      Height = 313
      Brush.Style = bsClear
      Pen.Color = clNavy
      Pen.Width = 3
    end
    object Label5: TLabel
      Left = 8
      Top = 32
      Width = 83
      Height = 13
      Caption = 'Temp. Mancal 01'
    end
    object lblMODSBB_TEMPMANCAL1: TLabel
      Left = 152
      Top = 32
      Width = 12
      Height = 13
      Alignment = taRightJustify
      Caption = '50'
    end
    object lblInit2: TLabel
      Left = 8
      Top = 16
      Width = 40
      Height = 13
      Caption = 'lblInitX'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label8: TLabel
      Left = 8
      Top = 104
      Width = 83
      Height = 13
      Caption = 'Temp. Mancal 03'
    end
    object lblMODSBB_TEMPMANCAL3: TLabel
      Left = 152
      Top = 104
      Width = 12
      Height = 13
      Alignment = taRightJustify
      Caption = '50'
    end
    object Label10: TLabel
      Left = 8
      Top = 176
      Width = 83
      Height = 13
      Caption = 'Temp. Mancal 05'
    end
    object lblMODSBB_TEMPMANCAL5: TLabel
      Left = 152
      Top = 176
      Width = 12
      Height = 13
      Alignment = taRightJustify
      Caption = '50'
    end
    object Label12: TLabel
      Left = 8
      Top = 248
      Width = 83
      Height = 13
      Caption = 'Temp. Mancal 07'
    end
    object lblMODSBB_TEMPMANCAL7: TLabel
      Left = 152
      Top = 248
      Width = 12
      Height = 13
      Alignment = taRightJustify
      Caption = '50'
    end
    object Label15: TLabel
      Left = 192
      Top = 32
      Width = 83
      Height = 13
      Caption = 'Temp. Mancal 02'
    end
    object lblMODSBB_TEMPMANCAL2: TLabel
      Left = 344
      Top = 32
      Width = 12
      Height = 13
      Alignment = taRightJustify
      Caption = '50'
    end
    object Label17: TLabel
      Left = 192
      Top = 104
      Width = 83
      Height = 13
      Caption = 'Temp. Mancal 04'
    end
    object lblMODSBB_TEMPMANCAL4: TLabel
      Left = 344
      Top = 104
      Width = 12
      Height = 13
      Alignment = taRightJustify
      Caption = '50'
    end
    object Label20: TLabel
      Left = 192
      Top = 176
      Width = 83
      Height = 13
      Caption = 'Temp. Mancal 06'
    end
    object lblMODSBB_TEMPMANCAL6: TLabel
      Left = 344
      Top = 176
      Width = 12
      Height = 13
      Alignment = taRightJustify
      Caption = '50'
    end
    object Label37: TLabel
      Left = 192
      Top = 248
      Width = 83
      Height = 13
      Caption = 'Temp. Mancal 08'
    end
    object lblMODSBB_TEMPMANCAL8: TLabel
      Left = 344
      Top = 248
      Width = 12
      Height = 13
      Alignment = taRightJustify
      Caption = '50'
    end
    object prbMODSBB_TEMPMANCAL1: TProgressBar
      Left = 8
      Top = 48
      Width = 161
      Height = 17
      Min = 0
      Max = 100
      Step = 1
      TabOrder = 0
    end
    object txtMODSBB_TEMPMANCAL1: TEdit
      Left = 8
      Top = 72
      Width = 49
      Height = 21
      TabOrder = 1
      Text = '0'
    end
    object btnMODSBB_TEMPMANCAL1: TButton
      Left = 64
      Top = 72
      Width = 106
      Height = 17
      Caption = 'Escrever Nível'
      TabOrder = 2
      OnClick = btnMODSBB_TEMPMANCAL1Click
    end
    object prbMODSBB_TEMPMANCAL3: TProgressBar
      Left = 8
      Top = 120
      Width = 161
      Height = 17
      Min = 0
      Max = 100
      Step = 1
      TabOrder = 3
    end
    object txtMODSBB_TEMPMANCAL3: TEdit
      Left = 8
      Top = 144
      Width = 49
      Height = 21
      TabOrder = 4
      Text = '0'
    end
    object btnMODSBB_TEMPMANCAL3: TButton
      Left = 64
      Top = 144
      Width = 106
      Height = 17
      Caption = 'Escrever Nível'
      TabOrder = 5
      OnClick = btnMODSBB_TEMPMANCAL3Click
    end
    object prbMODSBB_TEMPMANCAL5: TProgressBar
      Left = 8
      Top = 192
      Width = 161
      Height = 17
      Min = 0
      Max = 100
      Step = 1
      TabOrder = 6
    end
    object txtMODSBB_TEMPMANCAL5: TEdit
      Left = 8
      Top = 216
      Width = 49
      Height = 21
      TabOrder = 7
      Text = '0'
    end
    object btnMODSBB_TEMPMANCAL5: TButton
      Left = 64
      Top = 216
      Width = 106
      Height = 17
      Caption = 'Escrever Nível'
      TabOrder = 8
      OnClick = btnMODSBB_TEMPMANCAL5Click
    end
    object prbMODSBB_TEMPMANCAL7: TProgressBar
      Left = 8
      Top = 264
      Width = 161
      Height = 17
      Min = 0
      Max = 100
      Step = 1
      TabOrder = 9
    end
    object txtMODSBB_TEMPMANCAL7: TEdit
      Left = 8
      Top = 288
      Width = 49
      Height = 21
      TabOrder = 10
      Text = '0'
    end
    object btnMODSBB_TEMPMANCAL7: TButton
      Left = 64
      Top = 288
      Width = 106
      Height = 17
      Caption = 'Escrever Nível'
      TabOrder = 11
      OnClick = btnMODSBB_TEMPMANCAL7Click
    end
    object prbMODSBB_TEMPMANCAL2: TProgressBar
      Left = 195
      Top = 48
      Width = 161
      Height = 17
      Min = 0
      Max = 100
      Step = 1
      TabOrder = 12
    end
    object txtMODSBB_TEMPMANCAL2: TEdit
      Left = 192
      Top = 72
      Width = 49
      Height = 21
      TabOrder = 13
      Text = '0'
    end
    object btnMODSBB_TEMPMANCAL2: TButton
      Left = 250
      Top = 72
      Width = 106
      Height = 17
      Caption = 'Escrever Nível'
      TabOrder = 14
      OnClick = btnMODSBB_TEMPMANCAL2Click
    end
    object prbMODSBB_TEMPMANCAL4: TProgressBar
      Left = 195
      Top = 120
      Width = 161
      Height = 17
      Min = 0
      Max = 100
      Step = 1
      TabOrder = 15
    end
    object txtMODSBB_TEMPMANCAL4: TEdit
      Left = 192
      Top = 144
      Width = 49
      Height = 21
      TabOrder = 16
      Text = '0'
    end
    object btnMODSBB_TEMPMANCAL4: TButton
      Left = 250
      Top = 144
      Width = 106
      Height = 17
      Caption = 'Escrever Nível'
      TabOrder = 17
      OnClick = btnMODSBB_TEMPMANCAL4Click
    end
    object prbMODSBB_TEMPMANCAL6: TProgressBar
      Left = 195
      Top = 192
      Width = 161
      Height = 17
      Min = 0
      Max = 100
      Step = 1
      TabOrder = 18
    end
    object txtMODSBB_TEMPMANCAL6: TEdit
      Left = 192
      Top = 216
      Width = 49
      Height = 21
      TabOrder = 19
      Text = '0'
    end
    object btnMODSBB_TEMPMANCAL6: TButton
      Left = 250
      Top = 216
      Width = 106
      Height = 17
      Caption = 'Escrever Nível'
      TabOrder = 20
      OnClick = btnMODSBB_TEMPMANCAL6Click
    end
    object prbMODSBB_TEMPMANCAL8: TProgressBar
      Left = 195
      Top = 264
      Width = 161
      Height = 17
      Min = 0
      Max = 100
      Step = 1
      TabOrder = 21
    end
    object txtMODSBB_TEMPMANCAL8: TEdit
      Left = 192
      Top = 288
      Width = 49
      Height = 21
      TabOrder = 22
      Text = '0'
    end
    object btnMODSBB_TEMPMANCAL8: TButton
      Left = 250
      Top = 288
      Width = 106
      Height = 17
      Caption = 'Escrever Nível'
      TabOrder = 23
      OnClick = btnMODSBB_TEMPMANCAL8Click
    end
  end
  object pnlEixos: TPanel
    Left = 10
    Top = 10
    Width = 600
    Height = 450
    TabOrder = 3
    object Shape4: TShape
      Left = 3
      Top = 8
      Width = 361
      Height = 97
      Brush.Style = bsClear
      Pen.Color = clNavy
      Pen.Width = 3
    end
    object lblInit4: TLabel
      Left = 8
      Top = 16
      Width = 40
      Height = 13
      Caption = 'lblInitX'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label4: TLabel
      Left = 8
      Top = 32
      Width = 114
      Height = 13
      Caption = 'Temp. Linha de Eixo AV'
    end
    object lblBB_MLEAV_TEMP: TLabel
      Left = 160
      Top = 32
      Width = 12
      Height = 13
      Alignment = taRightJustify
      Caption = '50'
    end
    object Label7: TLabel
      Left = 192
      Top = 32
      Width = 115
      Height = 13
      Caption = 'Temp. Linha de Eixo AR'
    end
    object lblBB_MLEAR_TEMP: TLabel
      Left = 344
      Top = 32
      Width = 12
      Height = 13
      Alignment = taRightJustify
      Caption = '50'
    end
    object Shape5: TShape
      Left = 3
      Top = 112
      Width = 361
      Height = 97
      Brush.Style = bsClear
      Pen.Color = clNavy
      Pen.Width = 3
    end
    object lblInit5: TLabel
      Left = 8
      Top = 120
      Width = 40
      Height = 13
      Caption = 'lblInitX'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label13: TLabel
      Left = 8
      Top = 136
      Width = 114
      Height = 13
      Caption = 'Temp. Linha de Eixo AV'
    end
    object lblBE_MLEAV_TEMP: TLabel
      Left = 152
      Top = 136
      Width = 12
      Height = 13
      Alignment = taRightJustify
      Caption = '50'
    end
    object Label18: TLabel
      Left = 192
      Top = 136
      Width = 115
      Height = 13
      Caption = 'Temp. Linha de Eixo AR'
    end
    object lblBE_MLEAR_TEMP: TLabel
      Left = 344
      Top = 136
      Width = 12
      Height = 13
      Alignment = taRightJustify
      Caption = '50'
    end
    object prbBB_MLEAV_TEMP: TProgressBar
      Left = 8
      Top = 48
      Width = 161
      Height = 17
      Min = 0
      Max = 100
      Step = 1
      TabOrder = 0
    end
    object txtBB_MLEAV_TEMP: TEdit
      Left = 8
      Top = 72
      Width = 49
      Height = 21
      TabOrder = 1
      Text = '0'
    end
    object btnBB_MLEAV_TEMP: TButton
      Left = 64
      Top = 72
      Width = 106
      Height = 17
      Caption = 'Escrever Nível'
      TabOrder = 2
      OnClick = btnBB_MLEAV_TEMPClick
    end
    object prbBB_MLEAR_TEMP: TProgressBar
      Left = 195
      Top = 48
      Width = 161
      Height = 17
      Min = 0
      Max = 100
      Step = 1
      TabOrder = 3
    end
    object txtBB_MLEAR_TEMP: TEdit
      Left = 192
      Top = 72
      Width = 49
      Height = 21
      TabOrder = 4
      Text = '0'
    end
    object btnBB_MLEAR_TEMP: TButton
      Left = 250
      Top = 72
      Width = 106
      Height = 17
      Caption = 'Escrever Nível'
      TabOrder = 5
      OnClick = btnBB_MLEAR_TEMPClick
    end
    object prbBE_MLEAV_TEMP: TProgressBar
      Left = 8
      Top = 152
      Width = 161
      Height = 17
      Min = 0
      Max = 100
      Step = 1
      TabOrder = 6
    end
    object txtBE_MLEAV_TEMP: TEdit
      Left = 8
      Top = 176
      Width = 49
      Height = 21
      TabOrder = 7
      Text = '0'
    end
    object btnBE_MLEAV_TEMP: TButton
      Left = 64
      Top = 176
      Width = 106
      Height = 17
      Caption = 'Escrever Nível'
      TabOrder = 8
      OnClick = btnBE_MLEAV_TEMPClick
    end
    object prbBE_MLEAR_TEMP: TProgressBar
      Left = 195
      Top = 152
      Width = 161
      Height = 17
      Min = 0
      Max = 100
      Step = 1
      TabOrder = 9
    end
    object txtBE_MLEAR_TEMP: TEdit
      Left = 192
      Top = 176
      Width = 49
      Height = 21
      TabOrder = 10
      Text = '0'
    end
    object btnBE_MLEAR_TEMP: TButton
      Left = 250
      Top = 176
      Width = 106
      Height = 17
      Caption = 'Escrever Nível'
      TabOrder = 11
      OnClick = btnBE_MLEAR_TEMPClick
    end
  end
  object btnMODSBB: TButton
    Left = 8
    Top = 464
    Width = 120
    Height = 57
    Caption = 'MOD. SEC. BB'
    TabOrder = 4
    OnClick = btnMODSBBClick
  end
  object btnMODPRI: TButton
    Left = 136
    Top = 464
    Width = 120
    Height = 57
    Caption = 'MOD. PRIM.'
    TabOrder = 5
    OnClick = btnMODPRIClick
  end
  object btnEIXOS: TButton
    Left = 264
    Top = 464
    Width = 120
    Height = 57
    Caption = 'MANC. ESCORAS'
    TabOrder = 6
    OnClick = btnEIXOSClick
  end
  object btnMODSBE: TButton
    Left = 392
    Top = 464
    Width = 120
    Height = 57
    Caption = 'MOD. SEC. BE'
    TabOrder = 7
    OnClick = btnMODSBEClick
  end
  object btnFechar: TButton
    Left = 520
    Top = 464
    Width = 89
    Height = 57
    Caption = 'FECHAR'
    TabOrder = 8
    OnClick = btnFecharClick
  end
end
