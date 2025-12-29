#ifndef AFLIB_H
#define AFLIB_H

#include <Windows.h>

namespace AFLib {
	/*----- アプリケーション関連 -----*/

	// AFLibの初期化
	int AFLib_Init(HINSTANCE hInstance, int nCmdShow);

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


	/*----- ウィンドウ管理関連 -----*/

	// ウィンドウサイズを設定
	int SetWindowSize(int width, int height);

	// ウィンドウタイトルを設定
	int SetWindowTitle(const wchar_t* title);

	// マウスの表示/非表示を設定
	int SetMouseDisplay(bool show);


	/*----- カラー関連 -----*/

	constexpr int C_RED = 0xFF0000; // 赤色
	constexpr int C_GREEN = 0x00FF00; // 緑色
	constexpr int C_BLUE = 0x0000FF; // 青色
	constexpr int C_YELLOW = 0xFFFF00; // 黄色
	constexpr int C_CYAN = 0x00FFFF; // シアン色
	constexpr int C_MAGENTA = 0xFF00FF; // マゼンタ色
	constexpr int C_ORANGE = 0xFFA500; // 橙色
	constexpr int C_PURPLE = 0x800080; // 紫色
	constexpr int C_PINK = 0xFFC0CB; // ピンク色
	constexpr int C_BROWN = 0xA52A2A; // 茶色
	constexpr int C_LIME = 0x00FF00; // ライム色
	constexpr int C_BLACK = 0x000000; // 黒色
	constexpr int C_GRAY = 0x808080; // 灰色
	constexpr int C_WHITE = 0xFFFFFF; // 白色

	// 色を追加
	int AddColor(int r, int g, int b);

	// 色をWinAPI形式に変換
	int ToColorRef(int color);


	/*----- 入力関連 -----*/

	constexpr int KEY_ESC       = 0x1B; // ESCキー
	constexpr int KEY_OEM3      = 0xC0; // 半角/全角キー
	constexpr int KEY_MINUS     = 0xBD; // -キー
	constexpr int KEY_TILDE     = 0xC0; // ^キー
	constexpr int KEY_PIPE      = 0xE2; // \|キー(JIS配列専用)
	constexpr int KEY_BACKSPACE = 0x08; // BackSpaceキー
	constexpr int KEY_TAB       = 0x09; // Tabキー
	constexpr int KEY_AT        = 0xC0; // @キー
	constexpr int KEY_LBRACKET  = 0xDB; // [キー
	constexpr int KEY_ENTER     = 0x0D; // Enterキー
	constexpr int KEY_CAPS      = 0x14; // CapsLockキー
	constexpr int KEY_SEMICOLON = 0xBA; // ;キー
	constexpr int KEY_COLON     = 0xBA; // :キー
	constexpr int KEY_RBRACKET  = 0xDD; // ]キー
	constexpr int KEY_LSHIFT    = 0xA0; // 左Shiftキー
	constexpr int KEY_COMMA     = 0xBC; // ,キー
	constexpr int KEY_PERIOD    = 0xBE; // .キー
	constexpr int KEY_SLASH     = 0xBF; //キー
	constexpr int KEY_QUESTION  = 0xBF; // ?キー
	constexpr int KEY_YEN       = 0xE2; // \_キー
	constexpr int KEY_RSHIFT    = 0xA1; // 右Shiftキー
	constexpr int KEY_LCTRL     = 0xA2; // 左Ctrlキー
	constexpr int KEY_WIN       = 0x5B; // Windowsキー
	constexpr int KEY_LALT      = 0xA4; // 左Altキー
	constexpr int KEY_NONCONV   = 0x1D; // 無変換キー
	constexpr int KEY_SPACE     = 0x20; // スペースキー
	constexpr int KEY_CONV      = 0x1C; // 変換キー
	constexpr int KEY_RALT      = 0xA5; // 右Altキー
	constexpr int KEY_APP       = 0x5D; // アプリケーションキー
	constexpr int KEY_RCTRL     = 0xA3; // 右Ctrlキー

	constexpr int KEY_F1        = 0x70; // F1キー
	constexpr int KEY_F2        = 0x71; // F2キー
	constexpr int KEY_F3        = 0x72; // F3キー
	constexpr int KEY_F4        = 0x73; // F4キー
	constexpr int KEY_F5        = 0x74; // F5キー
	constexpr int KEY_F6        = 0x75; // F6キー
	constexpr int KEY_F7        = 0x76; // F7キー
	constexpr int KEY_F8        = 0x77; // F8キー
	constexpr int KEY_F9        = 0x78; // F9キー
	constexpr int KEY_F10       = 0x79; // F10キー
	constexpr int KEY_F11       = 0x7A; // F11キー
	constexpr int KEY_F12       = 0x7B; // F12キー

	constexpr int KEY_1         = 0x31; // 1キー
	constexpr int KEY_2         = 0x32; // 2キー
	constexpr int KEY_3         = 0x33; // 3キー
	constexpr int KEY_4         = 0x34; // 4キー
	constexpr int KEY_5         = 0x35; // 5キー
	constexpr int KEY_6         = 0x36; // 6キー
	constexpr int KEY_7         = 0x37; // 7キー
	constexpr int KEY_8         = 0x38; // 8キー
	constexpr int KEY_9         = 0x39; // 9キー
	constexpr int KEY_0         = 0x30; // 0キー

