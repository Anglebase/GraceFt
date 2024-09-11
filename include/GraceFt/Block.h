#pragma once

#include <set>

#include <GraphInterface.h>
#include <EventMonitor.h>
#include <Event.h>

namespace GFt {
    /// @class Block
    /// @brief 块对象
    /// @details 块对象是UI的基本构件, 它掌管了整个UI的对象树, 管理事件的分发、传递和处理, 同时也负责视图重绘
    /// @ingroup 基础UI封装库
    class Block : public GraphInterface, public EventMonitor {
        struct CompareByZIndex {
            bool operator()(const Block* a, const Block* b) const;
        };
        int zIndex_;
        Block* parent_;
        std::set<Block*, CompareByZIndex> children_;

        friend class Application;
        void handleOnDraw();
        void handleOnMouseButtonPress(const MouseButtonPressEvent& event, const iPoint& pos = iPoint());
        void handleOnMouseButtonRelease(const MouseButtonReleaseEvent& event, const iPoint& pos = iPoint());
        void handleOnMouseMove(const MouseMoveEvent& event, const iPoint& pos = iPoint());
        void handleOnMouseWheel(const MouseWheelEvent& event, const iPoint& pos = iPoint());
        void handleOnKeyPress(const KeyPressEvent& event);
        void handleOnKeyRelease(const KeyReleaseEvent& event);
        void handleOnTextInput(const TextInputEvent& event);

    protected:
        /// @brief 此函数用于绘制内容
        /// @param rect 绘制区域(相对于窗口的绝对坐标)
        /// @details 此函数会在每一帧绘制时被调用, 用于绘制内容
        /// @note 若此对象所在位置不与任何可见区域存在交集, 则此函数不会被调用
        void onDraw(const iRect& rect) override;
        /// @brief 此函数用于处理鼠标按钮按下事件
        /// @param event 鼠标按钮按下事件
        /// @note 鼠标处理函数会依据鼠标位置进行事件的捕获决断, 并将事件传递给相应的对象进行处理
        void onMouseButtonPress(const MouseButtonPressEvent& event) override;
        /// @brief 此函数用于处理鼠标按钮释放事件
        /// @param event 鼠标按钮释放事件
        /// @see onMouseButtonPress
        void onMouseButtonRelease(const MouseButtonReleaseEvent& event) override;
        /// @brief 此函数用于处理鼠标移动事件
        /// @param event 鼠标移动事件
        /// @see onMouseButtonPress
        void onMouseMove(const MouseMoveEvent& event) override;
        /// @brief 此函数用于处理鼠标滚轮事件
        /// @param event 鼠标滚轮事件
        /// @see onMouseButtonPress
        void onMouseWheel(const MouseWheelEvent& event) override;
        /// @brief 此函数用于处理键盘按键按下事件
        /// @param event 键盘按键按下事件
        /// @note 键盘处理函数会依据当前焦点块进行事件的捕获决断, 并将事件传递给相应的对象进行处理
        /// @see BlockFocusManager
        void onKeyPress(const KeyPressEvent& event) override;
        /// @brief 此函数用于处理键盘按键释放事件
        /// @param event 键盘按键释放事件
        /// @see onKeyPress
        void onKeyRelease(const KeyReleaseEvent& event) override;
        /// @brief 此函数用于处理文本输入事件
        /// @param event 文本输入事件
        /// @see onKeyPress
        void onTextInput(const TextInputEvent& event) override;

    public:
        /// @brief 构造函数
        /// @param rect 所在区域
        /// @param parent 父对象
        /// @param zIndex 层级
        /// @details 层级用于决定绘制事件的先后顺序和事件传递的优先级
        Block(const iRect& rect, Block* parent = nullptr, int zIndex = 0);
        virtual ~Block();
        /// @brief 添加子对象
        /// @param child 子对象
        void addChild(Block* child);
        /// @brief 移除子对象
        /// @param child 子对象
        void removeChild(Block* child);
        /// @brief 设置层级
        /// @param zIndex 层级
        void setZIndex(int zIndex);
        /// @brief 设置父对象
        /// @param parent 父对象
        void setParent(Block* parent);

        /// @brief 获取层级
        /// @return 层级
        int getZIndex() const;
        /// @brief 获取父对象
        /// @return 父对象
        Block* getParent() const;
    };
}