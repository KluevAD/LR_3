//---------------------------------------------------------------------------

#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
__fastcall ProcessThread::ProcessThread(bool CreateSuspended, TEvent* myEvent, char (&dataBufferPtr)[4096])
	: TThread(CreateSuspended)
{
	FreeOnTerminate = true;
	this->myEvent = myEvent;
	this->dataBuffer = dataBufferPtr;
}

void __fastcall ProcessThread::Execute()
{
    // ��������� ������
	while (true) {
		if (Terminated) {
			messageStatus = 0; Synchronize(&printStatus);
			break;
		}

		if (myEvent->WaitFor(0) == wrSignaled) {
			messageStatus = 1; Synchronize(&printStatus);

			// TODO ����������� ������ � ����

			// ������� ������
			// ������� ������ ReadThread � ���, ��� ������ ����������
			myEvent->ResetEvent();

			// ��������� ������������� ������
			Sleep(3000);
		}

		Sleep(20);
	}

    void printDebug(int colorCode, UnicodeString msg) {
	TColor colors[] = {
		clBlack, clRed, clYellow, clLime, clAqua, clBlue, clFuchsia, clWhite,
		clMaroon, clGreen, clOlive, clNavy, clPurple, clTeal, clGray, clSilver
	};

	Form1->DebugLabel->Font->Color = colors[colorCode];
	Form1->DebugLabel->Caption = msg;
}

	void __fastcall UpdateDebugStatus_Terminated()
	{
		printDebug(9, "����� ����������.");
	}

	void __fastcall UpdateDebugStatus_Processing()
	{
		printDebug(9, "��������� ������...");
    }
}
