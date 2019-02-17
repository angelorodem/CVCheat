#ifndef MWINDOW_H
#define MWINDOW_H

#include "includes.h"
#include "cheatcore.h"

namespace Ui {
class MWindow;
}

class MWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MWindow(QWidget *parent = nullptr);
    ~MWindow();

private slots:
    void on_go_clicked();

private:
    CheatCore* cheat;
    bool defined = false;
    Ui::MWindow *ui;
    void keyPressEvent(QKeyEvent *e);
    Overlay* over;
};

#endif // MWINDOW_H
