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
#include "Gui/FocusManager.hpp"
#include "Gui/Panel.hpp"
#include "Gui/TextField.hpp"
#include "Gui/Widget.hpp"
#include "Hud/BackgroundGradient.hpp"
#include "Hud/Text.hpp"
#include "States/EditorState.hpp"
#include "States/GameState.hpp"
#include "States/MenuState.hpp"

void do_console_command(void* sender, QString cmd) {
    std::cout << "Console > " << cmd.toStdString() << std::endl;
    ((TextField*)sender)->SetCaption("");
}

int main() {
    /* ======== Setup ======== */
    sf::RenderWindow app(sf::VideoMode::GetDesktopMode(), "NoisyHunter", sf::Style::Fullscreen);
    // sf::RenderWindow app(sf::VideoMode(1024, 768, 32), "NoisyHunter");
    // app.SetPosition(sf::VideoMode::GetDesktopMode().Width / 2 - app.GetWidth() / 2, sf::VideoMode::GetDesktopMode().Height / 2 - app.GetHeight() / 2);
    app.SetFramerateLimit(60);

    app.Clear();
    sf::Text loading("Loading ...");
    loading.SetCharacterSize(12);
    loading.SetPosition(round(app.GetWidth() / 2 - loading.GetRect().Width / 2), round(app.GetHeight() / 2- loading.GetRect().Height / 2));
    app.Draw(loading);
    app.Display();

    Input::GetInstance().SetDefaultWindow(app);
    Resources::GetInstance().LoadPath(QDir("../data"));
    Resources::GetInstance().SetDefaultFont("fonts/nouveau_ibm.ttf");

    /* ======== States ======== */
    StateManager::GetInstance().AddState(new MenuState());

    /* ======== Debug Overlay ======== */
    Entity overlay("debug_overlay");
    Text fps("fps", "?? FPS", Vector2D(app.GetWidth() - 5, app.GetHeight() - 25), 12, Text::TA_RIGHT | Text::TA_BOTTOM);
    overlay.AddChild(&fps);
    overlay.AddChild(new Text("info", "Noisy Hunter / Build " + QString(__DATE__), Vector2D(app.GetWidth() - 5, app.GetHeight() - 5), 12, Text::TA_RIGHT | Text::TA_BOTTOM));

    /* ======== CONSOLE ======== */
    Panel console("console", sf::Color(0, 0, 0, 200));
    console.Position = Vector2D(30, -2);
    console.Size = Vector2D(app.GetWidth() - 60, app.GetHeight() * 0.6);
    console.SetBorder(2.f, sf::Color(200, 200, 200));
    console.Hide();

    TextField* ci = new TextField("console-input");
    ci->Position = Vector2D(5, app.GetHeight() * 0.6 - 30);
    ci->Size = Vector2D(app.GetWidth() - 70, 25);
    ci->EventSubmitField = new Callback<QString>(&do_console_command);
    console.AddChild(ci);

    /* ======== Timing ======== */
    sf::Clock clock;
    float time = 0;
    float avg_fps = 60;

    /* ======== Main Loop ======== */
    while(app.IsOpened()) {
        StateManager::GetInstance().PushStates();
        if(StateManager::GetInstance().GetCurrentState() == nullptr) {
            app.Close();
            break;
        }

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
                } else if(e.Key.Code == sf::Keyboard::Q) {
                    if(e.Key.Control) {
                        // Ctrl + Q
                        app.Close();
                    }
                } else if(e.Key.Code == sf::Keyboard::Tab) {
                    FocusManager::GetInstance().ShiftFocus( e.Key.Shift ? -1 : 1 );
                } else if(e.Key.Code == sf::Keyboard::Right) {
                    FocusManager::GetInstance().ShiftFocusRight();
                } else if(e.Key.Code == sf::Keyboard::Left) {
                    FocusManager::GetInstance().ShiftFocusLeft();
                } else if(e.Key.Code == sf::Keyboard::Up) {
                    FocusManager::GetInstance().ShiftFocusUp();
                } else if(e.Key.Code == sf::Keyboard::Down) {
                    FocusManager::GetInstance().ShiftFocusDown();
                } else if(e.Key.Code == sf::Keyboard::F1) {
                    if(console.IsVisible())
                        console.Hide();
                    else
                        console.Show();
                }
            }


            console.HandleEvent(e);

            StateManager::GetInstance().HandleEvent(e);
        }

        // UPDATE
        StateManager::GetInstance().Update(time_diff);
        console.Update(time_diff);
        overlay.Update(time_diff);

        // DRAW
        app.Clear(sf::Color(0, 0, 0));
        StateManager::GetInstance().Draw(app);
        console.Draw(app);
        overlay.Draw(app);
        app.Display();

    }

}
