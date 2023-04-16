#ifndef MINISCADA_H
#define MINISCADA_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MiniScada; }
QT_END_NAMESPACE

class MiniScada : public QMainWindow
{
    Q_OBJECT

public:
    MiniScada(QWidget *parent = nullptr);
    ~MiniScada();

private:
    Ui::MiniScada *ui;
};
#endif // MINISCADA_H
