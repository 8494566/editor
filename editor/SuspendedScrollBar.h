#ifndef SUSPENDEDSCROLLBAR_H
#define SUSPENDEDSCROLLBAR_H

#include <QScrollBar> 


class SuspendedScrollBar : public QScrollBar
{
    Q_OBJECT
public:
    explicit SuspendedScrollBar(Qt::Orientation t , QWidget * parent = 0);
    ~SuspendedScrollBar(){}
public slots:
    void sltValueChangeScrollBar(int);//当使用该组件的控件的滚动条发出valueChanged信号时，该信号被触发
    void sltRangeChanged(int min,int max);//当使用该组件的控件的滚动条发出rangeChanged信号时，该信号被触发
 
};

#endif // SUSPENDEDSCROLLBAR_H