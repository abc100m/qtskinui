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

#include "Base_Widget.h"
#include "my_widget.h"
#include <QApplication>



const QString& app_path() {
    static QString path(QApplication::applicationDirPath() + "/");
    return path;
}

QString load_txt_file(const QString& file_name)
{
    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return QString("");
    }

    QByteArray data_byte = file.readAll();
    QTextStream ts(&data_byte);
    ts.setCodec("UTF-8");
    return ts.readAll();
}

#define cstr(str) QString::fromLocal8Bit(str)

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //加载全局QSS
    a.setStyleSheet(load_txt_file(app_path() + QStringLiteral("globalqss.config")));

    //主窗口
    Main_Form w;
    w.setWindowTitle(cstr("qt skin ui"));
    w.set_child_bkg_alpha(128);
    w.resize(400, 600);
    w.show();

    return a.exec();

}

