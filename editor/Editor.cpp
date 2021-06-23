#include "Editor.h"
#include <QtWidgets/QLabel>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QListView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QButtonGroup>
#include "LibraryManagers/Plugin/PluginManager.h"
#include "RenderViewSetting/Interface/RenderViewInterface.h"

#include "TreeWidget.h"
#include "ScrollArea.h"

Editor::Editor(QWidget *parent)
    : QMainWindow(parent)
{
	ui->setupUi(this);

	init();
}

Editor::~Editor()
{
	delete ui;
}

bool Editor::eventFilter(QObject* watched, QEvent* event)
{
	PluginManager* pm = PluginManager::GetPluginManager();
	RenderViewInterface* renderView = (RenderViewInterface*)pm->getPlugin("RenderViewSetting");
	renderView->TestCall();
	return QMainWindow::eventFilter(watched, event);
}

void Editor::init()
{
	//删除中央窗体
	QWidget* p = takeCentralWidget();
	if (p)
		delete p;
	//允许嵌套dock
	setDockNestingEnabled(true);
	//记录所有的dock指针

	std::vector<std::string> modelLoadInputDocksNameArr = { u8"轴承网络", u8"构件布置" , u8"楼板布置", u8"荷载输入" , u8"自定义工况", u8"楼层组装", u8"空间结构", u8"鉴定加固", u8"预制构件拆分"};
	newDockWidget(m_modelLoadInput, modelLoadInputDocksNameArr);

	std::vector<std::string> treeMoedlLoadDocksNameArr = { u8"选择", u8"工程树", u8"分组", u8"命令树" };
	newDockWidget(m_treeMoedlLoad, treeMoedlLoadDocksNameArr);

	std::vector<std::string> topStructureConstDocksNameArr = { u8"前处理及计算", u8"设计结果" , u8"弹性时程分析(新)", u8"弹性时程分析" , u8"直接积分法时程", u8"楼板及设备震动", u8"预应力", u8"工具箱"};
	newDockWidget(m_topStructureCount, topStructureConstDocksNameArr);

	std::vector<std::string> projectcCmpDocksNameArr = { u8"工程校审" };
	newDockWidget(m_projectcCmp, projectcCmpDocksNameArr);

	std::vector<std::string> cutBulkDocksNameArr = { u8"切体" };
	newDockWidget(m_cutBulk, cutBulkDocksNameArr);

	std::vector<std::string> baseDesignDocksNameArr = { u8"基础建模", u8"基础计算及结果", u8"基础施工图" };
	newDockWidget(m_baseDesign, baseDesignDocksNameArr);

	std::vector<std::string> workingPlanDocksNameArr = { u8"板施工图", u8"梁施工图", u8"柱施工图", u8"墙施工图", u8"梁柱墙施工图", u8"通用工具", u8"楼梯施工图"};
	newDockWidget(m_workingPlan, workingPlanDocksNameArr);

	std::vector<std::string> prefabricateDocksNameArr = { u8"平面图编辑", u8"预制结构设计", u8"折叠板施工图", u8"单构件详图设计"};
	newDockWidget(m_prefabricateMap, prefabricateDocksNameArr);

	std::vector<std::string> steelStructureDocksNameArr = { u8"钢结构施工图", u8"网架网壳施工图", u8"节点工具箱"};
	newDockWidget(m_steelStructure, steelStructureDocksNameArr);

	std::vector<std::string> nolinearCountDocksNameArr = { u8"动力弹塑性分析", u8"静力弹塑性分析", u8"转ABAQUS弹塑性分析"};
	newDockWidget(m_nolinearCount, nolinearCountDocksNameArr);

	std::vector<std::string> mapCompileDocksNameArr = { u8"常用", u8"输出"};
	newDockWidget(m_mapCompile, mapCompileDocksNameArr);

	std::vector<std::string> docksNameArr = { u8"图形", u8"命令", u8"工具栏" };
	newDockWidget(m_docks, docksNameArr);


	setModelLoadPonst();
	craeteToolBar();

	setBearingMeshButton();
	setComponentLayoutButton();
	setFloorLayoutButton();
	setLoadImportButton();
	setUserDefinedConditionButton();
	setFloorAssembleButton();
	setSpatialStructureButton();
	setAuthenticateReinforceButton();
	setToolbarButton();
	setCmdDockWidget();
	setSelectDockWidget();
	showGraphTest();
}

void Editor::removeAllDock()
{
	for (auto it : m_mapDocks)
	{
		removeDockWidget(it.second);
	}
}

void Editor::showDockWidget(const std::vector<QDockWidget*>& docks, const QList<int>& index)
{
	if (index.isEmpty())
	{
		for (auto it : docks)
		{
			it->show();
		}
	}
	else
	{
		foreach(int i, index) 
		{
			docks[i]->show();
		}
	}
}

void Editor::setModelLoadPonst()
{
	setDockWidgetPonst(m_modelLoadInput);

	splitDockWidget(m_mapDocks[u8"图形"], m_mapDocks[u8"选择"], Qt::Horizontal);
	splitDockWidget(m_mapDocks[u8"选择"], m_mapDocks[u8"工程树"], Qt::Vertical);
	splitDockWidget(m_mapDocks[u8"命令"], m_mapDocks[u8"工具栏"], Qt::Horizontal);

	m_mapDocks[u8"选择"]->setMaximumSize(QSize(370, 180));
	m_mapDocks[u8"图形"]->setMinimumSize(QSize(1200, 650));

	for (auto it = 2; it < m_treeMoedlLoad.size(); it++)
	{
		tabifyDockWidget(m_treeMoedlLoad[1], m_treeMoedlLoad[it]);
	}

	//m_mapDocks[u8"工具栏"]->setMinimumSize(QSize(1200, 0));

	showDockWidget(m_modelLoadInput);
	showDockWidget(m_treeMoedlLoad);
	showDockWidget(m_docks);
}

