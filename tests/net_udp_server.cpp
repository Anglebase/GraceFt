#ifdef GFT_NET

#include"GraceFt/net/Net.h"

int main() {
    Server<UDP> server;

    server.bind(8080, "127.0.0.1");
    for (;;) {
        Data data;
        auto addr = server.recvfrom(data);
        int n = data.read<int>(0);
        n++;
        printf("%d\n", n);
        data.write<0>(n);
        server.sendto(data, addr);
    }
}

#else

#include <iostream>
int main()
{
    std::cout << "Feature 'net' not enabled." << std::endl;
    return 0;
}

#endif