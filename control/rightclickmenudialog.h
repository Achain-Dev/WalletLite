#ifndef RIGHTCLICKMENUDIALOG_H
#define RIGHTCLICKMENUDIALOG_H

#include <QMenu>

namespace Ui {
class RightClickMenuDialog;
}

class RightClickMenuDialog : public QMenu
{
    Q_OBJECT

public:
    explicit RightClickMenuDialog(QString name, QWidget *parent = 0);
    ~RightClickMenuDialog();

private slots:
    void on_transferBtn_clicked();

    void on_renameBtn_clicked();

    void on_deleteBtn_clicked();

signals:
    void transferFromAccount(QString account);
    void renameAccount(QString account);
    void deleteAccount(QString account);

private:
    Ui::RightClickMenuDialog *ui;
    QString accountName;

	QAction* transferAction;
	QAction* renameAction;
	QAction* deleteAction;

};

#endif // RIGHTCLICKMENUDIALOG_H