void Editor::setTopStructureCountPonst()
{
	setDockWidgetPonst(m_topStructureCount);

	showDockWidget(m_topStructureCount);
	showDockWidget(m_docks);
}

void Editor::setProjectcCmpPonst()
{
	setDockWidgetPonst(m_projectcCmp);

	showDockWidget(m_projectcCmp);
	showDockWidget(m_docks);
}

void Editor::setCutBulkPonst()
{
	setDockWidgetPonst(m_cutBulk);

	showDockWidget(m_cutBulk);
	showDockWidget(m_docks);
}

void Editor::setBaseDesignPonst()
{
	setDockWidgetPonst(m_baseDesign);

	showDockWidget(m_baseDesign);
	showDockWidget(m_docks);
}

void Editor::setWorkingPlanPonst()
{
	setDockWidgetPonst(m_workingPlan);

	showDockWidget(m_workingPlan);
	showDockWidget(m_docks);
}

void Editor::setPrefabricatePonst()
{
	setDockWidgetPonst(m_prefabricateMap);

	showDockWidget(m_prefabricateMap);
	showDockWidget(m_docks);
}

void Editor::setSteelStructurePonst()
{
	setDockWidgetPonst(m_steelStructure);

	showDockWidget(m_steelStructure);
	showDockWidget(m_docks);
}

void Editor::setNolinearCountPonst()
{
	setDockWidgetPonst(m_nolinearCount);

	showDockWidget(m_nolinearCount);
	showDockWidget(m_docks);
}

void Editor::setMapCompilePonst()
{
	setDockWidgetPonst(m_mapCompile);

	showDockWidget(m_mapCompile);
	showDockWidget(m_docks);
}

void Editor::setCmdTreeWidgetPonst()
{	
    QGridLayout* pLayout = new QGridLayout();
	
	TreeWidget* treeWidget = new TreeWidget(this);
	treeWidget->setMinimumSize(QSize(70, 50));
	pLayout->addWidget(treeWidget);

    setScrollArea(u8"命令树", pLayout);
}

void Editor::craeteToolBar()
{
	m_toolBarButtonGroup = new QButtonGroup;
	
	std::vector<std::string> toolBarNameArr = { u8"模型荷载输入", u8"上部结构计算" , u8"工程校审", u8"砌体设计", u8"基础设计" , u8"施工图设计", u8"预制构件施工图", u8"钢结构图", u8"非线性计算", u8"二维图形编辑"};
	m_toolBarButtons.resize(toolBarNameArr.size());
	for (int i = 0; i < toolBarNameArr.size();i++)
	{
		QToolButton* toolBarButton = new QToolButton(this);
		toolBarButton->setText(toolBarNameArr[i].c_str());
		toolBarButton->setCheckable(true);
		if(!i)
			toolBarButton->setChecked(true);
		m_toolBarButtons[i] = toolBarButton;
		m_toolBarButtonGroup->addButton(toolBarButton, i);
		ui->mainToolBar->addWidget(toolBarButton);
		connect(toolBarButton, SIGNAL(clicked()), this, SLOT(onClickedToolBarButtonGroup()));
	}
}

void Editor::onClickedToolBarButtonGroup()
{
	if (m_toolBarButtonState == m_toolBarButtonGroup->checkedId())
		return;
	switch (m_toolBarButtonGroup->checkedId())
	{
	case 0:
		setModelLoadPonst();
		break;
	case 1:
		setTopStructureCountPonst();
		break;
	case 2:
		setProjectcCmpPonst();
		break;
	case 3:
		setCutBulkPonst();
		break;
	case 4:
		setBaseDesignPonst();
		break;
	case 5:
		setWorkingPlanPonst();
		break;
	case 6:
		setPrefabricatePonst();
		break;
	case 7:
		setSteelStructurePonst();
		break;
	case 8:
		setNolinearCountPonst();
		break;
	case 9:
		setMapCompilePonst();
		break;
	default:
		removeAllDock();
		break;
	}
	m_toolBarButtonState = m_toolBarButtonGroup->checkedId();
}

void Editor::setPonstStyleSheet(QWidget* widgrtPtr, const char* tpyeName, const int iconPonstRow, const int iconPonstRank)
{
	if (!widgrtPtr)
		return;

	QString string = widgrtPtr->styleSheet();
	widgrtPtr->setStyleSheet(QString("%5{border-image:url("":/Editor/img/RCDATA_32.png"") %1 %2 %3 %4 0;}").arg((iconPonstRow - 1) * 32).arg(640 - (iconPonstRank * 32)).arg(1792 - (32 * iconPonstRow)).arg((iconPonstRank - 1) * 32).arg(tpyeName) + string);
}

void Editor::setButton(QAbstractButton* buttonPtr, const char* tpyeName, const int iconPonstRow, const int iconPonstRank, const char* buttonText)
{
	if (!buttonPtr)
		return;

	QLabel* iconLabel = new QLabel(this);
	QLabel* textLabel = new QLabel(this);

	iconLabel->setFixedSize(32, 32);
	setPonstStyleSheet(iconLabel, "QLabel", iconPonstRow, iconPonstRank);

	QString strElidedText = textLabel->fontMetrics().elidedText(buttonText, Qt::ElideRight, 50, Qt::TextShowMnemonic);
	//textLabel->setWordWrap(true);
	textLabel->setText(strElidedText);
	textLabel->setToolTip(buttonText);

	// new一个V布局，若想左右放图片和文本，将QVBoxLayout改为QHBoxLayout即可
	QVBoxLayout* myLayout = new QVBoxLayout(this);
	myLayout->addSpacing(0);
	myLayout->addWidget(iconLabel, 0, Qt::AlignHCenter);
	myLayout->addSpacing(0);
	myLayout->addWidget(textLabel, 0, Qt::AlignHCenter);
	myLayout->addStretch();

	buttonPtr->setLayout(myLayout);
	buttonPtr->setStyleSheet(QString("%1{border-image: url("":/Editor/img/RCDATA_32.png"") 608 0 1152 608 0;border-radius:10px;}"
		"%1:hover{background-color:rgb(204 ,255 ,255);}"
		"%1:pressed{background-color:rgb(0 ,255 ,255);padding-left:3px;padding-top:3px;}"
		"%1::menu-indicator{subcontrol-position:bottom center;}").arg(tpyeName));
}

