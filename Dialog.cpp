#include <QDebug>
#include <QTimer>
#include <QCloseEvent>

#include "Dialog.h"
#include "ui_Dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    createActions();
    createTrayIcon();

    trayIcon->show();

    this->Key_Changed();

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &Dialog::trackActions);
    m_timer->setInterval(50);
    m_timer->start();
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::setVisible(bool visible)
{
    restoreAction->setEnabled(isMaximized() || !visible);
    QDialog::setVisible(visible);
}

void Dialog::closeEvent(QCloseEvent* event)
{
    if (trayIcon->isVisible()) {
        hide();
        event->ignore();
    }
}

void Dialog::trackActions()
{
    static bool last_key_pressed = false;
    bool current_key_pressed = GetKeyState(this->m_key) & 0x8000;

    if(current_key_pressed != last_key_pressed)
    {
        last_key_pressed = current_key_pressed;
        if(current_key_pressed == false)
        {
            int count = ui->label_Count->text().toInt()+1;
            ui->label_Count->setText(QString::number(count));
        }
    }
}

void Dialog::on_pushButton_Reset_clicked()
{
    ui->label_Count->setText("0");
}

void Dialog::Key_Changed()
{
    if(ui->radioButton_L_SHIFT->isChecked())   this->m_key = Left_shift;
    else if (ui->radioButton_R_SHIFT->isChecked())  this->m_key = Right_shift;
    else if (ui->radioButton_L_CTRL->isChecked())   this->m_key = Left_control;
    else if (ui->radioButton_R_CTRL->isChecked())   this->m_key = Right_control;
    else if (ui->radioButton_L_ALT->isChecked())    this->m_key = Left_menu;
    else if (ui->radioButton_R_ALT->isChecked())    this->m_key = Right_menu;
}

void Dialog::on_radioButton_L_CTRL_toggled(bool checked)
{
    Q_UNUSED(checked)
    this->Key_Changed();
}

void Dialog::on_radioButton_R_CTRL_toggled(bool checked)
{
    Q_UNUSED(checked)
    this->Key_Changed();
}

void Dialog::on_radioButton_L_SHIFT_toggled(bool checked)
{
    Q_UNUSED(checked)
    this->Key_Changed();
}

void Dialog::on_radioButton_R_SHIFT_toggled(bool checked)
{
    Q_UNUSED(checked)
    this->Key_Changed();
}

void Dialog::on_radioButton_L_ALT_toggled(bool checked)
{
    Q_UNUSED(checked)
    this->Key_Changed();
}

void Dialog::on_radioButton_R_ALT_toggled(bool checked)
{
    Q_UNUSED(checked)
    this->Key_Changed();
}


void Dialog::createActions()
{
    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, &QAction::triggered, this, &Dialog::showNormal);

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
}

void Dialog::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);

    QIcon icon = QIcon(":/Icon/heart.png");// iconComboBox->itemIcon(index);
    trayIcon->setIcon(this->windowIcon());
}

