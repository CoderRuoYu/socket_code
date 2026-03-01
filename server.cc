#include "Server.hpp"
#include <memory>

void Usage(std::string filename)
{
    std::cout << filename << ' ' << "ip" << ' ' << "port" << std::endl;
}
int main(int argc, char **argv)
{

    if (argc != 3)
    {
        Usage(argv[0]);
        exit(0);
    }
    std::string serverip(argv[1]);
    uint16_t serverport = std::stoi(aggv[2]);
    auto p = std::make_unique<EchoServer>(serverip, serverport);
    p->Init();
    p->Start();
    return 0;
}