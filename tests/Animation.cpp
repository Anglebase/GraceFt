#include <Application.h>
#include <Animation.hpp>
#include <BlockFocus.h>
#include <Button.h>
#include <Geometry.hpp>
#include <Plan.h>

using namespace GFt;
using namespace GFt::Widget;
using namespace GFt::literals;

class View : public Block {
    iPoint mousePos_;
protected:
    void onDraw(Graphics& g) override {
        static BrushSet bs{ 0x999999_rgb };
        g.bindBrushSet(&bs);
        g.drawFillRect({ rect().size() });
        g.drawText(
            anim.isStopped() ? L"停止状态" :
            anim.isPlaying() ? L"播放状态" :
            anim.isPaused() ? L"暂停状态" : L"无效状态",
            iPoint{ 10, 10 }
        );
        if (BlockHoverManager::getHoverOn() == this) {
            g.drawText(L"动画演示对象", mousePos_ + iPoint{ 0,-1_em });
        }
    }
    void onMouseMove(MouseMoveEvent* e) override {
        mousePos_ = e->absolutePosition() - this->absolutePos();
    }
public:
    View(const iRect& rect, Block* parent = nullptr, int zIndex = 0)
        : Block(rect, parent, zIndex), anim{
            AnimationParams<int>{
                .setter = std::bind(&Block::setX, this, std::placeholders::_1),
                .initial = rect.x(),
                .target = 500,
                .duration = 1000,
                .trans_func = TransFuncs::smoothInOut,
            }
        } {
        AnimationManager::getInstance().registerAnimation(&this->anim);
        // anim.onFinished.connect(&anim, &AnimationAbstract::setPlay);
        anim.onUpdated.connect([this] {
            auto absPos = Application::getAbsoluteMousePosition();
            if (contains({ this->absolutePos(), this->rect().size() }, absPos))
                BlockHoverManager::setHoverOn(this);
            this->mousePos_ = absPos - this->absolutePos();
            });
    }
    ~View() {
        AnimationManager::getInstance().unregisterAnimation(&this->anim);
    }
    Animation<int> anim;
};

int main() {
    Window::onWindowCreated.connect([](Window* w) {
        Application::onEventCall.connect(&Application::updateBlockHoverState);
        });

    Block root{ iRect{100,100,800,600} };

    View view{ iRect{100,100,100,100}, &root };

    Button button{ iRect{100,250,100,50}, &root };
    button.text() = L"开始播放";
    button.onClicked.connect([&] {
        view.anim.setPlay();
        PlanEvent::getInstance().addPlanEvent(1000,
            [] { std::cout << "PlanEvent Callback Function triggered" << std::endl; }
        );
        });

    Button button2{ iRect{100,310,100,50}, &root };
    button2.text() = L"暂停播放";
    button2.onClicked.connect(&view.anim, &AnimationAbstract::setPause);
    button2.setEnable(false);

    Button button3{ iRect{100,370,100,50}, &root };
    button3.text() = L"终止播放";
    button3.onClicked.connect(&view.anim, &AnimationAbstract::setStop);

    Button button4{ iRect{100,430,100,50}, &root };
    button4.text() = L"输出FPS";
    button4.onClicked.connect([] {
        PlanEvent::getInstance().addPlanEvent([] {std::cout << "PlanEvent Callback Function triggered" << std::endl;});
        std::cout << "FPS: " << Application::getRealFps() << std::endl;
        std::cout << "Event: " << Application::getEventTime() << "us" << std::endl;
        std::cout << "Render: " << Application::getRenderTime() << "ms" << std::endl;
        });

    view.anim.onStateChanged.connect([&](AnimationStateType before, AnimationStateType after) {
        after == AnimationStateType::Stop
            ? button2.setEnable(false)
            : button2.setEnable(true);
        });

    auto window = Window::createWindow(&root);
    Application app{ window };
    std::cout << "Path: " << Application::localPath() << std::endl;
    window->show();
    return app.run();
}