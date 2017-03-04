#ifndef __MY_WIDGHT_H_
#define __MY_WIDGHT_H_

#include "Base_Widget.h"

namespace Ui {
    class UI_About;
    class UI_Main_Form;
};


class Main_Form : public Base_Widget<QWidget> {
    Q_OBJECT
public:
    Main_Form(QWidget *parent = 0, Skin *skin = NULL);
    ~Main_Form();

protected slots:
    void btn_about_clicked();
    void btn_open_bg_image_clicked();
    void radio_button_clicked();

private:
    Ui::UI_Main_Form *ui_;
};

class About_Form : public Base_Widget<QDialog> {
    Q_OBJECT
public:
    About_Form(QWidget *parent = 0, Skin *skin = NULL);
    ~About_Form();

private:
    Ui::UI_About *ui_;
};


#endif // !__MY_WIDGHT_H_

