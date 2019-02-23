#include "mwindow.h"
#include "ui_mwindow.h"

MWindow::MWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MWindow)
{
    ui->setupUi(this);
    over = new Overlay();
    QScreen *screen;
    screen = QGuiApplication::primaryScreen();
    over->setFixedSize(screen->availableSize());
    over->show();
    cheat = new CheatCore;
    setWindowFlags(Qt::WindowStaysOnTopHint);
}

MWindow::~MWindow()
{
    delete ui;
}


void MWindow::keyPressEvent(QKeyEvent *e)
{
    QWidget::keyPressEvent(e);
    if (over == nullptr || defined) {
        return;
    }

    if (e->key() == Qt::Key_I) {
        QPoint temp = over->mapFromGlobal(QCursor::pos());
        ui->ammo_label->clear();
        over->ammo = temp;
    }

    if (e->key() == Qt::Key_O) {
        QPoint temp = over->mapFromGlobal(QCursor::pos());
        if (!over->bot.isNull()) {
            if(temp.rx() > over->bot.rx() || temp.ry() > over->bot.ry()){
                return;
            }
        }
        ui->t_label->clear();
        over->top = temp;
    }

    if (e->key() == Qt::Key_P) {
        if(over->top.isNull()){
            ui->t_label->setText(ui->t_label->text().toUpper());
            return;
        }

        QPoint temp = over->mapFromGlobal(QCursor::pos());
        if(temp.rx() < over->top.rx() || temp.ry() < over->top.ry()){
            return;
        }
        ui->b_label->clear();
        over->bot = temp;
        ui->go->setEnabled(true);
    }
}


void MWindow::on_go_clicked()
{
    if(defined){
        return;
    }

    defined = true;

    cheat->setup(over);

    over->hide();
    over->close();
    delete over;



    cheat->start();

}

