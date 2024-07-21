#ifndef UNIVERSITY_PROTOCOL_H
#define UNIVERSITY_PROTOCOL_H

#include <stdint.h>
#include <stddef.h>

// Message types
#define MSG_REQUEST  1
#define MSG_RESPONSE 2
#define MSG_ACK      3

// Protocol header structure
struct protocol_header {
    uint8_t protocol_version;
    uint8_t message_type;
    uint16_t message_length;
    uint32_t source_address;
    uint32_t destination_address;
};

// Function prototypes
void send_message(uint32_t dest_addr, uint8_t msg_type, void *payload, uint16_t payload_size);
void receive_message(uint8_t *buffer, size_t buffer_size);
void handle_request(struct protocol_header *header, uint8_t *payload);
void send_response(uint32_t dest_addr, uint8_t *payload, uint16_t payload_size);

#endif /* UNIVERSITY_PROTOCOL_H */
