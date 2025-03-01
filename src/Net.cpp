/**
 * @file Net.cpp
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


#include "net/Net.h"
#include <cstring>
#include <WinSock2.h>
#include <iostream>
#include <stdexcept>

void interNetError() {
    int err = WSAGetLastError();
    switch (err) {
    case WSAEACCES:
        throw std::runtime_error("Permission denied");
    case WSAEADDRINUSE:
        throw std::runtime_error("Address already in use");
    case WSAEADDRNOTAVAIL:
        throw std::runtime_error("Cannot assign requested address");
    case WSAEAFNOSUPPORT:
        throw std::runtime_error("Address family not supported by protocol family");
    case WSAEALREADY:
        throw std::runtime_error("Operation already in progress");
    case WSAEBADF:
        throw std::runtime_error("Bad file descriptor");
    case WSAECONNABORTED:
        throw std::runtime_error("Software caused connection abort");
    case WSAECONNREFUSED:
        throw std::runtime_error("Connection refused");
    case WSAECONNRESET:
        throw std::runtime_error("Connection reset by peer");
    case WSAEDESTADDRREQ:
        throw std::runtime_error("Destination address required");
    case WSAEFAULT:
        throw std::runtime_error("Bad address");
    case WSAEHOSTDOWN:
        throw std::runtime_error("Host is down");
    case WSAEHOSTUNREACH:
        throw std::runtime_error("No route to host");
    case WSAEINPROGRESS:
        throw std::runtime_error("Operation now in progress");
    case WSAEINTR:
        throw std::runtime_error("Interrupted function call");
    case WSAEINVAL:
        throw std::runtime_error("Invalid argument");
    case WSAEISCONN:
        throw std::runtime_error("Socket is already connected");
    case WSAEMFILE:
        throw std::runtime_error("Too many open files");
    case WSAEMSGSIZE:
        throw std::runtime_error("Message too long");
    case WSAENAMETOOLONG:
        throw std::runtime_error("File name too long");
    case WSAENETDOWN:
        throw std::runtime_error("Network is down");
    case WSAENETRESET:
        throw std::runtime_error("Network dropped connection on reset");
    case WSAENETUNREACH:
        throw std::runtime_error("Network is unreachable");
    case WSAENOBUFS:
        throw std::runtime_error("No buffer space available");
    case WSAENOPROTOOPT:
        throw std::runtime_error("Protocol not available");
    case WSAENOTCONN:
        throw std::runtime_error("Socket is not connected");
    case WSAENOTSOCK:
        throw std::runtime_error("Socket operation on non-socket");
    case WSAEOPNOTSUPP:
        throw std::runtime_error("Operation not supported on socket");
    case WSAEPFNOSUPPORT:
        throw std::runtime_error("Protocol family not supported");
    case WSAEPROCLIM:
        throw std::runtime_error("Too many processes");
    case WSAEPROTONOSUPPORT:
        throw std::runtime_error("Protocol not supported");
    case WSAEPROTOTYPE:
        throw std::runtime_error("Protocol wrong type for socket");
    case WSAESHUTDOWN:
        throw std::runtime_error("Cannot send after socket shutdown");
    case WSAESOCKTNOSUPPORT:
        throw std::runtime_error("Socket type not supported");
    case WSAETIMEDOUT:
        throw std::runtime_error("Connection timed out");
    case WSAETOOMANYREFS:
        throw std::runtime_error("Too many references");
    case WSAEUSERS:
        throw std::runtime_error("Too many users");
    case WSAEWOULDBLOCK:
        throw std::runtime_error("Operation would block");
    case WSAHOST_NOT_FOUND:
        throw std::runtime_error("Host not found");
    case WSANOTINITIALISED:
        throw std::runtime_error("Successful WSAStartup not yet performed");
    case WSANO_DATA:
        throw std::runtime_error("Valid name, no data record of requested type");
    case WSANO_RECOVERY:
        throw std::runtime_error("This is a non-recoverable error");
    case WSASERVICE_NOT_FOUND:
        throw std::runtime_error("Service not found");
    case WSASYSCALLFAILURE:
        throw std::runtime_error("System call failure");
    case WSASYSNOTREADY:
        throw std::runtime_error("Network subsystem is unavailable");
    case WSAVERNOTSUPPORTED:
        throw std::runtime_error("Winsock.dll version out of range");
    default:
        throw std::runtime_error("Unknown error");
    }
}

// 全局初始化
struct SocketInit {
    SocketInit() {
        WSADATA wsaData;
        auto res = WSAStartup(MAKEWORD(2, 2), &wsaData);
        switch (res) {
        case 0:
            break;
        case WSASYSNOTREADY:
            throw std::runtime_error("Network subsystem is unavailable");
        case WSAVERNOTSUPPORTED:
            throw std::runtime_error("Winsock.dll version out of range");
        default:
            throw std::runtime_error("Unknown error");
        }
    }
    ~SocketInit() {
        WSACleanup();
    }
};
SocketInit socketInit;

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

Data::Data(int length) {
    if (length > 0) {
        this->data = new byte[length];
        this->len = length;
    }
}

Data::Data(const Data& data) {
    this->data = new byte[data.len];
    this->len = data.len;
    std::memcpy(this->data, data.data, data.len);
}

Data::Data(Data&& data) {
    this->data = data.data;
    this->len = data.len;

    data.data = nullptr;
    data.len = 0;
}

const Data& Data::operator=(const Data& data) {
    if (this != &data) {
        delete[] this->data;
        this->data = new byte[data.len];
        this->len = data.len;
        std::memcpy(this->data, data.data, data.len);
    }
    return *this;
}

const Data& Data::operator=(Data&& data) {
    if (this != &data) {
        delete[] this->data;
        this->data = data.data;
        this->len = data.len;

        data.data = nullptr;
        data.len = 0;
    }
    return *this;
}

Data::~Data() {
    if (this->data)
        delete[] this->data;
    this->len = 0;
    this->data = nullptr;
}

int Data::read(int start, int size, byte* out) {
    if (start < 0 || start >= this->len || size < 0)
        return 0;
    if (start + size > this->len)
        size = this->len - start;
    std::memcpy(out, this->data + start, size);
    return size;
}

int Data::write(int start, int size, const byte* in) {
    if (start < 0 || start >= this->len || size < 0)
        return 0;
    if (start + size > this->len)
        size = this->len - start;
    std::memcpy(this->data + start, in, size);
    return size;
}

int Data::size() const {
    return this->len;
}

Server<TCP>::Server() {
    this->sock = (unsigned int*)socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if ((SOCKET)this->sock == INVALID_SOCKET)
        interNetError();
}

Server<TCP>::~Server() {
    if ((SOCKET)this->sock != INVALID_SOCKET)
        closesocket((SOCKET)this->sock);
}
Server<UDP>::Server() {
    this->sock = (unsigned int*)socket(AF_INET, SOCK_DGRAM, 0);
    if ((SOCKET)this->sock == INVALID_SOCKET)
        interNetError();
}

Server<UDP>::~Server() {
    if ((SOCKET)this->sock != INVALID_SOCKET)
        closesocket((SOCKET)this->sock);
}

bool Server<TCP>::bind(int port, const char* ip) {
    this->port = port;
    if (ip)
        this->ip = ip;
    else
        this->ip = "0.0.0.0";
    sockaddr_in addr;
    memset(&addr, 0, sizeof(sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (ip)
        addr.sin_addr.s_addr = inet_addr(ip);
    else
        addr.sin_addr.s_addr = INADDR_ANY;
    int res = ::bind((SOCKET)this->sock, (sockaddr*)&addr, sizeof(sockaddr_in)) == 0;
    if (res == SOCKET_ERROR)
        interNetError();
    return !res;
}

bool Server<UDP>::bind(int port, const char* ip) {
    this->port = port;
    if (ip)
        this->ip = ip;
    else
        this->ip = "0.0.0.0";
    sockaddr_in addr;
    memset(&addr, 0, sizeof(sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (ip)
        addr.sin_addr.s_addr = inet_addr(ip);
    else
        addr.sin_addr.s_addr = INADDR_ANY;
    auto res = ::bind((SOCKET)this->sock, (sockaddr*)&addr, sizeof(sockaddr_in));
    if (res == SOCKET_ERROR)
        interNetError();
    return !res;
}

std::tuple<std::string, int> Server<UDP>::recvfrom(Data& data) {
    int size = sizeof(sockaddr_in);
    sockaddr_in addr;
    int lenth;
    ::recvfrom((SOCKET)this->sock, (char*)&lenth, sizeof(int), 0, (sockaddr*)&addr, &size);
    data.len = lenth;
    if (data.data)
        delete[] data.data;
    data.data = new byte[lenth];
    ::recvfrom((SOCKET)this->sock, (char*)data.data, lenth, 0, (sockaddr*)&addr, &size);
    return { inet_ntoa(addr.sin_addr), ntohs(addr.sin_port) };
}

int Server<UDP>::sendto(const Data& data, std::tuple<std::string, int> addr) {
    sockaddr_in addr_in;
    memset(&addr_in, 0, sizeof(sockaddr_in));
    addr_in.sin_family = AF_INET;
    addr_in.sin_port = htons(std::get<Port>(addr));
    addr_in.sin_addr.s_addr = inet_addr(std::get<IP>(addr).c_str());

    auto res = ::sendto((SOCKET)this->sock, (const char*)&data.len, sizeof(int), 0,
        (sockaddr*)&addr_in, sizeof(sockaddr_in));
    if (res == SOCKET_ERROR)
        interNetError();
    res = ::sendto((SOCKET)this->sock, (const char*)data.data, data.len, 0,
        (sockaddr*)&addr_in, sizeof(sockaddr_in));
    if (res == SOCKET_ERROR)
        interNetError();
    return data.len;
}

bool Server<TCP>::listen(int backlog) {
    auto res = ::listen((SOCKET)this->sock, backlog);
    if (res == SOCKET_ERROR)
        interNetError();
    return true;
}

Client<TCP> Server<TCP>::accept() {
    Client<TCP> client(0);
    sockaddr_in addr;
    int len = sizeof(sockaddr_in);
    client.sock = (unsigned int*)::accept((SOCKET)this->sock, (sockaddr*)&addr, &len);
    if ((SOCKET)client.sock == INVALID_SOCKET)
        interNetError();
    client.ip = inet_ntoa(addr.sin_addr);
    client.port = ntohs(addr.sin_port);
    return client;
}

void Server<TCP>::close() {
    if ((SOCKET)this->sock != INVALID_SOCKET)
        closesocket((SOCKET)this->sock);
}

Client<TCP>::Client(int) {
    this->onlyRS = true;
}

Client<TCP>::Client() {
    this->sock = (unsigned int*)socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if ((SOCKET)this->sock == INVALID_SOCKET)
        interNetError();
}

Client<TCP>::~Client() {
    if ((SOCKET)this->sock != INVALID_SOCKET)
        closesocket((SOCKET)this->sock);
}

Client<UDP>::Client() {
    this->sock = (unsigned int*)socket(AF_INET, SOCK_DGRAM, 0);
    if ((SOCKET)this->sock == INVALID_SOCKET)
        interNetError();
}

Client<UDP>::~Client() {
    if ((SOCKET)this->sock != INVALID_SOCKET)
        closesocket((SOCKET)this->sock);
}

std::tuple<std::string, int> Client<UDP>::recvfrom(Data& data) {
    int size = sizeof(sockaddr_in);
    sockaddr_in addr;
    int lenth;
    auto res = ::recvfrom((SOCKET)this->sock, (char*)&lenth, sizeof(int),
        0, (sockaddr*)&addr, &size);
    if (res == SOCKET_ERROR)
        interNetError();
    data.len = lenth;
    if (data.data)
        delete[] data.data;
    data.data = new byte[lenth];
    res = ::recvfrom((SOCKET)this->sock, (char*)data.data, lenth,
        0, (sockaddr*)&addr, &size);
    if (res == SOCKET_ERROR)
        interNetError();
    return { inet_ntoa(addr.sin_addr), ntohs(addr.sin_port) };
}

int Client<UDP>::sendto(const Data& data, std::tuple<std::string, int> addr) {
    sockaddr_in addr_in;
    memset(&addr_in, 0, sizeof(sockaddr_in));
    addr_in.sin_family = AF_INET;
    addr_in.sin_port = htons(std::get<Port>(addr));
    addr_in.sin_addr.s_addr = inet_addr(std::get<IP>(addr).c_str());

    auto res = ::sendto((SOCKET)this->sock, (const char*)&data.len, sizeof(int), 0,
        (sockaddr*)&addr_in, sizeof(sockaddr_in));
    if (res == SOCKET_ERROR)
        interNetError();
    res = ::sendto((SOCKET)this->sock, (const char*)data.data, data.len, 0,
        (sockaddr*)&addr_in, sizeof(sockaddr_in));
    if (res == SOCKET_ERROR)
        interNetError();
    return data.len;
}

bool Client<TCP>::connect(const char* ip, int port) {
    if (this->onlyRS)
        return false;
    sockaddr_in addr;
    memset(&addr, 0, sizeof(sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);
    auto res = ::connect((SOCKET)this->sock, (sockaddr*)&addr, sizeof(sockaddr_in));
    if (res == SOCKET_ERROR)
        interNetError();
    return res == 0;
}

void Client<TCP>::close() {
    if ((SOCKET)this->sock != INVALID_SOCKET)
        closesocket((SOCKET)this->sock);
}

int Client<TCP>::send(const Data& data) {
    auto res = ::send((SOCKET)this->sock, (const char*)&data.len, sizeof(int), 0);
    if (res == SOCKET_ERROR)
        interNetError();
    res = ::send((SOCKET)this->sock, (const char*)data.data, data.len, 0);
    if (res == SOCKET_ERROR)
        interNetError();
    return data.len;
}

int Client<TCP>::recv(Data& data) {
    int length;
    auto res = ::recv((SOCKET)this->sock, (char*)&length, sizeof(int), 0);
    if (res == SOCKET_ERROR)
        interNetError();
    data.len = length;
    if (data.data)
        delete[] data.data;
    data.data = new byte[length];
    res = ::recv((SOCKET)this->sock, (char*)data.data, data.len, 0);
    if (res == SOCKET_ERROR)
        interNetError();
    return data.len;
}

Client<TCP>::operator bool() const {
    return (SOCKET)this->sock != INVALID_SOCKET;
}

bool Client<TCP>::operator!() const {
    return (SOCKET)this->sock == INVALID_SOCKET;
}

std::ostream& operator<<(std::ostream& os, const Server<TCP>& server) {
    if (server.ip.empty())
        return os << "[Servar: unbind]";
    return os << "[Servar: " << server.ip << ":" << server.port << "]";
}

std::ostream& operator<<(std::ostream& os, const Client<TCP>& client) {
    if (client.ip.empty())
        return os << "[Client:  this ]";
    return os << "[Client: " << client.ip << ":" << client.port << "]";
}

Client<TCP>& operator<<(Client<TCP>& client, const Data& data) {
    client.send(data);
    return client;
}

Client<TCP>& operator>>(Client<TCP>& client, Data& data) {
    client.recv(data);
    return client;
}

Client<TCP>& operator<<(Client<TCP>& client, const std::string& str) {
    Data data(str.length());
    data.write(0, str.length(), (const byte*)str.c_str());
    client.send(data);
    return client;
}

Client<TCP>& operator>>(Client<TCP>& client, std::string& str) {
    Data data;
    client.recv(data);
    char* p = new char[data.size() + 1];
    data.read(0, data.size(), (byte*)p);
    p[data.size()] = '\0';
    str = p;
    delete[] p;
    return client;
}

Client<TCP>& operator<<(Client<TCP>& client, char str) {
    Data data(1);
    data.write(0, 1, (const byte*)&str);
    client.send(data);
    return client;
}

Client<TCP>& operator>>(Client<TCP>& client, char& str) {
    Data data;
    client.recv(data);
    data.read(0, 1, (byte*)&str);
    return client;
}

Client<TCP>& operator<<(Client<TCP>& client, int num) {
    Data data(sizeof(int));
    data.write(0, sizeof(int), (const byte*)&num);
    client.send(data);
    return client;
}

Client<TCP>& operator>>(Client<TCP>& client, int& num) {
    Data data;
    client.recv(data);
    data.read(0, sizeof(int), (byte*)&num);
    return client;
}

Client<TCP>& operator<<(Client<TCP>& client, long long num) {
    Data data(sizeof(long long));
    data.write(0, sizeof(long long), (const byte*)&num);
    client.send(data);
    return client;
}

Client<TCP>& operator>>(Client<TCP>& client, long long& num) {
    Data data;
    client.recv(data);
    data.read(0, sizeof(long long), (byte*)&num);
    return client;
}

Client<TCP>& operator<<(Client<TCP>& client, unsigned int num) {
    Data data(sizeof(unsigned int));
    data.write(0, sizeof(unsigned int), (const byte*)&num);
    client.send(data);
    return client;
}

Client<TCP>& operator>>(Client<TCP>& client, unsigned int& num) {
    Data data;
    client.recv(data);
    data.read(0, sizeof(unsigned int), (byte*)&num);
    return client;
}

Client<TCP>& operator<<(Client<TCP>& client, unsigned long long num) {
    Data data(sizeof(unsigned long long));
    data.write(0, sizeof(unsigned long long), (const byte*)&num);
    client.send(data);
    return client;
}

Client<TCP>& operator>>(Client<TCP>& client, unsigned long long& num) {
    Data data;
    client.recv(data);
    data.read(0, sizeof(unsigned long long), (byte*)&num);
    return client;
}

Client<TCP>& operator<<(Client<TCP>& client, float num) {
    Data data(sizeof(float));
    data.write(0, sizeof(float), (const byte*)&num);
    client.send(data);
    return client;
}

Client<TCP>& operator>>(Client<TCP>& client, float& num) {
    Data data;
    client.recv(data);
    data.read(0, sizeof(float), (byte*)&num);
    return client;
}

Client<TCP>& operator<<(Client<TCP>& client, double num) {
    Data data(sizeof(double));
    data.write(0, sizeof(double), (const byte*)&num);
    client.send(data);
    return client;
}

Client<TCP>& operator>>(Client<TCP>& client, double& num) {
    Data data;
    client.recv(data);
    data.read(0, sizeof(double), (byte*)&num);
    return client;
}

Client<TCP>& operator<<(Client<TCP>& client, long double num) {
    Data data(sizeof(long double));
    data.write(0, sizeof(long double), (const byte*)&num);
    client.send(data);
    return client;
}

Client<TCP>& operator>>(Client<TCP>& client, long double& num) {
    Data data;
    client.recv(data);
    data.read(0, sizeof(long double), (byte*)&num);
    return client;
}
