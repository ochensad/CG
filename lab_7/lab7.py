from PyQt5 import QtWidgets, uic
from PyQt5.QtWidgets import QTableWidgetItem, QMessageBox
from PyQt5.QtGui import QPen, QColor, QImage, QPixmap, QPainter, QTransform
from PyQt5.QtCore import Qt, QTime, QCoreApplication, QEventLoop, QPoint, QPointF
import time

red = Qt.red
blue = Qt.blue
now = None

class Window(QtWidgets.QMainWindow):
    def __init__(self):
        QtWidgets.QWidget.__init__(self)
        uic.loadUi("window.ui", self)
        self.scene = Scene(0, 0, 1200, 800)
        self.scene.win = self
        self.view.setScene(self.scene)
        self.image = QImage(1200, 800, QImage.Format_ARGB32_Premultiplied)
        self.image.fill(Qt.white)
        self.bars.clicked.connect(lambda : set_bars(self))
        self.erase.clicked.connect(lambda: clean_all(self))
        self.paint.clicked.connect(lambda: clipping(self))
        self.rect.clicked.connect(lambda: set_rect(self))

        self.ect.clicked.connect(lambda: add_bars(self))
        self.lines = []
        self.clip = None
        self.point_now = None
        self.input_bars = False
        self.input_rect = False
        self.pen = QPen(red)
        self.check.setChecked(False)
        self.horiz.setChecked(False)
        self.vertic.setChecked(False)
        self.check_o.setChecked(False)




class Scene(QtWidgets.QGraphicsScene):

    def mousePressEvent(self, event):
        add_point(event.scenePos())

    def mouseMoveEvent(self, event):
        global now, w
        if w.check.isChecked() == True:
            xn = w.x_n.value()
            yn = w.y_n.value()
            xk = w.x_k.value()
            yk = w.y_k.value()
            self.addRect(xn, yn, xk, yk)
            now = QPointF(xn, yn)
            p = QPointF(xk, yk)

        elif w.input_rect:
            if now is None:
                now = event.scenePos()
            else:
                self.removeItem(self.itemAt(now, QTransform()))
                p = event.scenePos()
                print(p)
                self.addRect(now.x(), now.y(), abs(now.x() - p.x()), abs(now.y() - p.y()))
                w.x_n.setValue(int(now.x()))
                w.y_n.setValue(int(now.y()))
                w.x_k.setValue(int(abs(p.x())))
                w.y_k.setValue(int(abs(p.y())))



def set_bars(win):
    if win.input_bars:
        win.input_bars = False
        win.rect.setDisabled(False)
        win.erase.setDisabled(False)
        win.paint.setDisabled(False)
        win.ect.setDisabled(False)
    else:
        win.input_bars = True
        win.rect.setDisabled(True)
        win.erase.setDisabled(True)
        win.paint.setDisabled(True)
        win.ect.setDisabled(True)


def set_rect(win):
    if win.input_rect:
        win.input_rect = False
        win.bars.setDisabled(False)
        win.erase.setDisabled(False)
        win.paint.setDisabled(False)
        win.ect.setDisabled(False)
    else:
        win.input_rect = True
        win.bars.setDisabled(True)
        win.erase.setDisabled(True)
        win.paint.setDisabled(True)
        win.ect.setDisabled(True)


def add_row(win):
    win.table.insertRow(win.table.rowCount())


