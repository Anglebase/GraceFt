#include"widget/InputBox.h"
#include"BlockFocus.h"

namespace GFt {
    namespace Widget {
        InputBox::InputBox(const iRect& rect, Block* parent, int zIndex, const std::wstring& placeholder)
            : Block(rect, parent, zIndex), placeholder_(placeholder) {}
        InputBox::InputBox(const iRect& size, Block* parent, std::wstring placeholder)
            : Block(size, parent), placeholder_(placeholder) {}
        InputBox::InputBox(const iRect& size, Block* parent, unsigned int max_length)
            : Block(size, parent), max_length_(max_length) {}
        InputBox::~InputBox() = default;
        void InputBox::setPlaceholder(const std::wstring& placeholder) {
            this->placeholder_ = placeholder;
        }
        void InputBox::setMaxInputLength(unsigned int max_length) {
            this->max_length_ = max_length;
        }
        void InputBox::setContent(const std::wstring& content) {
            this->content_ = content;
        }
        const std::wstring& InputBox::getContent() const {
            return this->content_;
        }
        unsigned int InputBox::getMaxInputLength() const {
            return this->max_length_;
        }
        const std::wstring& InputBox::getPlaceholder() const {
            return this->placeholder_;
        }
        void InputBox::clearContent() {
            this->content_.clear();
        }
        void InputBox::onDraw(Graphics& g) {
            static PenSet border{ Color{230,230,230} };
            static PenSet foused{ Color{210,220,230} };
            static TextSet content{ Color{0,0,0} };
            static TextSet placeholder{ Color{150,150,150} };

            auto rect = iRect{ this->rect().size() };
            if (BlockFocusManager::getFocusOn() == this) {
                g.bindPenSet(&foused);
            }
            else {
                g.bindPenSet(&border);
            }
            g.drawRect(rect);
            auto inner_rect = rect.centerby(iSize{ rect.width() - 6, rect.height() - 6 });
            if (this->content_.empty()) {
                g.bindTextSet(&placeholder);
                g.drawText(this->placeholder_, inner_rect, TextAlign::Left | TextAlign::Middle);
            }
            else {
                g.bindTextSet(&content);
                g.drawText(this->content_, inner_rect, TextAlign::Left | TextAlign::Middle);
            }
        }
        void InputBox::onTextInput(TextInputEvent* event) {
            if (!event) return;
            wchar_t ch = (wchar_t)event->character();
            switch (ch) {
            case L'\b':
                if (!this->content_.empty())
                    this->content_.pop_back();
                break;
            case L'\r':
            case L'\n':
                this->onEnter(this->content_);
                break;
            case L'\t':
                ch = L' ';
            default:
                if (this->content_.size() < this->max_length_ - 1)
                    this->content_ += ch;
                this->onTextChanged(this->content_);
                break;
            }
        }
    }
}

