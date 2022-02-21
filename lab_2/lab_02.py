from tkinter import *
import tkinter.messagebox as box
import numpy as np
from math import *

Triangels_m_x = [[450, 420, 480], [450, 420, 410], [450, 480, 490],
				[410, 420, 400],[400, 420, 400], [490, 500, 480],
				[500, 480, 500], [420, 480, 450], [420, 450, 400],
				[420, 400, 425], [480, 500, 450], [480, 500, 475], 
				[500, 475, 490], [400, 410, 425], [450, 450, 475],
				[450, 450, 425],[425, 450, 410], [475, 450, 485]]


Triangels_m_y = [[240, 180, 180], [240, 180, 220], [240, 180, 220],
				[220, 180, 200] ,[200, 180, 175], [220, 200, 180],
				[200, 180, 175] , [180, 180, 155] , [180, 155, 175],
				[180, 175, 165], [180, 175, 155], [180, 175, 165],
				[175, 165, 145], [175, 145, 165], [400, 240, 290],
				[240, 400, 290], [290, 240, 220], [290, 240, 222]]

Filed_m_x = [[490, 500, 498], [402, 400, 410], [450, 445, 455], 
			[450, 445, 440], [450, 455, 460], [450, 422, 478],
			[600, 576, 580], [532, 548, 540], [530, 520, 525],
			[550, 570, 560], [380, 360, 370], [340, 345, 350],
			[372, 380, 388]]

Filed_m_y = [[145, 175, 135], [135, 175, 145], [240, 230, 230],
			[240, 230, 235], [240, 230, 235], [380, 395, 395],
			[398, 375, 388], [210, 210, 218], [230, 230, 235],
			[232, 232, 242], [380,380,390], [390, 395, 390],
			[415, 423, 415]]


Lines_m_x = [[450, 490], [490, 500], [500, 500], [500, 480], [480, 500], [480, 490],
			[480, 450], [480, 420], [420, 450], [420, 410], [410, 450],
			[410, 400], [400, 420], [400, 400], [400, 420], [420, 450],
			[480, 450], [450, 500], [450, 400], [420, 425], [480, 475],
			[425, 410], [475, 490], [450, 450], [450, 475], [475, 450],
			[425, 450], [425, 450], [425, 410], [475, 485], [425, 422],
			[475, 478], [410, 422], [485, 478], [485, 535], [535, 478],
			[535, 535], [535, 478], [478, 515], [515, 535], [515, 580],
			[580, 535], [580, 600], [600, 535]]

Lines_m_y = [[240, 220], [220, 200], [200, 175], [175, 180], [180, 200], [180, 220],
			[180, 240], [180, 180] , [180, 240], [180, 220], [220, 240],
			[220, 200], [200, 180], [200, 175], [175, 180], [180, 155],
			[180, 155], [155, 175], [155, 175], [180, 165], [180, 165],
			[165, 145], [165, 145], [240, 380], [380, 290], [290, 240],
			[290, 240], [290, 380], [290, 220], [290, 222], [290, 395],
			[290, 395], [220, 395], [222, 395], [222, 285], [285, 395],
			[285, 365], [365, 395], [395, 398], [398, 365], [398, 398],
			[398, 365], [398, 398], [398, 365]]

Ovals_m_x = [[415, 435], [465, 485]]
Ovals_m_y = [[195, 215], [195, 215]]
X_m = 450
Y_m = 240

K_p = 0.75 # Коэфициенты масштабирования
K_m = 1.25

X_m_t = X_m
Y_m_t = Y_m

X_t = X_m
Y_t = Y_m

f = pi/50

def draw_line(x_1, y_1, x_2, y_2):
	cvs.create_line(x_1, y_1, x_2, y_2, fill = "black")
def draw_trian(x_1, y_1, x_2, y_2,x_3, y_3):
	cvs.create_polygon([x_1, y_1], [x_2, y_2], [x_3, y_3], outline = "black", fill = "white")
