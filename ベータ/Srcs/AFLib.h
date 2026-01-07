#ifndef AFLIB_H
#define AFLIB_H

#include <Windows.h>

namespace AFLib {
	/*----- アプリケーション関連 -----*/

	// AFLibの初期化
	int Init_Lib(HINSTANCE hInstance, int nCmdShow);

	// AFLibの終了処理
	int Exit_Lib();

	// メッセージの処理
	int ProcMsg();

	// メッセージボックスを表示
	int ShowMsgBox(const wchar_t* mainText, const wchar_t* titleText);
}

#endif // !AFLIB_H