#!/bin/python

import client


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



