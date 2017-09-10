#ifndef DRAW_HPP
#define DRAW_HPP

#include "config.hpp"
#include "engine.hpp"
#include "mesh.hpp"
#include "shader.hpp"
#include <vector>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
using glm::vec2;

class Draw {
public:
    Engine *engine;
    ShaderProgram shader;
    Mesh2D circleMesh, boxMesh, polylineMesh;
    int maxVerts;
    Draw() {}
    Draw(Engine *engine);
    void mesh(mat4 transform, Mesh2D &mesh, vec3 color, int nElements=-1);
    void circle(float angle, vec2 center, float radius, vec3 color);
    void box(float angle, vec2 center, vec2 size, vec3 color);
    void polyline(mat4 transform, std::vector<vec2> vertices, vec3 color);
};

inline Draw::Draw(Engine *engine) {
    this->engine = engine;
    shader = ShaderProgram(Config::shaderVert, Config::shaderFrag);
    circleMesh.makeCircle(vec2(0,0), 1);
    circleMesh.createGPUData(engine);
    boxMesh.makeBox(vec2(-0.5,-0.5), vec2(0.5,0.5));
    boxMesh.createGPUData(engine);
    maxVerts = 100;
    polylineMesh.vertices.resize(maxVerts);
    for (int i = 0; i < maxVerts-1; i++)
        polylineMesh.edges.push_back(ivec2(i,i+1));
    polylineMesh.createGPUData(engine);
}

inline void Draw::mesh(mat4 transform, Mesh2D &mesh, vec3 color, int nElements) {
    shader.enable();
    shader.setUniform("modelViewMatrix", engine->getMatrix(GL_MODELVIEW)*transform);
    shader.setUniform("projectionMatrix", engine->getMatrix(GL_PROJECTION));
    shader.setUniform("color", color);
    shader.setAttribute("vertex", mesh.vertexBuffer, 2, GL_FLOAT);
    if (nElements < 0)
        nElements = mesh.edges.size();
    engine->drawElements(GL_LINES, mesh.indexBuffer, nElements*2);
    shader.disable();
}

inline void Draw::circle(float angle, vec2 center, float radius, vec3 color) {
    mat4 trans = glm::translate(vec3(center, 0));
    mat4 scale = glm::scale(vec3(radius, radius, 0));
    mat4 rot = glm::rotate(angle, vec3(0,0,1));
    mesh(trans*rot*scale, circleMesh, color);
}

inline void Draw::box(float angle, vec2 center, vec2 size, vec3 color) {
    mat4 trans = glm::translate(vec3(center, 0));
    mat4 scale = glm::scale(vec3(size, 0));
    mat4 rot = glm::rotate(angle, vec3(0,0,1));
    /*
    transform = glm::translate(transform, vec3(center, 0));
    transform = glm::scale(transform, vec3(size,0));
    mesh(transform, boxMesh, color);
    */
    mesh(trans*rot*scale, boxMesh, color);
}

inline void Draw::polyline(mat4 transform, std::vector<vec2> vertices, vec3 color) {
    for (int i = 0; i < vertices.size(); i += maxVerts-1) {
        int start = i, end = i + maxVerts;
        if (end > vertices.size())
            end = vertices.size();
        engine->copyVertexData(polylineMesh.vertexBuffer,
                               &vertices[start], (end-start)*sizeof(vec2));
        mesh(transform, polylineMesh, color, end-start-1);
    }
}

#endif
