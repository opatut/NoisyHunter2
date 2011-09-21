#ifndef _ENTITY
#define _ENTITY

#include "Vector2D.hpp"
#include <QString>
#include <map>

class Entity {
public:
    Entity(QString name);
    QString GetName();

    Vector2D Position;
    Vector2D Speed;
    Vector2D Size;
    float Rotation;

    Vector2D GetAbsolutePosition();
    Vector2D GetAbsoluteSpeed();
    Vector2D GetAbsoluteSize();
    float GetAbsoluteRotation();


    void Move(Vector2D vector);
    void Accelerate(Vector2D direction);
    void Scale(float factor);
    void Rotate(float angle);

    void Update(float time_diff);
    virtual void OnUpdate(float time_diff);

    void Draw(sf::RenderTarget& target);
    virtual void OnDraw(sf::RenderTarget& target);

    void SetParent(Entity* parent);
    Entity* GetParent();
    void AddChild(Entity* child);
    void RemoveChild(Entity* child);

protected:
    float mLifetime;

private:
    QString mName;

    Entity* mParent;
    std::map<QString, Entity*> mChildren;
};

#endif
