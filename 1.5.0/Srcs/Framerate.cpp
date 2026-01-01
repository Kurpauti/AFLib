#include <chrono>
#include <thread>

#include "AFLib.h"

namespace {
	using fpsClock = std::chrono::steady_clock;

	fpsClock::time_point sampleStart{}; // FPSサンプル開始時刻
	fpsClock::time_point frameStart{};  // フレーム開始時刻（待機計算用）

	int targetFPS = 60;
	int sampleFrame = 60;
	int frameCount = 0;
	float curFps = 0.0f;
	bool fpsInit = false;
}

namespace AFLib {
	// FPS初期化
	int InitFPS(int target, int samples) {
		if (!GetLibInit()) return -1;
		if (target <= 0) target = 60;
		if (samples <= 0) samples = 60;

		targetFPS = target;
		sampleFrame = samples;
		frameCount = 0;
		curFps = 0.0f;
		fpsInit = false;

		return 0;
	}

	// FPS更新（毎フレーム呼ぶ）
	int UpdateFPS() {
		if (!GetLibInit()) return -1;

		const auto now = fpsClock::now();

		// 初回初期化
		if (!fpsInit) {
			sampleStart = now;
			frameStart = now;
			frameCount = 0;
			curFps = 0.0f;
			fpsInit = true;
		}

		// フレーム数カウント
		++frameCount;

		// サンプル分のフレームが貯まったらFPS計算
		if (frameCount >= sampleFrame) {
			const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now - sampleStart).count();
			if (ms > 0) {
				// FPS = sampleFrame * 1000 / 経過ms
				curFps = (static_cast<float>(sampleFrame) * 1000.0f) / static_cast<float>(ms);
			}
			else {
				curFps = 0.0f;
			}
			// サンプルをリセット
			sampleStart = now;
			frameCount = 0;
		}

		return 0;
	}

	// 目標FPSに合わせて待機（フレーム末尾で呼ぶ）
	int WaitFPS() {
		if (!GetLibInit() || !fpsInit) return -1;

		// 目標フレーム時間（μs）
		const long long frameUs = static_cast<long long>(1000000.0f / static_cast<float>(targetFPS));
		const auto deadline = frameStart + std::chrono::microseconds(frameUs);

		// まず大雑把にスリープ（スリープ精度が粗いので少し手前で切り上げる）
		const auto now = fpsClock::now();
		if (deadline > now) {
			auto coarse = std::chrono::duration_cast<std::chrono::milliseconds>(deadline - now);
			if (coarse.count() > 2) {
				// 目標の少し手前まで寝る
				std::this_thread::sleep_for(coarse - std::chrono::milliseconds(1));
			}
		}

		// 残り時間を細かく待つ（CPU負荷を抑えるため短いsleep）
		while (fpsClock::now() < deadline) {
			std::this_thread::sleep_for(std::chrono::microseconds(100)); // 0.1ms刻み
		}

		// 次フレーム開始時刻更新
		frameStart = fpsClock::now();

		return 0;
	}

	// 現在FPS（サンプル平均）
	float GetFPS() {
		if (!GetLibInit()) return -1.0f;
		return curFps;
	}
}