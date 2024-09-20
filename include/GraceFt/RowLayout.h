#pragma once

#include <map>
#include <GraceFt/Layout.h>
#include <GraceFt/Block.h>

namespace GFt {
    /// @brief 行布局类
    /// @ingroup 基础UI支持库
    class RowLayout : public Layout, public Block {
        int space_{ 0 };
        std::map<Block*, float> blockLayout_;

        void updateLayout();

    protected:
        /// @brief 重写onDraw方法，刷新布局
        void onDraw(const iRect& rect) override;

    public:
        /// @brief 构造函数
        /// @param rect 布局的矩形区域
        /// @param parent 父对象
        /// @param zIndex 所在层级
        RowLayout(const iRect& rect, Block* parent = nullptr, int zIndex = 0);
        ~RowLayout() override;

        /// @brief 添加参与布局的块对象
        /// @param block 块对象
        /// @param widthProportion 块的宽度占比，默认1.f
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