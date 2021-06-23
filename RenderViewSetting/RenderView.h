#ifndef REDERVIEW_H
#define REDERVIEW_H
#include "Interface/RenderViewInterface.h"

class QWidget;

class RenderView : public RenderViewInterface
{
public:
	virtual QWidget* HWNDToQWidget(void *  hwnd);
	virtual void* QWidgetToHWND(QWidget* widget);
	virtual void TestCall();
private:
	void* m_hwnd{ nullptr };
	QWidget* m_widget{ nullptr };
};
#endif