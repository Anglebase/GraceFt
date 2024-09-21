#include "Path.h"

#include <ege.h>

#define PATH(x) (static_cast<ege::ege_path*>(x))

namespace GFt {
    using namespace ege;
    Path::Path() {
        data_ = ege_path_create();
    }
    Path::Path(const Path& other) {
        data_ = ege_path_clone(PATH(other.data_));
    }
    Path::Path(Path&& other) {
        data_ = other.data_;
        other.data_ = nullptr;
    }
    Path& Path::operator=(const Path& other) {
        if (this != &other) {
            if (data_)
                ege_path_destroy(PATH(data_));
            data_ = ege_path_clone(PATH(other.data_));
        }
        return *this;
    }
    Path& Path::operator=(Path&& other) {
        if (this != &other) {
            if (data_)
                ege_path_destroy(PATH(data_));
            data_ = other.data_;
            other.data_ = nullptr;
        }
        return *this;
    }
    Path::~Path() {
        if (data_)
            ege_path_destroy(PATH(data_));
        data_ = nullptr;
    }
    void Path::start() { ege_path_start(PATH(data_)); }
    void Path::close() { ege_path_close(PATH(data_)); }
    void Path::closeAll() { ege_path_closeall(PATH(data_)); }
    void Path::reset() { ege_path_reset(PATH(data_)); }
    void Path::reverse() { ege_path_reverse(PATH(data_)); }
    void Path::outline() { ege_path_outline(PATH(data_)); }
    fPoint Path::getLastPoint() const {
        auto p = ege_path_lastpoint(PATH(data_));
        return fPoint(p.x, p.y);
    }
    int Path::count() const { return ege_path_pointcount(PATH(data_)); }

    /// @details 对于输入的矩阵, 会默认其已经过齐次变换
    fRect Path::getBounds(const fMat3x3& transform) const {
        ege_transform_matrix matrix;
        matrix.m11 = transform[0][0];
        matrix.m12 = transform[0][1];
        matrix.m21 = transform[1][0];
        matrix.m22 = transform[1][1];
        matrix.m31 = transform[2][0];
        matrix.m32 = transform[2][1];
        ege_rect rect = ege_path_getbounds(PATH(data_), &matrix);
        return fRect(rect.x, rect.y, rect.w, rect.h);
    }
    /// @bug 由于EGE的ege_path_transform函数的实现问题, 导致无法正确实现transformBy函数(此函数会引发段错误)
    /// @warning 此函数会引发段错误
    void Path::transformBy(const fMat3x3& transform) {
        ege_transform_matrix matrix;
        matrix.m11 = transform[0][0];
        matrix.m12 = transform[0][1];
        matrix.m21 = transform[1][0];
        matrix.m22 = transform[1][1];
        matrix.m31 = transform[2][0];
        matrix.m32 = transform[2][1];
        ege_path_transform(PATH(data_), &matrix);
    }
    void Path::addPath(const Path& other, bool connect) {
        ege_path_addpath(PATH(data_), PATH(other.data_), connect);
    }
    void Path::addLine(const fLine& line) {
        ege_path_addline(PATH(data_), line.P1().x(), line.P1().y(), line.P2().x(), line.P2().y());
    }
    void Path::addArc(const fRect& rect, float startAngle, float sweepAngle) {
        ege_path_addarc(PATH(data_), rect.x(), rect.y(), rect.width(), rect.height(), startAngle, sweepAngle);
    }
    void Path::addCircle(const fCircle& circle) {
        ege_path_addcircle(PATH(data_), circle.origin().x(), circle.origin().y(), circle.radius());
    }
    void Path::addRect(const fRect& rect) {
        ege_path_addrect(PATH(data_), rect.x(), rect.y(), rect.width(), rect.height());
    }
    void Path::addEllipse(const fEllipse& ellipse) {
        ege_path_addellipse(PATH(data_),
            ellipse.rect().x(), ellipse.rect().y(),
            ellipse.rect().width(), ellipse.rect().height());
    }
    void Path::addPie(const fRect& rect, float startAngle, float sweepAngle) {
        ege_path_addpie(PATH(data_), rect.x(), rect.y(),
            rect.width(), rect.height(), startAngle, sweepAngle);
    }
    void Path::addBezier(const fBezier& bezier) {
        auto count = bezier.count();
        ege_point* p = new ege_point[count];
        for (int i = 0; i < count; ++i) {
            p[i].x = bezier.points[i].x();
            p[i].y = bezier.points[i].y();
        }
        ege_path_addbezier(PATH(data_), count, p);
        delete[] p;
    }
    void Path::addFitCurve(const fFitCurve& fitCurve) {
        auto count = fitCurve.count();
        ege_point* p = new ege_point[count];
        for (int i = 0; i < count; ++i) {
            p[i].x = fitCurve.points[i].x();
            p[i].y = fitCurve.points[i].y();
        }
        fitCurve.closed
            ? ege_path_addclosedcurve(PATH(data_), count, p, fitCurve.tension)
            : ege_path_addcurve(PATH(data_), count, p, fitCurve.tension);
        delete[] p;
    }
    void Path::addPolygon(const fPolygon& points) {
        auto count = points.count();
        ege_point* p = new ege_point[count];
        for (int i = 0; i < count; ++i) {
            p[i].x = points.points[i].x();
            p[i].y = points.points[i].y();
        }
        points.closed
            ? ege_path_addpolygon(PATH(data_), count, p)
            : ege_path_addpolyline(PATH(data_), count, p);
        delete[] p;
    }
    void Path::addText(const std::wstring& text, const fPoint& position, const Font& font) {
        int fontstyle = 0;
        if (font.weight() >= FontWeight::Bold)
            fontstyle |= FONTSTYLE_BOLD;
        if (font.italic())
            fontstyle |= FONTSTYLE_ITALIC;
        if (font.underline())
            fontstyle |= FONTSTYLE_UNDERLINE;
        if (font.strikeOut())
            fontstyle |= FONTSTYLE_STRIKEOUT;
        ege_path_addtext(
            PATH(data_), position.x(), position.y(),
            text.c_str(), font.size(),
            text.length(), font.fontFamily().c_str(), fontstyle);
    }
}