def draw_filed(x_1, y_1, x_2, y_2,x_3, y_3):
	cvs.create_polygon([x_1, y_1], [x_2, y_2], [x_3, y_3], outline = "black", fill = "black")
def draw_oval(x_1, y_1, x_2, y_2):
	#cvs.create_oval(x_1,y_1, x_2, y_2, fill = "grey")
	cvs.create_arc(x_1,y_1,x_2,y_2, start = 220, extent = 100, outline = "black", style = ARC)
def draw():
	#for i in range(0, len(Triangels_x)):
		#draw_trian(Triangels_x[i][0], Triangels_y[i][0], Triangels_x[i][1], Triangels_y[i][1],Triangels_x[i][2],Triangels_y[i][2])
	for i in range(0, len(Filed_m_x)):
		draw_filed(Filed_m_x[i][0], Filed_m_y[i][0], Filed_m_x[i][1], Filed_m_y[i][1], Filed_m_x[i][2],Filed_m_y[i][2])
	for i in range(0, len(Ovals_m_x)):
		draw_oval(Ovals_m_x[i][0], Ovals_m_y[i][0], Ovals_m_x[i][1], Ovals_m_y[i][1])
	for i in range(0, len(Lines_m_x)):
		draw_line(Lines_m_x[i][0], Lines_m_y[i][0], Lines_m_x[i][1], Lines_m_y[i][1])



def zoom_plus(event):
    xm = event.x
    ym = event.y

    global K_p

    global Lines_m_x
    global Lines_m_y

    global X_t
    global Y_t
    X_t = (K_p * X_t + (1 - K_p) * xm)
    Y_t = (K_p * Y_t + (1 - K_p) * ym)
    for i in range(0, len(Lines_m_x)):
        for j in range(0, 2):
            Lines_m_x[i][j] = (K_p * Lines_m_x[i][j] + (1 - K_p) * xm)
            Lines_m_y[i][j] = (K_p * Lines_m_y[i][j] + (1 - K_p) * ym)

    global Filed_m_x
    global Filed_m_y

    for i in range(0, len(Filed_m_x)):
        for j in range(0, 3):
            Filed_m_x[i][j] = (K_p * Filed_m_x[i][j] + (1 - K_p) * xm)
            Filed_m_y[i][j] = (K_p * Filed_m_y[i][j] + (1 - K_p) * ym)

    global Ovals_m_x
    global Ovals_m_y

    for i in range(0, len(Ovals_m_x)):
        for j in range(0, 2):
            Ovals_m_x[i][j] = (K_p * Ovals_m_x[i][j] + (1 - K_p) * xm)
            Ovals_m_y[i][j] = (K_p * Ovals_m_y[i][j] + (1 - K_p) * ym)

    cvs.delete("all")
    for i in range(0, len(Filed_m_x)):
        draw_filed(Filed_m_x[i][0], Filed_m_y[i][0], Filed_m_x[i][1], Filed_m_y[i][1], Filed_m_x[i][2],Filed_m_y[i][2])
    for i in range(0, len(Ovals_m_x)):
        draw_oval(Ovals_m_x[i][0], Ovals_m_y[i][0], Ovals_m_x[i][1], Ovals_m_y[i][1])
    for i in range(0, len(Lines_m_x)):
        draw_line(Lines_m_x[i][0], Lines_m_y[i][0], Lines_m_x[i][1], Lines_m_y[i][1])

