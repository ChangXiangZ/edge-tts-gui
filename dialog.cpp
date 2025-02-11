#include "dialog.h"
#include "ui_dialog.h"
#include <QFileDialog>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
    , m_comm()
{
    ui->setupUi(this);
    // connect this->send() to this->m_comm.start()
    connect(this, &Dialog::send, &m_comm, &Communicate::start);
    connect(&m_comm, &Communicate::finished, [&]() {
        ui->pushButtonPlay->setDisabled(false);
        ui->pushButtonPlay->setText("▶️ 播放");
        ui->pushButtonStop->setEnabled(false);
    });
    connect(this, &Dialog::stop, &m_comm, &Communicate::stop);

    connect(&m_comm, &Communicate::saveFinished, [&]() {
        ui->pushButtonSave->setDisabled(false);
    });
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButtonPlay_clicked()
{
    QString text = ui->plainTextEditContent->toPlainText();
    if (text.isEmpty()) {
        return;
    }

    ui->pushButtonPlay->setDisabled(true);
    ui->pushButtonPlay->setText("⏳合成中...");
    ui->pushButtonStop->setEnabled(true);

    m_comm.setText(text);
    m_comm.setVoice(voice);
    m_comm.setFileName("");

    emit send();
}

void Dialog::on_pushButtonStop_clicked()
{
    emit stop();
}

void Dialog::on_pushButtonSave_clicked()
{
    QString text = ui->plainTextEditContent->toPlainText();
    if (text.isEmpty()) {
        return;
    }

    QString dir;
    if (lastDir.isEmpty()) {
        dir = QDir::currentPath();
    } else {
        dir = lastDir;
    }

    QString fileName = QFileDialog::getSaveFileName(
        this, // 父窗口
        "保存音频文件", // 对话框标题
        dir, // 默认文件路径
        "音频文件 (*.mp3)" // 文件过滤器
    );

    if (fileName.isEmpty()) {
        return;
    }

    lastDir = fileName;

    ui->pushButtonSave->setDisabled(true);

    m_comm.setText(text);
    m_comm.setVoice(voice);
    m_comm.setFileName(fileName);

    emit send();
}


void Dialog::on_radioButtonXiaoxiao_clicked(bool checked)
{
    if (checked) {
        voice = "zh-CN, XiaoxiaoNeural";
    }
}


void Dialog::on_radioButtonXiaoyi_clicked(bool checked)
{
    if (checked) {
        voice = "zh-CN, XiaoyiNeural";
    }
}


void Dialog::on_radioButtonYunjian_clicked(bool checked)
{
    if (checked) {
        voice = "zh-CN, YunjianNeural";
    }
}


void Dialog::on_radioButtonYunxi_clicked(bool checked)
{
    if (checked) {
        voice = "zh-CN, YunxiNeural";
    }
}


void Dialog::on_radioButtonYunxia_clicked(bool checked)
{
    if (checked) {
        voice = "zh-CN, YunxiaNeural";
    }
}


void Dialog::on_radioButtonYunyang_clicked(bool checked)
{
    if (checked) {
        voice = "zh-CN, YunyangNeural";
    }
}
