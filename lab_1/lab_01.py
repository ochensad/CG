from tkinter import *
import tkinter.messagebox as box
import numpy as np
from math import *

X_p_a=[] #Первое множество точек изначальные координаты
Y_p_a=[]

X_p_b=[] #Второе множество точек изначальные координаты
Y_p_b=[]

K = 0 # Количество точек мн-ва а на окружности
M = 0 # Количество точек мн-ва b внутри окружности
Q = 0 # Количество точек мн-ва а внутри окружности

X_m_a=[] #Первое множество точек координаты после масштабирования
Y_m_a=[]

X_m_b=[] #Второе множество точек координаты после масштабирования
Y_m_b=[]

K_p = 0.5 # Коэфициенты масштабирования
K_m = 1.5


A_moves = [] # Массив действий над множеством а
B_moves = [] # Массив действий над множеством b
Flag_arr = [] # Массив del_flag-ов

nums = ['1', '2', '3', '4', '5', '6', '7','8','9','0']


def points_b():
    x = ''
    y = ''
    flag = 0
    global nums
    for sym in en2.get():
        if sym == ' ':
            flag = 1
        if flag == 0:
            if sym not in nums:
                F = box.showerror("Ошибка","Недопустимые символы")
                en2.delete(0, END)
                return
            else:
                x += sym
        else:
            if sym not in nums and sym != ' ':
                F = box.showerror("Ошибка","Недопустимые символы")
                en2.delete(0, END)
                return
            else:
                y += sym
    if (x == '' or y == ''):
    	F = box.showerror("Ошибка","Недостаточно данных")
    	return 0
    x = int(x)
    y = int(y)
    X_p_b.append(x)
    Y_p_b.append(y)

    last_move = cvs.create_oval(X_p_b[len(X_p_b) - 1]-5,Y_p_b[len(Y_p_b)-1]-5,X_p_b[len(X_p_b)-1]+5,Y_p_b[len(Y_p_b) - 1]+5,fill = "#00FF00")
    B_moves.append(last_move)
    Flag_arr.append("b")
    en2.delete(0, END)
    but9.config(state = NORMAL)
    but11.config(state = NORMAL)

def points_a():
    x = ''
    y = ''
    flag = 0
    for sym in en1.get():
        if sym == ' ':
            flag = 1
        if flag == 0:
            if sym not in nums:
                F = box.showerror("Ошибка","Недопустимые символы")
                en1.delete(0, END)
                return
            else:
                x += sym
        else:
            if sym not in nums and sym != ' ':
                F = box.showerror("Ошибка","Недопустимые символы")
                en1.delete(0, END)
                return
            else:
                y += sym
    if (x == '' or y == ''):
    	F = box.showerror("Ошибка","Недостаточно данных")
    	return 0
    x = int(x)
    y = int(y)
    X_p_a.append(x)
    Y_p_a.append(y)

    last_move = cvs.create_oval(X_p_a[len(X_p_a) - 1]-5,Y_p_a[len(Y_p_a)-1]-5,X_p_a[len(X_p_a)-1]+5,Y_p_a[len(Y_p_a) - 1]+5,fill = "#FF69B4")
    A_moves.append(last_move)
    Flag_arr.append("a")
    en1.delete(0, END)
    but9.config(state = NORMAL)
    but11.config(state = NORMAL)

def delite_move():
    del_flag = ""
    global Flag_arr
    if (len(Flag_arr) != 0):
        del_flag = Flag_arr[-1]
        Flag_arr.pop(-1)
    else:
        del_flag = "nope"

    if (del_flag == "b"):
        cvs.delete(B_moves[-1])
        B_moves.pop(-1)
        X_p_b.pop(-1)
        Y_p_b.pop(-1)
    elif (del_flag == "a"):
        cvs.delete(A_moves[-1])
        A_moves.pop(-1)
        X_p_a.pop(-1)
        Y_p_a.pop(-1)

def add_k():
    x = ''
    flag = 0
    for sym in en3.get():
        if sym not in nums:
            F = box.showerror("Ошибка","Недопустимые символы")
            en3.delete(0, END)
            return
        x += sym
    if (x == ''):
    	F = box.showerror("Ошибка","Недостаточно данных")
    	return 0
    x = int(x)
    if (x < 3):
        F = box.showerror("Ошибка","Для окружности нужны минимум 3 точки")
        en3.delete(0, END)
        return
    global K
    K = x;
    en3.delete(0, END)

