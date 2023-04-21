#ifndef REGISTERW_H
#define REGISTERW_H

#include <QWidget>

namespace Ui {
    class registerw;
}

class registerw : public QWidget {
Q_OBJECT

public:

    explicit registerw(QWidget *parent = nullptr);
    ~registerw();

signals:

    void setVisibleSignal();

private slots:

    void on_registerButton_clicked();
    void on_quitButton_clicked();
    void createuser(QString name);

private:

    Ui::registerw *ui;
    void getDbList();
};

#endif // REGISTERW_H
