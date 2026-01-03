#include <chrono>
#include <thread>

#include "AFLib.h"

namespace {
	using fpsClock = std::chrono::steady_clock;


	/*----- 変数 -----*/

	fpsClock::time_point sampleStart{}; // サンプル開始時刻
	fpsClock::time_point frameStart{};  // 各フレーム開始時刻

	int targetFPS = 60;                 // 目標FPS
	int sampleFrame = 60;               // 表示のサンプリング数
	int frameCount = 0;                 // フレームカウント
	float curFps = 0.0f;                // 現在のFPS値
	bool fpsInit = false;               // fpsの初期化フラグ
}

namespace AFLib {
	// FPSの初期化
	int InitFPS(int target, int samples) {
		if (!GetLibInit()) return -1;
		if (target <= 0 || samples <= 0) return -1;

		/*-値を更新-*/
		targetFPS = target;
		sampleFrame = samples;
		frameCount = 0;
		curFps = 0.0f;
		fpsInit = false;

		return 0;
	}

	// FPSを更新
	int UpdateFPS() {
		if (!GetLibInit() && !fpsInit) return -1;

		/*-現在の計測時間を取得-*/
		const auto now = fpsClock::now();

		/*-初期化されていないならば1度だけ-*/
		if (!fpsInit) {
			sampleStart = now;
			frameStart = now;
			frameCount = 0;
			curFps = 0.0f;
			fpsInit = true;
			return 0;
		}

		/*-カウントを進める-*/
		++frameCount;

		/*-カウントが既定のフレームに達したら更新-*/
		if (frameCount >= sampleFrame) {
			const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now - sampleStart).count();
			if (ms > 0) curFps = 1000.0f / (static_cast<float>(ms) / static_cast<float>(sampleFrame));

			// 次の計測のためにリセット
			sampleStart = now;
			frameCount = 0;
		}

		return 0;
	}

	// 待機
	int WaitFPS() {
		if (!GetLibInit() && !fpsInit) return -1;

		/*-現在の計測時間を取得-*/
		const auto now = fpsClock::now();

		/*-フレーム時間の計算-*/
		const float frameMs = 1000.0f / static_cast<float>(targetFPS);
		const float elapsedMs = static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(now - sampleStart).count());
		const float targetMs = static_cast<float>(frameCount) * frameMs;
		const float waitMs = targetMs - elapsedMs;

		/*-待機-*/
		if (waitMs > 0.0f) std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long long>(waitMs)));

		/*-フレーム開始時間を更新-*/
		frameStart = fpsClock::now();

		return 0;
	}

	// 現在のFPS値を取得
	float GetFPS() {
		if (!GetLibInit() && !fpsInit) return -1.0f;
		return curFps;
	}
}