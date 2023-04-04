#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>

typedef struct s_clients {
	int id,
	char msg[1024]
} t_clients;

t_clients clients[1024];
fd_set readfds, writefds, active;
int fdMax = 0, idNext = 0;
char bufferRead[120000], bufferWrite[120000];

void ft_Error(char *str)
{
	if (str)
		write(2, str, strlen(str));
	else
		write(2, "Fatal Error", strlen("Fatal error"));
	write(2, "\n", 1);
	exit(1);
}

int main(int ac, char **av) {
	if (ac != 2)
		ftError("Wrong number of arguments");

// initialise the socket AF_NET for the adress ip, SOCK STREAM for the type of socket and 0 for the default protocol
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		ftError(NULL);
	FD_ZERO(&active);
	bzero(&clients, sizeof(clients));
	fdMax = sockfd;
	FD_SET(sockfd, &active);

	struct sockaddr_in servaddr; // sockaddr_in is used to store socket address information for IPv4.
	socklen_t len;
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(2130706433);
	servaddr.sin_port = htons(atoi(av[1]));

	if ((bind (sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) < 0)
		ft_Error(NULL);
	if (listen(sockfd, 10) < 0)
		ft_Error(NULL);

	while(1) {
		readfs = writefs = active;
		if (select(fdMax + 1, &readfds, &writefds, NULL, NULL) < 0) // this line waits for the activity
			continue;
		for(int fdI = 0; fdI <= fdMax; fdI++)
		{
			if (fD_ISSET(fdI, &readfds) && fdI == sockfd) {
				int connfd = accept(accept(sockfd, (struct sockaddr *)&servaddr, &len));
				if (connfd < 0)
					continue;
				fdMax = connfd > fdMax ? connfd : fdMax;
				clients[connfd].id = idNext++;
				FD_SET(connfd, &active);
				sprintf(bufferWrite, "server: client %d just arrived \n", clients[connfd].id);
				sendAll(connfd);
				break;
			}
		}
	}

}