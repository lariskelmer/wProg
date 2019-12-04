#include "_nova_conversa.h"

#include "ui_nova_conversa.h"
#include <string>
#include "wprog.h"
#include "mysocket.h"
#include "dados_cliente.h"
#include "dados_whatsprog.h"
#include <QMessageBox>

extern tcp_mysocket sock;
extern HANDLE th_id;
extern wProg* pt_w;
extern DadosCliente DC;

using namespace std;

_nova_conversa::_nova_conversa(QWidget *parent)
{
    QDialog(parent),
    ui(new Ui::_nova_conversa)
{
    ui->setupUi(this);
}


_nova_conversa::~_nova_conversa()
{
    delete ui;
}

void _nova_conversa::on_buttonBox_accepted()
{
    QString dest = ui->CorrespEdit->text();
    if(dest.size()<TAM_MIN_NOME_USUARIO || dest.size()>TAM_MAX_NOME_USUARIO)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Erro");
        msgBox.setText("Nome de correspondente muito grande ou pequeno");
        msgBox.exec();
    }
    else
    {
        if (DC.insertConversa(dest.toStdString()))
        {
            emit pt_w->RedesenhaConversas();
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Erro");
            msgBox.setText("Não foi possivel inserir nova conversa");
            msgBox.exec();
        }
    }
}