void Editor::setDoubleMinButtonGridLayout(QGridLayout* pLayout, std::vector<QToolButton*>& buttonVector, int begin, int end, int lineFeed)
{
	for (int i = begin; i < end; i++)
	{
		buttonVector[i] = new QToolButton(this);
		buttonVector[i]->setMinimumSize(QSize(32, 32));
		buttonVector[i]->setMaximumSize(QSize(32, 32));
		buttonVector[i]->setStyleSheet("QToolButton:hover{background-color:rgb(204 ,255 ,255);border-radius:5px;}"
			"QToolButton:pressed{background-color:rgb(0 ,255 ,255);padding-left:3px; padding-top:3px;}");

		if (i > (begin + lineFeed - 1))
			pLayout->addWidget(buttonVector[i], 1, i - lineFeed, 1, 1);
		else					
			pLayout->addWidget(buttonVector[i], 0, i, 1, 1);
	}
}

void Editor::setButtonGridLayout(QGridLayout* pLayout, std::vector<QToolButton*>& buttonVector, int begin, int end)
{
	for (int i = begin; i < end; i++)
	{
		buttonVector[i] = new QToolButton(this);
		buttonVector[i]->setMinimumSize(QSize(66, 72));
		buttonVector[i]->setMaximumSize(QSize(66, 72));
		pLayout->addWidget(buttonVector[i], 0, i, 2, 1);
	}
}

void Editor::newDockWidget(std::vector<QDockWidget*>& docks, const std::vector<std::string>& dockNameArr)
{
	if (!docks.empty())
	{
		return;
	}
	docks.resize(dockNameArr.size());
	for (int i = 0; i < docks.size(); i++)
	{
		docks[i] = new QDockWidget(this);
		m_mapDocks.insert(std::pair < std::string, QDockWidget* >(dockNameArr[i], docks[i]));
		//docks[i]->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable);
		docks[i]->setWindowTitle(dockNameArr[i].c_str());
	}

}

void Editor::setDockWidgetPonst(std::vector<QDockWidget*>& docks)
{
	removeAllDock();

	addDockWidget(Qt::TopDockWidgetArea, docks[0]);
	addDockWidget(Qt::LeftDockWidgetArea, m_mapDocks[u8"图形"]);
	addDockWidget(Qt::BottomDockWidgetArea, m_mapDocks[u8"命令"]);

	for (auto it = 0; it < docks.size(); it++)
	{
		if (it != 0)
			tabifyDockWidget(docks[0], docks[it]);
		docks[it]->setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
		docks[it]->setMaximumSize(QSize(524287, 128));
		docks[it]->setMinimumSize(QSize(0, 128));
	}

	splitDockWidget(m_mapDocks[u8"命令"], m_mapDocks[u8"工具栏"], Qt::Horizontal);

	m_mapDocks[u8"图形"]->setMinimumSize(QSize(900, 650));
	//m_mapDocks[u8"工具栏"]->setMinimumSize(QSize(1200, 0));
}

void Editor::setScrollArea(const char* dockName, QLayout* layout)
{
	QWidget* newWidget = new QWidget(this);
	newWidget->setLayout(layout);

	ScrollArea* scrollArea = new ScrollArea(this);
	scrollArea->setWidget(newWidget);
	m_mapDocks[dockName]->setWidget(scrollArea);
}

void Editor::setBearingMeshButton()
{
	QGridLayout* pLayout = new QGridLayout(this);

	m_bearingMesh.resize(33);

	setButtonGridLayout(pLayout, m_bearingMesh, 0, 19);

	setButton(m_bearingMesh[0], "QToolButton", 3, 3, u8"节点");
	m_bearingMesh[0]->setPopupMode(QToolButton::InstantPopup);
	QMenu* menu = new QMenu(this);

	//menu->addAction(QApplication::style()->standardIcon(QStyle::SP_MessageBoxCritical), QString::fromLocal8Bit("节点"));
	//menu->addAction(QApplication::style()->standardIcon(QStyle::SP_MessageBoxQuestion), QString::fromLocal8Bit("定数等分"));

	// 为QToolButton设置菜单
	m_bearingMesh[0]->setMenu(menu);
	setButton(m_bearingMesh[1], "QToolButton", 1, 16, u8"直线");
	setButton(m_bearingMesh[2], "QToolButton", 1, 16, u8"两点直线");
	setButton(m_bearingMesh[3], "QToolButton", 6, 7, u8"平行直线");
	setButton(m_bearingMesh[4], "QToolButton", 3, 2, u8"辐射线");
	setButton(m_bearingMesh[5], "QToolButton", 1, 17, u8"圆弧");
	setButton(m_bearingMesh[6], "QToolButton", 2, 8, u8"折线");
	setButton(m_bearingMesh[7], "QToolButton", 3, 18, u8"矩形");
	setButton(m_bearingMesh[8], "QToolButton", 2, 11, u8"园");
	setButton(m_bearingMesh[9], "QToolButton", 5, 5, u8"正交网络");
	setButton(m_bearingMesh[10], "QToolButton", 5, 6, u8"圆弧网络");
	setButton(m_bearingMesh[11], "QToolButton", 30, 4, u8"导入DWG");
	setButton(m_bearingMesh[12], "QToolButton", 5, 7, u8"命名");
	setButton(m_bearingMesh[13], "QToolButton", 7, 19, u8"轴线显示");
	setButton(m_bearingMesh[14], "QToolButton", 6, 18, u8"点高");
	setButton(m_bearingMesh[15], "QToolButton", 6, 18, u8"节点下传");
	setButton(m_bearingMesh[16], "QToolButton", 5, 8, u8"清理网点");
	setButton(m_bearingMesh[17], "QToolButton", 3, 17, u8"节点归并");
	setButton(m_bearingMesh[18], "QToolButton", 5, 4, u8"形成网点");

	setDoubleMinButtonGridLayout(pLayout, m_bearingMesh, 19, 29, 5);

	setPonstStyleSheet(m_bearingMesh[19], "QToolButton", 7, 20);
	setPonstStyleSheet(m_bearingMesh[20], "QToolButton", 8, 1);
	setPonstStyleSheet(m_bearingMesh[21], "QToolButton", 8, 2);
	setPonstStyleSheet(m_bearingMesh[22], "QToolButton", 8, 3);
	setPonstStyleSheet(m_bearingMesh[23], "QToolButton", 8, 7);
	setPonstStyleSheet(m_bearingMesh[24], "QToolButton", 8, 4);
	setPonstStyleSheet(m_bearingMesh[25], "QToolButton", 8, 10);
	setPonstStyleSheet(m_bearingMesh[26], "QToolButton", 8, 9);
	setPonstStyleSheet(m_bearingMesh[27], "QToolButton", 30, 11);
	setPonstStyleSheet(m_bearingMesh[28], "QToolButton", 8, 6);

	setButtonGridLayout(pLayout, m_bearingMesh, 29, m_bearingMesh.size());

	setButton(m_bearingMesh[29], "QToolButton", 6, 10, u8"量测");
	setButton(m_bearingMesh[30], "QToolButton", 15, 11, u8"设置");
	setButton(m_bearingMesh[31], "QToolButton", 18, 13, u8"工程修复");
	setButton(m_bearingMesh[32], "QToolButton", 15, 20, u8"数据恢复");

	setScrollArea(u8"轴承网络", pLayout);
}

