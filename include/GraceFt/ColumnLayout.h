#pragma once

#include <vector>
#include <GraceFt/Layout.h>
#include <GraceFt/Block.h>

namespace GFt {
    /// @brief 列布局类
    /// @ingroup 基础UI封装库
    class ColumnLayout : public Layout, public Block {
        int space_{ 0 };
        std::vector<std::pair<Block*, float>> blockLayout_;
        std::unordered_map<Block*, std::size_t> SS;

        void updateLayout();

    protected:
        /// @brief 重写onDraw方法，刷新布局
        void onDraw(Graphics& g) override;

    public:
        /// @brief 构造函数
        /// @param rect 布局的矩形区域
        /// @param parent 父对象
        /// @param zIndex 所在层级
        ColumnLayout(const iRect& rect, Block* parent = nullptr, int zIndex = 0);
        ~ColumnLayout() override;

        /// @brief 添加参与布局的块对象
        /// @param block 块对象
        /// @param widthProportion 块的高度占比，默认1.f，如果为 Layout::Fixed (或其它非正数值)则表示该块宽度为初始化时的固定值
        void addItem(Block* block, float widthProportion = 1.f);
        /// @brief 移除参与布局的块对象
        /// @param block 块对象
        void removeItem(Block* block);

        /// @brief 设置布局之间的间隔宽度
        /// @param space 间隔宽度
        void setSpace(int space);
        /// @brief 获取布局之间的间隔宽度
        /// @return 间隔宽度
        int getSpace() const;
    };
}