# AFLib (Atelier Fazzy Library)

AFLib は、Windows 向けの軽量なゲーム制作用ユーティリティライブラリです。  
シンプルなウィンドウ作成、簡易なバックバッファ描画、入力処理やFPS制御などを提供します。  
初心者にも使いやすく、拡張しやすい設計を心がけています。

バージョン: 1.5.0 — 文字列描画(String)機能を追加しました。

---

## 目的
- ゲームや描画を学ぶための最小限の機能を提供します。
- 複雑な依存を増やさず、Windows APIを直接使う形で動作します。
- 安定性を重視し、使いやすいライブラリを目標としています。

---

## 追加要素
- 1.5.0: 文字列描画機能を追加
  - DrawString: 指定位置に文字列を描画します(バックバッファ優先、なければウィンドウDCにフォールバック)。
  - DrawStringCenter: 中央揃えで描画します。幅・高さの測定を試み、失敗時はフォールバック描画を行います。
  - 描画は既定フォントを使い、描画前後でDCの状態(テキスト色・背景モード)を必ず復帰します。
  - 書式付き出力(可変引数)に対して安全な固定バッファ(512文字)を用いてフォーマットします。

---

## 変更要素・修正要素
- FPS周りの修正
  - GetFPS: 戻り値をfloatに変更。
  - UpdateFPS: サンプル計算式を修正。
  - WaitFPS: 待機時間の算出でフレーム基準のタイムスタンプを使うよう修正。

- CreateBackBufferの安全チェック修正
  - CreateBackBuffer内でGetHWND()を正しく呼び出してハンドル存在チェックを行うように修正しました。

- SetWindowTitleの戻り値を0を返すように修正
  - intを返す関数なので最後にreturn 0を追加して未定義な戻り値を防止しました。

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
- 文字列描画は固定 512 文字まで安全に扱えます。これを超える非常に長い文字列は切れる可能性があります。必要なら将来動的バッファに対応予定です。
- 入力はポーリング方式です。バックグラウンドでもキー状態を拾います。ウィンドウフォーカス時のみ扱いたい場合は追加チェック（GetForegroundWindow 等）を入れてください。
- マルチスレッドから GUI 描画関数を呼ぶのは想定していません。描画はメインスレッドで行ってください。

---

## ライセンス
- （ここにライセンス名を入れてください。例: MIT License）
- ライセンスが未設定なら、配布前に README と LICENSE を整備することをおすすめします。
