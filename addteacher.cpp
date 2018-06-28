#include "addteacher.h"
#include "ui_addteacher.h"

addTeacher::addTeacher(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addTeacher)
{
    ui->setupUi(this);
}

addTeacher::~addTeacher()
{
    delete ui;
}

void addTeacher::on_bt_confirm_clicked()
{
    QString name = this->ui->le_name->text();
    QString id = this->ui->le_id->text();
    QString pwd = this->ui->le_pwd->text();
    QString college = this->ui->cbb_college->currentText();

   QString error;
    if(name.length() < 1 || id.length() < 6){
        QMessageBox::critical(this, "错误", "信息填写不完整", "确定");
    }else{
        QString content = name + " " + id + " " + pwd + " " + college + "\n";
        int ret = QMessageBox::question(this, "请确认信息",  content, "Save", "Cancel");
        if(ret == 0){
            writeToFile(content);
            QMessageBox::about(this, "提示", "信息保存成功");
            clearUserInterface();
        }
    }
}

void addTeacher::clearUserInterface()
{
    this->ui->le_name->clear();
    this->ui->le_id->clear();
    this->ui->le_pwd->clear();
    this->ui->rbtn_male->setChecked(true);    // 选中男生
    this->ui->cbb_college->setCurrentIndex(0);
    this->ui->le_name->setFocus();    // 光标移到名字上
}

void addTeacher::writeToFile(QString content)
{
    QFile file("teacher.txt");
    if(! file.open(QIODevice::Append | QIODevice::Text)){
        QMessageBox::critical(this, "错误", "文件打开失败,信息没有保存", "确认");
        return;
    }
    QTextStream out(&file);
    out << content;
    file.close();
}

void addTeacher::on_bt_cancle_clicked()
{
    this->close();
}
