//#include "mainwindow.h"
#include "BaseWindow.h"
#include "settings.h"

#include <QApplication>
#include <QFile>
#include <QDir>
#include <QScopedPointer>
#include <QTextStream>
#include <QDateTime>
#include <QLoggingCategory>

// Умный указатель на файл логирования
QScopedPointer<QFile>   m_logFile;

// Объявляение обработчика
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Устанавливаем конфиг файл
    QApplication::setOrganizationName("Organization name");
    QApplication::setApplicationName("App name");
    QFile cfgDefaults("./config/default.cfg");  // я обычно дефолтовые настройки помещаю в ресурсы
    cfgDefaults.open(QIODevice::ReadOnly);
    Settings::setDefaults(cfgDefaults.readAll());
    Settings::setDefaults("DataBase/DBHost: localhost; DataBase/DBPort: 5432; DataBase/DBName: postgres; DataBase/DBUser: guest; \nDataBase/DBPassword: guest; Size: 122;");
    qDebug() << Settings::get(Settings::DBUser, Settings::DataBase).toString();
    int size = Settings::get(Settings::Size).toInt();
    qDebug() << "before:" << size;
    Settings::set(Settings::Size) = "1234";
    size = Settings::get(Settings::Size).toInt();
    qDebug() << "after:"<< size;

    Settings::setDefaults(cfgDefaults.readAll());
    size = Settings::get(Settings::Size).toInt();
    qDebug() << "afterafter:"<< size;

    // Устанавливаем файл логирования,
    // внимательно сверьтесь с тем, какой используете путь для файла
    m_logFile.reset(new QFile("./logFile.txt"));
    // Открываем файл логирования
    m_logFile.data()->open(QFile::Append | QFile::Text);
    // Устанавливаем обработчик
    qInstallMessageHandler(messageHandler);

    //MainWindow w;
    BaseWindow w;
    w.show();
    return a.exec();
}

// Реализация обработчика
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // Открываем поток записи в файл
    QTextStream out(m_logFile.data());
    // Записываем дату записи
    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");
    // По типу определяем, к какому уровню относится сообщение
    switch (type)
    {
    //case QtInfoMsg:     out << "INF "; break;
    case QtInfoMsg:     out << "UAC "; break;
    case QtDebugMsg:    out << "DBG "; break;
    //case QtWarningMsg:  out << "WRN "; break;
    case QtWarningMsg:  out << "EXC "; break;
    case QtCriticalMsg: out << "CRT "; break;
    case QtFatalMsg:    out << "FTL "; break;
    }
    // Записываем в вывод категорию сообщения и само сообщение
    out << context.category << ": "
        << msg << "\n";
    out.flush();    // Очищаем буферизированные данные
}
