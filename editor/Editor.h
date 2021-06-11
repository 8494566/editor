#ifndef EDITOR_H
#define EDITOR_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QGridLayout>
#include <vector>
#include <map>
#include "ui_Editor.h"

class Editor : public QMainWindow
{
    Q_OBJECT

public:
    explicit Editor(QWidget *parent = Q_NULLPTR);
	~Editor();
private:
    void init();
public:
	void removeAllDock();
private:
    void showDockWidget(const std::vector<QDockWidget*>& docks, const QList<int>& index = QList<int>());
    void setPonstStyleSheet(QWidget* widgrtPtr, const char * tpyeName, const int iconPonstRow, const int iconPonstRank);
    void setButton(QAbstractButton * buttonPtr, const char* tpyeName, const int iconPonstRow, const int iconPonstRank, const char * buttonText);
    void setDoubleMinButtonGridLayout(QGridLayout* pLayout, std::vector<QToolButton*> & buttonVector, int begin, int end, int lineFeed);
    void setButtonGridLayout(QGridLayout* pLayout, std::vector<QToolButton*>& buttonVector, int begin, int end);
    void newDockWidget(std::vector<QDockWidget*> & docks , const std::vector<std::string> & dockNameArr);
    void setDockWidgetPonst(std::vector<QDockWidget*>& docks);
    void setScrollArea(const char * dockName, QLayout * layout);
private slots:
    void onClickedToolBarButtonGroup();
private:
    void craeteToolBar();
    void setBearingMeshButton();
    void setComponentLayoutButton();
    void setFloorLayoutButton();
    void setLoadImportButton();
    void setUserDefinedConditionButton();
    void setFloorAssembleButton();
    void setSpatialStructureButton();
    void setAuthenticateReinforceButton();
private:
    void setToolbarButton();
    void setCmdDockWidget();
private:
    void setSelectDockWidget();
private://设置窗口位置函数,重复调用,请勿使用new
	void setModelLoadPonst();
    void setTopStructureCountPonst();
    void setProjectcCmpPonst();
    void setCutBulkPonst();
    void setBaseDesignPonst();
    void setWorkingPlanPonst();
    void setPrefabricatePonst();
    void setSteelStructurePonst();
    void setNolinearCountPonst();
    void setMapCompilePonst();
    void setCmdTreeWidgetPonst();
private:
    QButtonGroup* m_toolBarButtonGroup{ nullptr };
    int m_toolBarButtonState{ 0 };
private:
    Ui::EditorClass* ui{ new Ui::EditorClass };
	std::map<std::string, QDockWidget*> m_mapDocks;
	std::vector<QDockWidget*> m_docks;
    std::vector<QDockWidget*> m_modelLoadInput;
    std::vector<QDockWidget*> m_treeMoedlLoad;
    std::vector<QDockWidget*> m_topStructureCount;
    std::vector<QDockWidget*> m_projectcCmp;
    std::vector<QDockWidget*> m_cutBulk;
    std::vector<QDockWidget*> m_baseDesign;
    std::vector<QDockWidget*> m_workingPlan;
    std::vector<QDockWidget*> m_prefabricateMap;
    std::vector<QDockWidget*> m_steelStructure;
    std::vector<QDockWidget*> m_nolinearCount;
    std::vector<QDockWidget*> m_mapCompile;
private:
    std::vector<QToolButton*> m_bearingMesh;
    std::vector<QToolButton*> m_componentLayout;
    std::vector<QToolButton*> m_floorLayout;
    std::vector<QToolButton*> m_loadImport;
    std::vector<QToolButton*> m_userDefinedCondition;
    std::vector<QToolButton*> m_floorAssemble;
    std::vector<QToolButton*> m_spatialStructure;
    std::vector<QToolButton*> m_authenticateReinforce;
    std::vector<QToolButton*> m_toolbar;
    std::vector<QToolButton*> m_toolBarButtons;
    std::vector<QToolButton*> m_prefabricateSplit;

};

#endif // EDITOR_H