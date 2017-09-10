#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>
#include <Box2D/Box2D.h>
using namespace std;
using glm::vec2;

// TODO: Modify these classes to keep track of the corresponding Box2D
// bodies. Feel free to add helpful methods like
//     mat4 getTransformation()
// and
//     vec2 getLocalPoint(vec2 worldPoint).

class Circle {
    public:
        b2Body * body;
        vec2 center;
        float radius;
        Circle() {}
        Circle(vec2 center, float radius, b2World* world, bool dynamic) {
            this->center = center;
            this->radius = radius;
            b2BodyDef bodyDef;
            if (dynamic)
                bodyDef.type = b2_dynamicBody;
            else
                bodyDef.type = b2_staticBody;
            bodyDef.position.Set(center.x, center.y);
            body = world->CreateBody(&bodyDef);
            b2CircleShape ballShape;
            ballShape.m_radius = radius;
            b2FixtureDef ballFD;
            ballFD.shape = &ballShape;
            ballFD.density = .2;
            ballFD.friction = .4;
            ballFD.restitution = .4;
            body->CreateFixture(&ballFD);
        }
        vec2 getBodyPos() {
            b2Vec2 pos = body->GetPosition();
            return vec2(pos.x, pos.y);
        }
        float getTransform() {
            float angle = body->GetAngle();
            return angle;
        }
        bool contains(vec2 worldPoint) {
            return glm::length(worldPoint - getBodyPos()) <= radius;
        }
        void destroy(b2World* world) {
            world->DestroyBody(body);
        }
};

class Box {
    public:
        b2Body * body;
        vec2 center;
        vec2 size;
        Box() {}
        Box(vec2 center, vec2 size, b2World * world, bool dynamic) {
            this->center = center;
            this->size = size;
            b2BodyDef bodyDef;
            if (dynamic)
                bodyDef.type = b2_dynamicBody;
            else
                bodyDef.type = b2_staticBody;
            bodyDef.position.Set(center.x, center.y);
            body = world->CreateBody(&bodyDef);
            b2PolygonShape squareShape;
            squareShape.SetAsBox(size.x / 2, size.y / 2);
            b2FixtureDef squareFD;
            squareFD.shape = &squareShape;
            squareFD.density = .2;
            squareFD.friction = .4;
            squareFD.restitution = .4;
            body->CreateFixture(&squareFD);
        }
        vec2 getBodyPos() {
            b2Vec2 pos = body->GetPosition();
            return vec2(pos.x, pos.y);
        }
        float getTransform() {
            float angle = body->GetAngle();
            return angle;
        }
        bool contains(vec2 worldPoint) {
            // b2Vec2 l = body->GetLocalPoint(worldPoint.x, worldPoint.y);
            b2Vec2 l = body->GetLocalPoint(b2Vec2(worldPoint.x, worldPoint.y));
            return (l.x <= size.x/2 && l.y <= size.y/2);
        }
        void destroy(b2World* world) {
            world->DestroyBody(body);
        }
};

class Polyline {
    public:
        vector<vec2> vertices;
        b2Body* body;
        Polyline() {}
        Polyline(vector<vec2> vertices, b2World* world) {
            vector<b2Vec2> bVerts;
            this->vertices = vertices;
            for (int i = 0; i < vertices.size(); i++) 
                bVerts.push_back(b2Vec2(vertices[i].x, vertices[i].y));
            b2ChainShape chain;
            chain.CreateChain(&bVerts[0], vertices.size());
            b2BodyDef bodyDef;
            bodyDef.type = b2_staticBody;
            body = world->CreateBody(&bodyDef);
            b2FixtureDef chainFD;
            chainFD.shape = &chain;
            chainFD.density = .2;
            chainFD.friction = .4;
            chainFD.restitution = .4;
            body->CreateFixture(&chainFD);
        }
        void destroy(b2World* world) {
            world->DestroyBody(body);
        }
};

#endif
