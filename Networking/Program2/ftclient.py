#!/bin/python

import sys
import time
import socket
import client

if (len(sys.argv) < 5) or (len(sys.argv) > 6):
    print("Usage: ftclient.py [SERVER_HOST][SERVER_PORT][COMMAND][FILENAME][DATA_PORT]")
    sys.exit(1)

def run_client():
    """Main function"""
    #Set up variables using helper function
    host = client.parse_host()
    serv_port = client.parse_servport()
    serv_port_int = int(serv_port)
    data_port = client.parse_dataport()     
    data_port_int = int(data_port) 
    command = client.parse_command()   
    file_name = client.parse_filen()    
    client_name = socket.gethostname()
    client_name += ":" + serv_port

    #Set up control connection
    control_sock = socket.socket()
    control_sock.connect((host, serv_port_int))  
    
    print("Control connection established with server %s:%s\n" % (host, serv_port))

    #Set up data connection, client listens on data_sock
    data_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    data_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    data_sock.bind(('',data_port_int))
    data_sock.listen(1)
    print("Waiting for data connection")
    buff = control_sock.send(data_port.encode())
    buff = control_sock.recv(1024)
    #Print server message
    print(buff.decode())
    client.parse_comm(control_sock, command, file_name)
    
    data_fd, addr = data_sock.accept()
    print("Data connection established with server %s:%s" % (host, data_port))
    
    if command == '-l':
        print("Requesting directory list")
        while(True):
            directory = data_fd.recv(1024)
            print(directory.decode())
            if len(directory) == 0:
                break
            print("Directory transfer complete.\nConnection closed by client")
            data_sock.close()
            data_fd.close()
            control_sock.close()
            exit(0)

    if command == '-g':
        #Get file name from server to check if found
        buff = data_fd.recv(1024)
        #print(buff.decode())        
        if buff.decode() == "NOFILE":
            print("FILE NOT FOUND. Please check the name and try again. Quitting.")
            control_sock.close()
            data_fd.close()
            exit(1)
        #Open file for writing
        rec_file = open(buff, 'w')        
        #First receive chunk
        buff = data_fd.recv(1024)
        bytes_recv = len(buff)
        print("Receiving file contents"); 
        #Continue while buff > 0
        while(buff):
            rec_file.write(buff.decode())
            buff = data_fd.recv(1024)
            bytes_recv += len(buff)
        #Cleanup
        rec_file.close()
        print("File transfer complete. Bytes received %i" % (bytes_recv))
        print("Connection closed by client")
        data_sock.close()
        data_fd.close()
        control_sock.close()
        exit(0)

run_client()
