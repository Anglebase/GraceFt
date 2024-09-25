#pragma once

#include <GraceFt/Block.h>

namespace GFt {
    namespace Widget {
        /// @brief 主窗口
        /// @details 此类作为模板实现，构建一个非WIN32的包含标题栏、最大化、最小化、关闭按钮、内容区域的窗口
        class MainWindow : public Block {
            void* minbtn_;
            void* maxbtn_;
            void* closebtn_;
            void* label_;
            void* layout_;

        public:
            MainWindow(const std::wstring& title, const iRect& rect);
            virtual ~MainWindow();
            /// @brief 设置标题
            /// @param title 标题
            void setTitle(const std::wstring& title);
        };
    }
}