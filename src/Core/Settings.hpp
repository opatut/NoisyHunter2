#ifndef _SETTINGS
#define _SETTINGS

#include <QString>
#include <QMap>
#include <QFile>
#include <QFileInfo>

class Settings {
public:
    static Settings& GetInstance();

    bool GetBool(QString key, bool def = false);
    int GetInt(QString key, int def = 0);
    float GetFloat(QString key, float def = 0);
    QString GetString(QString key, QString def = "");

    void SetBool(QString key, bool value);
    void SetInt(QString key, int value);
    void SetFloat(QString key, float value);
    void SetString(QString key, QString value);

    void Save(QFileInfo file);
    void Load(QFileInfo file);

private:
    void _Parse(QString s);
    QString _Compile();

    QMap<QString, QString> mKeyValues;
};

#endif
