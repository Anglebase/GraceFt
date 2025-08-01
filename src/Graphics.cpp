#include "GraceFt/Graphics.h"
#include <_private.inl>
#include <ege.h>

#define FONT(x) (static_cast<LOGFONTW*>(x))
#define IMG(x) (static_cast<PIMAGE>(x))
#define PATH(x) (static_cast<ege_path*>(x))
#define INIT_GRAPH                  \
        this->bindBrushSet(nullptr);\
        this->bindPenSet(nullptr);  \
        this->bindTextSet(nullptr); \
        this->setBackgroundColor(0xffffff_rgb); \
        this->setAntiAliasing(false)

namespace GFt {
    using namespace ege;
    using namespace _GFt_private_;
    using namespace literals;

    PenSet Graphics::defaultPenSet_{ 0x0_rgb };
    BrushSet Graphics::defaultBrushSet_{ 0xCFD1EFEC_rgba };
    TextSet Graphics::defaultTextSet_{ 0x0_rgb };

    Graphics::Graphics() {
        target_ = nullptr;
        targetPixelMap_ = nullptr;

        INIT_GRAPH;
    }
    Graphics::Graphics(Graphics&& other) {
        target_ = other.target_;
        targetPixelMap_ = other.targetPixelMap_;
        other.target_ = nullptr;
        other.targetPixelMap_ = nullptr;
    }
    Graphics& Graphics::operator=(Graphics&& other) {
        if (this == &other)
            return *this;
            target_ = other.target_;
            targetPixelMap_ = other.targetPixelMap_;
            other.target_ = nullptr;
            other.targetPixelMap_ = nullptr;
        return *this;
    }
    Graphics::~Graphics() {
        INIT_GRAPH;
    }
    void Graphics::reset() {
        INIT_GRAPH;
    }
    /// @note 若设置目标不为 nullptr, 则应保证后续调用此类的其它成员函数时, 目标对象未被析构
    /// @note 否则会引发段错误(指针越界访问)
    void Graphics::setTarget(PixelMap* target) {
        targetPixelMap_ = target;
        target_ = target->pixmap_;
        INIT_GRAPH;
    }
    void Graphics::setAntiAliasing(bool enable) {
        ege_enable_aa(enable, IMG(target_));
    }
    /// @details 对于传入的矩阵, 默认其已经过齐次变换, 即矩阵的最后一列为 (0, 0, 1)
    /// @code
    /// // 例如：将当前坐标系绕点 (100, 100) 逆时针旋转 45 度
    /// // 然后将变换后的坐标原点平移至 (100, 100)
    /// // 最后再以变换后的 (200, 200) 为中心进行缩放到原先的 2 倍
    /// g.setTransform(
    ///     rotate(makeVec2(100, 100), radians(45)) *
    ///     translate(makeVec2(100, 100)) *
    ///     scale(makeVec2(200, 200), makeVec2(2, 2));
    /// @endcode
    void Graphics::setTransform(const fMat3x3& matrix) {
        ege_transform_matrix mat;
        mat.m11 = matrix[0][0];
        mat.m12 = matrix[0][1];
        mat.m21 = matrix[1][0];
        mat.m22 = matrix[1][1];
        mat.m31 = matrix[2][0];
        mat.m32 = matrix[2][1];
        ege_set_transform(&mat, IMG(target_));
    }
    void Graphics::resetTransform() {
        ege_transform_reset(IMG(target_));
    }
    PixelMap* Graphics::getTarget() const {
        return targetPixelMap_;
    }
    fMat3x3 Graphics::getTransform() const {
        ege_transform_matrix mat;
        ege_get_transform(&mat, IMG(target_));
        fMat3x3 result = fMat3x3::I();
        result[0][0] = mat.m11;
        result[0][1] = mat.m12;
        result[1][0] = mat.m21;
        result[1][1] = mat.m22;
        result[2][0] = mat.m31;
        result[2][1] = mat.m32;
        return result;
    }
    void Graphics::clear() {
        clearviewport(IMG(target_));
    }

