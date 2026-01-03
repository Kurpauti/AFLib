# AFLib (Atelier Fazzy Library)

AFLib は Windows 向けの軽量なゲーム制作向けユーティリティライブラリです。  
ウィンドウ作成、簡易バックバッファ描画、FPS 制御、文字列描画など、ゲーム作りの入門に必要な機能をシンプルに提供します。  

最新バージョン: 1.6.0

---

## 目的
- ゲームや描画を学ぶための便利な機能を提供します。  
- できるだけ依存を増やさず Windows API を直接利用する実装にしています。  
- 安定性を優先し、使い方がわかりやすい API を目指します。

---

## 追加要素
- 1.6.0: 図形描画関数を追加
  - `DrawPoint(int x, int y, int color)`  
    指定位置に点を描画します。
  - `DrawBox(int x1, int y1, int x2, int y2, int color, bool filled)`  
    指定位置に四角形を描画します。filledを無効にすると枠組みのみ、有効にすると塗りつぶされた図形が表示されます。
  - `DrawCircle(int x, int y, int radius, int color, bool filled)`  
    指定位置に円を描画します。filledを無効にすると枠組みのみ、有効にすると塗りつぶされた図形が表示されます。
  - `DrawLine(int x1, int y1, int x2, int y2, int color)`  
    指定位置に線を描画します。
  - `DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int color, bool filled)`  
    指定位置に三角形を描画します。filledを無効にすると枠組みのみ、有効にすると塗りつぶされた図形が表示されます。

---

## 変更要素・修正要素
- FPS 関連の修正
  - `GetFPS()` の戻り値を `float` に変更しました。
  - `UpdateFPS()` の計算式を修正しました。
  - `WaitFPS()` はフレーム開始時刻を基準に待機時間を計算するように修正しました。

- `CreateBackBuffer()` の安全チェック修正  
  - `GetHWND()` を正しく呼んでウィンドウハンドルの有無を確認するようにしました。

- `SetWindowTitle()` の戻り値修正  
  - `int` を返す関数なので、処理の最後に `return 0;` を追加して未定義の戻り値を防止しました。

- 文字列描画（`DrawString` 系）の安全化
  - 可変引数の扱いを安全に処理するように改善しました。
  - 長い文字列に対しては将来動的バッファ対応を検討していますが、現状は 512 文字以内を想定しています。

---

## 使い方（最小構成）
```cpp
#include <Windows.h>
#include "AFLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    if (AFLib_Init(hInstance, nCmdShow) == -1) return -1;

    SetWindowSize(1080, 720);
    SetWindowTitle(L"My AFLib App");
    SetMouseDisplay(true);
    InitFPS(60, 10);

    bool showFPS = false;
    while (true) {
        if (AFLib_ProcMsg() == -1) break;
        UpdateFPS();

        ClearScreen(C_BLACK);

        if (GetKeyUp(KEY_TAB)) showFPS = !showFPS;
        if (showFPS) DrawStringCenter(60, 10, C_RED, L"%.1f FPS", GetFPS());
        DrawString(10, 100, C_WHITE, L"TAB で FPS 表示切替");

        FlipScreen();
        WaitFPS();

        if (GetKeyUp(KEY_ESC)) break;
        EndKeyInput();
    }

    AFLib_End();
    return 0;
}
```

---

## 注意事項 / 制限
- 文字列描画は現在 512 文字までの固定バッファを想定しています。長い文字列を扱う場合は自前で分割するか、将来のアップデートで動的バッファ対応を使用してください。  
- 入力はポーリング方式です。フォーカス以外での入力を無視したい場合は `GetForegroundWindow()` 等で追加チェックを行ってください。  
- GUI 描画はメインスレッドで行うことを前提としています。マルチスレッドから直接描画するのは避けてください。  
- Windows（Win32）向けの実装です。クロスプラットフォーム対応は現在のところ未対応です。

---

## ライセンス
- 著作権: Kuraputi / Atelier Fazzy に帰属します。  
- このライブラリを使って作られたアプリケーションに対して、ライセンス料は発生しません。  
- ライブラリを使ったことを明記する義務はありません。  
- このライブラリの使用により生じたいかなる損害についても、作者は責任を負いません。  
- 改造・再配布は自由です。好きに改造して使ってください。

Copyright (c) 2026 Kuraputi (GitHub: Kurpauti) and Atelier Fazzy

Permission is granted, free of charge, to anyone to use, copy, modify and distribute this software and its documentation for any purpose, without fee and without requiring attribution. You may include this library in free or commercial products.

This software is provided "as is", without warranty of any kind. In no event shall the authors be liable for any claim, damages or other liability arising from the use of this software.
