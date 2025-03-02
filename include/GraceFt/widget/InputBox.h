#include<GraceFt/Block.h>
#include<GraceFt/Signal.hpp>

namespace GFt {
    namespace Widget {
        class InputBox : public Block {
            std::wstring content_;
            std::wstring placeholder_;
            unsigned int max_length_ = 10;

        public:
            InputBox(const iRect& rect, Block* parent, int zIndex = 0,
                const std::wstring& placeholder = std::wstring());
            InputBox(const iRect& size, Block* parent, std::wstring placeholder = std::wstring());
            InputBox(const iRect& size, Block* parent, unsigned int max_length);
            ~InputBox() override;
            void setPlaceholder(const std::wstring& placeholder);
            void setMaxInputLength(unsigned int max_length);
            void setContent(const std::wstring& content);
            const std::wstring& getContent() const;
            unsigned int getMaxInputLength() const;
            const std::wstring& getPlaceholder() const;
            void clearContent();

        protected:
            void onDraw(Graphics& g) override;
            void onTextInput(TextInputEvent* event) override;

        public:
            Signal<const std::wstring&> onTextChanged;
            Signal<const std::wstring&> onEnter;
        };
    }
}