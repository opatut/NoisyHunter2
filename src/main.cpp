#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Core/Entity.hpp"
#include "Core/Input.hpp"
#include "Core/Resources.hpp"
#include "Core/StateManager.hpp"
#include "Entities/Level.hpp"
#include "Entities/Narwhal.hpp"
#include "Entities/Submarine.hpp"
#include "Entities/Torpedo.hpp"
#include "Gui/Button.hpp"
#include "Gui/Widget.hpp"
#include "Hud/BackgroundGradient.hpp"
#include "Hud/Text.hpp"
#include "States/GameState.hpp"
#include "States/MenuState.hpp"

int main() {
    /* ======== Setup ======== */
    sf::RenderWindow app(sf::VideoMode(800, 600, 32), "NoisyHunter");
    app.SetPosition(sf::VideoMode::GetDesktopMode().Width / 2 - 400, sf::VideoMode::GetDesktopMode().Height / 2 - 300);
    app.SetFramerateLimit(60);
    Input::GetInstance().SetDefaultWindow(app);
    Resources::GetInstance().LoadPath(QDir("../data"));

    /* ======== States ======== */
    StateManager mgr;
    mgr.AddState(new MenuState());

    /* ======== Debug Overlay ======== */
    Entity overlay("debug_overlay");

    Text fps("fps", "?? FPS");
    fps.Position.x = 795;
    fps.Position.y = 580;
    fps.SetAlign(Text::TA_RIGHT | Text::TA_BOTTOM);
    fps.SetSize(8);
    overlay.AddChild(&fps);

    Text text("text", "Noisy Hunter - Build 3");
    text.Position.x = 795;
    text.Position.y = 595;
    text.SetAlign(Text::TA_RIGHT | Text::TA_BOTTOM);
    text.SetSize(8);
    overlay.AddChild(&text);

    /* ======== GUI ======== */
    Entity gui("gui");
    Button* b;

    b = new Button("button1", "Hello World Button");
    b->Position.x = 300;
    b->Position.y = 300;
    b->Size.x = 200;
    b->Size.y = 40;
    gui.AddChild(b);

    /* ======== Timing ======== */
    sf::Clock clock;
    float time = 0;
    float avg_fps = 60;

    /* ======== Main Loop ======== */
    while(app.IsOpened()) {
        mgr.PushStates();

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
                if(e.Key.Code == sf::Keyboard::F12) {
                    app.Capture().SaveToFile("screenshot.png");
                } else if(e.Key.Code == sf::Keyboard::Space) {
                    mgr.AddState(new GameState(), 0);
                } else if(e.Key.Code == sf::Keyboard::Q) {
                    if(e.Key.Control) {
                        // Ctrl + Q
                        app.Close();
                    }
                }
            }
            mgr.HandleEvent(e);
        }

        // UPDATE
        mgr.Update(time_diff);
        overlay.Update(time_diff);
        gui.Update(time_diff);

        // DRAW
        app.Clear(sf::Color(0, 0, 0));
        mgr.Draw(app);
        overlay.Draw(app);
        gui.Draw(app);
        app.Display();

    }

}