def add_m():
    x = ''
    flag = 0
    for sym in en4.get():
        if sym not in nums:
            F = box.showerror("Ошибка","Недопустимые символы")
            en4.delete(0, END)
            return
        x += sym
    if (x == ''):
        F = box.showerror("Ошибка","Недостаточно данных")
        return 0
    x = int(x)
    global M
    M = x;
    en4.delete(0, END)

def add_q():
    x = ''
    flag = 0
    for sym in en5.get():
        if sym not in nums:
            F = box.showerror("Ошибка","Недопустимые символы")
            en5.delete(0, END)
            return
        x += sym
    if (x == ''):
        F = box.showerror("Ошибка","Недостаточно данных")
        return 0
    x = int(x)
    global Q
    Q = x;
    en5.delete(0, END)


def paint_a(event):
    x1 = event.x
    y1 = event.y

    if ((x1 - 5 >= 0) and (x1 + 5 <= 1500) and (y1 - 5 >= 0) and (y1 + 5 <= 900)):
        last_move = cvs.create_oval(x1-5,y1-5,x1+5,y1+5,fill = "#FF69B4")
        A_moves.append(last_move)
        Flag_arr.append("a")
        X_p_a.append(x1)
        Y_p_a.append(y1)
        but9.config(state = NORMAL)
        but11.config(state = NORMAL)

def paint_b(event):
    x1 = event.x
    y1 = event.y

    if ((x1 - 5 >= 0) and (x1 + 5 <= 1500) and (y1 - 5 >= 0) and (y1 + 5 <= 900)):
        last_move = cvs.create_oval(x1-5,y1-5,x1+5,y1+5,fill = "#00FF00")
        B_moves.append(last_move)
        Flag_arr.append("b")
        X_p_b.append(x1)
        Y_p_b.append(y1)
        but9.config(state = NORMAL)
        but11.config(state = NORMAL)

def zoom_minus(event):
    xm = event.x
    ym = event.y

    global K_m

    global X_m_a
    global Y_m_a
    if (len(X_m_a) == 0):
        X_m_a = X_p_a.copy()
        Y_m_a = Y_p_a.copy()

    for i in range(0, len(X_m_a)):
        X_m_a[i] = (K_m * X_m_a[i] + (1 - K_m) * xm)
        Y_m_a[i] = (K_m * Y_m_a[i] + (1 - K_m) * ym)

    cvs.delete("all")

    for i in range(0, len(X_m_a)):
        if ((X_m_a[i] - 5 >= 0) and (X_m_a[i] + 5 <= 1500) and (Y_m_a[i] - 5 >= 0) and (Y_m_a[i] + 5 <= 900)):
            cvs.create_oval(X_m_a[i]-5,Y_m_a[i]-5,X_m_a[i]+5,Y_m_a[i]+5, fill = "#FF69B4")

    global X_m_b
    global Y_m_b
    if (len(X_m_b) == 0):
        X_m_b = X_p_b.copy()
        Y_m_b = Y_p_b.copy()

    for i in range(0, len(X_m_b)):
        X_m_b[i] = (K_m * X_m_b[i] + (1 - K_m) * xm)
        Y_m_b[i] = (K_m * Y_m_b[i] + (1 - K_m) * ym)


    for i in range(0, len(X_m_b)):
        if ((X_m_b[i] - 5 >= 0) and (X_m_b[i] + 5 <= 1500) and (Y_m_b[i] - 5 >= 0) and (Y_m_b[i] + 5 <= 900)):
            cvs.create_oval(X_m_b[i]-5,Y_m_b[i]-5,X_m_b[i]+5,Y_m_b[i]+5, fill = "#00FF00")

