//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	#Считывание буквы диска
	UnicodeString deviceName = ChooseDeviceEdit->Text;
	wchar_t deviceLiteral = deviceName.w_str()[0];

	#Запуск потока
	readThread = new ReadThread(false, deviceLiteral);
	Button1->Enabled = false;
	Button2->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	Button1->Enabled = true;
	Button2->Enabled = false;
	readThread->Terminate();
}
//---------------------------------------------------------------------------
