import socket
import thread
import time
import serial
import os

def Main():
	global connection, address
        pos={
	'0000000':'a',
	'0J00000':'b',
	'0j00000':'c',
	'J000000':'d',
	'JJ00000':'e',
	'Jj00000':'f',
	'j000000':'g',
	'jJ00000':'h',
	'jj00000':'i',
	'00J0000':'j',
	'00j0000':'k',
	'J0J0000':'l',
	'J0j0000':'m',
	'j0J0000':'n',
	'j0j0000':'o',
	'000J000':'p',
	'000j000':'q',
	'J00J000':'r',
	'J00j000':'s',
	'j00J000':'t',
	'j00j000':'u',
	'0000B00':'v',
	'0000b00':'w',
	'0000J00':'x',
	'0000j00':'y',
	'00000J0':'z',
	'00000j0':'A',
	'000000J':'B'
	}

        pos2={
		'JJJ':'1',
        'JJ0':'2',
        'J0J':'3',
        'J00':'4',
        '0JJ':'5',
        '0J0':'6',
        '00J':'7',
        '000':'8'
        }

#	HOST = ''
#	PORT = 5000
	
#	SocketServer = socket.socket()
#	SocketServer.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
#	SocketServer.bind((HOST, PORT))

#	SocketServer.listen(1)
#	connection, address = SocketServer.accept()
	print "connection from: ", str(address)	
	connected = True
	while True:
		while not connected:
			#os.system('/sbin/ifup --force wlan0')
			serialCommunication('ac')
			print 'Se perdio la conexion, intentado reconectar...'
			try:
				SocketServer.listen(1)
				connection, address = SocketServer.accept()
				connected = True
			except socket.error:
				connection.close()
				SocketServer.close()
				reconnect(HOST,PORT)
				connected = True

		connection.settimeout(0.04)
		try:
			data = connection.recv(10)
		except socket.timeout:
			connection.close()
			SocketServer.close()
			reconnect(HOST,PORT)
			continue

		if not data:
			connected = False
		try:
			red = pos[data[0:7]]+pos2[data[7:10]]
		#	print red
			print data
		except KeyError:
			continue
		serialCommunication(red)
		time.sleep(0.001)

def serialCommunication(BufferOut):
	try:
		Mercury = serial.Serial('/dev/ttyAMA0',115200)
		#Mercury.open()
		#Mercury.write('=')
		Mercury.write(BufferOut)
		time.sleep(0.0001)
		#a = Mercury.read(size=4)
		print BufferOut
		#for i in BufferOut:
		#	Mercury.write(i)
		#	time.sleep(0.0001)
	except:
		print "Error abriendo el puerto serial"

def reconnect(host, port):
	serialCommunication('ac')
	print 'Conexion perdida, reconectando...'
	flag = True

	while flag:
		try:
			global connection, address
			SocketServer = socket.socket()
			SocketServer.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
			SocketServer.bind((HOST, PORT))
			SocketServer.listen(1)
			connection, address = SocketServer.accept()
			return 
		except socket.error:
			continue

	return

HOST = ''
PORT = 5000

SocketServer = socket.socket()
SocketServer.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
SocketServer.bind((HOST, PORT))	
SocketServer.listen(1)
connection, address = SocketServer.accept()

if __name__ == '__main__':
	Main()
