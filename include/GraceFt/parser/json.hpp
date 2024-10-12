/**
 * @file json.hpp
 * @author Anglebase[@github]
 * @brief 一个用于 JSON 序列化/反序列化的仅头文件库 (C++20)
 *        这个库支持反序列化带有注释和尾随逗号的 JSON 格式，但将在序列化时忽略它们
 */
#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <concepts>
#include <type_traits>
#include <istream>
#include <ostream>

namespace GFt {
    /// @brief JSON 序列化和反序列化支持
    /// @details 这个命名空间包含所有用于 JSON 序列化/反序列化的类和函数
    /// @code 使用示例
    /// #include <iostream>
    /// #include <sstream>
    /// #include <string>
    /// #include <GraceFt/parser/json.hpp>
    ///
    /// using namespace GFt;
    /// using namespace std;
    ///
    /// int main() {
    ///     string json_str = R"({"name": "Grace", "age": 25, "city": "Beijing", "hobbies": ["reading", "swimming"]})";
    ///     istringstream iss(json_str); // 输入流，可以是任意流对象，如 ifstream、stringstream 等
    ///
    ///     json::Value<char> data;
    ///     iss >> data;
    ///
    ///     // 格式化输出
    ///     cout << data << endl;
    ///     cout << "----------------------------" << endl;
    ///     // 压缩输出
    ///     json::print(data, cout, -1);
    ///     cout << endl;
    ///     // 访问属性
    ///     cout << data["name"].toString() << endl;
    ///     cout << data["age"].toInt() << endl;
    ///     // 如果属性类型不匹配，则会抛出异常
    ///     // cout << data["age"].toString() << endl; // throws exception: std::bad_cast
    ///     // 访问数组元素
    ///     cout << data["hobbies"][0].toString() << endl;
    ///
    ///     return 0;
    /// }
    /// @endcode
    namespace json {
        template<typename CharT>
        using StdString = std::basic_string<CharT>;
        template<typename CharT>
        using StdiStream = std::basic_istream<CharT>;
        template<typename CharT>
        using StdoStream = std::basic_ostream<CharT>;

        template<typename CharT>
        class Value;
        template<typename CharT>
        class Object;
        template<typename CharT>
        class Array;
        template<typename CharT>
        class String;
        template<typename CharT>
        class Number;
        template<typename CharT>
        class Boolean;
        template<typename CharT>
        class Null;
        enum class Type {
            Null,       ///< 空
            Boolean,    ///< 布尔值
            Number,     ///< 数字
            String,     ///< 字符串
            Array,      ///< 数组
            Object,     ///< 对象
            Invalid     ///< 无效类型
        };
        /// @brief 此概念约束类型 V 必须是非空有效的 JSON 值类型
        template<typename V, typename CharT>
        concept Child = std::derived_from<std::remove_cvref_t<V>, Value<CharT>>
            && !std::same_as<std::remove_cvref_t<V>, Value<CharT>>;

        /// @brief JSON 值类型
        /// @tparam CharT 字符类型，通常为 char 或 wchar_t，它可以通过 json::parse() 函数由流对象决定
        template<typename CharT>
        class Value {
            Value<CharT>* ref{ nullptr };

        protected:
            Value(const Value<CharT>& other) {
                ref = new Value<CharT>();
            }
            Value(Value<CharT>&& other) {
                ref = other.ref;
                other.ref = nullptr;
            }
            Value& operator=(const Value<CharT>& other) {
                if (this == &other) return *this;
                delete ref;
                ref = new Value<CharT>();
                assign(*ref, other);
                return *this;
            }
            Value& operator=(Value<CharT>&& other) {
                if (this == &other) return *this;
                delete ref;
                ref = other.ref;
                other.ref = nullptr;
                return *this;
            }
        public:
            Value() = default;
            virtual ~Value() { delete ref; }
            /// @brief 从类型 V 的值构造 JSON 值
            /// @tparam V 类型 V 的值必须是非空有效的 JSON 值类型，可有cv限定
            /// @param other 类型 V 的值
            template<typename V>
                requires Child<V, CharT>
            Value(V other) { ref = new std::remove_cvref_t<V>(other); }

