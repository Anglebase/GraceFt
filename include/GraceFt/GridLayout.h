#pragma once

#include <map>
#include <GraceFt/Rect.hpp>
#include <GraceFt/Layout.h>
#include <GraceFt/Block.h>

namespace GFt {
    /// @brief 网格布局类
    /// @ingroup 基础UI支持库
    class GridLayout : public Layout, public Block {
        int rows_{ 1 }, cols_{ 1 };
        int vspace_{ 0 }, hspace_{ 0 };
        std::map<Block*, iRect> griditems_;

        void updateLayout();
    public:
        /// @brief 重写onDraw方法，刷新布局
        void onDraw(const iRect& rect) override;

    public:
        /// @brief 构造函数
        /// @param rect 布局的矩形区域
        /// @param parent 父布局块
        /// @param zIndex 布局的层级
        GridLayout(const iRect& rect, Block* parent = nullptr, int zIndex = 0);
        ~GridLayout() override;

        /// @brief 添加子布局块
        /// @param item 子布局块
        /// @param rect 子布局块在网格中的相对矩形区域
        void addItem(Block* item, const iRect& rect);
        /// @brief 移除子布局块
        /// @param item 子布局块
        void removeItem(Block* item);

        /// @brief 设置网格间距
        /// @param space 网格间距
        void setSpace(int space);
        /// @brief 设置网格间距
        /// @param hspace 水平间距
        /// @param vspace 垂直间距
        void setSpace(int hspace, int vspace);
        /// @brief 设置网格大小
        /// @param size 网格大小，即行数、列数相同
        void setGridSize(int size);
        /// @brief 设置网格大小
        /// @param rows 行数
        /// @param cols 列数
        void setGridSize(int rows, int cols);

        /// @brief 设置垂直间距
        void setVSpace(int vspace);
        /// @brief 设置水平间距
        void setHSpace(int hspace);
        /// @brief 设置行数
        void setRows(int rows);
        /// @brief 设置列数
        void setCols(int cols);

        /// @brief 获取网格行数
        int getRows() const;
        /// @brief 获取网格列数
        int getCols() const;
        /// @brief 获取垂直间距
        int getVSpace() const;
        /// @brief 获取水平间距
        int getHSpace() const;
    };
}