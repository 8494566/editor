#include "Editor.h"
#include <QtWidgets/QApplication>
#include "LibraryManagers/Plugin/PluginManager.h"
#include "JsonToQtInterface/Interface/JsonToQtInterface.h"
#include "RenderViewSetting/Interface/RenderViewInterface.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
	PluginManager* pm = PluginManager::GetPluginManager();
	pm->loadPlugin(application.applicationDirPath().toStdString());//设置exe路径 必须
    application.setWindowIcon(QIcon(":/Editor/img/yjks.ico"));
    Editor editorExe;
    editorExe.showMaximized();
    //editorExe.setWindowOpacity(0.7);

    JsonToQtInterface* pJson =  (JsonToQtInterface*)pm->getPlugin("JsonToQtInterface");
    pJson->call("小小wuzi,可笑可笑");

    return application.exec();
}