def zoom_plus(event):
    xm = event.x
    ym = event.y

    global K_p

    global X_m_a
    global Y_m_a
    if (len(X_m_a) == 0):
        X_m_a = X_p_a.copy()
        Y_m_a = Y_p_a.copy()

    for i in range(0, len(X_m_a)):
        X_m_a[i] = (K_p * X_m_a[i] + (1 - K_p) * xm)
        Y_m_a[i] = (K_p * Y_m_a[i] + (1 - K_p) * ym)

    cvs.delete("all")

    for i in range(0, len(X_m_a)):
        if ((X_m_a[i] - 5 >= 0) and (X_m_a[i] + 5 <= 1500) and (Y_m_a[i] - 5 >= 0) and (Y_m_a[i] + 5 <= 900)):
            cvs.create_oval(X_m_a[i]-5,Y_m_a[i]-5,X_m_a[i]+5,Y_m_a[i]+5,fill = "#FF69B4")

    global X_m_b
    global Y_m_b
    if (len(X_m_b) == 0):
        X_m_b = X_p_b.copy()
        Y_m_b = Y_p_b.copy()

    for i in range(0, len(X_m_b)):
        X_m_b[i] = (K_p * X_m_b[i] + (1 - K_p) * xm)
        Y_m_b[i] = (K_p * Y_m_b[i] + (1 - K_p) * ym)

    for i in range(0, len(X_m_b)):
        if ((X_m_b[i] - 5 >= 0) and (X_m_b[i] + 5 <= 1500) and (Y_m_b[i] - 5 >= 0) and (Y_m_b[i] + 5 <= 900)):
            cvs.create_oval(X_m_b[i]-5,Y_m_b[i]-5,X_m_b[i]+5,Y_m_b[i]+5,fill = "#00FF00")

def cancel_zoom():
    cvs.delete("all")
    global X_p_b
    global Y_p_b

    for i in range(0, len(X_p_b)):
        if ((X_p_b[i] - 5 >= 0) and (X_p_b[i] + 5 <= 1500) and (Y_p_b[i] - 5 >= 0) and (Y_p_b[i] + 5 <= 900)):
            cvs.create_oval(X_p_b[i]-5,Y_p_b[i]-5,X_p_b[i]+5,Y_p_b[i]+5,fill = "#00FF00")

    global X_m_b
    global Y_m_b
    if (len(X_m_b) != 0):
        X_m_b = []
        Y_m_b = []
    global X_p_a
    global Y_p_a

    for i in range(0, len(X_p_a)):
        if ((X_p_a[i] - 5 >= 0) and (X_p_a[i] + 5 <= 1500) and (Y_p_a[i] - 5 >= 0) and (Y_p_a[i] + 5 <= 900)):
            cvs.create_oval(X_p_a[i]-5,Y_p_a[i]-5,X_p_a[i]+5,Y_p_a[i]+5,fill = "#FF69B4")

    global X_m_a
    global Y_m_a

    if (len(X_m_a) != 0):
        X_m_a = []
        Y_m_a = []

def fake_func(event):
    return

def edit(event):
    x = event.x
    y = event.y

    global find_i
    global en1_2

    find_i = -1
    for i in range(0, len(X_p_a)):
        if (x > X_p_a[i] - 3 and x < X_p_a[i] + 3) and (y > Y_p_a[i] - 3 and y < Y_p_a[i] + 3):
            find_i = i

    if (find_i != -1):
        cvs.create_oval(X_p_a[find_i]-5,Y_p_a[find_i]-5,X_p_a[find_i]+5,Y_p_a[find_i]+5,fill = "#FFFF00")
        cvs.bind('<Button-1>', fake_func)
        window_2 = Tk()
        window_2.geometry('300x150')
        window_2.resizable(width=False, height=False)
        window_2.title("Редактирование точки")

        name1_2 = Label(window_2, text = "Редактирование координат", relief = "solid", bg = "#FFFFFF")
        name1_2.place(x = 70, y = 15)
        name2_2 = Label(window_2, text = "x y:")
        name2_2.place(x = 40, y = 50)
        en1_2 = Entry(window_2)
        en1_2.place(x = 60, y = 50)
        but3_2 = Button(window_2, text = "ОК", command = new_point_a)
        but3_2.place(x = 200, y = 48)
        but4_2 = Button(window_2, text = "Удалить точку", command = del_point_a)
        but4_2.place(x = 100, y = 90)
        window_2.mainloop()
        return

    for i in range(0, len(X_p_b)):
        if (x > X_p_b[i] - 3 and x < X_p_b[i] + 3) and (y > Y_p_b[i] - 3 and y < Y_p_b[i] + 3):
            find_i = i

    if (find_i != -1):
        cvs.create_oval(X_p_b[find_i]-5,Y_p_b[find_i]-5,X_p_b[find_i]+5,Y_p_b[find_i]+5,fill = "#FFFF00")
        cvs.bind('<Button-1>', fake_func)
        window_2 = Tk()
        window_2.geometry('300x150')
        window_2.resizable(width=False, height=False)
        window_2.title("Редактирование точки")

        name1_2 = Label(window_2, text = "Редактирование координат", relief = "solid", bg = "#FFFFFF")
        name1_2.place(x = 70, y = 15)
        name2_2 = Label(window_2, text = "x y:")
        name2_2.place(x = 40, y = 50)
        en1_2 = Entry(window_2)
        en1_2.place(x = 60, y = 50)
        but3_2 = Button(window_2, text = "ОК", command = new_point_b)
        but3_2.place(x = 200, y = 48)
        but4_2 = Button(window_2, text = "Удалить точку", command = del_point_b)
        but4_2.place(x = 100, y = 90)
        window_2.mainloop()



