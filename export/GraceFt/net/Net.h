#pragma once

/**
 * @file Net.h
 * @author Weiyi Anglebase
 * @date 2024-07-17
 * @brief 网络通信封装库
 *
 * 该库提供C++流操作符风格的网络通信接口封装，支持TCP和UDP协议。此库基于Winsock2 API实现，请确保编译时链接了ws2_32库。
 *
 *
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

#include<string>
#include<tuple>

#ifdef _MSC_VER
#pragma comment(lib, "ws2_32.lib")
#endif
#ifdef __GNUC__
#pragma message("Please add -lws2_32 to your linker options")
#endif

using byte = unsigned char;
/**
 * @brief 网络通信类型枚举
 */
enum NetType {
    TCP,
    UDP
};
template <NetType type> class Client;
template <NetType type> class Server;

/**
 * @brief 数据包
 */
class Data {
    template <NetType type> friend class Client;
    template <NetType type> friend class Server;
    int len = 0;
    byte* data = nullptr;

public:
    /**
     * @brief 构造函数
     * @param length 数据包长度
     */
    Data(int length = 0);
    Data(const Data& data);
    Data(Data&& data);
    const Data& operator = (const Data& data);
    const Data& operator = (Data&& data);
    ~Data();

    /**
     * @brief 读取数据
     * @param start 开始位置
     * @param size 读取大小
     * @param out 输出缓冲区
     * @return 实际读取大小
     */
    int read(int start, int size, byte* out);
    /**
     * @brief 写入数据
     * @param start 开始位置
     * @param size 写入大小
     * @param in 输入缓冲区
     * @return 实际写入大小
     * @note 如果数据包没有足够的容量容纳要写入的数据,它将会截断数据到数据包的最大容量
     */
    int write(int start, int size, const byte* in);
    /**
     * @brief 获取数据包长度
     * @return 数据包长度
     */
    int size() const;

    /**
     * @brief 读取数据包中的数据
     * @tparam T 数据类型
     * @param start 开始位置
     * @return 数据
     */
    template<typename T>
    T read(int start) {
        T result;
        this->read(start, sizeof(T), (byte*)&result);
        return result;
    }
    /**
     * @brief 读取数据包中的字符串
     * @param start 开始位置
     * @param size 读取最大长度
     * @return 字符串
     */
    std::string read(int start, int size) {
        char* result = new char[size];
        this->read(start, size, (byte*)result);
        return std::string(result);
    }
    /**
     * @brief 向数据包中写入数据
     * @tparam N 数据起始位置
     * @tparam T 数据类型
     * @param in 数据
     */
    template<std::size_t N, typename T>
    int write(const T& in) {
        return this->write(N, sizeof(T), (const byte*)&in);
    }
    /**
     * @brief 向数据包中写入字符串
     * @tparam N 数据起始位置
     * @param in 字符串
     */
    template<std::size_t N>
    int write(const std::string& in) {
        return this->write(N, in.length(), (const byte*)in.data());
    }
};

/**
 * @brief TCP服务端类
 */
template<>
class Server<TCP> {
    unsigned int* sock;
    int port;
    std::string ip;

public:
    Server();
    ~Server();

    /**
     * @brief 绑定端口
     * @param port 端口号
     * @param ip IP地址
     * @return 是否绑定成功
     * @note 如果ip为空，则绑定地址为“0.0.0.0”
     */
    bool bind(int port, const char* ip = nullptr);
    /**
     * @brief 监听连接
     * @param backlog 最大连接数(半连接池大小)
     * @return 是否监听成功
     */
    bool listen(int backlog);
    /**
     * @brief 从连接池中接收连接
     * @return 客户端对象
     */
    Client<TCP> accept();

    /**
     * @brief 关闭连接
     */
    void close();

    friend std::ostream& operator << (std::ostream& os, const Server<TCP>& server);
};

template<>
class Client<TCP> {
    friend class Server<TCP>;
    unsigned int* sock;