void Editor::setComponentLayoutButton()
{
	QGridLayout* pLayout = new QGridLayout(this);

	m_componentLayout.resize(39);

	setButtonGridLayout(pLayout, m_componentLayout, 0, 25);

	setButton(m_componentLayout[0], "QToolButton", 4, 5, u8"柱");
	setButton(m_componentLayout[1], "QToolButton", 4, 1, u8"梁");
	setButton(m_componentLayout[2], "QToolButton", 4, 6, u8"墙");
	setButton(m_componentLayout[3], "QToolButton", 4, 12, u8"墙洞");
	setButton(m_componentLayout[4], "QToolButton", 4, 6, "斜墙");
	setButton(m_componentLayout[5], "QToolButton", 29, 19, u8"隔墙填充墙");
	setButton(m_componentLayout[6], "QToolButton", 4, 3, u8"斜杠");
	setButton(m_componentLayout[7], "QToolButton", 4, 4, u8"次梁");
	setButton(m_componentLayout[8], "QToolButton", 29, 19, u8"绘墙线");
	setButton(m_componentLayout[9], "QToolButton", 29, 18, u8"绘梁线");
	setButton(m_componentLayout[10], "QToolButton", 25, 5, u8"斜梁");
	setButton(m_componentLayout[11], "QToolButton", 35, 14, u8"加腋");
	setButton(m_componentLayout[12], "QToolButton", 10, 9, u8"楼梯");
	setButton(m_componentLayout[13], "QToolButton", 28, 8, u8"拾取布置");
	setButton(m_componentLayout[14], "QToolButton", 34, 20, u8"定义刷");
	setButton(m_componentLayout[15], "QToolButton", 16, 4, u8"导入截面");
	setButton(m_componentLayout[16], "QToolButton", 6, 4, u8"墙洞转连梁");
	setButton(m_componentLayout[17], "QToolButton", 16, 17, u8"本层信息");
	setButton(m_componentLayout[18], "QToolButton", 23, 10, u8"材料");
	setButton(m_componentLayout[19], "QToolButton", 6, 6, u8"上下对齐");
	setButton(m_componentLayout[20], "QToolButton", 6, 4, u8"平面对齐");
	setButton(m_componentLayout[21], "QToolButton", 1, 15, u8"构件查询");
	setButton(m_componentLayout[22], "QToolButton", 38, 1, u8"超限");
	setButton(m_componentLayout[23], "QToolButton", 12, 5, u8"显示截面");
	setButton(m_componentLayout[24], "QToolButton", 25, 17, u8"替换");

	setDoubleMinButtonGridLayout(pLayout, m_componentLayout, 25, 29, 2);

	setPonstStyleSheet(m_componentLayout[25], "QToolButton", 7, 20);
	setPonstStyleSheet(m_componentLayout[26], "QToolButton", 8, 1);
	setPonstStyleSheet(m_componentLayout[27], "QToolButton", 8, 2);
	setPonstStyleSheet(m_componentLayout[28], "QToolButton", 8, 3);

	setButtonGridLayout(pLayout, m_componentLayout, 29, m_componentLayout.size());

	setButton(m_componentLayout[29], "QToolButton", 8, 7, u8"删除");
	setButton(m_componentLayout[30], "QToolButton", 18, 9, u8"单参修改");
	setButton(m_componentLayout[31], "QToolButton", 1, 12, u8"层间复制");
	setButton(m_componentLayout[32], "QToolButton", 16, 1, u8"删除准层");
	setButton(m_componentLayout[33], "QToolButton", 29, 2, u8"导到空间");
	setButton(m_componentLayout[34], "QToolButton", 14, 16, u8"漏斗");
	setButton(m_componentLayout[35], "QToolButton", 48, 3, u8"门式钢架");
	setButton(m_componentLayout[36], "QToolButton", 46, 6, u8"墙预应力钢筋");
	setButton(m_componentLayout[37], "QToolButton", 48, 10, u8"石化");
	setButton(m_componentLayout[38], "QToolButton", 32, 17, u8"基础");

	setScrollArea(u8"构件布置", pLayout);
}

