#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Submarine.hpp"
#include "BackgroundGradient.hpp"
#include "Resources.hpp"
#include "Text.hpp"
#include "Entity.hpp"
#include "Narwhal.hpp"
#include "Torpedo.hpp"

int LastID = 100;
QString NextID() {
    LastID++;
    return QString::number(LastID);
}

int main() {
    sf::RenderWindow app(sf::VideoMode(800, 600, 32), "NoisyHunter");
    app.SetFramerateLimit(60);

    Resources::GetInstance().LoadPath(QDir("../data"));

    Entity scene("scene");

    BackgroundGradient background("background");
    scene.AddChild(&background);

    Submarine submarine("submarine");
    scene.AddChild(&submarine);

    Narwhal narwhal("narwhal-01");
    scene.AddChild(&narwhal);

    Text text("text", "Noisy Hunter - Build 1");
    text.Position.x = 795;
    text.Position.y = 595;
    text.SetAlign(Text::TA_RIGHT | Text::TA_BOTTOM);
    text.SetSize(8);

    scene.AddChild(&text);

    Text fps("fps", "?? FPS");
    fps.Position.x = 795;
    fps.Position.y = 580;
    fps.SetAlign(Text::TA_RIGHT | Text::TA_BOTTOM);
    fps.SetSize(8);

    Text name("name", "opatut");
    name.Position.x = 0;
    name.Position.y = -24;
    submarine.AddChild(&name);
    name.SetAlign(Text::TA_BOTTOM);
    name.SetSize(9);

    scene.AddChild(&fps);

    sf::Clock clock;

    float time = 0;
    float avg_fps = 60;

    while(app.IsOpened()) {
        float time_diff = clock.GetElapsedTime() * 0.001;
        time += time_diff;
        clock.Reset();
        if(time_diff != 0)
            avg_fps -= (avg_fps - 1.f / time_diff) * 0.01;

        fps.SetCaption(QString::number(round(avg_fps)) + " FPS");

        sf::Event e;
        while(app.PollEvent(e)) {
            if(e.Type == sf::Event::Closed) {
                app.Close();
            } else if(e.Type == sf::Event::KeyPressed) {
                if(e.Key.Code == sf::Keyboard::Space) {
                    scene.AddChild(new Torpedo("torpedo-" + NextID(), submarine.Position, submarine.Speed, submarine.Rotation + (submarine.Speed.x < 0 ? PI : 0)));
                }
            }
        }

        // UPDATE
        scene.Update(time_diff);

        // DRAW
        app.Clear(sf::Color(0, 0, 0));
        scene.Draw(app);
        app.Display();

    }

    std::cout << "Hello" << std::endl;
}
