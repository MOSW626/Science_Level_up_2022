from copy import deepcopy
from list_expansion import list_expansion
import numpy as np
import cv2

Rmax = 100
scale = 1.
field = [[0]]
Rx, Ry = 0, 0


def updateField(lidarResult):
    """
    lidarResult = [
        [radian, ...],
        [distance, ...] ]
    """
    print(lidarResult)
    global field, Rmax, scale, Rx, Ry
    for (theta, r) in zip(lidarResult[0], lidarResult[1]):
        print('theta, r:',theta, r)
        print('update robot...')
        updateRobot()
        print('updated robot')
        if r > Rmax:
            print('over range')
            continue
        dx = r*np.cos(theta)*scale
        dy = r*np.sin(theta)*scale
        tx = Rx+dx
        ty = Ry+dy
        print(tx, ty)
        w,h = len(field[0]), len(field)
        if tx < 0:
            print('x-')
            list_expansion(field,loc=1, num=int(abs(tx)+1) )
            updateRobot(dx=int(tx))
        elif len(field[0]) < tx :
            print('x+')
            list_expansion(field, loc=1, direction=1, num=int(abs(tx-w)+1))
        elif ty < 0:
            print('y-')
            list_expansion(field, num=int(abs(ty)+1))
            updateRobot(dy=int(ty))
        elif len(field) < ty:
            print('y+')
            list_expansion(field, direction=1, num=int(abs(ty-h)+1))
        field[int(ty)][int(tx)] = 1
    print('end\n')

def updateRobot(xy=(None, None),dx=None,dy=None):
    global Rx, Ry
    if not None in xy:
        Rx = xy[0]
        Ry = xy[1]
    if dx != None:
        Rx += dx
    if dy != None:
        Ry -= dy

def show():
    global field
    img_f = deepcopy(field)
    x,y = len(img_f[0]), len(img_f)
    list_expansion(img_f, loc=1, direction=1, num=int(400-x))
    list_expansion(img_f, loc=0, direction=1, num=int(400-y))
    img_f = np.array(img_f, dtype=np.uint8) * 255
    cv2.imshow("test", img_f)
    cv2.waitKey()
    cv2.destroyAllWindows()

while True:
    a = input()
    l = a.split()
    print(l)
    if l[0].lower() == "end":
        break
    elif l[0] == "add":
        try:
            rad = float(l[1])
            dis = float(l[2])
            print('rad, dis:',rad, dis)
            updateField([[rad],[dis]])
        except:
            print('Wrong Form')
    print(field)

    show()