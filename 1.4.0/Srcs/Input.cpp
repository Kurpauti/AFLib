#include <Windows.h>

#include "AFLib.h"

namespace {
	/*----- 変数 -----*/

	int mouseX = 0;       // マウスのX座標
	int mouseY = 0;       // マウスのY座標
	int preKey[256] = {}; // 以前のキー状態
	int curKey[256] = {}; // 現在のキー状態
	int preMouse[2] = {}; // 以前のマウス状態(0=左 1=右)
	int curMouse[2] = {}; // 現在のマウス状態*
}

namespace AFLib {
	// キーが押されていることを取得
	int GetKey(int key) {
		if (!GetLibInit()) return -1;
		if (key < 0 || key > 255) return 0;

		return curKey[key];
	}

	// キーが押されたことを取得
	int GetKeyDown(int key) {
		if (!GetLibInit()) return -1;
		if (key < 0 || key > 255) return 0;

		return (curKey[key] && !preKey[key]) ? 1 : 0;
	}

	// キーが離されたことを取得
	int GetKeyUp(int key) {
		if (!GetLibInit()) return -1;
		if (key < 0 || key > 255) return 0;

		return (!curKey[key] && preKey[key]) ? 1 : 0;
	}

	// 左クリックが押されていることを取得
	int GetMouseLeft() {
		if (!GetLibInit()) return -1;

		return curMouse[0];
	}

	// 左クリックが押されたことを取得
	int GetMouseLeftDown() {
		if (!GetLibInit()) return -1;

		return (curMouse[0] && !preMouse[0]) ? 1 : 0;
	}

	// 左クリックが離されたことを取得
	int GetMouseLeftUp() {
		if (!GetLibInit()) return -1;

		return (!curMouse[0] && preMouse[0]) ? 1 : 0;
	}

	// 右クリックが押されていることを取得
	int GetMouseRight() {
		if (!GetLibInit()) return -1;

		return curMouse[1];
	}

	// 右クリックが押されたことを取得
	int GetMouseRightDown() {
		if (!GetLibInit()) return -1;

		return (curMouse[1] && !preMouse[1]) ? 1 : 0;
	}

	// 右クリックが離されたことを取得
	int GetMouseRightUp() {
		if (!GetLibInit()) return -1;

		return (!curMouse[1] && preMouse[1]) ? 1 : 0;
	}

	// マウスのX座標を取得
	int GetMouseX() {
		if (!GetLibInit()) return -1;

		return mouseX;
	}

	// マウスのY座標を取得
	int GetMouseY() {
		if (!GetLibInit()) return -1;

		return mouseY;
	}

	// 入力フレームの更新
	int UpdateKeyInput() {
		if (!GetLibInit()) return -1;

		/*-前フレームの状態を保存-*/
		for (int i = 0; i < 256; ++i) preKey[i] = curKey[i];
		preMouse[0] = curMouse[0];
		preMouse[1] = curMouse[1];

		/*-キー状態をボーリング-*/
		for (int i = 0; i < 256; ++i) {
			SHORT s = GetAsyncKeyState(i);
			curKey[i] = (s & 0x8000) ? 1 : 0;
		}

		/*-現在のマウス状態を更新-*/
		curMouse[0] = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) ? 1 : 0;
		curMouse[1] = (GetAsyncKeyState(VK_RBUTTON) & 0x8000) ? 1 : 0;

		/*-マウス座標を更新(クライアント)-*/
		POINT p{};
		if (GetCursorPos(&p)) {
			HWND hwnd = GetHWND();
			if (hwnd) {
				ScreenToClient(hwnd, &p);
				mouseX = p.x;
				mouseY = p.y;
			}
		}

		return 0;
	}

	// 入力フレームの終了処理
	int EndKeyInput() {
		if (!GetLibInit()) return -1;

		/*-入力状態を以前の状態にコピー-*/
		for (int i = 0; i < 256; ++i) preKey[i] = curKey[i];
		for (int i = 0; i < 2; ++i) preMouse[i] = curMouse[i];

		return 0;
	}
}