#ifndef RAWBMPWIDGET_H
#define RAWBMPWIDGET_H

#include <QWidget>
#include <QLabel>

#include "raw_bmp.h"

class ImageWidget : public QWidget
{
    Q_OBJECT
public:
    ImageWidget(QWidget *parent);
    ~ImageWidget();
    int updateImage(QImage *img);

    int setMouseDrag(int x, int y, int w, int h);
    int setMouseClick(int x, int y);

signals:
    void sendMouseClick(int x, int y);
    void sendMouseDrag(int xl, int yt, int w, int h);

protected:
    void mousePressEvent(QMouseEvent *me);
    void mouseReleaseEvent(QMouseEvent *me);
    void mouseMoveEvent(QMouseEvent *me);
    void paintEvent(QPaintEvent *event);

private:
    int x_pressed, y_pressed, x_dragging, y_dragging;

    QImage *img;

    bool isDragging;
    bool isClicked;

};

class RawBmpWidget : public QWidget
{
    Q_OBJECT
public:
    RawBmpWidget(QWidget *parent = 0);
    ~RawBmpWidget();
    int open(string path);

protected:
    ImageWidget *iwImage;
    int setInfoClickI16(int x, int y);
    int setInfoDragI16(int x, int y, int w, int h);
    int cvt_rgb_to_bgr(uint8_t *data, int W, int H);
    int mapW, mapH;
    color_map_t cmap;
    raw_bmp_type_t type;
    void *buf;

protected:
    QLabel *lbInfo1, *lbInfo2;

signals:
//    void mouseClick(int x, int y, MapType mapType);
//    void mouseDrag(int x, int y, int w, int h, MapType mapType);

protected slots:
    void onIWMouseClick(int x, int y);
    void onIWMouseDrag(int x, int y, int w, int h);

};

#endif // RAWBMPWIDGET_H
