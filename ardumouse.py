import serial
import time
import uinput

def main():
    events = (
        uinput.REL_X,
        uinput.REL_Y,
        uinput.BTN_LEFT,
        uinput.BTN_RIGHT,
        )
    step = 2
    with uinput.Device(events) as device:
		ser = serial.Serial('/dev/ttyACM0', 9600)
		while True:
			input = str(ser.readline())
			i=0
			str1=""
			print input
			for i in range(0,len(input)):
				if(input[i]>='a' and input[i]<='z'):
					str1=str1+input[i]
			if (str1 == "up"):
				ans=int(0)
				for i in range(2,len(input)):
					if(ord(input[i])-ord('0')>=0 and ord(input[i])-ord('0')<=9):
						ans=10*ans+(ord(input[i])-ord('0'))
				print ans	
				for i in range(0,ans):	
					device.emit(uinput.REL_Y, -step, syn=False)
			if(str1 == "down"):
				ans=int(0)
				for i in range(4,len(input)):
					if(ord(input[i])-ord('0')>=0 and ord(input[i])-ord('0')<=9):
						ans=10*ans+(ord(input[i])-ord('0'))
				print ans
				for i in range(0,ans):
					device.emit(uinput.REL_Y, step, syn=False)
			if(str1 == "left"):
				ans=int(0)
				for i in range(4,len(input)):
					if(ord(input[i])-ord('0')>=0 and ord(input[i])-ord('0')<=9):
						ans=10*ans+(ord(input[i])-ord('0'))
				print ans
				for i in range(0,ans):
					device.emit(uinput.REL_X, -step)
			if(str1 == "right"):
				ans=int(0)
				for i in range(5,len(input)):
					if(ord(input[i])-ord('0')>=0 and ord(input[i])-ord('0')<=9):
						ans=10*ans+(ord(input[i])-ord('0'))
				print ans
				for i in range(0,ans):
					device.emit(uinput.REL_X, step)
			if(str1 == "lb"):
				device.emit(uinput.BTN_LEFT, 1)
			if(str1 == "lbr"):
				device.emit(uinput.BTN_LEFT,0)
			if(str1 == "rb"):
				device.emit(uinput.BTN_RIGHT,1)
			if(str1 == "rbr"):
				device.emit(uinput.BTN_RIGHT,0)

if __name__ == "__main__":
	main()