void Editor::setFloorLayoutButton()
{
	QGridLayout* pLayout = new QGridLayout(this);

	m_floorLayout.resize(29);
	setButtonGridLayout(pLayout, m_floorLayout, 0, m_floorLayout.size());

	setButton(m_floorLayout[0], "QToolButton", 4, 7, u8"生成楼板");
	setButton(m_floorLayout[1], "QToolButton", 4, 10, u8"楼板错层");
	setButton(m_floorLayout[2], "QToolButton", 5, 10, u8"修改板厚");
	setButton(m_floorLayout[3], "QToolButton", 42, 11, u8"布置");
	setButton(m_floorLayout[4], "QToolButton", 5, 10, u8"修改");
	setButton(m_floorLayout[5], "QToolButton", 37, 7, u8"加腋");
	setButton(m_floorLayout[6], "QToolButton", 37, 7, u8"加腋查询");
	setButton(m_floorLayout[7], "QToolButton", 4, 11, u8"板洞布置");
	setButton(m_floorLayout[8], "QToolButton", 4, 13, u8"全房间洞");
	setButton(m_floorLayout[9], "QToolButton", 4, 11, u8"位置检查");
	setButton(m_floorLayout[10], "QToolButton", 4, 9, u8"悬挑板");
	setButton(m_floorLayout[11], "QToolButton", 42, 12, u8"预制阳台");
	setButton(m_floorLayout[12], "QToolButton", 42, 10, u8"预制空调板");
	setButton(m_floorLayout[13], "QToolButton", 4, 9, u8"挑檐");
	setButton(m_floorLayout[14], "QToolButton", 8, 7, u8"删除");
	setButton(m_floorLayout[15], "QToolButton", 1, 12, u8"层间复制");
	setButton(m_floorLayout[16], "QToolButton", 39, 11, u8"布空心板");
	setButton(m_floorLayout[17], "QToolButton", 39, 9, u8"布压形钢板");
	setButton(m_floorLayout[18], "QToolButton", 4, 8, u8"定义");
	setButton(m_floorLayout[19], "QToolButton", 4, 8, u8"布置");
	setButton(m_floorLayout[20], "QToolButton", 39, 13, u8"修改");
	setButton(m_floorLayout[21], "QToolButton", 4, 11, u8"预处理布置");
	setButton(m_floorLayout[22], "QToolButton", 23, 9, u8"叠合板统计");
	setButton(m_floorLayout[23], "QToolButton", 42, 14, u8"DWG导入");
	setButton(m_floorLayout[24], "QToolButton", 42, 5, u8"其他导入");
	setButton(m_floorLayout[25], "QToolButton", 37, 5, u8"布置柱帽");
	setButton(m_floorLayout[26], "QToolButton", 37, 5, u8"统一裁剪");
	setButton(m_floorLayout[27], "QToolButton", 37, 5, u8"自定义裁剪");
	setButton(m_floorLayout[28], "QToolButton", 1, 15, u8"楼板查询");

	setScrollArea(u8"楼板布置", pLayout);
}

void Editor::setLoadImportButton()
{
	QGridLayout* pLayout = new QGridLayout(this);

	m_loadImport.resize(29);
	setButtonGridLayout(pLayout, m_loadImport, 0, m_loadImport.size());

	setButton(m_loadImport[0], "QToolButton", 3, 19, u8"楼面恒活");
	setButton(m_loadImport[1], "QToolButton", 25, 6, u8"导荷方式");
	setButton(m_loadImport[2], "QToolButton", 4, 17, u8"楼板");
	setButton(m_loadImport[3], "QToolButton", 4, 16, u8"梁墙");
	setButton(m_loadImport[4], "QToolButton", 4, 18, u8"柱");
	setButton(m_loadImport[5], "QToolButton", 23, 1, u8"板间");
	setButton(m_loadImport[6], "QToolButton", 4, 16, u8"次梁");
	setButton(m_loadImport[7], "QToolButton", 4, 15, u8"墙洞");
	setButton(m_loadImport[8], "QToolButton", 5, 3, u8"节点");
	setButton(m_loadImport[9], "QToolButton", 7, 15, u8"恒载删除");
	setButton(m_loadImport[10], "QToolButton", 3, 19, u8"楼板");
	setButton(m_loadImport[11], "QToolButton", 9, 16, u8"房间属性");
	setButton(m_loadImport[12], "QToolButton", 6, 14, u8"梁墙");
	setButton(m_loadImport[13], "QToolButton", 6, 20, u8"柱");
	setButton(m_loadImport[14], "QToolButton", 23, 1, u8"板间");
	setButton(m_loadImport[15], "QToolButton", 7, 16, u8"墙洞");
	setButton(m_loadImport[16], "QToolButton", 3, 17, u8"节点");
	setButton(m_loadImport[17], "QToolButton", 3, 20, u8"活载删除");
	setButton(m_loadImport[18], "QToolButton", 25, 17, u8"替换");
	setButton(m_loadImport[19], "QToolButton", 28, 8, u8"拾取布置");
	setButton(m_loadImport[20], "QToolButton", 15, 7, u8"构件复制");
	setButton(m_loadImport[21], "QToolButton", 1, 12, u8"层间复制");
	setButton(m_loadImport[22], "QToolButton", 35, 19, u8"移动荷载");
	setButton(m_loadImport[23], "QToolButton", 6, 11, u8"吊车");
	setButton(m_loadImport[24], "QToolButton", 4, 20, u8"人防");
	setButton(m_loadImport[25], "QToolButton", 48, 11, u8"筒仓荷载");
	setButton(m_loadImport[26], "QToolButton", 39, 14, u8"水池荷载");
	setButton(m_loadImport[27], "QToolButton", 4, 17, u8"筏板荷载");
	setButton(m_loadImport[28], "QToolButton", 1, 15, u8"板荷查询");

	setScrollArea(u8"荷载输入", pLayout);
}

