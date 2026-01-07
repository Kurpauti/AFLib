#include <Windows.h>

#include "AFLib.h"

// エントリーポイント
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int nCmdShow) {
	/*-AFLibを初期化-*/
	if (AFLib::Init_Lib(hInstance, nCmdShow) == -1) {
		AFLib::ShowMsgBox(L"AFLibの初期化に失敗しました。", L"エラー");
		return -1;
	}

	/*-メインループ-*/
	while (true) {
		if (AFLib::ProcMsg() == -1) break; // メッセージの処理
		AFLib::ShowMsgBox(L"Hello, AFLib!", L"タイトル1");
		AFLib::ShowMsgBox(L"Goodbye, AFLib!", L"タイトル2");
	}

	/*-AFLib-の解放処理-*/
	AFLib::Exit_Lib();
	return 0;
}