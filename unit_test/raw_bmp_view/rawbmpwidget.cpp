#include "rawbmpwidget.h"

#include <QVBoxLayout>
#include <QPainter>
#include <QMouseEvent>

#include <limits.h>

#include "raw_bmp.h"

ImageWidget::ImageWidget(QWidget *parent)
    :QWidget(parent)
{
    img = NULL;
    isDragging = false;
    isClicked = false;

}

ImageWidget::~ImageWidget()
{

}

int ImageWidget::updateImage(QImage *img)
{
    this->img = img;
    setMinimumSize((float)img->width(), (float)img->height());
    return 0;
}

int ImageWidget::setMouseDrag(int x, int y, int w, int h)
{
    x_pressed = x;
    y_pressed = y;
    x_dragging = x+w;
    y_dragging = y+h;
    this->isClicked = false;
    this->isDragging = true;
    update();
    return 0;
}

int ImageWidget::setMouseClick(int x, int y)
{
    x_pressed = x;
    y_pressed = y;
    this->isClicked = true;
    this->isDragging = false;
    update();
    return 0;
}

void ImageWidget::paintEvent(QPaintEvent *event)
{
    if(NULL == img)
        return;

    QPainter painter(this);
    painter.drawImage(0, 0, *img);

    QColor color = QColor(200, 0, 200);

    painter.setPen(color);
    if(isDragging)
    {
        // Draw dragging rectangle.
        int xl = qMin(x_dragging, x_pressed);
        int yt = qMin(y_dragging, y_pressed);
        int w = qAbs(x_dragging - x_pressed);
        int h = qAbs(y_dragging - y_pressed);
        painter.drawRect(xl, yt, w, h);
    }

    if(isClicked)
    {
        int r=2,w=1;
        QBrush brush(color);
        painter.setPen(QPen(brush, w) );
        painter.drawLine(x_pressed-r,y_pressed, x_pressed+r, y_pressed);
        painter.drawLine(x_pressed,y_pressed-r, x_pressed, y_pressed+r);
    }

}

void ImageWidget::mousePressEvent(QMouseEvent *me)
{
    if(NULL == img)
        return;

    x_pressed = me->x();
    y_pressed = me->y();
//    is_pressed = true;
}

void ImageWidget::mouseMoveEvent(QMouseEvent *me)
{
    if(NULL == img)
        return;

    x_dragging = me->x();
    y_dragging = me->y();
    isDragging = true;
    isClicked = false;
    update();
}

void ImageWidget::mouseReleaseEvent(QMouseEvent *me)
{
    if(NULL == img)
        return;

    if(me->x() == x_pressed && me->y() == y_pressed)
    {
//        sendMouseClick(x_pressed, y_pressed);
        isClicked = true;
        update();
        emit sendMouseClick(x_pressed, y_pressed);
    }
    else
    {
        int xl = qMin(me->x(), x_pressed);
        int yt = qMin(me->y(), y_pressed);
        int w = qAbs(me->x()-x_pressed);
        int h = qAbs(me->y()-y_pressed);
        isClicked = false;
        emit sendMouseDrag(xl, yt, w, h);
    }
    isDragging = false;
}

RawBmpWidget::RawBmpWidget(QWidget *parent)
    :QWidget(parent)
{
//    this->leftOrRight = leftOrRight;
    iwImage = new ImageWidget(this);
//    ivImage->setAlignment(Qt::AlignCenter);
    lbInfo1 = new QLabel("none", this);
    lbInfo2 = new QLabel("none", this);
    QVBoxLayout *lytMain = new QVBoxLayout(this);

    lytMain->addWidget(iwImage, 1);
    lytMain->addWidget(lbInfo1, 1);
    lytMain->addWidget(lbInfo2, 1);
    lytMain->addStretch(999);

    connect(iwImage, SIGNAL(sendMouseClick(int,int)), this,
            SLOT(onIWMouseClick(int,int)));
    connect(iwImage, SIGNAL(sendMouseDrag(int,int,int,int)), this,
            SLOT(onIWMouseDrag(int,int,int,int)));
}

RawBmpWidget::~RawBmpWidget()
{

}

int RawBmpWidget::open(string path)
{
    uint8_t *data_rgb;
    read_raw_bmp_file(path, &mapW, &mapH, &type, &buf, &data_rgb, &cmap);
    cvt_rgb_to_bgr(data_rgb, mapW, mapH);
    QImage *qimg_rgb = new QImage(data_rgb, mapW, mapH, QImage::Format_RGB888);
    iwImage->updateImage(qimg_rgb);
    return 0;
}

int RawBmpWidget::setInfoClickI16(int x, int y)
{
    int16_t v = ((int16_t*)buf)[y*mapW+x];
    QString info = "x:"+QString::number(x) + ", y:"+QString::number(y) +
            ", v:"+QString::number(v, 'g', 4);
    lbInfo1->setText(info);
    lbInfo2->setVisible(false);
    return 0;
}

int RawBmpWidget::setInfoDragI16(int x, int y, int w, int h)
{
    double sum = 0.0, N= 0.0, avr = 0.0;
    int16_t vmin = SHRT_MAX, vmax = SHRT_MIN;
    for(int r=y; r<y+h; r++)
    {
        for(int c=x; c<x+w; c++)
        {
            int16_t vi = ((int16_t*)buf)[r*mapW+c];

            // Invalid value.
            if((double)vi < cmap.min || (double)vi > cmap.max)
            {
                continue;
            }

            if(vi < vmin)
                vmin = vi;
            if(vi > vmax)
                vmax = vi;

            sum += (double)vi;
            N += 1.0;
        }
    }
    avr = (float)(sum/N);
//    *avr = (float)((int)(*avr*100))/100;  // set precision.


    QString  info = "xl:"+QString::number(x) + ", yt:"+QString::number(y)
            +", w:" + QString::number(w) + ", h:" + QString::number(h)
            +", xr:"+ QString::number(x+w) + ", yb:" +QString::number(y+h);
    lbInfo1->setText(info);
    info = "min:" + QString::number(vmin, 'g', 4)
            + ", max:"+QString::number(vmax, 'g', 4)
            + ", avr:"+QString::number(avr, 'g', 4);
    lbInfo2->setText(info);
    lbInfo2->setVisible(true);
    return 0;
}

int RawBmpWidget::cvt_rgb_to_bgr(uint8_t *data, int W, int H)
{
    for(int r=0; r<H; r++)
    {
        for(int c= 0; c<W; c++)
        {
            uint8_t tmp;
            tmp = data[3*(r*W+c+0)];
            data[3*(r*W+c)+0] = data[3*(r*W+c)+2];
            data[3*(r*W+c)+2] = tmp;
        }
    }
    return 0;
}

void RawBmpWidget::onIWMouseClick(int x, int y)
{

    switch(type)
    {
        case RAW_BMP_INT16 :
            setInfoClickI16(x, y);
        break;
    }
}

void RawBmpWidget::onIWMouseDrag(int x, int y, int w, int h)
{
    switch(type)
    {
        case RAW_BMP_INT16 :
            setInfoDragI16(x, y, w, h);
        break;
    }
}
