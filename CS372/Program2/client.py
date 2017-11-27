#file client.py

import sys
import socket

def parse_comm(connsock, command, file_name):
    """Interpret client command""" 
    print("Command: %s" % (command))
    sys.stdout.flush()
    if command == '-l':     
        buff = connsock.send(command.encode())
        buff = connsock.recv(1024)
        print(buff.decode())
        return
    elif command == '-g':
        buff = connsock.send(command.encode())
        buff = connsock.recv(1024)
        print(buff.decode())

        print("Sending file request: %s" % (file_name))
        buff = connsock.send(file_name.encode())
        buff = connsock.recv(1024)   
        print(buff.decode())
        return
    else:
        print("Please enter a valid command: -l or -g")
        connsock.close()
        sys.exit(1)
def parse_command():
    """Returns stripped client command"""
    comm = sys.argv[3].strip()
    return comm
def parse_host():
    """Returns stripped host name"""
    haddr = socket.gethostbyname(sys.argv[1].strip())
    return haddr
def parse_servport():
    """Returns server port"""
    servp = sys.argv[2]
    return servp
def parse_dataport():
    """Returns data port"""
    if len(sys.argv) == 5:
        datap = sys.argv[4]
    else:
        datap = sys.argv[5]
    return datap
def parse_filen():
    """If correct arg# then parse filename, otherwise return null"""
    if len(sys.argv) == 5:
        return "null"
    else:
        fname = sys.argv[4].strip()
        return fname
