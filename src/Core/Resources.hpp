#ifndef _RESOURCES
#define _RESOURCES

#include <QDir>
#include <QMap>

#include <SFML/Graphics.hpp>

class Resources {
public:
    static Resources& GetInstance();

    void ReadPath(QDir path, QString prefix = "", bool direct_load = false);
    void LoadQueue();
    void LoadFile(QString path, QString name);

    const sf::Texture& GetTexture(QString filename);
    void SetTextureSmooth(QString name, bool smooth);
    const sf::Font& GetDefaultFont();
    const sf::Font& GetFont(QString filename);
    void SetDefaultFont(QString name);

    QString GetNextID();

    int GetQueueItem();
    int GetQueueSize();

private:
    Resources();

    void _LoadFont(QString path, QString name);
    void _LoadTexture(QString path, QString name);

    QMap<QString, sf::Texture> mTextures;
    QMap<QString, sf::Font> mFonts;
    QString mDefaultFont;
    int mLastId;

    QMap<QString, QString> mQueue; // path <-> name
    int mQueueItem;

};

#endif