def del_point_a():
    F = box.showinfo("Внимание","Действие необратимо")
    X_p_a.pop(find_i)
    Y_p_a.pop(find_i)
    cancel_zoom()

def del_point_b():
    F = box.showinfo("Внимание","Действие необратимо")
    X_p_b.pop(find_i)
    Y_p_b.pop(find_i)
    cancel_zoom()

def new_point_a():
    x = ''
    y = ''
    flag = 0
    for sym in en1_2.get():
        if sym == ' ':
            flag = 1
        if flag == 0:
            if sym not in nums:
                F = box.showerror("Ошибка","Недопустимые символы")
                en1_2.delete(0, END)
                return
            else:
                x += sym
        else:
            if sym not in nums and sym != ' ':
                F = box.showerror("Ошибка","Недопустимые символы")
                en1_2.delete(0, END)
                return
            else:
                y += sym
    if (x == '' or y == ''):
        F = box.showerror("Ошибка","Недостаточно данных")
        return 0
    x = int(x)
    y = int(y)
    X_p_a[find_i] = x
    Y_p_a[find_i] = y
    cancel_zoom()
    en1_2.delete(0, END)

def new_point_b():
    x = ''
    y = ''
    flag = 0
    for sym in en1_2.get():
        if sym == ' ':
            flag = 1
        if flag == 0:
            if sym not in nums:
                F = box.showerror("Ошибка","Недопустимые символы")
                en1_2.delete(0, END)
                return
            else:
                x += sym
        else:
            if sym not in nums and sym != ' ':
                F = box.showerror("Ошибка","Недопустимые символы")
                en1_2.delete(0, END)
                return
            else:
                y += sym
    if (x == '' or y == ''):
        F = box.showerror("Ошибка","Недостаточно данных")
        return 0
    x = int(x)
    y = int(y)
    X_p_b[find_i] = x
    Y_p_b[find_i] = y
    cancel_zoom()
    en1_2.delete(0, END)


