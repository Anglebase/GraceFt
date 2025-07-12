/**
 * @file json.hpp
 * @author Anglebase[@github]
 * @note  (仅)此文件以 MIT 许可证独立于此项目发布
 *        (Only) This file is published independently of this project under the MIT license.
 * @brief 这是一个用于 JSON 序列化/反序列化的仅头文件库 (C++17)
 *        这个库支持反序列化带有注释和尾随逗号的 JSON 格式，但并不会存储它们
 *        由于此库不依赖多态技术实现，使得它具有十分良好的性能，并且可以与 C++ 无缝集成
 */
#pragma once

#include <iostream>
#include <variant>
#include <string>
#include <vector>
#include <unordered_map>
#include <cmath>

namespace GFt {
    /// @brief JSON 支持库
    /// @details 这个命名空间包含了 JSON 相关的类型和函数
    namespace json {
        enum class Type {
            Null,       ///< 空值
            Boolean,    ///< 布尔值
            Number,     ///< 数字
            String,     ///< 字符串
            Array,      ///< 数组
            Object,     ///< 对象
            Invalid     ///< 无效值
        };
        template<typename CharT>
        class Value;
        template<typename CharT>
        using StdString = std::basic_string<CharT>;
        template<typename CharT>
        using StdIStream = std::basic_istream<CharT>;
        template<typename CharT>
        using StdOStream = std::basic_ostream<CharT>;
        template<typename CharT>
        using Array = std::vector<Value<CharT>>;
        template<typename CharT>
        using Object = std::unordered_map<StdString<CharT>, Value<CharT>>;

        /// @brief 格式化选项
        /// @details 这个结构用于控制 JSON 序列化的格式
        ///          在 JSON 序列化时，可以通过设置这个结构的成员变量来控制格式化选项
        ///          默认情况下，会输出没有格式化的 JSON 字符串(不包含冗余空白符)
        /// @code 示例：
        /// // 以 4 个空格为一个缩进单位，输出格式化后的 JSON 字符串
        /// std::cout << json::Format(4) << /* json value */ << std::endl;
        /// // 以压缩后格式输出 JSON 字符串
        /// std::cout << json::Format() << /* json value */ << std::endl;
        /// @endcode
        struct Format {
            template<typename CharT>
            friend class Value;
        private:
            static inline bool format_json_ = false;
            static inline int tabsize_ = 4;
        public:
            using jFormat = std::ios_base& (*)(std::ios_base&);
            /// @brief 设置格式化选项
            /// @param tabsize 一个整数，表示一个缩进单位的空格数，默认为 -1 表示不格式化
            Format(int tabsize = -1) {
                tabsize_ = tabsize;
                format_json_ = tabsize >= 0;
            }
            operator jFormat() {
                return [](std::ios_base& os)->std::ios_base& {
                    return os;
                    };
            }

            static inline bool isFormat() {
                return format_json_;
            }

            static inline int tabSize() {
                return tabsize_;
            }
        };

        /// @brief JSON 值对象
        template<typename CharT>
        class Value {
            static inline const CharT null_[]{ 'n', 'u', 'l', 'l', 0 };
            static inline const CharT true_[]{ 't', 'r', 'u', 'e', 0 };
            static inline const CharT fals_[]{ 'f', 'a', 'l', 's', 0 };
            static inline const CharT false_[]{ 'f', 'a', 'l', 's', 'e', 0 };
            static inline const CharT invaild_[]{
                '/', '*', 'I', 'n', 'v', 'a', 'i', 'l', 'd', ' ', 'v', 'a', 'l', 'u', 'e', '*', '/', 0 };

            Type type_;
            using Variant = std::variant<bool, double, StdString<CharT>, Array<CharT>, Object<CharT>>;
            Variant value_;
            void removeRedundantComma(StdIStream<CharT>& is) const {
                do {
                    is >> std::ws;
                    if (is.peek() == '/') {
                        is.get();
                        if (is.peek() == '/') {
                            is.ignore(std::string().max_size(), '\n');
                        }
                        else if (is.peek() == '*') {
                            is.get();
                            while (is.peek() == '/')
                                is.get();
                            while (is.peek() != '/')
                                is.ignore(std::string().max_size(), '*');
                        }
                    }
                    else {
                        break;
                    }
                } while (true);
            }
        public:
            Value() : type_(Type::Invalid) {}
            Value(bool b) : type_(Type::Boolean), value_(b) {}
            Value(double d) : type_(Type::Number), value_(d) {}
            template<size_t N>
            Value(const CharT(&s)[N]) : type_(Type::String), value_(StdString<CharT>(s)) {}
            Value(const CharT* s) : type_(Type::String), value_(StdString<CharT>(s)) {}
            Value(const StdString<CharT>& s) : type_(Type::String), value_(s) {}
            Value(const Array<CharT>& a) : type_(Type::Array), value_(a) {}
            Value(const Object<CharT>& o) : type_(Type::Object), value_(o) {}

