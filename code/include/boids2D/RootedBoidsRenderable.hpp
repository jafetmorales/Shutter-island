#ifndef ROOTED_BOIDS_RENDERABLE_HPP
#define ROOTED_BOIDS_RENDERABLE_HPP

#include <glm/glm.hpp>
#include "../HierarchicalRenderable.hpp"
#include "./../lighting/Material.hpp"
#include <vector>
#include "BoidsManager.hpp"

/**
 * @class RootedBoidsRenderable
 * @brief Renderable for all the rabbit in the RabbitsManager. @see Renderable
 */
class RootedBoidsRenderable : public HierarchicalRenderable
{
    public:
        RootedBoidsRenderable(ShaderProgramPtr shaderProgram, BoidsManagerPtr boidsManager, BoidType boidType,
            const std::string& mesh, const std::string & texture);

        ~RootedBoidsRenderable();
        
        void setMaterial(const MaterialPtr& material);

    private:
        void do_draw();
        void do_animate( float time );
        void compute_modelMatrix();

        std::vector< glm::vec2 > m_texCoords;
        std::vector< glm::vec3 > m_vectorBuffer;
        std::vector< glm::mat4 > m_modelMatrix;
        int m_nbElement;

        unsigned int m_instanceVBO;
        std::vector< unsigned int > m_VAOs;
        unsigned int m_VBO;
        unsigned int m_tBuffer;
        unsigned int m_texId;

        MaterialPtr m_material;
        BoidType m_boidType;
        BoidsManagerPtr m_boidsManager;     
};

typedef std::shared_ptr<RootedBoidsRenderable> RootedBoidsRenderablePtr;

#endif