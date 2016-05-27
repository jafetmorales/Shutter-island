#ifndef MOVABLE_STATE_HPP
#define MOVABLE_STATE_HPP

#include <glm/glm.hpp>
#include <vector>
#include <cmath>
#include "BoidsManager.hpp"

class BoidsManager;

class MovableBoid;
typedef std::shared_ptr<MovableBoid> MovableBoidPtr;

class RootedBoid;
typedef std::shared_ptr<RootedBoid> RootedBoidPtr;

/**
 * @class MovableState
 * @brief Virtual class to describe a state of boid. Contain some methods
 *        to compute a force for a boid 
 */
class MovableState 
{
 public:
  /**
   * @brief     Returns the acceleration and reset the acceleration of the boid
   * @param[in] b   The boid which has its acceleration reset and computed.
   *                It is this thing which knows what it should do
   * @param[in] mvB Vector of boids which b should be awared of
   * @param[in] dt  Time step useful to compute some forces
   * @return    The new acceleration of the boid
   */
  glm::vec3 computeAcceleration(MovableBoid& b,
              const BoidsManager & boidsManager, const float & dt) const;

 private:
  /**
   * @brief     Pure virtual function to compute the force of the boid
   *            @see computeAcceleration
   * @param[in] b   The boid which knows what do to
   * @param[in] mvB Vector of boids which b should be awared of
   * @param[in] dt  Time step useful to compute some forces
   * @return    The acceleration (decision) of the boid
   */
  virtual glm::vec3 computeNewForces(MovableBoid& b,
          const BoidsManager & boidsManager, const float & dt) const = 0;

 protected:
  /**
   * @brief     Computes the force for a boid b to go to the target
   * @param[in] b       The concerned boid
   * @param[in] target  Position aimed by the boid
   * @return    Returns the force required for b to go to target
   */
  glm::vec3 seek(const MovableBoid& b, const glm::vec3 & target) const;
  
  /**
   * @brief     Computes the force for a boid b to flee the repulsion point
   * @param[in] b              The concerned boid
   * @param[in] repulsionPoint Point the boid want to flee from
   * @return    Returns the force required for b to flee the repulsion point
   */
  glm::vec3 flee(const MovableBoid& b, const glm::vec3 & repulsionPoint) const;
  
  /**
   * @brief     Computes the force for a boid b to wander (random movement)
   * @param[in] b The concerned boid
   * @return    Returns the force required for b to wander
   */
  glm::vec3 wander(const MovableBoid& b) const;
  
  /**
   * @brief     Computes the force for a boid b to arrive gently at the target
   * @param[in] b       The concerned boid
   * @param[in] target  Position aimed by the boid
   * @return    Returns the force required for the b to go to target
   */
  glm::vec3 arrive(const MovableBoid& b, const glm::vec3 & target) const;
  
  /**
   * @brief     Computes the force for a boid b to stay within a border
   * @param[in] b The concerned boid
   * @return    Returns the force required for the b stay within the border
   */
  ///< @todo : Upgrade this function
  glm::vec3 stayWithinWalls(const MovableBoid& b) const;
  
  /**
   * @brief     Computes the force for a boid b separate from others boids
   * @param[in] b   The concerned boid
   * @param[in] mvB Vector of boids which b should be awared of
   * @return    Returns the force required for the b to separate
   */
  glm::vec3 separate(const MovableBoid& b, const std::vector<MovableBoidPtr> & bVec) const;

  /**
   * @todo
   */
  glm::vec3 collisionAvoid (const MovableBoid& b, const std::vector<RootedBoidPtr> & rootB) const;
  
  /**
   * @brief     Computes the force for a boid b to align with other boids
   * @param[in] b   The concerned boid
   * @param[in] mvB Vector of boids which b align with
   * @return    Returns the force required for the b to align
   */
  glm::vec3 align (const MovableBoid& b, const std::vector<MovableBoidPtr> & mvB) const;
  
  /**
   * @brief     Computes the force for a boid b to be in cohesion with other boids
   * @param[in] b   The concerned boid
   * @param[in] mvB Vector of boids which b have cohesion with
   * @return    Returns the force required for the b to be in cohesion with the others
   */
  glm::vec3 cohesion (const MovableBoid& b, const std::vector<MovableBoidPtr> & mvB) const;
  
  /**
   * @brief     Computes the force for a hunter to pursuit a target. The hunter
   *            forecast the position of the target.
   * @param[in] hunter The hunter
   * @param[in] target The target. It is a boid to forecast its position
   * @param[in] dt     Time step
   * @return    Returns the force required for the hunter to hunt the target
   */
  glm::vec3 pursuit (const MovableBoid & hunter, const MovableBoid & target, const float & dt) const;
  
