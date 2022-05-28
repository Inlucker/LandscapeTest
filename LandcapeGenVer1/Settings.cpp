#include "Settings.h"
#include <QSettings>
#include <QMetaEnum>
//#include <QRegExp>
#include <QRegularExpression>
#include <QStringList>

Settings::Settings()
{
    const QMetaObject &mo = staticMetaObject;
    int idx = mo.indexOfEnumerator("Key");
    keys = mo.enumerator(idx);

    idx = mo.indexOfEnumerator("Section");
    sections = mo.enumerator(idx);
}

QVariant Settings::get(Key k, Section s)
{
    Settings &self = instance();
    QString key = self.keyPath(s, k);
    QVariant res = self.conf.value(key, self.defaults[key]);
    QString str = res.toString();
    int i = res.toInt();
    return res;
}

Settings::ValueRef Settings::set(Key k, Section s)
{
    Settings &self = instance();
    return ValueRef(self, self.keyPath(s, k));
}

void Settings::setDefaults(const QString &str)
{
    Settings &self = instance();

    //section/key : value
    //section - optional
    QRegularExpression rxRecord("^\\s*(((\\w+)/)?(\\w+))\\s*:\\s*([^\\s].{0,})\\b\\s*$");

    //qDebug() << "TEST";

    auto kvs = str.split(QRegularExpression(";\\W*"), Qt::SkipEmptyParts); //key-values
    //auto kvs = str.split(";\\W*", Qt::SkipEmptyParts); //key-values
    for(auto kv : kvs)
    {
        QRegularExpressionMatchIterator i = rxRecord.globalMatch(kv);
        while (i.hasNext())
        {
            QRegularExpressionMatch match = i.next();

            QString section = match.captured(3);
            QString key = match.captured(4);
            QString value = match.captured(5);

            /*qDebug() << match.captured(3);
            qDebug() << match.captured(4);
            qDebug() << match.captured(5);
            qDebug() << match.captured(1);
            qDebug() << "NEXT:";*/
            int iKey = self.keys.keyToValue(key.toLocal8Bit().data());
            if (iKey != -1)
            {
                //const char* data = section.toLocal8Bit().data();
                //QMetaEnum met_enum = self.sections;
                int iSection = self.sections.keyToValue(section.toLocal8Bit().data());
                if (section.isEmpty() || iSection != -1)
                {
                    self.defaults[match.captured(1)] = value;
                }
            }
        }
        //qDebug() << kv;
        /*if (kv.indexOf(rxRecord) != -1)
        {
            QString section = rxRecord.captured(3);
            QString key = rxRecord.cap(4);
            QString value = rxRecord.cap(5);

            int iKey = self.keys.keyToValue(key.toLocal8Bit().data());
            if (iKey != -1)
            {
                int iSection = self.sections.keyToValue(section.toLocal8Bit().data());
                if (section.isEmpty() || iSection != -1)
                {
                    self.defaults[rxRecord.cap(1)] = value;
                }
            }
        }*/
        /*if (rxRecord.indexIn(kv) != -1)
        {
            QString section = rxRecord.cap(3);
            QString key = rxRecord.cap(4);
            QString value = rxRecord.cap(5);

            int iKey = self.keys.keyToValue(key.toLocal8Bit().data());
            if (iKey != -1)
            {
                int iSection = self.sections.keyToValue(section.toLocal8Bit().data());
                if (section.isEmpty() || iSection != -1)
                {
                    self.defaults[rxRecord.cap(1)] = value;
                }
            }
        }*/
    }
}

//Settings::ValueRef-----------------------------------------------------------
Settings::ValueRef & Settings::ValueRef::operator = (const QVariant &data)
{
    parent.conf.setValue(keyPath, data);
    return *this;
}


//PRIVATE METHODS--------------------------------------------------------------
QString Settings::keyPath(Section s, Key k)
{
    auto szSection = sections.valueToKey(s);
    auto szKey = keys.valueToKey(k);
    return QString(s == General ? "%1" : "%2/%1").arg(szKey).arg(szSection);
}

Settings & Settings::instance()
{
    static Settings singleton;
    return singleton;
}
