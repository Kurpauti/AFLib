#ifndef AFLIB_H
#define AFLIB_H

#include "Windows.h"

namespace AFLib {
	// AFLibの初期化
	int AFLib_Init(HINSTANCE hInstance, int nCmdShow, int width, int height, const wchar_t* title);

	// AFLibの解放処理
	void AFLib_End();

	// メッセージ処理
	int AFLib_ProcMsg();

	// メッセージボックス
	int MsgBox(const wchar_t* text, const wchar_t* title = L"AFLib");
}

using namespace AFLib;

#endif // !AFLIB_H