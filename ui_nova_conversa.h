/********************************************************************************
** Form generated from reading UI file '_nova_conversa.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOVA_CONVERSA_H
#define UI_NOVA_CONVERSA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_nova_conversa
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *labelNovaconv;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *labelConv;
    QLineEdit *CorrespEdit;

    void setupUi(QDialog *_nova_conversa)
    {
        if (_nova_conversa->objectName().isEmpty())
            _nova_conversa->setObjectName(QStringLiteral("_nova_conversa"));
        _nova_conversa->resize(280, 180);
        buttonBox = new QDialogButtonBox(_nova_conversa);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(0, 120, 221, 41));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        labelNovaconv = new QLabel(_nova_conversa);
        labelNovaconv->setObjectName(QStringLiteral("labelNovaconv"));
        labelNovaconv->setGeometry(QRect(100, 30, 101, 16));
        widget = new QWidget(_nova_conversa);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 70, 261, 22));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        labelConv = new QLabel(widget);
        labelConv->setObjectName(QStringLiteral("labelConv"));

        horizontalLayout->addWidget(labelConv);

        CorrespEdit = new QLineEdit(widget);
        CorrespEdit->setObjectName(QStringLiteral("CorrespEdit"));

        horizontalLayout->addWidget(CorrespEdit);


        retranslateUi(_nova_conversa);
        QObject::connect(buttonBox, SIGNAL(accepted()), _nova_conversa, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), _nova_conversa, SLOT(reject()));

        QMetaObject::connectSlotsByName(_nova_conversa);
    } // setupUi

    void retranslateUi(QDialog *_nova_conversa)
    {
        _nova_conversa->setWindowTitle(QApplication::translate("_nova_conversa", "Nova Conversa", 0));
        labelNovaconv->setText(QApplication::translate("_nova_conversa", "NOVA CONVERSA", 0));
        labelConv->setText(QApplication::translate("_nova_conversa", "Correspondente:", 0));
    } // retranslateUi

};

namespace Ui {
    class _nova_conversa: public Ui_nova_conversa {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOVA_CONVERSA_H
