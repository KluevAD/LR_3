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
	this->dataBufferPtr = dataBufferPtr;
}

void __fastcall ProcessThread::Execute()
{
    // Обработка данных
	while (true) {
		if (Terminated) {
			Synchronize(&UpdateDebugStatus_Terminated);
			break;
		}

		if (myEvent->WaitFor(0) == wrSignaled) {
			Synchronize(&UpdateDebugStatus_Processing);

			// TODO Копирование данных к себе

			// Снимаем флажок
			// Говорим потоку ReadThread о том, что данные обработаны
			myEvent->ResetEvent();

			// Обработка скопированных данных
			Sleep(3000);
		}

		Sleep(20);
	}
}

void printDebug(int colorCode, UnicodeString msg)
	{
		TColor colors[] = {
		clBlack, clRed, clYellow, clLime, clAqua, clBlue, clFuchsia, clWhite,
		clMaroon, clGreen, clOlive, clNavy, clPurple, clTeal, clGray, clSilver
		};

	Form1->DebugLabel->Font->Color = colors[colorCode];
	Form1->DebugLabel->Caption = msg;
	}

	void __fastcall ProcessThread::UpdateDebugStatus_Terminated()
	{
		printDebug(9, "Поток остановлен.");
	}

	void __fastcall ProcessThread::UpdateDebugStatus_Processing()
	{
		printDebug(9, "Обработка данных...");
	}
