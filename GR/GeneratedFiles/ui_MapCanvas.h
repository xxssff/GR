/********************************************************************************
** Form generated from reading UI file 'MapCanvas.ui'
**
** Created: Fri Nov 14 21:12:38 2014
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAPCANVAS_H
#define UI_MAPCANVAS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>

QT_BEGIN_NAMESPACE

class Ui_MapCanvas
{
public:

    void setupUi(QLabel *MapCanvas)
    {
        if (MapCanvas->objectName().isEmpty())
            MapCanvas->setObjectName(QString::fromUtf8("MapCanvas"));
        MapCanvas->resize(400, 300);

        retranslateUi(MapCanvas);

        QMetaObject::connectSlotsByName(MapCanvas);
    } // setupUi

    void retranslateUi(QLabel *MapCanvas)
    {
        MapCanvas->setWindowTitle(QApplication::translate("MapCanvas", "MapCanvas", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MapCanvas: public Ui_MapCanvas {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPCANVAS_H