            /// @brief 将 V 类型的 JSON 值赋给此对象
            /// @tparam V 类型 V 的值必须是非空有效的 JSON 值类型，可有cv限定
            /// @param other 类型 V 的值
            template<typename V>
                requires Child<V, CharT>
            Value& operator=(V other) {
                using V_t = std::remove_cvref_t<V>;
                delete ref;
                ref = new V_t(other);
                return *this;
            }
            template<size_t N>
            Value& operator=(const CharT(&str)[N]) { return operator=(StdString<CharT>(str)); }
            Value& operator=(const CharT* str) { return operator=(StdString<CharT>(str)); }
            Value& operator=(const StdString<CharT>& str) { return operator=(String<CharT>(str)); }
            Value& operator=(long long num) { return operator=(Number<CharT>(num)); }
            Value& operator=(double num) { return operator=(Number<CharT>(num)); }
            Value& operator=(bool b) { return operator=(Boolean<CharT>(b)); }
            /// @brief 判断当前对象是否是类型 T 的 JSON 值
            /// @tparam T 类型 T 的值必须是非空有效的 JSON 值所属的类模板
            /// @return 当前对象是否是类型 T 的 JSON 值
            template<template<typename> typename T>
                requires Child<T<CharT>, CharT>
            bool is() const {
                return ref
                    ? dynamic_cast<const volatile T<CharT>*>(ref)
                    : dynamic_cast<const volatile T<CharT>*>(this);
            }
            /// @brief 使得当前对象作为 T 类型的 JSON 值使用
            /// @tparam T 类型 T 的值必须是非空有效的 JSON 值所属的类模板
            /// @return 当前对象作为 T 类型的 JSON 值的引用
            /// @throws std::bad_cast 如果当前对象不是类型 T 的 JSON 值则会抛出此异常
            template<template<typename> typename T>
                requires Child<T<CharT>, CharT>
            T<CharT>& as() {
                return ref
                    ? dynamic_cast<T<CharT>&>(*ref)
                    : dynamic_cast<T<CharT>&>(*this);
            }
            /// @brief 此函数是 as() 函数的 const 版本
            template<template<typename> typename T>
                requires Child<T<CharT>, CharT>
            const T<CharT>& as() const {
                return ref
                    ? dynamic_cast<const T<CharT>&>(*ref)
                    : dynamic_cast<const T<CharT>&>(*this);
            }
            /// @brief 获取枚举形式的当前对像 JSON 值所属数据类型
            /// @return 枚举形式的 JSON 数据类型
            Type type() const {
                if (this->template is<Null>())
                    return Type::Null;
                else if (this->template is<Boolean>())
                    return Type::Boolean;
                else if (this->template is<Number>())
                    return Type::Number;
                else if (this->template is<String>())
                    return Type::String;
                else if (this->template is<Array>())
                    return Type::Array;
                else if (this->template is<Object>())
                    return Type::Object;
                else
                    return Type::Invalid;
            }
            /// @brief 转换当前对象到整型
            /// @return 当前对象转换后的整型值
            /// @throws std::bad_cast 如果当前对象不是 Number 类型则会抛出此异常
            long long toInt() const { return as<Number>().toInt(); }
            /// @brief 转换当前对象到浮点型
            /// @return 当前对象转换后的浮点型值
            /// @throws std::bad_cast 如果当前对象不是 Number 类型则会抛出此异常
            double toFloat() const { return as<Number>().toFloat(); }
            /// @brief 转换当前对象到布尔型
            /// @return 当前对象转换后的布尔型值
            /// @throws std::bad_cast 如果当前对象不是 Boolean 类型则会抛出此异常
            bool toBool() const { return as<Boolean>().toBool(); }
            /// @brief 转换当前对象到字符串
            /// @return 当前对象转换后的字符串值
            /// @throws std::bad_cast 如果当前对象不是 String 类型则会抛出此异常
            const StdString<CharT>& toString() const { return as<String>().toString(); }

            /// @brief 键下标访问
            /// @param key 要访问的属性或数组下标
            /// @return 对应属性或数组下标的值
            /// @throws std::bad_cast 如果当前对象不是 Object 类型则会抛出此异常
            Value& operator[](const StdString<CharT>& key) { return as<Object>()[key]; }
            /// @brief 键下标访问的 const 版本
            const Value& operator[](const StdString<CharT>& key) const { return as<Object>()[key]; }
            /// @brief 索引下标访问
            /// @param index 要访问的数组下标
            /// @return 对应数组下标的值
            /// @throws std::bad_cast 如果当前对象不是 Array 类型则会抛出此异常
            Value& operator[](size_t index) { return as<Array>()[index]; }
            /// @brief 索引下标访问的 const 版本
            const Value& operator[](size_t index) const { return as<Array>()[index]; }
        };
        /// @brief Value 类型赋值函数
        /// @param value 被赋值的 JSON 值
        /// @param other 要赋值的 JSON 值
        /// @return 等同于 value 的引用
        template<typename CharT>
        Value<CharT>& assign(Value<CharT>& value, const Value<CharT>& other) {
            if (other.template is<Null>())
                value = other.template as<Null>();
            else if (other.template is<Boolean>())
                value = other.template as<Boolean>();
            else if (other.template is<Number>())
                value = other.template as<Number>();
            else if (other.template is<String>())
                value = other.template as<String>();
            else if (other.template is<Array>())
                value = other.template as<Array>();
            else if (other.template is<Object>())
                value = other.template as<Object>();
            else
                throw std::bad_cast();
            return value;
        }
        /// @brief JSON 值类型 Object
        template<typename CharT>
        class Object : public Value<CharT> {
            std::unordered_map<StdString<CharT>, Value<CharT>*> members;

            class Iterator {
                Object<CharT>& obj;
                using iterator = typename std::unordered_map<StdString<CharT>, Value<CharT>*>::iterator;
                iterator it;
            public:
                Iterator(Object<CharT>& obj, iterator it) : obj(obj), it(it) {}
                ~Iterator() = default;