	constexpr int KEY_Q         = 0x51; // Qキー
	constexpr int KEY_W         = 0x57; // Wキー
	constexpr int KEY_E         = 0x45; // Eキー
	constexpr int KEY_R         = 0x52; // Rキー
	constexpr int KEY_T         = 0x54; // Tキー
	constexpr int KEY_Y         = 0x59; // Yキー
	constexpr int KEY_U         = 0x55; // Uキー
	constexpr int KEY_I         = 0x49; // Iキー
	constexpr int KEY_O         = 0x4F; // Oキー
	constexpr int KEY_P         = 0x50; // Pキー
	constexpr int KEY_A         = 0x41; // Aキー
	constexpr int KEY_S         = 0x53; // Sキー
	constexpr int KEY_D         = 0x44; // Dキー
	constexpr int KEY_F         = 0x46; // Fキー
	constexpr int KEY_G         = 0x47; // Gキー
	constexpr int KEY_H         = 0x48; // Hキー
	constexpr int KEY_J         = 0x4A; // Jキー
	constexpr int KEY_K         = 0x4B; // Kキー
	constexpr int KEY_L         = 0x4C; // Lキー
	constexpr int KEY_Z         = 0x5A; // Zキー
	constexpr int KEY_X         = 0x58; // Xキー
	constexpr int KEY_C         = 0x43; // Cキー
	constexpr int KEY_V         = 0x56; // Vキー
	constexpr int KEY_B         = 0x42; // Bキー
	constexpr int KEY_N         = 0x4E; // Nキー
	constexpr int KEY_M         = 0x4D; // Mキー

	constexpr int KEY_PRINTSCAN = 0x2C; // PrintScreenキー
	constexpr int KEY_SCROLL    = 0x91; // ScrollLockキー
	constexpr int KEY_PAUSE     = 0x13; // PauseBreakキー
	constexpr int KEY_INSERT    = 0x2D; // Insertキー
	constexpr int KEY_HOME      = 0x24; // Homeキー
	constexpr int KEY_PAGEUP    = 0x21; // PageUpキー
	constexpr int KEY_DELETE    = 0x2E; // Deleteキー
	constexpr int KEY_END       = 0x23; // Endキー
	constexpr int KEY_PAGEDOWN  = 0x22; // PageDownキー

	constexpr int KEY_UP        = 0x26; // ↑キー
	constexpr int KEY_LEFT      = 0x25; // ←キー
	constexpr int KEY_DOWN      = 0x28; // ↓キー
	constexpr int KEY_RIGHT     = 0x27; // →キー

	constexpr int KEY_NUMLOCK   = 0x90; // NumLockキー
	constexpr int KEY_NUMSLASH  = 0x6F; // テンキー/キー
	constexpr int KEY_NUMSTAR   = 0x6A; // テンキー*キー
	constexpr int KEY_NUMMINUS  = 0x6D; // テンキー-キー
	constexpr int KEY_NUM7      = 0x67; // テンキー7キー
	constexpr int KEY_NUM8      = 0x68; // テンキー8キー
	constexpr int KEY_NUM9      = 0x69; // テンキー9キー
	constexpr int KEY_NUMPLUS   = 0x6B; // テンキー+キー
	constexpr int KEY_NUM4      = 0x64; // テンキー4キー
	constexpr int KEY_NUM5      = 0x65; // テンキー5キー
	constexpr int KEY_NUM6      = 0x66; // テンキー6キー
	constexpr int KEY_NUM1      = 0x61; // テンキー1キー
	constexpr int KEY_NUM2      = 0x62; // テンキー2キー
	constexpr int KEY_NUM3      = 0x63; // テンキー3キー
	constexpr int KEY_NUMENTER  = 0x0D; // テンキーEnterキー
	constexpr int KEY_NUM0      = 0x60; // テンキー0キー
	constexpr int KEY_NUMDOT    = 0x6E; // テンキー.キー

	// キーが押されていることを取得
	int GetKey(int key);

	// キーが押されたことを取得
	int GetKeyDown(int key);

	// キーが離されたことを取得
	int GetKeyUp(int key);

	// 左クリックが押されていることを取得
	int GetMouseLeft();

	// 左クリックが押されたことを取得
	int GetMouseLeftDown();

	// 左クリックが離されたことを取得
	int GetMouseLeftUp();

	// 右クリックが押されていることを取得
	int GetMouseRight();

	// 右クリックが押されたことを取得
	int GetMouseRightDown();

	// 右クリックが離されたことを取得
	int GetMouseRightUp();

	// マウスのX座標を取得
	int GetMouseX();

	// マウスのY座標を取得
	int GetMouseY();

	// 入力フレームの更新
	int UpdateKeyInput();

	// 入力フレームの終了処理
	int EndKeyInput();
}

// 名前空間を省略
using namespace AFLib;

#endif // !AFLIB_H