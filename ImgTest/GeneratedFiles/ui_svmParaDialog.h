/********************************************************************************
** Form generated from reading UI file 'svmParaDialog.ui'
**
** Created: Sat Aug 16 14:21:15 2014
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SVMPARADIALOG_H
#define UI_SVMPARADIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_svmParaDialog
{
public:
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLabel *label;
    QLineEdit *roiFilePath;
    QComboBox *kernelTypeComboBox;
    QLineEdit *modelFilePath;
    QSpacerItem *verticalSpacer;
    QPushButton *modelFileBrowseBtn;
    QPushButton *roiFileBrowseBtn;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *ExecuteBtn;
    QPushButton *CancelBtn;
    QGridLayout *gridLayout_2;
    QLabel *label_4;
    QSpinBox *degreeSpinBox;
    QLabel *label_6;
    QLineEdit *biasLineEdit;
    QLabel *label_5;
    QLineEdit *PenaltyLineEdit;
    QLineEdit *GammaLineEdit;
    QLabel *label_7;
    QSpinBox *pyramidLevelsSpinBox;
    QLabel *label_8;
    QHBoxLayout *horizontalLayout;
    QLabel *label_9;
    QLineEdit *resultFilePath;
    QPushButton *resultFileBrowseBtn;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_4;

    void setupUi(QWidget *svmParaDialog)
    {
        if (svmParaDialog->objectName().isEmpty())
            svmParaDialog->setObjectName(QString::fromUtf8("svmParaDialog"));
        svmParaDialog->setEnabled(true);
        svmParaDialog->resize(332, 454);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(svmParaDialog->sizePolicy().hasHeightForWidth());
        svmParaDialog->setSizePolicy(sizePolicy);
        svmParaDialog->setMinimumSize(QSize(332, 454));
        svmParaDialog->setMaximumSize(QSize(332, 454));
        gridLayout_3 = new QGridLayout(svmParaDialog);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_3 = new QLabel(svmParaDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        label = new QLabel(svmParaDialog);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        roiFilePath = new QLineEdit(svmParaDialog);
        roiFilePath->setObjectName(QString::fromUtf8("roiFilePath"));

        gridLayout->addWidget(roiFilePath, 0, 1, 1, 1);

        kernelTypeComboBox = new QComboBox(svmParaDialog);
        kernelTypeComboBox->setObjectName(QString::fromUtf8("kernelTypeComboBox"));

        gridLayout->addWidget(kernelTypeComboBox, 3, 1, 1, 1);

        modelFilePath = new QLineEdit(svmParaDialog);
        modelFilePath->setObjectName(QString::fromUtf8("modelFilePath"));

        gridLayout->addWidget(modelFilePath, 1, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 1, 1, 1);

        modelFileBrowseBtn = new QPushButton(svmParaDialog);
        modelFileBrowseBtn->setObjectName(QString::fromUtf8("modelFileBrowseBtn"));

        gridLayout->addWidget(modelFileBrowseBtn, 1, 2, 1, 1);

        roiFileBrowseBtn = new QPushButton(svmParaDialog);
        roiFileBrowseBtn->setObjectName(QString::fromUtf8("roiFileBrowseBtn"));

        gridLayout->addWidget(roiFileBrowseBtn, 0, 2, 1, 1);

        label_2 = new QLabel(svmParaDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);


        gridLayout_3->addLayout(gridLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        ExecuteBtn = new QPushButton(svmParaDialog);
        ExecuteBtn->setObjectName(QString::fromUtf8("ExecuteBtn"));

        horizontalLayout_2->addWidget(ExecuteBtn);

        CancelBtn = new QPushButton(svmParaDialog);
        CancelBtn->setObjectName(QString::fromUtf8("CancelBtn"));

        horizontalLayout_2->addWidget(CancelBtn);


        gridLayout_3->addLayout(horizontalLayout_2, 6, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_4 = new QLabel(svmParaDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 0, 0, 1, 1);

        degreeSpinBox = new QSpinBox(svmParaDialog);
        degreeSpinBox->setObjectName(QString::fromUtf8("degreeSpinBox"));
        degreeSpinBox->setMaximumSize(QSize(51, 16777215));

        gridLayout_2->addWidget(degreeSpinBox, 0, 1, 1, 1);

        label_6 = new QLabel(svmParaDialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 2, 0, 1, 1);

        biasLineEdit = new QLineEdit(svmParaDialog);
        biasLineEdit->setObjectName(QString::fromUtf8("biasLineEdit"));
        biasLineEdit->setMaximumSize(QSize(51, 16777215));

        gridLayout_2->addWidget(biasLineEdit, 1, 1, 1, 1);

        label_5 = new QLabel(svmParaDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 1, 0, 1, 1);

        PenaltyLineEdit = new QLineEdit(svmParaDialog);
        PenaltyLineEdit->setObjectName(QString::fromUtf8("PenaltyLineEdit"));
        PenaltyLineEdit->setMaximumSize(QSize(51, 16777215));

        gridLayout_2->addWidget(PenaltyLineEdit, 3, 1, 1, 1);

        GammaLineEdit = new QLineEdit(svmParaDialog);
        GammaLineEdit->setObjectName(QString::fromUtf8("GammaLineEdit"));
        GammaLineEdit->setMaximumSize(QSize(51, 16777215));

        gridLayout_2->addWidget(GammaLineEdit, 2, 1, 1, 1);

        label_7 = new QLabel(svmParaDialog);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 3, 0, 1, 1);

        pyramidLevelsSpinBox = new QSpinBox(svmParaDialog);
        pyramidLevelsSpinBox->setObjectName(QString::fromUtf8("pyramidLevelsSpinBox"));
        pyramidLevelsSpinBox->setMaximumSize(QSize(51, 16777215));

        gridLayout_2->addWidget(pyramidLevelsSpinBox, 4, 1, 1, 1);

        label_8 = new QLabel(svmParaDialog);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_2->addWidget(label_8, 4, 0, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 2, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_9 = new QLabel(svmParaDialog);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout->addWidget(label_9);

        resultFilePath = new QLineEdit(svmParaDialog);
        resultFilePath->setObjectName(QString::fromUtf8("resultFilePath"));

        horizontalLayout->addWidget(resultFilePath);

        resultFileBrowseBtn = new QPushButton(svmParaDialog);
        resultFileBrowseBtn->setObjectName(QString::fromUtf8("resultFileBrowseBtn"));

        horizontalLayout->addWidget(resultFileBrowseBtn);


        gridLayout_3->addLayout(horizontalLayout, 4, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_2, 1, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_3, 3, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_4, 5, 0, 1, 1);


        retranslateUi(svmParaDialog);

        QMetaObject::connectSlotsByName(svmParaDialog);
    } // setupUi

    void retranslateUi(QWidget *svmParaDialog)
    {
        svmParaDialog->setWindowTitle(QApplication::translate("svmParaDialog", "Support Vector Machine", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("svmParaDialog", "Kernel Type:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("svmParaDialog", "Roi File:", 0, QApplication::UnicodeUTF8));
        kernelTypeComboBox->clear();
        kernelTypeComboBox->insertItems(0, QStringList()
         << QApplication::translate("svmParaDialog", "Linear", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("svmParaDialog", "Radial Based Function", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("svmParaDialog", "Sigmoid", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("svmParaDialog", "Polynomial", 0, QApplication::UnicodeUTF8)
        );
        modelFileBrowseBtn->setText(QApplication::translate("svmParaDialog", "Browse", 0, QApplication::UnicodeUTF8));
        roiFileBrowseBtn->setText(QApplication::translate("svmParaDialog", "Browse", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("svmParaDialog", "Model File:", 0, QApplication::UnicodeUTF8));
        ExecuteBtn->setText(QApplication::translate("svmParaDialog", "Execute", 0, QApplication::UnicodeUTF8));
        CancelBtn->setText(QApplication::translate("svmParaDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("svmParaDialog", "Degree of Kernel Polynomial:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("svmParaDialog", "Gamma in Kernel Function:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("svmParaDialog", "Bias in Kernel Function:", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("svmParaDialog", "Penalty Parameter:", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("svmParaDialog", "Pyramid Levels:", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("svmParaDialog", "Result File:", 0, QApplication::UnicodeUTF8));
        resultFileBrowseBtn->setText(QApplication::translate("svmParaDialog", "Browse", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class svmParaDialog: public Ui_svmParaDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SVMPARADIALOG_H
