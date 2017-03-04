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

#ifndef _SKIN_H_
#define _SKIN_H_

#include <QScopedPointer>
#include <QPixmap>
#include <QMargins>

//边框图片：包含一张背景图, qss的border-width, qss的margin
class Border_Image
{
public:
    const QMargins& margin() const {return margin_;}
    const QMargins& border() const {return border_;}
    const QPixmap&  pixmap() const {return pixmap_;}
    const QString&  pixmap_url() const {return pixmap_url_;}

public:
    void set_pixmap(const QString& url);
    void set_pixmap(const QPixmap& pixmap);

    //order: left top right bottom
    void set_border(const QString& border); 
    void set_border(const QMargins& border);
    void set_border(int left, int top, int right, int bottom);

    void set_margin(const QString& border);
    void set_margin(const QMargins& border);
    void set_margin(int left, int top, int right, int bottom);

    void load(const QString& pixmap_url, const QString& border, const QString& margin);

private:
    QMargins margin_;
    QMargins border_;
    QPixmap  pixmap_;
    QString  pixmap_url_;
};

class QSettings;
class Skin
{
public:
    Skin();
    ~Skin();

public:
    //应用程序图标
    const QPixmap& app_pixmap() const {return app_pixmap_;}
    void set_app_pixmap(const QPixmap& pixmap) {app_pixmap_ = pixmap;}

    //最小化按钮,4种状态
    const QPixmap& min_pixmap() const {return min_pixmap_;}
    void set_min_pixmap(const QPixmap& pixmap){min_pixmap_ = pixmap;}

    //最大化按钮,4种状态
    const QPixmap& max_pixmap() const {return max_pixmap_;}
    void set_max_pixmap(const QPixmap& pixmap){max_pixmap_ = pixmap;}

    //恢复按钮,4种状态
    const QPixmap& restore_pixmap() const {return restore_pixmap_;}
    void set_restore_pixmap(const QPixmap& pixmap){restore_pixmap_ = pixmap;}
    
    //关闭按钮,4种状态
    const QPixmap& close_pixmap() const {return close_pixmap_;}
    void set_close_pixmap(const QPixmap& pixmap){close_pixmap_ = pixmap;}
    
    //换肤按钮，4种状态
    const QPixmap& skin_pixmap() const {return skin_pixmap_;}
    void set_skin_pixmap(const QPixmap& pixmap){skin_pixmap_ = pixmap;}

    //菜单按钮，4种状态
    const QPixmap& menu_pixmap() const {return menu_pixmap_;}
    void set_menu_pixmap(const QPixmap& pixmap){menu_pixmap_ = pixmap;}
    
    //标题的QSS,这是一个label
    const QString& titlebar_qss() const {return titlebar_qss_;}
    void set_titlebar_qss(const QString& qss){titlebar_qss_ = qss;}

    //标题栏的背景
    const Border_Image& titlebar_background() const {return titlebar_background_;}
    Border_Image& titlebar_background() {return titlebar_background_;}

    //标题栏高度. -1: 设置为背景图片的高度; 0: 设置为当前样式标题栏的高度: 1~N: 高度即为此值
    int titlebar_height() const {return titlebar_height_;}
    void set_titlebar_height(int h) {titlebar_height_ = h;}

    //titlebar样式, 指定显示哪些按钮
    int titlebar_showstyle() const {return titlebar_showstyle_;}
    void set_titlebar_showstyle(int s){titlebar_showstyle_ = s;}

    //Base_Widget在创建后默认使用的qss, 可以用来设置字体
    const QString& widget_qss() const {return widget_qss_;}
    void set_widget_qss(const QString& qss){widget_qss_ = qss;}

    //背景
    inline const Border_Image& background() const {return background_;}
    inline Border_Image& background() {return background_;}

    //客户区背景图
    inline const QPixmap& client_pixmap() const {return client_pixmap_;}
    QPixmap& client_pixmap() {return client_pixmap_;}
    void set_client_pixmap(const QPixmap& pixmap);
    void set_client_pixmap(const QString& url);

    //客户区背景绘制方式
    inline int client_draw_type() const {return client_draw_type_;}
    void set_client_draw_type(int v);

    //圆角
    int round_radius_x() const {return round_radius_x_;}
    int round_radius_y() const {return round_raidus_y_;}
    void set_round_radius(int x, int y);
    void set_round_radius(const QString& radius);

public:
    //读取皮肤. 默认从skin.ini中读取default节作为skin
    virtual void load();

    //从ini中读取皮肤配置
    void load_from_ini(const QString& ini_file_name, const QString& section);

    //从配置文件中读取Skin, 返回Skin对象(由调用者删除)
    //@ini_file_name, ini配置文件; @section, ini文件中的节
    static Skin* read_config_skin(const QString& ini_file_name, const QString& section);

protected:
    void load_pixmap(QSettings* ini, QPixmap& pixmap, const QString& key);
    void load_border_image(QSettings* ini, Border_Image& bi, 
                           const QString& bg_key, const QString& border_key, 
                           const QString& margin_key);
    void load_int(QSettings* ini, int& i, const QString& key);
    void load_string(QSettings* ini, QString& str, const QString& key);

protected:
    //图片资源
    QPixmap      app_pixmap_;
    QPixmap      min_pixmap_;
    QPixmap      max_pixmap_;
    QPixmap      restore_pixmap_;
    QPixmap      close_pixmap_;
    QPixmap      skin_pixmap_;
    QPixmap      menu_pixmap_;

    //标题QSS,QLabel
    QString      titlebar_qss_;
    //titlebar边框图
    Border_Image titlebar_background_;
    //titlebar高度
    int          titlebar_height_;
    //titlebar样式, 指定显示哪些按钮
    int          titlebar_showstyle_;

    //背景图, 相当于frame
    Border_Image background_;
    //Base_Widget在创建后默认使用的qss, 设置一些公共属性，如：字体
    QString      widget_qss_;
    //客户区背景图片
    QPixmap      client_pixmap_;
    //客户区背景图片拉伸方式： 1-从左上固定，右下拉伸；2-右上固定，左下拉伸; 3-将图片拉伸至整个背景(可能会导致背景失真!)
    int          client_draw_type_;

    //圆角
    int         round_radius_x_, round_raidus_y_;
};

class Skin_Manager: public QObject
{
public:
    Skin_Manager(QObject *parent=0);
    ~Skin_Manager();

public:
    //从ini文件中加载skin
    void store(const QString& name, const QString& ini_file_name, const QString& section);
    void store(const QString& name, Skin* skin);
    void store(const QString& name, const QString& section);

    Skin* remove(const QString& name);
    void  erase(const QString& name);
    void  clear();

    Skin* default_skin();         //ini文件中[default]描述的skin
    Skin* msgbox_skin();          //ini文件中[msgbox]节描述的skin
    Skin* get(const QString& skin_name);

    static Skin_Manager* instance();

private:
    QHash<QString, Skin*> skin_hash_;
    QString               ini_file_;
};

#define skinman Skin_Manager::instance()

#endif
