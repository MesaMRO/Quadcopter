pins = ((8,13,18),(8,19,19),(9,14,14),(9,16,15),(9,21,16),(9,22,17))
path = '/sys/devices/ocp.2/P{0}_{1}.{2}/duty'

class signal:
  pwmfile=None
  def __init__(self,number):
    self.pwmfile=open(path.format(*pins[number]))
  def setwidth(self,width):
    self.pwmfile.write(str(width))

