#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Editor.h"

class Editor : public QMainWindow
{
    Q_OBJECT

public:
    Editor(QWidget *parent = Q_NULLPTR);
public:
    void setPonstStyleSheet(QWidget* widgrtPtr, const char * tpyeName, const int iconPonstRow, const int iconPonstRank);
    void setButton(QAbstractButton * buttonPtr, const int iconPonstRow, const int iconPonstRank, const char * buttonText);

private:
    void setBearingNetworkButton();
    void setToolButton();

private:
    Ui::EditorClass ui;
};
