#!/usr/bin/env python
import socket
from binascii import hexlify
def convert_ip4_address():
    for ip_addr in ['127.0.0.1', '192.168.0.1']:
        packed_ip4_addr = socket.inet_aton(ip_addr)
        unpacked_ip4_addr = socket.inet_ntoa(packed_ip4_addr)
        print ("IP address : %s => Packed: %s, Unpacked: %s" %(ip_addr, hexlify(packed_ip4_addr), unpacked_ip4_addr))
if __name__ == '__main__':
    convert_ip4_address()