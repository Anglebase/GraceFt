#include "Tools.h"

#include <ege.h>

static inline auto _ = SetProcessDPIAware();

namespace GFt {
    namespace literals {
        int operator""_px(unsigned long long n) {
            return static_cast<int>(GetDpiForSystem() * n / 96.0);
        }
        int operator""_px(long double n) {
            return static_cast<int>(GetDpiForSystem() * n / 96.0);
        }
        int operator""_em(unsigned long long n) {
            return static_cast<int>(GetDpiForSystem() * n / 96.0 * 16.0);
        }
        int operator""_em(long double n) {
            return static_cast<int>(GetDpiForSystem() * n / 96.0 * 16.0);
        }
        int operator""_sw(unsigned long long n) {
            int screenWidth = GetSystemMetrics(SM_CXSCREEN);
            return static_cast<int>(screenWidth * n / 100.0);
        }
        int operator""_sw(long double n) {
            int screenWidth = GetSystemMetrics(SM_CXSCREEN);
            return static_cast<int>(screenWidth * n / 100.0);
        }
        int operator""_sh(unsigned long long n) {
            int screenHeight = GetSystemMetrics(SM_CYSCREEN);
            return static_cast<int>(screenHeight * n / 100.0);
        }
        int operator""_sh(long double n) {
            int screenHeight = GetSystemMetrics(SM_CYSCREEN);
            return static_cast<int>(screenHeight * n / 100.0);
        }
        int operator""_vw(unsigned long long n) {
            if (!ege::getHWnd())
                return 0;
            return static_cast<int>(ege::getwidth() * n / 100.0);
        }
        int operator""_vw(long double n) {
            if (!ege::getHWnd())
                return 0;
            return static_cast<int>(ege::getwidth() * n / 100.0);
        }
        int operator""_vh(unsigned long long n) {
            if (!ege::getHWnd())
                return 0;
            return static_cast<int>(ege::getheight() * n / 100.0);
        }
        int operator""_vh(long double n) {
            if (!ege::getHWnd())
                return 0;
            return static_cast<int>(ege::getheight() * n / 100.0);
        }
    }
}