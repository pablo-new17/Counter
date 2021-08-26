#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>

#include <windows.h>
#include <winuser.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE


    //Code          Meaning
    //VK_LSHIFT     Left-shift key.
    //VK_RSHIFT     Right-shift key.
    //VK_LCONTROL	Left-control key.
    //VK_RCONTROL	Right-control key.
    //VK_LMENU      Left-menu key.
    //VK_RMENU      Right-menu key.
    typedef enum KEY_MAPPING
{
    Left_shift = VK_LSHIFT,
    Right_shift = VK_RSHIFT,
    Left_control = VK_LCONTROL,
    Right_control = VK_RCONTROL,
    Left_menu = VK_LMENU,
    Right_menu =VK_RMENU,
    }KEY_MAPPING;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

    void setVisible(bool visible) override;
protected:
    void closeEvent(QCloseEvent *event) override;


private slots:
    void trackActions();

    void on_pushButton_Reset_clicked();

    void Key_Changed();

    void on_radioButton_L_CTRL_toggled(bool checked);

    void on_radioButton_R_CTRL_toggled(bool checked);

    void on_radioButton_L_SHIFT_toggled(bool checked);

    void on_radioButton_R_SHIFT_toggled(bool checked);

    void on_radioButton_L_ALT_toggled(bool checked);

    void on_radioButton_R_ALT_toggled(bool checked);

    void createActions();
    void createTrayIcon();

private:
    Ui::Dialog *        ui;
    QTimer *            m_timer;
    KEY_MAPPING         m_key;

    QAction *           restoreAction;
    QAction *           quitAction;
    QSystemTrayIcon *   trayIcon;
    QMenu *             trayIconMenu;
private:

};
#endif // DIALOG_H
