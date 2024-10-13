#include <iostream>
#include <sstream>
#include <string>
#include <GraceFt/parser/json.hpp>

using namespace GFt;
using namespace std;

int main() {
    string json_str = R"({"name": "Grace", "age": 25, "city": "Beijing", "hobbies": ["reading", "swimming"]})";
    istringstream iss(json_str); // 输入流，可以是任意流对象，如 ifstream、stringstream 等

    json::Value<char> data;
    iss >> data;

    // 格式化输出
    cout << data << endl;
    cout << "----------------------------" << endl;
    // 压缩输出
    json::print(data, cout, -1);
    cout << endl;
    // 访问属性
    cout << data["name"].toString() << endl;
    cout << data["age"].toInt() << endl;
    // 如果属性类型不匹配，则会抛出异常
    // cout << data["age"].toString() << endl; // throws exception: std::bad_cast
    // 访问数组元素
    cout << data["hobbies"][0].toString() << endl;

    return 0;
}