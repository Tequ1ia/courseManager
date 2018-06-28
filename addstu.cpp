#include "addstu.h"
#include "ui_addstu.h"

addStu::addStu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addStu)
{
    ui->setupUi(this);

}

addStu::~addStu()
{
    delete ui;
}

void addStu::on_bt_confirm_clicked()
{
    QString name = this->ui->le_name->text();
    QString id = this->ui->le_id->text();
    QString pwd = this->ui->le_pwd->text();
    QString sex;
    if(this->ui->rbtn_male->isChecked())
       sex = "male";
    else
        sex = "female";
    QString college = this->ui->cbb_college->currentText();
    QString class_  = this->ui->cbb_class->currentText();

    qDebug() << name << id << pwd << sex << college << class_ << "\n";

    if(name.length() < 1 || id.length() < 13){
        QMessageBox::critical(this, "错误", "信息填写不完整", "确定");
    }else{
        QString content = name + " " + id + " " + pwd + " " + sex + " " + college + " " + class_  + "\n";
        int ret = QMessageBox::question(this, "请确认信息",  content, "Save", "Cancel");
        if(ret == 0){
            writeToFile(content);
            QMessageBox::about(this, "提示", "保存成功");
            clearUserInterface();
        }
    }
}

void addStu::clearUserInterface()
{
    this->ui->le_name->clear();
    this->ui->le_id->clear();
    this->ui->le_pwd->clear();
    this->ui->rbtn_male->setChecked(true);    // 默认选中男生
    this->ui->cbb_college->setCurrentIndex(0);
    this->ui->cbb_class->setCurrentIndex(0);
//    QList<QAbstractButton *> courses_list = this->ui->buttonGroup->buttons();
//    for(int i = 0; i < courses_list.length(); i++)
//    {
//        courses_list.at(i)->setChecked(false);
//    }
//    this->ui->le_name->setFocus();

}

void addStu::writeToFile(QString content)
{
    QFile file("student.txt");
    if(! file.open(QIODevice::Append | QIODevice::Text)){
        QMessageBox::critical(this, "Error", "文件打开失败,信息没有保存", "确认");
        return;
    }
    QTextStream out(&file);
    out << content;
    file.close();
}

void addStu::on_bt_cancle_clicked()
{
    this->close();
}

void addStu::on_cbb_college_currentIndexChanged(int index)
{
    QStringList list;
    switch (index) {
    case 1:
        this->ui->cbb_class->clear();
        list<<"计算机类17(1)"<<"计算机类17(2)"<<"计算机类17(3)"<<"计算机类17(4)"<<"计算机类17(5)"<<"计算机全英文17(1)";
        this->ui->cbb_class->addItems(list);
        break;
    case 2:
        this->ui->cbb_class->clear();
        list<<"英语17(1)"<<"英语17(2)"<<"日语17(1)"<<"日语17(2)";
        this->ui->cbb_class->addItems(list);
        break;
    default:
        this->ui->cbb_class->clear();
        break;
    }
}
