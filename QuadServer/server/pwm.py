import os
pins = ((8,13,18),(8,19,19),(9,14,14),(9,16,15),(9,21,16),(9,22,17))
pwmpath = '/sys/devices/ocp.2/P{0}_{1}.{2}/duty'

class signal:
  pwmfile=None
  def __init__(self,number):
    if not os.path.exists(pwmpath.format(*pins[number])):
      os.system('echo MULTC > /sys/devices/bone_capemgr.8/slots')
    self.pwmfile=open(pwmpath.format(*pins[number]),'w')
  def set_width(self,width):
    self.pwmfile.write(str(width))
    self.pwmfile.seek(0)
