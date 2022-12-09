#include "ServerSocket.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <cstring>

namespace pr {

ServerSocket::ServerSocket(int port) {
	struct sockaddr_in sin; /* Nom de la socket de connexion */
	/* creation de la socket */
	if ((socketfd = socket(AF_INET,SOCK_STREAM,0)) < 0) {
		perror("socket"); exit(1);
	}
	memset((char *)&sin,0, sizeof(sin));
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_port = htons(port);
	sin.sin_family = AF_INET;
	/* nommage */
	if (bind(socketfd,(struct sockaddr *)&sin,sizeof(sin)) < 0) {
		perror("bind");
		exit(1);
	}
	listen(socketfd, 5);
}

void Socket::accept() {
    // Appeler la fonction accept() système
    struct sockaddr_in client_address;
    socklen_t client_address_len = sizeof(client_address);
    int client_fd = ::accept(socket_fd, (struct sockaddr*) &client_address, &client_address_len);


    // Afficher un message indiquant que la connexion a été reçue
    std::cout << "Connexion reçue de " << inet_ntoa(client_address.sin_addr) << std::endl;

    // Renvoyer un objet Socket pour la nouvelle connexion
    return Socket(client_fd);
}
	

}