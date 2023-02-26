# com6 : 모터부
# com8 : 센서부

import time
from datetime import datetime
from multiprocessing import Pool, Process
import os

import serial
import time

sensor_port = 'com8'
sensor_rate = 115200
motor_port = 'com6'
motor_rate = 9600


def getSensor(name):
    arduino = serial.Serial(sensor_port, sensor_rate)
    time.sleep(1)
    now = datetime.now()
    title = str(now.strftime('%Y-%m-%d %H.%M.%S')) + ".csv"
    f = open(title, 'w')
    f.close()
    while True:
        
        f = open(title, 'a')

        get = arduino.readline()
        get = get.decode()
        print("get", get)
        print(get.split())
        if len(get.split()) <= 1:
            continue
        data = get.split()[1]
        print("data:", data)

        f.write(data+"\n")
        
        f.close()

def controlMotor(name):
    arduino = serial.Serial(motor_port, motor_rate)
    time.sleep(1)
    cnt = 1
    while True:
        if cnt > 4:
            cnt = 1
        var = str(cnt)+'\n'
        var = var.encode('utf-8')
        arduino.write(var)
        cnt += 1
        time.sleep(1)

    # cnt = 0
    # while cnt <= 10:
    #     cnt += 1
    #     print(name, cnt)
 
if __name__ == '__main__':
    print('pid of main:', os.getpid())
 
    p1 = Process(target=getSensor, args=("proc_sensor",))
    p2 = Process(target=controlMotor, args=("proc_motor",))
 
    p1.start()
    p2.start()
    p1.join()
    p2.join()