#include <iostream>
#include <string>
#include <cstdint>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <arpa/inet.h>
int defaultsocketfd = -1;
class EchoServer
{
public:
	EchoServer(std::string ip, uint16_t port)
		: _isRunning(false),
		  _serverport(port),
		  _serverip(ip),
		  _socketfd(defaultsocketfd) {}
	void Init()
	{
		_socketfd = socket(AF_INET, SOCK_DGRAM, 0);
		if (_socketfd == -1)
		{
			std::cout << "创建套接字失败" << std::endl;
			exit(1);
		}
		struct sockaddr_in addr;
		bzero(&addr, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_port = htons(_serverport);
		addr.sin_addr.s_addr = inet_addr(_serverip.c_str());

		if (-1 == bind(_socketfd, (sockaddr *)&addr, sizeof(addr)))
		{
			std::cout << "绑定ip:port失败" << std::endl;
			exit(2);
		}
	}
	void Start()
	{
		_isRunning = true;
		while (_isRunning)
		{
			char buff[1024];
			buff[0] = 0;
			struct sockaddr_in clientaddr;
			socklen_t addrlen = sizeof(clientaddr);
			int recvnums = recvfrom(_socketfd, buff, sizeof(buff), 0, (struct sockaddr *)&clientaddr, &addrlen);

			if (recvnums <= 0)
			{
				std::cout << "recv error" << std::endl;
				exit(0);
			}
			buff[recvnums] = 0;
			std::cout << "[" << "Client Ssy" << "]" << ":" << buff << std::endl;

			sendto(_socketfd, buff, recvnums, 0, (struct sockadd *)&clientaddr, addrlen);
		}
		_isRunning = false;
	}
	~EchoServer()
	{
		_isRunning = true;
	}

private:
	bool _isRunning;
	uint16_t _serverport;
	std::string _serverip;
	int _socketfd;
};
