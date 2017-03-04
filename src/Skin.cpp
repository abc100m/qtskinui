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

#include "Skin.h"
#include "Title_Bar.h"  //use: Title_Bar::str2style
#include <QTextStream>
#include <QSettings>

Skin::Skin()
    :titlebar_height_(0)
    ,titlebar_showstyle_(-1)
    ,round_radius_x_(0)
    ,round_raidus_y_(0)
    ,client_draw_type_(1)
{
}

Skin::~Skin()
{
}

void Skin::load()
{
    load_from_ini(":/skin.ini", "default");
}

void Skin::set_round_radius( int x, int y )
{
    round_radius_x_ = x;
    round_raidus_y_ = y;
}

void Skin::set_round_radius( const QString& radius )
{
    QTextStream qs((QString*)&radius);
    int x, y;
    qs >> x >> y;
    set_round_radius(x, y);
}

void Skin::load_pixmap(QSettings* ini, QPixmap& pixmap, const QString& key )
{
    QString val = ini->value(key).toString();
    if (!val.isEmpty())
    {
        pixmap.load(val);
    }
}

void Skin::load_border_image( QSettings* ini, Border_Image& bi, 
                             const QString& bg_key, const QString& border_key, 
                             const QString& margin_key 
                            )
{
    QString bg_val     = ini->value(bg_key).toString();
    QString border_val = ini->value(border_key).toString();
    QString margin_val = ini->value(margin_key).toString();

    if (!bg_val.isEmpty())
    {
        bi.set_pixmap(bg_val);
    }
    if (!border_val.isEmpty())
    {
        bi.set_border(border_val);
    }
    if (!margin_val.isEmpty())
    {
        bi.set_margin(margin_val);
    }
}

void Skin::load_int( QSettings* ini, int& i, const QString& key )
{
    QString val = ini->value(key).toString();
    if (!val.isEmpty())
    {
        i = val.toInt();
    }
}

void Skin::load_string( QSettings* ini, QString& str, const QString& key )
{
    QString val = ini->value(key).toString();
    if (!val.isEmpty())
    {
        str = val;
    }
}

void Skin::load_from_ini( const QString& ini_file_name, const QString& section )
{
    QSettings settings(ini_file_name, QSettings::IniFormat);
    settings.setIniCodec("GB2312");     //GB2312-->ini必须保存为ascii码, 否则是乱码
    QString val;

    settings.beginGroup(section);

    //inherit
    val = settings.value("inherit").toString();
    if (!val.isEmpty())
    {
        load_from_ini(ini_file_name, val);
    }

    //pixmap
    load_pixmap(&settings, app_pixmap_, "icon_pixmap");
    load_pixmap(&settings, min_pixmap_, "min_pixmap");
    load_pixmap(&settings, max_pixmap_, "max_pixmap");
    load_pixmap(&settings, restore_pixmap_, "restore_pixmap");
    load_pixmap(&settings, close_pixmap_, "close_pixmap");
    load_pixmap(&settings, skin_pixmap_, "skin_pixmap");
    load_pixmap(&settings, menu_pixmap_, "menu_pixmap");

    //titilebar
    load_border_image(&settings, titlebar_background_, "titlebar_bg", "titlebar_border", "titlebar_margin");
    load_int(&settings, titlebar_height_, "titlebar_height");
    load_string(&settings, titlebar_qss_, "titlebar_qss");
    //titilebar样式, 显示哪些按钮
    val = settings.value("titlebar_style").toString();
    if (!val.isEmpty())
    {
        titlebar_showstyle_ = Title_Bar::str2showstyle(val.toLocal8Bit().data());
    }

    //main widget
    load_border_image(&settings, background_, "widget_bg", "widget_border", "widget_margin");
    load_string(&settings, widget_qss_, "widget_qss");

    //client pximap
    val = settings.value("widget_client_pixmap").toString();
    if (!val.isEmpty() || val == QStringLiteral("none"))
    {
        set_client_pixmap(val);
    }

    //client draw type
    load_int(&settings, client_draw_type_, "widget_client_draw_type");

    //round radius
    val = settings.value("round_radius").toString();
    if (!val.isEmpty())
    {
        set_round_radius(val);
    }

    settings.endGroup();
}

