#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "server.h"

client_t *client_insert(client_t **head, struct libwebsocket *socket) {
	client_t *client = (struct server_client_t *)malloc(sizeof(struct server_client_t));
	client->socket = socket;
	client->next = *head;
	*head = client;
	return client;
}

void client_remove(client_t **head, struct libwebsocket *socket) {
	for( client_t **current = head; *current; current = &(*current)->next ) {
		if( (*current)->socket == socket ) {
			client_t* next = (*current)->next;
			free(*current);
			*current = next;
			break;
		}
	}
}

static int callback_http(struct libwebsocket_context *, struct libwebsocket *, enum libwebsocket_callback_reasons, void *, void *, size_t);
static int callback_websockets(struct libwebsocket_context *, struct libwebsocket *, enum libwebsocket_callback_reasons,void *, void *, size_t);

static struct libwebsocket_protocols server_protocols[] = {
	{ "http-only", callback_http, 0 },
	{ NULL, callback_websockets, sizeof(int), 1024*1024 },
	{ NULL, NULL, 0 /* End of list */ }
};

server_t *server_create(int port, size_t buffer_size) {
	server_t *self = (server_t *)malloc(sizeof(server_t));
	memset(self, 0, sizeof(server_t));

  self->buffer_size = buffer_size;
	size_t full_buffer_size = LWS_SEND_BUFFER_PRE_PADDING + buffer_size + LWS_SEND_BUFFER_POST_PADDING;
	self->send_buffer_with_padding = (unsigned char *)malloc(full_buffer_size);
	self->send_buffer = &self->send_buffer_with_padding[LWS_SEND_BUFFER_PRE_PADDING];

  self->port = port;
	self->clients = NULL;

	lws_set_log_level(LLL_ERR | LLL_WARN, NULL);
}
