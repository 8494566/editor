#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QTreeWidget> 

class TreeWidget : public QTreeWidget
{
    Q_OBJECT

public:
    explicit TreeWidget(QWidget *parent = Q_NULLPTR);
	~TreeWidget();
public:
    void init();

protected:
	void contextMenuEvent(QContextMenuEvent* ev) override;
	void mousePressEvent(QMouseEvent* ev) override;
	void mouseMoveEvent(QMouseEvent* ev) override;
	void mouseDoubleClickEvent(QMouseEvent* ev) override;
};

#endif // TREEWIDGET_H