object MainFrm: TMainFrm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'BreakModule v1.0'
  ClientHeight = 336
  ClientWidth = 351
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCloseQuery = FormCloseQuery
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label2: TLabel
    Left = 16
    Top = 16
    Width = 67
    Height = 13
    Caption = 'Module name:'
  end
  object Label1: TLabel
    Left = 16
    Top = 40
    Width = 69
    Height = 13
    Caption = 'Break on load:'
  end
  object btnAdd: TButton
    Left = 261
    Top = 11
    Width = 75
    Height = 25
    Caption = 'Add'
    TabOrder = 0
    OnClick = btnAddClick
  end
  object btnDelete: TButton
    Left = 261
    Top = 43
    Width = 75
    Height = 25
    Caption = 'Delete'
    TabOrder = 1
    OnClick = btnDeleteClick
  end
  object edtModule: TEdit
    Left = 94
    Top = 13
    Width = 163
    Height = 21
    TabOrder = 2
  end
  object GroupBox1: TGroupBox
    Left = 16
    Top = 74
    Width = 320
    Height = 247
    Caption = 'Modules to break on:'
    TabOrder = 3
  end
  object chkActive: TCheckBox
    Left = 94
    Top = 40
    Width = 97
    Height = 17
    Caption = 'Active'
    TabOrder = 4
  end
  object lstModules: TListView
    Left = 32
    Top = 96
    Width = 289
    Height = 209
    Columns = <
      item
        Caption = 'Module'
        Width = 180
      end
      item
        Caption = 'Active'
        Width = 60
      end>
    GridLines = True
    ReadOnly = True
    RowSelect = True
    PopupMenu = popmnuModules
    TabOrder = 5
    ViewStyle = vsReport
    OnSelectItem = lstModulesSelectItem
  end
  object popmnuModules: TPopupMenu
    OnPopup = popmnuModulesPopup
    Left = 144
    Top = 194
    object Activate1: TMenuItem
      Caption = 'Activate'
      OnClick = Activate1Click
    end
    object Delete1: TMenuItem
      Caption = 'Delete'
      OnClick = Delete1Click
    end
  end
end
