#include <GraceFt/Application.h>
#include <GraceFt/Window.h>
#include <GraceFt/UI.h>

#include <sstream>
#include <stack>
#include <vector>
#include <variant>
#include <unordered_map>
#include <algorithm>

using namespace GFt;
using namespace GFt::UI;
using namespace GFt::Widget;
using namespace GFt::literals;
using namespace std::string_literals;

// 计算表达式
std::wstring eval(const std::wstring& expr) {
    // 检查有效性
    if (expr.empty())
        return L"";
    if (expr.find_first_not_of(L"0123456789+-*/(.)") != std::wstring::npos ||
        "0123456789"s.find(expr[0]) == std::string::npos)
        return L"出错";
    const std::unordered_map<wchar_t, int> precedence = {
        { L'+', 1 },
        { L'-', 1 },
        { L'*', 2 },
        { L'/', 2 },
    };
    enum class State {
        Num,
        Op,
        Group,
    };
    // 分离Token
    std::vector<std::pair<State, std::wstring>> tokens;
    tokens.push_back({ State::Num, L"" });
    for (auto c : expr) {
        switch (c) {
        case L'0':
        case L'1':
        case L'2':
        case L'3':
        case L'4':
        case L'5':
        case L'6':
        case L'7':
        case L'8':
        case L'9':
        case L'.':
        {
            auto& [s, t] = tokens.back();
            if (s != State::Num)
                tokens.push_back({ State::Num, L"" });
            tokens.back().second += c;
        }
        break;
        case L'+':
        case L'-':
        case L'*':
        case L'/':
        {
            auto& [s, t] = tokens.back();
            if (s == State::Num || s == State::Group) {
                tokens.push_back({ State::Op, std::wstring(1, c) });
            }
            else {
                return L"出错";
            }
        }
        break;
        case L'(':
        case L')':
        {
            tokens.push_back({ State::Group, std::wstring(1, c) });
        }
        break;
        default:
            return L"出错";
        }
    }
    // 计算
    std::stack<double> values;
    std::stack<wchar_t> ops;
    for (auto [s, t] : tokens) {
        if (s == State::Num) {
            if (std::count_if(t.begin(), t.end(), [](wchar_t c) { return c == L'.'; }) > 1)
                return L"出错";
            try { values.push(std::stod(t)); }
            catch (...) { return L"出错"; }
        }
        else if (s == State::Op || s == State::Group) {
            switch (t[0]) {
            case L'(':
                ops.push(t[0]);
                break;
            case L')':
            {
                while (!ops.empty() && ops.top() != L'(') {
                    auto op = ops.top();
                    ops.pop();
                    if (values.empty())
                        return L"出错";
                    auto b = values.top();
                    values.pop();
                    if (values.empty())
                        return L"出错";
                    auto a = values.top();
                    values.pop();
                    switch (op) {
                    case L'+': values.push(a + b); break;
                    case L'-': values.push(a - b); break;
                    case L'*': values.push(a * b); break;
                    case L'/': values.push(a / b); break;
                    }
                }
                if (ops.empty() || ops.top() != L'(')
                    return L"出错";
                ops.pop();
            }
            break;
            default:
            {
                while (!ops.empty() && ops.top() != L'(' && precedence.at(t[0]) <= precedence.at(ops.top())) {
                    auto op = ops.top();
                    ops.pop();
                    if (values.empty())
                        return L"出错";
                    auto b = values.top();
                    values.pop();
                    if (values.empty())
                        return L"出错";
                    auto a = values.top();
                    values.pop();
                    switch (op) {
                    case L'+': values.push(a + b); break;
                    case L'-': values.push(a - b); break;
                    case L'*': values.push(a * b); break;
                    case L'/': values.push(a / b); break;
                    }
                }
                ops.push(t[0]);
            }
            break;
            }
        }
    }
    // =
    while (!ops.empty()) {
        auto op = ops.top();
        ops.pop();
        if (values.empty())
            return L"出错";
        auto b = values.top();
        values.pop();
        if (values.empty())
            return L"出错";
        auto a = values.top();
        values.pop();
        switch (op) {
        case L'+': values.push(a + b); break;
        case L'-': values.push(a - b); break;
        case L'*': values.push(a * b); break;
        case L'/': values.push(a / b); break;
        }
    }
    if (!ops.empty() || values.size() != 1)
        return L"出错";
    std::wostringstream woss;
    woss << values.top();
    return woss.str();
}

