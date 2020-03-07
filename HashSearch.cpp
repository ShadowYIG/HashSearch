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
            tr("ѡ���ļ�"),
            "C:",
            tr("CSV(*csv)"));
    }
    else {
        fileName = QFileDialog::getOpenFileName(this,
            tr("ѡ���ļ�"),
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
    int inputValue = QInputDialog::getInt(this, "������������", "��������Ҫ���ɵ���������", 9, 0, 200000, 1, &ok);
    ui.statusBar->showMessage(QString::fromStdString("�����У����Ժ�....."), 120000);
    if (!ok) //�Ƿ�ȷ������
    {
        return;
    }
    
    hashpro *myhashdata = new hashpro();
    if (myhashdata->randomCsvFile(inputValue)) {
        ui.text_file->setPlainText(QString::fromStdString(myhashdata->getFileName()));
        QMessageBox::information(this, "�ɹ�", "��������ļ��ɹ�", QMessageBox::Ok, QMessageBox::NoButton);
        ui.statusBar->showMessage(QString::fromStdString("���ɳɹ�"), 5000);
    }
    else {
        QMessageBox::critical(this, "ʧ��", "��������ļ�ʧ�ܣ����ٳ���");
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
        QMessageBox::critical(this, "δ�����ļ�", "����ѡ���ļ�");
        return;
    }
    QString qname = "", qmail = "", qaddr = "", qnumber = "";
    qname = ui.text_name->toPlainText();
    qnumber = ui.text_number->toPlainText();
    qmail = ui.text_mail->toPlainText();
    qaddr = ui.text_addr->toPlainText();
    if (qname == "") {
        QMessageBox::critical(this, "�������", "��������Ϊ�գ�����������");
        return;
    }
    if (qnumber == "") {
        QMessageBox::critical(this, "�������", "�绰���벻��Ϊ�գ�������绰����");
        return;
    }
    if (qmail == "") {
        QMessageBox::critical(this, "�������", "���䲻��Ϊ�գ�����������");
        return;
    }
    if (qaddr == "") {
        QMessageBox::critical(this, "�������", "��ַ����Ϊ�գ��������ַ");
        return;
    }
    string name = qstr2str(qname);
    string mail = qstr2str(qnumber);
    string addr = qstr2str(qaddr);
    string number = qstr2str(qmail);

    if (phashdata->addCsvDate(name, number, mail, addr)) {
        QMessageBox::information(this, "�ɹ�", "����ɹ�", QMessageBox::Ok, QMessageBox::NoButton);
        ui.tableWidget->repaint();
        ui.text_name->setPlainText("");
        ui.text_number->setPlainText("");
        ui.text_mail->setPlainText("");
        ui.text_addr->setPlainText("");
    }
    else {
        QMessageBox::critical(this, "ʧ��", "����ʶ��");
    }
    
}

void HashSearch::btn_search_click()
{
    if (ui.text_file->toPlainText() == "") {
        QMessageBox::critical(this, "δ�����ļ�", "����ѡ���ļ�");
        return;
    }
    if (ui.text_name->toPlainText() == "") {
        QMessageBox::critical(this, "�������", "��������Ϊ�գ�����������");
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
    //�����ͻ��ʽ
    if (qcon_sol == "���Ŷ�ַ��") {
        con_sol = openaddr;
    }
    if (qcon_sol == "����ַ��") {
        con_sol = linkaddr;
    }
    /*if (qcon_sol == "�ٹ�ϣ��") {
        con_sol = reHash;
    }*/
    if (qcon_sol == "�������������") {
        con_sol = overflawArea;
    }
    int code = phashdata->SearchInfo(name, hex_type, con_sol, persionInfo);
    if (code==0) {
        QMessageBox::critical(this, "δ���ֹ�ϣ��", "���Ƚ����ù�ϣ��");
        return;
    }
    if (code == -1) {
        QMessageBox::critical(this, "������", "δ�ҵ�����Ҫ������");
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
    ui.statusBar->showMessage(QString::fromStdString("��ѯ�ɹ�"), 5000);
    qDebug() <<"����ʱ�䣺" <<phashdata->getsearchtime().BKDRtime;

}

void HashSearch::btn_built_click()
{
    ui.statusBar->showMessage(QString::fromStdString("�����У����Ժ�...."), 120000);
    if (ui.text_file->toPlainText() == "") {
        QMessageBox::critical(this, "δ�����ļ�", "����ѡ���ļ�");
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
    //�����ͻ��ʽ
    if (qcon_sol == "���Ŷ�ַ��") {
        con_sol = openaddr;
    }
    if (qcon_sol == "����ַ��") {
        con_sol = linkaddr;
    }
    //if (qcon_sol == "�ٹ�ϣ��") {
    //    con_sol = reHash;
    //}
    if (qcon_sol == "�������������") {
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
    ui.statusBar->showMessage(QString::fromStdString("�����ɹ�"), 5000);
    qDebug() << "������ʱ��" << phashdata->getsearchtime().BKDRtime;
}


void HashSearch::text_length()
{
    QString textContent = ui.text_name->toPlainText();
    int length = textContent.count();
    int maxLength = 4; // ����ַ���
    if (length > maxLength)
    {
        int position = ui.text_name->textCursor().position();
        QTextCursor textCursor = ui.text_name->textCursor();
        textContent.remove(position - (length - maxLength), length - maxLength);
        ui.text_name->setText(textContent);
        textCursor.setPosition(position - (length - maxLength));
        ui.text_name->setTextCursor(textCursor);
        QMessageBox::critical(this, "��ʾ", "�������ܳ���4���ַ�");
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