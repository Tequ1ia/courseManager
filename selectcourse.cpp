#include "selectcourse.h"
#include "ui_selectcourse.h"

selectCourse::selectCourse(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::selectCourse)
{
    ui->setupUi(this);
    this->ui->cbb_course_type->hide();    // 隐藏
    this->ui->cbb_course_list->hide();
    this->ui->label_coure_type->hide();
    this->ui->label_coure_list->hide();
    this->ui->tableView->hide();
    this->ui->btn_add_course->hide();
    this->ui->btn_delete_course->hide();
    this->ui->label_show_courses->hide();
    this->ui->btn_submit->hide();
    this->ui->tableView_courses->hide();
    this->ui->tableView_scores->hide();
    this->ui->lb_average->hide();
    this->ui->lb_average_display->hide();
    this->ui->label_weighted_average->hide();
    this->ui->lb_weighted_average_display->hide();
    this->ui->btn_login->setFocus();

    if(readFromFile("student.txt") == -1){
        QMessageBox::critical(this, "严重错误", "文件打开失败,请重试");
        this->close();
    }
    if(readFromFile("course.txt") == -1){
        QMessageBox::critical(this, "严重错误", "文件打开失败,请重试");
        this->close();
    }

    this->model = new QStandardItemModel();    // new一个表格
    this->model_courses = new QStandardItemModel();    // new一个打印课程表的表格
    this->model_scores = new QStandardItemModel();    // new一个打印成绩的表格

    setHeaderItem();    // 设置表头
}

selectCourse::~selectCourse()
{
    delete ui;
}

void selectCourse::on_btn_login_clicked()
{
    QString stu_name;
    bool is_login = false;
    QString id = this->ui->le_id->text();
    QString pwd = this->ui->le_pwd->text();
    for(int i = 0; i < stu_info.length(); i++)
    {
        QString line = stu_info.at(i);
        QStringList info_list = line.split(" ");    // 按空格分隔
        if(info_list[1] == id && info_list[2] == pwd)
        {
            stu_name = info_list[0];
            is_login = true;
            break;
        }
    }
    if(is_login)
    {
        if(readFromFile("scores.txt") == -1){
            QMessageBox::critical(this, "严重错误", "文件打开失败,请重试");
            this->close();
        }
        QMessageBox::about(this, "登录提示", "登陆成功");
        this->ui->cbb_course_type->show();
        this->ui->cbb_course_list->show();
        this->ui->label_coure_type->show();
        this->ui->label_coure_list->show();
        this->ui->tableView->show();
        this->ui->btn_add_course->show();
        this->ui->btn_delete_course->show();
        this->ui->btn_submit->show();
        this->ui->label_welcome->setText("你好," + stu_name + "同学! 欢迎使用学生选课系统!");
        // 隐藏登陆界面
        this->ui->label_id->hide();
        this->ui->label_pwd->hide();
        this->ui->le_id->hide();
        this->ui->le_pwd->hide();
        this->ui->btn_login->hide();
        display();    // 显示已经选择了的课程
    }
    else
    {
        QMessageBox::critical(this, "登录失败", "学号或者密码错误!", "确定");
    }

}

int selectCourse::readFromFile(QString file_name)
{
    QFile file(file_name);
    if(! file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return -1;    // 打开文件失败
    }

    QTextStream in(&file);

    if(file_name == "student.txt") {
        while(!in.atEnd()){
            QString line = in.readLine();
            stu_info.append(line);
        }
    } else if(file_name == "course.txt"){
        while(!in.atEnd()){
            QString line = in.readLine();
            course_info.append(line);
        }
    } else if(file_name == "scores.txt") {
        while(!in.atEnd()){
            QString line = in.readLine();
            total_selected_courses.insert(line);
            if(line.split(" ")[0] == this->ui->le_id->text()){
                selected_courses.append(line);
                total_selected_courses.remove(line);
            }
        }
    } else {

    }
    file.close();

    return 0;    // 打开文件成功
}