void ButtonsContent(GridLayout& it) {
    // 基本属性
    it.setGridSize(5, 4);
    it.setSpace(0.5_em);
    // + 键
#pragma region +
    XButton{
        .name = "+",
        .parent = it,
        .content = [](Button& it) {
            it.textSet().font().setSize(2_em);
            it.textSet().font().setWeight(FontWeight::Bold);
            it.textSet().font().setFontFamily(L"等线");
            it.text() = L"+";
            it.onClicked.connect([] {
                auto exprLabel = dynamic_cast<Label*>(BLOCK("exprLabel"));
                exprLabel->text() += L"+";
            });
        }
    };
    it.addItem(BLOCK("+"), iRect{ 3,1,1,1 });
#pragma endregion
    // - 键
#pragma region -
    XButton{
        .name = "-",
        .parent = it,
        .content = [](Button& it) {
            it.textSet().font().setSize(2_em);
            it.textSet().font().setWeight(FontWeight::Bold);
            it.textSet().font().setFontFamily(L"等线");
            it.text() = L"-";
            it.onClicked.connect([] {
                auto exprLabel = dynamic_cast<Label*>(BLOCK("exprLabel"));
                exprLabel->text() += L"-";
            });
        }
    };
    it.addItem(BLOCK("-"), iRect{ 3,2,1,1 });
#pragma endregion
    // * 键
#pragma region *
    XButton{
        .name = "*",
        .parent = it,
        .content = [](Button& it) {
            it.textSet().font().setSize(2_em);
            it.textSet().font().setWeight(FontWeight::Bold);
            it.textSet().font().setFontFamily(L"等线");
            it.text() = L"*";
            it.onClicked.connect([] {
                auto exprLabel = dynamic_cast<Label*>(BLOCK("exprLabel"));
                exprLabel->text() += L"*";
            });
        }
    };
    it.addItem(BLOCK("*"), iRect{ 3,3,1,1 });
#pragma endregion
    // / 键
#pragma region /
    XButton{
        .name = "/",
        .parent = it,
        .content = [](Button& it) {
            it.textSet().font().setSize(2_em);
            it.textSet().font().setWeight(FontWeight::Bold);
            it.textSet().font().setFontFamily(L"等线");
            it.text() = L"/";
            it.onClicked.connect([] {
                auto exprLabel = dynamic_cast<Label*>(BLOCK("exprLabel"));
                exprLabel->text() += L"/";
            });
        }
    };
    it.addItem(BLOCK("/"), iRect{ 3,4,1,1 });
#pragma endregion
    // . 键
#pragma region .
    XButton{
        .name = ".",
        .parent = it,
        .content = [](Button& it) {
            it.textSet().font().setSize(2_em);
            it.textSet().font().setWeight(FontWeight::Bold);
            it.textSet().font().setFontFamily(L"等线");
            it.text() = L".";
            it.onClicked.connect([] {
                auto exprLabel = dynamic_cast<Label*>(BLOCK("exprLabel"));
                exprLabel->text() += L".";
            });
        }
    };
    it.addItem(BLOCK("."), iRect{ 0,4,1,1 });
#pragma endregion
    // = 键
#pragma region =
    XButton{
        .name = "=",
        .parent = it,
        .content = [](Button& it) {
            it.textSet().font().setSize(2_em);
            it.textSet().font().setWeight(FontWeight::Bold);
            it.textSet().font().setFontFamily(L"等线");
            it.text() = L"=";
            it.onClicked.connect([] {
                auto exprLabel = dynamic_cast<Label*>(BLOCK("exprLabel"));
                auto result = eval(exprLabel->text());
                exprLabel->text() = result;
                std::cout << "FPS: " << Application::getRealFps() << std::endl;
                std::cout << "RenderTime: " << Application::getRenderTime() << std::endl;
                std::cout << "EventTime: " << Application::getEventTime() << std::endl;
                });
    }
    };
    it.addItem(BLOCK("="), iRect{ 2,4,1,1 });
#pragma endregion
    // 0 键
#pragma region 0
    XButton{
        .name = "0",
        .parent = it,
        .content = [](Button& it) {
            it.textSet().font().setSize(2_em);
            it.textSet().font().setWeight(FontWeight::Bold);
            it.textSet().font().setFontFamily(L"等线");
            it.text() = L"0";
            it.onClicked.connect([] {
                auto exprLabel = dynamic_cast<Label*>(BLOCK("exprLabel"));
                exprLabel->text() += L"0";
            });
        }
    };
    it.addItem(BLOCK("0"), iRect{ 1,4,1,1 });
#pragma endregion
    // ( 键
#pragma region ()
    XButton{
        .name = "(",
        .parent = it,
        .content = [](Button& it) {
            it.textSet().font().setSize(2_em);
            it.textSet().font().setWeight(FontWeight::Bold);
            it.textSet().font().setFontFamily(L"等线");
            it.text() = L"(";
            it.onClicked.connect([] {
                auto exprLabel = dynamic_cast<Label*>(BLOCK("exprLabel"));
                exprLabel->text() += L"(";
            });
        }
    };
    it.addItem(BLOCK("("), iRect{ 0,0,1,1 });
    // ) 键
    XButton{
        .name = ")",
        .parent = it,
        .content = [](Button& it) {
            it.textSet().font().setSize(2_em);
            it.textSet().font().setWeight(FontWeight::Bold);
            it.textSet().font().setFontFamily(L"等线");
            it.text() = L")";
            it.onClicked.connect([] {
                auto exprLabel = dynamic_cast<Label*>(BLOCK("exprLabel"));
                exprLabel->text() += L")";
            });
        }
    };
    it.addItem(BLOCK(")"), iRect{ 1,0,1,1 });
#pragma endregion
    // backarrow 键
#pragma region backarrow
    XButton{
        .name = "backarrow",
        .parent = it,
        .content = [](Button& it) {
            it.textSet().font().setSize(2_em);
            it.textSet().font().setWeight(FontWeight::Bold);
            it.textSet().font().setFontFamily(L"等线");
            it.text() = L"<";
            it.onClicked.connect([] {
                auto exprLabel = dynamic_cast<Label*>(BLOCK("exprLabel"));
                if (!exprLabel->text().empty()) {
                    exprLabel->text().pop_back();
                }
            });
        }
    };
    it.addItem(BLOCK("backarrow"), iRect{ 2,0,1,1 });
#pragma endregion
    // clear 键
#pragma region clear
    XButton{
        .name = "clear",
        .parent = it,
        .content = [](Button& it) {
            it.textSet().font().setSize(2_em);
            it.textSet().font().setWeight(FontWeight::Bold);
            it.textSet().font().setFontFamily(L"等线");
            it.text() = L"C";
            it.onClicked.connect([] {
                auto exprLabel = dynamic_cast<Label*>(BLOCK("exprLabel"));
                exprLabel->text().clear();
            });
        }
    };
    it.addItem(BLOCK("clear"), iRect{ 3,0,1,1 });
#pragma endregion
    // 数字键 
#pragma region 1-9
    for (int i = 1; i <= 9; i++) {
        std::string name = std::to_string(i);
        XButton{
            .name = name,
            .parent = it,
            .content = [i](Button& it) {
                it.textSet().font().setSize(2_em);
                it.textSet().font().setWeight(FontWeight::Bold);
                it.textSet().font().setFontFamily(L"等线");
                it.text() = std::to_wstring(i);
                it.onClicked.connect([i] {
                    auto exprLabel = dynamic_cast<Label*>(BLOCK("exprLabel"));
                    exprLabel->text() += std::to_wstring(i);
                });
            }
        };
        auto k = i - 1;
        it.addItem(BLOCK(name), iRect{ k % 3,3 - k / 3,1,1 });
    }
#pragma endregion
}

