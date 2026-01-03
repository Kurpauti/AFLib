#include <Windows.h>

#include "AFLib.h"

// エントリーポイント
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int nCmdShow) {
	/*-AFLibを初期化-*/
	if (AFLib_Init(hInstance, nCmdShow) == -1) {
		MsgBox(L"AFLibの初期化に失敗しました", L"AFLib");
		return -1;
	}

	/*-初期設定-*/
	SetWindowSize(1080, 720);              // ウィンドウサイズの設定
	SetWindowTitle(L"ことば の かみさま"); // ウィンドウタイトルの設定
	SetMouseDisplay(true);                 // マウスカーソルを表示
	InitFPS(60, 10);                       // FPSの初期化

	/*-変数-*/
	int score = 0;
	bool showFPS = false;

	/*-メインループ-*/
	while (true) {
		if (AFLib_ProcMsg() == -1) break;  // メッセージ処理
		UpdateFPS();                       // FPSを更新
		ClearScreen(C_BLACK);              // 画面をクリア

		if (GetKeyUp(KEY_TAB)) showFPS = !showFPS;
		if (showFPS) DrawStringCenter(60, 10, C_RED, L"%.1f FPS", GetFPS());
		DrawString(10, 100, C_WHITE, L"TABキーでFPS表示切替");

		score++;
		DrawString(10, 130, C_WHITE, L"%d", score);

		FlipScreen();                      // 裏画面にする
		WaitFPS();                         // 待機

		if (GetKeyUp(KEY_ESC)) break;      // 終了条件
		EndKeyInput();                     // 入力フレーム終了
	}

	/*-AFLibの解放処理-*/
	AFLib_End();
	return 0;
}