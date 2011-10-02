#include "Settings.hpp"

#include <iostream>
#include <QStringList>

Settings& Settings::GetInstance() {
    static Settings instance;
    return instance;
}

bool Settings::GetBool(QString key, bool def) {
    QString v = GetString(key).toLower();
    if(v == "")
        return def;
    return (v == "1" || v == "yes" || v == "y" || v == "true" || v == "on" || v == "+");
}

int Settings::GetInt(QString key, int def) {
    QString v = GetString(key).toLower();
    if(v == "")
        return def;
    return v.toInt();
}

float Settings::GetFloat(QString key, float def) {
    QString v = GetString(key).toLower();
    if(v == "")
        return def;
    return v.toFloat();
}

QString Settings::GetString(QString key, QString def) {
    return mKeyValues.value(key, def); }

void Settings::SetBool(QString key, bool value) {
    SetString(key, value ? "true" : "false");
}

void Settings::SetInt(QString key, int value) {
    SetString(key, QString("%i").arg(value));
}

void Settings::SetFloat(QString key, float value) {
    SetString(key, QString("%f").arg(value));
}

void Settings::SetString(QString key, QString value) {
    mKeyValues.insert(key, value);
}

void Settings::Save(QFileInfo file) {

}

void Settings::Load(QFileInfo file) {
    QFile f(file.absoluteFilePath());
    if(f.open(QFile::ReadOnly | QFile::Text)) {
        QString content;
        while(!f.atEnd()) {
            content += f.readLine() + "\n";
        }
        _Parse(content);
        f.close();
    } else {
        std::cerr << "Cannot open settings file: " << file.fileName().toStdString() << std::endl;
    }
}

void Settings::_Parse(QString s) {
    QStringList lines = s.split("\n");
    for(QStringList::iterator iter = lines.begin(); iter != lines.end(); ++iter) {
        QString line = (*iter).trimmed();
        if(!line.startsWith("#")) {
            QStringList split = line.split("=");
            if(split.length() > 1) {
                QString key = split[0].trimmed();
                split.removeAt(0);
                QString value = split.join("=").trimmed();

                SetString(key, value);
            }
        }
    }
}

QString Settings::_Compile() {
    return "";
}
