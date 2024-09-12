#include "Tools.h"

#include <ege.h>

static inline auto _ = SetProcessDPIAware();

namespace GFt {
    namespace literals {
        int operator""_px(unsigned long long n) {
            return static_cast<int>(GetDpiForSystem() * n * 1.04166667E-2);
        }
        int operator""_px(long double n) {
            return static_cast<int>(GetDpiForSystem() * n * 1.04166667E-2);
        }
        int operator""_em(unsigned long long n) {
            return static_cast<int>(GetDpiForSystem() * n * 1.66666667E-1);
        }
        int operator""_em(long double n) {
            return static_cast<int>(GetDpiForSystem() * n * 1.66666667E-1);
        }
        int operator""_sw(unsigned long long n) {
            int screenWidth = GetSystemMetrics(SM_CXSCREEN);
            return static_cast<int>(screenWidth * n / 100);
        }
        int operator""_sw(long double n) {
            int screenWidth = GetSystemMetrics(SM_CXSCREEN);
            return static_cast<int>(screenWidth * n / 100);
        }
        int operator""_sh(unsigned long long n) {
            int screenHeight = GetSystemMetrics(SM_CYSCREEN);
            return static_cast<int>(screenHeight * n / 100);
        }
        int operator""_sh(long double n) {
            int screenHeight = GetSystemMetrics(SM_CYSCREEN);
            return static_cast<int>(screenHeight * n / 100);
        }
        int operator""_vw(unsigned long long n) {
            auto hwnd = ege::getHWnd();
            RECT rect;
            GetClientRect(hwnd, &rect);
            return static_cast<int>((rect.right - rect.left) * n / 100);
        }
        int operator""_vw(long double n) {
            auto hwnd = ege::getHWnd();
            RECT rect;
            GetClientRect(hwnd, &rect);
            return static_cast<int>((rect.right - rect.left) * n / 100);
        }
        int operator""_vh(unsigned long long n) {
            auto hwnd = ege::getHWnd();
            RECT rect;
            GetClientRect(hwnd, &rect);
            return static_cast<int>((rect.bottom - rect.top) * n / 100);
        }
        int operator""_vh(long double n) {
            auto hwnd = ege::getHWnd();
            RECT rect;
            GetClientRect(hwnd, &rect);
            return static_cast<int>((rect.bottom - rect.top) * n / 100);
        }
    }
}