    int Graphics::textWidth(wchar_t c, const std::vector<std::wstring>& fonts) {
        if (fonts.empty())
            return ege::textwidth(c, IMG(target_));
        LOGFONTW font_buf, font_env;
        int ret = 0;
        getfont(&font_env, IMG(target_));
        getfont(&font_buf, IMG(target_));
        for (auto& font : fonts) {
            wcscpy_s(font_buf.lfFaceName, LF_FACESIZE, font.c_str());
            setfont(&font_buf, IMG(target_));
            WORD index = 0;
            GetGlyphIndicesW(
                getHDC(IMG(target_)), &c, 1,
                &index, GGI_MARK_NONEXISTING_GLYPHS);
            if (index != 0xFFFF) {
                ret = ege::textwidth(c, IMG(target_));
                break;
            }
        }
        setfont(&font_env, IMG(target_));
        return ret;
    }
    int Graphics::textHeight(wchar_t c, const std::vector<std::wstring>& fonts) {
        if (fonts.empty())
            return ege::textheight(c, IMG(target_));
        LOGFONTW font_buf, font_env;
        int ret = 0;
        getfont(&font_env, IMG(target_));
        getfont(&font_buf, IMG(target_));
        for (auto& font : fonts) {
            wcscpy_s(font_buf.lfFaceName, LF_FACESIZE, font.c_str());
            setfont(&font_buf, IMG(target_));
            WORD index = 0;
            GetGlyphIndicesW(
                getHDC(IMG(target_)), &c, 1,
                &index, GGI_MARK_NONEXISTING_GLYPHS);
            if (index != 0xFFFF) {
                ret = ege::textheight(c, IMG(target_));
                break;
            }
        }
        setfont(&font_env, IMG(target_));
        return ret;
    }

    int Graphics::textWidth(const std::wstring& text, const std::vector<std::wstring>& fonts) {
        if (fonts.empty())
            return ege::textwidth(text.c_str(), IMG(target_));
        int ret = 0;
        for (auto& c : text)
            ret += textWidth(c, fonts);
        return ret;
    }
    int Graphics::textHeight(const std::wstring& text, const std::vector<std::wstring>& fonts) {
        if (fonts.empty())
            return ege::textheight(text.c_str(), IMG(target_));
        int ret = 0;
        using namespace std;
        for (auto& c : text)
            ret = max(ret, textHeight(c, fonts));
        return ret;
    }

