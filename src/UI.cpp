#include "UI.h"

#include <map>

namespace GFt {
    DeclarativeUIManager::~DeclarativeUIManager() {
        for (auto& [name, pblock] : this->blocks)
            delete pblock;
    }
    Block* DeclarativeUIManager::findBlock(const std::string& name) {
        if (blocks.find(name) == blocks.end())
            return nullptr;
        return blocks.at(name);
    }
    void DeclarativeUIManager::addBlock(const std::string& name, Block* pblock) {
        if (blocks.find(name) != blocks.end())
            delete blocks.at(name);
        blocks[name] = pblock;
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
            content(*it);
        }
        XBlock::~XBlock() {
            GFt::Block* it = new GFt::Block(this->rect, &this->parent, this->zIndex);
            auto& uiManager = GFt::DeclarativeUIManager::getInstance();
            uiManager.addBlock(name, it);
            content(*it);
        }
        XButton::~XButton() {
            GFt::Widget::Button* it = new GFt::Widget::Button(this->text, this->rect, &this->parent, this->zIndex);
            auto& uiManager = GFt::DeclarativeUIManager::getInstance();
            uiManager.addBlock(name, it);
            content(*it);
        }
    }
}