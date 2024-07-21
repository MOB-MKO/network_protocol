#include "test.h"
#include <stdint.h>
#include <string.h>

int main() {
    uint32_t server_address = 0x12345678; // Example server address
    uint8_t message[] = "Hello, world!";
    uint16_t message_size = strlen((const char *)message) + 1; // Include null terminator

    // Example: Sending a message
    send_message(server_address, MSG_REQUEST, message, message_size);

    // Example: Receiving and handling incoming messages
    uint8_t buffer[1024];
    receive_message(buffer, sizeof(buffer));

    struct protocol_header *header = (struct protocol_header *)buffer;
    uint8_t *payload = buffer + sizeof(struct protocol_header);

    handle_request(header, payload);

    return 0;
}
