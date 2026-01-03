#include <Windows.h>
#include <atomic>

#include "AFLib.h"

namespace {
	/*----- 変数 -----*/

	HWND af_hwnd = nullptr;                         // AFLibのウィンドウハンドル
	std::atomic<bool> af_init{ false };             // AFLibの初期化フラグ
	const int SCREEN_WIDTH = 1080;                  // ウィンドウの幅
	const int SCREEN_HEIGHT = 720;                  // ウィンドウの高さ
	const wchar_t* className = L"AFLibWindowClass"; // AFLibのウィンドウクラス名


	/*----- ウィンドウプロシージャ -----*/

	// 専用のウィンドウプロシージャ
	LRESULT CALLBACK AFWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		switch (msg) {
		case WM_CLOSE:
			DestroyWindow(hWnd);
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		default:
			return DefWindowProcW(hWnd, msg, wParam, lParam);
		}
	}
}

namespace AFLib {
	// AFLibの初期化
	int AFLib_Init(HINSTANCE hInstance, int nCmdShow) {
		if (af_init.load()) return 0;
		if (!hInstance) return -1;

		/*-ウィンドウを設定-*/
		WNDCLASSEXW wc{};
		wc.cbSize = sizeof(WNDCLASSEXW);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = AFWndProc;
		wc.hInstance = hInstance;
		wc.hIcon = LoadIconW(nullptr, MAKEINTRESOURCEW(IDI_APPLICATION));
		wc.hCursor = LoadCursorW(nullptr, MAKEINTRESOURCEW(IDC_ARROW));
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wc.lpszClassName = className;
		wc.hIconSm = LoadIconW(nullptr, MAKEINTRESOURCEW(IDI_APPLICATION));

		/*-ウィンドウの登録に失敗した場合は終了-*/
		if (!RegisterClassExW(&wc)) return -1;

		/*-ウィンドウサイズとスタイルを定義-*/
		RECT rc = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

		/*-ウィンドウサイズの調整に失敗した場合は終了-*/
		if (!AdjustWindowRect(&rc, style, FALSE)) {
			UnregisterClassW(className, hInstance);
			return -1;
		}

		/*-ウィンドウを作成-*/
		af_hwnd = CreateWindowExW(
			0,
			className,
			L"AFLib Window",
			style,
			CW_USEDEFAULT, CW_USEDEFAULT,
			rc.right - rc.left,
			rc.bottom - rc.top,
			nullptr,
			nullptr,
			hInstance,
			nullptr
		);

		/*-ウィンドウの作成に失敗した場合は終了-*/
		if (!af_hwnd) {
			UnregisterClassW(className, hInstance);
			return -1;
		}

		/*-ウィンドウの表示 & 更新-*/
		ShowWindow(af_hwnd, nCmdShow);
		UpdateWindow(af_hwnd);

		/*-バックバッファを作成-*/
		CreateBackBuffer(SCREEN_WIDTH, SCREEN_HEIGHT);

		/*-初期化完了-*/
		af_init.store(true);
		return 0;
	}

	// AFLibの解放処理
	int AFLib_End() {
		if (!af_init.load()) return -1;

		/*-ウィンドウの破棄-*/
		DestroyWindow(af_hwnd);

		/*-バックバッファの破棄-*/
		DestroyBackBuffer();

		/*-ウィンドウクラスの登録を解除-*/
		UnregisterClassW(className, GetModuleHandleW(nullptr));

		/*-変数をリセット-*/
		af_init.store(false);
		af_hwnd = nullptr;

		return 0;
	}

	// メッセージ処理
	int AFLib_ProcMsg() {
		if (!af_init.load()) return -1;

		/*-メッセージがある限りループする-*/
		MSG msg{};
		while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) return -1;

			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}

		/*-入力処理を更新-*/
		UpdateKeyInput();

		return 0;
	}

	// メッセージボックス
	int MsgBox(const wchar_t* text, const wchar_t* title) {
		HWND owner = af_init.load() ? af_hwnd : nullptr;
		return MessageBoxW(owner, text, title, MB_OK | MB_ICONINFORMATION);
	}

	// AFLibの初期化状態を取得
	int GetLibInit() {
		return af_init.load() ? 1 : 0;
	}

	// ウィンドウハンドルを取得
	HWND GetHWND() {
		return af_hwnd;
	}
}