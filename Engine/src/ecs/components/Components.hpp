#pragma once

#include "../../common/Utils.hpp"
#include <SDL.h>

struct Transform
{
    // Transformation in a 2D plane
    Vector2 position; float rotation; size_t scale;

    Transform(const Vector2& position = { 0, 0 }, float rotation = 0.0, size_t scale = 1)
        : position(position), rotation(rotation), scale(scale) {}
};

struct Sprite
{
    SDL_Texture* texture;

    // Source and destination rect
    SDL_Rect src;
    SDL_Rect dst;

    size_t frame;

    size_t hframes; // Total frames in one row
    size_t vframes; // Total frames in one column

    size_t speed; // Speed in frames per second

    int8_t z_index; // Sprite layer

    // Map of animations
    std::unordered_map<std::string, std::vector<size_t>> animations{};
    const char* animation = "none";

    bool fliph = false;
    bool flipv = false;

    Sprite(SDL_Texture* texture = nullptr, size_t hframes = 1, size_t vframes = 1, size_t speed = 0, int8_t z_index = 0)
        : texture(texture), src({ 0, 0, 0, 0 }), dst({ 0, 0, 0, 0 }),
        frame(0), hframes(hframes), vframes(vframes), speed(speed), z_index(z_index)
    {
        animations.insert({ "none", {} });
    }

    void addAnim(const char* anim, const std::vector<size_t>& frames) 
    {
        if (animations.find(anim) != animations.end()) 
        {
            printf("[INFO]: Animation '%s' already added, overriding\n", anim);

            // Override animation
            animations[anim] = frames;
            return;
        }
        if (frames.empty()) 
        {
            fprintf(stderr, "[ERROR]: Animation '%s' cannot have empty frame list\n", anim);
            return;
        }

        // Add animation
        animations[anim] = frames;
    }

    void setAnim(const char* anim) 
    {
        if (animations.find(anim) == animations.end())
        {
            fprintf(stderr, "[ERROR]: Animation '%s' does not exist\n", anim);
            return;
        }

        // Set animation
        animation = anim;
    }
       
    void delAnim(const char* anim)
    {
        if (animations.find(anim) == animations.end()) 
        {
            fprintf(stderr, "[ERROR]: Animation '%s' does not exist\n", anim);
            return;
        }

        // Remove animation
        animations.erase(anim);
    }
};

struct Movement
{
    Vector2 direction;
    Vector2 speed;

    Movement(const Vector2& direction = { 0, 0 }, const Vector2& speed = { 0, 0 }) : direction(direction), speed(speed) {}
};

struct AABB 
{
    // Center
    Vector2 center;

    // Size
    Vector2 dimensions;

    // Boundaries
    Vector2 min;
    Vector2 max;

    bool isSolid;
    bool isRigid;

    AABB(float cx, float cy, float w, float h, 
        bool isSolid=true, bool isRigid=true)
        : center({ cx, cy }), dimensions({ w, h }), isSolid(isSolid), isRigid(isRigid)
    {
        min = { -w / 2, -h / 2 };
        max = {  w / 2,  h / 2 };
    }

    AABB(const Vector2& center = { 0, 0 }, const Vector2& dimensions = { 0, 0 },
        bool isSolid=true, bool isRigid=true)
        : center(center), dimensions(dimensions), isSolid(isSolid), isRigid(isRigid)
    {
        min = { -dimensions.x / 2, -dimensions.y / 2 };
        max = {  dimensions.x / 2,  dimensions.y / 2 };
    }

    // Check for AABB overlap
    bool intersects(AABB& other) 
    {
        // Set isColliding to true if there is overlap on both the X and Y axes
        isColliding = !(max.x < other.min.x || min.x > other.max.x || max.y < other.min.y || min.y > other.max.y);
        other.isColliding = isColliding;

        return isColliding;
    }

    bool colliding() 
    {
        return isColliding;
    }

private:
    bool isColliding = false;
};

// Work in progress
struct CircleCollider 
{
    // Center and dimensions
    Vector2 center;
    float r;

    AABB aabb;

    CircleCollider(float cx, float cy, float r) : center(Vector2(cx, cy)), r(r) {}
    CircleCollider(const Vector2& center, float r) : center(center), r(r) {}
};

struct BoxCollider 
{
    // Center and dimensions
    Vector2 center;
    float w;
    float h;

    AABB aabb;

    // Box vertices
    std::array<Vector2, 4> vertices{ Vector2::ZERO };
    std::array<Vector2, 4> transformedVertices{ Vector2::ZERO };

    BoxCollider(float cx, float cy, float w, float h) : center(Vector2(cx, cy)), w(w), h(h) {};
    BoxCollider(const Vector2& center, float w, float h) : center(center), w(w), h(h) {};
};

