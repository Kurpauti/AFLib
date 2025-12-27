#include <Windows.h>

#include "AFLib.h"

// エントリーポイント
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int nCmdShow) {
	/*-AFLibを初期化-*/
	if (AFLib_Init(hInstance, nCmdShow, 1080, 720, L"Sample 3D Game") == -1) {
		MsgBox(L"AFLibの初期化に失敗しました", L"AFLib");
		return -1;
	}

	InitFPS(60, 10);                      // FPSの初期化

	/*-メインループ-*/
	while (true) {
		if (AFLib_ProcMsg() == -1) break; // メッセージ処理
		UpdateFPS();                      // FPSを更新
		MsgBox(L"実行成功1", L"AFLib");
		MsgBox(L"実行成功2", L"AFLib");

		WaitFPS();                        // 待機
	}

	/*-AFLibの解放処理-*/
	AFLib_End();
	return 0;
}