def add_point(point):
    global w
    if w.check_o.isChecked() == True:
        xn = w.xn.value()
        yn = w.yn.value()
        xk = w.xk.value()
        yk = w.yk.value()
        w.point_now = QPointF(xn, yn)
        point = QPointF(xk, yk)
        w.lines.append([[w.point_now.x(), w.point_now.y()],
                        [point.x(), point.y()]])

        add_row(w)
        i = w.table.rowCount() - 1
        item_b = QTableWidgetItem("[{0}, {1}]".format(w.point_now.x(), w.point_now.y()))
        item_e = QTableWidgetItem("[{0}, {1}]".format(point.x(), point.y()))
        w.table.setItem(i, 0, item_b)
        w.table.setItem(i, 1, item_e)
        w.scene.addLine(w.point_now.x(), w.point_now.y(), point.x(), point.y(), w.pen)
        w.point_now = None
    elif w.input_bars:
        if w.point_now is None:
            w.point_now = point



        elif w.vertic.isChecked() == True:
            w.lines.append([[w.point_now.x(), w.point_now.y()],
                            [w.point_now.x(), point.y()]])
            w.xn.setValue(w.point_now.x())
            w.yn.setValue(w.point_now.y())
            w.xk.setValue(w.point_now.x())
            w.yk.setValue(point.y())

            add_row(w)
            i = w.table.rowCount() - 1
            item_b = QTableWidgetItem("[{0}, {1}]".format(w.point_now.x(), w.point_now.y()))
            item_e = QTableWidgetItem("[{0}, {1}]".format(w.point_now.x(), point.y()))
            w.table.setItem(i, 0, item_b)
            w.table.setItem(i, 1, item_e)
            w.scene.addLine(w.point_now.x(), w.point_now.y(), w.point_now.x(), point.y(), w.pen)
            w.point_now = None
        elif w.horiz.isChecked() == True:
            w.lines.append([[w.point_now.x(), w.point_now.y()],
                            [point.x(), w.point_now.y()]])
            w.xn.setValue(w.point_now.x())
            w.yn.setValue(w.point_now.y())
            w.xk.setValue(point.x())
            w.yk.setValue(w.point_now.y())
            add_row(w)
            i = w.table.rowCount() - 1
            item_b = QTableWidgetItem("[{0}, {1}]".format(w.point_now.x(), w.point_now.y()))
            item_e = QTableWidgetItem("[{0}, {1}]".format(point.x(), w.point_now.y()))
            w.table.setItem(i, 0, item_b)
            w.table.setItem(i, 1, item_e)
            w.scene.addLine(w.point_now.x(), w.point_now.y(), point.x(), w.point_now.y(), w.pen)
            w.point_now = None

        else:
            w.lines.append([[w.point_now.x(), w.point_now.y()],
                            [point.x(), point.y()]])
            w.xn.setValue(int(w.point_now.x()))
            w.yn.setValue(int(w.point_now.y()))
            w.xk.setValue(int(point.x()))
            w.yk.setValue(int(point.y()))

            add_row(w)
            i = w.table.rowCount() - 1
            item_b = QTableWidgetItem("[{0}, {1}]".format(w.point_now.x(), w.point_now.y()))
            item_e = QTableWidgetItem("[{0}, {1}]".format(point.x(), point.y()))
            w.table.setItem(i, 0, item_b)
            w.table.setItem(i, 1, item_e)
            w.scene.addLine(w.point_now.x(), w.point_now.y(), point.x(), point.y(), w.pen)
            w.point_now = None


def clean_all(win):
    win.scene.clear()
    win.table.clear()
    win.lines = []
    win.image.fill(Qt.white)
    r = win.table.rowCount()
    for i in range(r, -1, -1):
        win.table.removeRow(i)


def add_bars(win):
    global now
    if now is None:
        QMessageBox.warning(win, "????????????????!", "???? ???????????? ????????????????????!")
        return
    buf = win.scene.itemAt(now, QTransform())
    if buf is None:
        QMessageBox.warning(win, "????????????????!", "???? ???????????? ????????????????????!")
    else:
        buf = buf.rect()
        win.clip = [buf.left(), buf.right(), buf.top(),  buf.bottom()]

        t = abs(win.clip[2] - win.clip[3]) * 0.8
        k = abs(win.clip[0] - win.clip[1]) * 0.8
        # ???????????? ?????????????????? ??????????????
        win.pen.setColor(red)
        w.lines.append([[win.clip[0], win.clip[2] + t],  [win.clip[0], win.clip[3] - t]])
        add_row(w)
        i = w.table.rowCount() - 1
        item_b = QTableWidgetItem("[{0}, {1}]".format(win.clip[0], win.clip[2] + t))
        item_e = QTableWidgetItem("[{0}, {1}]".format(win.clip[0], win.clip[3] - t))
        w.table.setItem(i, 0, item_b)
        w.table.setItem(i, 1, item_e)
        win.scene.addLine(win.clip[0], win.clip[2] + t,  win.clip[0], win.clip[3] - t, win.pen)

        w.lines.append([[win.clip[1], win.clip[2] + t],  [win.clip[1], win.clip[3] - t]])
        add_row(w)
        i = w.table.rowCount() - 1
        item_b = QTableWidgetItem("[{0}, {1}]".format(win.clip[1], win.clip[2] + t))
        item_e = QTableWidgetItem("[{0}, {1}]".format(win.clip[1], win.clip[3] - t))
        w.table.setItem(i, 0, item_b)
        w.table.setItem(i, 1, item_e)
        win.scene.addLine(win.clip[1], win.clip[3] - t,  win.clip[1], win.clip[2] + t, win.pen)

        w.lines.append([[win.clip[0] + k, win.clip[2]], [win.clip[1] - k, win.clip[2]]])
        add_row(w)
        i = w.table.rowCount() - 1
        item_b = QTableWidgetItem("[{0}, {1}]".format(win.clip[0] + k, win.clip[2]))
        item_e = QTableWidgetItem("[{0}, {1}]".format(win.clip[1] - k, win.clip[2]))
        w.table.setItem(i, 0, item_b)
        w.table.setItem(i, 1, item_e)
        win.scene.addLine(win.clip[0] + k, win.clip[2], win.clip[1] - k, win.clip[2], win.pen)

        w.lines.append([[win.clip[0] + k, win.clip[3]], [win.clip[1] - k, win.clip[3]]])
        add_row(w)
        i = w.table.rowCount() - 1
        item_b = QTableWidgetItem("[{0}, {1}]".format(win.clip[0] + k, win.clip[3]))
        item_e = QTableWidgetItem("[{0}, {1}]".format(win.clip[1] - k, win.clip[3]))
        w.table.setItem(i, 0, item_b)
        w.table.setItem(i, 1, item_e)
        win.scene.addLine(win.clip[0] + k, win.clip[3], win.clip[1] - k, win.clip[3], win.pen)


