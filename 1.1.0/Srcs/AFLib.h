#ifndef AFLIB_H
#define AFLIB_H

#include "Windows.h"

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
	int AFLib_Initialized();


	/*----- フレームレート関連 -----*/

	// FPSの初期化
	int InitFPS(int target, int samples);

	// FPSを更新
	int UpdateFPS();

	// 待機
	int WaitFPS();

	// 現在のFPS値を取得
	int GetFPS();
}

// 名前空間を省略
using namespace AFLib;

#endif // !AFLIB_H