            Value& operator=(bool b) { type_ = Type::Boolean; value_ = b; return *this; }
            Value& operator=(double d) { type_ = Type::Number; value_ = d; return *this; }
            template<size_t N>
            Value& operator=(const CharT(&s)[N]) { type_ = Type::String; value_ = StdString<CharT>(s); return *this; }
            Value& operator=(const CharT* s) { type_ = Type::String; value_ = StdString<CharT>(s); return *this; }
            Value& operator=(const StdString<CharT>& s) { type_ = Type::String; value_ = s; return *this; }
            Value& operator=(const Array<CharT>& a) { type_ = Type::Array; value_ = a; return *this; }
            Value& operator=(const Object<CharT>& o) { type_ = Type::Object; value_ = o; return *this; }

            /// @brief 获取当前 JSON 值对象持有的 JSON 值类型
            Type type() const { return type_; }

            bool isNull() const { return type_ == Type::Null; }
            bool isBool() const { return type_ == Type::Boolean; }
            bool isString() const { return type_ == Type::String; }
            bool isArray() const { return type_ == Type::Array; }
            bool isObject() const { return type_ == Type::Object; }
            bool isNumber() const { return type_ == Type::Number; }
            bool isInteger() const {
                if (!isNumber()) return false;
                double d = std::get<double>(value_);
                return d == std::floor(d);
            }
            bool isFloat() const { return isNumber() && !isInteger(); }

            bool& asBoolean() { return std::get<bool>(value_); }
            double& asNumber() { return std::get<double>(value_); }
            StdString<CharT>& asString() { return std::get<StdString<CharT>>(value_); }
            Array<CharT>& asArray() { return std::get<Array<CharT>>(value_); }
            Object<CharT>& asObject() { return std::get<Object<CharT>>(value_); }

            const bool& asBoolean() const { return std::get<bool>(value_); }
            const int& asInteger() const { return std::get<int>(value_); }
            const double& asNumber() const { return std::get<double>(value_); }
            const StdString<CharT>& asString() const { return std::get<StdString<CharT>>(value_); }
            const Array<CharT>& asArray() const { return std::get<Array<CharT>>(value_); }
            const Object<CharT>& asObject() const { return std::get<Object<CharT>>(value_); }

