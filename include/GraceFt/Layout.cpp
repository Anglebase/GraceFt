#include "Layout.h"

namespace GFt {
    void Layout::setPadding(int padding) {
        leftPadding_ = padding;
        rightPadding_ = padding;
        topPadding_ = padding;
        bottomPadding_ = padding;
    }
    void Layout::setPadding(int leftright, int topbottom) {
        leftPadding_ = leftright;
        rightPadding_ = leftright;
        topPadding_ = topbottom;
        bottomPadding_ = topbottom;
    }
    void Layout::setPadding(int left, int top, int right, int bottom) {
        leftPadding_ = left;
        rightPadding_ = right;
        topPadding_ = top;
        bottomPadding_ = bottom;
    }

    int& Layout::leftPadding() { return leftPadding_; }
    int& Layout::rightPadding() { return rightPadding_; }
    int& Layout::topPadding() { return topPadding_; }
    int& Layout::bottomPadding() { return bottomPadding_; }

    int Layout::leftPadding() const { return leftPadding_; }
    int Layout::rightPadding() const { return rightPadding_; }
    int Layout::topPadding() const { return topPadding_; }
    int Layout::bottomPadding() const { return bottomPadding_; }
}
