#ifndef _ENTITY
#define _ENTITY

#include "Core/Serializable.hpp"
#include "Core/Vector2D.hpp"
#include "Globals.hpp"
#include <QString>
#include <map>
#include <SFML/Graphics.hpp>

class Entity : public Serializable {
public:
    Entity(QString name, Vector2D position = Vector2D(), Vector2D size = Vector2D(1,1), Vector2D speed = Vector2D(), float rotation = 0.f);
    ~Entity();
    QString GetName() const;

    virtual void Serialize(IOPacket& packet);
    virtual uint32_t GetTypeId() const;
    virtual Serializable* CreateInstance() const;

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
    void RemoveAllChildren();

protected:
    float mLifetime;
    std::map<QString, Entity*> mChildren;

private:
    QString mName;
    Entity* mParent;
};

#endif
