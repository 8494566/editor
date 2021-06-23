#include "TreeWidget.h"
#include <QMenu>
#include <QApplication>
#include <QFileDialog>
#include <QDrag>
#include <QMimeData>
#include <QContextMenuEvent>
#include <QMessageBox>
#include <QHeaderView>

TreeWidget::TreeWidget(QWidget* parent)
{
	init();
}

TreeWidget::~TreeWidget()
{
}

void TreeWidget::init()
{
	header()->setVisible(false);
	//setHeaderLabel(u8"");
	setSelectionMode(QAbstractItemView::ExtendedSelection);
	QTreeWidgetItem* rootItem = new QTreeWidgetItem(this, QStringList(u8"模型文件"));
	QFont font(u8"微软雅黑", 12, QFont::Bold);
	rootItem->setFont(0, font);
	rootItem->setForeground(0, QBrush(QColor("#BBBBBB")));
	//rootItem->setData(0, Qt::UserRole, rootItem);

}

void TreeWidget::contextMenuEvent(QContextMenuEvent* ev)
{
	const QPoint& p = ev->pos();
	QTreeWidgetItem* curItem = itemAt(p);
	QMenu rightMenu;
	QAction importAction(u8"导入");
	connect(&importAction, SIGNAL(triggered()), this, SLOT(onAddItem()));
	QAction appendAction(u8"添加");
	connect(&appendAction, SIGNAL(triggered()), this, SLOT(onAppendItem()));
	QAction exportAction(u8"导出");
	connect(&exportAction, SIGNAL(triggered()), this, SLOT(onExportItem()));
	QAction renameAction(u8"重命名");
	connect(&renameAction, SIGNAL(triggered()), this, SLOT(onRenameItem()));
	QAction delteAction(u8"移除");
	connect(&delteAction, SIGNAL(triggered()), this, SLOT(onDeleteItem()));
	QAction locateAction(u8"转到");
	connect(&locateAction, SIGNAL(triggered()), this, SLOT(onLocateItem()));

	rightMenu.exec(QCursor::pos());
}

void TreeWidget::mousePressEvent(QMouseEvent* ev)
{
}

void TreeWidget::mouseMoveEvent(QMouseEvent* ev)
{
}

void TreeWidget::mouseDoubleClickEvent(QMouseEvent* ev)
{
}
