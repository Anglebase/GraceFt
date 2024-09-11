#include "Tools.h"

#include <ege.h>

static inline auto _ = SetProcessDPIAware();

namespace GFt {
    namespace literals {
        unsigned long operator""_px(unsigned long long n) {
            return static_cast<unsigned long>(GetDpiForSystem() * n / 96.0);
        }
        unsigned long operator""_px(long double n) {
            return static_cast<unsigned long>(GetDpiForSystem() * n / 96.0);
        }
        unsigned long operator""_em(unsigned long long n) {
            return static_cast<unsigned long>(GetDpiForSystem() * n / 96.0 * 16.0);
        }
        unsigned long operator""_em(long double n) {
            return static_cast<unsigned long>(GetDpiForSystem() * n / 96.0 * 16.0);
        }
        unsigned long operator""_sw(unsigned long long n) {
            int screenWidth = GetSystemMetrics(SM_CXSCREEN);
            return static_cast<unsigned long>(screenWidth * n / 100.0);
        }
        unsigned long operator""_sw(long double n) {
            int screenWidth = GetSystemMetrics(SM_CXSCREEN);
            return static_cast<unsigned long>(screenWidth * n / 100.0);
        }
        unsigned long operator""_sh(unsigned long long n) {
            int screenHeight = GetSystemMetrics(SM_CYSCREEN);
            return static_cast<unsigned long>(screenHeight * n / 100.0);
        }
        unsigned long operator""_sh(long double n) {
            int screenHeight = GetSystemMetrics(SM_CYSCREEN);
            return static_cast<unsigned long>(screenHeight * n / 100.0);
        }
        unsigned long operator""_vw(unsigned long long n) {
            if (!ege::getHWnd())
                return 0;
            return static_cast<unsigned long>(ege::getwidth() * n / 100.0);
        }
        unsigned long operator""_vw(long double n) {
            if (!ege::getHWnd())
                return 0;
            return static_cast<unsigned long>(ege::getwidth() * n / 100.0);
        }
        unsigned long operator""_vh(unsigned long long n) {
            if (!ege::getHWnd())
                return 0;
            return static_cast<unsigned long>(ege::getheight() * n / 100.0);
        }
        unsigned long operator""_vh(long double n) {
            if (!ege::getHWnd())
                return 0;
            return static_cast<unsigned long>(ege::getheight() * n / 100.0);
        }
    }
}