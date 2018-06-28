#include "teacherlogin.h"
#include "ui_teacherlogin.h"

teacherLogin::teacherLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::teacherLogin)
{
    ui->setupUi(this);

    this->ui->cbb_course->hide();
    this->ui->cbb_students_list->hide();
    this->ui->le_score->hide();
    this->ui->btn_submit->hide();
    this->ui->label_select_course->hide();
    this->ui->label_select_student->hide();
    this->ui->label_score->hide();
    this->ui->btn_save->hide();

    if(readFromFile("teacher.txt") == -1){
        QMessageBox::critical(this, "严重错误", "文件打开失败,请重试");
        this->close();
    }
    if(readFromFile("course.txt") == -1){
        QMessageBox::critical(this, "严重错误", "文件打开失败,请重试");
        this->close();
    }
    if(readFromFile("scores.txt") == -1){
        QMessageBox::critical(this, "严重错误", "文件打开失败,请重试");
        this->close();
    }
}

teacherLogin::~teacherLogin()
{
    delete ui;
}

void teacherLogin::on_btn_login_clicked()
{
    QString teacher_name;
    bool is_login = false;
    QString id = this->ui->le_id->text();
    QString pwd = this->ui->le_pwd->text();
    for(int i = 0; i < teacher_info.length(); i++)
    {
        QString line = teacher_info.at(i);
        QStringList info_list = line.split(" ");    // 按空格分隔
        if(info_list[1] == id && info_list[2] == pwd)
        {
            teacher_name = info_list[0];
            is_login = true;
            break;
        }
    }
    if(is_login)
    {
        QMessageBox::about(this, "登录提示", "登陆成功");
        this->ui->cbb_course->show();
        this->ui->cbb_students_list->show();
        this->ui->le_score->show();
        this->ui->btn_submit->show();
        this->ui->label_select_course->show();
        this->ui->label_select_student->show();
        this->ui->label_score->show();
        this->ui->btn_save->show();
        QStringList list;    // 下拉框中老师的所有课程
        for(int i = 0; i < course_info.length(); i++)
        {
            QString line = course_info.at(i);
            QStringList info_list = line.split(" ");    // 按空格分隔
            if(info_list[6] == teacher_name)    // 根据课程的任课老师的名字来查询老师的所有课程
            {
                list<<line;
            }
            this->ui->cbb_course->clear();
            this->ui->cbb_course->addItems(list);
        }
    }
    else
    {
        QMessageBox::critical(this, "登录失败", "工号或者密码错误!", "确定");
    }
}

int teacherLogin::readFromFile(QString file_name)
{
    QFile file(file_name);
    if(! file.open(QIODevice::ReadWrite | QIODevice::Text)){
        return -1;    // 打开文件失败
    }

    QTextStream in(&file);

    if(file_name == "teacher.txt") {
        while(!in.atEnd()){
        QString line = in.readLine();
        teacher_info.append(line);
        }
    } else if(file_name == "scores.txt"){
        while(!in.atEnd()){
        QString line = in.readLine();
        student_info.append(line);
        }
    } else if(file_name == "course.txt"){
        while(!in.atEnd()){
        QString line = in.readLine();
        course_info.append(line);
        }
    } else {

    }
    file.close();

    return 0;    // 打开文件成功
}

void teacherLogin::on_cbb_course_currentIndexChanged(int index)
{
    this->ui->cbb_students_list->clear();
    QStringList current_course = this->ui->cbb_course->currentText().split(" ");    // 按空格分隔
    QString course_num = current_course[0];

    QStringList list;
    for(int i = 0; i < student_info.length(); i++)
    {
        QString line = student_info.at(i);
        QStringList info_list = line.split(" ");
        if(info_list[1] == course_num)
        {
            list<<info_list[0];    // 将选了这门课的学生的学号加进去
        }
    }
    this->ui->cbb_students_list->addItems(list);
}

void teacherLogin::on_btn_submit_clicked()
{
    QString stu_id = this->ui->cbb_students_list->currentText();    // 学生id
    QStringList list = this->ui->cbb_course->currentText().split(" ");
    QString course_id = list[list.length()-1];    // 课程id是课程描述中的最后一个
    QString score = this->ui->le_score->text();
    for(int i = 0; i < student_info.length(); i++)
    {
        QString line = student_info.at(i);
        QStringList info_list = line.split(" ");
        if(info_list[0] == stu_id && info_list[info_list.length()-1-1] == course_id)
        {

            student_info.replace(i, student_info.at(i) + " " + score);
            qDebug()<<student_info.at(i);
        }
    }
}

void teacherLogin::on_btn_save_clicked()
{
    QString content;
    for(int i =0; i < student_info.length(); i++)
    {
        content = content + student_info.at(i) + "\n";
    }
    QFile file("scores.txt");
    if(! file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::critical(this, "Error", "文件打开失败,信息没有保存", "确认");
        return;
    }
    QTextStream out(&file);
    out <<content;
    file.close();
    QMessageBox::about(this, "提示", "分数提交成功");
}
