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

#include "State_Button.h"
#include <QStylePainter>
#include <QStyleOptionButton>
#include <QStyle>

State_Button::State_Button(QWidget *parent)
	:QPushButton(parent)
    ,status_(NORMAL)
    ,mouse_pressed_(false)
    ,pixmap_type_(NONE)
{
    setStyleSheet("QPushButton{background:transparent;}");
}

State_Button::~State_Button()
{
}

void State_Button::load_pximap(const QString& pic_name, int state_count)
{
    pixmap_type_ = FOREGROUND;
    pixmap_.load(pic_name);
    state_count_ = state_count;
	width_       = pixmap_.width()/state_count;
	height_      = pixmap_.height();
	setFixedSize(width_, height_);
}

void State_Button::set_pixmap( const QPixmap& pixmap, int state_count )
{
    pixmap_type_ = FOREGROUND;
    pixmap_      = pixmap;
    state_count_ = state_count;
    width_       = pixmap_.width()/state_count;
    height_      = pixmap_.height();
    setFixedSize(width_, height_);
}

void State_Button::load_background( const QString& pic_name, int state_count/*=4*/ )
{
    load_pximap(pic_name, state_count);
    pixmap_type_ = BACKGROUND;
}

void State_Button::set_background( const QPixmap& pixmap, int state_count/*=4*/ )
{
    set_pixmap(pixmap, state_count);
    pixmap_type_ = BACKGROUND;
}

void State_Button::enterEvent(QEvent *e)
{
    status_ = HOVER;
    update();
}

void State_Button::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		mouse_pressed_ = true;
		status_ = PRESSED;
		update();
	}

    QPushButton::mousePressEvent(event);
}

void State_Button::mouseReleaseEvent(QMouseEvent *event)
{
	if (mouse_pressed_)
	{
        mouse_pressed_ = false;
        
        if (this->rect().contains(event->pos()))
        {
            //if (isCheckable())
            //{
            //    setChecked(!isChecked());
            //}
            //emit clicked();

            status_ = HOVER;
        }else{
            status_ = NORMAL;
        }

        update();
	}

    QPushButton::mouseReleaseEvent(event);
}

void State_Button::leaveEvent(QEvent *e)
{
	status_ = NORMAL;
	update();
    QPushButton::leaveEvent(e);
}

void State_Button::paintEvent(QPaintEvent *e)
{
    if (pixmap_type_ == BACKGROUND) {
        paint_pixmap();
    }

   // QPushButton::paintEvent(e);
    QStylePainter p(this);
    QStyleOptionButton option;
    initStyleOption(&option);
    if (option.state & QStyle::State_HasFocus) {
        option.state ^= QStyle::State_HasFocus;    //去除焦点框
        option.state |= QStyle::State_MouseOver;
    }
    p.drawControl(QStyle::CE_PushButton, option);

    if (pixmap_type_ == FOREGROUND) {
        paint_pixmap();
    }
}

void State_Button::paint_pixmap() 
{
    QPainter painter(this);

    //根据状态显示图片
    ButtonStatus status = status_;
    if (!isEnabled()) {
        status = DISABLED;
    }
    else if (isChecked()) {
        status = CHECKED;
        //没有checked图片，用hover代替
        if (status >= state_count_) {
            status = HOVER;
        }
    }

    if (status >= state_count_) {
        status = NORMAL;
    }

    painter.drawPixmap(rect(), pixmap_.copy(width_ * status, 0, width_, height_));
}
//////////////////////////////////////////////////////////////////////////


Icon_Text_Button::Icon_Text_Button( QWidget *parent )
    :QPushButton(parent)
{
}

Icon_Text_Button::~Icon_Text_Button()
{
}

void Icon_Text_Button::paintEvent( QPaintEvent *e )
{
    QStyleOptionButton opt;
    initStyleOption(&opt);
    //opt.text = "";
    //opt.icon = QIcon();
    //opt.state &= ~QStyle::State_HasFocus;   //去除焦点框

    QStylePainter p(this);
    //绘制QSS描述的如border-image等
    p.drawControl(QStyle::CE_PushButtonBevel, opt);

    QRect r = rect(); //style()->subElementRect ( QStyle::SE_PushButtonContents, &opt, this);

    int v_space = 2;
    int x = r.left() + (r.width() - opt.iconSize.width()) / 2;
    int h = opt.iconSize.height() + v_space + opt.fontMetrics.height();
    int y = r.top()  + (r.height() - h) / 2;

    //y -= 2;

    p.drawPixmap(x, y, opt.icon.pixmap(opt.iconSize));

    y += opt.iconSize.height() + v_space;
    y += opt.fontMetrics.ascent();  //加这个值的原因：The y-position is used as the baseline of the font.
    x = r.left() + (r.width() - opt.fontMetrics.width(opt.text)) / 2;
    p.drawText(x, y, opt.text);
}
//////////////////////////////////////////////////////////////////////////

QString g_common_btn =
    "QPushButton { background:transparent; border-image:url(:/images/btn_normal.png) 3 3; border-width: 3 3;}"\
    "QPushButton:hover, QPushButton:focus{border-image:url(:/images/btn_hover.png) 3 3; border-width: 3 3; }"\
    "QPushButton:pressed{ border-image:url(:/images/btn_down.png) 3 3; border-width: 3 3;}"\
    "QPushButton:disabled{ border-image:url(:/images/btn_disabled.png) 3 3; border-width: 3 3;}";


Common_Button::Common_Button(QWidget *parent /*= 0*/)
    :State_Button(parent)
{
    setMinimumSize(QSize(75, 26));
    setStyleSheet(g_common_btn);
}
