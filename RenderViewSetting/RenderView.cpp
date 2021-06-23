#include "RenderView.h"
#include <windows.h>
#include <QtWidgets\QWidget>

QWidget* RenderView::HWNDToQWidget(void * hwnd)
{
	if (hwnd == nullptr)
		return nullptr;
	m_widget = QWidget::find((WId)hwnd);
	m_hwnd = hwnd;
	return m_widget;
}

void * RenderView::QWidgetToHWND(QWidget* widget)
{
	if (widget == nullptr)
		return nullptr;
	m_hwnd = (HWND)widget->winId();
	m_widget = widget;
	return m_hwnd;
}

void RenderView::TestCall()
{
	if (m_hwnd == nullptr)
		return;
	//1.获取窗口句柄
	HWND hwnd((HWND)m_hwnd);

	//2.获取DC.
	HDC hdc = ::GetDC(hwnd);

	//3.创建图形对象.
	HPEN hPen = CreatePen(PS_SOLID, 10, RGB(0xFF, 0, 0)); //设置为红色画笔
	HBRUSH hBru = (HBRUSH)::GetStockObject(DC_BRUSH);
	//4.关联图形对象跟DC
	HPEN oldPen = (HPEN)::SelectObject(hdc, hPen); //返回旧的画笔
	SetDCBrushColor(hdc, RGB(0x54, 0x54, 0x54)); //设置画刷颜色
	HBRUSH oldBrush = (HBRUSH)::SelectObject(hdc, hBru);
	//5.绘制句柄
	Rectangle(hdc, 0, 0, m_widget->width(), m_widget->height());

	//6.释放资源.
	::SelectObject(hdc, oldPen); //首先还原旧画笔
	DeleteObject(hPen);          //删除图形对象.
	ReleaseDC(hwnd, hdc);              //释放Dc
}
