#include "UI.h"

#include <map>

namespace GFt {
    DeclarativeUIManager::~DeclarativeUIManager() {

    }
    Block* DeclarativeUIManager::findBlock(const std::string_view& name) {
        if (blocks.find(name) == blocks.end())
            return nullptr;
        return blocks.at(name).get();
    }
    std::string_view DeclarativeUIManager::findBlockByName(const Block* block) const {
        for (auto& [name, pblock] : this->blocks)
            if (pblock.get() == block)
                return name;
        using namespace std::literals;
        return ""sv;
    }
    void DeclarativeUIManager::addBlock(const std::string_view& name, Block* pblock) {
        if (blocks.find(name) != blocks.end())
            throw std::runtime_error("Block with the same name already exists.");
        blocks[name] = std::unique_ptr<Block>(pblock);
    }
    void DeclarativeUIManager::removeBlock(const std::string_view& name) {
        if (blocks.find(name) == blocks.end())
            return;
        blocks.erase(name);
    }
    void DeclarativeUIManager::replaceBlock(const std::string_view& name, Block* block) {
        blocks[name] = std::unique_ptr<Block>(block);
    }
    DeclarativeUIManager& DeclarativeUIManager::getInstance() {
        static DeclarativeUIManager instance;
        return instance;
    }

    namespace UI {
        XWindow::~XWindow() {
            GFt::Block* it = new GFt::Block(this->rect);
            auto& uiManager = GFt::DeclarativeUIManager::getInstance();
            uiManager.addBlock(name, it);
            if (content)
                content(*it);
        }
        XBlock::~XBlock() {
            GFt::Block* it = new GFt::Block(this->rect, &this->parent, this->zIndex);
            auto& uiManager = GFt::DeclarativeUIManager::getInstance();
            uiManager.addBlock(name, it);
            if (content)
                content(*it);
        }
        XButton::~XButton() {
            GFt::Widget::Button* it = new GFt::Widget::Button(this->text, this->rect, &this->parent, this->zIndex);
            auto& uiManager = GFt::DeclarativeUIManager::getInstance();
            uiManager.addBlock(name, it);
            if (content)
                content(*it);
        }
        XLabel::~XLabel() {
            GFt::Widget::Label* it = new GFt::Widget::Label(this->text, this->rect, &this->parent, this->zIndex);
            auto& uiManager = GFt::DeclarativeUIManager::getInstance();
            uiManager.addBlock(name, it);
            if (content)
                content(*it);
        }
        XRowLayout::~XRowLayout() {
            GFt::RowLayout* it = new GFt::RowLayout(this->rect, &this->parent, this->zIndex);
            auto& uiManager = GFt::DeclarativeUIManager::getInstance();
            uiManager.addBlock(name, it);
            if (content)
                content(*it);
        }
        XColumnLayout::~XColumnLayout() {
            GFt::ColumnLayout* it = new GFt::ColumnLayout(this->rect, &this->parent, this->zIndex);
            auto& uiManager = GFt::DeclarativeUIManager::getInstance();
            uiManager.addBlock(name, it);
            if (content)
                content(*it);
        }
        XGridLayout::~XGridLayout() {
            GFt::GridLayout* it = new GFt::GridLayout(this->rect, &this->parent, this->zIndex);
            auto& uiManager = GFt::DeclarativeUIManager::getInstance();
            uiManager.addBlock(name, it);
            if (content)
                content(*it);
        }
    }
}