                bool operator!=(const Iterator& other) const { return it != other.it; }
                bool operator==(const Iterator& other) const { return it == other.it; }
                Iterator& operator++() { ++it; return *this; }
                Iterator operator++(int) { Iterator tmp(*this); ++it; return tmp; }
                std::pair<StdString<CharT>, Value<CharT>&> operator*() const {
                    return { it->first, *it->second };
                }
            };
            class ConstIterator {
                const Object<CharT>& obj;
                using const_iterator = typename std::unordered_map<StdString<CharT>, Value<CharT>*>::const_iterator;
                const_iterator it;
            public:
                ConstIterator(const Object<CharT>& obj, const_iterator it) : obj(obj), it(it) {}
                ~ConstIterator() = default;

                bool operator!=(const ConstIterator& other) const { return it != other.it; }
                bool operator==(const ConstIterator& other) const { return it == other.it; }
                ConstIterator& operator++() { ++it; return *this; }
                ConstIterator operator++(int) { ConstIterator tmp(*this); ++it; return tmp; }
                std::pair<StdString<CharT>, const Value<CharT>&> operator*() const {
                    return { it->first, *it->second };
                }
            };
        public:
            Object() = default;
            Object(const Object<CharT>& other) {
                for (const auto& [key, value] : other.members) {
                    members[key] = new Value<CharT>();
                    assign(*members[key], *value);
                }
            }
            Object(Object<CharT>&& other) {
                members.swap(other.members);
                other.members.clear();
            }
            Object& operator=(const Object<CharT>& other) {
                if (this == &other) return *this;
                for (auto& [key, value] : members) delete value;
                members.clear();
                for (const auto& [key, value] : other.members) {
                    members[key] = new Value<CharT>();
                    assign(*members[key], *value);
                }
                return *this;
            }
            Object& operator=(Object<CharT>&& other) {
                if (this == &other) return *this;
                for (auto& [key, value] : members) delete value;
                members.swap(other.members);
                other.members.clear();
                return *this;
            }
            ~Object() override { for (auto& [key, value] : members) delete value; }

            Iterator begin() { return Iterator(*this, members.begin()); }
            Iterator end() { return Iterator(*this, members.end()); }
            ConstIterator begin() const { return ConstIterator(*this, members.begin()); }
            ConstIterator end() const { return ConstIterator(*this, members.end()); }

            template<typename V>
                requires std::derived_from<std::remove_cvref_t<V>, Value<CharT>>
            void insert(const StdString<CharT>& key, V value) {
                if (members.find(key) != members.end())
                    delete members[key];
                members[key] = new Value<CharT>(value);
            }
            template<size_t N>
            void insert(const StdString<CharT>& key, const CharT(&value)[N]) {
                if (members.find(key) != members.end())
                    delete members[key];
                members[key] = new String<CharT>(value);
            }
            void insert(const StdString<CharT>& key, const CharT* value) {
                if (members.find(key) != members.end())
                    delete members[key];
                members[key] = new String<CharT>(value);
            }
            void insert(const StdString<CharT>& key, const StdString<CharT>& value) {
                if (members.find(key) != members.end())
                    delete members[key];
                members[key] = new String<CharT>(value);
            }
            void insert(const StdString<CharT>& key, double value) {
                if (members.find(key) != members.end())
                    delete members[key];
                members[key] = new Number<CharT>(value);
            }
            void insert(const StdString<CharT>& key, long long value) {
                if (members.find(key) != members.end())
                    delete members[key];
                members[key] = new Number<CharT>(value);
            }
            void insert(const StdString<CharT>& key, bool value) {
                if (members.find(key) != members.end())
                    delete members[key];
                members[key] = new Boolean<CharT>(value);
            }

            template<typename V>
                requires std::derived_from<std::remove_cvref_t<V>, Value<CharT>>
            void insert(StdString<CharT>&& key, V value) {
                if (members.find(key) != members.end())
                    delete members[key];
                members[key] = new Value<CharT>(value);
            }
            template<size_t N>
            void insert(StdString<CharT>&& key, const CharT(&value)[N]) {
                if (members.find(key) != members.end())
                    delete members[key];
                members[key] = new String<CharT>(value);
            }
            void insert(StdString<CharT>&& key, const CharT* value) {
                if (members.find(key) != members.end())
                    delete members[key];
                members[key] = new String<CharT>(value);
            }
            void insert(StdString<CharT>&& key, const StdString<CharT>& value) {
                if (members.find(key) != members.end())
                    delete members[key];
                members[key] = new String<CharT>(value);
            }
            void insert(StdString<CharT>&& key, double value) {
                if (members.find(key) != members.end())
                    delete members[key];
                members[key] = new Number<CharT>(value);
            }
            void insert(StdString<CharT>&& key, long long value) {
                if (members.find(key) != members.end())
                    delete members[key];
                members[key] = new Number<CharT>(value);
            }
            void insert(StdString<CharT>&& key, bool value) {
                if (members.find(key) != members.end())
                    delete members[key];
                members[key] = new Boolean<CharT>(value);
            }

