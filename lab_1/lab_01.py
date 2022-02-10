from tkinter import *
import tkinter.messagebox as box
import numpy as np
from math import *

X_p_a=[] #Первое множество точек
Y_p_a=[]

X_p_b=[] #Второе множество точек
Y_p_b=[]

K = 0 # Количество точек мн-ва а на окружности
M = 0 # Количество точек мн-ва b внутри окружности
Q = 0 # Количество точек мн-ва а внутри окружности

last_move = 0
del_flag = "a"

def points_b():
    x = ''
    y = ''
    flag = 0
    for sym in en2.get():
        if sym == ' ':
            flag = 1
        if flag == 0:
            x += sym
        else:
            y += sym
    if (x == '' or y == ''):
    	F = box.showerror("Ошибка","Недостаточно данных")
    	return 0
    x = int(x)
    y = int(y)
    X_p_b.append(x)
    Y_p_b.append(y)
    global last_move
    global del_flag
    del_flag = "b"
    last_move = cvs.create_oval(X_p_b[len(X_p_b) - 1]-5,Y_p_b[len(Y_p_b)-1]-5,X_p_b[len(X_p_b)-1]+5,Y_p_b[len(Y_p_b) - 1]+5,fill = "#00FF00")
    en2.delete(0, END)
    but9.config(state = NORMAL)

def points_a():
    x = ''
    y = ''
    flag = 0
    for sym in en1.get():
        if sym == ' ':
            flag = 1
        if flag == 0:
            x += sym
        else:
            y += sym
    if (x == '' or y == ''):
    	F = box.showerror("Ошибка","Недостаточно данных")
    	return 0
    x = int(x)
    y = int(y)
    X_p_a.append(x)
    Y_p_a.append(y)
    global last_move
    global del_flag
    del_flag = "a"
    last_move = cvs.create_oval(X_p_a[len(X_p_a) - 1]-5,Y_p_a[len(Y_p_a)-1]-5,X_p_a[len(X_p_a)-1]+5,Y_p_a[len(Y_p_a) - 1]+5,fill = "#FF69B4")
    en1.delete(0, END)
    but9.config(state = NORMAL)

def delite_move():
	global del_flag
	cvs.delete(last_move)
	if (del_flag == "b"):
		X_p_b.pop(-1)
		Y_p_b.pop(-1)
	elif (del_flag == "a"):
		X_p_a.pop(-1)
		Y_p_a.pop(-1)
	del_flag = "nope"

def add_k():
    x = ''
    y = ''
    flag = 0
    for sym in en3.get():
        if sym == ' ':
            flag = 1
        if flag == 0:
            x += sym
        else:
            y += sym
    if (x == '' or y != ''):
    	F = box.showerror("Ошибка","Недостаточно данных")
    	return 0
    x = int(x)
    global K
    K = x;
    en3.delete(0, END)

def add_m():
    x = ''
    y = ''
    flag = 0
    for sym in en4.get():
        if sym == ' ':
            flag = 1
        if flag == 0:
            x += sym
        else:
            y += sym
    if (x == '' or y != ''):
    	F = box.showerror("Ошибка","Недостаточно данных")
    	return 0
    x = int(x)
    global M
    M = x;
    en4.delete(0, END)

def add_q():
    x = ''
    y = ''
    flag = 0
    for sym in en5.get():
        if sym == ' ':
            flag = 1
        if flag == 0:
            x += sym
        else:
            y += sym
    if (x == '' or y != ''):
    	F = box.showerror("Ошибка","Недостаточно данных")
    	return 0
    x = int(x)
    global Q
    Q = x;
    en5.delete(0, END)


def Keyboard():
    but2.config(state = DISABLED)
    but3.config(state = NORMAL)
    but4.config(state = NORMAL)
    but5.config(state = NORMAL)
    but6.config(state = NORMAL)
    but7.config(state = NORMAL)


def paint_a(event):
    x1 = event.x
    y1 = event.y
    global last_move
    if ((x1 - 5 >= 0) and (x1 + 5 <= 1500) and (y1 - 5 >= 0) and (y1 + 5 <= 900)):
        last_move = cvs.create_oval(x1-5,y1-5,x1+5,y1+5,fill = "#FF69B4")
        X_p_a.append(x1)
        Y_p_a.append(y1)
        but9.config(state = NORMAL)

def paint_b(event):
    x1 = event.x
    y1 = event.y
    global last_move
    if ((x1 - 5 >= 0) and (x1 + 5 <= 1500) and (y1 - 5 >= 0) and (y1 + 5 <= 900)):
        last_move = cvs.create_oval(x1-5,y1-5,x1+5,y1+5,fill = "#00FF00")
        X_p_b.append(x1)
        Y_p_b.append(y1)
        but9.config(state = NORMAL)


def Mouse():
    global last_move
    but1.config(state = DISABLED)
    but5.config(state = NORMAL)
    but6.config(state = NORMAL)
    but7.config(state = NORMAL)

    cvs.bind('<Button-1>', paint_a)
    cvs.bind('<Button-3>', paint_b)


window = Tk()
window.geometry('1200x600')
window.resizable(width=False, height=False) # Запрет разворота окна
window.title("Параметры")

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
name6.place(x = 1040, y = 280)
name7 = Label(window, text = "Введите значение k:")
name7.place(x = 1020, y = 310)
en3 = Entry(window)
en3.place(x = 1030, y = 333)
but5 = Button(window, state = DISABLED, text = "ОК", command = add_k)
but5.place(x = 1160, y = 330)

name8 = Label(window, text = "Введите значение m:")
name8.place(x = 1020, y = 360)
en4 = Entry(window)
en4.place(x = 1030, y = 383)
but6 = Button(window, state = DISABLED, text = "ОК", command = add_m)
but6.place(x = 1160, y = 380)

name9 = Label(window, text = "Введите значение q:")
name9.place(x = 1020, y = 410)
en5 = Entry(window)
en5.place(x = 1030, y = 433)
but7 = Button(window, state = DISABLED, text = "ОК", command = add_q)
but7.place(x = 1160, y = 430)

but8 = Button(window, state = DISABLED, text = " Окончить ввод ")
but8.place(x = 1050, y = 470)

but9 = Button(window, state = DISABLED, text = " Отменить действие ", command = delite_move)
but9.place(x = 1040, y = 510)

window.mainloop()	
