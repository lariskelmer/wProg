#include "wprog.h"
#include "ui_wprog.h"

wProg::wProg(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::wProg)
{
    ui->setupUi(this);
    // Largura das colunas da tabela de msg e conversas
    ui->msgsTable->setColumnWidth(0,480);
    ui->conversasTable->setColumnWidth(0,50);

    // Cabecalhos da tabela de msg e conversas
    ui->msgsTable->setStyleSheet("QHeaderView::section { background-color:lightgray }");
    ui->msgsTable->setHorizontalHeaderLabels(QStringList() << "Mensagem" << "status");
    ui->conversasTable->setStyleSheet("QHeaderView::section { background-color:lightgray }");
    ui->conversasTable->setHorizontalHeaderLabels(QStringList() << "Lidas" << "Conversas");

    // Status
    ipServidor = new QLabel;
    Login = new QLabel;
    Corresp = new QLabel;
    statusBar()->insertWidget(0,new QLabel("Servidor: "));
    statusBar()->insertWidget(1,ipServidor);
    statusBar()->insertWidget(2,new QLabel("   Login: "));
    statusBar()->insertWidget(3,Login);
    statusBar()->insertWidget(4,new QLabel("   Correspondente: "));
    statusBar()->insertWidget(5,Corresp);

    // Conexões
    connect(this, SIGNAL(interfaceConectada(void)), this, SLOT(slotinterfaceConectada(void)));
    connect(this, SIGNAL(interfaceDesconectada()), this, SLOT(slotinterfaceDesconectada()));
    connect(this, SIGNAL(RedesenhaConversas()), this, SLOT(slotRedesenhaConversas()));
    connect(this, SIGNAL(RedesenhaMsgs()), this, SLOT(slotRedesenhaMsgs()));

    // Coloca a interface no modo desconectado
    slotinterfaceDesconectada();
}

wProg::~wProg()
{
    delete ui;
}

//SETA COMO DEVE SER A INTERFACE DESCONECTADO
void wProg::slotinterfaceDesconectada()
{
    connected = false;
    ui->msgEdit->setEnabled(false);
    ui->enviarButton->setEnabled(false);
    ui->actionApagar->setEnabled(false);
    ui->actionDesconectar->setEnabled(false);
    ui->actionNovaConv->setEnabled(false);

    ui->actionConectar->setEnabled(true);
    ui->conversasTable->clearContents();
    ui->msgsTable->clearContents();
    ipServidor->setText("--");
    Login->setText("--");
    Corresp->setText("--");
    DC.clearConversas();
    DC.clearServidorUsuario();
}

//SETA COMO DEVE SER A INTERFACE CONECTADA
void wProg::slotinterfaceConectada()
{
    connected = true;
    ui->msgEdit->setEnabled(true);
    ui->enviarButton->setEnabled(true);
    ui->actionApagar->setEnabled(true);
    ui->actionDesconectar->setEnabled(true);
    ui->actionNovaConv->setEnabled(true);

    ui->actionConectar->setEnabled(false);

    emit RedesenhaConversas();
    emit RedesenhaMsgs();

    ipServidor->setText(QString::fromStdString(DC.getServidor()));
    Login->setText(QString::fromStdString(DC.getMeuUsuario()));
    Corresp->setText(QString::fromStdString(DC[DC.getIndexConversaAtual()].getCorrespondente()));
}

//DEFAULT INTERFACE
void wProg::slotRedesenhaConversas()
{
    ui->conversasTable->clearContents();
    ui->conversasTable->setRowCount(DC.size());

    for(unsigned i=0; i<DC.size(); i++)
    {
        //Lidas
        QTableWidgetItem *prov;
        prov = new QTableWidgetItem;
        prov->setText(QString::number(DC[i].getNumMsgsEntregues())+"/"+QString::number(DC[i].size()));
        prov->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        if (DC[i].getNumMsgsEntregues()>0) prov->setBackground(QBrush(QColor(200, 255, 200)));
        if ((int)i == DC.getIndexConversaAtual()) prov->setBackground(QBrush(QColor(0, 161, 241)));
        else prov->setBackground(QBrush(QColor(255,255,255)));
        ui->conversasTable->setItem(i,0,prov);

        //Correspondente
        prov = new QTableWidgetItem;
        prov->setText(QString::fromStdString(DC[i].getCorrespondente()));
        prov->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        if (DC[i].getNumMsgsEntregues()>0) prov->setBackground(QBrush(QColor(200, 255, 200)));
        if ((int)i == DC.getIndexConversaAtual()) prov->setBackground(QBrush(QColor(0, 161, 241)));
        else prov->setBackground(QBrush(QColor(255,255,255)));
        ui->conversasTable->setItem(i,1,prov);
    }

}

