/*
* Copyright(c) 2017 dragon jiang<jianlinlong@gmail.com>
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files(the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions :
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#ifndef _TITLE_BAR_H_
#define _TITLE_BAR_H_

#include <QtWidgets/QtWidgets>

class State_Button;
class Skin;

class Title_Bar: public QWidget
{
    Q_OBJECT
public:
    enum Show_Style{
        SHOW_ICON            = 0x01,
        SHOW_TITLE           = 0x02,
        SHOW_MIN_BUTTON      = 0x04,
        SHOW_MAX_BUTTON      = 0x08,
        SHOW_CLOSE_BUTTON    = 0x10,
        DRAW_BACKGROUND      = 0x20,        //是否绘制标题栏的背景
        SHOW_SKIN            = 0x40,        //皮肤按钮
        SHOW_MENU            = 0x80,        //菜单按钮

        FORM_STYLE           = SHOW_ICON|SHOW_TITLE|SHOW_MIN_BUTTON|SHOW_MAX_BUTTON|SHOW_CLOSE_BUTTON,
        FORM_BG_STYLE        = FORM_STYLE|DRAW_BACKGROUND,
        DIALOG_STYLE         = SHOW_TITLE|SHOW_CLOSE_BUTTON,
        DIALOG_BG_STYLE      = DIALOG_STYLE|DRAW_BACKGROUND,
        DIALOG_ICON_STYLE    = SHOW_ICON|DIALOG_STYLE,
        DIALOG_ICON_BG_STYLE = DIALOG_ICON_STYLE|DRAW_BACKGROUND,
        MAIN_FORM_STYLE      = FORM_STYLE|SHOW_MENU,
        MAIN_FORM_BG_STYLE   = MAIN_FORM_STYLE|DRAW_BACKGROUND,
        MAIN_FORM_SKIN_STYLE = MAIN_FORM_STYLE | SHOW_SKIN,
        MAIN_FORM_SKIN_BG_STYLE = MAIN_FORM_SKIN_STYLE | DRAW_BACKGROUND
    };
    Q_ENUMS(Show_Style)

public:
    Title_Bar(QWidget *parent, Skin *skin = NULL);
    /*virtual*/ ~Title_Bar();

    int   get_show_style() const {return show_style_;};
    void  set_show_style(int style);

    QString text(){return title_->text();}
    void set_text(const QString& text){title_->setText(text);}
    void set_text_style_sheet(const QString& qss){title_->setStyleSheet(qss);}
    bool is_window_maximized() const {return is_maxed_;}

    //将高度设置为背景图片的大小, 最好在show_style_设置为DRAW_BACKGROUND时使用
    void fix_height_to_background();

    void load_skin(Skin* skin=NULL);

    //将字符串转为枚举值
    static int str2showstyle(const char* str); 

public:
    QHBoxLayout* layout() const;
    QLabel* icon() const;
    QLabel* title() const;
    State_Button* skin_button() const;
    State_Button* menu_button() const;
    State_Button* min_button() const;
    State_Button* max_button() const;
    State_Button* close_button() const;

signals:
    //on skin button clicked
    void skin_clicked();
    // on menu button clicked
    void menu_clicked();

public slots:
    void show_small();
    void show_max_restore();

private:
    int  init();
    void load_skin_internal();
    void widget_set_visible();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);

protected:
    QHBoxLayout  *hbox_layout_;
    QLabel       *icon_;
    QLabel       *title_;
    State_Button *skin_button_;
    State_Button *menu_button_;
    State_Button *min_button_;
    State_Button *max_button_;
    State_Button *close_button_;

    int         show_style_;
    QRect       normal_rect_;
    QPoint      click_pos_;     //
    bool        left_pressed_;   //left mouse pressed
    bool        is_maxed_;       //window Maximized

    Skin        *skin_;
};

#endif

