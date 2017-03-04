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

#include "Title_Bar.h"
#include "Skin.h"
#include "State_Button.h"
#include <qdrawutil.h>

Title_Bar::Title_Bar( QWidget* parent, Skin *skin )
    :QWidget(parent)
    ,left_pressed_(false)
    ,show_style_(FORM_STYLE) //default: show all title buttons
    ,is_maxed_(false)
    ,skin_(skin)
{
    init();
}

Title_Bar::~Title_Bar()
{
}

int Title_Bar::init()
{
    hbox_layout_  = new QHBoxLayout(this);
    icon_         = new QLabel(this);
    title_        = new QLabel(this);
    skin_button_  = new State_Button(this);
    menu_button_  = new State_Button(this);
    min_button_   = new State_Button(this);
    max_button_   = new State_Button(this);
    close_button_ = new State_Button(this);

    //设置name以方便使用 CSS 
    icon_->setObjectName("title_bar_icon");
    title_->setObjectName("title_bar_text");
    skin_button_->setObjectName("title_bar_skin");
    menu_button_->setObjectName("title_bar_menu");
    min_button_->setObjectName("title_bar_min");
    max_button_->setObjectName("title_bar_max");
    close_button_->setObjectName("title_bar_close");

    //load Skin
    if (NULL == skin_)
    {
        skin_ = skinman->default_skin();
    }
    load_skin_internal();

    //title
    title_->setText("Title bar");

    const int frame_width = 5;

    //layout
    hbox_layout_->addWidget(icon_, 0, Qt::AlignVCenter);
    hbox_layout_->addSpacing(frame_width);
    hbox_layout_->addWidget(title_, 0, Qt::AlignVCenter);
    hbox_layout_->addStretch();
    hbox_layout_->addWidget(skin_button_, 0, Qt::AlignTop);
    hbox_layout_->addWidget(menu_button_, 0, Qt::AlignTop);
    hbox_layout_->addWidget(min_button_,  0, Qt::AlignTop);
    hbox_layout_->addWidget(max_button_,  0, Qt::AlignTop);
    hbox_layout_->addWidget(close_button_, 0, Qt::AlignTop);

    hbox_layout_->setSpacing(0);

    //
    setLayout(hbox_layout_);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    //
    connect(skin_button_, SIGNAL(clicked()), this, SIGNAL(skin_clicked()));
    connect(menu_button_, SIGNAL(clicked()), this, SIGNAL(menu_clicked()));
    connect(min_button_, SIGNAL(clicked()), this, SLOT(show_small()));
    connect(max_button_, SIGNAL(clicked()), this, SLOT(show_max_restore()));
    connect(close_button_, SIGNAL(clicked()), window(), SLOT(close()));

    return 0;
}

void Title_Bar::load_skin_internal()
{
    //show_style
    int show_style = skin_->titlebar_showstyle();
    if (show_style != -1 && show_style != show_style_ )
    {
        show_style_ = show_style;
        widget_set_visible();
    }

    //height
    int h = skin_->titlebar_height();
    switch (h)
    {
    case -1:    //设置为背景图片的高度
        {
            fix_height_to_background();
            break;
        }
    case 0:     //当前样式之标题栏的高度
        {
            int titlebar_height = style()->pixelMetric(QStyle::PM_TitleBarHeight);
            setFixedHeight(titlebar_height);
            break;
        }
    default:
        {
            setFixedHeight(h);
            break;
        }
    }    

    //margin
    hbox_layout_->setContentsMargins(skin_->titlebar_background().margin());

    //icon
    icon_->setPixmap(skin_->app_pixmap());
    icon_->setFixedSize(16, 16);
    icon_->setScaledContents(true);

    //title
    title_->setStyleSheet(skin_->titlebar_qss());

    //windows taskbar icon
    window()->setWindowIcon(skin_->app_pixmap());

    //
    skin_button_->set_pixmap(skin_->skin_pixmap());
    menu_button_->set_pixmap(skin_->menu_pixmap());
    min_button_->set_pixmap(skin_->min_pixmap());
    max_button_->set_pixmap(skin_->max_pixmap());
    close_button_->set_pixmap(skin_->close_pixmap());
}

