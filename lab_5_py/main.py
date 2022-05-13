from PyQt5 import QtWidgets, uic
from PyQt5.QtWidgets import QTableWidgetItem
from PyQt5.QtGui import QPen, QColor, QImage, QPixmap, QPainter
from PyQt5.QtCore import Qt, QTime, QCoreApplication, QEventLoop, QPoint
from PyQt5.QtWidgets import QPushButton, QColorDialog
import time
from time import process_time
import tkinter.messagebox as box

col_one = Qt.black
col_mark = Qt.blue
col_zero = Qt.white
global col_fill
col_fill = Qt.red
print(col_fill)


class Window(QtWidgets.QMainWindow):
    def __init__(self):
        QtWidgets.QWidget.__init__(self)
        uic.loadUi("window.ui", self)
        self.scene = myScene(0, 0, 1200, 800)
        self.scene.win = self
        self.view.setScene(self.scene)
        self.image = QImage(1200, 800, QImage.Format_ARGB32_Premultiplied)
        self.image.fill(col_zero)

        self.lock.clicked.connect(lambda: lock(self))
        self.erase.clicked.connect(lambda: clean_all(self))
        self.paint.clicked.connect(lambda: fill_xor(self))
        self.addpoint.clicked.connect(lambda: add_point_by_btn(self))
        self.change_color.clicked.connect(lambda: color_ch(self))
        self.edges = []
        self.point_now = None
        self.point_lock = None
        self.pen = QPen(col_one)
        self.delay.setChecked(False)
        self.horiz.setChecked(False)
        self.vertic.setChecked(False)
        self.timer.setChecked(False)


class myScene(QtWidgets.QGraphicsScene):
    def mousePressEvent(self, event):
        add_point(event.scenePos())



def color_ch(self):
    global col_fill
    col_fill = QColorDialog.getColor()


def add_row(win):
    win.table.insertRow(win.table.rowCount())



def add_point(point):
    global w

    if w.point_now is None:
        w.point_now = point
        w.point_lock = point
        add_row(w)
        i = w.table.rowCount() - 1
        item_x = QTableWidgetItem("{0}".format(point.x()))
        item_y = QTableWidgetItem("{0}".format(point.y()))
        w.table.setItem(i, 0, item_x)
        w.table.setItem(i, 1, item_y)
    else:
        if w.horiz.isChecked():
            w.edges.append([w.point_now.x(), w.point_now.y(),
                            point.x(), w.point_now.y()])
            w.point_now.x = point.x
            add_row(w)
            i = w.table.rowCount() - 1
            item_x = QTableWidgetItem("{0}".format(point.x()))
            item_y = QTableWidgetItem("{0}".format(w.point_now.y()))

            w.table.setItem(i, 0, item_x)
            w.table.setItem(i, 1, item_y)

            item_x = w.table.item(i - 1, 0)
            item_y = w.table.item(i - 1, 1)
            w.scene.addLine(point.x(), float(item_y.text()), float(item_x.text()), float(item_y.text()), w.pen)
            return

        elif w.vertic.isChecked():
            w.edges.append([w.point_now.x(), w.point_now.y(),
                            w.point_now.x(), point.y()])
            w.point_now.y = point.y
            add_row(w)
            i = w.table.rowCount() - 1
            item_x = QTableWidgetItem("{0}".format(w.point_now.x()))
            item_y = QTableWidgetItem("{0}".format(point.y()))

            w.table.setItem(i, 0, item_x)
            w.table.setItem(i, 1, item_y)

            item_x = w.table.item(i - 1, 0)
            item_y = w.table.item(i - 1, 1)
            w.scene.addLine(float(item_x.text()), point.y(), float(item_x.text()), float(item_y.text()), w.pen)
            return
        

        else:

            w.edges.append([w.point_now.x(), w.point_now.y(),
                                point.x(), point.y()])
            w.point_now = point
            add_row(w)
            i = w.table.rowCount() - 1
            item_x = QTableWidgetItem("{0}".format(point.x()))
            item_y = QTableWidgetItem("{0}".format(point.y()))
            w.table.setItem(i, 0, item_x)
            w.table.setItem(i, 1, item_y)
            item_x = w.table.item(i-1, 0)
            item_y = w.table.item(i-1, 1)
            w.scene.addLine(point.x(), point.y(), float(item_x.text()), float(item_y.text()), w.pen)
            return


