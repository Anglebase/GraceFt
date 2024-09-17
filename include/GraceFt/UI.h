#pragma once

#include <map>
#include <Window.h>
#include <Button.h>
#include <Label.h>

namespace GFt {
    /// @brief 定义式UI管理器
    /// @details 管理所有声明式UI块，并提供查找和添加和统一析构的功能
    class DeclarativeUIManager final {
        std::map<std::string_view, Block*> blocks;
    private:
        DeclarativeUIManager() = default;
        DeclarativeUIManager(const DeclarativeUIManager&) = delete;
        DeclarativeUIManager(DeclarativeUIManager&&) = delete;
        DeclarativeUIManager& operator=(const DeclarativeUIManager&) = delete;
        DeclarativeUIManager& operator=(DeclarativeUIManager&&) = delete;
    public:
        ~DeclarativeUIManager();
        /// @brief 查找UI块
        /// @param name 块名称
        /// @return 块指针，如果没有找到则返回nullptr
        Block* findBlock(const std::string_view& name);
        /// @brief 添加UI块
        /// @param name 块名称
        /// @param block 块指针
        /// @details 块名称不能重复，如果名称已存在，则会抛出异常
        void addBlock(const std::string_view& name, Block* block);
        /// @brief 获取UI管理器实例
        /// @return UI管理器实例
        static DeclarativeUIManager& getInstance();
    };

    /// @brief 声明式UI框架
    namespace UI {
        /// @brief 窗口声明式UI块
        /// @details 窗口声明式UI块用于声明式地创建窗口，并提供窗口内容的设置
        struct XWindow final {
            /// @brief 块识别名称
            const std::string_view name;
            /// @brief 所在矩形
            iRect rect;
            /// @brief 内容定义
            std::function<void(GFt::Block&)> content;
            ~XWindow();
        };
        /// @brief 块声明式UI块
        /// @details 块声明式UI块用于声明式地创建块，并提供块内容的设置
        struct XBlock final {
            /// @brief 块识别名称
            const std::string_view name;
            /// @brief 所在矩形
            iRect rect;
            /// @brief 父块
            GFt::Block& parent;
            /// @brief 层级
            int zIndex = 0;
            /// @brief 内容定义
            std::function<void(GFt::Block&)> content;
            ~XBlock();
        };
        /// @brief 按钮声明式UI块
        /// @details 按钮声明式UI块用于声明式地创建按钮，并提供按钮内容的设置
        struct XButton final {
            /// @brief 块识别名称
            const std::string_view name;
            /// @brief 按钮文本
            std::wstring text;
            /// @brief 所在矩形
            iRect rect;
            /// @brief 父块
            GFt::Block& parent;
            /// @brief 层级
            int zIndex = 0;
            /// @brief 内容定义
            std::function<void(GFt::Widget::Button&)> content;
            ~XButton();
        };
        /// @brief 标签声明式UI块
        /// @details 标签声明式UI块用于声明式地创建标签，并提供标签内容的设置
        struct XLabel final {
            /// @brief 块识别名称
            const std::string_view name;
            /// @brief 标签文本
            std::wstring text;
            /// @brief 所在矩形
            iRect rect;
            /// @brief 父块
            GFt::Block& parent;
            /// @brief 层级
            int zIndex = 0;
            /// @brief 内容定义
            std::function<void(GFt::Widget::Label&)> content;
            ~XLabel();
        };
    }
}

#define DNAME(name) (std::move(std::string_view(#name)))
#define BLOCK(name) (GFt::DeclarativeUIManager::getInstance().findBlock(#name))