def zoom_minus(event):
    xm = event.x
    ym = event.y

    global K_p

    global Lines_m_x
    global Lines_m_y

    global X_t
    global Y_t
    X_t = (K_m * X_t + (1 - K_m) * xm)
    Y_t = (K_m * Y_t + (1 - K_m) * ym)
    for i in range(0, len(Lines_m_x)):
        for j in range(0, 2):
            Lines_m_x[i][j] = (K_m * Lines_m_x[i][j] + (1 - K_m) * xm)
            Lines_m_y[i][j] = (K_m * Lines_m_y[i][j] + (1 - K_m) * ym)

    global Filed_m_x
    global Filed_m_y

    for i in range(0, len(Filed_m_x)):
        for j in range(0, 3):
            Filed_m_x[i][j] = (K_m * Filed_m_x[i][j] + (1 - K_m) * xm)
            Filed_m_y[i][j] = (K_m * Filed_m_y[i][j] + (1 - K_m) * ym)

    global Ovals_m_x
    global Ovals_m_y

    for i in range(0, len(Ovals_m_x)):
        for j in range(0, 2):
            Ovals_m_x[i][j] = (K_m * Ovals_m_x[i][j] + (1 - K_m) * xm)
            Ovals_m_y[i][j] = (K_m * Ovals_m_y[i][j] + (1 - K_m) * ym)

    cvs.delete("all")
    for i in range(0, len(Filed_m_x)):
        draw_filed(Filed_m_x[i][0], Filed_m_y[i][0], Filed_m_x[i][1], Filed_m_y[i][1], Filed_m_x[i][2],Filed_m_y[i][2])
    for i in range(0, len(Ovals_m_x)):
        draw_oval(Ovals_m_x[i][0], Ovals_m_y[i][0], Ovals_m_x[i][1], Ovals_m_y[i][1])
    for i in range(0, len(Lines_m_x)):
        draw_line(Lines_m_x[i][0], Lines_m_y[i][0], Lines_m_x[i][1], Lines_m_y[i][1])

def fake_func(event):
	return

def Zoom():
    cvs.bind('<Double-Button-1>', zoom_minus)
    cvs.bind('<Double-Button-3>', zoom_plus)
    cvs.bind('<Button-1>', fake_func)
    cvs.bind('<Button-3>', fake_func)

def get_center(event):
	global X_m_t
	global Y_m_t
	X_m_t = event.x
	Y_m_t = event.y

def transfer_to(event):
    x = event.x
    y = event.y
    global X_t
    global Y_t
    dx = x - X_t
    dy = y - Y_t
    X_t = x
    Y_t = y
    print(dx, dy)
    global Lines_m_x
    global Lines_m_y


    for i in range(0, len(Lines_m_x)):
        for j in range(0, 2):
            Lines_m_x[i][j] = Lines_m_x[i][j] + dx
            Lines_m_y[i][j] = Lines_m_y[i][j] + dy

    global Filed_m_x
    global Filed_m_y


    for i in range(0, len(Filed_m_x)):
        for j in range(0, 3):
            Filed_m_x[i][j] = Filed_m_x[i][j] + dx
            Filed_m_y[i][j] = Filed_m_y[i][j] + dy

    global Ovals_m_x
    global Ovals_m_y


    for i in range(0, len(Ovals_m_x)):
        for j in range(0, 2):
            Ovals_m_x[i][j] = Ovals_m_x[i][j] + dx
            Ovals_m_y[i][j] = Ovals_m_y[i][j] + dy

    cvs.delete("all")
    for i in range(0, len(Filed_m_x)):
        draw_filed(Filed_m_x[i][0], Filed_m_y[i][0], Filed_m_x[i][1], Filed_m_y[i][1], Filed_m_x[i][2],Filed_m_y[i][2])
    for i in range(0, len(Ovals_m_x)):
        draw_oval(Ovals_m_x[i][0], Ovals_m_y[i][0], Ovals_m_x[i][1], Ovals_m_y[i][1])
    for i in range(0, len(Lines_m_x)):
        draw_line(Lines_m_x[i][0], Lines_m_y[i][0], Lines_m_x[i][1], Lines_m_y[i][1])

def Transfer():
    cvs.bind('<Button-1>', transfer_to)
    cvs.bind('<Double-Button-1>', fake_func)
    cvs.bind('<Double-Button-3>', fake_func)

