#include "include/requests.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

int get(const char *url, char *path, char **response) {
  // TODO: Refactor

    char host[256];
    int port = 80;

    // Parse URL
    if ((sscanf(url, "https://%255[^:/]:%d/%255[^\n]", host, &port, path) < 1) &&
    		(sscanf(url, "http://%255[^:/]:%d/%255[^\n]", host, &port, path) < 1)) {
        fprintf(stderr, "Invalid URL format\n");
        return -1;
    }

    // Create socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket");
        return -1;
    }

    // Resolve hostname
    struct hostent *he = gethostbyname(host);
    if (he == NULL) {
        herror("gethostbyname");
        close(sock);
        return -1;
    }

    // Set up the server address structure
    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    memcpy(&server_addr.sin_addr, he->h_addr_list[0], he->h_length);

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        close(sock);
        return -1;
    }

    // Format the HTTP request
    char request[MAX_REQUEST_SIZE];
    snprintf(request, sizeof(request),
             "GET /%s HTTP/1.1\r\n"
             "Host: %s\r\n"
             "Connection: close\r\n"
             "\r\n",
             path, host);

    // Send the request
    if (send(sock, request, strlen(request), 0) < 0) {
        perror("send");
        close(sock);
        return -1;
    }

    // Receive the response
    int total_bytes = 0;
    int bytes_received;
    while ((bytes_received = recv(sock, *response + total_bytes, MAX_RESPONSE_SIZE - total_bytes - 1, 0)) > 0) {
        total_bytes += bytes_received;
        if (total_bytes >= MAX_RESPONSE_SIZE - 1) break;
    }

    if (bytes_received < 0) {
        perror("recv");
        free(*response);
        close(sock);
        return -1;
    }

    (*response)[total_bytes] = '\0';  // Null-terminate the response

    close(sock);
    return 0;
}