void Title_Bar::load_skin(Skin* skin)
{
    if (NULL != skin)
    {
        skin_ = skin;
    }
    load_skin_internal();
}

void Title_Bar::show_max_restore()
{
    if (is_maxed_)
    {
        is_maxed_ = false;
        window()->setGeometry(normal_rect_);
        max_button_->set_pixmap(skin_->max_pixmap());
    } else {
        is_maxed_ = true;
        //avoid max-size overlap taskbar, this BUG still exists until Qt 5.1
        normal_rect_ = window()->geometry();
        window()->setGeometry(QApplication::desktop()->availableGeometry());
        max_button_->set_pixmap(skin_->restore_pixmap());
    }
}

void Title_Bar::mousePressEvent( QMouseEvent *e )
{
    QRect r = rect();
    r.adjust(5, 5, -5, -5);
    if (r.contains(e->pos()))   //5:边框大小，边框用来拉伸改变窗口大小
    {
        if (e->button() == Qt::LeftButton)
        {
            left_pressed_ = true;
            click_pos_ = mapToParent(e->pos());
            e->accept();
            return;
        }
    }

    e->ignore();
}

void Title_Bar::mouseMoveEvent( QMouseEvent *e )
{
    if (left_pressed_ && !is_maxed_)
    {
        window()->move(e->globalPos() - click_pos_);
        e->accept();
    }else{
        e->ignore();
    }
}

void Title_Bar::mouseReleaseEvent( QMouseEvent *e )
{
    left_pressed_ = false;
    e->ignore();
}

void Title_Bar::show_small()
{
    window()->showMinimized();
}

void Title_Bar::mouseDoubleClickEvent( QMouseEvent *e )
{
    if (show_style_ & SHOW_MAX_BUTTON)
    {
        show_max_restore();
        left_pressed_ = false;
    }
}

void Title_Bar::set_show_style( int style )
{
    show_style_ = style;
    widget_set_visible();
}

void Title_Bar::widget_set_visible() 
{
    icon_->setVisible(show_style_ & SHOW_ICON);
    title_->setVisible(show_style_ & SHOW_TITLE);
    skin_button_->setVisible(show_style_ & SHOW_SKIN);
    menu_button_->setVisible(show_style_ & SHOW_MENU);
    min_button_->setVisible(show_style_ & SHOW_MIN_BUTTON);
    max_button_->setVisible(show_style_ & SHOW_MAX_BUTTON);
    close_button_->setVisible(show_style_ & SHOW_CLOSE_BUTTON);
}

void Title_Bar::paintEvent( QPaintEvent *e )
{
    QWidget::paintEvent(e);

    if (show_style_ & DRAW_BACKGROUND)
    {
        const Border_Image& bi = skin_->titlebar_background();

        QPainter painter(this);
        qDrawBorderPixmap(&painter, rect(), bi.border(), bi.pixmap());
    }
}

void Title_Bar::fix_height_to_background()
{
    const Border_Image& bi = skin_->titlebar_background();
    int h = bi.pixmap().height();
    if (h > 0)
    {
        setFixedHeight(h);
    }
}

int Title_Bar::str2showstyle( const char* str )
{
    int index = Title_Bar::staticMetaObject.indexOfEnumerator("Show_Style");
    QMetaEnum myEnum = Title_Bar::staticMetaObject.enumerator(index);
    bool ok = false;
    int ret = myEnum.keyToValue(str, &ok); //-1: error
    return ok ? ret : -1; //
}

QHBoxLayout* Title_Bar::layout() const
{
    return hbox_layout_;
}

QLabel* Title_Bar::icon() const
{
    return icon_;
}

QLabel* Title_Bar::title() const
{
    return title_;
}

State_Button* Title_Bar::skin_button() const
{
    return skin_button_;
}

State_Button* Title_Bar::menu_button() const
{
    return menu_button_;
}

State_Button* Title_Bar::min_button() const
{
    return min_button_;
}

State_Button* Title_Bar::max_button() const
{
    return max_button_;
}

State_Button* Title_Bar::close_button() const
{
    return close_button_;
}