//DEFAULT SLOT MENSAGEM
void wProg::slotRedesenhaMsgs() // Fazer status
{
    ui->msgsTable->clearContents();
    ui->msgsTable->setRowCount(DC[DC.getIndexConversaAtual()].size());

    int atual = DC.getIndexConversaAtual();
    for(unsigned i=0; i<DC[atual].size(); i++)
    {
        // MENSAGEM
        QTableWidgetItem *prov;
        prov = new QTableWidgetItem;
        prov->setText(QString::fromStdString(DC[atual][i].getTexto()));
        if (DC[atual][i].getRemetente()==DC.getMeuUsuario())
        {
            prov->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
            prov->setBackground(QBrush(QColor(200,255,200)));
        }
        if (DC[atual][i].getRemetente()==DC[atual].getCorrespondente())
        {
            prov->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            prov->setBackground(QBrush(QColor(255,255,255)));
        }
        ui->msgsTable->setItem(i,0,prov);
    }
}

//AÇÕES PARA INICIAR CONEXÃO E CONVERSA
void wProg::on_actionConectar_triggered()
{
    telaConnect.exec();
}

void wProg::on_actionNovaConv_triggered()
{
    telaConversa.exec();
}

//AÇÕES PARA APAGAR E DESCONECTAR
void wProg::on_actionApagar_triggered()
{
    int atual = DC.getIndexConversaAtual();
    if (DC[atual].getCorrespondente()=="" || DC.size()==0)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Erro");
        msgBox.setText("Selecione uma conversa");
        msgBox.exec();
        return;
    }

    else
    {
        DC[atual].clearMessages();
        emit RedesenhaMsgs();
        emit RedesenhaConversas();
    }
}

void wProg::on_actionDesconectar_triggered()
{
    if (connected)
    {
        // Encerra o socket
        MYSOCKET_STATUS iResult;
        iResult = sock.write_int(CMD_LOGOUT_USER);
        if (iResult != SOCKET_ERROR)
        {
            sock.close();

            // Termina a thread inicial
            // Ao fechar o socket, a thread deve se encerrar e liberar os recursos
            // Seta a interface no modo desconectado
            emit interfaceDesconectada();
        }

        else // Erro no envio do comando
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Erro no envio");
            msgBox.setText("Não foi possível enviar o comando de logout");
            msgBox.exec();
        }
    }
    emit interfaceDesconectada();
}

// COMANDO PARA SAIR
void wProg::on_actionSair_triggered()
{
    on_actionDesconectar_triggered();
    QCoreApplication::quit();
}

