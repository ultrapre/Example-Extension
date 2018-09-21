#include "Extension.h"

//#define COPY_CLIPBOARD
//#define EXTRA_NEWLINES

void OnExtensionLoad() {}
void OnExtensionUnload() {}

/**
	* Param sentence: sentence received by NextHooker (UTF-16).
	* Param miscInfo: pointer to start of singly linked list containing misc info about the sentence.
	* Return value: whether the sentence was modified.
	* NextHooker will display the sentence after all extensions have had a chance to process and/or modify it.
	* THIS FUNCTION MAY BE RUN SEVERAL TIMES CONCURRENTLY: PLEASE ENSURE THAT IT IS THREAD SAFE!
*/
bool ProcessSentence(std::wstring& sentence, const InfoForExtension* miscInfo)
{
#ifdef COPY_CLIPBOARD
	// This example extension automatically copies sentences from the hook currently selected by the user into the clipboard.
	if (GetProperty("current select", miscInfo))
	{
		HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, (sentence.size() + 2) * sizeof(wchar_t));
		memcpy(GlobalLock(hMem), sentence.c_str(), (sentence.size() + 2) * sizeof(wchar_t));
		GlobalUnlock(hMem);
		OpenClipboard(0);
		EmptyClipboard();
		SetClipboardData(CF_UNICODETEXT, hMem);
		CloseClipboard();
	}
	return false;
#endif // COPY_CLIPBOARD

#ifdef EXTRA_NEWLINES
	// This example extension adds extra newlines to all sentences.
	sentence += L"\r\n";
	return true;
#endif // EXTRA_NEWLINES
}
