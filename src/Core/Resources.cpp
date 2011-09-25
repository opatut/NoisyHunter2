#include "Resources.hpp"

#include <iostream>

Resources::Resources() {
    mDefaultFont = "";
}

Resources& Resources::GetInstance() {
    static Resources instance;
    return instance;
}

void Resources::LoadPath(QDir path, QString prefix) {
    QFileInfoList list = path.entryInfoList();
    for(QFileInfoList::iterator info = list.begin(); info != list.end(); ++info) {
        QFileInfo i = *info;
        if(i.isDir() && i.fileName() != "." && i.fileName() != "..")  {
            LoadPath(i.absoluteFilePath(), prefix + i.fileName() + "/");
        } else if(i.isFile()) {
            LoadFile(i.absoluteFilePath(), prefix + i.fileName());
        }
    }
}

void Resources::LoadFile(QString path, QString name) {
    if(path.endsWith(".ttf", Qt::CaseInsensitive)) {
        _LoadFont(path, name);
    }
    if(path.endsWith(".png", Qt::CaseInsensitive)) {
        _LoadTexture(path, name);
    }
}

const sf::Texture& Resources::GetTexture(QString filename) {
    if(!mTextures.contains(filename)) {
        std::cerr << "Error: Cannot find texture \"" << filename.toStdString() << "\" - Returning empty texture." << std::endl;
    }
    return mTextures[filename];
}

const sf::Font& Resources::GetDefaultFont() {
    if(mDefaultFont == "") {
        return sf::Font::GetDefaultFont();
    }
    return GetFont(mDefaultFont);
}

const sf::Font& Resources::GetFont(QString filename) {
    if(!mFonts.contains(filename)) {
        std::cerr << "Error: Cannot get font \"" << filename.toStdString() << "\" - Returning default font." << std::endl;
        return sf::Font::GetDefaultFont();
    }
    return mFonts[filename];
}

void Resources::_LoadFont(QString path, QString name) {
    sf::Font font;
    font.LoadFromFile(path.toStdString());
    mFonts.insert(name, font);
    if(mDefaultFont == "")
        SetDefaultFont(name);
}

void Resources::_LoadTexture(QString path, QString name) {
    sf::Texture texture;
    texture.LoadFromFile(path.toStdString());
    texture.SetSmooth(true);
    mTextures.insert(name, texture);
}

void Resources::SetDefaultFont(QString name) {
    mDefaultFont = name;
}

QString Resources::GetNextID() {
    mLastId++;
    return QString::number(mLastId);
}
