#include "Level.hpp"

#include "Core/Resources.hpp"

#include "Entities/Rock.hpp"

Level::Level(QString name)
    : Entity(name) {
    Generate();
    mInfo = sf::Text("Level 01", Resources::GetInstance().GetDefaultFont());
    mInfo.SetPosition(10, 10);
    mInfo.SetCharacterSize(10);
}

void Level::OnDraw(sf::RenderTarget& target) {
    target.Draw(mInfo);
}

void Level::Generate() {
    for(unsigned int i = 0; i < 100; ++i) {
        for(unsigned int j = 0; j < 10; ++j) {
            Rock* r = new Rock("rocks-" + QString::number(i) + "-" + QString::number(j), "01");
            r->Position.x = i * 50;
            r->Position.y = 400 + j * 40;
            r->Rotation = i * 10000000.123 + j * 1001.5213 + i * j + sqrt(j) + 20 * sin(i);
            AddChild(r);
        }
    }
}
