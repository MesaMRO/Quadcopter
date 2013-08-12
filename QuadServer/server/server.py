import socket
import pwm
import struct

srvsock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
srvsock.bind(('', 1337))
srvsock.listen(1)
axes=[]

<<<<<<< HEAD
for m in range(0,3):
  axes.append(pwm.signal(m))

while 1:
  for m in range(0,3):
    axes[m].set_width(1000000)
  (sock,addr)=srvsock.accept()
=======
for m in range(0,4):
  motors.append(pwm.signal(m))

while 1:
  for m in range(0,4):
    motors[m].set_width(1000000)
  print('listening')
  sock,addr=srvsock.accept()
  print('connected')
>>>>>>> 6349bb048767ae3159ca3d9c6fa25b142f545afa
  while 1:
    pkt=sock.recv(8)
    if len(pkt) == 0:
      break
<<<<<<< HEAD
    (axis,value)=struct.unpack_from('ii',pkt)
    axes[axis].set_width(100000*value+1000000)
=======
    motor,value=struct.unpack_from('ii',pkt)
    print('{0}: {1}'.format(motor,value))
    motors[motor].set_width(100000*value+1000000)
  print('disconnected')
>>>>>>> 6349bb048767ae3159ca3d9c6fa25b142f545afa
