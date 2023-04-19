#ifndef FIELDMANAGER_H
#define FIELDMANAGER_H

#include <QWidget>

namespace Ui {
    class FieldManager;
}

class FieldManager : public QWidget {
Q_OBJECT

public:

    explicit FieldManager(QWidget *parent = nullptr);
    ~FieldManager();

private slots:

    void on_add_clicked();

    void on_modify_clicked();

    void on_dele_clicked();

    void on_display_clicked();

    void on_isPK_clicked();

    void on_isNull_clicked();

private:

    Ui::FieldManager *ui;

    void initDir();
    bool isTableExist();

    QString dirPath;
    QString dbName;
    QString userName;
    QString tablePath;
    void display();
    bool isDuplicate(QString);
    void addComma2trd();
    void removedata(int);
};

#endif // FIELDMANAGER_H
