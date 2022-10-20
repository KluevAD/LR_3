//---------------------------------------------------------------------------

#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall ReadThread::ReadThread(bool CreateSuspended, wchar_t deviceLiteral)
	: TThread(CreateSuspended)
{
	this->myEvent = new TEvent(NULL, true, false, "", false);
	this->processThread = new ProcessThread(true, myEvent, &dataBuffer);
	this->deviceLiteral = deviceLiteral;

	FreeOnTerminate = true;
}

void __fastcall ReadThread::Execute()
{

    wchar_t deviceName[18];
	swprintf(deviceName, L"\\\\.\\%c:", deviceLiteral);

	HANDLE fileHandle = CreateFile(
		MediaType, // ��� �����/���������� (wchar*)
		GENERIC_READ, // ����� �������
		FILE_SHARE_READ, //����� ���������� ������
		NULL, // �������� ������������
		OPEN_EXISTING, //������ ��������
		FILE_ATTRIBUTE_NORMAL, //����� � ��������
		NULL
		//��������� (�������������) ����� ������� � ������� ������� GENERIC_READ
		);

	if(fileHandle == INVALID_HANDLE_VALUE)
	{
	   Synchronize(&UpdateDebugStatus_INVALID_HANDLE_VALUE);
	   CloseHandle(fileHandle);
	   return;
	}

	LARGE_INTEGER sectorOffset;
	sectorOffset.QuadPart = 0; //���������������� ������������ ������

	// ������� �������
	unsigned long currentPosition = SetFilePointer(
		  fileHandle,
		  sectorOffset.LowPart,// ������� ����� LARGE_INTEGER
		  &sectorOffset.HighPart, // ������� �����
		  FILE_BEGIN
	// ����� � �����, ������������ ������� ���������� �����������������
	// (FILE_BEGIN, FILE_CURRENT, FILE_END)
		);

	if(currentPosition != sectorOffset.LowPart)
	{
		Synchronize(&UpdateLabelErrorPosition);
		CloseHandle(fileHandle);
		return;
	}

	ProcessThread->Start();

	DWORD bytesToRead = 4096; // ������� ����� �������
	DWORD bytesRead; // ������� ������� �������


	while(true)
	{
		// ������ ������
		bool readResult = ReadFile(
			  fileHandle, // ����������
			  dataBuffer, // ���� ������ ������
			  bytesToRead,
			  &bytesRead,
			  NULL //������ ���������� ������������
			);

		if(readResult == false || bytesRead != bytesToRead)
		{
			Synchronize(&UpdateDebugStatus_ErrorbytesRead);
			Synchronize(&UpdateDebugStatus_End);
			break;
		}
		Sleep(100);
		Synchronize(&UpdateDebugStatus);

		//��������� ������ ����� � ���������� ������
		myEvent->SetEvent();

		Sleep(20);

		while (myEvent->WaitFor(0) == wrSignaled)
		{
			Sleep(10);
		}

		// ��������� ����� �� ����������
		if(Terminated) break;
	}

	CloseHandle(fileHandle);
	ProcessThread->Terminate();
	delete ProcessThreadPtr;
}

void printDebug(int colorCode, UnicodeString msg) {
	TColor colors[] = {
		clBlack, clRed, clYellow, clLime, clAqua, clBlue, clFuchsia, clWhite,
		clMaroon, clGreen, clOlive, clNavy, clPurple, clTeal, clGray, clSilver
	};

	Form1->DebugLabel->Font->Color = colors[colorCode];
	Form1->DebugLabel->Caption = msg;
}

void __fastcall ReadThread::UpdateDebugStatus()
{
	printDebug(9, "���������� ������ ��������� �������.");
}

void __fastcall ReadThread::UpdateDebugStatus_INVALID_HANDLE_VALUE()
{
	printDebug(1, "INVALID_HANDLE_VALUE.");
}

void __fastcall ReadThread::UpdateDebugStatus_ErrorPosition()
{
	printDebug(1, "Error Position.");
}

void __fastcall ReadThread::UpdateDebugStatus_ErrorbytesRead()
{
	printDebug(1, "Error bytesRead.");
}

void __fastcall ReadThread::UpdateDebugStatus_End()
{
	printDebug(9, "��������� ���������.");
}


