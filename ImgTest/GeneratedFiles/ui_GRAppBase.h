/********************************************************************************
** Form generated from reading UI file 'GRAppBase.ui'
**
** Created: Thu Oct 23 13:54:05 2014
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPPBASE_H
#define UI_GRAPPBASE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GRAppBase
{
public:
    QAction *actionOpen_project;
    QAction *actionSave_project;
    QAction *actionSave_project_as;
    QAction *actionExit;
    QAction *actionAdd_a_vector_layer;
    QAction *actionCheck_GR_version;
    QAction *actionPlugin_manager;
    QAction *actionTest_plugin_functions;
    QAction *actionOptions;
    QAction *action_About;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QFrame *frameMain;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuView;
    QMenu *menuTools;
    QMenu *menuHelp;
    QStatusBar *statusbar;
    QToolBar *toolBar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;

    void setupUi(QMainWindow *GRAppBase)
    {
        if (GRAppBase->objectName().isEmpty())
            GRAppBase->setObjectName(QString::fromUtf8("GRAppBase"));
        GRAppBase->resize(808, 509);
        GRAppBase->setDocumentMode(false);
        actionOpen_project = new QAction(GRAppBase);
        actionOpen_project->setObjectName(QString::fromUtf8("actionOpen_project"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ImgTest/open_proj.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen_project->setIcon(icon);
        actionSave_project = new QAction(GRAppBase);
        actionSave_project->setObjectName(QString::fromUtf8("actionSave_project"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ImgTest/save_proj.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_project->setIcon(icon1);
        actionSave_project_as = new QAction(GRAppBase);
        actionSave_project_as->setObjectName(QString::fromUtf8("actionSave_project_as"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/ImgTest/save_as_proj.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_project_as->setIcon(icon2);
        actionExit = new QAction(GRAppBase);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/ImgTest/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon3);
        actionAdd_a_vector_layer = new QAction(GRAppBase);
        actionAdd_a_vector_layer->setObjectName(QString::fromUtf8("actionAdd_a_vector_layer"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/ImgTest/add_vector.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAdd_a_vector_layer->setIcon(icon4);
        actionCheck_GR_version = new QAction(GRAppBase);
        actionCheck_GR_version->setObjectName(QString::fromUtf8("actionCheck_GR_version"));
        actionPlugin_manager = new QAction(GRAppBase);
        actionPlugin_manager->setObjectName(QString::fromUtf8("actionPlugin_manager"));
        actionTest_plugin_functions = new QAction(GRAppBase);
        actionTest_plugin_functions->setObjectName(QString::fromUtf8("actionTest_plugin_functions"));
        actionOptions = new QAction(GRAppBase);
        actionOptions->setObjectName(QString::fromUtf8("actionOptions"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/ImgTest/options.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOptions->setIcon(icon5);
        action_About = new QAction(GRAppBase);
        action_About->setObjectName(QString::fromUtf8("action_About"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/ImgTest/about.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_About->setIcon(icon6);
        centralwidget = new QWidget(GRAppBase);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        frameMain = new QFrame(centralwidget);
        frameMain->setObjectName(QString::fromUtf8("frameMain"));
        frameMain->setFrameShape(QFrame::StyledPanel);
        frameMain->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(frameMain, 0, 0, 1, 1);

        GRAppBase->setCentralWidget(centralwidget);
        menubar = new QMenuBar(GRAppBase);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 808, 23));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuView = new QMenu(menubar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuTools = new QMenu(menubar);
        menuTools->setObjectName(QString::fromUtf8("menuTools"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        GRAppBase->setMenuBar(menubar);
        statusbar = new QStatusBar(GRAppBase);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        GRAppBase->setStatusBar(statusbar);
        toolBar = new QToolBar(GRAppBase);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        GRAppBase->addToolBar(Qt::TopToolBarArea, toolBar);
        dockWidget = new QDockWidget(GRAppBase);
        dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        dockWidget->setWidget(dockWidgetContents);
        GRAppBase->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuView->menuAction());
        menubar->addAction(menuTools->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOpen_project);
        menuFile->addSeparator();
        menuFile->addAction(actionSave_project);
        menuFile->addAction(actionSave_project_as);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuView->addAction(actionAdd_a_vector_layer);
        menuTools->addAction(actionCheck_GR_version);
        menuTools->addAction(actionPlugin_manager);
        menuTools->addAction(actionTest_plugin_functions);
        menuTools->addAction(actionOptions);
        menuHelp->addAction(action_About);
        toolBar->addAction(actionOpen_project);
        toolBar->addAction(actionSave_project);
        toolBar->addAction(actionSave_project_as);
        toolBar->addAction(actionAdd_a_vector_layer);
        toolBar->addAction(action_About);

        retranslateUi(GRAppBase);

        QMetaObject::connectSlotsByName(GRAppBase);
    } // setupUi

    void retranslateUi(QMainWindow *GRAppBase)
    {
        GRAppBase->setWindowTitle(QApplication::translate("GRAppBase", "GIS and RS", 0, QApplication::UnicodeUTF8));
        actionOpen_project->setText(QApplication::translate("GRAppBase", "&Open project", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionOpen_project->setToolTip(QApplication::translate("GRAppBase", "Open project", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionOpen_project->setShortcut(QApplication::translate("GRAppBase", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        actionSave_project->setText(QApplication::translate("GRAppBase", "Save project", 0, QApplication::UnicodeUTF8));
        actionSave_project->setShortcut(QApplication::translate("GRAppBase", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionSave_project_as->setText(QApplication::translate("GRAppBase", "Save project as", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSave_project_as->setToolTip(QApplication::translate("GRAppBase", "Save project as", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionSave_project_as->setShortcut(QApplication::translate("GRAppBase", "Ctrl+Shift+S", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("GRAppBase", "Exit", 0, QApplication::UnicodeUTF8));
        actionAdd_a_vector_layer->setText(QApplication::translate("GRAppBase", "Add a vector layer", 0, QApplication::UnicodeUTF8));
        actionCheck_GR_version->setText(QApplication::translate("GRAppBase", "Check GR version", 0, QApplication::UnicodeUTF8));
        actionPlugin_manager->setText(QApplication::translate("GRAppBase", "Plugin Manager", 0, QApplication::UnicodeUTF8));
        actionTest_plugin_functions->setText(QApplication::translate("GRAppBase", "Test plugin functions", 0, QApplication::UnicodeUTF8));
        actionOptions->setText(QApplication::translate("GRAppBase", "options", 0, QApplication::UnicodeUTF8));
        action_About->setText(QApplication::translate("GRAppBase", "&About ", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("GRAppBase", "File", 0, QApplication::UnicodeUTF8));
        menuView->setTitle(QApplication::translate("GRAppBase", "View", 0, QApplication::UnicodeUTF8));
        menuTools->setTitle(QApplication::translate("GRAppBase", "Tools", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("GRAppBase", "Help", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("GRAppBase", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GRAppBase: public Ui_GRAppBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPPBASE_H
