#ifndef DIALOGTESTCURVE_H
#define DIALOGTESTCURVE_H

#include <QDialog>

class QLabel;
class MyPath;

namespace Ui {
class DialogTestCurve;
}

class DialogTestCurve : public QDialog
{
    Q_OBJECT

public:
    explicit DialogTestCurve(QWidget *parent = nullptr);
    ~DialogTestCurve();

    QList<QLabel*> labels;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::DialogTestCurve *ui;

    QLabel* selectedLabel;
    MyPath* myPath;

    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

    void drawCurve();
};

#endif // DIALOGTESTCURVE_H
