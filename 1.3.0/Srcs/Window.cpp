#include <Windows.h>

#include "AFLib.h"

namespace AFLib {
	// ウィンドウサイズを設定
	int SetWindowSize(int width, int height) {
		if (!GetLibInit()) return -1;
		if (width <= 0 || height <= 0) return -1;

		/*-スタイルを取得-*/
		DWORD style = (DWORD)GetWindowLongPtr(GetHWND(), GWL_STYLE);
		DWORD exStyle = (DWORD)GetWindowLongPtr(GetHWND(), GWL_EXSTYLE);

		/*-必要なウィンドウサイズを取得-*/
		RECT rc{ 0, 0, width, height };
		AdjustWindowRectEx(&rc, style, FALSE, exStyle);
		const int winW = rc.right - rc.left;
		const int winH = rc.bottom - rc.top;

		/*-ウィンドウを反映-*/
		SetWindowPos(GetHWND(), nullptr, 0, 0, winW, winH, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);

		/*-バックバッファを再生成-*/
		CreateBackBuffer(width, height);

		return 0;
	}

	// ウィンドウタイトルを設定
	int SetWindowTitle(const wchar_t* name) {
		if (!GetLibInit()) return -1;

		/*-名前を反映-*/
		SetWindowTextW(GetHWND(), name ? name : L"");
	}

	// マウスの表示/非表示を設定
	int SetMouseDisplay(bool show) {
		if (!GetLibInit()) return -1;

		/*-フラグによって表示設定を切り替える-*/
		while (ShowCursor(show) >= 0 && !show) {}
		while (ShowCursor(show) < 0 && show) {}

		return 0;
	}
}