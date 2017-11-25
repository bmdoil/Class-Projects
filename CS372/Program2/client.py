#file client.py


import sys
import socket

def commands(connsock, com, fname, buff):
    """Interpret client commands"""
    if com == '-l':
        buff = connsock.send(com.encode())
        buff = connsock.recv(1024)
    elif com == '-g':
        buff = connsock.send(com.encode())
        buff = connsock.recv(1024)
        buff = connsock.send(fname.encode())
        buff = connsock.recv(1024)
        fname = buff
    else:
        print("Please enter a valid command: -l or -g")
        connsock.close()
        sys.exit(1)
    return
def recv_dir(connection, buff):
    """Gets directory list from server"""
    command = parse_command()
    if command == "-l":
        print("Retrieving server directory")
        while 1:
            buff = connection.recv(1024)
            if len(buff) == 0:
                break
            print("%s", buff.decode())
    else: return "null"
def recv_file(connection, buff, filename):
    """Retrieves file from server, if it exists"""
    command = parse_command()
    if command == "-g":

        print("Retrieving file from server")
        buff = connection.recv(1024)
        connection.send(buff)
        buff.rstrip()

        filename = repr(buff.decode().rstrip('\x00'))

        if filename == "NOFILE":
            print("File does not exist on server. Quitting.")
            sys.exit(1)

        server_file = open(filename, 'w')
        buff = connection.recv(1024)

        while buff:
            server_file.write(buff.decode())
            buff = connection.recv(1024)
        server_file.close()
        print("Transfer complete")
    else: return "null"
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
def control_conn():
    """Connects control socket"""
    conn_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    conn_sock.connect(('', parse_servport))
    return conn_sock
def data_conn():
    """Sets up data socket"""
    data_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    data_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    data_sock.bind((''), parse_dataport)
    data_sock.listen(10)
    print("Waiting for a connection.\n")
    return data_sock