void Editor::setUserDefinedConditionButton()
{
	QGridLayout* pLayout = new QGridLayout(this);

	m_userDefinedCondition.resize(16);
	setButtonGridLayout(pLayout, m_userDefinedCondition, 0, m_userDefinedCondition.size());

	setButton(m_userDefinedCondition[0], "QToolButton", 17, 4, u8"工况设置");
	setButton(m_userDefinedCondition[1], "QToolButton", 4, 17, u8"楼板");
	setButton(m_userDefinedCondition[2], "QToolButton", 4, 16, u8"梁墙");
	setButton(m_userDefinedCondition[3], "QToolButton", 4, 18, u8"柱");
	setButton(m_userDefinedCondition[4], "QToolButton", 4, 16, u8"次梁");
	setButton(m_userDefinedCondition[5], "QToolButton", 4, 15, u8"墙洞");
	setButton(m_userDefinedCondition[6], "QToolButton", 23, 1, u8"板间");
	setButton(m_userDefinedCondition[7], "QToolButton", 5, 3, u8"节点");
	setButton(m_userDefinedCondition[8], "QToolButton", 7, 15, u8"删除");
	setButton(m_userDefinedCondition[9], "QToolButton", 48, 11, u8"筒仓荷载");
	setButton(m_userDefinedCondition[10], "QToolButton", 39, 14, u8"水池荷载");
	setButton(m_userDefinedCondition[11], "QToolButton", 4, 17, u8"筏板荷载");
	setButton(m_userDefinedCondition[12], "QToolButton", 25, 17, u8"替换");
	setButton(m_userDefinedCondition[13], "QToolButton", 28, 8, u8"拾取布置");
	setButton(m_userDefinedCondition[14], "QToolButton", 15, 7, u8"构件复制");
	setButton(m_userDefinedCondition[15], "QToolButton", 1, 12, u8"层间复制");

	setScrollArea(u8"自定义工况", pLayout);
}

void Editor::setFloorAssembleButton()
{
	QGridLayout* pLayout = new QGridLayout(this);

	m_floorLayout.resize(21);
	setButtonGridLayout(pLayout, m_floorLayout, 0, m_floorLayout.size());

	setButton(m_floorLayout[0], "QToolButton", 23, 13, u8"必要参数");
	setButton(m_floorLayout[1], "QToolButton", 5, 17, u8"楼层组装");
	setButton(m_floorLayout[2], "QToolButton", 18, 5, u8"各层信息");
	setButton(m_floorLayout[3], "QToolButton", 18, 16, u8"局部楼层");
	setButton(m_floorLayout[4], "QToolButton", 11, 12, u8"单层拼装");
	setButton(m_floorLayout[5], "QToolButton", 14, 4, u8"工程拼装");
	setButton(m_floorLayout[6], "QToolButton", 14, 4, u8"自动拼装");
	setButton(m_floorLayout[7], "QToolButton", 16, 1, u8"删除准层");
	setButton(m_floorLayout[8], "QToolButton", 1, 11, u8"插入准层");
	setButton(m_floorLayout[9], "QToolButton", 16, 15, u8"层间编辑");
	setButton(m_floorLayout[10], "QToolButton", 29, 16, u8"标准层合并");
	setButton(m_floorLayout[11], "QToolButton", 48, 7, u8"模型检查");
	setButton(m_floorLayout[12], "QToolButton", 48, 5, u8"计算数检");
	setButton(m_floorLayout[13], "QToolButton", 38, 1, u8"超限信息");
	setButton(m_floorLayout[14], "QToolButton", 48, 4, u8"工程对比");
	setButton(m_floorLayout[15], "QToolButton", 48, 2, u8"对比结果");
	setButton(m_floorLayout[16], "QToolButton", 49, 12, u8"清理对比");
	setButton(m_floorLayout[17], "QToolButton", 23, 9, u8"工程量统计");
	setButton(m_floorLayout[18], "QToolButton", 11, 8, u8"模型链接");
	setButton(m_floorLayout[19], "QToolButton", 11, 8, u8"隐藏链接模型");
	setButton(m_floorLayout[20], "QToolButton", 11, 8, u8"删除链接模型");

	setScrollArea(u8"楼层组装", pLayout);
}

void Editor::setSpatialStructureButton()
{
	QGridLayout* pLayout = new QGridLayout(this);

	m_spatialStructure.resize(38);
	setButtonGridLayout(pLayout, m_spatialStructure, 0, 25);

	setButton(m_spatialStructure[0], "QToolButton", 18, 16, u8"参照楼层");
	setButton(m_spatialStructure[1], "QToolButton", 3, 3, u8"节点");
	setButton(m_spatialStructure[2], "QToolButton", 1, 16, u8"直线");
	setButton(m_spatialStructure[3], "QToolButton", 5, 6, u8"圆弧网络");
	setButton(m_spatialStructure[4], "QToolButton", 36, 9, u8"空间桁架");
	setButton(m_spatialStructure[5], "QToolButton", 35, 4, u8"网架网壳");
	setButton(m_spatialStructure[6], "QToolButton", 35, 3, u8"一榀桁架");
	setButton(m_spatialStructure[7], "QToolButton", 30, 4, u8"导入DWG");
	setButton(m_spatialStructure[8], "QToolButton", 38, 4, u8"MST");
	setButton(m_spatialStructure[9], "QToolButton", 38, 6, u8"3D3S");
	setButton(m_spatialStructure[10], "QToolButton", 13, 12, u8"工作基面");
	setButton(m_spatialStructure[11], "QToolButton", 37, 6, u8"取消工作基面");
	setButton(m_spatialStructure[12], "QToolButton", 6, 18, u8"上节点高");
	setButton(m_spatialStructure[13], "QToolButton", 4, 5, u8"柱");
	setButton(m_spatialStructure[14], "QToolButton", 4, 1, u8"梁");
	setButton(m_spatialStructure[15], "QToolButton", 4, 3, u8"斜杠");
	setButton(m_spatialStructure[16], "QToolButton", 42, 17, u8"杠件转换");
	setButton(m_spatialStructure[17], "QToolButton", 17, 4, u8"工况设置");
	setButton(m_spatialStructure[18], "QToolButton", 4, 16, u8"梁");
	setButton(m_spatialStructure[19], "QToolButton", 11, 8, u8"节点");
	setButton(m_spatialStructure[20], "QToolButton", 6, 14, u8"梁");
	setButton(m_spatialStructure[21], "QToolButton", 3, 17, u8"节点");
	setButton(m_spatialStructure[22], "QToolButton", 9, 8, u8"蒙皮");
	setButton(m_spatialStructure[23], "QToolButton", 25, 11, u8"显示荷载");
	setButton(m_spatialStructure[24], "QToolButton", 29, 2, u8"导入楼层");

	setDoubleMinButtonGridLayout(pLayout, m_spatialStructure, 25, 33, 4);

	setPonstStyleSheet(m_spatialStructure[25], "QToolButton", 7, 20);
	setPonstStyleSheet(m_spatialStructure[26], "QToolButton", 8, 1);
	setPonstStyleSheet(m_spatialStructure[27], "QToolButton", 8, 2);
	setPonstStyleSheet(m_spatialStructure[28], "QToolButton", 8, 3);
	setPonstStyleSheet(m_spatialStructure[29], "QToolButton", 8, 4);
	setPonstStyleSheet(m_spatialStructure[30], "QToolButton", 8, 10);
	setPonstStyleSheet(m_spatialStructure[31], "QToolButton", 8, 9);
	setPonstStyleSheet(m_spatialStructure[32], "QToolButton", 30, 11);

	setButtonGridLayout(pLayout, m_spatialStructure, 33, m_spatialStructure.size());
	setButton(m_spatialStructure[33], "QToolButton", 8, 7, u8"节点网络");
	setButton(m_spatialStructure[34], "QToolButton", 8, 7, u8"构件");
	setButton(m_spatialStructure[35], "QToolButton", 7, 15, u8"荷载");
	setButton(m_spatialStructure[36], "QToolButton", 35, 4, u8"自动生成");
	setButton(m_spatialStructure[37], "QToolButton", 42, 16, u8"指定上下弦");

	setScrollArea(u8"空间结构", pLayout);
}

