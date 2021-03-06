/**
 * @file HeightTree.cpp
 * 
 * @see HeightTree.hpp
 */
#include "../../include/terrain/MapUtils.hpp"
#include "../../include/terrain/HeightTree.hpp"

HeightTree::HeightTree(MapParameters& parameters, HeightNode content,
		       HeightTree *tlChild, HeightTree *trChild,
		       HeightTree *blChild, HeightTree *brChild) :
    QuadTree<HeightNode, HeightTree>(content,
				     tlChild, trChild,
				     blChild, brChild),
    m_mapParameters(parameters)
{}

// Freeing recursively the tree
void HeightTree::freeHeightTree() {

    HeightTree *tlTree = this->getChild(TopLeft);
    if (tlTree) {
        tlTree->freeHeightTree();
        tlTree = NULL;
    }

    HeightTree *trTree = this->getChild(TopRight);
    if (trTree) {
        trTree->freeHeightTree();
        trTree = NULL;
    }

    HeightTree *blTree = this->getChild(BottomLeft);
    if (blTree) {
        blTree->freeHeightTree();
        blTree = NULL;
    }

    HeightTree *brTree = this->getChild(BottomRight);
    if (brTree) {
        brTree->freeHeightTree();
        brTree = NULL;
    }

    delete this;
}

// Simply test in wich subsquare the point is
// This function assumes that the position is within the square
HeightTree* HeightTree::locatePosition(Vertex2D & pos) {

    HeightNode content = this->getContent();

    Vertex2D posTL = content.getData(TopLeft).getPosition();
    Vertex2D posBR = content.getData(BottomRight).getPosition();

    float centerX = (posTL.first  + posBR.first)/2.0f;
    float centerY = (posTL.second + posBR.second)/2.0f;
    
    float posX = pos.first;
    float posY = pos.second;

    if (posY >= centerY) {
	if (posX <= centerX) {
	    return this->getChild(TopLeft);
	} else {
	    return this->getChild(TopRight);
	}
    } else {
	if (posX <= centerX) {
	    return this->getChild(BottomLeft);
	} else {
	    return this->getChild(BottomRight);
	}
    }
}

// Try to find if the point is already in the tree
bool HeightTree::findVertexHeight(Vertex2D & pos, int depth, float* height) {

    if (depth == 1) {
	// Check the node
	HeightNode content = this->getContent();
	HeightData data = content.getData(TopLeft);
	if (distanceV2D(pos, data.getPosition()) < m_mapParameters.getDetectionThreshold()) {
	    *height =  data.getHeight();
	    return true;
	}

	data = content.getData(TopRight);
	if (distanceV2D(pos, data.getPosition()) < m_mapParameters.getDetectionThreshold()) {
	    *height =  data.getHeight();
	    return true;
	}

	data = content.getData(BottomLeft);
	if (distanceV2D(pos, data.getPosition()) < m_mapParameters.getDetectionThreshold()) {
	    *height =  data.getHeight();
	    return true;
	}

	data = content.getData(BottomRight);
	if (distanceV2D(pos, data.getPosition()) < m_mapParameters.getDetectionThreshold()) {
	    *height =  data.getHeight();
	    return true;
	}
	return false;	    
    } else {
	// Else try to search deeper
	HeightTree* child = this->locatePosition(pos);
	if (!child)
	    return false;
	return child->findVertexHeight(pos, depth-1, height);
    }
}


void HeightTree::computeTree(voro::container & container, std::vector<Seed> seeds) {
    this->computeTreeInternal(container, seeds, 1, this);
}