def lock(win):
    win.edges.append([win.point_now.x(), win.point_now.y(), win.point_lock.x(), win.point_lock.y()])
    win.scene.addLine(win.point_now.x(), win.point_now.y(), win.point_lock.x(), win.point_lock.y(), w.pen)
    win.point_now = None



def clean_all(win):
    win.scene.clear()
    win.table.clear()
    win.edges = []
    win.point_now = None
    win.point_lock = None
    win.image.fill(col_zero)
    r = win.table.rowCount()
    for i in range(r, -1, -1):
        win.table.removeRow(i)


def draw_edges(image, edges):
    p = QPainter()
    p.begin(image)
    p.setPen(QPen(Qt.black))
    for ed in edges:
        p.drawLine(int(ed[0]), int(ed[1]), int(ed[2]), int(ed[3]))
    p.end()

def RoundToInt(a):
	return int(round(a))

def draw_line(image, x_s, y_s, x_e, y_e):
    p = QPainter()
    p.begin(image)
    p.setPen(QPen(Qt.black))
    
    if (x_s == x_e and y_s == y_e):
        p.drawPoint(int(x_e), int(y_e))

    l = abs(x_e - x_s)
    if (l < abs(y_e - y_s)):
    	l = abs(y_e - y_s)

    dx = float(x_e - x_s) / l
    dy = float(y_e - y_s) / l

    x = x_s
    y = y_s

    x_prev = RoundToInt(x)
    y_prev = RoundToInt(y)

    for i in range(0, l + 1):
    	x_r = RoundToInt(x)
    	y_r = RoundToInt(y)

    	x_prev = x_r
    	y_prev = y_r

    	p.drawPoint(int(x_r), int(y_r))

    	x += dx
    	y += dy

    p.end()

def draw_lines(image, edges):
    for ed in edges:
        draw_line(image, int(ed[0]), int(ed[1]), int(ed[2]), int(ed[3]))

def delay(ms):
    #QCoreApplication.processEvents(QEventLoop.AllEvents, 1)
    #QtWidgets.QApplication.processEvents(QEventLoop.AllEvents, 0.00000001)
    #time.sleep(.005)

    t = QTime.currentTime().addMSecs(ms)
    while QTime.currentTime() < t:
        QCoreApplication.processEvents(QEventLoop.AllEvents, 1)


def find_x(ed):
    x_max = None
    x_min = None
    for i in range(len(ed)):
        if x_max is None or ed[i][0] > x_max:
            x_max = ed[i][0]

        if x_max is None or ed[i][2] > x_max:
            x_max = ed[i][2]

        if x_min is None or ed[i][0] < x_min:
            x_min = ed[i][0]

        if x_min is None or ed[i][2] < x_min:
            x_min = ed[i][2]

    return x_max, x_min

def find_y(ed):
    y_max = None
    y_min = None
    for i in range(len(ed)):
        if y_max is None or ed[i][1] > y_max:
            y_max = ed[i][1]

        if y_max is None or ed[i][3] > y_max:
            y_max = ed[i][3]

        if y_min is None or ed[i][1] < y_min:
            y_min = ed[i][1]

        if y_min is None or ed[i][3] < y_min:
            y_min = ed[i][3]

    return y_max, y_min

