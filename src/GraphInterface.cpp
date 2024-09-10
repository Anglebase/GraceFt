#include "GraphInterface.h"

namespace GFt {
    GraphInterface::GraphInterface(iRect rect) :rect_(rect) {}
    GraphInterface::~GraphInterface() {}
    iRect& GraphInterface::rect() { return rect_; }
    const iRect& GraphInterface::rect() const { return rect_; }
}