            Value<CharT>& operator[](const StdString<CharT>& key) {
                if (members.find(key) == members.end())
                    members[key] = new Null<CharT>();
                return *members[key];
            }
            const Value<CharT>& operator[](const StdString<CharT>& key) const {
                if (members.find(key) == members.end())
                    members[key] = new Null<CharT>();
                return *members[key];
            }
            void erase(const StdString<CharT>& key) {
                auto it = members.find(key);
                if (it != members.end()) {
                    delete it->second;
                    members.erase(it);
                }
            }
            Value<CharT>& at(const StdString<CharT>& key) { return *members.at(key); }
            const Value<CharT>& at(const StdString<CharT>& key) const { *members.at(key); }
            size_t size() const { return members.size(); }
        };
        /// @brief JSON 值类型 Array
        template<typename CharT>
        class Array : public Value<CharT> {
            std::vector<Value<CharT>*> values;

            class Iterator {
                Array<CharT>& arr;
                using iterator = typename std::vector<Value<CharT>*>::iterator;
                iterator it;
            public:
                Iterator(Array<CharT>& arr, iterator it) : arr(arr), it(it) {}
                ~Iterator() = default;

                bool operator!=(const Iterator& other) const { return it != other.it; }
                bool operator==(const Iterator& other) const { return it == other.it; }
                Iterator& operator++() { ++it; return *this; }
                Iterator operator++(int) { Iterator tmp(*this); ++it; return tmp; }
                Value<CharT>& operator*() const { return **it; }
            };
            class ConstIterator {
                const Array<CharT>& arr;
                using const_iterator = typename std::vector<Value<CharT>*>::const_iterator;
                const_iterator it;
            public:
                ConstIterator(const Array<CharT>& arr, const_iterator it) : arr(arr), it(it) {}
                ~ConstIterator() = default;

                bool operator!=(const ConstIterator& other) const { return it != other.it; }
                bool operator==(const ConstIterator& other) const { return it == other.it; }
                ConstIterator& operator++() { ++it; return *this; }
                ConstIterator operator++(int) { ConstIterator tmp(*this); ++it; return tmp; }
                const Value<CharT>& operator*() const { return **it; }
            };
        public:
            Array() = default;
            Array(const Array<CharT>& other) {
                for (const auto& member : other.values) {
                    values.push_back(new Value<CharT>());
                    assign(*values.back(), *member);
                }
            }
            Array(Array<CharT>&& other) {
                values.clear();
                values.swap(other.values);
            }
            Array& operator=(const Array<CharT>& other) {
                if (this == &other) return *this;
                for (auto member : values) delete member;
                for (const auto& member : other.values) {
                    values.push_back(new Value<CharT>());
                    assign(*values.back(), *member);
                }
                return *this;
            }
            Array& operator=(Array<CharT>&& other) {
                if (this == &other) return *this;
                for (auto member : values) delete member;
                values.clear();
                values.swap(other.values);
                return *this;
            }
            ~Array() override { for (auto member : values) delete member; }

            Iterator begin() { return Iterator(*this, values.begin()); }
            Iterator end() { return Iterator(*this, values.end()); }
            ConstIterator begin() const { return ConstIterator(*this, values.begin()); }
            ConstIterator end() const { return ConstIterator(*this, values.end()); }

            template<typename V>
                requires std::derived_from<std::remove_cvref_t<V>, Value<CharT>>
            void push_back(V value) {
                values.push_back(new Value<CharT>(value));
            }
            template<typename V>
                requires std::derived_from<std::remove_cvref_t<V>, Value<CharT>>
            void insert(size_t index, V value) {
                values.insert(values.begin() + index, new Value<CharT>(value));
            }
            template<size_t N>
            void push_back(const CharT(&value)[N]) { values.push_back(new String<CharT>(value)); }
            void push_back(const CharT* value) { values.push_back(new String<CharT>(value)); }
            void push_back(const StdString<CharT>& value) { values.push_back(new String<CharT>(value)); }
            void push_back(double value) { values.push_back(new Number<CharT>(value)); }
            void push_back(long long value) { values.push_back(new Number<CharT>(value)); }
            void push_back(bool value) { values.push_back(new Boolean<CharT>(value)); }
            template<size_t N>
            void push_front(const CharT(&value)[N]) { values.insert(values.begin(), new String<CharT>(value)); }
            void push_front(const CharT* value) { values.insert(values.begin(), new String<CharT>(value)); }
            void push_front(const StdString<CharT>& value) { values.insert(values.begin(), new String<CharT>(value)); }
            void push_front(double value) { values.insert(values.begin(), new Number<CharT>(value)); }
            void push_front(long long value) { values.insert(values.begin(), new Number<CharT>(value)); }
            void push_front(bool value) { values.insert(values.begin(), new Boolean<CharT>(value)); }
            template<size_t N>
            void insert(size_t index, const CharT(&value)[N]) { values.insert(values.begin() + index, new String<CharT>(value)); }
            void insert(size_t index, const CharT* value) { values.insert(values.begin() + index, new String<CharT>(value)); }
            void insert(size_t index, const StdString<CharT>& value) { values.insert(values.begin() + index, new String<CharT>(value)); }
            void insert(size_t index, double value) { values.insert(values.begin() + index, new Number<CharT>(value)); }
            void insert(size_t index, long long value) { values.insert(values.begin() + index, new Number<CharT>(value)); }
            void insert(size_t index, bool value) { values.insert(values.begin() + index, new Boolean<CharT>(value)); }

