import numpy as np

def list_expansion(List:list=None, loc:bool=0, direction:bool=0, num:int=1, dum=0):
    if List == None:
        print('#list_expansion director#\n\
        List: target List to expand. it has to be 2D([[],[],...])\n\
        loc: 0 is row, 1 is column. default=0\n\
        direction: 0 is upper(or left) 1 is bottom(or right). default=0\n\
        num: length of list to be expanded. default=1\n\
        dum: it will be the item of list that will be added. default=0')
        return
    r,l = len(List), len(List[0])
    for _ in range(num):
        if loc==0: # row
            List.insert(0 if direction==0 else r, [dum for i in range(l)])
        else: # column
            for z in List:
                z.insert(0 if direction==0 else r, dum)

DEBUG = False

if DEBUG:
    f = [[0]]
    list_expansion(f, loc=1, direction=1, num=1)
    print(f)