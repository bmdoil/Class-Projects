#!/usr/bin/python

# Brent Doil - Project 1
# chatserv.py [port]
# OSU CS 372 - Fall 2017
# C chat server that listens on port given in CL argument. 
# If connection to chat server successful, allows server to send and recv 
# messages w/ client, set server handle, and close connection


import sys
import socket

#Constants in python ?!

#Check port
if len(sys.argv) != 2:
	print("Usage: ./chatserve.py [port]")
	sys.exit(1)

#Set server handle
serverHandle = ''
while(len(serverHandle) > 12 or len(serverHandle) == 0):
	serverHandle = input("Please enter your server handle [12 characters or less]\n")

#Function to send a chat message
def sendChat(socketConn, chat):
	charSent = 0
	while charSent < len(chat):
		sent = socketConn.send(chat[charSent:].encode())
		if sent == 0:
			socketConn.close()
		charSent += sent

#Function to receive a chat message
def recChat(socketConn):
	while True:
		read = ''
		read = socketConn.recv(512)
		return read.decode()

#Set port num
port = int(sys.argv[1])

#Connect and bind to socket
socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
socket.bind(('', port))

#Listen for a connection
socket.listen(1)

print("Waiting for a connection.\n")

#Listening: When connected, begin send and receive loops. Quit by entering !quit.
while True:
socketConn, addr = socket.accept()

	#Get client handle from client
	clientHandle = recChat(socketConn)
	print(clientHandle + " has connected.\n")

	clientCursor = clientHandle + "> "

	#Send server handle to client
	socketConn.send(serverHandle.encode())
	serverCursor = serverHandle + "> "

	while 1:
		#Receive, format, and print client message
		recMessage = recChat(socketConn)
		if recMessage:
			recMessage = recMessage.rstrip()
			print(clientCursor + recMessage)
		#Format and send server message, unless \quit
		sendMessage = input(serverCursor)
		if sendMessage == "!quit":
			print("Quitting.")
			break
		sendChat(socketConn, sendMessage)

	socketConn.close()
	print("Connection to client is closed")
	sys.exit(0)