            void pop_back() {
                delete values.back();
                values.pop_back();
            }
            void pop_front() {
                delete values.front();
                values.erase(values.begin());
            }
            void erase(size_t index) {
                delete values[index];
                values.erase(values.begin() + index);
            }

            Value<CharT>& operator[](size_t index) { return *values[index]; }
            const Value<CharT>& operator[](size_t index) const { return *values[index]; }
            Value<CharT>& at(size_t index) { return *values.at(index); }
            const Value<CharT>& at(size_t index) const { return *values.at(index); }
            size_t size() const { return values.size(); }
        };
        /// @brief JSON 值类型 String
        template<typename CharT>
        class String : public Value<CharT> {
            StdString<CharT> value;
        public:
            String() = default;
            template<size_t N>
            String(const CharT(&value)[N]) : value(value, N) {}
            String(const StdString<CharT>& value) : value(value) {}
            String(StdString<CharT>&& value) { this->value.swap(value); }
            String(const String<CharT>& other) = default;
            String(String<CharT>&&) = default;
            String& operator=(const String<CharT>& other) = default;
            String& operator=(String<CharT>&&) = default;
            ~String() override = default;

            const StdString<CharT>& toString() const { return value; }

            template<size_t N>
            String& operator=(const CharT(&value)[N]) { this->value = StdString<CharT>(value, N); return *this; }
            String& operator=(const StdString<CharT>& value) { this->value = value; return *this; }
            String& operator=(StdString<CharT>&& value) { this->value.swap(value); return *this; }
            operator const StdString<CharT>& () const { return value; }
            bool operator==(const String<CharT>& other) const { return value == other.value; }
            bool operator!=(const String<CharT>& other) const { return value != other.value; }
        };
        /// @brief JSON 值类型 Number
        template<typename CharT>
        class Number : public Value<CharT> {
            double value{ 0 };
        public:
            Number() = default;
            Number(double value) : value(value) {}
            Number(const Number<CharT>& other) = default;
            Number(Number<CharT>&&) = default;
            Number& operator=(const Number<CharT>& other) = default;
            Number& operator=(Number<CharT>&&) = default;
            ~Number() override = default;

            double toFloat() const { return value; }
            long long toInt() const { return static_cast<long long>(value); }

            Number& operator=(double value) { this->value = value; return *this; }
            Number& operator=(long long value) { this->value = static_cast<double>(value); return *this; }
            operator double() const { return value; }
            operator long long() const { return toInt(); }
            bool operator==(const Number<CharT>& other) const { return value == other.value; }
            bool operator!=(const Number<CharT>& other) const { return value != other.value; }
            bool operator<(const Number<CharT>& other) const { return value < other.value; }
            bool operator<=(const Number<CharT>& other) const { return value <= other.value; }
            bool operator>(const Number<CharT>& other) const { return value > other.value; }
            bool operator>=(const Number<CharT>& other) const { return value >= other.value; }
        };
        /// @brief JSON 值类型 Boolean
        template<typename CharT>
        class Boolean : public Value<CharT> {
            bool value{ false };
        public:
            Boolean() = default;
            Boolean(bool value) : value(value) {}
            Boolean(const Boolean<CharT>& other) = default;
            Boolean(Boolean<CharT>&&) = default;
            Boolean& operator=(const Boolean<CharT>& other) = default;
            Boolean& operator=(Boolean<CharT>&&) = default;
            ~Boolean() override = default;

            bool toBool() const { return value; }

            Boolean& operator=(bool value) { this->value = value; return *this; }
            operator bool() const { return value; }
            bool operator!() const { return !value; }
            bool operator==(const Boolean<CharT>& other) const { return value == other.value; }
            bool operator!=(const Boolean<CharT>& other) const { return value != other.value; }
        };
        /// @brief JSON 值类型 Null
        template<typename CharT>
        class Null : public Value<CharT> {
        public:
            Null() = default;
            Null(const Null<CharT>&) = default;
            Null(Null<CharT>&&) = default;
            Null& operator=(const Null<CharT>&) = default;
            Null& operator=(Null<CharT>&&) = default;
            ~Null() override = default;

            operator bool() const { return false; }
            operator std::nullptr_t() const { return nullptr; }
            bool operator!() const { return true; }
        };