// 无bug
void selectCourse::on_cbb_course_type_currentIndexChanged(int index)
{
    QStringList list;
    switch (index) {
    case 1:
        this->ui->cbb_course_list->clear();
        for(int i = 0; i < course_info.length(); i++)
        {
            QString line = course_info.at(i);
            QStringList info_list = line.split(" ");    // 按空格分隔
            if(info_list[2] == "必修理论课程")
            {
                list<<line;
            }
        }
        break;
    case 2:
        this->ui->cbb_course_list->clear();
        for(int i = 0; i < course_info.length(); i++)
        {
            QString line = course_info.at(i);
            QStringList info_list = line.split(" ");    // 按空格分隔
            if(info_list[2] == "选修理论课程")
            {
                list<<line;
            }
        }
        break;
    case 3:
        this->ui->cbb_course_list->clear();
        for(int i = 0; i < course_info.length(); i++)
        {
            QString line = course_info.at(i);
            QStringList info_list = line.split(" ");    // 按空格分隔
            if(info_list[2] == "实验课程")
            {
                list<<line;
            }
        }
        break;
    case 4:
        this->ui->cbb_course_list->clear();
        for(int i = 0; i < course_info.length(); i++)
        {
            QString line = course_info.at(i);
            QStringList info_list = line.split(" ");    // 按空格分隔
            if(info_list[2] == "体育课程")
            {
                list<<line;
            }
        }
        break;
    default:
        this->ui->cbb_course_list->clear();
        break;
    }
    this->ui->cbb_course_list->addItems(list);    // 添加选好课程类别下的课程
}

void selectCourse::on_btn_add_course_clicked()
{
    this->model->clear();    // 每次查询之前先清除
    setHeaderItem();    // 重新设置表头
    QString added_course = this->ui->le_id->text() + " " + this->ui->cbb_course_list->currentText();
    for(int i = 0; i < selected_courses.length(); i++)
    {
        if(added_course.split(" ")[2] == selected_courses.at(i).split(" ")[2])
        {
            QMessageBox::critical(this, "错误", "不能重复添加同一类课程或者同一门课程!");
            display();
            return;
        }
    }
    selected_courses.append(added_course);
    display();
}

void selectCourse::on_btn_delete_course_clicked()
{
    this->model->clear();    // 每次查询之前先清除
    setHeaderItem();    // 重新设置表头
    QString deleted_course = this->ui->le_id->text() + " " + this->ui->cbb_course_list->currentText();
    selected_courses.removeOne(deleted_course);
    total_selected_courses.remove(deleted_course);
    display();
}


void selectCourse::setHeaderItem()
{
    // 设置表头
    this->model->setHorizontalHeaderItem(0, new QStandardItem("课程编号"));    // 第0列显示课程编号
    this->model->setHorizontalHeaderItem(1, new QStandardItem("课程名称"));
    this->model->setHorizontalHeaderItem(2, new QStandardItem("课程类别"));
    this->model->setHorizontalHeaderItem(3, new QStandardItem("建议修读学期"));
    this->model->setHorizontalHeaderItem(4, new QStandardItem("星期几"));
    this->model->setHorizontalHeaderItem(5, new QStandardItem("节数"));
    this->model->setHorizontalHeaderItem(6, new QStandardItem("任课老师"));
    this->model->setHorizontalHeaderItem(7, new QStandardItem("上课地点"));
    this->model->setHorizontalHeaderItem(8, new QStandardItem("课程容量"));
    this->model->setHorizontalHeaderItem(9, new QStandardItem("学分"));

    // 将表格添加到tableView中
    this->ui->tableView->setModel(model);
    // 调整表格的每列的宽度
    this->ui->tableView->setColumnWidth(0, 150);
    this->ui->tableView->setColumnWidth(1, 150);
    this->ui->tableView->setColumnWidth(2, 150);
    this->ui->tableView->setColumnWidth(3, 150);
    this->ui->tableView->setColumnWidth(4, 150);
    this->ui->tableView->setColumnWidth(5, 150);
    this->ui->tableView->setColumnWidth(6, 150);
    this->ui->tableView->setColumnWidth(7, 150);
    this->ui->tableView->setColumnWidth(8, 150);
    this->ui->tableView->setColumnWidth(9, 150);
}

void selectCourse::display()
{
    // 显示已经选择的课程信息
    int row = 0;
    for(int i = 0; i < selected_courses.length(); i++)
    {
        QString line = selected_courses.at(i);
        QStringList info_list = line.split(" ");    // 按空格分隔
        for(int j = 0; j < info_list.length()-1; j++)
        {
            this->model->setItem(row, j, new QStandardItem(info_list.at(j+1)));
        }
        row++;
    }
}


void selectCourse::on_btn_submit_clicked()
{
    for(int i = 0; i < selected_courses.length(); i++)
    {
        total_selected_courses.insert(selected_courses.at(i));
    }
    QString content;    // 将选的课程写入到txt中
    for(QSet<QString>::iterator i = total_selected_courses.begin(); i != total_selected_courses.end(); i++)
    {
        content = content + *(i) + "\n";
    }
    QFile file("scores.txt");
    if(! file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::critical(this, "Error", "文件打开失败,信息没有保存", "确认");
        return;
    }
    QTextStream out(&file);
    out << content;
    file.close();
    QMessageBox::about(this, "提示", "提交内容成功");
}