  /**
   * @brief     Computes the force for a prey to flee from the hunter
   * @param[in] prey   The prey concerned by the force to compute
   * @param[in] hunter The hunter. The prey forecast the position of the hunter
   * @param[in] dt     Time step
   * @return    Returns the force required for the prey to evade the hunter
   */
  glm::vec3 evade(const MovableBoid & prey, const MovableBoid & hunter, const float & dt) const;

  /**
   * @brief     Computes the force for a boid b to follow its leader
   * @param[in] b The concerned boid
   * @param[in] mvB Vector of boids which b have should be aware
   * @return    Returns the force required for the boid to follow its leader
   */
  glm::vec3 followLeader(const MovableBoid & b, const std::vector<MovableBoidPtr> & mvB, const float & dt) const;

  /**
   * @brief Forecast of the position of a boid
   * @param[in] b The boid to forecast the position
   * @param[in] dt Step of time
   * @param[in] cst Constante for the movement
   */
  glm::vec3 positionForecast(const MovableBoid & b, const float & dt, const float & cst) const;

  glm::vec3 normalWalk(const MovableBoid & b, const BoidsManager & boidsManager) const;

  glm::vec3 globalAvoid(const MovableBoid & b, const BoidsManager & boidsManager) const;

  void detectDanger(const MovableBoid& b, const std::vector<MovableBoidPtr> & mvB) const;

  bool alone(const MovableBoid& b, const std::vector<MovableBoidPtr> & mvB) const;

};

/**
 * @class TestState
 * @brief State for bebugging
 */
class TestState : public MovableState 
{
 private:
  glm::vec3 computeNewForces(MovableBoid& b, const BoidsManager & boidsManager, const float & dt) const;
};

/**
 * @class WalkState
 * @brief State of a boid walking
 */
class WalkState : public MovableState 
{
 private:
  glm::vec3 computeNewForces(MovableBoid& b, const BoidsManager & boidsManager, const float & dt) const;
};

/**
 * @class StayState
 * @brief State of a boid staying at a position
 */
class StayState : public MovableState 
{
 private:
  glm::vec3 computeNewForces(MovableBoid& b, const BoidsManager & boidsManager, const float & dt) const;
};

/**
 * @class SleepState
 * @brief State of a boid sleeping
 */
class SleepState : public MovableState 
{
 private:
  glm::vec3 computeNewForces(MovableBoid& b, const BoidsManager & boidsManager, const float & dt) const;
};

/**
 * @class FleeState
 * @brief State of a boid fleeing
 */
class FleeState : public MovableState 
{
 private:
  glm::vec3 computeNewForces(MovableBoid& b, const BoidsManager & boidsManager, const float & dt) const;
};

/**
 * @class FindFoodState
 * @brief State of a boid finding food
 */
class FindFoodState : public MovableState 
{
 private:
  glm::vec3 computeNewForces(MovableBoid& b, const BoidsManager & boidsManager, const float & dt) const;
};

/**
 * @class EatState
 * @brief State of a boid eating
 */
class EatState : public MovableState 
{
 private:
  glm::vec3 computeNewForces(MovableBoid& b, const BoidsManager & boidsManager, const float & dt) const;
};

/**
 * @class FindWaterState
 * @brief State of a boid looking for water
 */
class FindWaterState : public MovableState 
{
 private:
  glm::vec3 computeNewForces(MovableBoid& b, const BoidsManager & boidsManager, const float & dt) const;
};

/**
 * @class DrinkState
 * @brief State of a boid drinking
 */
class DrinkState : public MovableState 
{
 private:
  glm::vec3 computeNewForces(MovableBoid& b, const BoidsManager & boidsManager, const float & dt) const;
};

/**
 * @class MateState
 * @brief State of a boid mating
 */
class MateState : public MovableState 
{
 private:
  glm::vec3 computeNewForces(MovableBoid& b, const BoidsManager & boidsManager, const float & dt) const;
};

/**
 * @class AttackState
 * @brief State of a boid attacking
 */
class AttackState : public MovableState
{
 private:
  glm::vec3 computeNewForces(MovableBoid& b, const BoidsManager & boidsManager, const float & dt) const;
};

/**
 * @class LostState
 * @brief State of a lost boid
 */
class LostState : public MovableState
{
 private:
  glm::vec3 computeNewForces(MovableBoid& b, const BoidsManager & boidsManager, const float & dt) const;
};

/**
 * @class DeadState
 * @brief State of a dead boid
 */
class DeadState : public MovableState
{
 private:
  glm::vec3 computeNewForces(MovableBoid& b, const BoidsManager & boidsManager, const float & dt) const;
};


// Return the closest animal of b of the good type in the vector.
// Need to be seen too.
MovableBoidPtr closestAnimal(const MovableBoid & b, const BoidType & type, const std::vector<MovableBoidPtr> & mvB);

#endif