def get_code(a, rect):
    code = [0, 0, 0, 0]
    print(rect)
    if a[0] < rect[0]:
        code[0] = 1
    if a[0] > rect[1]:
        code[1] = 1
    if a[1] < rect[2]:
        code[2] = 1
    if a[1] > rect[3]:
        code[3] = 1

    return code


def clipping(win):
    buf = win.scene.itemAt(now, QTransform()).rect()
    win.clip = [buf.left(), buf.right(), buf.top(),  buf.bottom()]
    for b in win.lines:
        pass
        win.pen.setColor(blue)
        cohen_sutherland(b, win.clip, win)
        win.pen.setColor(red)


def log_prod(code1, code2):
    p = 0
    for i in range(4):
        p += code1[i] & code2[i]

    return p


def is_visible(bar, rect):
    """?????????????????? - 0 = ??????????????????
                   1 = ??????????????
                   2 = ???????????????? ??????????????"""
    # ???????????????????? ?????????? ???????????????? ?????????? ??????????????
    s1 = sum(get_code(bar[0], rect))
    s2 = sum(get_code(bar[1], rect))


    # ??????????????????????, ?????? ?????????????? ???????????????? ??????????
    vis = 2

    # ???????????????? ???????????? ?????????????????? ??????????????
    if not s1 and not s2:
        vis = 1
    else:
        # ???????????????? ?????????????????????? ?????????????????????? ??????????????
        l = log_prod(get_code(bar[0], rect), get_code(bar[1], rect))
        if l != 0:
            vis = 0

    return vis


def cohen_sutherland(bar, rect, win):
    # ?????????????????????????? ??????????
    flag = 1 # ???????????? ??????????????????
    t = 1

    # ???????????????? ???????????????????????????? ?? ???????????????????????????????? ??????????????
    if bar[1][0] - bar[0][0] == 0:
        flag = -1   # ???????????????????????? ??????????????
    else:
        # ???????????????????? ??????????????
        t = (bar[1][1] - bar[0][1]) / (bar[1][0] - bar[0][0])
        if t == 0:
            flag = 0   # ????????????????????????????

    # ?????? ???????????? ?????????????? ????????
    for i in range(4):
        vis = is_visible(bar, rect)
        if vis == 1:
            win.scene.addLine(bar[0][0], bar[0][1], bar[1][0], bar[1][1], win.pen)
            return
        elif not vis:
            return

        # ???????????????? ?????????????????????? ?????????????? ?? ?????????????? ????????
        code1 = get_code(bar[0], rect)
        code2 = get_code(bar[1], rect)

        if code1[i] == code2[i]:
            continue

        # ???????????????? ???????????????????? ??1 ?????? ????????; ???????? ??1 ???????????? ????????, ???? ??2 ?? ??1 ???????????????? ??????????????
        if not code1[i]:
            bar[0], bar[1] = bar[1], bar[0]

        # ?????????? ?????????????????????? ?????????????? ???? ?????????????????? ????????
        # ???????????????? ???????????????????????????? ??????????????
        if flag != -1:
            if i < 2:
                bar[0][1] = t * (rect[i] - bar[0][0]) + bar[0][1]
                print(bar[0][1])
                bar[0][0] = rect[i]
                continue
            else:
                bar[0][0] = (1 / t) * (rect[i] - bar[0][1]) + bar[0][0]

        bar[0][1] = rect[i]
    win.scene.addLine(bar[0][0], bar[0][1], bar[1][0], bar[1][1], win.pen)

if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    w = Window()
    w.show()
    sys.exit(app.exec_())
