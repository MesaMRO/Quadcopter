class pid:
  kp=None
  ki=None
  kd=None
  err=None
  i=0
  d=0
  __init__(self,p,i,d):
    self.kp=p
    self.ki=i
    self.kd=d
    self.err=0

  step(self,target,value):
    self.err=target-value
    self.p_val=self.err*self.kp
    self.d_Val=self.kd*(self.err-self.d)
    self.d=self.err
    self.i=self.i+self.err
    self.i_val=self.i*self.ki
    self.i=self.i*.99
    return self.p_val+self.i_val+self.d_val
