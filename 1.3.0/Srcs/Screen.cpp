#include <Windows.h>

#include "AFLib.h"

namespace {
	/*----- 変数 -----*/

	HDC backBuffDC = nullptr;           // 裏画面のデバイスコンテキスト
	HBITMAP preBmp = nullptr;           // 以前のバックバッファ
	HBITMAP curBmp = nullptr;           // 現在のバックバッファ
	COLORREF clearColor = RGB(0, 0, 0); // 画面のクリア時の色
	int bmpWidth = 0;                   // 裏画面の幅
	int bmpHeight = 0;                  // 裏画面の高さ
}

namespace AFLib {
	// バックバッファを破棄
	int DestroyBackBuffer() {
		if (!GetLibInit() || !backBuffDC) return -1;

		/*-バックバッファを破棄-*/
		SelectObject(backBuffDC, preBmp);
		DeleteObject(curBmp);
		DeleteDC(backBuffDC);

		/*-変数をリセット-*/
		backBuffDC = nullptr;
		preBmp = nullptr;
		curBmp = nullptr;
		bmpWidth = 0;
		bmpHeight = 0;

		return 0;
	}

	// バックバッファを作成
	int CreateBackBuffer(int width, int height) {
		if (!GetHWND) return -1;
		if (width <= 0 || height <= 0) return -1;

		/*-バックバッファがあるならば破棄-*/
		DestroyBackBuffer();

		/*-バックバッファ用のDCとビットマップを作成-*/
		HDC wndDC = GetDC(GetHWND());
		backBuffDC = CreateCompatibleDC(wndDC);
		curBmp = CreateCompatibleBitmap(wndDC, width, height);
		preBmp = (HBITMAP)SelectObject(backBuffDC, curBmp);
		ReleaseDC(GetHWND(), wndDC);

		/*-バックバッファのサイズを保存-*/
		bmpWidth = width;
		bmpHeight = height;

		/*-バックバッファを指定色で塗りつぶす-*/
		RECT rc{ 0, 0, bmpWidth, bmpHeight };
		HBRUSH brush = CreateSolidBrush(clearColor);
		FillRect(backBuffDC, &rc, brush);
		DeleteObject(brush);
		
		return 0;
	}

	// 画面をクリア
	int ClearScreen(int color) {
		if (!backBuffDC) return -1;

		/*-指定の色を変換-*/
		clearColor = static_cast<COLORREF>(ToColorRef(color));

		/*-指定色でバックバッファを塗りつぶす-*/
		RECT rc{ 0, 0, bmpWidth, bmpHeight };
		HBRUSH brush = CreateSolidBrush(clearColor);
		FillRect(backBuffDC, &rc, brush);
		DeleteObject(brush);

		return 0;
	}

	// 裏画面に反転
	int FlipScreen() {
		if (!GetLibInit() || !backBuffDC) return -1;

		/*-バックバッファをメインウィンドウに送信-*/
		HDC wndDC = GetDC(GetHWND());
		BitBlt(wndDC, 0, 0, bmpWidth, bmpHeight, backBuffDC, 0, 0, SRCCOPY);
		ReleaseDC(GetHWND(), wndDC);

		return 0;
	}
}