void Editor::setAuthenticateReinforceButton()
{
	QGridLayout* pLayout = new QGridLayout(this);

	m_authenticateReinforce.resize(5);
	setButtonGridLayout(pLayout, m_authenticateReinforce, 0, 5);

	setButton(m_authenticateReinforce[0], "QToolButton", 9, 7, u8"新增构件");
	setButton(m_authenticateReinforce[1], "QToolButton", 9, 8, u8"柱加固");
	setButton(m_authenticateReinforce[2], "QToolButton", 4, 1, u8"梁加固");
	setButton(m_authenticateReinforce[3], "QToolButton", 16, 18, u8"震损系数");
	setButton(m_authenticateReinforce[4], "QToolButton", 21, 18, u8"删除");
	pLayout->setHorizontalSpacing(10);

	setScrollArea(u8"鉴定加固", pLayout);
}

void Editor::setToolbarButton()
{
	QGridLayout* pLayout = new QGridLayout(this);

	m_toolbar.resize(37);

	setDoubleMinButtonGridLayout(pLayout, m_toolbar, 0, m_toolbar.size(), 29);

	setPonstStyleSheet(m_toolbar[0], "QToolButton", 39, 2);
	setPonstStyleSheet(m_toolbar[1], "QToolButton", 39, 1);
	setPonstStyleSheet(m_toolbar[2], "QToolButton", 28, 15);
	setPonstStyleSheet(m_toolbar[3], "QToolButton", 7, 2);
	setPonstStyleSheet(m_toolbar[4], "QToolButton", 7, 4);
	setPonstStyleSheet(m_toolbar[5], "QToolButton", 7, 6);
	setPonstStyleSheet(m_toolbar[6], "QToolButton", 15, 1);
	setPonstStyleSheet(m_toolbar[7], "QToolButton", 7, 12);
	setPonstStyleSheet(m_toolbar[8], "QToolButton", 19, 2);
	setPonstStyleSheet(m_toolbar[9], "QToolButton", 18, 20);
	setPonstStyleSheet(m_toolbar[10], "QToolButton", 19, 3);
	setPonstStyleSheet(m_toolbar[11], "QToolButton", 7, 13);
	setPonstStyleSheet(m_toolbar[12], "QToolButton", 6, 10);
	setPonstStyleSheet(m_toolbar[13], "QToolButton", 30, 9);
	setPonstStyleSheet(m_toolbar[14], "QToolButton", 30, 10);
	setPonstStyleSheet(m_toolbar[15], "QToolButton", 30, 14);
	setPonstStyleSheet(m_toolbar[16], "QToolButton", 30, 15);
	setPonstStyleSheet(m_toolbar[17], "QToolButton", 30, 20);
	setPonstStyleSheet(m_toolbar[18], "QToolButton", 15, 11);
	setPonstStyleSheet(m_toolbar[19], "QToolButton", 15, 13);
	setPonstStyleSheet(m_toolbar[20], "QToolButton", 14, 3);
	setPonstStyleSheet(m_toolbar[21], "QToolButton", 36, 11);
	setPonstStyleSheet(m_toolbar[22], "QToolButton", 36, 14);
	setPonstStyleSheet(m_toolbar[23], "QToolButton", 5, 17);
	setPonstStyleSheet(m_toolbar[24], "QToolButton", 16, 15);
	setPonstStyleSheet(m_toolbar[25], "QToolButton", 16, 1);
	setPonstStyleSheet(m_toolbar[26], "QToolButton", 14, 18);
	setPonstStyleSheet(m_toolbar[27], "QToolButton", 12, 5);
	setPonstStyleSheet(m_toolbar[28], "QToolButton", 18, 5);
	setPonstStyleSheet(m_toolbar[29], "QToolButton", 28, 16);
	setPonstStyleSheet(m_toolbar[30], "QToolButton", 17, 4);
	setPonstStyleSheet(m_toolbar[31], "QToolButton", 15, 8);
	setPonstStyleSheet(m_toolbar[32], "QToolButton", 15, 10);
	setPonstStyleSheet(m_toolbar[33], "QToolButton", 15, 9);
	setPonstStyleSheet(m_toolbar[34], "QToolButton", 29, 10);
	setPonstStyleSheet(m_toolbar[35], "QToolButton", 38, 18);
	setPonstStyleSheet(m_toolbar[36], "QToolButton", 30, 4);

	setScrollArea(u8"工具栏", pLayout);
}

