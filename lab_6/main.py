from PyQt5 import QtWidgets, uic, QtTest
from PyQt5.QtWidgets import QTableWidgetItem
from PyQt5.QtGui import QPen, QColor, QImage, QPixmap, QPainter
from PyQt5.QtCore import Qt, QTime, QCoreApplication, QEventLoop, QPointF
import time

from time import process_time
import tkinter.messagebox as box

col_one = Qt.black
col_zero = Qt.white
global col_fill
col_fill = Qt.red
point_zat = False
fill = QColor(255, 0, 0).rgb()


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
        self.paint.clicked.connect(lambda: fill_seed(self))
        self.addpoint.clicked.connect(lambda: add_point_by_btn(self))
        self.pixel_z.clicked.connect(lambda: set_seed_pix(self))
        self.addpoint_2.clicked.connect(lambda: set_color1())
        self.addpoint_3.clicked.connect(lambda: set_color2())
        self.addpoint_4.clicked.connect(lambda: set_color3())
        self.addpoint_5.clicked.connect(lambda: set_color4())
        self.addpoint_6.clicked.connect(lambda: set_color5())
        self.addpoint_7.clicked.connect(lambda: set_color6())
        self.addpoint_8.clicked.connect(lambda: set_color7())
        self.addpoint_9.clicked.connect(lambda: set_color8())
        self.addpoint_10.clicked.connect(lambda: set_color9())
        self.addpoint_11.clicked.connect(lambda: set_color10())
        self.addpoint_12.clicked.connect(lambda: set_color11())
        self.addpoint_13.clicked.connect(lambda: set_color12())
        self.edges = []

        self.point_now = None
        self.point_lock = None
        self.check_draw = False
        self.pen = QPen(col_one)
        self.delay.setChecked(False)
        self.horiz.setChecked(False)
        self.vertic.setChecked(False)
        self.timer.setChecked(False)

def set_color1():
    global fill
    fill = QColor(255, 0, 0).rgb()

def set_color2():
    global fill
    fill = QColor(255, 255, 0).rgb()

def set_color3():
    global fill
    fill = QColor(0, 170, 0).rgb()

def set_color4():
    global fill
    fill = QColor(255, 0, 255).rgb()

def set_color5():
    global fill
    fill = QColor(24, 27, 255).rgb()

def set_color6():
    global fill
    fill = QColor(255, 255, 255).rgb()

def set_color7():
    global fill
    fill = QColor(255, 170, 0).rgb()

def set_color8():
    global fill
    fill = QColor(255, 230, 208).rgb()

def set_color9():
    global fill
    fill = QColor(125, 111, 111).rgb()

def set_color10():
    global fill
    fill = QColor(144, 250, 255).rgb()

def set_color11():
    global fill
    fill = QColor(219, 255, 135).rgb()

def set_color12():
    global fill
    fill = QColor(85, 85, 0).rgb()

def set_color13():
    global fill
    fill = QColor(148, 33, 33).rgb()



def set_seed_pix(w):
    global point_zat
    point_zat = True
    w.lock.setDisabled(True)

    w.erase.setDisabled(True)

    w.paint.setDisabled(True)
    w.addpoint.setDisabled(True)
    w.pixel_z.setDisabled(True)



class myScene(QtWidgets.QGraphicsScene):
    def mousePressEvent(self, event):
        if point_zat:
            get_pix(event.scenePos())
        else:
            add_point(event.scenePos())






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
    global point_zat
    point_zat = False
    win.check_draw = False
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


def delay(win):
    #QCoreApplication.processEvents(QEventLoop.AllEvents, 1)
    QtWidgets.QApplication.processEvents(QEventLoop.AllEvents)
    #time.sleep(.005)

