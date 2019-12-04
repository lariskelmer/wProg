#ifndef _NOVA_CONVERSA_H
#define _NOVA_CONVERSA_H

#include <QDialog>

namespace Ui {
class _nova_conversa;
}


class _nova_conversa : public QDialog
{
    Q_OBJECT

public:
    explicit _nova_conversa(QWidget *parent = 0);
    ~_nova_conversa();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::_nova_conversa *ui;
};


#endif // _NOVA_CONVERSA_H
