#pragma once

#include <map>
#include <string_view>
#include <memory>

#include <GraceFt/Window.h>
#include <GraceFt/Button.h>
#include <GraceFt/Label.h>
#include <GraceFt/RowLayout.h>
#include <GraceFt/ColumnLayout.h>
#include <GraceFt/GridLayout.h>
#include <GraceFt/MainWindow.h>
#include <GraceFt/Radio.h>

#define DEF_DECLUI(ns, classname)                                         \
        struct X##classname final {                                       \
            /** @brief 块识别名称 */                                        \
            const std::string name;                                  \
            /** @brief 所在矩形 */                                         \
            GFt::iRect rect = GFt::iRect();                               \
            /** @brief 父块 */                                             \
            GFt::Block& parent;                                           \
            /** @brief 层级 */                                             \
            int zIndex = 0;                                               \
            /** @brief 内容定义 */                                         \
            std::function<void(ns::classname&)> content;                  \
            ~X##classname(){                                              \
            ns::classname* it = new ns::classname(rect, &parent, zIndex); \
            auto& uiManager = GFt::DeclarativeUIManager::getInstance();   \
            uiManager.addBlock(name, it);                                 \
            if (content)                                                  \
                content(*it);                                             \
            }                                                             \
        }
namespace GFt {
    /// @brief 定义式UI管理器
    /// @details 管理所有声明式UI块，并提供查找和添加和统一析构的功能
    class DeclarativeUIManager final {
        std::unordered_map<std::string, std::unique_ptr<Block>> blocks;
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
        Block* findBlock(const std::string& name);
        /// @brief 查找UI块名称
        /// @param block 块指针
        /// @return 块名称，如果没有找到则返回空字符串
        std::string findBlockByName(const Block* block) const;
        /// @brief 添加UI块
        /// @param name 块名称
        /// @param block 块指针
        /// @details 所有通过此方法添加的块都会被包装为std::unique_ptr，并自动管理生命周期
        ///          因此，不需要再手动delete块
        /// @throw 块名称不能重复，如果名称已存在，则会抛出异常
        void addBlock(const std::string& name, Block* block);
        /// @brief 移除UI块
        /// @param name 块名称
        /// @details 如果名称不存在，则不会有任何操作
        void removeBlock(const std::string& name);
        /// @brief 替换UI块
        /// @param name 块名称
        /// @param block 新的块指针
        /// @details 如果名称不存在，则会自动添加；如果名称已存在，则会自动替换
        void replaceBlock(const std::string& name, Block* block);
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
            const std::string name;
            /// @brief 所在矩形
            iRect rect;
            /// @brief 内容定义
            std::function<void(GFt::Block&)> content;
            ~XWindow();
        };
        /// @brief 主窗口声明式UI块
        /// @details 主窗口声明式UI块用于声明式地创建主窗口，并提供窗口内容的设置
        struct XMainWindow final {
            /// @brief 块识别名称
            const std::string name;
            /// @brief 窗口标题
            std::wstring title;
            /// @brief 所在矩形
            iRect rect;
            /// @brief 内容定义
            std::function<void(GFt::Widget::MainWindow&)> content;
            ~XMainWindow();
        };
        /// @brief 单选框声明式UI块
        /// @details 单选框声明式UI块用于声明式地创建单选框，并提供单选框内容的设置
        struct XRadioBox final {
            /// @brief 块识别名称
            const std::string name;
            /// @brief 关联的单选框管理器
            GFt::RadioManager& radioManager;
            /// @brief 所在矩形
            iRect rect = iRect();
            /// @brief 父块
            GFt::Block& parent;
            /// @brief Z轴层级
            int zIndex = 0;
            /// @brief 内容定义
            std::function<void(GFt::Widget::RadioBox&)> content;
            ~XRadioBox();
        };
        /// @brief 块声明式UI块
        /// @details 块声明式UI块用于声明式地创建块，并提供块内容的设置
        DEF_DECLUI(GFt, Block);
        /// @brief 按钮声明式UI块
        /// @details 按钮声明式UI块用于声明式地创建按钮，并提供按钮内容的设置
        DEF_DECLUI(GFt::Widget, Button);
        /// @brief 标签声明式UI块
        /// @details 标签声明式UI块用于声明式地创建标签，并提供标签内容的设置
        DEF_DECLUI(GFt::Widget, Label);
        /// @brief 行布局声明式UI块
        /// @details 行布局声明式UI块用于声明式地创建行布局，并提供布局内容的设置
        DEF_DECLUI(GFt, RowLayout);
        /// @brief 列布局声明式UI块
        /// @details 列布局声明式UI块用于声明式地创建列布局，并提供布局内容的设置
        DEF_DECLUI(GFt, ColumnLayout);
        /// @brief 网格布局声明式UI块
        /// @details 网格布局声明式UI块用于声明式地创建网格布局，并提供布局内容的设置
        DEF_DECLUI(GFt, GridLayout);
    }
}

#define BLOCK(name) (GFt::DeclarativeUIManager::getInstance().findBlock(name))