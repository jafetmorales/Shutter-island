/**
 * @file HeightTree.hpp
 *
 * @brief Defining the 'HeightMap' of the world
 */

#ifndef HEIGHTTREE_HPP
#define HEIGHTTREE_HPP

#include "HeightNode.hpp"
#include "../structures/QuadTree.hpp"

/**
 * @brief
 * Determining if a point is already in the tree before inserting it,
 * we have to compare the position of the point to insert with the positions
 * of all the already inserted points.
 * However, when comparing floats, such as the coordinates of the points, the
 * computation error has to be taken into account (so as to avoid false
 * negative).
 * This threshold aims precisely at that : if the distance between two points
 * is lesser than the former, the two points are considered equal.
 */
#define DETECTION_THRESHOLD (0.1f)

/**
 * @brief
 * When determining the height associated with a point, we iterate recursively
 * from the root of the tree to the corresponding node of the deepest level
 * of subdivision.
 * Each level contributes to the global height, but their contribution is
 * recursively reduced by applying the defined blending coefficient.
 */
#define HEIGHT_BLENDING_COEFFICIENT (0.7f)

/**
 * @brief
 * The HeightTree class implements the QuadTree template so as to compute
 * the HeightMap associated with the Map.
 */
class HeightTree : public QuadTree<HeightNode, HeightTree> {

public :

    /**
     * @brief Constructor
     * 
     * @param content
     * @param tlChild
     * @param trChild
     * @param blChild
     * @param brChild
     */
    HeightTree(HeightNode content,
	       HeightTree *tlChild = NULL, HeightTree *trChild = NULL,
	       HeightTree *blChild = NULL, HeightTree *brChild = NULL);
     
    
    /**
     * @brief Create the height tree, taking this as the root 
     * of the tree (ie depth = 1, the content as the main square map)
     * 
     * @param container The container of the seeds
     */
    void computeTree(voro::container & container, std::vector<Seed> seeds);

    /**
     * @brief Free the whole tree. 
     * The root is undefined after the call of this method
     */
    void freeHeightTree();

    /**
     * @brief Compute the height of a point within the 
     * map defined by the tree
     *
     * @param pos The position of the point
     *
     * @return The height of the point
     */
    float evalHeight(Vertex2D pos);

private :

    /**
     * @brief Choose the correct child where the given point is
     * assuming that the point belongs to the node
     *
     * @param pos The point we want to know the subsquare it belongs in
     *
     * @return The right child
     */

    HeightTree* locatePosition(Vertex2D & pos);

    /**
     * @brief Search in the tree if a vertex has alreadeay been defined
     * if so, it returns its height
     * This function is here to ensure the continuity between squares of the map
     *
     * @param pos    The vertex we'd like to check
     * @parap depth  The depth of the vertex we'd like to check
     * @param height The height of the vertex if found
     *
     * @return if the vertex has been found
     */
    bool findVertexHeight(Vertex2D & pos, int depth, float* height);

    /**
     * @brief The internal function to create the height tree
     *
     * @param container The container of the seeds
     * @param seeds     The sorted set of seeds
     * @param depth     The depth in the tree
     * @param root      The root of the tree
     */
    void computeTreeInternal(voro::container & container, std::vector<Seed> seeds, 
			     int depth, HeightTree* root);


};



#endif
