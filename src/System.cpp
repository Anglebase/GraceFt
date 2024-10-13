#include "System.h"
#include "ege.h"
#include <windows.h>

namespace GFt {
    namespace Sys {
        unsigned short getKeyState(Key key) {
            return GetKeyState(static_cast<int>(key));
        }
        unsigned short getAsyncKeyState(Key key) {
            return GetAsyncKeyState(static_cast<int>(key));
        }
        iPoint getCursorPosition() {
            POINT p;
            GetCursorPos(&p);
            return iPoint(p.x, p.y);
        }
        void setCursorPosition(iPoint pos) {
            SetCursorPos(pos.x(), pos.y());
        }
        std::wstring getCilpBoardText() {
            HWND hWnd = ege::getHWnd();
            ::OpenClipboard(hWnd);
            HANDLE hClipMemory = ::GetClipboardData(CF_UNICODETEXT);
            DWORD dwLength = ::GlobalSize(hClipMemory);
            LPBYTE lpClipMemory = (LPBYTE)::GlobalLock(hClipMemory);
            auto text = std::wstring((wchar_t*)lpClipMemory, dwLength / 2);
            ::GlobalUnlock(hClipMemory);
            ::CloseClipboard();
            return std::wstring(text);
        }
        void setCilpBoardText(std::wstring text_) {
            auto text = (std::wstring)text_;
            DWORD dwLength = text.size() + 1;
            HANDLE hGlobalMemory = ::GlobalAlloc(GHND, dwLength * 2 + 2);
            LPBYTE lpGlobalMemory = (LPBYTE)::GlobalLock(hGlobalMemory);
            for (unsigned int i = 0; i < dwLength; i++) {
                *lpGlobalMemory++ = (text[i] & 0xff);
                *lpGlobalMemory++ = (text[i] >> 8) & 0xff;
            }
            *lpGlobalMemory++ = (L'\0' & 0xff);
            *lpGlobalMemory = (L'\0' >> 8) & 0xff;
            ::GlobalUnlock(hGlobalMemory);
            HWND hWnd = ege::getHWnd();
            ::OpenClipboard(hWnd);
            ::EmptyClipboard();
            ::SetClipboardData(CF_UNICODETEXT, hGlobalMemory);
            ::CloseClipboard();
        }
        std::optional<std::string> getEnv(const std::string& name) {
            char* value = getenv(name.c_str());
            if (value == nullptr)
                return std::nullopt;
            return std::string(value);
        }
    }
}

