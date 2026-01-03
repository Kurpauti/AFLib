#include <Windows.h>

#include "AFLib.h"

namespace AFLib {
	// 点の描画
	int DrawPoint(int x, int y, int color) {
		if (!GetLibInit() && !GetBackBufferDC()) return -1;

		/*-色を変換-*/
		const COLORREF col = ToColorRef(color);

		/*-点を描画-*/
		SetPixel(GetBackBufferDC(), x, y, col);

		return 0;
	}

	// 四角形の描画
	int DrawBox(int x1, int y1, int x2, int y2, int color, bool filled) {
		if (!GetLibInit() && !GetBackBufferDC()) return -1;

		/*-四辺の定義-*/
		const int left = (x1 < x2) ? x1 : x2;
		const int right = (x1 > x2) ? x1 : x2;
		const int top = (y1 < y2) ? y1 : y2;
		const int bottom = (y1 > y2) ? y1 : y2;

		/*-色を変換-*/
		const COLORREF col = ToColorRef(color);

		/*-ペンとブラシを作成-*/
		HPEN pen = CreatePen(PS_SOLID, 1, col);
		HBRUSH brush = filled ? CreateSolidBrush(col) : (HBRUSH)GetStockObject(HOLLOW_BRUSH);
		HGDIOBJ oldPen = SelectObject(GetBackBufferDC(), pen);
		HGDIOBJ oldBrush = SelectObject(GetBackBufferDC(), brush);

		/*-四角形を描画-*/
		Rectangle(GetBackBufferDC(), left, top, right, bottom);

		/*-ブラシとペンを解放-*/
		SelectObject(GetBackBufferDC(), oldPen);
		SelectObject(GetBackBufferDC(), oldBrush);
		DeleteObject(pen);
		if (filled) DeleteObject(brush);

		return 0;
	}

	// 円の描画
	int DrawCircle(int x, int y, int radius, int color, bool filled) {
		if (!GetLibInit() && !GetBackBufferDC()) return -1;

		/*-定義-*/
		if (radius < 0) radius = -radius;
		const int left = x - radius;
		const int top = y - radius;
		const int right = x + radius;
		const int bottom = y + radius;

		/*-色を変換-*/
		const COLORREF col = ToColorRef(color);

		/*-ペンとブラシを作成-*/
		HPEN pen = CreatePen(PS_SOLID, 1, col);
		HBRUSH brush = filled ? CreateSolidBrush(col) : (HBRUSH)GetStockObject(HOLLOW_BRUSH);
		HGDIOBJ oldPen = SelectObject(GetBackBufferDC(), pen);
		HGDIOBJ oldBrush = SelectObject(GetBackBufferDC(), brush);

		/*-円を描画-*/
		Ellipse(GetBackBufferDC(), left, top, right, bottom);

		/*-ペンとブラシを解放-*/
		SelectObject(GetBackBufferDC(), oldPen);
		SelectObject(GetBackBufferDC(), oldBrush);
		DeleteObject(pen);
		if (filled) DeleteObject(brush);

		return 0;
	}

	// 線の描画
	int DrawLine(int x1, int y1, int x2, int y2, int color) {
		if (!GetLibInit() && !GetBackBufferDC()) return -1;

		/*-色を変換-*/
		const COLORREF col = ToColorRef(color);

		/*-ペンを作成-*/
		HPEN pen = CreatePen(PS_SOLID, 1, col);
		HGDIOBJ oldPen = SelectObject(GetBackBufferDC(), pen);

		/*-線を描画-*/
		MoveToEx(GetBackBufferDC(), x1, y1, nullptr);
		LineTo(GetBackBufferDC(), x2, y2);

		/*-ペンを解放-*/
		SelectObject(GetBackBufferDC(), oldPen);
		DeleteObject(pen);

		return 0;
	}

	// 三角形の描画
	int DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int color, bool filled) {
		if (!GetLibInit() && !GetBackBufferDC()) return -1;

		/*-頂点を定義-*/
		POINT p[3] = { {x1, y1}, {x2, y2}, {x3, y3} };

		/*-色を変換-*/
		const COLORREF col = ToColorRef(color);

		/*-ペンとブラシを作成-*/
		HPEN pen = CreatePen(PS_SOLID, 1, col);
		HBRUSH brush = filled ? CreateSolidBrush(col) : (HBRUSH)GetStockObject(HOLLOW_BRUSH);
		HGDIOBJ oldPen = SelectObject(GetBackBufferDC(), pen);
		HGDIOBJ oldBrush = SelectObject(GetBackBufferDC(), brush);

		/*-三角形を描画-*/
		Polygon(GetBackBufferDC(), p, 3);

		/*-ペンとブラシを解放-*/
		SelectObject(GetBackBufferDC(), oldPen);
		SelectObject(GetBackBufferDC(), oldBrush);
		DeleteObject(pen);
		if (filled) DeleteObject(brush);

		return 0;
	}
}