    void Graphics::setBackgroundColor(const Color& color) {
        setbkcolor(EGERGBA(color.red(), color.green(), color.blue(), color.alpha()), IMG(target_));
    }
    void Graphics::bindPenSet(PenSet* penSet) {
        if (penSet == nullptr) {
            bindPenSet(&defaultPenSet_);
            return;
        }
        PenSetPrivate* pPS = static_cast<PenSetPrivate*>(penSet->pen_);
        setlinecolor(pPS->color, IMG(target_));
        setlinestyle(pPS->line_type, pPS->userdef, pPS->width, IMG(target_));
        setlinecap((line_cap_type)pPS->startcap_type, (line_cap_type)pPS->endcap_type, IMG(target_));
        setlinejoin((line_join_type)pPS->join_type, pPS->miterlimit, IMG(target_));
    }
    void Graphics::bindBrushSet(BrushSet* brushSet) {
        if (brushSet == nullptr) {
            bindBrushSet(&defaultBrushSet_);
            return;
        }
        BrushSetPrivate* pBS = static_cast<BrushSetPrivate*>(brushSet->brush_);
        switch (static_cast<BrushStyle>(pBS->mode)) {
        case BrushStyle::Default:
            setfillstyle(pBS->def.style, pBS->def.color, IMG(target_));
            break;
        case BrushStyle::LinearGradient:
            ege_setpattern_lineargradient(
                pBS->linear.x1, pBS->linear.y1, pBS->linear.color1,
                pBS->linear.x2, pBS->linear.y2, pBS->linear.color2,
                IMG(target_)
            );
            break;
        case BrushStyle::RadialGradient:
            ege_setpattern_ellipsegradient(
                { pBS->radial.cx, pBS->radial.cy }, pBS->radial.ccolor,
                pBS->radial.x, pBS->radial.y, pBS->radial.w, pBS->radial.h,
                pBS->radial.ocolor, IMG(target_)
            );
            break;
        case BrushStyle::Texture:
            ege_setpattern_texture(
                IMG(pBS->texture.data),
                pBS->texture.x, pBS->texture.y,
                pBS->texture.w, pBS->texture.h,
                IMG(target_));
            break;
        case BrushStyle::PolygonGradient:
            ege_setpattern_pathgradient(
                { pBS->polygon.cx, pBS->polygon.cy }, pBS->polygon.ccolor,
                pBS->polygon.num_points, (ege_point*)pBS->polygon.points,
                pBS->polygon.num_colors, (color_t*)pBS->polygon.colors,
                IMG(target_)
            );
            break;
        }
    }
    void Graphics::bindTextSet(TextSet* textSet) {
        if (textSet == nullptr) {
            bindTextSet(&defaultTextSet_);
            return;
        }
        settextcolor(textSet->color_, IMG(target_));
        setfont(FONT(textSet->font_.font_), IMG(target_));
        setbkmode(textSet->transparent_ ? TRANSPARENT : OPAQUE, IMG(target_));
    }