            bool toBool() const { return std::get<bool>(value_); }
            int toInt() const { return static_cast<int>(std::get<double>(value_)); }
            double toFloat() const { return std::get<double>(value_); }
            const StdString<CharT>& toString() const { return std::get<StdString<CharT>>(value_); }
            Value& operator[](size_t i) { return asArray()[i]; }
            const Value& operator[](size_t i) const { return asArray()[i]; }
            Value& operator[](const StdString<CharT>& key) { return asObject()[key]; }
            const Value& operator[](const StdString<CharT>& key) const { return asObject()[key]; }
            Value& at(const StdString<CharT>& key) { return asObject().at(key); }
            const Value& at(const StdString<CharT>& key) const { return asObject().at(key); }
        private:
            static inline int indent_ = 0;
        public:
            /// @brief 向流中写入 JSON 值对象
            friend StdOStream<CharT>& operator<<(StdOStream<CharT>& os, const Value<CharT>& v) {
                switch (v.type_) {
                case Type::Null: os << null_; break;
                case Type::Boolean: os << (v.asBoolean() ? true_ : false_); break;
                case Type::Number:
                {
                    if (v.isFloat())
                        os << v.toFloat();
                    else
                        os << v.toInt();
                } break;
                case Type::String: os << '"' << v.asString() << '"'; break;
                case Type::Array:
                {
                    os << '[' << (Format::isFormat() ? StdString<CharT>(1, '\n') : StdString<CharT>());
                    Value<CharT>::indent_++;
                    for (std::size_t i = 0; i < v.asArray().size(); ++i)
                        os << (Format::isFormat()
                            ? StdString<CharT>(Format::tabSize() * Value<CharT>::indent_, ' ')
                            : StdString<CharT>())
                        << v[i] << (i == v.asArray().size() - 1 ? StdString<CharT>() : StdString<CharT>(1, ','))
                        << (Format::isFormat() ? StdString<CharT>(1, '\n') : StdString<CharT>());
                    Value<CharT>::indent_--;
                    os << (Format::isFormat()
                        ? StdString<CharT>(Format::tabSize() * Value<CharT>::indent_, ' ')
                        : StdString<CharT>()) << ']';
                } break;
                case Type::Object:
                {
                    os << '{' << (Format::isFormat() ? StdString<CharT>(1, '\n') : StdString<CharT>());
                    Value<CharT>::indent_++;
                    std::size_t i = 0;
                    for (const auto& [key, value] : v.asObject()) {
                        os << (Format::isFormat()
                            ? StdString<CharT>(Format::tabSize() * Value<CharT>::indent_, ' ')
                            : StdString<CharT>())
                            << '"' << key << '"' << ':' << (Format::isFormat()
                                ? StdString<CharT>(1, ' ')
                                : StdString<CharT>())
                            << value << (i == v.asObject().size() - 1
                                ? StdString<CharT>() : StdString<CharT>(1, ','))
                            << (Format::isFormat() ? StdString<CharT>(1, '\n') : StdString<CharT>());
                        ++i;
                    }
                    Value<CharT>::indent_--;
                    os << (Format::isFormat()
                        ? StdString<CharT>(Format::tabSize() * Value<CharT>::indent_, ' ')
                        : StdString<CharT>()) << '}';
                } break;
                case Type::Invalid: os << invaild_; break;
                }
                return os;
            }
            /// @brief 从流中读取 JSON 值对象
            /// @details 这个函数会尝试解析 JSON 格式的字符串，并将解析结果存储在当前 JSON 值对象中
            ///          它会忽略冗余的空白符、注释和尾随逗号
            /// @note 若在读取时遇到错误，会设置流状态为 failbit
            friend StdIStream<CharT>& operator>>(StdIStream<CharT>& is, Value<CharT>& v) {
                v.removeRedundantComma(is);
                char c = is.peek();
                switch (c) {
                case 'n':
                {
                    CharT null[4] = { 0 };
                    is.read(null, 4);
                    if (StdString<CharT>(null) != null_) {
                        is.setstate(std::ios_base::failbit);
                        return is;
                    }
                    v = nullptr;
                }break;
                case 't':
                case 'f':
                {
                    CharT boolean[5] = { 0 };
                    is.read(boolean, 4);
                    if (StdString<CharT>(boolean) == true_) {
                        v = true;
                    }
                    else if (StdString<CharT>(boolean) == fals_ && is.get() == 'e') {
                        v = false;
                    }
                    else {
                        is.setstate(std::ios_base::failbit);
                        return is;
                    }
                }break;
                case '-':
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                {
                    std::string number;
                    bool is_end = false;
                    while (!is_end) switch (is.peek()) {
                    case '0': case '1': case '2': case '3': case '4':
                    case '5': case '6': case '7': case '8': case '9':
                    case '.': case '+': case '-': case 'e': case 'E':
                        number += is.get();
                        break;
                    default:
                        is_end = true;
                        break;
                    }
                    try { v = std::stod(number); }
                    catch (const std::exception&) {
                        is.setstate(std::ios_base::failbit);
                        return is;
                    }
                }break;
                case '"':
                {
                    v = StdString<CharT>();
                    is.get();
                    std::getline(is, v.asString(), (CharT)'"');
                }break;
                case '[':
                {
                    v = Array<CharT>();
                    is.get();
                    while (is.peek() != ']') {
                        v.removeRedundantComma(is);
                        Value value;
                        is >> value;
                        v.asArray().push_back(std::move(value));
                        v.removeRedundantComma(is);
                        if (is.peek() == ']') {
                            break;
                        }
                        if (is.peek() != ',') {
                            is.setstate(std::ios_base::failbit);
                            return is;
                        }
                        is.get();
                        v.removeRedundantComma(is);
                    }
                    if (is.get() != ']') {
                        is.setstate(std::ios_base::failbit);
                        return is;
                    }
                }break;
                case '{':
                {
                    v = Object<CharT>();
                    is.get();
                    while (is.peek() != '}') {
                        v.removeRedundantComma(is);
                        Value key;
                        is >> key;
                        if (key.type() != Type::String) {
                            is.setstate(std::ios_base::failbit);
                            return is;
                        }
                        v.removeRedundantComma(is);
                        if (is.get() != ':') {
                            is.setstate(std::ios_base::failbit);
                            return is;
                        }
                        Value value;
                        is >> value;
                        v[key.toString()] = std::move(value);
                        v.removeRedundantComma(is);
                        if (is.peek() == '}') {
                            break;
                        }
                        if (is.peek() != ',') {
                            is.setstate(std::ios_base::failbit);
                            return is;
                        }
                        is.get();
                        v.removeRedundantComma(is);
                    }
                    if (is.get() != '}') {
                        is.setstate(std::ios_base::failbit);
                        return is;
                    }
                }break;
                default:
                    is.setstate(std::ios_base::failbit);
                }
                return is;
            }
        };
    }
}

/*
(仅)此文件以 MIT 许可证独立于此项目发布

MIT License

Copyright (c) 2024 Weiyi Anglebase

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/