int main() {
    XMainWindow{
        // 主窗口
        .name = "AppWindow",
        .title = L"四则运算计算器",
        .rect = iRect{ 50, 50, 600, 800 },
        .content = [](MainWindow& it) {
            // 窗口布局
            XColumnLayout{
                .name = "WindowLayout",
                .rect = iRect{ it.rect().size() },
                .parent = it,
                .content = [](ColumnLayout& it) {
                    // 基本属性配置
                    it.setPadding(1_em);
                    Window::onWindowSizeChanged.connect([&it](Window* w) {
                        it.setSize(iSize{100_vw, 100_vh});
                    });
                    Window::onWindowCreated.connect([&it](Window* w) {
                        it.setSize(iSize{100_vw, 100_vh});
                    });
                    XLabel {
                        .name = "exprLabel",
                        .parent = it,
                        .content = [](Label& it) {
                            it.textSet().font().setSize(5_em);
                            it.textSet().font().setWeight(FontWeight::Bold);
                            it.textSet().font().setFontFamily(L"等线");
                        }
                    };
                    XGridLayout {
                        .name = "btns",
                        .parent = it,
                        .content = ButtonsContent,
                    };
                    it.addItem(BLOCK("exprLabel"), 0.5);
                    it.addItem(BLOCK("btns"), 2.5);
                }
            };
        }
    };

    Window* window = Window::createWindow(BLOCK("AppWindow"));
    Application app(window);
    window->show();
    return app.run();
}