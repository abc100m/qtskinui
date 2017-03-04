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

#ifndef _BASE_WIDGET_H_
#define _BASE_WIDGET_H_

#include <QtWidgets/QtWidgets>
#include <QWidget>
#include <QDialog>

#include "Skin.h"
#include "Title_Bar.h"

//class Title_Bar;
//class Skin;
class NcFramelessHelper;


class Base_Widget_Imp
{
public:
    Base_Widget_Imp(QWidget *owner, Skin *skin = NULL, bool is_dialog = false);
    ~Base_Widget_Imp();

public:
    //是否允许通过鼠标改变窗口大小
    bool get_resizable() const {return resizable_;}
    void set_resizable(bool b);

    //overwrite
    bool isMaximized() const;
    QString windowTitle() const;
    void setWindowTitle(const QString &);

    //skin
    void load_skin(Skin* skin=NULL);

    //显示一个Widget, 这Widget作为内容
    void setup_widget(QWidget *content);

    //保存对话框位置, 0成功，其它值失败
    int save_geometry(const QString& name);
    int save_geometry();

    //恢复对话框位置, 0成功，其它值失败
    int load_geometry(const QString& name);

    //在主窗或屏幕居中
    void move_center();

    //除去边框后的客户区rect
    QRect client_rect() const;

    //画好的背景图片
    const QPixmap* bg_pixmap() const;

    //将一个窗口坐标点调整到客户区坐标
    QPoint window_to_client(const QPoint& pt);
    QRect  window_to_client(const QRect& rt);

    //将一个客户区坐标调整到窗口坐标
    QPoint client_to_window(const QPoint& pt);
    QRect  client_to_window(const QRect& rt);

    //事件过滤，处理paintEvent, 控制子窗口对背景图的alpha透明
    bool eventFilter( QObject *o, QEvent *e );

    //子窗口背景alpha, 0-255(0:全透明；255-不透明)
    inline int child_bkg_alpha() const {return child_bkg_alpha_;}
    void set_child_bkg_alpha(int alpha); 

    //背景已修改
    void set_bg_changed() {
        recreate_bg_pixmap_ = true;
    }

public:
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *);

private:
    void load_skin_internal();

    //画背景图, 左上角画原始图，右下角拉伸
    void draw_bg_topleft(QPainter *painter, const QRect& r, const QPixmap& img);

    //画背景图, 右上角画原始图，左下角拉伸
    void draw_bg_topright(QPainter *painter, const QRect& r, const QPixmap& img);

protected:
    int  init(bool is_dialog);    //初始化

public:
    QVBoxLayout  *layout_;                      //由其parent删除
    Title_Bar    *title_bar_;                   //由其parent删除
    Skin         *skin_;                        //不删除

private:
    bool               resize_temp_disabled_;   //当窗口最大化后禁止拖动改变大小
    bool               resizable_;              //是否允许改变窗口的大小
    bool               recreate_bg_pixmap_;     //是否需要重新创建客户区图像
    QPixmap           *bg_pixmap_;              //画好的背景图像
    NcFramelessHelper *resize_helper_;
    QString            save_object_name_;       //这个对象名用于将窗口大小、位置保存
    int                child_bkg_alpha_;         //子窗口背景alpha
    QHash<QObject*, QPixmap*> alpha_cache_;      //保存子控件alpha透明后的背景图

private:
    QWidget *q;                                 //owner
};

//T can be QWidget or QDialog, 
//template class can not have Q_OBJECT, so this class can not have signal/slot
template<class T>
class Base_Widget: public T
{
public:
    Base_Widget(QWidget* parent=NULL, Skin* skin=NULL)
        :T(parent)
    {
        p = new Base_Widget_Imp(this, skin, inherits("QDialog")/*typeid(T) == typeid(QDialog)*/);
    }

    ~Base_Widget()
    {
        delete p;
    }

    typedef typename Base_Widget<T> BaseClass;

public:
    //是否允许通过鼠标改变窗口大小
    bool get_resizable() const {return p->resizable_;}
    void set_resizable(bool b) {p->set_resizable(b);}

    //overwrite
    bool isMaximized() const {return p->isMaximized();}
    QString windowTitle() const {return p->windowTitle();}
    void setWindowTitle(const QString &s) {p->setWindowTitle(s);}

    //skin
    virtual void load_skin(Skin* skin=NULL) {p->load_skin(skin);}

    //设置显示的内容. 用Qt Designer设计对话框, 然后调用此方法加入到layout_中
    template<typename UI>
    QWidget* setup_UI(UI* ui)
    {
        QWidget *content = new QWidget(this);   //由parent删除
        ui->setupUi(content);
        setup_widget(content);
        return content;
    }

    //显示一个Widget, 这Widget作为内容
    void setup_widget(QWidget *content) {p->setup_widget(content);}

    //保存对话框位置, 0成功，其它值失败
    int save_geometry(const QString& name) {return p->save_geometry(name);}
    int save_geometry() {return p->save_geometry();}

    //恢复对话框位置, 0成功，其它值失败
    int load_geometry(const QString& name) {return p->load_geometry(name);}

    //在主窗或屏幕居中
    void move_center() {p->move_center();}

    //除去边框后的客户区rect
    QRect client_rect() const {return p->client_rect();}

    //背景图片
    const QPixmap* bg_pixmap() const {return p->bg_pixmap();}

    //将一个窗口坐标点调整到客户区坐标
    QPoint window_to_client(const QPoint& pt) {return p->window_to_client(pt);}
    QRect  window_to_client(const QRect& rt) {return p->window_to_client(rt);}

    //将一个客户区坐标调整到窗口坐标
    QPoint client_to_window(const QPoint& pt) {return p->client_to_window(pt);}
    QRect  client_to_window(const QRect& rt) {return p->client_to_window(rt);}

    /*
    事件过滤，处理paintEvent, 让子窗口相对于背景图片alpha透明
    子窗口需设置一个半透明的背景图，再installEventFilter(w), 然后窗口即可调整子窗口相对于背景的透明度
    */
    bool eventFilter( QObject *o, QEvent *e )
    {
        if (alpha_children_.contains(o)) {
            if (p->eventFilter(o, e)) {
                return true;
            }
        }
        return T::eventFilter(o, e);
    }

    //子窗口背景alpha, 0-255(0:全透明；255-不透明)
    inline int child_bkg_alpha() const {p->child_bkg_alpha();}
    inline void set_child_bkg_alpha(int alpha) {p->set_child_bkg_alpha(alpha);}

    //让子控件@child的背景alpha透明. 先用qss为@child设置一个半透明的border-image
    void make_bkg_alpha(QWidget *child) 
    {
        alpha_children_.insert(child); 
        child->installEventFilter(this);
    }

    void redraw_background() {
        p->set_bg_changed();
        this->update();
    }

public:
    QVBoxLayout*  layout()    {return p->layout_;}
    Title_Bar*    title_bar() {return p->title_bar_;}
    Skin*         skin()      {return p->skin_;}

protected:
    void resizeEvent(QResizeEvent *e) {p->resizeEvent(e);}
    void paintEvent(QPaintEvent *e) {p->paintEvent(e);}

private:
    Base_Widget_Imp *p;
    QSet<QObject*> alpha_children_;
};

//将@child居中到@parent
void CenterParent(QWidget* parent, QWidget* child);


#endif

