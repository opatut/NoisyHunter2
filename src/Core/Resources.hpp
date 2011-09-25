#ifndef _RESOURCES
#define _RESOURCES

#include <QDir>
#include <QMap>

#include <SFML/Graphics.hpp>

class Resources {
public:
    static Resources& GetInstance();

    void LoadPath(QDir path, QString prefix = "");
    void LoadFile(QString path, QString name);

    const sf::Texture& GetTexture(QString filename);
    void SetTextureSmooth(QString name, bool smooth);
    const sf::Font& GetDefaultFont();
    const sf::Font& GetFont(QString filename);
    void SetDefaultFont(QString name);

    QString GetNextID();

private:
    Resources();

    void _LoadFont(QString path, QString name);
    void _LoadTexture(QString path, QString name);

    QMap<QString, sf::Texture> mTextures;
    QMap<QString, sf::Font> mFonts;
    QString mDefaultFont;
    int mLastId;

};

#endif
