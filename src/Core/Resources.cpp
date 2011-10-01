#include "Resources.hpp"

#include <iostream>

Resources::Resources() {
    mDefaultFont = "";
}

Resources& Resources::GetInstance() {
    static Resources instance;
    return instance;
}

void Resources::ReadPath(QDir path, QString prefix, bool direct_load) {
    QFileInfoList list = path.entryInfoList();
    for(QFileInfoList::iterator info = list.begin(); info != list.end(); ++info) {
        QFileInfo i = *info;
        if(i.isDir() && i.fileName() != "." && i.fileName() != "..")  {
            ReadPath(i.absoluteFilePath(), prefix + i.fileName() + "/", direct_load);
        } else if(i.isFile()) {
            if(direct_load)
                LoadFile(i.absoluteFilePath(), prefix + i.fileName());
            else
                mQueue.insert(i.absoluteFilePath(), prefix + i.fileName());
        }
    }
}

void Resources::LoadQueue() {
    mQueueItem = 0;
    for(QMap<QString,QString>::iterator iter = mQueue.begin(); iter != mQueue.end(); ++iter) {
        LoadFile(iter.key(), iter.value());
        ++mQueueItem;
        sf::Sleep(50);
    }
}

int Resources::GetQueueItem() {
    return mQueueItem;
}

int Resources::GetQueueSize() {
    return mQueue.size();
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

void Resources::SetTextureSmooth(QString name, bool smooth) {
    if(mTextures.contains(name)) {
        mTextures[name].SetSmooth(smooth);
    }

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