//COMANDO PARA ENVIAR MENSAGENS
void wProg::on_enviarButton_clicked()
{
    int atual = DC.getIndexConversaAtual();
    if (DC.size()==0 || DC[atual].getCorrespondente()=="")
    {
        //NENHUMA CONVERSA SELECIONADA
        QMessageBox msgBox;
        msgBox.setWindowTitle("Erro");
        msgBox.setText("Antes de enviar alguma mensagem, \n"
                       "adicione uma conversa");
        msgBox.exec();
        if(DC.size()==0) telaConversa.exec();
        return;
    }
    QString remet = QString::fromStdString(DC.getMeuUsuario());
    QString dest = QString::fromStdString(DC[atual].getCorrespondente());
    QString texto = ui->msgEdit->text();
    if (texto.size()>TAM_MAX_MSG || texto.size()==0)
    {
        //ULTRAPASSA O MÁXIMO DE CARACTERES OU NÃO ATINGE O MÍNIMO
        QMessageBox msgBox;
        msgBox.setWindowTitle("Erro");
        msgBox.setText("Mensagem muito grande ou vazia");
        msgBox.exec();
        return;
    }

    Mensagem M;
    M.setRemetente(remet.toStdString());
    M.setDestinatario(dest.toStdString());
    M.setTexto(texto.toStdString());
    M.setId(DC[atual].size()+1);
    M.setStatus(MSG_ENVIADA);

    //ENVIA AO SERVIDOR
    MYSOCKET_STATUS iResult;

    if (connected)
    {
        iResult = sock.write_int(CMD_NOVA_MSG);
        if (iResult != SOCKET_ERROR)
        {
            iResult = sock.write_int(M.getId());
            if(iResult != SOCKET_ERROR)
            {
                iResult = sock.write_string(M.getDestinatario());
                if (iResult != SOCKET_ERROR)
                {
                    iResult = sock.write_string(M.getTexto());
                    if (iResult != SOCKET_ERROR)
                    {
                        DC[atual].pushMessage(M);
                        emit RedesenhaMsgs();
                    }
                    else //MENSAGEM FALHOU
                    {
                        sock.close();
                        emit interfaceDesconectada();

                        QMessageBox msgBox;
                        msgBox.setWindowTitle("Erro no envio");
                        msgBox.setText("Nao foi possivel enviar texto "+texto);
                        msgBox.exec();
                    }
                }
                else //DESTINATÁRIO FALHOU
                {
                    sock.close();
                    emit interfaceDesconectada();

                    QMessageBox msgBox;
                    msgBox.setWindowTitle("Erro no envio");
                    msgBox.setText("Nao foi possivel enviar destinatario"+dest);
                    msgBox.exec();
                }
            }
            else //ERRO DA ID
            {
                sock.close();
                emit interfaceDesconectada();

                QMessageBox msgBox;
                msgBox.setWindowTitle("Erro no envio");
                msgBox.setText("Nao foi possivel enviar id "+
                               QString::number(M.getId())+" da msg");
                msgBox.exec();
            }
        }
        else // CMD erro
        {
            sock.close();
            emit interfaceDesconectada();

            QMessageBox msgBox;
            msgBox.setWindowTitle("Erro");
            msgBox.setText("Erro ao enviar o comando");
            msgBox.exec();
        }
    }
    else //CLIENTE DESCONECTADO
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Erro");
        msgBox.setText("O cliente não está conectado a um servidor");
        msgBox.exec();
    }

    emit RedesenhaConversas();
    ui->msgEdit->clear();
}

//POSSIBILITA ENVIO COM TECLA ENTER
void wProg::on_msgEdit_returnPressed()
{
    QString text = ui->msgEdit->text();
    if (text.size()>0)
    {
        on_enviarButton_clicked();
    }
}

//MEXE NO STATUS DE VISUALIZADO
void wProg::on_conversasTable_cellClicked(int row, int column)
{
    DC.setIndexConversaAtual(row);
    if (column > ui->conversasTable->columnCount()) return;
    Corresp->setText(QString::fromStdString(DC[DC.getIndexConversaAtual()].getCorrespondente()));

    testDestStatus coisa(DC[row].getCorrespondente(), MSG_ENTREGUE);

    itr_Msg itr;
    MYSOCKET_STATUS iResult;
    for (itr=DC[row].begin(); itr!=DC[row].end(); itr++)
    {
        itr = std::find(itr, DC[row].end(), coisa);
        if (itr != DC[row].end())
        {
            DC[row][itr->getId()].setStatus(MSG_LIDA); // GAMBIARRA
            if (connected)
            {
                iResult = sock.write_int(CMD_MSG_LIDA1);
                if (iResult != SOCKET_ERROR)
                {
                    iResult = sock.write_int(itr->getId());
                    if (iResult != SOCKET_ERROR)
                    {
                        iResult = sock.write_string(itr->getRemetente());
                        if (iResult != SOCKET_ERROR)
                        {
                            std::cout << "Mensagem '" << itr->getTexto()
                            << "' informada ao servidor que foi visualida.\n";
                        }
                        else //ERRO NO ENVIO DO REMETENTE
                        {
                            QMessageBox msgBox;
                            msgBox.setWindowTitle("Erro no envio");
                            msgBox.setText("Nao foi possivel enviar remetente"
                                           + QString::fromStdString(itr->getRemetente()));
                            msgBox.exec();
                        }
                    }
                    else //ERRO NO ENVIO DA ID
                    {
                        QMessageBox msgBox;
                        msgBox.setWindowTitle("Erro no envio");
                        msgBox.setText("Nao foi possivel enviar id");
                        msgBox.exec();
                    }
                }
                else //ERRO NO ENVIO DO CMD
                {
                    QMessageBox msgBox;
                    msgBox.setWindowTitle("Erro no envio");
                    msgBox.setText("Nao foi possivel enviar cmd");
                    msgBox.exec();
                }
            }
            else //NÃO CONECTADO
            {
                QMessageBox msgBox;
                msgBox.setWindowTitle("Erro");
                msgBox.setText("Cliente nao conectado!");
                msgBox.exec();
            }
        }
    }

    emit RedesenhaMsgs();
    emit RedesenhaConversas();

}
