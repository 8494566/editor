#include "ScrollArea.h"
#include "SuspendedScrollBar.h"


ScrollArea::ScrollArea(QWidget* parent /* = 0 */)
{
	init();
}

void ScrollArea::sltValueChangeWidget(int value)
{
	this->horizontalScrollBar()->setValue(value);
}

void ScrollArea::init()
{
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	m_pVertScrollBar = new SuspendedScrollBar(Qt::Horizontal, this);
	connect(this->horizontalScrollBar(), SIGNAL(valueChanged(int)), m_pVertScrollBar, SLOT(sltValueChangeScrollBar(int)));
	connect(m_pVertScrollBar, SIGNAL(valueChanged(int)), this, SLOT(sltValueChangeWidget(int)));
	connect(this->horizontalScrollBar(), SIGNAL(rangeChanged(int, int)), m_pVertScrollBar, SLOT(sltRangeChanged(int, int)));
}

void ScrollArea::resizeEvent(QResizeEvent* e)
{
	int iX = this->height() - 8;
	m_pVertScrollBar->setGeometry(1, iX, this->width() - 2, 8);
	if(!m_pVertScrollBar->maximum())
		m_pVertScrollBar->setMinimum(1);
	return QWidget::resizeEvent(e);
}

void ScrollArea::enterEvent(QEvent* e)
{
	if (m_pVertScrollBar->maximum() > 0)
		m_pVertScrollBar->show();
	return QWidget::enterEvent(e);
}

void ScrollArea::leaveEvent(QEvent* e)
{
	m_pVertScrollBar->hide();
	return QWidget::leaveEvent(e);
}