void selectCourse::on_btn_query_clicked()
{
    this->ui->tableView_courses->show();
    QString term = this->ui->cbb_term->currentText();
    // 设置表头
    this->model_courses->setHorizontalHeaderItem(0, new QStandardItem("课程名称"));    // 第0列显示课程编号
    this->model_courses->setHorizontalHeaderItem(1, new QStandardItem("星期几"));
    this->model_courses->setHorizontalHeaderItem(2, new QStandardItem("第几节"));
    this->model_courses->setHorizontalHeaderItem(3, new QStandardItem("任课教师"));
    this->model_courses->setHorizontalHeaderItem(4, new QStandardItem("上课地点"));
    this->model_courses->setHorizontalHeaderItem(5, new QStandardItem("学分"));

    // 将表格添加到tableView_courses中
    this->ui->tableView_courses->setModel(model_courses);
    // 调整表格的每列的宽度
    this->ui->tableView_courses->setColumnWidth(0, 150);
    this->ui->tableView_courses->setColumnWidth(1, 150);
    this->ui->tableView_courses->setColumnWidth(2, 150);
    this->ui->tableView_courses->setColumnWidth(3, 150);
    this->ui->tableView_courses->setColumnWidth(4, 150);
    this->ui->tableView_courses->setColumnWidth(5, 150);


    // 显示已经选择的课程信息
    int row = 0;
    for(int i = 0; i < selected_courses.length(); i++)
    {
        QString line = selected_courses.at(i);
        QStringList info_list = line.split(" ");
        if(info_list[4] == term)
        {
            this->model_courses->setItem(row, 0, new QStandardItem(info_list.at(2)));    // 课程名称
            this->model_courses->setItem(row, 1, new QStandardItem(info_list.at(5)));    // 星期几
            this->model_courses->setItem(row, 2, new QStandardItem(info_list.at(6)));    // 第几节
            this->model_courses->setItem(row, 3, new QStandardItem(info_list.at(7)));    // 任课教师
            this->model_courses->setItem(row, 4, new QStandardItem(info_list.at(8)));    // 上课地点
            this->model_courses->setItem(row, 5, new QStandardItem(info_list.at(10)));    // 学分
            row++;
        }
    }
}


void selectCourse::on_btn_query_scores_clicked()
{
    this->ui->tableView_scores->show();
    this->ui->lb_average->show();
    this->ui->lb_average_display->show();
    this->ui->label_weighted_average->show();
    this->ui->lb_weighted_average_display->show();

    QString term = this->ui->cbb_term->currentText();
    // 设置表头
    this->model_scores->setHorizontalHeaderItem(0, new QStandardItem("课程名称"));    // 课程名称
    this->model_scores->setHorizontalHeaderItem(1, new QStandardItem("学分"));
    this->model_scores->setHorizontalHeaderItem(2, new QStandardItem("绩点"));

    // 将表格添加到tableView_courses中
    this->ui->tableView_scores->setModel(model_scores);
    // 调整表格的每列的宽度
    this->ui->tableView_scores->setColumnWidth(0, 150);
    this->ui->tableView_scores->setColumnWidth(1, 150);
    this->ui->tableView_scores->setColumnWidth(2, 150);

    // 显示已经选择的课程的成绩
    int row = 0;
    double gpa_sum = 0.0;    // 总的绩点和
    double credit_sum = 0.0;    // 总的加权绩点和
    double total_credit = 0.0;    // 总的学分和
    int count = 0;    // 总的门数
    for(int i = 0; i < selected_courses.length(); i++)
    {
        QString line = selected_courses.at(i);
        QStringList info_list = line.split(" ");
        if(info_list[4] == term && info_list.length() == 12)
        {
            this->model_scores->setItem(row, 0, new QStandardItem(info_list.at(2)));    // 课程名称

            this->model_scores->setItem(row, 1, new QStandardItem(info_list.at(10)));    // 学分

            this->model_scores->setItem(row, 2, new QStandardItem(info_list.at(11)));    // 成绩
            double credit = info_list.at(10).toDouble();
            double gpa = info_list.at(11).toDouble();
            gpa_sum += gpa;
            credit_sum += credit * gpa;
            total_credit += credit;
            count++;
            row++;
        }
    }
    if(count != 0){
        double average_gpa = gpa_sum / count;    // 平均绩点
        double weighted_gpa = credit_sum / total_credit;    // 加权绩点
        this->ui->lb_average_display->setText(QString("%2").arg(average_gpa));
        this->ui->lb_weighted_average_display->setText(QString("%2").arg(weighted_gpa));
    }
}
