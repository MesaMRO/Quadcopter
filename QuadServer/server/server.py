import socket
import pwm
import struct

srvsock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
srvsock.bind(('', 1337))
srvsock.listen(1)
motors=[]

for m in range(0,4):
  motors.append(pwm.signal(m))

while 1:
  for m in range(0,4):
    motors[m].set_width(1000000)
  print('listening')
  sock,addr=srvsock.accept()
  print('connected')
  while 1:
    pkt=sock.recv(8)
    if len(pkt) == 0:
      break
    motor,value=struct.unpack_from('ii',pkt)
    print('{0}: {1}'.format(motor,value))
    motors[motor].set_width(100000*value+1000000)
  print('disconnected')
