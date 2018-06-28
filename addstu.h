#ifndef ADDSTU_H
#define ADDSTU_H

#include <QDialog>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QPushButton>
#include <QCheckBox>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QList>

namespace Ui {
class addStu;
}

class addStu : public QDialog
{
    Q_OBJECT

public:
    explicit addStu(QWidget *parent = 0);
    ~addStu();
    void clearUserInterface();
    void writeToFile(QString content);

private slots:
    void on_bt_confirm_clicked();    
    void on_bt_cancle_clicked();

    void on_cbb_college_currentIndexChanged(int index);

private:
    Ui::addStu *ui;
};

#endif // ADDSTU_H
