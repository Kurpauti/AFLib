#include <Windows.h>

namespace {
	/*----- 変数 -----*/

	bool initAFLib = false;                         // AFLibの初期化状態
	int screenW = 1080;                             // ウィンドウの幅
	int screenH = 720;                              // ウィンドウの高さ
	const wchar_t* className = L"AFLibWindowClass"; // AFLibのウィンドウクラスの名前
	const wchar_t* wndTitle = L"AFLib Window";      // ウィンドウのタイトル
	HWND wndHandle = nullptr;                       // AFLibのウィンドウハンドル
	HINSTANCE appInstance = nullptr;                // AFLibのインスタンスハンドル


	/*----- プロシージャ -----*/

	// 専用のウィンドウプロシージャ
	LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		switch (msg) {
			// ウィンドウが閉じられたとき
		case WM_CLOSE:
			PostQuitMessage(0);
			break;
			// その他のメッセージ
		default:
			return DefWindowProcW(hWnd, msg, wParam, lParam);
			break;
		}
		return 0;
	}
}

namespace AFLib {
	// AFLibの初期化
	int Init_Lib(HINSTANCE hInstance, int nCmdShow) {
		/*-既に初期化されているならスキップ-*/
		if (initAFLib) return 0;

		/*-ウィンドウを設定-*/
		WNDCLASSEXW wc = {};
		wc.cbSize = sizeof(WNDCLASSEXW);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = (HICON)LoadIconW(NULL, MAKEINTRESOURCEW(IDI_APPLICATION));
		wc.hCursor = (HCURSOR)LoadCursorW(NULL, MAKEINTRESOURCEW(IDC_ARROW));
		wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = className;
		wc.hIconSm = (HICON)LoadIconW(NULL, MAKEINTRESOURCEW(IDI_APPLICATION));

		/*-ウィンドの登録に失敗したときは強制終了-*/
		if (!RegisterClassExW(&wc)) return -1;

		/*-ウィンドウサイズ+スタイルを定義-*/
		RECT rc = { 0, 0, screenW, screenH };
		DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

		/*-ウィンドウサイズの調整等に失敗した場合は強制終了-*/
		if (!AdjustWindowRect(&rc, style, FALSE)) {
			UnregisterClassW(className, hInstance);
			return -1;
		}

		/*-ウィンドウを作成-*/
		wndHandle = CreateWindowExW(
			0,
			className,
			wndTitle,
			style,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			rc.right - rc.left,
			rc.bottom - rc.top,
			nullptr,
			nullptr,
			hInstance,
			nullptr
		);

		/*-ウィンドウの作成に失敗したら強制終了-*/
		if (!wndHandle) {
			UnregisterClassW(className, hInstance);
			return -1;
		}

		/*-ウィンドウの表示+更新-*/
		ShowWindow(wndHandle, nCmdShow);
		UpdateWindow(wndHandle);

		/*-初期化完了-*/
		initAFLib = true;        // 初期化完了にする
		appInstance = hInstance; // インスタンスを保持
		return 0;
	}

	// AFLibの終了処理
	int Exit_Lib() {
		/*-ライブラリの初期化が完了していないなら強制終了-*/
		if (!initAFLib) return -1;

		/*-ウィンドウを破棄-*/
		DestroyWindow(wndHandle);

		/*-登録しているウィンドウクラスを解除-*/
		UnregisterClassW(className, appInstance);

		/*-変数を初期化-*/
		initAFLib = false;
		screenW = 0;
		screenH = 0;
		wndHandle = nullptr;
		appInstance = nullptr;

		return 0;
	}

	// メッセージの処理
	int ProcMsg() {
		/*-ライブラリの初期化が完了していないなら強制終了-*/
		if (!initAFLib) return -1;

		/*-メッセージ変数を作成-*/
		MSG msg = {};

		/*-メッセージが存在する限り処理を繰り返す-*/
		while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) return -1;

			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}

		return 0;
	}

	// メッセージボックスを表示
	int ShowMsgBox(const wchar_t* mainText, const wchar_t* titleText) {
		/*-ライブラリの初期化が完了していないなら強制終了-*/
		if (!initAFLib) return -1;

		/*-メッセージボックスを表示-*/
		MessageBoxW(wndHandle, mainText, titleText, MB_OK | MB_ICONINFORMATION);

		return 0;
	}
}