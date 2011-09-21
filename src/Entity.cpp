#include "Entity.hpp"
#include <iostream>

Entity::Entity(QString name) {
    mName = name;
    Position = Vector2D(0, 0);
    Size = Vector2D(1, 1);
    Rotation = 0.f;
    mParent = nullptr;
}

QString Entity::GetName() {
    return mName;
}

Vector2D Entity::GetAbsolutePosition() {
    if(mParent != nullptr)
        return mParent->GetAbsolutePosition() + Position;
    return Position;
}

Vector2D Entity::GetAbsoluteSpeed() {
    if(mParent != nullptr)
        return mParent->GetAbsoluteSpeed() + Speed;
    return Speed;
}

Vector2D Entity::GetAbsoluteSize() {
    if(mParent != nullptr)
        return Vector2D(mParent->GetAbsoluteSize().x * Size.x, mParent->GetAbsoluteSize().y * Size.y);
    return Size;
}

float Entity::GetAbsoluteRotation() {
    if(mParent != nullptr)
        return mParent->GetAbsoluteRotation() + Rotation;
    return Rotation;
}

void Entity::Move(Vector2D vector) {
    Position += vector;
}

void Entity::Accelerate(Vector2D direction) {
    Speed += direction;
}

void Entity::Scale(float factor) {
    Size *= factor;
}

void Entity::Rotate(float angle) {
    Rotation += angle;
}

void Entity::Update(float time_diff) {
    mLifetime += time_diff;
    Vector2D s = Speed;
    s.Rotate(Rotation);
    Position += s * time_diff;
    OnUpdate(time_diff);

    // update children
    for(auto iter = mChildren.begin(); iter != mChildren.end(); ++iter) {
        iter->second->Update(time_diff);
    }
}

void Entity::OnUpdate(float time_diff) {}

void Entity::Draw(sf::RenderTarget& target) {
    OnDraw(target);

    // draw children
    for(auto iter = mChildren.begin(); iter != mChildren.end(); ++iter) {
        iter->second->Draw(target);
    }
}

void Entity::OnDraw(sf::RenderTarget& target) {}

void Entity::SetParent(Entity* parent) {
    if(parent == nullptr) {
        if(mParent != nullptr)
            mParent->RemoveChild(this);
        mParent = nullptr;
    } else if(mParent != parent) {
        if(mParent != nullptr)
            mParent->RemoveChild(this);
        mParent = parent;
        mParent->AddChild(this);
    }
}

Entity* Entity::GetParent() {
    return mParent;
}

void Entity::AddChild(Entity* child) {
    if(mChildren.count(child->GetName()) == 0) {
        // not yet in list
        mChildren.insert(std::pair<QString, Entity*>(child->GetName(), child));
        child->SetParent(this);
    }
}

void Entity::RemoveChild(Entity* child) {
    if(mChildren.count(child->GetName()) != 0) {
        // mChildren[child->GetName()] = nullptr;
        mChildren.erase(child->GetName());
    }
}
