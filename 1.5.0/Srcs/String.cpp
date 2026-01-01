#include <Windows.h>
#include <cwchar>
#include <cstdarg>
#include <cstdio>

#include "AFLib.h"

namespace AFLib {
	// 文字列の描画
	int DrawString(int x, int y, int color, const wchar_t* fmt, ...) {
		if (!GetLibInit()) return -1;

		/*-文字列をバッファに一時的に格納-*/
		wchar_t buf[512];

		/*-可変長引数を使って文字列をフォーマット-*/
		va_list args;
		va_start(args, fmt);
		vswprintf(buf, sizeof(buf) / sizeof(wchar_t), fmt, args);
		va_end(args);

		/*-文字列描画用の設定-*/
		SetBkMode(GetBackBufferDC(), TRANSPARENT);
		SetTextColor(GetBackBufferDC(), ToColorRef(color));

		/*-文字列を描画-*/
		TextOutW(GetBackBufferDC(), x, y, buf, (int)wcslen(buf));

		return 0;
	}

	int DrawStringCenter(int x, int y, int color, const wchar_t* fmt, ...) {
		if (!GetLibInit()) return -1;

		/*-文字列をバッファに一時的に格納-*/
		wchar_t buf[512];

		/*-可変長引数を使って文字列をフォーマット-*/
		va_list args;
		va_start(args, fmt);
		vswprintf(buf, sizeof(buf) / sizeof(wchar_t), fmt, args);
		va_end(args);

		/*-文字列描画用の設定-*/
		SetBkMode(GetBackBufferDC(), TRANSPARENT);
		SetTextColor(GetBackBufferDC(), ToColorRef(color));

		/*-文字列の幅を取得-*/
		SIZE size{};
		GetTextExtentPoint32W(GetBackBufferDC(), buf, (int)wcslen(buf), &size);

		/*-文字列を中央揃えで描画-*/
		TextOutW(GetBackBufferDC(), x - size.cx / 2, y - size.cy / 2, buf, (int)wcslen(buf));

		return 0;
	}
}