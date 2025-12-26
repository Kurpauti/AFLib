#include <Windows.h>

#include "AFLib.h"

// エントリーポイント
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int nCmdShow) {
	/*-AFLibを初期化-*/
	if (AFLib_Init(hInstance, nCmdShow, 1080, 780, L"Sample 3D Game") == -1) {
		MsgBox(L"AFLibの初期化に失敗しました");
		return -1;
	}

	/*-メインループ-*/
	while (true) {
		if (AFLib_ProcMsg() == -1) break;
		MsgBox(L"実行成功1");
		MsgBox(L"実行成功2");
	}

	/*-AFLibの解放処理-*/
	AFLib_End();
	return 0;
}