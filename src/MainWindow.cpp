#include "MainWindow.h"

#include <numbers>

#include <Button.h>
#include <Graphics.h>
#include <BlockFocus.h>
#include <Window.h>
#include <Application.h>
#include <RowLayout.h>

namespace GFt {
    /// @cond IGNORE
    using namespace GFt::literals;
    // MainWindow 标题栏按钮基类
    class CtrlBtn : public Block {
    protected:
        bool state = false;
        void onMouseButtonPress(MouseButtonPressEvent* event) override {
            if (event->button() != MouseButton::Left)
                return;
            state = true;
            onToggled(state);
        }
        void onMouseButtonRelease(MouseButtonReleaseEvent* event) override {
            if (event->button() != MouseButton::Left)
                return;
            state = false;
            onToggled(state);
        }
    public:
        CtrlBtn(const iRect& rect, Block* parent) : Block(rect, parent) {}
        Signal<bool> onToggled;
    };
    // 最小化按钮
    class MiniBtn : public CtrlBtn {
    protected:
        void onDraw(Graphics& g) override {
            static PenSet ps(0_rgb, 2_px);
            static BrushSet bs(0xffffff_rgb);
            BlockHoverManager::getHoverOn() == this
                ? bs.setFillStyle(0xeeeeee_rgb)
                : bs.setFillStyle(0xffffff_rgb);
            g.bindBrushSet(&bs);
            g.bindPenSet(&ps);
            auto r = fRect{ rect().size() };
            g.drawFillRect(r);
            constexpr auto sc = 1 / (std::numbers::phi * 2);
            fLine l{
                Point<double>{ r.size().width()* sc, r.size().height() * 0.5 },
                Point<double>{ r.size().width()* (1 - sc), r.size().height() * 0.5 },
            };
            g.setAntiAliasing(true);
            g.drawLine(l);
        }
    public:
        MiniBtn(const iRect& rect, Block* parent) : CtrlBtn(rect, parent) {
            onToggled.connect([](bool state) {
                if (state)
                    Window::window()->minimize();
                });
        }
    };
    // 最大化按钮
    class MaxiBtn : public CtrlBtn {
        bool max_ = false;
    protected:
        void onDraw(Graphics& g) override {
            static PenSet ps(0_rgb, 2_px);
            static BrushSet bs(0xffffff_rgb);
            BlockHoverManager::getHoverOn() == this
                ? bs.setFillStyle(0xeeeeee_rgb)
                : bs.setFillStyle(0xffffff_rgb);
            g.bindBrushSet(&bs);
            g.bindPenSet(&ps);
            auto r = fRect{ fPoint{}, rect().size() };
            g.drawFillRect(r);
            constexpr auto sc = 1 / (std::numbers::phi * 2);
            fRect rc = r.centerby(Size<double>{ r.size().width()* sc, r.size().height()* sc });
            if (!max_) {
                fLine l1{
                    Point<double>{ rc.left(), rc.top() + rc.height() * (1 - sc) },
                    Point<double>{ rc.left(), rc.bottom() },
                };
                fLine l2{
                    Point<double>{ rc.left(), rc.bottom() },
                    Point<double>{ rc.left() + rc.width() * sc, rc.bottom() },
                };
                fLine l3{
                    Point<double>{ rc.left() + rc.width() * (1 - sc), rc.top() },
                    Point<double>{ rc.right(), rc.top() },
                };
                fLine l4{
                    Point<double>{ rc.right(), rc.top() },
                    Point<double>{ rc.right(), rc.top() + rc.height() * sc },
                };
                g.drawLine(l1);
                g.drawLine(l2);
                g.drawLine(l3);
                g.drawLine(l4);
            }
            else {
                fLine l1{
                    Point<double>{ rc.left(), rc.top() + rc.height() * (1 - sc) },
                    Point<double>{ rc.left() + rc.width() * sc, rc.top() + rc.height() * (1 - sc) },
                };
                fLine l2{
                    Point<double>{ rc.left() + rc.width() * sc, rc.top() + rc.height() * (1 - sc) },
                    Point<double>{ rc.left() + rc.width() * sc, rc.bottom() },
                };
                fLine l3{
                    Point<double>{ rc.left() + rc.width() * (1 - sc), rc.top() },
                    Point<double>{ rc.left() + rc.width() * (1 - sc), rc.top() + rc.height() * sc },
                };
                fLine l4{
                    Point<double>{ rc.left() + rc.width() * (1 - sc), rc.top() + rc.height() * sc },
                    Point<double>{ rc.right(), rc.top() + rc.height() * sc },
                };
                g.setAntiAliasing(true);
                g.drawLine(l1);
                g.drawLine(l2);
                g.drawLine(l3);
                g.drawLine(l4);
            }
        }
    public:
        MaxiBtn(const iRect& rect, Block* parent) : CtrlBtn(rect, parent) {
            onToggled.connect([this](bool state) {
                if (!state)
                    return;
                if (max_) {
                    Window::window()->restore();
                    max_ = false;
                }
                else {
                    Window::window()->maximize();
                    max_ = true;
                }
                });
        }
    };
    // 关闭按钮
    class CloseBtn : public CtrlBtn {
    protected:
        void onDraw(Graphics& g) override {
            static PenSet ps(0_rgb, 2_px);
            static BrushSet bs(0xffffff_rgb);
            if (BlockHoverManager::getHoverOn() == this) {
                bs.setFillStyle(state ? 0xbb0000_rgb : 0xff0000_rgb);
                ps.setColor(0xffffff_rgb);
            }
            else {
                bs.setFillStyle(0xffffff_rgb);
                ps.setColor(0_rgb);
            }
            g.bindBrushSet(&bs);
            g.bindPenSet(&ps);
            auto r = fRect{ fPoint{}, rect().size() };
            g.drawFillRect(r);
            constexpr auto sc = 1 / (std::numbers::phi * 2);
            fRect rc = r
                .centerby(rect().size() - iSize{ 2_px, 2_px })
                .centerby(Size<double>{ r.size().width()* sc, r.size().height()* sc });
            fLine l1{
                fPoint{ rc.left(), rc.top() },
                fPoint{ rc.right(), rc.bottom() },
            };
            fLine l2{
                fPoint{ rc.left(), rc.bottom() },
                fPoint{ rc.right(), rc.top() },
            };
            g.setAntiAliasing(true);
            g.drawLine(l1);
            g.drawLine(l2);
        }
    public:
        CloseBtn(const iRect& rect, Block* parent) : CtrlBtn(rect, parent) {
            onToggled.connect([](bool state) {
                if (!state)
                    Application::exit();
                });
        }
    };
    // 标题栏标签
    class TitleLabel : public Block {
        std::wstring title_;
        bool drag_ = false;
        iPoint drag_pos_;
        iPoint current_;
    protected:
        void onDraw(Graphics& g) override {
            static TextSet ts(0_rgb, Font{ L"等线", 1.2_em });
            static BrushSet bs(0xffffff_rgb);
            g.bindBrushSet(&bs);
            g.bindTextSet(&ts);
            auto r = fRect{ rect().size() };
            g.drawFillRect(r);
            g.drawText(title_, fRect{
                iPoint{ 5_px, 0_px },
                fSize{ r.size().width() - 5_px, r.size().height() } },
                TextAlign::Middle | TextAlign::Left);
        }
        void onMouseButtonPress(MouseButtonPressEvent* event) override {
            if (event->button() != MouseButton::Left)
                return;
            drag_pos_ = event->absolutePosition();
            current_ = event->absolutePosition() - event->position();
            drag_ = true;
        }
        void onMouseButtonRelease(MouseButtonReleaseEvent* event) override {
            if (event->button() != MouseButton::Left)
                return;
            drag_pos_ = iPoint{};
            current_ = iPoint{};
            drag_ = false;
        }
        void onMouseMove(MouseMoveEvent* event) override {
            if (!drag_)
                return;
            Window::window()->moveTo(
                current_ + (event->absolutePosition() - drag_pos_)
            );
        }
    public:
        TitleLabel(const iRect& rect, const std::wstring& title, Block* parent)
            : Block(rect, parent), title_(title) {}
        
