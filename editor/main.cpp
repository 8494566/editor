#include "Editor.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    application.setWindowIcon(QIcon(":/Editor/img/yjks.ico"));
    Editor editorExe;
    editorExe.show();
    return application.exec();
}
