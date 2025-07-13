#ifdef GFT_NET

#include"GraceFt/net/Net.h"

int main() {
    Server<TCP> server;

    server.bind(8080, "127.0.0.1");
    server.listen(5);

    auto client = server.accept();

    std::string s;
    client >> s;
    for (auto& c : s) {
        c = toupper(c);
    }

    client << s;

    server.close();
}

#else

#include <iostream>
int main()
{
    std::cout << "Feature 'net' not enabled." << std::endl;
    return 0;
}

#endif