def Turn():
    cvs.bind('<Button-1>', get_center)
    cvs.bind('<Double-Button-1>', fake_func)
    cvs.bind('<Double-Button-3>', fake_func)

def turn_right():
    global Lines_m_x
    global Lines_m_y


    global X_t
    global Y_t
    X_t = X_m_t + (X_t - X_m_t) * cos(-f) + (Y_t - Y_m_t) * sin(-f)
    Y_t = Y_m_t - (X_t - X_m_t) * sin(-f) + (Y_t - Y_m_t) * cos(-f)
    for i in range(0, len(Lines_m_x)):
        for j in range(0, 2):
            Lines_m_x[i][j] = X_m_t + (Lines_m_x[i][j] - X_m_t) * cos(-f) + (Lines_m_y[i][j] - Y_m_t) * sin(-f)
            Lines_m_y[i][j] = Y_m_t - (Lines_m_x[i][j] - X_m_t) * sin(-f) + (Lines_m_y[i][j] - Y_m_t) * cos(-f)

    global Filed_m_x
    global Filed_m_y

    for i in range(0, len(Filed_m_x)):
        for j in range(0, 3):
            Filed_m_x[i][j] = X_m_t + (Filed_m_x[i][j] - X_m_t) * cos(-f) + (Filed_m_y[i][j] - Y_m_t) * sin(-f)
            Filed_m_y[i][j] = Y_m_t - (Filed_m_x[i][j] - X_m_t) * sin(-f) + (Filed_m_y[i][j] - Y_m_t) * cos(-f)

    global Ovals_m_x
    global Ovals_m_y

    for i in range(0, len(Ovals_m_x)):
        for j in range(0, 2):
            Ovals_m_x[i][j] = X_m_t + (Ovals_m_x[i][j] - X_m_t) * cos(-f) + (Ovals_m_y[i][j] - Y_m_t) * sin(-f)
            Ovals_m_y[i][j] = Y_m_t - (Ovals_m_x[i][j] - X_m_t) * sin(-f) + (Ovals_m_y[i][j] - Y_m_t) * cos(-f)

    cvs.delete("all")
    for i in range(0, len(Filed_m_x)):
        draw_filed(Filed_m_x[i][0], Filed_m_y[i][0], Filed_m_x[i][1], Filed_m_y[i][1], Filed_m_x[i][2],Filed_m_y[i][2])
    for i in range(0, len(Ovals_m_x)):
        draw_oval(Ovals_m_x[i][0], Ovals_m_y[i][0], Ovals_m_x[i][1], Ovals_m_y[i][1])
    for i in range(0, len(Lines_m_x)):
        draw_line(Lines_m_x[i][0], Lines_m_y[i][0], Lines_m_x[i][1], Lines_m_y[i][1])

