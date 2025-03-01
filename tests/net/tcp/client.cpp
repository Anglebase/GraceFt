#include"net/Net.h"

int main() {
    Client<TCP> client;

    client.connect("127.0.0.1", 8080);
    printf("Connected\n");
    std::string msg("Hello World!");

    client << msg;
    std::string s;
    client >> s;

    printf("%s\n", s.c_str());
}