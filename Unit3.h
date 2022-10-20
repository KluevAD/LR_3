//---------------------------------------------------------------------------

#ifndef Unit3H
#define Unit3H
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class ProcessThread : public TThread
{
private:
	TEvent* myEvent;
protected:
	void __fastcall Execute();
	void __fastcall UpdateDebugStatus_Terminated();
	void __fastcall UpdateDebugStatus_Processing();
public:
	__fastcall ProcessThread(bool CreateSuspended, TEvent* myEvent, char (&dataBufferPtr)[4096]);

	char* dataBufferPtr;
};
#endif
