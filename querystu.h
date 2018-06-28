#ifndef QUERYSTU_H
#define QUERYSTU_H

#include <QDialog>
#include <QFile>
#include <QList>
#include <QString>
#include <QDebug>
#include <QTextStream>
#include <QMessageBox>
#include <QStringList>
#include <QStandardItem>
#include <QStandardItemModel>


namespace Ui {
class QueryStu;
}

class QueryStu : public QDialog
{
    Q_OBJECT

public:
    explicit QueryStu(QWidget *parent = 0);
    ~QueryStu();
    int readFromFile();
    void queryInfo(int queryIndex, QString queryCnt);
    void display(int row, QStringList stu_info);
    void setHeaderItem();
private slots:
    void on_btn_search_clicked();

private:
    Ui::QueryStu *ui;
    QList<QString> stu_info;
    QStandardItemModel *model;
};

#endif // QUERYSTU_H
