#include "GraceFt/BrushSet.h"

#include <_private.inl>
#include <ege/ege.h>

#define BRUSH(x) (static_cast<BrushSetPrivate*>(brush_))

namespace GFt {
    using namespace _GFt_private_;
    void BrushSet::release() {
        if (BRUSH(brush_)->mode == static_cast<int>(BrushStyle::PolygonGradient)) {
            delete BRUSH(brush_)->polygon.points;
            delete BRUSH(brush_)->polygon.colors;
        }
    }
    BrushSet::BrushSet(const Color& color) {
        brush_ = new BrushSetPrivate;
        BRUSH(brush_)->mode = static_cast<int>(BrushStyle::Default);
        BRUSH(brush_)->def.color = EGERGBA(color.red(), color.green(), color.blue(), color.alpha());
        BRUSH(brush_)->def.style = static_cast<int>(FillStyle::Solid);
    }
    BrushSet::BrushSet(const BrushSet& other) {
        brush_ = new BrushSetPrivate;
        *BRUSH(brush_) = *BRUSH(&other);
    }

    BrushSet::BrushSet(BrushSet&& other) {
        brush_ = other.brush_;
        other.brush_ = nullptr;
    }
    BrushSet& BrushSet::operator=(const BrushSet& other) {
        if (this == &other)
            return *this;
        delete BRUSH(brush_);
        brush_ = new BrushSetPrivate;
        *BRUSH(brush_) = *BRUSH(&other);
        return *this;
    }
    BrushSet& BrushSet::operator=(BrushSet&& other) {
        if (this == &other)
            return *this;
        delete BRUSH(brush_);
        brush_ = other.brush_;
        other.brush_ = nullptr;
        return *this;
    }
    BrushSet::~BrushSet() {
        release();
        delete BRUSH(brush_);
    }

    void BrushSet::setFillStyle(const Color& color, FillStyle style) {
        release();
        BRUSH(brush_)->mode = static_cast<int>(BrushStyle::Default);
        BRUSH(brush_)->def.style = static_cast<int>(style);
        BRUSH(brush_)->def.color = EGERGBA(color.red(), color.green(), color.blue(), color.alpha());
    }
    void BrushSet::setTexture(const Texture& texture, const fRect& rect) {
        release();
        BRUSH(brush_)->mode = static_cast<int>(BrushStyle::Texture);
        BRUSH(brush_)->texture.x = rect.x();
        BRUSH(brush_)->texture.y = rect.y();
        BRUSH(brush_)->texture.w = rect.width();
        BRUSH(brush_)->texture.h = rect.height();
        BRUSH(brush_)->texture.data = texture.texture_;
    }

    void BrushSet::setLinearGradient(
        const fPoint& start, const Color& startColor,
        const fPoint& end, const Color& endColor) {
        release();
        BRUSH(brush_)->mode = static_cast<int>(BrushStyle::LinearGradient);
        BRUSH(brush_)->linear.x1 = start.x();
        BRUSH(brush_)->linear.y1 = start.y();
        BRUSH(brush_)->linear.x2 = end.x();
        BRUSH(brush_)->linear.y2 = end.y();
        BRUSH(brush_)->linear.color1 = EGERGBA(
            startColor.red(), startColor.green(), startColor.blue(), startColor.alpha());
        BRUSH(brush_)->linear.color2 = EGERGBA(
            endColor.red(), endColor.green(), endColor.blue(), endColor.alpha());
    }
    void BrushSet::setRadialGradient(
        const fPoint& center, const Color& centerColor,
        const fRect& rect, const Color& outerColor) {
        release();
        BRUSH(brush_)->mode = static_cast<int>(BrushStyle::RadialGradient);
        BRUSH(brush_)->radial.cx = center.x();
        BRUSH(brush_)->radial.cy = center.y();
        BRUSH(brush_)->radial.x = rect.x();
        BRUSH(brush_)->radial.y = rect.y();
        BRUSH(brush_)->radial.w = rect.width();
        BRUSH(brush_)->radial.h = rect.height();
        BRUSH(brush_)->radial.ccolor = EGERGBA(
            centerColor.red(), centerColor.green(), centerColor.blue(), centerColor.alpha());
        BRUSH(brush_)->radial.ocolor = EGERGBA(
            outerColor.red(), outerColor.green(), outerColor.blue(), outerColor.alpha());
    }

    void BrushSet::setPolygonGradient(
        const fPoint& center, const Color& centerColor,
        const std::vector<fPoint>& points, const std::vector<Color>& colors) {
        release();
        BRUSH(brush_)->mode = static_cast<int>(BrushStyle::PolygonGradient);
        BRUSH(brush_)->polygon.cx = center.x();
        BRUSH(brush_)->polygon.cy = center.y();
        BRUSH(brush_)->polygon.ccolor = EGERGBA(
            centerColor.red(), centerColor.green(), centerColor.blue(), centerColor.alpha());
        BRUSH(brush_)->polygon.num_points = static_cast<int>(points.size());
        BRUSH(brush_)->polygon.num_colors = static_cast<int>(colors.size());
        BRUSH(brush_)->polygon.points = new float[points.size() * 2];
        BRUSH(brush_)->polygon.colors = new unsigned int[colors.size()];
        for (int i = 0; i < points.size(); i++) {
            BRUSH(brush_)->polygon.points[i * 2] = points[i].x();
            BRUSH(brush_)->polygon.points[i * 2 + 1] = points[i].y();
        }
        for (int i = 0; i < colors.size(); i++)
            BRUSH(brush_)->polygon.colors[i] = EGERGBA(
                colors[i].red(), colors[i].green(), colors[i].blue(), colors[i].alpha());
    }
    BrushStyle BrushSet::getBrushStyle() const {
        return static_cast<BrushStyle>(BRUSH(brush_)->mode);
    }
}