def get_pix(point):
    global w
    global point_zat
    pix = QPixmap()

    w.p_x.setValue(int(point.x()))
    w.p_y.setValue(int(point.y()))
    draw_edges(w.image, w.edges)
    point_zat = False

    pix.convertFromImage(w.image)
    w.scene.addPixmap(pix)

    w.lock.setDisabled(False)
    w.erase.setDisabled(False)
    
    w.paint.setDisabled(False)
    w.addpoint.setDisabled(False)
    w.pixel_z.setDisabled(False)

def Check_point(x,y, win, edge):
	count = 0
	for i in range(y, 800):
		if (win.image.pixel(int(x), int(i)) == edge):
			count += 1
	if (count % 2 == 0):
		return False
	return True

def fill_seed(win):
    pix = QPixmap()
    paint = QPainter()
    paint.begin(win.image)
    edge = QColor(0, 0, 0).rgb()

    if len(win.edges) == 0 and win.check_draw == False:
        box.showerror(title = "Ошибка закраски", message = "Ребра фигуры отсутствуют! Пожалуйста, введите хотя бы 2 ребра и замкинете их.")
        return
    if len(win.edges) < 3 and len(win.edges) > 0 and win.check_draw == False:
        box.showerror(title = "Ошибка закраски", message = "Нехватка ребер! Пожалуйста, введите больше ребер для закраски и замкинете фигуру")
        return
    if (win.p_x.value() == 1 and win.p_y.value() == 1):
        box.showerror(title = "Ошибка закраски", message = "Не введена затравочная точка")
        return
    if (Check_point(win.p_x.value(), win.p_y.value(), win, edge) == False):
        box.showerror(title = "Ошибка закраски", message = "Затравочная точка за границей")
        return

    win.check_draw = True

    edge = QColor(0, 0, 0).rgb()
    global fill


    stack = []
    z = QPointF(win.p_x.value(), win.p_y.value())
    stack.append(z)
    beg = process_time()
    while stack:
        p = stack.pop()
        x = p.x()
        y = p.y()

        xt = p.x()
        win.image.setPixel(int(x), int(y), fill)


        x += 1
        while win.image.pixel(int(x), int(y)) != edge:
            win.image.setPixel(int(x), int(y), fill)
            x += 1

        xr = x - 1

        x = xt

        x -= 1
        while win.image.pixel(int(x), int(y)) != edge:
            win.image.setPixel(int(x), int(y), fill)
            x -= 1

        xl = x + 1
        y = y + 1
        x = xl
        for i in range(0, 2):
            x = xl
            while x <= xr:
                Fl = False
                while win.image.pixel(int(x), int(y)) != edge and win.image.pixel(int(x), int(y)) != fill and x <= xr:
                    Fl = True
                    x += 1
                if Fl:
                	x -= 1
                	stack.append(QPointF(int(x), int(y)))
                	x += 1
                    #if x == xr and win.image.pixel(x, y) != fill and win.image.pixel(x, y) != edge:
                        #stack.append(QPointF(x, y))
                    #else:
                        #stack.append(QPointF(x - 1, y))
                    #Fl = 0

               # xt = x
                while (win.image.pixel(int(x), int(y)) == edge or win.image.pixel(int(x), int(y)) == fill) and x <= xr:
                    x += 1
                #if x == xt:
                    #x = x + 1
            y -= 2

        if win.delay.isChecked():
            delay(win)
            pix.convertFromImage(win.image)
            win.scene.addPixmap(pix)

        if not win.delay.isChecked():
            pix.convertFromImage(win.image)
            win.scene.addPixmap(pix)
    end = process_time() - beg

    if win.timer.isChecked():
        box.showinfo(title="Время закраски",
                      message="Время закраски фигуры: " + str(end))
    win.table.clear()
    win.edges = []
    w.point_now = None
    global point_zat
    point_zat = False
    w.point_lock = None
    r = win.table.rowCount()
    for i in range(r, -1, -1):
        win.table.removeRow(i)

def add_point_by_btn(win):
    x = win.x.value()
    y = win.y.value()
    p = QPointF()
    p.setX(x)
    p.setY(y)
    add_point(p)

if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    w = Window()
    w.show()
    sys.exit(app.exec_())


