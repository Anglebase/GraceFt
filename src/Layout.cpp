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
    void Layout::setLeftPadding(int left) {
        leftPadding_ = left;
        setShouldUpdateLayout();
    }
    void Layout::setTopPadding(int top) {
        topPadding_ = top;
        setShouldUpdateLayout();
    }
    void Layout::setRightPadding(int right) {
        rightPadding_ = right;
        setShouldUpdateLayout();
    }
    void Layout::setBottomPadding(int bottom) {
        bottomPadding_ = bottom;
        setShouldUpdateLayout();
    }

    int Layout::getLeftPadding() const { return leftPadding_; }
    int Layout::getTopPadding() const { return topPadding_; }
    int Layout::getRightPadding() const { return rightPadding_; }
    int Layout::getBottomPadding() const { return bottomPadding_; }
    void Layout::setShouldUpdateLayout(bool shouldUpdateLayout) {
        shouleUpdateLayout_ = shouldUpdateLayout;
    }
    bool Layout::shouldUpdateLayout() const {
        return shouleUpdateLayout_;
    }
}