def turn_left():
    global Lines_m_x
    global Lines_m_y

    global X_t
    global Y_t
    X_t = X_m_t + (X_t - X_m_t) * cos(f) + (Y_t - Y_m_t) * sin(f)
    Y_t = Y_m_t - (X_t - X_m_t) * sin(f) + (Y_t - Y_m_t) * cos(f)
    for i in range(0, len(Lines_m_x)):
        for j in range(0, 2):
            Lines_m_x[i][j] = X_m_t + (Lines_m_x[i][j] - X_m_t) * cos(f) + (Lines_m_y[i][j] - Y_m_t) * sin(f)
            Lines_m_y[i][j] = Y_m_t - (Lines_m_x[i][j] - X_m_t) * sin(f) + (Lines_m_y[i][j] - Y_m_t) * cos(f)

    global Filed_m_x
    global Filed_m_y

    for i in range(0, len(Filed_m_x)):
        for j in range(0, 3):
            Filed_m_x[i][j] = X_m_t + (Filed_m_x[i][j] - X_m_t) * cos(f) + (Filed_m_y[i][j] - Y_m_t) * sin(f)
            Filed_m_y[i][j] = Y_m_t - (Filed_m_x[i][j] - X_m_t) * sin(f) + (Filed_m_y[i][j] - Y_m_t) * cos(f)

    global Ovals_m_x
    global Ovals_m_y

    for i in range(0, len(Ovals_m_x)):
        for j in range(0, 2):
            Ovals_m_x[i][j] = X_m_t + (Ovals_m_x[i][j] - X_m_t) * cos(f) + (Ovals_m_y[i][j] - Y_m_t) * sin(f)
            Ovals_m_y[i][j] = Y_m_t - (Ovals_m_x[i][j] - X_m_t) * sin(f) + (Ovals_m_y[i][j] - Y_m_t) * cos(f)

    cvs.delete("all")
    for i in range(0, len(Filed_m_x)):
        draw_filed(Filed_m_x[i][0], Filed_m_y[i][0], Filed_m_x[i][1], Filed_m_y[i][1], Filed_m_x[i][2],Filed_m_y[i][2])
    for i in range(0, len(Ovals_m_x)):
        draw_oval(Ovals_m_x[i][0], Ovals_m_y[i][0], Ovals_m_x[i][1], Ovals_m_y[i][1])
    for i in range(0, len(Lines_m_x)):
        draw_line(Lines_m_x[i][0], Lines_m_y[i][0], Lines_m_x[i][1], Lines_m_y[i][1])

def info_task():
    F = box.showinfo(title='О программе', message =
    '''
    Вариант №14
    Нарисовать рисунок, затем его переместить, промасштабировать и повернуть.
    Масштабирование: двойной щелчок левой кнопкой - отдаление, правой - приближение
    Поворот: сначала выберите центр поворота (по умолчанию (450,240)), затем стрелочкам вправо и влево поворачивайте изображение
    Перенос: щелчок мышью для выбора точки переноса 
    ''')

def info_auther():
    F = box.showinfo(title='Об авторе', message =
    '''
    Ляпина Наталья ИУ7-42Б
    Вариант №14
    Могу рассказать анекдот
    ''')

def exit():
    window.destroy()

window = Tk()
window.geometry('1200x600')
#window.resizable(width=False, height=False) # Запрет разворота окна
window.title("Задача №1")

mainmenu = Menu(window)
window.config(menu=mainmenu)
mainmenu.add_command(label='О программе',command = info_task)
mainmenu.add_command(label='Об авторе',command = info_auther)
mainmenu.add_command(label='Выход',command = exit)

frame_cvs = Frame(window, relief = RAISED, borderwidth = 1)
frame_cvs.pack(fill = BOTH, expand = True, side = LEFT)
cvs = Canvas (frame_cvs, bg = "white")
cvs.pack(fill = BOTH, expand = True)

frame_but = Frame(window, relief = RAISED, borderwidth = 1)
frame_but.pack(side = TOP)
but1 = Button(frame_but, text = "Нарисовать", command = draw)
but1.grid(column = 0, row = 0, sticky = W + E, pady = 10, columnspan = 2)

but3 = Button(frame_but, text = "Масштабирование", command = Zoom )
but3.grid(column = 0, row = 4, pady = 10, columnspan = 2)

but4 = Button(frame_but, text = "Перенос", command = Transfer)
but4.grid(column = 0, row = 5, pady = 10, columnspan = 2, sticky = W + E)

but5 = Button(frame_but, state = DISABLED, text = " Отменить действие ")
but5.grid(column = 0, row = 6, columnspan = 2, pady = 10, sticky = W + E)

but6 = Button(frame_but, text = "Центр поворота", command = Turn)
but6.grid(column = 0, row = 2, pady = 10 , sticky = W + E, columnspan = 2)

but7 = Button(frame_but,text = "->", command = turn_right)
but7.grid(column = 1, row = 3, pady = 10)
but8 = Button(frame_but, text = "<-", command = turn_left)
but8.grid(column = 0, row = 3, pady = 10)

window.mainloop()	