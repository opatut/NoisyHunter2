#include "Entity.hpp"
#include <iostream>

#include "Serializer.hpp"

Entity::Entity(QString name, Vector2D position, Vector2D size, Vector2D speed, float rotation) {
    mName = name;
    Position = position;
    Size = size;
    Speed = speed;
    Rotation = rotation;
    mParent = nullptr;
}

Entity::~Entity() {
    RemoveAllChildren();
}

QString Entity::GetName() const {
    return mName;
}

void Entity::Serialize(IOPacket& packet) {
    packet & mName;
    packet & Position;
    packet & Speed;
    packet & Size;
    packet & Rotation;

    // serialize all children
    if(packet.GetMode() == IOPacket::DESERIALIZE) {
        // Read children
        uint32_t children_count;
        packet & children_count;

        for(unsigned int i = 0; i < children_count; ++i) {
            Serializable* s = Serializer::Load(packet.GetPacket());
            AddChild((Entity*)s);
        }
    } else {
        // count the children that are being serialized
        uint32_t children_count = 0;
        for(auto iter = mChildren.begin(); iter != mChildren.end(); ++iter) {
            if(iter->second->GetTypeId() != ET_UNKNOWN)
                ++children_count;
        }
        packet & children_count;
        // Write children
        for(auto iter = mChildren.begin(); iter != mChildren.end(); ++iter) {
            Serializer::Write(packet.GetPacket(), iter->second);
        }
    }
}

uint32_t Entity::GetTypeId() const {
    return ET_ENTITY;
}

Serializable* Entity::CreateInstance() const {
    return nullptr;
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

void Entity::RemoveAllChildren() {
    while(mChildren.size() > 0) {
        RemoveChild(mChildren.begin()->second);
    }
}
