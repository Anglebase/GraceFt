#include "PenSet.h"

#include <ege.h>
#include <_private.inl>

#define PEN(x) (static_cast<_GFt_private_::PenSetPrivate*>(x))

namespace GFt {
    using namespace ege;
    PenSet::PenSet(const Color& color, int width) {
        pen_ = new _GFt_private_::PenSetPrivate;
        PEN(pen_)->color = EGERGBA(color.red(), color.green(), color.blue(), color.alpha());
        PEN(pen_)->width = width;
        PEN(pen_)->line_type = SOLID_LINE;
        PEN(pen_)->startcap_type = LINECAP_ROUND;
        PEN(pen_)->endcap_type = LINECAP_ROUND;
        PEN(pen_)->join_type = LINEJOIN_ROUND;
        PEN(pen_)->userdef = 0;
    }
    PenSet::PenSet(const PenSet& other) {
        pen_ = new _GFt_private_::PenSetPrivate;
        PEN(pen_)->width = PEN(other.pen_)->width;
        PEN(pen_)->line_type = PEN(other.pen_)->line_type;
        PEN(pen_)->userdef = PEN(other.pen_)->userdef;
    }
    PenSet::PenSet(PenSet&& other) {
        pen_ = other.pen_;
        other.pen_ = nullptr;
    }
    PenSet& PenSet::operator=(const PenSet& other) {
        if (this != &other) {
            PEN(pen_)->width = PEN(other.pen_)->width;
            PEN(pen_)->line_type = PEN(other.pen_)->line_type;
            PEN(pen_)->userdef = PEN(other.pen_)->userdef;
        }
        return *this;
    }
    PenSet& PenSet::operator=(PenSet&& other) {
        if (this != &other) {
            delete PEN(pen_);
            pen_ = other.pen_;
            other.pen_ = nullptr;
        }
        return *this;
    }
    PenSet::~PenSet() {
        delete PEN(pen_);
        pen_ = nullptr;
    }

    void PenSet::setColor(const Color& color) {
        PEN(pen_)->color = EGERGBA(color.red(), color.green(), color.blue(), color.alpha());
    }

    void PenSet::setLineWidth(int width) { PEN(pen_)->width = width; }
    /// @details 此函数指定 LineStyle::UserDefined 是无效的
    void PenSet::setLineStyle(LineStyle style) {
        switch (style) {
        case LineStyle::Solid:
            PEN(pen_)->line_type = SOLID_LINE;
            break;
        case LineStyle::Dash:
            PEN(pen_)->line_type = CENTER_LINE;
            break;
        case LineStyle::Dot:
            PEN(pen_)->line_type = DOTTED_LINE;
            break;
        case LineStyle::DashDot:
            PEN(pen_)->line_type = DASHED_LINE;
            break;
        case LineStyle::Null:
            PEN(pen_)->line_type = NULL_PEN;
            break;
        default:
            break;
        }
    }
    /// @details 调用此函数时, 会自动设置 LineStyle::UserDefined
    void PenSet::setLineStyle(short style) {
        PEN(pen_)->line_type = USERBIT_LINE;
        PEN(pen_)->userdef = style;
    }
    void PenSet::setCapStyle(CapStyle style) {
        setStartCap(style);
        setEndCap(style);
    }
    void PenSet::setStartCap(CapStyle style) {
        switch (style) {
        case CapStyle::Flat:
            PEN(pen_)->startcap_type = LINECAP_FLAT;
            break;
        case CapStyle::Square:
            PEN(pen_)->startcap_type = LINECAP_SQUARE;
            break;
        case CapStyle::Round:
            PEN(pen_)->startcap_type = LINECAP_ROUND;
            break;
        default:
            break;
        }
    }
    void GFt::PenSet::setEndCap(CapStyle style) {
        switch (style) {
        case CapStyle::Flat:
            PEN(pen_)->endcap_type = LINECAP_FLAT;
            break;
        case CapStyle::Square:
            PEN(pen_)->endcap_type = LINECAP_SQUARE;
            break;
        case CapStyle::Round:
            PEN(pen_)->endcap_type = LINECAP_ROUND;
            break;
        default:
            break;
        }
    }
    void PenSet::setJoinStyle(JoinStyle style, float miterLimit) {
        switch (style) {
        case JoinStyle::Miter:
            PEN(pen_)->join_type = LINEJOIN_MITER;
            break;
        case JoinStyle::Bevel:
            PEN(pen_)->join_type = LINEJOIN_BEVEL;
            break;
        case JoinStyle::Round:
            PEN(pen_)->join_type = LINEJOIN_ROUND;
            break;
        default:
            break;
        }
        PEN(pen_)->miterlimit = miterLimit;
    }
    Color PenSet::getColor() const {
        return Color(
            EGEGET_R(PEN(pen_)->color),
            EGEGET_G(PEN(pen_)->color),
            EGEGET_B(PEN(pen_)->color),
            EGEGET_A(PEN(pen_)->color)
        );
    }
    int PenSet::getPenWidth() const {
        return PEN(pen_)->width;
    }
    LineStyle PenSet::getPenStyle() const {
        switch (PEN(pen_)->line_type) {
        case SOLID_LINE:
            return LineStyle::Solid;
        case CENTER_LINE:
            return LineStyle::Dash;
        case DOTTED_LINE:
            return LineStyle::Dot;
        case DASHED_LINE:
            return LineStyle::DashDot;
        case NULL_PEN:
            return LineStyle::Null;
        case USERBIT_LINE:
            return LineStyle::UserDefined;
        }
        return LineStyle::Solid;
    }
    /// @details 此函数仅在线型为 LineStyle::UserDefined 时有效, 否则返回 0
    short PenSet::getUserPenStyle() const {
        if (PEN(pen_)->line_type != USERBIT_LINE)
            return 0;
        return PEN(pen_)->userdef;
    }
    /// @details 此函数只会返回起始线帽的样式, 若两端线帽不同, 则应该分别调用 getStartCap() 和 getEndCap()
    CapStyle PenSet::getCapStyle() const {
        return getStartCap();
    }
    CapStyle PenSet::getStartCap() const {
        switch (PEN(pen_)->startcap_type) {
        case LINECAP_FLAT:
            return CapStyle::Flat;
        case LINECAP_SQUARE:
            return CapStyle::Square;
        case LINECAP_ROUND:
            return CapStyle::Round;
        }
        return CapStyle::Round;
    }
    CapStyle PenSet::getEndCap() const {
        switch (PEN(pen_)->endcap_type) {
        case LINECAP_FLAT:
            return CapStyle::Flat;
        case LINECAP_SQUARE:
            return CapStyle::Square;
        case LINECAP_ROUND:
            return CapStyle::Round;
        }
        return CapStyle::Round;
    }
    JoinStyle PenSet::getJoinStyle() const {
        switch (PEN(pen_)->join_type) {
        case LINEJOIN_MITER:
            return JoinStyle::Miter;
        case LINEJOIN_BEVEL:
            return JoinStyle::Bevel;
        case LINEJOIN_ROUND:
            return JoinStyle::Round;
        }
        return JoinStyle::Round;
    }
}