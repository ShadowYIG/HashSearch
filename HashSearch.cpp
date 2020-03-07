#include "HashSearch.h"
#include <QDebug>
#include <direct.h>
#include <QMessageBox>
#include <QInputDialog>

HashSearch::HashSearch(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    phashdata = NULL;
    ui.tableWidget->setRowCount(1);
    ui.tableWidget_2->setRowCount(1);
    ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui.tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui.tableWidget_2->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void HashSearch::btn_file_click()
{
    char filepath[256];
    QString fileName="";
    if (_getcwd(filepath, 256) == NULL) {
        fileName = QFileDialog::getOpenFileName(this,
            tr("选择文件"),
            "C:",
            tr("CSV(*csv)"));
    }
    else {
        fileName = QFileDialog::getOpenFileName(this,
            tr("选择文件"),
            filepath,
            tr("CSV(*csv)"));
    }
    
    //qDebug() << "filename : " << fileName;
    if (phashdata != NULL) {
        delete phashdata;
        phashdata = NULL;
    }
    //string str_filename = fileName.toStdString();
    string str_filename = qstr2str(fileName);
    hashpro* myhashdata = new hashpro(str_filename);
    phashdata = myhashdata;
    ui.text_file->setPlainText(fileName);
}

void HashSearch::btn_rand_click()
{
    bool ok = false;
    int inputValue = QInputDialog::getInt(this, "输入生成数量", "请输入需要生成的数据数量", 9, 0, 200000, 1, &ok);
    ui.statusBar->showMessage(QString::fromStdString("生成中，请稍后....."), 120000);
    if (!ok) //是否确认输入
    {
        return;
    }
    
    hashpro *myhashdata = new hashpro();
    if (myhashdata->randomCsvFile(inputValue)) {
        ui.text_file->setPlainText(QString::fromStdString(myhashdata->getFileName()));
        QMessageBox::information(this, "成功", "生成随机文件成功", QMessageBox::Ok, QMessageBox::NoButton);
        ui.statusBar->showMessage(QString::fromStdString("生成成功"), 5000);
    }
    else {
        QMessageBox::critical(this, "失败", "生成随机文件失败，请再尝试");
    }
    if (phashdata != NULL) {
        //qDebug() << "phashdata != NULL";
        delete phashdata;
        phashdata = NULL;
    }
    phashdata = myhashdata;
    
}

void HashSearch::btn_add_click()
{
    if (ui.text_file->toPlainText() == "") {
        QMessageBox::critical(this, "未发现文件", "请先选择文件");
        return;
    }
    QString qname = "", qmail = "", qaddr = "", qnumber = "";
    qname = ui.text_name->toPlainText();
    qnumber = ui.text_number->toPlainText();
    qmail = ui.text_mail->toPlainText();
    qaddr = ui.text_addr->toPlainText();
    if (qname == "") {
        QMessageBox::critical(this, "输入错误", "姓名不能为空，请输入姓名");
        return;
    }
    if (qnumber == "") {
        QMessageBox::critical(this, "输入错误", "电话号码不能为空，请输入电话号码");
        return;
    }
    if (qmail == "") {
        QMessageBox::critical(this, "输入错误", "邮箱不能为空，请输入邮箱");
        return;
    }
    if (qaddr == "") {
        QMessageBox::critical(this, "输入错误", "地址不能为空，请输入地址");
        return;
    }
    string name = qstr2str(qname);
    string mail = qstr2str(qnumber);
    string addr = qstr2str(qaddr);
    string number = qstr2str(qmail);

    if (phashdata->addCsvDate(name, number, mail, addr)) {
        QMessageBox::information(this, "成功", "加入成功", QMessageBox::Ok, QMessageBox::NoButton);
        ui.tableWidget->repaint();
        ui.text_name->setPlainText("");
        ui.text_number->setPlainText("");
        ui.text_mail->setPlainText("");
        ui.text_addr->setPlainText("");
    }
    else {
        QMessageBox::critical(this, "失败", "加入识别");
    }
    
}

void HashSearch::btn_search_click()
{
    if (ui.text_file->toPlainText() == "") {
        QMessageBox::critical(this, "未发现文件", "请先选择文件");
        return;
    }
    if (ui.text_name->toPlainText() == "") {
        QMessageBox::critical(this, "输入错误", "姓名不能为空，请输入姓名");
        return;
    }
    QString qname = ui.text_name->toPlainText();
    QString qhex_type = ui.com_fun->currentText();
    QString qcon_sol = ui.con_sol->currentText();
    string name = qstr2str(qname);
    hash_type hex_type;
    conflict_solution con_sol;
    perInfo persionInfo;
    //enum hash_type { BKDR = 1, JS, AP, RS, SDBM, PJW };
    //enum conflict_solution { openaddr = 1, linkaddr, reHash, overflawArea };
    if (qhex_type == "BKDR Hash") {
        hex_type = BKDR;
    }
    else if (qhex_type == "JS Hash") {
        hex_type = JS;
    }
    else if (qhex_type == "AP Hash") {
        hex_type = AP;
    }
    else if (qhex_type == "RS Hash") {
        hex_type = RS;
    }
    else if (qhex_type == "SDBM Hash") {
        hex_type = SDBM;
    }
    else if (qhex_type == "PJW Hash") {
        hex_type = PJW;
    }
    //解决冲突方式
    if (qcon_sol == "开放定址法") {
        con_sol = openaddr;
    }
    if (qcon_sol == "链地址法") {
        con_sol = linkaddr;
    }
    /*if (qcon_sol == "再哈希法") {
        con_sol = reHash;
    }*/
    if (qcon_sol == "建立公共溢出区") {
        con_sol = overflawArea;
    }
    int code = phashdata->SearchInfo(name, hex_type, con_sol, persionInfo);
    if (code==0) {
        QMessageBox::critical(this, "未发现哈希表", "请先建立该哈希表");
        return;
    }
    if (code == -1) {
        QMessageBox::critical(this, "无数据", "未找到你需要的数据");
        return;
    }
    int count = ui.tableWidget->rowCount();
    ui.tableWidget->setItem(count - 1, 0, new QTableWidgetItem(str2qstr(persionInfo.name)));
    ui.tableWidget->setItem(count - 1, 1, new QTableWidgetItem(str2qstr(persionInfo.phone)));
    ui.tableWidget->setItem(count - 1, 2, new QTableWidgetItem(str2qstr(persionInfo.email)));
    ui.tableWidget->setItem(count - 1, 3, new QTableWidgetItem(str2qstr(persionInfo.address)));
    
    if (qhex_type == "BKDR Hash") {
        ui.tableWidget->setItem(count - 1, 4, new QTableWidgetItem(QString::number(phashdata->getsearchtime().BKDRtime / 1000.0, 10, 5)));
    }
    else if (qhex_type == "JS Hash") {
        ui.tableWidget->setItem(count - 1, 4, new QTableWidgetItem(QString::number(phashdata->getsearchtime().JStime / 1000.0, 10, 5)));
    }
    else if (qhex_type == "AP Hash") {
        ui.tableWidget->setItem(count - 1, 4, new QTableWidgetItem(QString::number(phashdata->getsearchtime().APtime / 1000.0, 10, 5)));
    }
    else if (qhex_type == "RS Hash") {
        ui.tableWidget->setItem(count - 1, 4, new QTableWidgetItem(QString::number(phashdata->getsearchtime().RStime / 1000.0, 10, 5)));
    }
    else if (qhex_type == "SDBM Hash") {
        ui.tableWidget->setItem(count - 1, 4, new QTableWidgetItem(QString::number(phashdata->getsearchtime().SDBMtime / 1000.0, 10, 5)));
    }
    else if (qhex_type == "PJW Hash") {
        ui.tableWidget->setItem(count - 1, 4, new QTableWidgetItem(QString::number(phashdata->getsearchtime().PJWtime / 1000.0, 10, 5)));
    }
    ui.tableWidget->item(count - 1, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui.tableWidget->item(count - 1, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui.tableWidget->item(count - 1, 2)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui.tableWidget->item(count - 1, 3)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui.tableWidget->item(count - 1, 4)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui.tableWidget->repaint();
    ui.text_name->setPlainText("");
    ui.text_number->setPlainText("");
    ui.text_mail->setPlainText("");
    ui.text_addr->setPlainText("");
    ui.statusBar->showMessage(QString::fromStdString("查询成功"), 5000);
    qDebug() <<"搜索时间：" <<phashdata->getsearchtime().BKDRtime;

}

void HashSearch::btn_built_click()
{
    ui.statusBar->showMessage(QString::fromStdString("建立中，请稍后...."), 120000);
    if (ui.text_file->toPlainText() == "") {
        QMessageBox::critical(this, "未发现文件", "请先选择文件");
        return;
    }
    QString qhex_type = ui.com_fun->currentText();
    QString qcon_sol = ui.con_sol->currentText();
    hash_type hex_type;
    conflict_solution con_sol;
    perInfo persionInfo;
    if (qhex_type == "BKDR Hash") {
        hex_type = BKDR;
    }
    else if (qhex_type == "JS Hash") {
        hex_type = JS;
    }
    else if (qhex_type == "AP Hash") {
        hex_type = AP;
    }
    else if (qhex_type == "RS Hash") {
        hex_type = RS;
    }
    else if (qhex_type == "SDBM Hash") {
        hex_type = SDBM;
    }
    else if (qhex_type == "PJW Hash") {
        hex_type = PJW;
    }
    //解决冲突方式
    if (qcon_sol == "开放定址法") {
        con_sol = openaddr;
    }
    if (qcon_sol == "链地址法") {
        con_sol = linkaddr;
    }
    //if (qcon_sol == "再哈希法") {
    //    con_sol = reHash;
    //}
    if (qcon_sol == "建立公共溢出区") {
        con_sol = overflawArea;
    }
    phashdata->BuiltTable(hex_type, con_sol);
    phashdata->avgSearchTime(hex_type, con_sol);
    int count = ui.tableWidget_2->rowCount();
    int index = count - 1;
    qDebug() << count;
    //ui.tableWidget_2->setRowCount(1);
    
    //for (int i = 0; i < count;i++) {
    //    if ((ui.tableWidget_2->item(i, 0)->text() == qhex_type) && (ui.tableWidget_2->item(i, 1)->text() == qcon_sol)) {
    //        index = i;
    //    }
    //}

    ui.tableWidget_2->insertRow(count);
    ui.tableWidget_2->setItem(index, 0, new QTableWidgetItem(qhex_type));
    ui.tableWidget_2->setItem(index, 1, new QTableWidgetItem(qcon_sol));
    ui.tableWidget_2->setItem(index, 2, new QTableWidgetItem(QString::number(phashdata->getInfoSize())));
    if (qhex_type == "BKDR Hash") {
        ui.tableWidget_2->setItem(index, 3, new QTableWidgetItem(QString::number(phashdata->getConflictRate(con_sol).BKDRr / (double)phashdata->getInfoSize() * 100, 2, 5) + "%"));
        ui.tableWidget_2->setItem(index, 4, new QTableWidgetItem(QString::number(phashdata->getbuilttime(con_sol).BKDRtime / 1000.0, 10, 5)));
        ui.tableWidget_2->setItem(index, 5, new QTableWidgetItem(QString::number((phashdata->getavgsearchtime(con_sol).BKDRtime / 1000.0) / (double)phashdata->getInfoSize(), 10, 5)));
    }
    else if (qhex_type == "JS Hash") {
        ui.tableWidget_2->setItem(index, 3, new QTableWidgetItem(QString::number((phashdata->getConflictRate(con_sol).JSr / (double)phashdata->getInfoSize()) * 100, 2, 5) + "%"));
        ui.tableWidget_2->setItem(index, 4, new QTableWidgetItem(QString::number(phashdata->getbuilttime(con_sol).JStime / 1000.0, 10, 5)));
        ui.tableWidget_2->setItem(index, 5, new QTableWidgetItem(QString::number((phashdata->getavgsearchtime(con_sol).JStime / 1000.0) / (double)phashdata->getInfoSize(), 10, 5)));
    }
    else if (qhex_type == "AP Hash") {
        ui.tableWidget_2->setItem(index, 3, new QTableWidgetItem(QString::number((phashdata->getConflictRate(con_sol).APr / (double)phashdata->getInfoSize()) * 100, 2, 5) + "%"));
        ui.tableWidget_2->setItem(index, 4, new QTableWidgetItem(QString::number(phashdata->getbuilttime(con_sol).APtime / 1000.0, 10, 5)));
        ui.tableWidget_2->setItem(index, 5, new QTableWidgetItem(QString::number((phashdata->getavgsearchtime(con_sol).APtime / 1000.0) / (double)phashdata->getInfoSize(), 10, 5)));
    }
    else if (qhex_type == "RS Hash") {
        ui.tableWidget_2->setItem(index, 3, new QTableWidgetItem(QString::number((phashdata->getConflictRate(con_sol).RSr / (double)phashdata->getInfoSize()) * 100, 2, 5) + "%"));
        ui.tableWidget_2->setItem(index, 4, new QTableWidgetItem(QString::number(phashdata->getbuilttime(con_sol).RStime / 1000.0, 10, 5)));
        ui.tableWidget_2->setItem(index, 5, new QTableWidgetItem(QString::number((phashdata->getavgsearchtime(con_sol).RStime / 1000.0) / (double)phashdata->getInfoSize(), 10, 5)));
    }
    else if (qhex_type == "SDBM Hash") {
        ui.tableWidget_2->setItem(index, 3, new QTableWidgetItem(QString::number((phashdata->getConflictRate(con_sol).SDBr / (double)phashdata->getInfoSize()) * 100, 2, 5) + "%"));
        ui.tableWidget_2->setItem(index, 4, new QTableWidgetItem(QString::number(phashdata->getbuilttime(con_sol).SDBMtime / 1000.0, 10, 5)));
        ui.tableWidget_2->setItem(index, 5, new QTableWidgetItem(QString::number((phashdata->getavgsearchtime(con_sol).SDBMtime / 1000.0) / (double)phashdata->getInfoSize(), 10, 5)));
    }
    else if (qhex_type == "PJW Hash") {
        ui.tableWidget_2->setItem(index, 3, new QTableWidgetItem(QString::number((phashdata->getConflictRate(con_sol).PJWr / (double)phashdata->getInfoSize()) * 100, 2, 5) + "%"));
        ui.tableWidget_2->setItem(index, 4, new QTableWidgetItem(QString::number(phashdata->getbuilttime(con_sol).PJWtime / 1000.0, 10, 5)));
        ui.tableWidget_2->setItem(index, 5, new QTableWidgetItem(QString::number((phashdata->getavgsearchtime(con_sol).PJWtime / 1000.0)/ (double)phashdata->getInfoSize(), 10, 5)));
    }

    ui.tableWidget_2->item(index, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui.tableWidget_2->item(index, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui.tableWidget_2->item(index, 2)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui.tableWidget_2->item(index, 3)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui.tableWidget_2->item(index, 4)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui.tableWidget_2->item(index, 5)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui.tableWidget_2->repaint();
    //QString::number(timer.costTime / 1000.0, 10, 5)
    ui.statusBar->showMessage(QString::fromStdString("建立成功"), 5000);
    qDebug() << "建立耗时：" << phashdata->getsearchtime().BKDRtime;
}


void HashSearch::text_length()
{
    QString textContent = ui.text_name->toPlainText();
    int length = textContent.count();
    int maxLength = 4; // 最大字符数
    if (length > maxLength)
    {
        int position = ui.text_name->textCursor().position();
        QTextCursor textCursor = ui.text_name->textCursor();
        textContent.remove(position - (length - maxLength), length - maxLength);
        ui.text_name->setText(textContent);
        textCursor.setPosition(position - (length - maxLength));
        ui.text_name->setTextCursor(textCursor);
        QMessageBox::critical(this, "提示", "姓名不能超过4个字符");
    }
}

QString HashSearch::str2qstr(const string str)
{
    return QString::fromLocal8Bit(str.data());
}

string HashSearch::qstr2str(const QString qstr)
{
    QByteArray cdata = qstr.toLocal8Bit();
    return string(cdata);
}