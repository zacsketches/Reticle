//
// Hello World, ZeroMQ server
// Binds REP socket to tcp://*:5555
// Expects "Hello" from client and replies with "World!"
//
#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(void) {

	void* context = zmq_ctx_new();

	// Socket to talk to clients
	void* responder = zmq_socket(context, ZMQ_REP);
	zmq_bind(responder, "tcp://*:5555");

	printf("Starting Hello World server on port 5555\n");

	// Run server forever
	while(1) {
		// Wait for the next request from server
		zmq_msg_t request;
		zmq_msg_init (&request);
		zmq_msg_recv (&request, responder, 0);
		printf("Received Hello\n");
		zmq_msg_close (&request);

		// Do some work
		sleep(1);

		// Send reply back to client
		zmq_msg_t reply;
		zmq_msg_init_size(&reply, 6);
		memcpy(zmq_msg_data(&reply), "World!", 6);
		zmq_msg_send(&reply, responder, 0);
		zmq_msg_close(&reply);
	}
	// We never get here, but clean up for style
	zmq_close(responder);
	zmq_ctx_destroy(context);
	return 0;
}
