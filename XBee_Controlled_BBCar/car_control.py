import time
import serial
import sys,tty,termios

class _Getch:
    def __call__(self):
        fd = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd)
        try:
            tty.setraw(sys.stdin.fileno())
            ch = sys.stdin.read(1)
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
        return ch

def get():
    inkey = _Getch()
    while(1):
        k=inkey()
        if k!='':break
    if k=='\x1b':
        k2 = inkey()
        k3 = inkey()
        if k3=='A': #up
            print ("d1 = 7 d2 = 7 west")
            s.write("/parking/run 7 7 W \n".encode())
        if k3=='B': #down
            print ("d1 = 12 d2 = 4 east")
            s.write("/parking/run 12 4 E \n".encode())
        if k3=='C': #right
            print ("d1 = 11 d2 = 9 east")
            s.write("/parking/run 11 9 E \n".encode())
        if k3=='D':
            print ("left")
            s.write("/turn/run 100 0.3 \n".encode())
        time.sleep(1)
        s.write("/stop/run \n".encode())
    elif k=='q':
        print ("quit")
        return 0
    else:
        print ("not an arrow key!")
    return 1

if len(sys.argv) < 1:
    print ("No port input")
s = serial.Serial(sys.argv[1])
while get():
    i = 0