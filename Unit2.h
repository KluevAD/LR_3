//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class ReadThread : public TThread
{
private:
	class ProcessThread* ProcessThreadPtr;
	TEvent* myEvent;
protected:
	void __fastcall Execute();
	void __fastcall UpdateDebugStatus();
	void __fastcall UpdateDebusStatus_INVALID_HANDLE_VALUE();
	void __fastcall UpdateDebugStatus_ErrorPosition();
	void __fastcall UpdateDebugStatus_ErrorbytesRead();
	void __fastcall UpdateDebugStatus_End();
public:
	__fastcall ReadThread(bool CreateSuspended);
	char dataBuffer[4096];
	wchar_t deviceLiteral;
};
//---------------------------------------------------------------------------
#endif