Skin* Skin::read_config_skin( const QString& ini_file_name, const QString& section )
{
    Skin* skin = new Skin();
    skin->load_from_ini(ini_file_name, section);
    return skin;
}

void Skin::set_client_pixmap( const QString& url )
{
    QPixmap pmp;
    pmp.load(url);
    client_pixmap_.swap(pmp);
}

void Skin::set_client_pixmap( const QPixmap& pixmap )
{
    client_pixmap_ = pixmap;
}

void Skin::set_client_draw_type( int v )
{
    client_draw_type_ = v;
}

////////////////////Border_Image/////////////////////////////////////////////////

void Border_Image::set_pixmap( const QString& url )
{
    pixmap_url_ = url;
    pixmap_.load(url);
}

void Border_Image::set_pixmap( const QPixmap& pixmap )
{
    pixmap_ = pixmap;
}

void Border_Image::set_border( const QString& border )
{
    QTextStream qs((QString*)&border);
    int left, top, right, bottom;
    qs >> left >> top >> right >> bottom;
    set_border(left, top, right, bottom);
}

void Border_Image::set_border( const QMargins& border )
{
    border_ = border;
}

void Border_Image::set_border( int left, int top, int right, int bottom )
{
    QMargins m(left, top, right, bottom);
    border_ = m;
}

void Border_Image::set_margin( const QString& border )
{
    QTextStream qs((QString*)&border);
    int left, top, right, bottom;
    qs >> left >> top >> right >> bottom;
    set_margin(left, top, right, bottom);
}

void Border_Image::set_margin( const QMargins& border )
{
    margin_ = border;
}

void Border_Image::set_margin( int left, int top, int right, int bottom )
{
    QMargins m(left, top, right, bottom);
    margin_ = m;
}

void Border_Image::load( const QString& pixmap_url, const QString& border, const QString& margin )
{
    set_pixmap(pixmap_url);
    set_border(border);
    set_margin(margin);
}
//////////////////////////////////////////////////////////////////////////

Skin_Manager::Skin_Manager( QObject *parent/*=0*/ )
    :QObject(parent)
{
    QString f = QApplication::applicationDirPath() + "/skin.ini";
    if (QFile::exists(f))
    {
        ini_file_ = f;
    }else{
        ini_file_ = ":/skin.ini";
    }

    store("default", ini_file_, "default");
}

Skin_Manager::~Skin_Manager()
{
    clear();
}

void Skin_Manager::store( const QString& name, const QString& ini_file_name, const QString& section )
{
    Skin *skin = Skin::read_config_skin(ini_file_name, section);
    store(name, skin);
}

void Skin_Manager::store( const QString& name, Skin* skin )
{
    erase(name);
    skin_hash_.insert(name, skin);
}

void Skin_Manager::store( const QString& name, const QString& section )
{
    store(name, ini_file_, section);
}

Skin* Skin_Manager::remove( const QString& name )
{
    if (skin_hash_.contains(name))
    {
        return skin_hash_.take(name);
    }
    return NULL;
}

void Skin_Manager::erase( const QString& name )
{
    Skin *skin = remove(name);
    if (skin) { delete skin; }
}

void Skin_Manager::clear()
{
    for (QHash<QString, Skin*>::iterator it=skin_hash_.begin(); 
         it != skin_hash_.end(); 
         ++it
        )
    {
        delete it.value();
    }
    skin_hash_.clear();
}

Skin* Skin_Manager::default_skin()
{
    static const QString skin_name("default");
    return get(skin_name);
}

Skin* Skin_Manager::get( const QString& skin_name )
{
    if (skin_hash_.contains(skin_name))
    {
        return skin_hash_.value(skin_name);
    }

    store(skin_name, skin_name);
    if (skin_hash_.contains(skin_name))
    {
        return skin_hash_.value(skin_name);
    }

    return NULL;
}

Skin_Manager* Skin_Manager::instance()
{
    static QScopedPointer<Skin_Manager> s_instance(new Skin_Manager(0));
    return s_instance.data();
}

Skin* Skin_Manager::msgbox_skin()
{
    static const QString section("msgbox");
    return get(section);
    
    //if (!skin_hash_.contains(section))
    //{
    //    store(section, section);
    //}
    //return get(section);
}
