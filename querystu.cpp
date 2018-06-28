#include "querystu.h"
#include "ui_querystu.h"


QueryStu::QueryStu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QueryStu)
{
    ui->setupUi(this);
    if(readFromFile() == -1){
        QMessageBox::critical(this, "严重错误", "文件打开失败,请重试");
        this->close();
    }

    this->model = new QStandardItemModel();    // new一个表格
    setHeaderItem();    // 设置表头
}

QueryStu::~QueryStu()
{
    delete ui;
}

int QueryStu::readFromFile()
{
    QFile file("student.txt");
    if(! file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return -1;    // 打开文件失败
    }

    QTextStream in(&file);

    while(!in.atEnd()){
        QString line = in.readLine();
        stu_info.append(line);
    }
    file.close();

    return 0;    // 打开文件成功
}

void QueryStu::on_btn_search_clicked()
{
    this->model->clear();    // 每次查询之前先清除
    setHeaderItem();    // 重新设置表头
    int queryIndex = this->ui->cbb_method->currentIndex();    // 获取当前选择的查询方式的下标
    QString queryContent = this->ui->le_content->text();
    queryInfo(queryIndex, queryContent);
}

void QueryStu::queryInfo(int queryIndex, QString queryCnt)
{
    int row = 0;
    for(int i = 0; i < stu_info.length(); i++)
    {
        QString line = stu_info.at(i);
        QStringList info_list = line.split(" ");    // 按空格分隔
        // 按queryIndex查询 queryIndex是以1开始的
        if(queryIndex != 0){
            if(info_list[queryIndex-1] == queryCnt)
            {
                display(row++, info_list);
            }
        }
    }
}


void QueryStu::display(int row, QStringList stu_info)
{
    for(int i = 0; i < stu_info.length(); i++)
    {
        this->model->setItem(row, i, new QStandardItem(stu_info.at(i)));
    }
}

void QueryStu::setHeaderItem()
{
    // 设置表头
    this->model->setHorizontalHeaderItem(0, new QStandardItem("姓名"));    // 第0列显示姓名
    this->model->setHorizontalHeaderItem(1, new QStandardItem("学号"));
    this->model->setHorizontalHeaderItem(2, new QStandardItem("密码"));
    this->model->setHorizontalHeaderItem(3, new QStandardItem("性别"));
    this->model->setHorizontalHeaderItem(4, new QStandardItem("学院"));
    this->model->setHorizontalHeaderItem(5, new QStandardItem("班级"));

    // 将表格添加到tableView中
    this->ui->tableView->setModel(model);
    // 调整表格的每列的宽度
    this->ui->tableView->setColumnWidth(0, 80);
    this->ui->tableView->setColumnWidth(1, 150);
    this->ui->tableView->setColumnWidth(2, 80);
    this->ui->tableView->setColumnWidth(3, 150);
    this->ui->tableView->setColumnWidth(4, 150);
    this->ui->tableView->setColumnWidth(4, 150);
}