        template<typename CharT>
        void print(const Null<CharT>&, StdoStream<CharT>& ostream, int, int) {
            ostream << "null";
        }
        template<typename CharT>
        void print(const Boolean<CharT>& value, StdoStream<CharT>& ostream, int, int) {
            ostream << (value.toBool() ? "true" : "false");
        }
        template<typename CharT>
        void print(const Number<CharT>& value, StdoStream<CharT>& ostream, int, int) {
            ostream << value.toFloat();
        }
        template<typename CharT>
        void print(const String<CharT>& value, StdoStream<CharT>& ostream, int, int) {
            ostream << '"';
            bool escape = false;
            for (auto c : value.toString()) {
                if (escape) {
                    switch (c) {
                    case 'u': ostream << "\\"; break;
                    default: ostream << "\\\\"; break;
                    }
                    escape = false;
                }
                if (c == '\\') {
                    escape = true;
                    continue;
                }
                switch (c) {
                case '\b': ostream << "\\b"; break;
                case '\f': ostream << "\\f"; break;
                case '\n': ostream << "\\n"; break;
                case '\r': ostream << "\\r"; break;
                case '\t': ostream << "\\t"; break;
                case '"': ostream << "\\\""; break;
                default: ostream << c; break;
                }
            }
            ostream << '"';
        }
        template<typename CharT>
        void print(const Array<CharT>& value, StdoStream<CharT>& ostream, int tabsize = 4, int indent = 0) {
            ostream << "[" << (tabsize >= 0 ? "\n" : "");
            size_t index = 0;
            for (auto& member : value) {
                if (tabsize >= 0)
                    ostream << StdString<CharT>(tabsize * (indent + 1), ' ');
                print(member, ostream, tabsize, indent + 1);
                if (index + 1 != value.size())
                    ostream << ",";
                if (tabsize >= 0)
                    ostream << "\n";
                ++index;
            }
            if (value.size() > 0 && tabsize >= 0) {
                ostream << StdString<CharT>(tabsize * indent, ' ');
            }
            ostream << "]";
        }
        template<typename CharT>
        void print(const Object<CharT>& value, StdoStream<CharT>& ostream, int tabsize = 4, int indent = 0) {
            ostream << "{" << (tabsize >= 0 ? "\n" : "");
            size_t index = 0;
            for (auto [key, member] : value) {
                if (tabsize >= 0)
                    ostream << StdString<CharT>(tabsize * (indent + 1), ' ');
                print(String<CharT>(key), ostream, tabsize, indent + 1);
                ostream << ":" << (tabsize >= 0 ? " " : "");
                print(member, ostream, tabsize, indent + 1);
                if (index + 1 != value.size())
                    ostream << ",";
                if (tabsize >= 0)
                    ostream << "\n";
                ++index;
            }
            if (value.size() > 0 && tabsize >= 0) {
                ostream << StdString<CharT>(tabsize * indent, ' ');
            }
            ostream << "}";
        }

        /// @brief 序列化 JSON 数据到流
        /// @param value JSON 数据
        /// @param ostream 输出流
        /// @param tabsize 缩进空格数，若为负数则输出压缩后(无多余空白符)的 JSON 格式
        /// @throws std::bad_cast 输出检查类型识别失败时抛出此异常，通常是由于传入的 Value 不含有任何有效数据导致的
        ///                       例如直接从 Value<T> 构造且未经任何修改的的无效对象
        template<typename CharT>
        void print(const Value<CharT>& value, StdoStream<CharT>& ostream, int tabsize = 4, int indent = 0) {
            switch (value.type()) {
            case Type::Null:
                print(Null<CharT>(), ostream, tabsize, indent);
                break;
            case Type::Boolean:
                print(value.template as<Boolean>(), ostream, tabsize, indent);
                break;
            case Type::Number:
                print(value.template as<Number>(), ostream, tabsize, indent);
                break;
            case Type::String:
                print(value.template as<String>(), ostream, tabsize, indent);
                break;
            case Type::Array:
                print(value.template as<Array>(), ostream, tabsize, indent);
                break;
            case Type::Object:
                print(value.template as<Object>(), ostream, tabsize, indent);
                break;
            default:
                throw std::bad_cast();
            }
        }

        /// @brief JSON 解析异常类
        class JsonParseError : public std::runtime_error {
        public:
            JsonParseError(const std::string& message) : std::runtime_error(message) {}
        };