void HeightTree::computeTreeInternal(voro::container & container, std::vector<Seed> seeds, 
				     int depth, HeightTree* root) {
    
    // Check the current level must be built or not
    if(!checkSubdivision(m_mapParameters, depth)) return;

    // Recuperating all the needed informations
    HeightNode content = this->getContent();

    HeightData tlData = content.getData(TopLeft);
    HeightData trData = content.getData(TopRight);
    HeightData blData = content.getData(BottomLeft);
    HeightData brData = content.getData(BottomRight);

    // Building now the 5 new heightData required to cut the square
    Vertex2D tlPos = tlData.getPosition();
    Vertex2D brPos = brData.getPosition();

    float tlX = tlPos.first;
    float tlY = tlPos.second;
    float brX = brPos.first;
    float brY = brPos.second;

    float size = brX - tlX;

    float centerX = (tlX + brX)/2.0f;
    float centerY = (tlY + brY)/2.0f;

    // Position of the peaks
    Vertex2D centerPos = Vertex2D(centerX, centerY);
    Vertex2D northPos  = Vertex2D(centerX, tlY);
    Vertex2D southPos  = Vertex2D(centerX, brY);
    Vertex2D eastPos   = Vertex2D(brX,     centerY);
    Vertex2D westPos   = Vertex2D(tlX,     centerY);

    // Their biome
    Biome centerBiome = findClosestBiome(centerPos, container, seeds);
    Biome northBiome  = findClosestBiome(northPos,  container, seeds);
    Biome southBiome  = findClosestBiome(southPos,  container, seeds);
    Biome eastBiome   = findClosestBiome(eastPos,   container, seeds);
    Biome westBiome   = findClosestBiome(westPos,   container, seeds);

    // Computing the height
    // NB : Because the tree is built in this order : TL -> TR -> BL -> BR
    // Only the north and the west might have been already computed
    // Thus we only search for them
    // This ensures the continuity on this level
    float centerHeight = biomeHeight(m_mapParameters, centerBiome);
    float northHeight;
    if (!(root->findVertexHeight(northPos, depth+1, &northHeight))) 
	northHeight = biomeHeight(m_mapParameters, northBiome);
    float southHeight = biomeHeight(m_mapParameters, southBiome);
    float eastHeight = biomeHeight(m_mapParameters, eastBiome);
    float westHeight;
    if (!(root->findVertexHeight(westPos, depth+1, &westHeight)))
	westHeight = biomeHeight(m_mapParameters, westBiome);

    // Finally the 5 datas
    HeightData centerData = HeightData(centerPos, centerHeight, centerBiome);
    HeightData northData  = HeightData(northPos,  northHeight,  northBiome);
    HeightData southData  = HeightData(southPos,  southHeight,  southBiome);
    HeightData eastData   = HeightData(eastPos,   eastHeight,   eastBiome);
    HeightData westData   = HeightData(westPos,   westHeight,   westBiome);

    // Building now the 4 children of the current node
    float subSize = size/2.0f; 
    HeightTree *tlTree = new HeightTree(m_mapParameters, 
					HeightNode(m_mapParameters, subSize,
						   tlData,     northData,
						   westData,   centerData));
    HeightTree *trTree = new HeightTree(m_mapParameters, 
					HeightNode(m_mapParameters, subSize,
						   northData,  trData,
						   centerData, eastData));
    HeightTree *blTree = new HeightTree(m_mapParameters, 
					HeightNode(m_mapParameters, subSize,
						   westData,   centerData,
						   blData,     southData));
    HeightTree *brTree = new HeightTree(m_mapParameters, 
					HeightNode(m_mapParameters, subSize,
						   centerData, eastData,
						   southData,  brData));    

    // Setting them
    this->setChild(TopLeft,     tlTree);
    this->setChild(TopRight,    trTree);
    this->setChild(BottomLeft,  blTree);
    this->setChild(BottomRight, brTree);

    // Building now the next level
    tlTree->computeTreeInternal(container, seeds, depth+1, root);
    trTree->computeTreeInternal(container, seeds, depth+1, root);
    blTree->computeTreeInternal(container, seeds, depth+1, root);
    brTree->computeTreeInternal(container, seeds, depth+1, root);
    
}

float HeightTree::evalHeight(Vertex2D & pos,
			     int effMapSize,
			     Biome* biomeMap) {
    
    // Height generated by the 4 blobs of this level
    float height = this->getContent().evalHeight(pos, effMapSize, biomeMap);

    HeightTree *child = this->locatePosition(pos);
    // If the next level is defined
    if (child)
	// Then also bleding with the height generated by the next level
	height += m_mapParameters.getHeightBlendingCoefficient()*
	    child->evalHeight(pos, effMapSize, biomeMap);

    return height;
}
