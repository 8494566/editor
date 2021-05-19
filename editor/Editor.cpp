#include "Editor.h"
#include <QtWidgets/QLabel>

Editor::Editor(QWidget *parent)
    : QMainWindow(parent)
{
	ui.setupUi(this);
	tabifyDockWidget(ui.headDock, ui.dockWidget);
	tabifyDockWidget(ui.headDock, ui.dockWidget_2);
	ui.headDock->raise();

	setBearingNetworkButton();
	setToolButton();
}

void Editor::setPonstStyleSheet(QWidget* widgrtPtr, const char* tpyeName, const int iconPonstRow, const int iconPonstRank)
{
	if (!widgrtPtr)
		return;

	QString string = widgrtPtr->styleSheet();
	widgrtPtr->setStyleSheet(QString("%5{border-image:url("":/Editor/img/RCDATA_32.png"") %1 %2 %3 %4 0;}").arg((iconPonstRow - 1) * 32).arg(640 - (iconPonstRank * 32)).arg(1792 - (32 * iconPonstRow)).arg((iconPonstRank - 1) * 32).arg(tpyeName) + string);
}

void Editor::setButton(QAbstractButton* buttonPtr, const int iconPonstRow, const int iconPonstRank, const char* buttonText)
{
	if (!buttonPtr)
		return;

	QLabel* iconLabel = new QLabel;
	QLabel* textLabel = new QLabel;

	iconLabel->setFixedSize(32, 32);
	setPonstStyleSheet(iconLabel, "QLabel", iconPonstRow, iconPonstRank);
	textLabel->setText(QString::fromLocal8Bit(buttonText));
	// new一个V布局，若想左右放图片和文本，将QVBoxLayout改为QHBoxLayout即可
	QVBoxLayout* myLayout = new QVBoxLayout();
	myLayout->addSpacing(0);
	myLayout->addWidget(iconLabel, 0, Qt::AlignHCenter);
	myLayout->addSpacing(0);
	myLayout->addWidget(textLabel, 0, Qt::AlignHCenter);
	myLayout->addStretch();
	buttonPtr->setLayout(myLayout);
	buttonPtr->setStyleSheet("QPushButton{border-image: url("":/Editor/img/RCDATA_32.png"") 608 0 1152 608 0;}"
		"QPushButton:hover{background-color:rgb(204 ,255 ,255);}"
		"QPushButton:pressed{background-color:rgb(0 ,255 ,255);padding-left:3px;padding-top:3px;}");
}

void Editor::setBearingNetworkButton()
{
	setButton(ui.pushButton_1, 3, 3, "节点");
	setButton(ui.pushButton_2, 1, 16, "直线");
	setButton(ui.pushButton_3, 1, 16, "两点直线");
	setButton(ui.pushButton_4, 6, 7, "平行直线");
	setButton(ui.pushButton_5, 3, 2, "辐射线");
	setButton(ui.pushButton_6, 1, 17, "圆弧");
	setButton(ui.pushButton_7, 2, 8, "折线");
	setButton(ui.pushButton_8, 3, 18, "矩形");
	setButton(ui.pushButton_9, 2, 11, "园");
	setButton(ui.pushButton_10, 5, 5, "正交网络");
	setButton(ui.pushButton_11, 5, 6, "圆弧网络");
	setButton(ui.pushButton_12, 30, 4, "导入DWG");
	setButton(ui.pushButton_13, 5, 7, "命名");
	setButton(ui.pushButton_14, 7, 19, "轴线显示");
	setButton(ui.pushButton_15, 6, 18, "点高");
	setButton(ui.pushButton_16, 6, 18, "节点下传");
	setButton(ui.pushButton_17, 5, 8, "清理网点");
	setButton(ui.pushButton_18, 3, 17, "节点归并");
	setButton(ui.pushButton_19, 5, 4, "形成网点");
}

void Editor::setToolButton()
{
	setPonstStyleSheet(ui.toolbarButton_1, "QPushButton", 39, 2);
	setPonstStyleSheet(ui.toolbarButton_2, "QPushButton", 39, 1);
	setPonstStyleSheet(ui.toolbarButton_3, "QPushButton", 28, 15);
	setPonstStyleSheet(ui.toolbarButton_4, "QPushButton", 7, 2);
	setPonstStyleSheet(ui.toolbarButton_5, "QPushButton", 7, 4);
	setPonstStyleSheet(ui.toolbarButton_6, "QPushButton", 7, 6);
	setPonstStyleSheet(ui.toolbarButton_7, "QPushButton", 15, 1);
	setPonstStyleSheet(ui.toolbarButton_8, "QPushButton", 7, 12);
	setPonstStyleSheet(ui.toolbarButton_9, "QPushButton", 19, 2);
	setPonstStyleSheet(ui.toolbarButton_10, "QPushButton", 18, 20);
	setPonstStyleSheet(ui.toolbarButton_11, "QPushButton", 19, 3);
	setPonstStyleSheet(ui.toolbarButton_12, "QPushButton", 7, 13);
	setPonstStyleSheet(ui.toolbarButton_13, "QPushButton", 6, 10);
	setPonstStyleSheet(ui.toolbarButton_14, "QPushButton", 30, 9);
	setPonstStyleSheet(ui.toolbarButton_15, "QPushButton", 30, 10);
	setPonstStyleSheet(ui.toolbarButton_16, "QPushButton", 30, 14);
	setPonstStyleSheet(ui.toolbarButton_17, "QPushButton", 30, 15);
	setPonstStyleSheet(ui.toolbarButton_18, "QPushButton", 30, 20);
	setPonstStyleSheet(ui.toolbarButton_19, "QPushButton", 15, 11);
	setPonstStyleSheet(ui.toolbarButton_20, "QPushButton", 15, 13);
	setPonstStyleSheet(ui.toolbarButton_21, "QPushButton", 14, 3);
	setPonstStyleSheet(ui.toolbarButton_22, "QPushButton", 36, 11);
	setPonstStyleSheet(ui.toolbarButton_23, "QPushButton", 36, 14);
	setPonstStyleSheet(ui.toolbarButton_24, "QPushButton", 5, 17);
	setPonstStyleSheet(ui.toolbarButton_25, "QPushButton", 16, 15);
	setPonstStyleSheet(ui.toolbarButton_26, "QPushButton", 16, 1);
	setPonstStyleSheet(ui.toolbarButton_27, "QPushButton", 14, 18);
	setPonstStyleSheet(ui.toolbarButton_28, "QPushButton", 12, 5);
	setPonstStyleSheet(ui.toolbarButton_29, "QPushButton", 18, 5);
	setPonstStyleSheet(ui.toolbarButton_30, "QPushButton", 28, 16);
	setPonstStyleSheet(ui.toolbarButton_31, "QPushButton", 17, 4);
	setPonstStyleSheet(ui.toolbarButton_32, "QPushButton", 15, 8);
	setPonstStyleSheet(ui.toolbarButton_33, "QPushButton", 15, 10);
	setPonstStyleSheet(ui.toolbarButton_34, "QPushButton", 15, 9);
	setPonstStyleSheet(ui.toolbarButton_35, "QPushButton", 29, 10);
	setPonstStyleSheet(ui.toolbarButton_36, "QPushButton", 38, 18);
	setPonstStyleSheet(ui.toolbarButton_37, "QPushButton", 7, 13);
}