void Editor::setCmdDockWidget()
{
	QListView* cmdShowCase = new QListView(this);
	cmdShowCase->setMinimumSize(QSize(700, 90));
	cmdShowCase->setMaximumSize(QSize(700, 90));
	QTextEdit* cmdCallCase = new QTextEdit(this);
	cmdCallCase->setMinimumSize(QSize(700, 20));
	cmdCallCase->setMaximumSize(QSize(700, 20));

	QVBoxLayout* pLayout = new QVBoxLayout(this);
	pLayout->addSpacing(0);
	pLayout->addWidget(cmdShowCase);
	pLayout->addSpacing(0);
	pLayout->addWidget(cmdCallCase);
	pLayout->addStretch();

	setScrollArea(u8"命令", pLayout);
}

void Editor::setSelectDockWidget()
{
	QWidget* newWidget = new QWidget(this);
	m_mapDocks[u8"选择"]->setWidget(newWidget);
	QGridLayout* pLayout = new QGridLayout();

	std::vector<std::string> radioButtonNameArr = { u8"全部", u8"筛选" , u8"光标", u8"围区" };
	std::vector<QRadioButton*> radioButtons;
	radioButtons.resize(radioButtonNameArr.size());

	QGroupBox* state = new QGroupBox(this);
	QVBoxLayout* stateLayout = new QVBoxLayout(this);
	QGroupBox* area = new QGroupBox(this);
	QVBoxLayout* areaLayout = new QVBoxLayout(this);
	for (auto i = 0;i < radioButtons.size();i++)
	{
		radioButtons[i] = new QRadioButton(this);
		radioButtons[i]->setText(radioButtonNameArr[i].c_str());
		if (i > 1)
			stateLayout->addWidget(radioButtons[i]);
		else
			areaLayout->addWidget(radioButtons[i]);
	}
	state->setLayout(stateLayout);
	area->setLayout(areaLayout);
	pLayout->addWidget(state, 0, 0, 2, 1, Qt::AlignLeft | Qt::AlignVCenter);
	pLayout->addWidget(area, 2, 0, 2, 1, Qt::AlignLeft | Qt::AlignVCenter);

	std::vector<std::string> checkboxNameArr = { u8"柱", u8"梁" , u8"墙", u8"窗", u8"斜杠", u8"板", u8"板洞", u8"次梁", u8"悬挑板", u8"节点", u8"网络" };
	std::vector<QCheckBox*> checkboxs;
	checkboxs.resize(checkboxNameArr.size());
	for (auto i = 0; i < checkboxs.size(); i++)
	{
		checkboxs[i] = new QCheckBox(this);
		checkboxs[i]->setText(checkboxNameArr[i].c_str());
		if (i > 8)
			pLayout->addWidget(checkboxs[i], 2, i - 8, 1, 1);
		else if (i > 4)
			pLayout->addWidget(checkboxs[i], 1, i - 4, 1, 1);
		else
			pLayout->addWidget(checkboxs[i], 0, i + 1, 1, 1);
	}

	std::vector<QRadioButton*> electoralDistricts;
	electoralDistricts.resize(3);
	for (auto i = 0;i < electoralDistricts.size();i++)
	{
		electoralDistricts[i] = new QRadioButton(this);
		pLayout->addWidget(electoralDistricts[i], 3, i + 1, 1, 2);
	}

	std::vector<QToolButton*> selectButtons;
	selectButtons.resize(5);
	for (auto i = 0; i < 4; i++)
	{
		selectButtons[i] = new QToolButton(this);
		selectButtons[i]->setMinimumSize(QSize(32, 32));
		selectButtons[i]->setMaximumSize(QSize(32, 32));
		selectButtons[i]->setStyleSheet("QToolButton:hover{background-color:rgb(204 ,255 ,255);border-radius:5px;}"
			"QToolButton:pressed{background-color:rgb(0 ,255 ,255);padding-left:3px; padding-top:3px;}");
		pLayout->addWidget(selectButtons[i], 4, i + 1, 1, 2);
	}

	setPonstStyleSheet(selectButtons[0], "QToolButton", 15, 10);
	setPonstStyleSheet(selectButtons[1], "QToolButton", 15, 8);
	setPonstStyleSheet(selectButtons[2], "QToolButton", 15, 9);
	setPonstStyleSheet(selectButtons[3], "QToolButton", 19, 16);

	selectButtons[4] = new QToolButton(this);
	selectButtons[4]->setMinimumSize(QSize(40, 30));
	selectButtons[4]->setMaximumSize(QSize(40, 30));
	selectButtons[4]->setText(u8"显示");
	selectButtons[4]->setStyleSheet("QToolButton:hover{background-color:rgb(204 ,255 ,255);}"
		"QToolButton:pressed{background-color:rgb(0 ,255 ,255);padding-left:3px; padding-top:3px;}");
	pLayout->addWidget(selectButtons[4], 4, 5, 1, 2);

	newWidget->setLayout(pLayout);
}

void Editor::showGraphTest()
{
	//setScrollArea(u8"图形", pLayout);
	//QWidget* newWidget = new QWidget(this);

	QWidget* widget = m_mapDocks[u8"图形"];
	PluginManager* pm = PluginManager::GetPluginManager();
	RenderViewInterface* renderView = (RenderViewInterface*)pm->getPlugin("RenderViewSetting");
	void* hwnd = renderView->QWidgetToHWND(widget);
	widget->installEventFilter(this);

	//ScrollArea* scrollArea = new ScrollArea(this);
	//scrollArea->setWidget(newWidget);
	//m_mapDocks[u8"图形"]->setWidget(scrollArea);
}

