; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDTODlg
LastTemplate=CView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DTO.h"

ClassCount=5
Class1=CDTOApp
Class2=CDTODlg

ResourceCount=11
Resource2=IDD_DTO_DIALOG
Resource1=IDR_MAINFRAME
Class3=DTO_info
Resource3=IDD_DIALOGBAR (English (U.S.))
Class4=DTO_einstellungen
Class5=jz
Resource4=IDD_DTO_info
Resource5=IDD_DTO_einstellungen
Resource6=IDD_FORMVIEW (English (U.S.))
Resource7=IDR_TOOLBAR1
Resource8=IDD_PROPPAGE_LARGE (English (U.S.))
Resource9=IDD_DIALOG1
Resource10=IDD_DTO_info (German (Germany))
Resource11=IDD_DTO_DIALOG (German (Germany))

[CLS:CDTOApp]
Type=0
HeaderFile=DTO.h
ImplementationFile=DTO.cpp
Filter=N
LastObject=CDTOApp

[CLS:CDTODlg]
Type=0
HeaderFile=DTODlg.h
ImplementationFile=DTODlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_info



[DLG:IDD_DTO_DIALOG]
Type=1
Class=CDTODlg
ControlCount=32
Control1=IDCANCEL,button,1342177792
Control2=IDC_EDIT_Pfad,edit,1350631552
Control3=IDC_EDIT_Jahr,edit,1350631552
Control4=IDC_EDIT_Monat,edit,1350631553
Control5=IDC_EDIT_Tag,edit,1350631553
Control6=IDC_EDIT_Typ,edit,1350631552
Control7=IDC_Ordner_erstellen,button,1342177536
Control8=IDC_CHECK_CRW,button,1342181378
Control9=IDC_dDateien_ordnen,button,1342177536
Control10=IDC_Dateien_umbenennen,button,1342177536
Control11=IDC_neu_ordnen,button,1342181120
Control12=IDC_info,button,1342177536
Control13=IDC_reinigen,button,1342177536
Control14=IDC_EDIT_Name,edit,1350631552
Control15=IDC_STATIC,static,1476395022
Control16=IDC_STATIC,static,1476395022
Control17=IDC_STATIC,static,1342177294
Control18=IDC_STATIC,static,1342177294
Control19=IDC_STATIC,static,1342177294
Control20=IDC_STATIC,static,1342177294
Control21=IDC_STATIC,static,1342177294
Control22=IDC_STATIC,static,1342177294
Control23=IDC_hilfe,button,1342243328
Control24=IDC_raw_parameter,button,1342177280
Control25=IDC_EDIT_mark1,edit,1342244994
Control26=IDC_EDIT_mark2,edit,1342244994
Control27=IDC_EDIT_mark3,edit,1342244994
Control28=IDC_EDIT_mark4,edit,1342244994
Control29=IDC_neu_erstellen,button,1342181120
Control30=IDC_STATIC,static,1342177294
Control31=IDC_EDIT_mark5,edit,1342244994
Control32=IDC_EDIT_mark6,edit,1342244994

[DLG:IDD_DTO_info]
Type=1
Class=DTO_info
ControlCount=5
Control1=IDCANCEL,button,1342177792
Control2=IDC_STATIC,static,1342177283
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342177294

[DLG:IDD_DTO_einstellungen]
Type=1
Class=DTO_einstellungen
ControlCount=28
Control1=IDCANCEL,button,1342177792
Control2=IDC_EDIT_01,edit,1350566016
Control3=IDC_EDIT_02,edit,1350566016
Control4=IDC_EDIT_03,edit,1350566016
Control5=IDC_EDIT_04,edit,1350566016
Control6=IDC_EDIT_05,edit,1350566016
Control7=IDC_CHECK_einstellungen,button,1342181378
Control8=IDC_STATIC,static,1342177294
Control9=IDC_STATIC,static,1342177294
Control10=IDC_STATIC,static,1342177294
Control11=IDC_STATIC,static,1342177294
Control12=IDC_STATIC,static,1342177294
Control13=IDC_STATIC,static,1342177294
Control14=IDC_STATIC,static,1342177294
Control15=IDC_EDIT_num_i,edit,1350566018
Control16=IDC_EDIT_num_k,edit,1350566018
Control17=IDC_STATIC,static,1342177294
Control18=IDC_STATIC,static,1342177294
Control19=IDC_EDIT_06,edit,1350566016
Control20=IDC_STATIC,static,1342177294
Control21=IDC_EDIT_2,edit,1350566017
Control22=IDC_STATIC,static,1342177294
Control23=IDC_CHECK_log,button,1342181378
Control24=IDC_CHECK_auto,button,1342181378
Control25=IDC_CHECK_view,button,1342181378
Control26=IDC_STATIC,static,1342177294
Control27=IDC_STATIC,static,1342177294
Control28=IDC_STATIC,static,1342177294