    bool onlyRS = false;
    std::string ip;
    int port;

    Client(int);
public:
    Client();
    ~Client();

    /**
     * @brief 连接到服务器
     * @param ip IP地址
     * @param port 端口号
     * @return 是否连接成功
     */
    bool connect(const char* ip, int port);
    /**
     * @brief 关闭连接
     */
    void close();

    /**
     * @brief 发送数据
     * @param data 数据包
     * @return 实际发送大小
     */
    int send(const Data& data);
    /**
     * @brief 接收数据
     * @param data 数据包
     * @return 实际接收大小
     */
    int recv(Data& data);

    /**
     * @brief 若为无效连接，返回false，否则返回true
     */
    operator bool() const;
    bool operator ! () const;

    friend std::ostream& operator << (std::ostream& os, const Client<TCP>& client);
};

// C++ IO流操作符重载
// 使用 >> 接收数据，使用 << 发送数据(箭头指向代表数据流向)
// 若没有数据可被接收，则会阻塞
// 开发者也可以通过重载 >> 和 << 实现自定义数据类型读写
Client<TCP>& operator << (Client<TCP>& client, const Data& data);
Client<TCP>& operator >> (Client<TCP>& client, Data& data);
Client<TCP>& operator << (Client<TCP>& client, const std::string& str);
Client<TCP>& operator >> (Client<TCP>& client, std::string& str);
Client<TCP>& operator << (Client<TCP>& client, char str);
Client<TCP>& operator >> (Client<TCP>& client, char& str);
Client<TCP>& operator << (Client<TCP>& client, int num);
Client<TCP>& operator >> (Client<TCP>& client, int& num);
Client<TCP>& operator << (Client<TCP>& client, long long num);
Client<TCP>& operator >> (Client<TCP>& client, long long& num);
Client<TCP>& operator << (Client<TCP>& client, unsigned int num);
Client<TCP>& operator >> (Client<TCP>& client, unsigned int& num);
Client<TCP>& operator << (Client<TCP>& client, unsigned long long num);
Client<TCP>& operator >> (Client<TCP>& client, unsigned long long& num);
Client<TCP>& operator << (Client<TCP>& client, float num);
Client<TCP>& operator >> (Client<TCP>& client, float& num);
Client<TCP>& operator << (Client<TCP>& client, double num);
Client<TCP>& operator >> (Client<TCP>& client, double& num);
Client<TCP>& operator << (Client<TCP>& client, long double num);
Client<TCP>& operator >> (Client<TCP>& client, long double& num);

enum MsgType {
    IP,
    Port
};

/**
 * @brief UDP服务端类
 */
template<>
class Server<UDP> {
    unsigned int* sock;
    std::string ip;
    int port;

public:
    Server();
    ~Server();

    /**
     * @brief 绑定端口
     * @param port 端口号
     * @param ip IP地址
     * @return 是否绑定成功
     * @note 如果ip为空，则绑定地址为“0.0.0.0”
     */
    bool bind(int port, const char* ip = nullptr);

    /**
     * @brief 接收数据
     * @param data 数据包
     * @return 数据来源地址
     */
    std::tuple<std::string, int> recvfrom(Data& data);
    /**
     * @brief 发送数据
     * @param data 数据包
     * @param addr 数据目标地址
     * @return 实际发送大小
     */
    int sendto(const Data& data, std::tuple<std::string, int> addr);
};

/**
 * @brief UDP客户端类
 */
template<>
class Client<UDP> {
    unsigned int* sock;

public:
    Client();
    ~Client();

    /**
     * @brief 接收数据
     * @param data 数据包
     * @return 数据来源地址
     */
    std::tuple<std::string, int> recvfrom(Data& data);
    /**
     * @brief 发送数据
     * @param data 数据包
     * @param addr 数据目标地址
     * @return 实际发送大小
     */
    int sendto(const Data& data, std::tuple<std::string, int> addr);
};