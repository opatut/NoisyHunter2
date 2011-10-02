#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Core/Entity.hpp"
#include "Core/Input.hpp"
#include "Core/Random.hpp"
#include "Core/Resources.hpp"
#include "Core/Settings.hpp"
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
#include "States/LoadingState.hpp"
#include "States/MenuState.hpp"

void load() {
    Resources::GetInstance().LoadQueue();
    Resources::GetInstance().SetDefaultFont("fonts/nouveau_ibm.ttf");

}

QString console_text;
Text* console_output;

void WriteConsole(QString line) {
    console_text += line + "\n";
    console_output->SetCaption(console_text);
}

void do_console_command(void* sender, QString cmd) {
    std::cout << "Console > " << cmd.toStdString() << std::endl;
    ((TextField*)sender)->SetCaption("");
    WriteConsole("> " + cmd);
}

int main() {
    Random::Initialize();

    Settings& s = Settings::GetInstance();
    s.Load(QFileInfo("settings.conf"));

    sf::VideoMode mode;
    if(s.GetBool("video.resolution.use_desktop", true)) {
        mode = sf::VideoMode::GetDesktopMode();
    } else {
        mode.Width = s.GetInt("video.resolution.width");
        mode.Height = s.GetInt("video.resolution.height");
        mode.BitsPerPixel = s.GetInt("video.resolution.depth");
    }
    bool fullscreen = s.GetBool("video.fullscreen", true);

    /* ======== Setup ======== */
    sf::RenderWindow app(mode, "NoisyHunter", fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
    if(!fullscreen)
        app.SetPosition(sf::VideoMode::GetDesktopMode().Width / 2 - app.GetWidth() / 2, sf::VideoMode::GetDesktopMode().Height / 2 - app.GetHeight() / 2);
    Input::GetInstance().SetDefaultWindow(app);
    app.SetFramerateLimit(60);

    sf::Sprite logo;
    sf::Texture logo_texture;
    logo_texture.LoadFromFile("../data/logo.png");
    logo.SetTexture(logo_texture);
    logo.SetOrigin(logo_texture.GetWidth() / 2, logo_texture.GetHeight() / 2);
    logo.SetPosition(app.GetWidth() / 2, app.GetHeight() / 2);

    Resources::GetInstance().ReadPath(QDir("../data"));
    // std::cout << "Queued a total of " << Resources::GetInstance().GetQueueSize() << " files." << std::endl;

    sf::Thread thread(&load);
    thread.Launch();

    /* ======== States ======== */
    StateManager::GetInstance().AddState(new LoadingState());

    /* ======== Debug Overlay ======== */
    Panel overlay("debug_overlay", sf::Color(0,0,0,0));
    overlay.Position = Vector2D(0,0);
    overlay.Size = Vector2D(app.GetWidth(), app.GetHeight());

    Text fps("fps", "?? FPS", Vector2D(app.GetWidth() - 5, app.GetHeight() - 25), 12, Text::TA_RIGHT | Text::TA_BOTTOM);
    overlay.AddChild(&fps);
    overlay.AddChild(new Text("info", "Noisy Hunter / Build " + QString(__DATE__), Vector2D(app.GetWidth() - 5, app.GetHeight() - 5), 12, Text::TA_RIGHT | Text::TA_BOTTOM));

    /* ======== CONSOLE ======== */
    Panel console("console", sf::Color(0, 0, 0, 200));
    console.Position = Vector2D(30, -2);
    console.Size = Vector2D(app.GetWidth() - 60, app.GetHeight() * 0.6);
    console.SetBorder(2.f, sf::Color(200, 200, 200));
    console.Hide();

    console_output = new Text("output", "Console", Vector2D(5, app.GetHeight() * 0.6 - 50), Text::TA_BOTTOM | Text::TA_LEFT);
    console_output->SetSize(12);
    console.AddChild(console_output);

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

        // fps.SetCaption(QString::number(round(avg_fps)) + " FPS");
        fps.SetCaption(QString::number(round(1.f / time_diff)) + " FPS");

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


            if(console.HandleEvent(e))
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
        if(sf::Keyboard::IsKeyPressed(sf::Keyboard::F3)) {
            overlay.Draw(app);
        }
        app.Display();

    }

}
