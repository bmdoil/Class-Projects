#!/bin/python

import sys
import socket
import client

if (len(sys.argv) < 5) or (len(sys.argv) > 6):
    print("Usage: ftclient.py [SERVER_HOST][SERVER_PORT][COMMAND][FILENAME][DATA_PORT]")
    sys.exit(1)

command = client.parse_command()
serv_addr = client.parse_host()
serv_port = client.parse_servport()
data_port = client.parse_dataport()
file_name = client.parse_filen()
control_sock = client.control_conn()
buffer = 0

client.commands(control_sock, command, file_name, buffer)

data_sock = client.data_conn()

active_conn, address = socket.accept()
client.recv_dir(active_conn, buffer)
client.recv_file(active_conn, buffer, file_name)

print("Connection closed by client")
active_conn.close()



