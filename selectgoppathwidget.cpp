#include "selectgoppathwidget.h"
#include "ui_selectgoppathwidget.h"
#include "goopal.h"
#include "commondialog.h"
#include "macro.h"
#include "datamgr.h"

#include <QPainter>
#include <QFileDialog>
#include <QDebug>
#include <QDesktopServices>

SelectGopPathWidget::SelectGopPathWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectGopPathWidget)
{
    ui->setupUi(this);

    ui->pathLineEdit->setText(DataMgr::getInstance()->getAppDataPath());
    ui->pathLineEdit->setStyleSheet("color:white;background:transparent;border-width:0;border-style:outset;");

    ui->minBtn->setStyleSheet(QString("QToolButton{background-image:url(%1pic2/minimize2.png);background-repeat: repeat-xy;background-position: center;background-attachment: fixed;background-clip: padding;border-style: flat;}"
                              "QToolButton:hover{background-image:url(%2pic2/minimize_hover.png);background-repeat: repeat-xy;background-position: center;background-attachment: fixed;background-clip: padding;border-style: flat;}").arg(DataMgr::getDataMgr()->getWorkPath()).arg(DataMgr::getDataMgr()->getWorkPath()));
    ui->closeBtn->setStyleSheet(QString("QToolButton{background-image:url(%1pic2/close2.png);background-repeat: repeat-xy;background-position: center;background-attachment: fixed;background-clip: padding;border-style: flat;}"
                                "QToolButton:hover{background-image:url(%2pic2/close_hover.png);background-repeat: repeat-xy;background-position: center;background-attachment: fixed;background-clip: padding;border-style: flat;}").arg(DataMgr::getDataMgr()->getWorkPath()).arg(DataMgr::getDataMgr()->getWorkPath()));

	ui->versionLabel->setText(ACHAIN_WALLET_VERSION_STR);

    ui->logoLabel->setPixmap(QPixmap(QString("%1pic2/Achainwallet.png").arg(DataMgr::getDataMgr()->getWorkPath())));

    setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap(QString("%1pic2/bg.png").arg(DataMgr::getDataMgr()->getWorkPath()))));
    setPalette(palette);
}

SelectGopPathWidget::~SelectGopPathWidget()
{
    delete ui;
}

void SelectGopPathWidget::on_selectPathBtn_clicked()
{
	QString path = ui->pathLineEdit->text();
	QString file = QFileDialog::getExistingDirectory(this, tr("Select the path to store the blockchain"), path);
    if( !file.isEmpty())
    {
#ifdef WIN32
        file.replace("/","\\");
#endif // WIN32 //zxlrun
        ui->pathLineEdit->setText(file);
    }
}

void SelectGopPathWidget::on_okBtn_clicked()
{
	if (ui->pathLineEdit->text().isEmpty())  return;
	QString str = ui->pathLineEdit->text();

	DataMgr::getInstance()->getSettings()->setValue("/settings/achainPath", str);

	//RpcMgr::getInstance()->startBlockChain();
	emit enter();
	close();
}

void SelectGopPathWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::white);
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(1);
    painter.setPen(pen);
    painter.drawLine(QPoint(368,344),QPoint(595,344));
}

void SelectGopPathWidget::on_minBtn_clicked()
{
    emit minimum();
}

void SelectGopPathWidget::on_closeBtn_clicked()
{
    emit closeGOP();
}
