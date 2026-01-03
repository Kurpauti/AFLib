#include "AFLib.h"

namespace AFLib {
	// F‚ğ’Ç‰Á
	int AddColor(int r, int g, int b) {
		if (!GetLibInit()) return -1;

		return ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF);
	}

	// F‚ğWinAPIŒ`®‚É•ÏŠ·
	int ToColorRef(int color) {
		if (!GetLibInit()) return -1;

		int r = (color >> 16) & 0xFF; // Ô¬•ª
		int g = (color >> 8) & 0xFF;  // —Î¬•ª
		int b = color & 0xFF;         // Â¬•ª

		return (r) | (g << 8) | (b << 16);
	}
}