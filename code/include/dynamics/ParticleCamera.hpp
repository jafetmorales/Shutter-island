#ifndef PARTICLE_CAMERA_HPP
#define PARTICLE_CAMERA_HPP

#include "./../../include/HierarchicalRenderable.hpp"
#include "./../../include/dynamics/ConstantForceField.hpp"
#include "./../../include/Viewer.hpp"
#include "./../../include/terrain/MapGenerator.hpp"

/**@brief Status of a ControlledForceField.
 *
 * This status holds important variables that are used to control a force
 * field thanks to user inputs. You can (and should) adapt this class
 * and its default value to the kind of behavior you want in your project.
 */
class ParticleForceFieldStatus
{
public:
    ParticleForceFieldStatus();
    ParticleForceFieldStatus(const glm::vec3& initial_direction);
    ~ParticleForceFieldStatus();
    void clear();

public:
    glm::vec3 initial;
    glm::vec3 movement;
    float angle;
    float last_time;
    float intensity;
    float min_intensity;
    float max_intensity;
    float acceleration;
    float deacceleration;
    float angularSpeed;
    float dampingFactor;

    bool accelerating;
    bool deaccelerating;
    bool turning_left;
    bool turning_right;
};


/**@brief Implement a force field controlled by user input.
 *
 * This class is an example of what you could do to control a dynamic component
 * (e.g. the kart in your project) thanks to user inputs. This is done by modifying
 * the force of a constant force field applied to the mobile(s) you want to control.
 *
 * We derive from a renderable to be able to react to user input. This might look
 * nasty, but since you dealt with renderables during all previous praticales, we think
 * this is the easiest way to do so. We derive from a hierarchical renderable to be able
 * to use the same local frame as the dynamic system using the force field (see DynamicSystemRenderable).
 */
class ParticleCamera : public HierarchicalRenderable
{
public:
  /**@brief Build a new controlled force field renderable.
   *
   * Build a new controlled force field by user inputs.
   * @param program The shader program used to render the force applied to particles.
   * @param forceField The force field to control with user inputs.
   */
  ParticleCamera(ShaderProgramPtr program, ConstantForceFieldPtr forceField,  MapGenerator & map, Viewer & viewer);
  ~ParticleCamera();

private:

  virtual void do_keyPressedEvent( sf::Event& e );
  virtual void do_keyReleasedEvent( sf::Event& e );
  virtual void do_animate( float time );
  virtual void do_draw();

  ParticleForceFieldStatus m_status;
  ConstantForceFieldPtr m_force;
  MapGenerator & m_map;
  Viewer & m_viewer;
};

typedef std::shared_ptr<ParticleCamera> ParticleCameraPtr;

#endif //CONTROLLED_FORCE_FIELD_RENDERABLE_HPP
