/**
 * @file MapUtils.cpp
 *
 * @see MapUtils.hpp
 */

#include <cmath>

#include "../../include/terrain/MapUtils.hpp"


Biome findClosestBiome(
    Vertex2D & pos, 
	voro::container & container, 
    std::vector<Seed> & seeds
){
    double rx, ry, rz;
    int seedID;
    if (
            !(
                container.find_voronoi_cell(
                    pos.first, 
                    pos.second, 
                    0.0,
                    rx, 
                    ry, 
                    rz, 
                    seedID
                )
            )
    ) {
        exit(EXIT_FAILURE);
    }

    return seeds[seedID].getBiome();
}


float distanceV2D(Vertex2D & a, Vertex2D & b) {
    
    float aX = a.first;
    float aY = a.second;
    float bX = b.first;
    float bY = b.second;

    float u = bX - aX;
    float v = bY - aY;

    return sqrt(u*u + v*v);
}