        void setTitle(const std::wstring& title) {
            title_ = title;
        }
    };
    /// @endcond

    namespace Widget {
        MainWindow::MainWindow(const std::wstring& title, const iRect& rect)
            : Block(rect, nullptr) {
            // 移除边框
            Window::onWindowCreated.connect([](Window* w) {
                w->setFrameless(true);
                });
            // 创建行布局对象
            RowLayout* layout = new RowLayout{
                iRect{ 0,0,this->rect().width(), 2_em + 4_px },
                this, std::numeric_limits<int>::max() };
            // 当窗口大小改变时，更新布局
            Window::onWindowSizeChanged.connect([layout](Window* w) {
                layout->setWidth(100_vw);
                });
            Window::onWindowCreated.connect([layout](Window* w) {
                layout->setWidth(100_vw);
                });
            // 创建标题栏元素
            TitleLabel* titleLabel = new TitleLabel{ iRect{}, title, layout };
            MiniBtn* miniBtn = new MiniBtn{ iRect{ 0,0,2_em, 2_em }, layout };
            MaxiBtn* maxiBtn = new MaxiBtn{ iRect{ 0,0,2_em, 2_em }, layout };
            CloseBtn* closeBtn = new CloseBtn{ iRect{ 0,0,2_em, 2_em }, layout };
            // 应用布局
            layout->addItem(titleLabel, 1);
            layout->addItem(miniBtn, Layout::Fixed);
            layout->addItem(maxiBtn, Layout::Fixed);
            layout->addItem(closeBtn, Layout::Fixed);
            // 保存指针
            layout_ = layout;
            label_ = titleLabel;
            minbtn_ = miniBtn;
            maxbtn_ = maxiBtn;
            closebtn_ = closeBtn;
        }
        MainWindow::~MainWindow() {
            delete (RowLayout*)layout_;
            delete (MiniBtn*)minbtn_;
            delete (MaxiBtn*)maxbtn_;
            delete (CloseBtn*)closebtn_;
            delete (TitleLabel*)label_;
        }
        void MainWindow::setTitle(const std::wstring& title) {
            ((TitleLabel*)label_)->setTitle(title);
        }
    }
}