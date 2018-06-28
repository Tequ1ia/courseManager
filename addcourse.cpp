#include "addcourse.h"
#include "ui_addcourse.h"

addCourse::addCourse(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addCourse)
{
    ui->setupUi(this);
}

addCourse::~addCourse()
{
    delete ui;
}

void addCourse::on_btn_confirm_clicked()
{
    QString course_name = this->ui->le_course_name->text();    // 课程名字
    QString course_type = this->ui->cbb_course_type->currentText();    // 课程类别
    QString course_term = this->ui->cbb_term->currentText();    // 建议修读学期
    QString course_day = this->ui->cbb_course_day->currentText();    // 星期几
    QString course_time = this->ui->cbb_course_time->currentText();    // 第几节
    QString course_teacher = this->ui->le_teacher->text();    // 任课教师
    QString course_location = this->ui->le_location->text();    // 上课地点
    QString course_stu_number = this->ui->le_num->text();    // 容量
    QString course_credit = this->ui->le_credit->text();    // 学分
    QString content = course_name + " " + course_type + " " + course_term + " " +
            course_day + " " + course_time + " " + course_teacher + " " + course_location + " " + course_stu_number + " " + course_credit + "\n";
    int ret = QMessageBox::question(this, "请确认信息",  content, "Save", "Cancel");
    if(ret == 0){
        if(writeToFile(content))     // 如果写入文件成功
        {
            QMessageBox::about(this, "提示", "信息保存成功");
        }
        else
        {
            QMessageBox::critical(this, "警告", "写入文件失败!");
        }
        clearUserInterface();
    } else {
        this->close();
    }

}

bool addCourse::writeToFile(QString content)
{
    int course_num = get_primary_key();    // 获取当前的课程总数
    QFile file("course.txt");
    if(! file.open(QIODevice::Append | QIODevice::Text)){
        QMessageBox::critical(this, "Error", "文件打开失败,信息没有保存", "确认");
        return false;
    }
    QTextStream out(&file);

    out << course_num+1 << " " << content;
    file.close();
    return true;
}

void addCourse::clearUserInterface()
{
    this->ui->le_course_name->clear();
    this->ui->cbb_course_type->setCurrentIndex(0);
    this->ui->cbb_term->setCurrentIndex(0);
    this->ui->cbb_course_day->setCurrentIndex(0);
    this->ui->cbb_course_time->setCurrentIndex(0);
    this->ui->le_teacher->clear();
    this->ui->le_location->clear();
    this->ui->le_num->clear();
    this->ui->le_credit->clear();
    this->ui->le_course_name->setFocus();
}

void addCourse::on_btn_cancel_clicked()
{
    clearUserInterface();
}

int addCourse::get_primary_key()
{
    QStringList courses_info;
    QFile file("course.txt");
    if(! file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::critical(this, "Error", "文件打开失败,无法读取信息", "确认");
        return -1;
    }
    QTextStream in(&file);

    while(!in.atEnd()){
        QString line = in.readLine();
        courses_info.append(line);
    }
    file.close();
    bool ok;
    int num = courses_info.at(courses_info.length()-1).split(" ")[0].toInt(&ok, 10);
    return num;    // 返回目前的课程总数
}
