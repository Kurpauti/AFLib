# AFLib (Atelier Fazzy Library)

AFLib は、Windows 向けの軽量なゲーム制作用ユーティリティライブラリです。  
シンプルなウィンドウ作成、簡易なバックバッファ描画、入力ポーリングや FPS 制御などを提供します。  
初心者にも使いやすく、拡張しやすい設計を心がけています。

バージョン: 1.5.0 — 文字列描画（String）機能を追加したリリース

---

## 目的
- ゲームや描画を学ぶための最小限の機能を提供します。
- 複雑な依存を増やさず、Windows API を直接使う形で動作します。
- 安定性を重視し、使いやすい API を目標としています。

---

## 主要機能
- ウィンドウ作成 / 終了 (AFLib_Init / AFLib_End)
- メッセージ処理 (AFLib_ProcMsg)
- バックバッファ作成・破棄・反転 (CreateBackBuffer / DestroyBackBuffer / FlipScreen)
- クリア、色ユーティリティ (ClearScreen / AddColor / ToColorRef)
- シンプルな FPS 制御 (InitFPS / UpdateFPS / WaitFPS / GetFPS)
- 入力（ポーリング）(GetKey / GetKeyDown / GetMouseX / GetMouseY 等)
- 文字列描画（今回の追加）(DrawString / DrawStringCenter)

---

## 追加要素
（この順番で README に必ず表示しています）

- 1.5.0: 文字列描画機能を追加
  - DrawString: 指定位置に文字列を描画します（バックバッファ優先、なければウィンドウ DC にフォールバック）。
  - DrawStringCenter: 中央揃えで描画します。幅・高さの測定を試み、失敗時はフォールバック描画を行います。
  - 描画は既定フォントを使い、描画前後で DC の状態（テキスト色・背景モード）を必ず復帰します。
  - 書式付き出力（可変引数）に対して安全な固定バッファ（512文字）を用いてフォーマットします。512 文字以上は現状サポート外の旨を README に明記しています。

- GetBackBufferDC() を公開
  - バックバッファ用の HDC を取得できます（内部バックバッファがない場合は nullptr を返します）。
  - String 描画はこの DC を優先的に使います。

---

## 変更要素・修正要素
（この順番で README に必ず表示しています）

- FPS 周りの修正（重要）
  - GetFPS の戻り値を float に変更（より正確な値を返します）。
  - UpdateFPS: サンプル計算式を修正（curFps = sampleFrame * 1000 / elapsed_ms）。
  - WaitFPS: 待機時間の算出でフレーム基準のタイムスタンプを使うよう修正（frameStart を基準に計算）。
  - これにより、目標 FPS（例: 60fps）に近い挙動になります。

- CreateBackBuffer の安全チェック修正
  - CreateBackBuffer 内で GetHWND() を正しく呼び出してハンドル存在チェックを行うように修正しました（未初期化時の誤動作回避）。

- SetWindowTitle の戻り値を 0 を返すように修正
  - int を返す関数なので最後に return 0 を追加して未定義な戻り値を防止しました。

- String（DrawString 系）の安全化
  - 可変長フォーマットの扱いを安全に（vswprintf_s 等を用いる／固定バッファの範囲内）しました。
  - バックバッファが無い場合はウィンドウ DC を一時取得して描画し、必ず ReleaseDC で返却します。
  - 描画前後でテキスト色・背景モードを元に戻します。

- 入力処理についての注意
  - 現在は GetAsyncKeyState によるポーリング方式です（AFLib_ProcMsg 内で UpdateKeyInput を呼び、毎フレーム更新される想定）。
  - 将来 Raw Input に移すことは可能ですが、今はシンプルで扱いやすいポーリング方式を採用しています。

---

## インストール / ビルド
- Visual Studio（MSVC）でのビルドを想定しています。
- ソリューション / プロジェクトにソースを追加し、Windows アプリケーション設定でビルドしてください。
- 必要な追加設定は特にありません（Windows.h を使います）。

簡単なビルド手順（例）:
1. Visual Studio で新規 Visual C++ -> Windows デスクトップウィザードを作成
2. ソース群（.cpp, .h）を追加
3. プロジェクトをビルドして実行

---

## 使い方（最小サンプル）
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

## バージョン / リリース方針
- 小さな機能追加や安定化の単位でバージョンを切っていきます。  
  例: 1.5.0 — String（文字列描画）を追加、安定化
- README の「追加要素」「変更要素・修正要素」は毎リリース時に更新します（現在この README は 1.5.0 向けです）。

---

## 貢献・報告
- バグ報告や要望は Issue でお願いします。
- プルリクエスト歓迎：簡単な修正から順にマージします。大きな変更は別ブランチで提案してください。
- コードの互換性を壊す変更は事前に Issue で相談してください。

---

## ライセンス
- （ここにライセンス名を入れてください。例: MIT License）
- ライセンスが未設定なら、配布前に README と LICENSE を整備することをおすすめします。

---

## 最後に（短い助言）
- 今の状態はリリースに十分な安定性があります。  
- 私が提案した軽微な修正（FPS の式・CreateBackBuffer のチェック・DrawString の安全化・SetWindowTitle の戻り値）は既に取り込まれているか確認してください。取り込んでいれば 1.5.0 をタグ付けして公開して大丈夫です。  
- 追加で README の英語版や例を増やしたい場合は手伝います。

Happy coding!