        template<typename CharT>
        Value<CharT>& parse(Null<CharT>& value, StdiStream<CharT>& istream) {
            using namespace std::string_literals;
            static StdString<CharT> null;
            static bool initialized = false;
            if (!initialized) {
                initialized = true;
                null.push_back((CharT)'n');
                null.push_back((CharT)'u');
                null.push_back((CharT)'l');
                null.push_back((CharT)'l');
            }
            StdString<CharT> sub;
            for (int count = 0; count < 4; ++count)
                sub += istream.get();
            if (sub != null)
                throw JsonParseError("Invalid null value");
            return value;
        }
        template<typename CharT>
        Value<CharT>& parse(Boolean<CharT>& value, StdiStream<CharT>& istream) {
            using namespace std::string_literals;
            static StdString<CharT> true_;
            static StdString<CharT> fals_;
            static StdString<CharT> false_;
            static bool initialized = false;
            if (!initialized) {
                initialized = true;
                true_.push_back((CharT)'t');
                true_.push_back((CharT)'r');
                true_.push_back((CharT)'u');
                true_.push_back((CharT)'e');
                fals_.push_back((CharT)'f');
                fals_.push_back((CharT)'a');
                fals_.push_back((CharT)'l');
                fals_.push_back((CharT)'s');
                false_.push_back((CharT)'f');
                false_.push_back((CharT)'a');
                false_.push_back((CharT)'l');
                false_.push_back((CharT)'s');
                false_.push_back((CharT)'e');
            }
            StdString<CharT> sub;
            for (int count = 0; count < 4; ++count)
                sub += istream.get();
            if (sub == true_) {
                value = true;
                return value;
            }
            if (sub == fals_) {
                sub += istream.get();
                if (sub != false_)
                    throw JsonParseError("Invalid boolean value");
                value = false;
                return value;
            }
            throw JsonParseError("Invalid boolean value");
        }
        template<typename CharT>
        Value<CharT>& parse(Number<CharT>& value, StdiStream<CharT>& istream) {
            using namespace std::string_literals;
            StdString<CharT> sub;
            while (isdigit(istream.peek())
                || istream.peek() == '.'
                || istream.peek() == 'e'
                || istream.peek() == 'E'
                || istream.peek() == '+'
                || istream.peek() == '-'
                ) sub += istream.get();
            if (sub[0] != '-' && !isdigit(sub[0]))
                throw JsonParseError("Invalid number value");
            try { value = std::stod(sub.c_str()); }
            catch (const std::exception& e) { throw JsonParseError("Invalid number value"); }
            return value;
        }
        template<typename CharT>
        Value<CharT>& parse(String<CharT>& value, StdiStream<CharT>& istream) {
            using namespace std::string_literals;
            if (istream.peek() != '"')
                throw JsonParseError("Invalid string value");
            istream.get();
            StdString<CharT> sub;
            while (istream.peek() != '"' && istream.peek() != std::char_traits<CharT>::eof()) {
                if (istream.peek() == '\\') {
                    istream.get();
                    switch (istream.peek()) {
                    case 'b': sub += '\b'; break;
                    case 'f': sub += '\f'; break;
                    case 'n': sub += '\n'; break;
                    case 'r': sub += '\r'; break;
                    case 't': sub += '\t'; break;
                    case '"': sub += '"'; break;
                    case '\\': sub += '\\'; break;
                    case '/': sub += '/'; break;
                    case 'u': (sub += '\\') += 'u'; break;
                    default: throw JsonParseError("Invalid escape sequence");
                    }
                    istream.get();
                }
                else if (istream.peek() == '\n') {
                    throw JsonParseError("Unexpected end of line in string value");
                }
                else {
                    sub += istream.get();
                }
            }
            if (istream.peek() == std::char_traits<CharT>::eof())
                throw JsonParseError("Unexpected end of file");
            istream.get();
            value = std::move(sub);
            return value;
        }
        template<typename CharT>
        Value<CharT>& parse(Value<CharT>&, StdiStream<CharT>&);
        template<typename CharT>
        Value<CharT>& parse(Array<CharT>& value, StdiStream<CharT>& istream) {
            using namespace std::string_literals;
            if (istream.peek() != '[')
                throw JsonParseError("Invalid array value");
            istream.get();
            while (istream.peek() != std::char_traits<CharT>::eof()) {
                while (std::isspace(istream.peek()))
                    istream.get();
                if (istream.peek() == std::char_traits<CharT>::eof())
                    throw JsonParseError("Unexpected end of file");
                if (istream.peek() == ']')
                    break;
                Value<CharT> member;
                parse(member, istream);
                switch (member.type()) {
                case Type::Null:
                    value.push_back(std::move(member.template as<Null>()));
                    break;
                case Type::Boolean:
                    value.push_back(std::move(member.template as<Boolean>()));
                    break;
                case Type::Number:
                    value.push_back(std::move(member.template as<Number>()));
                    break;
                case Type::String:
                    value.push_back(std::move(member.template as<String>()));
                    break;
                case Type::Array:
                    value.push_back(std::move(member.template as<Array>()));
                    break;
                case Type::Object:
                    value.push_back(std::move(member.template as<Object>()));
                    break;
                default:
                    throw JsonParseError("Invalid array value");
                }
                while (std::isspace(istream.peek()))
                    istream.get();
                if (istream.peek() == ',')
                    istream.get();
                else if (istream.peek() == ']')
                    break;
                else
                    throw JsonParseError("Invalid array value");
            }
            if (istream.peek() == std::char_traits<CharT>::eof())
                throw JsonParseError("Unexpected end of file");
            istream.get();
            return value;
        }
        template<typename CharT>
        Value<CharT>& parse(Object<CharT>& value, StdiStream<CharT>& istream) {
            using namespace std::string_literals;
            if (istream.peek() != '{')
                throw JsonParseError("Invalid object value");
            istream.get();
            while (istream.peek() != std::char_traits<CharT>::eof()) {
                while (std::isspace(istream.peek())) istream.get();
                if (istream.peek() == std::char_traits<CharT>::eof())
                    throw JsonParseError("Unexpected end of file");
                if (istream.peek() == '}')
                    break;
                String<CharT> key;
                parse(key, istream);
                while (std::isspace(istream.peek())) istream.get();
                if (istream.peek() != ':')
                    throw JsonParseError("Invalid object value");
                istream.get();
                while (std::isspace(istream.peek())) istream.get();
                Value<CharT> member;
                parse(member, istream);
                switch (member.type()) {
                case Type::Null:
                    value.insert(std::move(key.toString()), std::move(member.template as<Null>()));
                    break;
                case Type::Boolean:
                    value.insert(std::move(key.toString()), std::move(member.template as<Boolean>()));
                    break;
                case Type::Number:
                    value.insert(std::move(key.toString()), std::move(member.template as<Number>()));
                    break;
                case Type::String:
                    value.insert(std::move(key.toString()), std::move(member.template as<String>()));
                    break;
                case Type::Array:
                    value.insert(std::move(key.toString()), std::move(member.template as<Array>()));
                    break;
                case Type::Object:
                    value.insert(std::move(key.toString()), std::move(member.template as<Object>()));
                    break;
                default:
                    throw JsonParseError("Invalid object value");
                }
                while (std::isspace(istream.peek())) istream.get();
                if (istream.peek() == ',')
                    istream.get();
                else if (istream.peek() == '}')
                    break;
                else
                    throw JsonParseError("Invalid object value");
            }
            if (istream.peek() == std::char_traits<CharT>::eof())
                throw JsonParseError("Unexpected end of file");
            istream.get();
            return value;
        }
        /// @brief 从输入流中反序列化出一个 JSON 数据对象
        /// @param value 此参数将被填充为反序列化出的 JSON 数据
        /// @param istream 输入流
        /// @throws json::JsonParseError 解析 JSON 数据失败时抛出此异常
        /// @return value 参数
        template<typename CharT>
        Value<CharT>& parse(Value<CharT>& value, StdiStream<CharT>& istream) {
            using namespace std::string_literals;
            do {
                while (std::isspace(istream.peek()))
                    istream.get();
                if (istream.peek() == std::char_traits<CharT>::eof())
                    throw JsonParseError("Unexpected end of file");
                if (istream.peek() == '/') {
                    istream.get();
                    if (istream.peek() == '/') {
                        // Single-line comment
                        while (istream.peek() != '\n' && istream.peek() != std::char_traits<CharT>::eof())
                            istream.get();
                    }
                    else if (istream.peek() == '*') {
                        // Multi-line comment
                        bool maybeEnd = false;
                        while (istream.peek() != std::char_traits<CharT>::eof()) {
                            if (istream.peek() == '*')
                                maybeEnd = true;
                            else if (maybeEnd && istream.peek() == '/')
                                break;
                            else
                                maybeEnd = false;
                            istream.get();
                        }
                        istream.get();
                    }
                }
                else {
                    break;
                }
            } while (true);
            switch (istream.peek()) {
            case 'n': { value = Null<CharT>(); return parse(value.template as<Null>(), istream); }
            case 't': { value = Boolean<CharT>(); return parse(value.template as<Boolean>(), istream); }
            case 'f': { value = Boolean<CharT>(); return parse(value.template as<Boolean>(), istream); }
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            case '-': case '+': case '.': case 'e': case 'E':
            { value = Number<CharT>(); return parse(value.template as<Number>(), istream); }
            case '"': { value = String<CharT>(); return parse(value.template as<String>(), istream); }
            case '[': { value = Array<CharT>(); return parse(value.template as<Array>(), istream); }
            case '{': { value = Object<CharT>(); return parse(value.template as<Object>(), istream); }
            default:
                throw JsonParseError("Invalid value");
            }
        }
        /// @brief 从输入流中反序列化出一个 JSON 数据对象
        /// @param istream 输入流
        /// @param value 此参数将被填充为反序列化出的 JSON 数据
        /// @throws json::JsonParseError 解析 JSON 数据失败时抛出此异常
        /// @note 若输入流中没有有效数据，则此函数什么也不做，不会修改 value 参数
        template<typename CharT>
        StdiStream<CharT>& operator>>(StdiStream<CharT>& istream, Value<CharT>& value) {
            if (istream.peek() == std::char_traits<CharT>::eof())
                return istream;
            parse(value, istream);
            return istream;
        }
        /// @brief 序列化 JSON 数据到流
        /// @param value JSON 数据
        /// @param ostream 输出流
        /// @throw std::bad_cast 输出检查类型识别失败时抛出此异常，通常是由于传入的 Value 不含有任何有效数据导致的
        template<typename CharT>
        StdoStream<CharT>& operator<<(StdoStream<CharT>& ostream, const Value<CharT>& value) {
            print(value, ostream);
            return ostream;
        }
    }
}

/*
(仅)此文件以 MIT 许可证发布

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