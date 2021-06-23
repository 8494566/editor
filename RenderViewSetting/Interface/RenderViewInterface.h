#ifndef REDERVIEWINTERFACE_H
#define REDERVIEWINTERFACE_H
#include "LibraryManagers/Plugin/Plugin.h"


class QWidget;

class RenderViewInterface : public Plugin
{
public:
	virtual QWidget* HWNDToQWidget(void* hwnd) = 0;
	virtual void* QWidgetToHWND(QWidget* widget) = 0;
	virtual void TestCall() = 0;
};
#endif