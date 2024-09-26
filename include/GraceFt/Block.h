#pragma once

#include <set>

#include <GraceFt/GraphInterface.h>
#include <GraceFt/EventMonitor.h>
#include <GraceFt/Event.h>
#include <GraceFt/Signal.hpp>

namespace GFt {
    /// @class Block
    /// @brief 块对象
    /// @details 块对象是UI的基本构件, 它提供了对象嵌入UI的基础设施
    ///          它掌管了整个UI的对象树, 管理事件的分发、传递和处理,
    ///          同时也负责视图重绘
    /// @ingroup 基础UI封装库
    class Block : public GraphInterface, public EventMonitor {
        struct CompareByZIndex {
            bool operator()(const Block* a, const Block* b) const;
        };
        int zIndex_;
        Block* parent_;
        std::multiset<Block*, CompareByZIndex> children_;
        bool sortChildren_ = true;
        bool hide_ = false;

        friend class Application;
        void handleOnDraw(const iPoint& pos, bool cilpO);
        void handleOnMouseButtonPress(MouseButtonPressEvent* event, const iPoint& pos = iPoint());
        void handleOnMouseButtonRelease(MouseButtonReleaseEvent* event, const iPoint& pos = iPoint());
        void handleOnMouseMove(MouseMoveEvent* event, const iPoint& pos = iPoint());
        void handleOnMouseWheel(MouseWheelEvent* event, const iPoint& pos = iPoint());
        void handleOnKeyPress(KeyPressEvent* event);
        void handleOnKeyRelease(KeyReleaseEvent* event);
        void handleOnTextInput(TextInputEvent* event);

    protected:
        /// @brief 此函数用于绘制内容
        /// @param g 绘图设备对象
        /// @details 此函数会在每一帧绘制时被调用, 用于绘制内容
        /// @note 若启用了裁剪优化，且此对象所在位置不与父对象的区域存在交集, 则此函数不会被调用
        void onDraw(Graphics& g) override;
        /// @brief 此函数用于处理鼠标按钮按下事件
        /// @details 此函数存在默认行为：当此对象被点击时捕获焦点
        /// @param event 鼠标按钮按下事件
        /// @note 鼠标处理函数会依据鼠标位置进行事件的捕获决断, 并将事件传递给相应的对象进行处理
        /// @note 具体的决断逻辑为：从根节点开始，查找首个满足鼠标位置在其区域内的对象，以该对象
        ///       为根节点再次重复此操作，直到某个对象不存在满足条件的子对象，则将事件传递给该对
        ///       象进行处理。该对象处理后若冒泡行为未被阻止，则再向上冒泡(即向父对象传递事件)，
        ///       直到根节点。
        /// @image html handlemouse.svg "鼠标事件处理示意图"
        void onMouseButtonPress(MouseButtonPressEvent* event) override;
        /// @brief 此函数用于处理鼠标按钮释放事件
        /// @param event 鼠标按钮释放事件
        /// @see onMouseButtonPress
        void onMouseButtonRelease(MouseButtonReleaseEvent* event) override;
        /// @brief 此函数用于处理鼠标移动事件
        /// @param event 鼠标移动事件
        /// @see onMouseButtonPress
        void onMouseMove(MouseMoveEvent* event) override;
        /// @brief 此函数用于处理鼠标滚轮事件
        /// @param event 鼠标滚轮事件
        /// @see onMouseButtonPress
        void onMouseWheel(MouseWheelEvent* event) override;
        /// @brief 此函数用于处理键盘按键按下事件
        /// @param event 键盘按键按下事件
        /// @note 键盘处理函数会依据当前焦点块进行事件的捕获决断, 并将事件传递给相应的对象进行处理
        /// @note 具体的决断逻辑为：从当前焦点块开始，调用其事件处理函数，之后若冒泡行为未被阻止，
        ///       则再向上冒泡(即向父对象传递事件)，直到根节点。
        /// @image html handlekey.svg "键盘事件处理示意图"
        /// @see BlockFocusManager
        void onKeyPress(KeyPressEvent* event) override;
        /// @brief 此函数用于处理键盘按键释放事件
        /// @param event 键盘按键释放事件
        /// @see onKeyPress
        void onKeyRelease(KeyReleaseEvent* event) override;
        /// @brief 此函数用于处理文本输入事件
        /// @param event 文本输入事件
        /// @see onKeyPress
        void onTextInput(TextInputEvent* event) override;

    public:
        /// @brief 构造函数
        /// @param rect 所在区域
        /// @param parent 父对象
        /// @param zIndex 层级
        /// @details 层级用于决定绘制事件的先后顺序和事件传递的优先级
        Block(const iRect& rect, Block* parent = nullptr, int zIndex = 0);
        virtual ~Block();
        /// @brief 添加子对象
        /// @note 如果子类为Layout的子类，且希望更新布局，则应当调用子类的 addItem() 方法添加子对象，否则将不会引发布局更新
        /// @param child 子对象
        /// @see RowLayout::addItem() ColumnLayout::addItem() GridLayout::addItem()
        void addChild(Block* child);
        /// @brief 移除子对象
        /// @note 如果子类为Layout的子类，且希望更新布局，则应当调用子类的 removeItem() 方法移除子对象，否则将不会引发布局更新
        /// @param child 子对象
        /// @see RowLayout::removeItem() ColumnLayout::removeItem() GridLayout::removeItem()
        void removeChild(Block* child);
        /// @brief 设置层级
        /// @param zIndex 层级
        /// @details 层级用于决定绘制事件和输入事件的先后顺序，层级越高，越先捕获输入事件，越后触发绘制事件
        /// @details 若层级相同，则根据添加顺序决定先后顺序
        /// @details 层级只决定同一对象的子对象之间的顺序
        /// @image html zindex.svg "层级关系示意图"
        void setZIndex(int zIndex);
        /// @brief 设置父对象
        /// @param parent 父对象
        void setParent(Block* parent);
        /// @brief 隐藏块对象
        /// @details 此操作影响当前对象及其所有子对象，被隐藏的对象将不会被触发任何事件
        void hide();
        /// @brief 显示块对象
        /// @details 此操作影响当前对象及其所有子对象
        /// @see hide()
        void show();

        /// @brief 获取层级
        /// @return 层级
        /// @see setZIndex
        int getZIndex() const;
        /// @brief 获取父对象
        /// @return 父对象
        Block* getParent() const;

        /// @brief 计算相对于指定对象的相对坐标
        /// @param block 指定对象
        /// @return 相对坐标
        /// @details 计算相对于指定对象的相对坐标，以此对象的左上角为原点，计算出相对于指定对象的坐标
        /// @note 若指定对象为nullptr，则返回相对于屏幕的绝对坐标
        iPoint relativePosFrom(Block* block) const;
        /// @brief 计算相对于屏幕的绝对坐标
        /// @return 绝对坐标
        iPoint absolutePos() const;
    public:
        Signal<Block*> HoverOn;     ///< 当鼠标悬停该对象时之上时触发该信号
        Signal<Block*> HoverOff;    ///< 当鼠标移开该对象时之上时触发该信号
        Signal<Block*> FocusOn;     ///< 当该对象获得焦点时触发该信号
        Signal<Block*> FocusOff;    ///< 当该对象失去焦点时触发该信号
    };
}