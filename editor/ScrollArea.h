#ifndef SCROLLAREA_H
#define SCROLLAREA_H

#include <QScrollArea> 

class SuspendedScrollBar;

class ScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    explicit ScrollArea(QWidget * parent = 0);
    ~ScrollArea(){}
    void init();
protected:
	void resizeEvent(QResizeEvent* e) override;
	void enterEvent(QEvent* e) override;
	void leaveEvent(QEvent* e) override;
public slots:
    void sltValueChangeWidget(int value);
private:
    SuspendedScrollBar * m_pVertScrollBar;
};

#endif // SCROLLAREA_H