#include "UI.h"

using namespace std::literals;

namespace GFt {
    DeclarativeUIManager::~DeclarativeUIManager() {

    }
    Block* DeclarativeUIManager::findBlock(const std::string& name) {
        if (blocks.find(name) == blocks.end())
            return nullptr;
        return blocks.at(name).get();
    }
    std::string DeclarativeUIManager::findBlockByName(const Block* block) const {
        for (auto& [name, pblock] : this->blocks)
            if (pblock.get() == block)
                return name;
        using namespace std::literals;
        return ""s;
    }
    void DeclarativeUIManager::addBlock(const std::string& name, Block* pblock) {
        if (blocks.find(name) != blocks.end())
            throw std::runtime_error("Block with the same name '"s + name.data() + "' already exists."s);
        blocks[name] = std::unique_ptr<Block>(pblock);
    }
    void DeclarativeUIManager::removeBlock(const std::string& name) {
        if (blocks.find(name) == blocks.end())
            return;
        blocks.erase(name);
    }
    void DeclarativeUIManager::replaceBlock(const std::string& name, Block* block) {
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
        XMainWindow::~XMainWindow() {
            GFt::Widget::MainWindow* it = new GFt::Widget::MainWindow(title, rect);
            auto& uiManager = GFt::DeclarativeUIManager::getInstance();
            uiManager.addBlock(name, it);
            if (content)
                content(*it);
        }
}
}