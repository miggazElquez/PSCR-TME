#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "Socket.h"

namespace pr {


void Socket::connect(const std::string& host, int port) {


	struct sockaddr_in dest;
	struct addrinfo *result;

	if (getaddrinfo(host.c_str()	, NULL, NULL, &result) != 0) {
		perror("getaddrinfo"); exit(EXIT_FAILURE);}
	dest.sin_addr = ((struct sockaddr_in*)result->ai_addr)->sin_addr;
	dest.sin_family = AF_INET;
	dest.sin_port = htons(port);


	if ((fd = socket(AF_INET,SOCK_STREAM,0)) == -1) {
		perror("socket");
		exit(1);
	}


	if (::connect(fd, (struct sockaddr *) &dest, sizeof(dest)) == -1) {
		perror("connect"); exit(1);
	}
}

void Socket::connect(in_addr ipv4, int port) {
	struct sockaddr_in dest;

	dest.sin_addr = ipv4;
	dest.sin_family = AF_INET;
	dest.sin_port = htons(port);

	if ((fd = socket(AF_INET,SOCK_STREAM,0)) == -1) {
		perror("socket");
		exit(1);
	}


	if (::connect(fd, (struct sockaddr *) &dest, sizeof(dest)) == -1) {
		perror("connect"); exit(1);
	}



}





}