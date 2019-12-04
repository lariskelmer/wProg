#ifndef WPROG_H
#define WPROG_H

#include <QMainWindow>

#include <QMainWindow>
#include <QObject>
#include <QFrame>
#include <QLabel>
#include "connectserver.h"
#include "_nova_conversa.h"

namespace Ui {
class wProg;
}

class wProg : public QMainWindow
{
    Q_OBJECT

public:
    explicit wProg(QWidget *parent = 0);
    ~wProg();

signals:
    void interfaceConectada();
    void interfaceDesconectada();
    void RedesenhaConversas();
    void RedesenhaMsgs();
    void MsgErro(QString S);

public slots:
    void slotinterfaceDesconectada();
    void slotinterfaceConectada();
    void slotRedesenhaConversas();
    void slotRedesenhaMsgs();
    void slotMsgErro(QString S);

private slots:
    void on_actionConectar_triggered();

    void on_actionNovaConv_triggered();

    void on_actionDesconectar_triggered();

    void on_actionSair_triggered();

    void on_enviarButton_clicked();

    void on_conversasTable_cellClicked(int row, int column);

    void on_msgEdit_returnPressed();

    void on_actionApagar_triggered();


private:
    Ui::wProg *ui;
    connectServer telaConnect;
    _nova_conversa telaConversa;

    QLabel* ipServidor;
    QLabel* Login;
    QLabel* Corresp;
    bool connected;
};

#endif // WPROG_H
