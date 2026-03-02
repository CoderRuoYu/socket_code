#include <iostream>
#include <sys/socket.h>
#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
void Usage(std::string filename)
{
    std::cout << "USAGE:" << filename << ' ' << "ip" << ' ' << "port" << std::endl;
}
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        Usage(argv[0]);
        exit(0);
    }
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in server;
    bzero(&server,sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(std::stoi(argv[2]));
    std::string serverip(argv[1]);
    server.sin_addr.s_addr = inet_addr(serverip.c_str());
    while (true)
    {
        std::cout << "请您输入您要发送的消息：";
        std::string sendmsg;
        std::cin >> sendmsg;

        sendto(sockfd, sendmsg.c_str(), sendmsg.size(), 0, (struct sockaddr *)&server, sizeof(server));
        struct sockaddr_in temp;
        socklen_t len = sizeof(temp);
        char buffer[1024];
        int m = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&temp, &len);
        if (m > 0)
        {
            buffer[m] = 0;
            std::cout << buffer << std::endl;
        }
    }

    return 0;
}