def check_points(x_1, y_1, x_2, y_2, x_3, y_3):
    a = sqrt((x_1 - x_2)**2 + (y_1 - y_2)**2)
    b = sqrt((x_2 - x_3)**2 + (y_2 - y_3)**2)
    c = sqrt((x_3 - x_1)**2 + (y_3 - y_1)**2)
    p = (a + b + c) / 2
    global x_c
    global y_c
    global R
    try:
        S_tr = sqrt(p*(p-a)*(p-b)*(p-c))
        R = (a*b*c)/(4*S_tr)
        A = x_2 - x_1
        B = y_2 - y_1
        C = x_3 - x_1
        D = y_3 - y_1
        E = A * (x_1 + x_2) + B * (y_1 + y_2)
        F = C * (x_1 + x_3) + D * (y_1 + y_3)
        G = 2 * (A * (y_3 - y_2) - B * (x_3 - x_2))
        x_c = (D * E - B * F) / G
        y_c = (A * F - C * E) / G

        if ((x_3 - x_1) / (x_2 - x_1)) == ((y_3 - y_1)/ (y_2 - y_1)):
            R = 100000
            return 0
    except ZeroDivisionError:
        R = 10000
        return 0
    k_count = 3
    R = floor(R)
    x_c = floor(x_c)
    y_c = floor(y_c)
    for i in range(0, len(X_p_a)):
        if ((X_p_a[i] != x_1 and Y_p_a[i] != y_1) and (X_p_a[i] != x_2 and Y_p_a[i] != y_2) and (Y_p_a[i] != y_3 and X_p_a[i] != x_3)):
            if ((X_p_a[i] - x_c)**2 + (Y_p_a[i] - y_c) **2) <= (R+2)**2 and ((X_p_a[i] - x_c)**2 + (Y_p_a[i] - y_c) **2) >= (R - 2)**2:
                k_count+=1

    if (k_count != K):
        R = 100000
        return 0
    m_count = 0
    for i in range(0, len(X_p_b)):
        if ((X_p_b[i] - x_c)**2 + (Y_p_b[i] - y_c)**2) < R**2:
            m_count+=1

    if (m_count != M):
        R = 100000
        return 0

    q_count = 0
    for i in range(0, len(X_p_a)):
        if ((X_p_a[i] - x_c)**2 + (Y_p_a[i] - y_c)**2) < (R - 2)**2:
            q_count+=1

    if (q_count != Q):
        R = 10000
        return 0

    return 1

D = [0,0,0,0,0,0]
def combinations():
    global R
    R = 100000
    for i in range(0, len(X_p_a)):
        for j in range(i + 1, len(X_p_a)):
            for k in range(j + 1, len(X_p_a)):
                if (check_points(X_p_a[i], Y_p_a[i], X_p_a[j], Y_p_a[j], X_p_a[k], Y_p_a[k]) == 1):
                    D[0] = X_p_a[i]
                    D[1] = Y_p_a[i]
                    D[2] = X_p_a[j]
                    D[3] = Y_p_a[j]
                    D[4] = X_p_a[k]
                    D[5] = Y_p_a[k]
                    return

def Edit_points():
    but3.config(state = DISABLED)
    but4.config(state = DISABLED)
    but5.config(state = DISABLED)
    but6.config(state = DISABLED)
    but7.config(state = DISABLED)
    but8.config(state = DISABLED)
    but9.config(state = DISABLED)
    but10.config(state = DISABLED)

    cvs.bind('<Button-1>', edit)


def Keyboard():
    cancel_zoom()
    but3.config(state = NORMAL)
    but4.config(state = NORMAL)
    but5.config(state = NORMAL)
    but6.config(state = NORMAL)
    but7.config(state = NORMAL)
    but8.config(state = NORMAL)
    but10.config(state = NORMAL)

def Mouse():
    cancel_zoom()
    but3.config(state = DISABLED)
    but4.config(state = DISABLED)
    but5.config(state = NORMAL)
    but6.config(state = NORMAL)
    but7.config(state = NORMAL)
    but8.config(state = NORMAL)
    but10.config(state = NORMAL)

    cvs.bind('<Button-1>', paint_a)
    cvs.bind('<Button-3>', paint_b)

def Zoom():
    but3.config(state = DISABLED)
    but4.config(state = DISABLED)

    cvs.bind('<Double-Button-1>', zoom_minus)
    cvs.bind('<Double-Button-3>', zoom_plus)
    cvs.bind('<Button-1>', fake_func)
    cvs.bind('<Button-3>', fake_func)

def info_task():
    F = box.showinfo(title='О программе', message =
    '''
    Вариант №14
    Даны два множества точек на плоскости. Найти центр и радиус окружности, проходящей через k точек первого множества и содержащей строго внутри себя m точек второго множества и q точек первого.
    ''')

def info_auther():
    F = box.showinfo(title='Об авторе', message =
    '''
    Ляпина Наталья ИУ7-42Б
    Вариант №14
    Могу рассказать анекдот
    ''')

