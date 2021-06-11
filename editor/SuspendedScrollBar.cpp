#include "SuspendedScrollBar.h"
#include <QFile>

SuspendedScrollBar::SuspendedScrollBar(Qt::Orientation t ,  QWidget *parent) : QScrollBar(parent){
 
	this->setOrientation(t);

	QFile styleFile(u8"./scrollbar-horizontal.qss");//路径名
	if (styleFile.open(QFile::ReadOnly)) {
		QString style(styleFile.readAll());
		this->setStyleSheet(style);
	}

	this->setRange(0, 0);
	this->hide();
}
 
void SuspendedScrollBar::sltRangeChanged(int min,int max){
    this->setMinimum(min);
    this->setRange(0 , max);
    this->setPageStep(0.75 * (this->width() + max));
    if(max <= 0)
        this->hide();
}

void SuspendedScrollBar::sltValueChangeScrollBar(int value)
{ 
    this->setValue(value); 
}