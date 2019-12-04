#ifndef UI_WPROG_H
#define UI_WPROG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_wProg
{
public:
    QAction *actionConectar;
    QAction *actionDesconectar;
    QAction *actionSair;
    QAction *actionNovaConv;
    QAction *actionApagar;
    QWidget *centralWidget;
    QLabel *msgLabel;
    QLineEdit *msgEdit;
    QPushButton *enviarButton;
    QTableWidget *conversasTable;
    QTableWidget *msgsTable;
    QMenuBar *menuBar;
    QMenu *menuConex_o;
    QMenu *menuConversas;
    QMenu *menuMensagens;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *wProg)
    {
        if (wProg->objectName().isEmpty())
            wProg->setObjectName(QStringLiteral("wProg"));
        wProg->resize(800, 600);
        actionConectar = new QAction(wProg);
        actionConectar->setObjectName(QStringLiteral("actionConectar"));
        actionDesconectar = new QAction(wProg);
        actionDesconectar->setObjectName(QStringLiteral("actionDesconectar"));
        actionSair = new QAction(wProg);
        actionSair->setObjectName(QStringLiteral("actionSair"));
        actionNovaConv = new QAction(wProg);
        actionNovaConv->setObjectName(QStringLiteral("actionNovaConv"));
        actionApagar = new QAction(wProg);
        actionApagar->setObjectName(QStringLiteral("actionApagar"));
        centralWidget = new QWidget(wProg);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        msgLabel = new QLabel(centralWidget);
        msgLabel->setObjectName(QStringLiteral("msgLabel"));
        msgLabel->setGeometry(QRect(10, 530, 59, 16));
        msgEdit = new QLineEdit(centralWidget);
        msgEdit->setObjectName(QStringLiteral("msgEdit"));
        msgEdit->setGeometry(QRect(70, 530, 640, 20));
        enviarButton = new QPushButton(centralWidget);
        enviarButton->setObjectName(QStringLiteral("enviarButton"));
        enviarButton->setGeometry(QRect(720, 527, 70, 25));
        conversasTable = new QTableWidget(centralWidget);
        if (conversasTable->columnCount() < 2)
            conversasTable->setColumnCount(2);
        conversasTable->setObjectName(QStringLiteral("conversasTable"));
        conversasTable->setGeometry(QRect(10, 10, 240, 510));
        conversasTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        conversasTable->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        conversasTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        conversasTable->setTabKeyNavigation(false);
        conversasTable->setAlternatingRowColors(true);
        conversasTable->setSelectionMode(QAbstractItemView::NoSelection);
        conversasTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        conversasTable->setColumnCount(2);
        conversasTable->horizontalHeader()->setDefaultSectionSize(50);
        conversasTable->horizontalHeader()->setMinimumSectionSize(50);
        conversasTable->horizontalHeader()->setStretchLastSection(true);
        conversasTable->verticalHeader()->setVisible(false);
        msgsTable = new QTableWidget(centralWidget);
        if (msgsTable->columnCount() < 2)
            msgsTable->setColumnCount(2);
        msgsTable->setObjectName(QStringLiteral("msgsTable"));
        msgsTable->setGeometry(QRect(260, 10, 530, 510));
        msgsTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        msgsTable->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        msgsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        msgsTable->setTabKeyNavigation(false);
        msgsTable->setSelectionMode(QAbstractItemView::NoSelection);
        msgsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        msgsTable->setColumnCount(2);
        msgsTable->horizontalHeader()->setCascadingSectionResizes(false);
        msgsTable->horizontalHeader()->setMinimumSectionSize(50);
        msgsTable->horizontalHeader()->setStretchLastSection(true);
        msgsTable->verticalHeader()->setVisible(false);
        wProg->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(wProg);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        menuConex_o = new QMenu(menuBar);
        menuConex_o->setObjectName(QStringLiteral("menuConex_o"));
        menuConversas = new QMenu(menuBar);
        menuConversas->setObjectName(QStringLiteral("menuConversas"));
        menuMensagens = new QMenu(menuBar);
        menuMensagens->setObjectName(QStringLiteral("menuMensagens"));
        wProg->setMenuBar(menuBar);
        statusBar = new QStatusBar(wProg);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        wProg->setStatusBar(statusBar);

        menuBar->addAction(menuConex_o->menuAction());
        menuBar->addAction(menuConversas->menuAction());
        menuBar->addAction(menuMensagens->menuAction());
        menuConex_o->addAction(actionConectar);
        menuConex_o->addAction(actionDesconectar);
        menuConex_o->addSeparator();
        menuConex_o->addAction(actionSair);
        menuConversas->addAction(actionNovaConv);
        menuMensagens->addAction(actionApagar);

        retranslateUi(wProg);

        QMetaObject::connectSlotsByName(wProg);
    } // setupUi

    void retranslateUi(QMainWindow *wProg)
    {
        wProg->setWindowTitle(QApplication::translate("wProg", "Cliente wProg", 0));
        actionConectar->setText(QApplication::translate("wProg", "Conectar...", 0));
        actionDesconectar->setText(QApplication::translate("wProg", "Desconectar", 0));
        actionSair->setText(QApplication::translate("wProg", "Sair", 0));
        actionNovaConv->setText(QApplication::translate("wProg", "Nova Conversa...", 0));
        actionApagar->setText(QApplication::translate("wProg", "Apagar", 0));
        msgLabel->setText(QApplication::translate("wProg", "MENSAGEM:", 0));
        enviarButton->setText(QApplication::translate("wProg", "ENVIAR", 0));
        menuConex_o->setTitle(QApplication::translate("wProg", "Conex\303\243o", 0));
        menuConversas->setTitle(QApplication::translate("wProg", "Conversas", 0));
        menuMensagens->setTitle(QApplication::translate("wProg", "Mensagens", 0));
    } // retranslateUi

};

namespace Ui {
    class wProg: public Ui_wProg{};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WPROG_H