def Check_changing(x,y,edges,flag_2):
	count_r = 0
	count_l = 0
	x -= 1
	for ed in edges:
		if (ed[0] > x or ed[2] > x):
			if ((ed[1] >= y and ed[3] <= y) or (ed[1] <= y and ed[3] >= y)): 
				if ( ( (ed[0] - x)*(ed[1] - ed[3]) - (ed[0] - ed[2]) * (ed[1] - y) ) > 0):
					count_r += 1
		if (ed[0] < x or ed[2] < x):
			if ((ed[1] >= y and ed[3] <= y) or (ed[1] <= y and ed[3] >= y)): 
				if ( ( (ed[0] - x)*(ed[1] - ed[3]) - (ed[0] - ed[2]) * (ed[1] - y) ) <= 0):
					count_l += 1
	
	return flag

def mark_points(win):
	pix = QPixmap()
	p = QPainter()
	for ed in win.edges:
		p.begin(win.image)
		if (ed[3] == ed[1]):
			continue

		if (ed[3] > ed[1]):
			y_max = ed[3]
			y_min = ed[1]
		else:
			y_max = ed[1]
			y_min = ed[3]

		dx = ed[2] - ed[0]
		dy = ed[3] - ed[1]

		y = int(y_min)
		
		while y < y_max:
			x = dx / dy * (y - ed[1]) + ed[0]
			col = QColor(win.image.pixel(int(x) + 1, int(y)))
			p.setPen(QPen(col_mark))
			if (col == col_mark):
				p.drawPoint(int(x) + 2, int(y))
			else:
				p.drawPoint(int(x) + 1, int(y))
			y += 1
		pix.convertFromImage(win.image)
		win.scene.addPixmap(pix)
		p.end()


def fill_xor(win):
    #draw_lines(win.image, win.edges)
    #draw_edges(win.image, win.edges)
    pix = QPixmap()
    p = QPainter()
    if len(win.edges) == 0:
        box.showerror(title = "Ошибка закраски", message = "Ребра фигуры отсутствуют! Пожалуйста, введите хотя бы 2 ребра и замкните их.")
        return
    if len(win.edges) < 3 and len(win.edges) > 0:
        box.showerror(title = "Ошибка закраски", message = "Нехватка ребер! Пожалуйста, введите больше ребер для закраски и замкинете фигуру")
        return

    ms = win.ms_del.value()

    mark_points(win)
    x_max, x_min = find_x(win.edges)
    y_max, y_min = find_y(win.edges)

    x_max = int(x_max)
    x_min = int(x_min)
    y_max = int(y_max)
    y_min = int(y_min)

    flag = False
    flag_2 = False
    flag_3 = False

    beg = process_time()

    for y in range(y_max - 1, y_min, -1):
        p.begin(win.image)
        flag = False
        for x in range(x_min, x_max):
            col = QColor(win.image.pixel(int(x), int(y)))

            if (col == col_mark):
            	flag = not flag
                #flag = Check_changing(x,y,win.edges,flag)

            if (flag == True):
                p.setPen(QPen(col_fill))
            else:
                p.setPen(QPen(col_zero))

            p.drawPoint(int(x), int(y))
        if win.delay.isChecked():
            delay(ms)
            pix.convertFromImage(win.image)
            win.scene.addPixmap(pix)
        if not win.delay.isChecked():
            pix.convertFromImage(win.image)
            win.scene.addPixmap(pix)
        p.end()
    draw_edges(win.image, win.edges)
    end = process_time() - beg

    if win.timer.isChecked():
        box.showinfo(title="Время закраски",
                      message="Время закраски фигуры: " + str(end))
    win.table.clear()
    win.edges = []
    w.point_now = None
    w.point_lock = None
    r = win.table.rowCount()
    for i in range(r, -1, -1):
        win.table.removeRow(i)

def add_point_by_btn(win):
    x = win.x.value()
    y = win.y.value()
    p = QPoint()
    p.setX(x)
    p.setY(y)
    add_point(p)

if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    w = Window()
    w.show()
    sys.exit(app.exec_())