def Task_func():
    combinations()
    if (R < 100000):
        d = 2*(D[0]*(D[3]-D[5])+D[2]*(D[5]-D[1])+D[4]*(D[1]-D[3]))
        ux = ((D[0]*D[0]+D[1]*D[1])*(D[3]-D[5])+(D[2]*D[2]+D[3]*D[3])*(D[5]-D[1])+(D[4]*D[4]+D[5]*D[5])*(D[1]-D[3]))/d
        uy = ((D[0]*D[0]+D[1]*D[1])*(D[4]-D[2])+(D[2]*D[2]+D[3]*D[3])*(D[0]-D[4])+(D[4]*D[4]+D[5]*D[5])*(D[2]-D[0]))/d
        cvs.create_oval(ux-R,uy-R,ux+R,uy+R)
        text = "Радиус окружности " + str(R) + ". Центр окружности x: " + str(x_c) + " y: " + str(y_c)
        print(text) 
        F = box.showinfo("Решение",text)

    else:
        F = box.showinfo("Решение","Такой окружности нет:(")

window = Tk()
window.geometry('1200x600')
window.resizable(width=False, height=False) # Запрет разворота окна
window.title("Задача №1")

mainmenu = Menu(window)
window.config(menu=mainmenu)
mainmenu.add_command(label='О программе',command = info_task)
mainmenu.add_command(label='Об авторе',command = info_auther)


cvs = Canvas (window, width = 1000, height = 600, bg = "lightblue")
cvs.place(x = 0, y = 0)

name1 = Label(window, text = "Выберете способ ввода:", relief = "solid", bg = "#FFFFFF")
name1.place(x = 1030, y = 10)
but1 = Button(window, text = "Клавиатура", command = Keyboard)
but1.place(x = 1020, y = 35)
but2 = Button(window, text = "Мышь", command = Mouse)
but2.place(x = 1125, y = 35)

name2 = Label(window, text = "Первое множество", relief = "solid", bg = "#FF69B4")
name2.place(x = 1040, y = 80)
name3 = Label(window, text = "Введите координаты точки:")
name3.place(x = 1020, y = 110)
en1 = Entry(window)
en1.place(x = 1030, y = 133)
but3 = Button(window, state = DISABLED, text = "ОК", command = points_a)
but3.place(x = 1160, y = 130)

name4 = Label(window, text = "Второе множество", relief = "solid", bg = "#00FF00")
name4.place(x = 1040, y = 180)
name5 = Label(window, text = "Введите координаты точки:")
name5.place(x = 1020, y = 210)
en2 = Entry(window)
en2.place(x = 1030, y = 233)
but4 = Button(window, state = DISABLED, text = "ОК", command = points_b)
but4.place(x = 1160, y = 230)

name6 = Label(window, text = "Данные для задачи", relief = "solid", bg = "#FFFF00")
name6.place(x = 1040, y = 270)
name7 = Label(window, text = "Введите значение k:")
name7.place(x = 1020, y = 300)
en3 = Entry(window)
en3.place(x = 1030, y = 323)
but5 = Button(window, state = DISABLED, text = "ОК", command = add_k)
but5.place(x = 1160, y = 320)

name8 = Label(window, text = "Введите значение m:")
name8.place(x = 1020, y = 350)
en4 = Entry(window)
en4.place(x = 1030, y = 373)
but6 = Button(window, state = DISABLED, text = "ОК", command = add_m)
but6.place(x = 1160, y = 370)

name9 = Label(window, text = "Введите значение q:")
name9.place(x = 1020, y = 400)
en5 = Entry(window)
en5.place(x = 1030, y = 423)
but7 = Button(window, state = DISABLED, text = "ОК", command = add_q)
but7.place(x = 1160, y = 420)

but8 = Button(window, state = DISABLED, text = " Окончить ввод ", command = Task_func)
but8.place(x = 1050, y = 450)

but9 = Button(window, state = DISABLED, text = " Отменить действие ", command = delite_move)
but9.place(x = 1040, y = 485)

but10 = Button(window, state = DISABLED, text = " Масштабирование ", command = Zoom)
but10.place(x = 1040, y = 520)

but11 = Button(window, state = DISABLED, text = " Режим редактирования ", command = Edit_points)
but11.place(x = 1030, y = 555)

window.mainloop()	