[CLS:DTO_einstellungen]
Type=0
HeaderFile=DTO_einstellungen.h
ImplementationFile=DTO_einstellungen.cpp
BaseClass=CDialog
Filter=D
LastObject=DTO_einstellungen
VirtualFilter=dWC

[CLS:DTO_info]
Type=0
HeaderFile=dto_info.h
ImplementationFile=dto_info.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=DTO_info

[CLS:jz]
Type=0
HeaderFile=jz.h
ImplementationFile=jz.cpp
BaseClass=CView
Filter=C
LastObject=jz

[DLG:IDD_DIALOG1]
Type=1
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342177286
Control4=AFX_IDC_PICTURE,static,1342177285

[DLG:IDD_FORMVIEW (English (U.S.))]
Type=1
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[TB:IDR_TOOLBAR1]
Type=1
Command1=ID_BUTTON32771
Command2=VS_VERSION_INFO
Command3=ID_BUTTON32773
Command4=ID_BUTTON32774
CommandCount=4

[DLG:IDD_PROPPAGE_LARGE (English (U.S.))]
Type=1
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOGBAR (English (U.S.))]
Type=1
ControlCount=2
Control1=IDC_STATIC,static,1342308352
Control2=AFX_IDC_PICTURE,static,1342177286

[DLG:IDD_DTO_info (German (Germany))]
Type=1
ControlCount=5
Control1=IDCANCEL,button,1342177792
Control2=IDC_STATIC,static,1342177283
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342177294

[DLG:IDD_DTO_DIALOG (German (Germany))]
Type=1
ControlCount=32
Control1=IDCANCEL,button,1342177792
Control2=IDC_EDIT_Pfad,edit,1350631552
Control3=IDC_EDIT_Jahr,edit,1350631552
Control4=IDC_EDIT_Monat,edit,1350631553
Control5=IDC_EDIT_Tag,edit,1350631553
Control6=IDC_EDIT_Typ,edit,1350631552
Control7=IDC_Ordner_erstellen,button,1342177536
Control8=IDC_CHECK_CRW,button,1342181378
Control9=IDC_dDateien_ordnen,button,1342177536
Control10=IDC_Dateien_umbenennen,button,1342177536
Control11=IDC_neu_ordnen,button,1342181120
Control12=IDC_info,button,1342177536
Control13=IDC_reinigen,button,1342177536
Control14=IDC_EDIT_Name,edit,1350631552
Control15=IDC_STATIC,static,1476395022
Control16=IDC_STATIC,static,1476395022
Control17=IDC_STATIC,static,1342177294
Control18=IDC_STATIC,static,1342177294
Control19=IDC_STATIC,static,1342177294
Control20=IDC_STATIC,static,1342177294
Control21=IDC_STATIC,static,1342177294
Control22=IDC_STATIC,static,1342177294
Control23=IDC_hilfe,button,1342243328
Control24=IDC_raw_parameter,button,1342177280
Control25=IDC_EDIT_mark1,edit,1342244994
Control26=IDC_EDIT_mark2,edit,1342244994
Control27=IDC_EDIT_mark3,edit,1342244994
Control28=IDC_EDIT_mark4,edit,1342244994
Control29=IDC_neu_erstellen,button,1342181120
Control30=IDC_STATIC,static,1342177294
Control31=IDC_EDIT_mark5,edit,1342244994
Control32=IDC_EDIT_mark6,edit,1342244994

