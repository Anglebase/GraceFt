#include <Application.h>
#include <Animation.hpp>
#include <Button.h>

using namespace GFt;
using namespace GFt::Widget;
using namespace GFt::literals;

class View : public Block {
protected:
    void onDraw(Graphics& g) {
        static BrushSet bs{ 0x999999_rgb };
        g.bindBrushSet(&bs);
        g.drawFillRect({ rect().size() });
        g.drawText(
            anim.isStopped() ? L"停止状态" :
            anim.isPlaying() ? L"播放状态" :
            anim.isPaused() ? L"暂停状态" : L"无效状态",
            iPoint{ 10, 10 }
        );
    }
public:
    View(const iRect& rect, Block* parent = nullptr, int zIndex = 0)
        : Block(rect, parent, zIndex), anim{
            AnimationParams<int>{
                .setter = std::bind(&Block::setX, this, std::placeholders::_1),
                .initial = 100,
                .target = 500,
                .duration = 1000,
                .trans_func = TransFuncs::easeIn,
            }
        } {
        AnimationManager::getInstance().registerAnimation(&this->anim);
        // anim.onFinished.connect([this] { this->setX(100); });
    }
    ~View() {
        AnimationManager::getInstance().unregisterAnimation(&this->anim);
    }
    Animation<int> anim;
};

int main() {
    Block root{ iRect{100,100,800,600} };

    View view{ iRect{100,100,100,100}, &root };

    Button button{ iRect{100,250,100,50}, &root };
    button.text() = L"开始播放";
    button.onClicked.connect(&view.anim, &AnimationAbstract::setPlay);

    Button button2{ iRect{100,310,100,50}, &root };
    button2.text() = L"暂停播放";
    button2.onClicked.connect(&view.anim, &AnimationAbstract::setPause);
    button2.setEnable(false);

    Button button3{ iRect{100,370,100,50}, &root };
    button3.text() = L"终止播放";
    button3.onClicked.connect(&view.anim, &AnimationAbstract::setStop);

    view.anim.onStateChanged.connect([&](AnimationStateType before, AnimationStateType after) {
        after == AnimationStateType::Stop
            ? button2.setEnable(false)
            : button2.setEnable(true);
        });

    auto window = Window::createWindow(&root);
    Application app{ window };
    window->show();
    return app.run();
}