    void Graphics::drawLine(const fLine& line) {
        ege_line(line.P1().x(), line.P1().y(), line.P2().x(), line.P2().y(), IMG(target_));
    }
    void Graphics::drawRect(const fRect& rect) {
        ege_rectangle(rect.x(), rect.y(), rect.width(), rect.height(), IMG(target_));
    }
    void Graphics::drawRoundRect(const fRoundRect& rect) {
        ege_roundrect(
            rect.rect().x(), rect.rect().y(), rect.rect().width(), rect.rect().height(),
            rect.radiusTopLeft(), rect.radiusTopRight(),
            rect.radiusBottomLeft(), rect.radiusBottomRight(),
            IMG(target_)
        );
    }
    void Graphics::drawArc(const fRect& rect, float startAngle, float sweepAngle) {
        ege_arc(
            rect.x(), rect.y(), rect.width(), rect.height(),
            startAngle, sweepAngle, IMG(target_)
        );
    }
    void Graphics::drawEllipse(const fEllipse& ellipse) {
        ege_ellipse(
            ellipse.rect().x(), ellipse.rect().y(),
            ellipse.rect().width(), ellipse.rect().height(),
            IMG(target_)
        );
    }
    void Graphics::drawCircle(const fCircle& circle) {
        ege_circle(circle.origin().x(), circle.origin().y(), circle.radius(), IMG(target_));
    }
    void Graphics::drawPie(const fRect& rect, float startAngle, float sweepAngle) {
        ege_pie(
            rect.x(), rect.y(), rect.width(), rect.height(),
            startAngle, sweepAngle, IMG(target_)
        );
    }
    void Graphics::drawPolygon(const fPolygon& polygon) {
        bool closed = polygon.isClosed();
        auto count = polygon.count();
        if (count < 2)
            return;
        ege_point* points = new ege_point[count + (closed ? 1 : 0)];
        for (int i = 0; i < count; ++i) {
            points[i].x = polygon.points[i].x();
            points[i].y = polygon.points[i].y();
        }
        if (closed) {
            points[count].x = polygon.points[0].x();
            points[count].y = polygon.points[0].y();
        }
        ege_drawpoly(count + (closed ? 1 : 0), points, IMG(target_));
        delete[] points;
    }
    void Graphics::drawBezier(const fBezier& curve) {
        auto count = curve.count();
        ege_point* points = new ege_point[count];
        for (int i = 0; i < count; ++i) {
            points[i].x = curve.points[i].x();
            points[i].y = curve.points[i].y();
        }
        ege_drawbezier(count, points, IMG(target_));
        delete[] points;
    }
    void Graphics::drawFitCurve(const fFitCurve& curve) {
        auto count = curve.count();
        ege_point* points = new ege_point[count];
        for (int i = 0; i < count; ++i) {
            points[i].x = curve.points[i].x();
            points[i].y = curve.points[i].y();
        }
        curve.isClosed()
            ? ege_drawcurve(count, points, curve.tension, IMG(target_))
            : ege_drawclosedcurve(count, points, curve.tension, IMG(target_));
        delete[] points;
    }
    void Graphics::drawPath(const Path& path, const fPoint& pos) {
        ege_drawpath(PATH(path.data_), pos.x(), pos.y(), IMG(target_));
    }
    void Graphics::drawFillRect(const fRect& rect) {
        ege_fillrect(rect.x(), rect.y(), rect.width(), rect.height(), IMG(target_));
    }
    void Graphics::drawFillRoundRect(const fRoundRect& rect) {
        ege_fillroundrect(
            rect.rect().x(), rect.rect().y(), rect.rect().width(), rect.rect().height(),
            rect.radiusTopLeft(), rect.radiusTopRight(),
            rect.radiusBottomLeft(), rect.radiusBottomRight(),
            IMG(target_)
        );
    }
    void Graphics::drawFillPie(const fRect& rect, float startAngle, float sweepAngle) {
        ege_fillpie(
            rect.x(), rect.y(), rect.width(), rect.height(),
            startAngle, sweepAngle, IMG(target_)
        );
    }
    /// @details 如果传入的多边形不是闭合的, 则此函数无效果
    void Graphics::drawFillPolygon(const fPolygon& polygon) {
        if (!polygon.isClosed() || polygon.count() < 2)
            return;
        auto count = polygon.count();
        ege_point* points = new ege_point[count];
        for (int i = 0; i < count; ++i) {
            points[i].x = polygon.points[i].x();
            points[i].y = polygon.points[i].y();
        }
        ege_fillpoly(count, points, IMG(target_));
        delete[] points;
    }
    void Graphics::drawFillEllipse(const fEllipse& rect) {
        ege_fillellipse(
            rect.rect().x(), rect.rect().y(),
            rect.rect().width(), rect.rect().height(),
            IMG(target_)
        );
    }
    void Graphics::drawFillCircle(const fCircle& circle) {
        ege_fillcircle(circle.origin().x(), circle.origin().y(), circle.radius(), IMG(target_));
    }
    /// @details 如果传入的曲线不是闭合的, 则此函数无效果
    void Graphics::drawFillFitCurve(const fFitCurve& curve) {
        if (!curve.isClosed())
            return;
        auto count = curve.count();
        ege_point* points = new ege_point[count];
        for (int i = 0; i < count; ++i) {
            points[i].x = curve.points[i].x();
            points[i].y = curve.points[i].y();
        }
        ege_fillclosedcurve(count, points, curve.tension, IMG(target_));
        delete[] points;
    }
    void Graphics::drawFillPath(const Path& path, const fPoint& pos) {
        ege_fillpath(PATH(path.data_), pos.x(), pos.y(), IMG(target_));
    }
    void Graphics::drawImage(const fPoint& pos, const PixelMap& pixelMap) {
        ege_drawimage(IMG(pixelMap.pixmap_), pos.x(), pos.y(), IMG(target_));
    }
    void Graphics::drawImage(const fRect& dest, const fRect& src, const PixelMap& pixelMap) {
        ege_drawimage(
            IMG(pixelMap.pixmap_),
            dest.x(), dest.y(), dest.width(), dest.height(),
            src.x(), src.y(), src.width(), src.height(),
            IMG(target_)
        );
    }
    void Graphics::drawAlphaImage(const PixelMap& pixelMap, const fPoint& dest, const fRect& src) {
        putimage_withalpha(
            IMG(target_),
            IMG(pixelMap.pixmap_),
            dest.x(), dest.y(),
            src.x(), src.y(), src.width(), src.height()
        );
    }
    void Graphics::drawAlphaImage(const PixelMap& pixelMap, const fRect& dest, const fRect& src, bool smooth) {
        putimage_withalpha(
            IMG(target_),
            IMG(pixelMap.pixmap_),
            dest.x(), dest.y(), dest.width(), dest.height(),
            src.x(), src.y(), src.width(), src.height(),
            smooth
        );
    }
    int Graphics::drawText(
        const std::wstring& text, const fPoint& pos,
        const std::vector<std::wstring>& fonts, bool show) {
        // 若没有指定字体, 则使用当前配置字体
        if (fonts.empty()) {
            ege_outtextxy(pos.x(), pos.y(), text.c_str(), IMG(target_));
            return textwidth(text.c_str(), IMG(target_));
        }
        // 否则, 尝试使用指定的字体
        std::size_t* count = new size_t[text.length()]{ 0 };
        int width = 0;
        LOGFONTW fs, fset;
        // 保存当前字体环境
        getfont(&fs, IMG(target_));
        getfont(&fset, IMG(target_));
        // 查找字体的支持情况
        for (std::size_t i = 0; i < fonts.size(); ++i) {
            WORD* indices = new WORD[text.length()]{ 0 };
            wcscpy_s(fset.lfFaceName, LF_FACESIZE, fonts[i].c_str());
            setfont(&fset, IMG(target_));
            GetGlyphIndicesW(
                getHDC(IMG(target_)), text.c_str(), text.length(),
                indices, GGI_MARK_NONEXISTING_GLYPHS);
            for (std::size_t j = 0; j < text.length(); ++j)
                if (indices[j] != 0xFFFF && count[j] == 0)
                    count[j] = i + 1;
            delete[] indices;
        }
        // 输出文字
        for (std::size_t i = 0; i < text.length(); ++i) {
            if (count[i])
                wcscpy_s(fset.lfFaceName, LF_FACESIZE, fonts[count[i] - 1].c_str());
            LOGFONTW* pfs = count == 0 ? &fs : &fset;
            setfont(pfs, IMG(target_));
            if (show)
                ege_outtextxy(pos.x() + width, pos.y(), text[i], IMG(target_));
            // 统计宽度
            width += textwidth(text[i], IMG(target_));
        }
        // 还原字体环境
        setfont(&fs, IMG(target_));
        delete[] count;
        return width;
    }
    /// @details 若传入了无效的 flags, 则此函数将会忽略它们, 并使用默认的对齐方式(左上对齐)
    int Graphics::drawText(const std::wstring& text, const fRect& rect, int flags, const std::vector<std::wstring>& fonts) {
        TextAlign halign = static_cast<TextAlign>(flags & 0x0F);
        TextAlign valign = static_cast<TextAlign>((flags >> 4) & 0x0F);
        float x = rect.x();
        float y = rect.y();
        switch (halign) {
        case TextAlign::Center:
            x += rect.width() / 2.f - textwidth(text.c_str(), IMG(target_)) / 2.f;
            break;
        case TextAlign::Right:
            x += rect.width() - textwidth(text.c_str(), IMG(target_));
            break;
        case TextAlign::Left:
            [[fallthrough]];
        default:
            break;
        }
        switch (valign) {
        case TextAlign::Center:
            y += rect.height() / 2.f - textheight(text.c_str(), IMG(target_)) / 2.f;
            break;
        case TextAlign::Bottom:
            y += rect.height() - textheight(text.c_str(), IMG(target_));
            break;
        case TextAlign::Top:
            [[fallthrough]];
        default:
            break;
        }
        return drawText(text, fPoint{ x, y }, fonts);
    }
}