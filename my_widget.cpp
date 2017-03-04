#include "my_widget.h"
#include "ui_main.h"
#include "ui_about.h"

Main_Form::Main_Form(QWidget *parent /*= 0*/, Skin *skin /*= NULL*/)
    : BaseClass(parent, skin)
{
    ui_ = new Ui::UI_Main_Form();
    QWidget *c = this->setup_UI(ui_);

    connect(ui_->btnAbout, SIGNAL(clicked()), this, SLOT(btn_about_clicked()));
    connect(ui_->btnImport, SIGNAL(clicked()), this, SLOT(btn_open_bg_image_clicked()));
    connect(ui_->btnLeftToRight, SIGNAL(clicked()), this, SLOT(radio_button_clicked()));
    connect(ui_->btnRightToLeft, SIGNAL(clicked()), this, SLOT(radio_button_clicked()));
    connect(ui_->btnStretch, SIGNAL(clicked()), this, SLOT(radio_button_clicked()));

    this->make_bkg_alpha(ui_->btnImport);
    this->set_child_bkg_alpha(128);
}

Main_Form::~Main_Form()
{
    delete ui_;
}

void Main_Form::btn_about_clicked()
{
    About_Form w(this, skinman->get("sub_main"));
    w.exec();
}

void Main_Form::btn_open_bg_image_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
        this,
        "choose an image",
        "", //QDir::currentPath(),
        "Image files (*.bmp; *.png; *.jpg;);;All files(*.*)");

    if (!filename.isNull()) {
        //load client image
        skin()->set_client_pixmap(filename);
        skinman->get("sub_main")->set_client_pixmap(filename);
        
        QRect rect = skin()->client_pixmap().rect();
        QRect fix_size(0, 0, 400, 600);
        if (rect.width() > fix_size.width() || rect.height() > fix_size.height()) {
            rect = fix_size;
        }
        this->resize(rect.size());
        this->redraw_background();
    }
}

void Main_Form::radio_button_clicked()
{
    if (ui_->btnLeftToRight->isChecked()) {
        skin()->set_client_draw_type(1);
        skinman->get("sub_main")->set_client_draw_type(1);
    } 
    else if (ui_->btnRightToLeft->isChecked()){
        skin()->set_client_draw_type(2);
        skinman->get("sub_main")->set_client_draw_type(2);
    }
    else {
        skin()->set_client_draw_type(3);
        skinman->get("sub_main")->set_client_draw_type(3);
    } 
    this->redraw_background();
}

//////////////////////////////////////////////////////////////////////////

About_Form::About_Form(QWidget *parent /*= 0*/, Skin *skin /*= NULL*/)
    :BaseClass(parent, skin)
{
    ui_ = new Ui::UI_About();
    this->setup_UI(ui_);
}

About_Form::~About_Form()
{
    delete ui_;
}

