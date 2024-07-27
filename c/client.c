#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include "socket.h"
#include "tcp.h"

int main(const int argc, const char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: client should receive the name of the file to save\n");
        return 1;
    }

    const char *const filename = argv[1];

    int fd = open(filename, O_RDONLY);

    if (fd == -1)
    {
        perror("Error opening file");
        return 1;
    }

    struct stat file_stats;
    if (fstat(fd, &file_stats) == -1)
    {
        perror("Error getting file stats");
        return 1;
    }

    const off_t file_size = file_stats.st_size;
    const int file_size_int = (int)file_size;

    int sock;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket creation error");
        return 1;
    }

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(CLIENT_PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        perror("Error when converting");
        return 1;
    }

    int socket_fd;
    if ((socket_fd = connect(sock, (struct sockaddr *)&serv_addr,
                             sizeof(serv_addr))) < 0)
    {
        perror("Connection failed");
        return 1;
    }

    close(fd);
}