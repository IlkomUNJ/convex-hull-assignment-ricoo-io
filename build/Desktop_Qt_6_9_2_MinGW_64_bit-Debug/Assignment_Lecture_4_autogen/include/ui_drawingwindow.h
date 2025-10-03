/********************************************************************************
** Form generated from reading UI file 'drawingwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRAWINGWINDOW_H
#define UI_DRAWINGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DrawingWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QPushButton *pushButtonClear;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *DrawingWindow)
    {
        if (DrawingWindow->objectName().isEmpty())
            DrawingWindow->setObjectName("DrawingWindow");
        DrawingWindow->resize(800, 600);
        centralwidget = new QWidget(DrawingWindow);
        centralwidget->setObjectName("centralwidget");
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(300, 490, 80, 24));
        pushButtonClear = new QPushButton(centralwidget);
        pushButtonClear->setObjectName("pushButtonClear");
        pushButtonClear->setGeometry(QRect(410, 490, 80, 24));
        DrawingWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(DrawingWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        DrawingWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(DrawingWindow);
        statusbar->setObjectName("statusbar");
        DrawingWindow->setStatusBar(statusbar);

        retranslateUi(DrawingWindow);

        QMetaObject::connectSlotsByName(DrawingWindow);
    } // setupUi

    void retranslateUi(QMainWindow *DrawingWindow)
    {
        DrawingWindow->setWindowTitle(QCoreApplication::translate("DrawingWindow", "DrawingWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("DrawingWindow", "Clear Button", nullptr));
        pushButtonClear->setText(QCoreApplication::translate("DrawingWindow", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DrawingWindow: public Ui_DrawingWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRAWINGWINDOW_H
