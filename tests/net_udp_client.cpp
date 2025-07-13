#ifdef GFT_NET

#include"GraceFt/net/Net.h"

int main() {
    Client<UDP> client;
    auto addr = std::make_tuple(std::string("127.0.0.1"), 8080);
    int n = 15;
    Data data(sizeof(int));
    data.write<0>(n);
    client.sendto(data, addr);

    client.recvfrom(data);
    n = data.read<int>(0);
    printf("%d\n", n);
}

#else

#include <iostream>
int main()
{
    std::cout << "Feature 'net' not enabled." << std::endl;
    return 0;
}

#endif