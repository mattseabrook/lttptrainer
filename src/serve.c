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
						 HTTP SERVE
=============================================================================
*/

static char response[2048];

//===========================================================================

/*
===============
http_serve

Basic HTTP functionality
===============
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
        char buffer[8192];

        while (read(client_fd, buffer, sizeof buffer - 1) > 0)
        {
            char *url = strtok(buffer, "\n");

            http_route(url);

            break;
        }

        write(client_fd, response, sizeof(response) - 1); /*-1:'\0'*/
        close(client_fd);

        //...
        memset(response, 0, sizeof response);
    }
}

/*
===============
http_route

Delimit the first line of the request by " " and determine the action requested by the platform and/or end -user
===============
*/
void http_route(char *url)
{
    const char *pattern = " ";

    char *target = NULL;
    char *start, *end;

    if (start = strstr(url, pattern))
    {
        start += strlen(pattern);
        if (end = strstr(start, pattern))
        {
            target = (char *)malloc(end - start + 1);
            memcpy(target, start, end - start);
            target[end - start] = '\0';
        }
    }

    // Check for ? and remove all that before dealing with "target"

    if (target)
    {
        //
        // Home Page
        //
        if (strcmp(target, "/") == 0)
        {
            strcat(response, "HTTP/1.1 200 OK\r\n");
            strcat(response, "Content-Type: text/html; charset=UTF-8\r\n\r\n");
            strcat(response, "<!DOCTYPE html><html><head><title>lttpLabs v.1.1 - Lakeshore Technical</title></head>");
            strcat(response, "<body><div id=\"app\"></div></body><script src=\"http://127.0.0.1:52386/app.js\"></html>\r\n");
        }
        //
        // z3 API
        //
        else if (strcmp(target, "/api/z3") == 0)
        {
            strcat(response, "00EE0F5A");
        }
        //
        //
        //
        else
        {
            strcat(response, "HTTP/1.1 404 Not Found\r\n");
            strcat(response, "Content-Type: text/html; charset=UTF-8\r\n\r\n");
            strcat(response, "<!DOCTYPE html><html><head><title>lttpLabs v.1.1 - Lakeshore Technical</title></head>");
            strcat(response, "<body><p>Not Found!</p></body></html>\r\n");
        }
    }

    free(target);
}