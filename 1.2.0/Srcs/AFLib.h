#ifndef AFLIB_H
#define AFLIB_H

#include <Windows.h>

namespace AFLib {
	/*----- アプリケーション関連 -----*/

	// AFLibの初期化
	int AFLib_Init(HINSTANCE hInstance, int nCmdShow, int width, int height, const wchar_t* title);

	// AFLibの解放処理
	int AFLib_End();

	// メッセージ処理
	int AFLib_ProcMsg();

	// メッセージボックス
	int MsgBox(const wchar_t* text, const wchar_t* title);

	// AFLibの初期化状態を取得
	int GetLibInit();

	// ウィンドウハンドルを取得
	HWND GetHWND();


	/*----- フレームレート関連 -----*/

	// FPSの初期化
	int InitFPS(int target, int samples);

	// FPSを更新
	int UpdateFPS();

	// 待機
	int WaitFPS();

	// 現在のFPS値を取得
	int GetFPS();


	/*----- 画面更新関連 -----*/

	// バックバッファを破棄
	int DestroyBackBuffer();

	// バックバッファを作成
	int CreateBackBuffer(int width, int height);

	// 画面をクリア
	int ClearScreen(int color);

	// 裏画面に反転
	int FlipScreen();


	/*----- カラー関連 -----*/

	constexpr int C_RED     = 0xFF0000; // 赤色
	constexpr int C_GREEN   = 0x00FF00; // 緑色
	constexpr int C_BLUE    = 0x0000FF; // 青色
	constexpr int C_YELLOW  = 0xFFFF00; // 黄色
	constexpr int C_CYAN    = 0x00FFFF; // シアン色
	constexpr int C_MAGENTA = 0xFF00FF; // マゼンタ色
	constexpr int C_ORANGE  = 0xFFA500; // 橙色
	constexpr int C_PURPLE  = 0x800080; // 紫色
	constexpr int C_PINK    = 0xFFC0CB; // ピンク色
	constexpr int C_BROWN   = 0xA52A2A; // 茶色
	constexpr int C_LIME    = 0x00FF00; // ライム色
	constexpr int C_BLACK   = 0x000000; // 黒色
	constexpr int C_GRAY    = 0x808080; // 灰色
	constexpr int C_WHITE   = 0xFFFFFF; // 白色

	// 色を追加
	int AddColor(int r, int g, int b);

	// 色をWinAPI形式に変換
	int ToColorRef(int color);
}

// 名前空間を省略
using namespace AFLib;

#endif // !AFLIB_H