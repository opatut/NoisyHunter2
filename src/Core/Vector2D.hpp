#ifndef _VECTOR2D
#define _VECTOR2D

#define PI 3.14159265358979323846
#include <cmath>

#include <SFML/Network/Packet.hpp>
#include <SFML/System/Vector2.hpp>

class Vector2D {
public:
    Vector2D(float x = 0, float y = 0);
    Vector2D(sf::Vector2f pos);
    ~Vector2D() {}

    void Rotate( const float angle );
    float Magnitude() const;
    float Rotation() const;
    float Normalize();
    float DotProduct( const Vector2D& v2 ) const;
    float CrossProduct( const Vector2D& v2 ) const;

    static Vector2D Zero();
    static float Distance( const Vector2D& v1, const Vector2D& v2);
    static float Angle( const Vector2D& v1, const Vector2D& v2);
    static float rad2Deg( const float rad );
    static float deg2Rad( const float deg );

    Vector2D& operator= ( const Vector2D& v2 );

    Vector2D& operator+= ( const Vector2D& v2 );
    Vector2D& operator-= ( const Vector2D& v2 );
    Vector2D& operator*= ( const float scalar);
    Vector2D& operator/= ( const float scalar);

    const Vector2D operator+( const Vector2D &v2 ) const;
    const Vector2D operator-( const Vector2D &v2 ) const;
    const Vector2D operator*( const float scalar ) const;
    const Vector2D operator/( const float scalar ) const;

    bool operator== ( const Vector2D& v2 ) const;
    bool operator!= ( const Vector2D& v2 ) const;

public:
    float x, y;
};

sf::Packet& operator << (sf::Packet& p, Vector2D& v);
sf::Packet& operator >> (sf::Packet& p, Vector2D& v);

#endif

