/********************************************************************************
** Form generated from reading UI file 'AddOrEditSGOOnMapDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDOREDITSGOONMAPDIALOG_H
#define UI_ADDOREDITSGOONMAPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_AddOrEditSGOOnMapDialog
{
public:
    QGroupBox *positionGroupBox;
    QLabel *xPosLbl;
    QLabel *yPosLbl;
    QLineEdit *yPosTxt;
    QLabel *zPosLbl;
    QLineEdit *zPosTxt;
    QLineEdit *xPosTxt;
    QGroupBox *rotateGroupBox;
    QLabel *xRotateLbl;
    QLabel *yRotateLbl;
    QLineEdit *yRotateTxt;
    QLabel *zRotateLbl;
    QLineEdit *zRotateTxt;
    QLineEdit *xRotateTxt;
    QLabel *instanceNameLbl;
    QLineEdit *instanceNameTxt;
    QDialogButtonBox *buttonBox;
    QLabel *validationWarningLbl;

    void setupUi(QDialog *AddOrEditSGOOnMapDialog)
    {
        if (AddOrEditSGOOnMapDialog->objectName().isEmpty())
            AddOrEditSGOOnMapDialog->setObjectName(QStringLiteral("AddOrEditSGOOnMapDialog"));
        AddOrEditSGOOnMapDialog->resize(341, 223);
        positionGroupBox = new QGroupBox(AddOrEditSGOOnMapDialog);
        positionGroupBox->setObjectName(QStringLiteral("positionGroupBox"));
        positionGroupBox->setGeometry(QRect(20, 50, 151, 111));
        xPosLbl = new QLabel(positionGroupBox);
        xPosLbl->setObjectName(QStringLiteral("xPosLbl"));
        xPosLbl->setGeometry(QRect(10, 20, 16, 16));
        yPosLbl = new QLabel(positionGroupBox);
        yPosLbl->setObjectName(QStringLiteral("yPosLbl"));
        yPosLbl->setGeometry(QRect(10, 50, 16, 16));
        yPosTxt = new QLineEdit(positionGroupBox);
        yPosTxt->setObjectName(QStringLiteral("yPosTxt"));
        yPosTxt->setGeometry(QRect(20, 50, 113, 20));
        zPosLbl = new QLabel(positionGroupBox);
        zPosLbl->setObjectName(QStringLiteral("zPosLbl"));
        zPosLbl->setGeometry(QRect(10, 80, 16, 16));
        zPosTxt = new QLineEdit(positionGroupBox);
        zPosTxt->setObjectName(QStringLiteral("zPosTxt"));
        zPosTxt->setGeometry(QRect(20, 80, 113, 20));
        xPosTxt = new QLineEdit(positionGroupBox);
        xPosTxt->setObjectName(QStringLiteral("xPosTxt"));
        xPosTxt->setGeometry(QRect(20, 20, 113, 20));
        rotateGroupBox = new QGroupBox(AddOrEditSGOOnMapDialog);
        rotateGroupBox->setObjectName(QStringLiteral("rotateGroupBox"));
        rotateGroupBox->setGeometry(QRect(180, 50, 151, 111));
        xRotateLbl = new QLabel(rotateGroupBox);
        xRotateLbl->setObjectName(QStringLiteral("xRotateLbl"));
        xRotateLbl->setGeometry(QRect(10, 20, 16, 16));
        yRotateLbl = new QLabel(rotateGroupBox);
        yRotateLbl->setObjectName(QStringLiteral("yRotateLbl"));
        yRotateLbl->setGeometry(QRect(10, 50, 16, 16));
        yRotateTxt = new QLineEdit(rotateGroupBox);
        yRotateTxt->setObjectName(QStringLiteral("yRotateTxt"));
        yRotateTxt->setGeometry(QRect(20, 50, 113, 20));
        zRotateLbl = new QLabel(rotateGroupBox);
        zRotateLbl->setObjectName(QStringLiteral("zRotateLbl"));
        zRotateLbl->setGeometry(QRect(10, 80, 16, 16));
        zRotateTxt = new QLineEdit(rotateGroupBox);
        zRotateTxt->setObjectName(QStringLiteral("zRotateTxt"));
        zRotateTxt->setGeometry(QRect(20, 80, 113, 20));
        xRotateTxt = new QLineEdit(rotateGroupBox);
        xRotateTxt->setObjectName(QStringLiteral("xRotateTxt"));
        xRotateTxt->setGeometry(QRect(20, 20, 113, 20));
        instanceNameLbl = new QLabel(AddOrEditSGOOnMapDialog);
        instanceNameLbl->setObjectName(QStringLiteral("instanceNameLbl"));
        instanceNameLbl->setGeometry(QRect(20, 20, 71, 16));
        instanceNameTxt = new QLineEdit(AddOrEditSGOOnMapDialog);
        instanceNameTxt->setObjectName(QStringLiteral("instanceNameTxt"));
        instanceNameTxt->setGeometry(QRect(90, 20, 241, 20));
        buttonBox = new QDialogButtonBox(AddOrEditSGOOnMapDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(170, 190, 156, 23));
        buttonBox->setLayoutDirection(Qt::RightToLeft);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        validationWarningLbl = new QLabel(AddOrEditSGOOnMapDialog);
        validationWarningLbl->setObjectName(QStringLiteral("validationWarningLbl"));
        validationWarningLbl->setEnabled(true);
        validationWarningLbl->setGeometry(QRect(20, 170, 311, 16));
        QPalette palette;
        QBrush brush(QColor(221, 147, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        QBrush brush2(QColor(120, 120, 120, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        validationWarningLbl->setPalette(palette);

        retranslateUi(AddOrEditSGOOnMapDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), AddOrEditSGOOnMapDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AddOrEditSGOOnMapDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(AddOrEditSGOOnMapDialog);
    } // setupUi

    void retranslateUi(QDialog *AddOrEditSGOOnMapDialog)
    {
        AddOrEditSGOOnMapDialog->setWindowTitle(QApplication::translate("AddOrEditSGOOnMapDialog", "add/edit static game object on map instance", Q_NULLPTR));
        positionGroupBox->setTitle(QApplication::translate("AddOrEditSGOOnMapDialog", "Position", Q_NULLPTR));
        xPosLbl->setText(QApplication::translate("AddOrEditSGOOnMapDialog", "x", Q_NULLPTR));
        yPosLbl->setText(QApplication::translate("AddOrEditSGOOnMapDialog", "y", Q_NULLPTR));
        zPosLbl->setText(QApplication::translate("AddOrEditSGOOnMapDialog", "z", Q_NULLPTR));
        rotateGroupBox->setTitle(QApplication::translate("AddOrEditSGOOnMapDialog", "Rotate", Q_NULLPTR));
        xRotateLbl->setText(QApplication::translate("AddOrEditSGOOnMapDialog", "x", Q_NULLPTR));
        yRotateLbl->setText(QApplication::translate("AddOrEditSGOOnMapDialog", "y", Q_NULLPTR));
        zRotateLbl->setText(QApplication::translate("AddOrEditSGOOnMapDialog", "z", Q_NULLPTR));
        instanceNameLbl->setText(QApplication::translate("AddOrEditSGOOnMapDialog", "instance name", Q_NULLPTR));
        validationWarningLbl->setText(QApplication::translate("AddOrEditSGOOnMapDialog", "Object with this name already exists", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AddOrEditSGOOnMapDialog: public Ui_AddOrEditSGOOnMapDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDOREDITSGOONMAPDIALOG_H
