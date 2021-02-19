#!/usr/bin/env python

import socket

TCP_IP = '127.0.0.1'
TCP_PORT = 5006

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((TCP_IP, TCP_PORT))
s.listen(1)
 
conn, addr = s.accept()
#print 'Endereco de conexao: ', addr

while True:
	data = conn.recv(1024) #Tamanho do buffer.
	if data == "EXIT":
		print "Cliente Desconectou"
		break
	else:
		print "Mensagem Recebida:", data
		message = raw_input("Digite Sua Mensagem: ")
		conn.send(message)  # echo

conn.close()
