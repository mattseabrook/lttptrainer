// serve.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <err.h>

#include "serve.h"
/*
=============================================================================
						 HTTP_SERVE
=============================================================================
*/

int http_serve()
{

    int one = 1, client_fd;
    struct sockaddr_in svr_addr, cli_addr;
    socklen_t sin_len = sizeof(cli_addr);

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        err(1, "Unable to open the socket");

    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int));

    int port = 80;
    svr_addr.sin_family = AF_INET;
    svr_addr.sin_addr.s_addr = INADDR_ANY;
    svr_addr.sin_port = htons(port);

    //
    // Bind the socket
    //
    if (bind(sock, (struct sockaddr *)&svr_addr, sizeof(svr_addr)) == -1)
    {
        close(sock);
        err(1, "Unable to bind the socket");
    }

    listen(sock, 5);
    while (1)
    {
        client_fd = accept(sock, (struct sockaddr *)&cli_addr, &sin_len);

        if (client_fd == -1)
        {
            perror("Unable to accept the connection");
            continue;
        }

        //...
        char buffer[64];
        char response[8192];

        while (read(client_fd, buffer, sizeof buffer - 1) > 0)
        {
            printf("%s", buffer);
            //response = http_route(buffer);
        }

        write(client_fd, response, sizeof(response) - 1); /*-1:'\0'*/
        close(client_fd);
    }
}

char http_route(char url)
{
    //...

    // strcat

    // /api/ ?
    //
    // Byte Buffer
    //
    char response[] = "HTTP/1.1 200 OK\r\n"
                      "Content-Type: text/html; charset=UTF-8\r\n\r\n"
                      "<!DOCTYPE html><html><head><title>lttpLabs v.1.0 - Lakeshore Technical</title></head>"
                      "<body><h1>lttpLabs v.1.0</h1><div id=\"app\"></div></body><script src=\"app.js\"></html>\r\n";

    return response;
}