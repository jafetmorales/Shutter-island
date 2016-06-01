#include <cstring>
#include <fstream>
#include <iostream>
#include <streambuf>

#include "../../include/rapidjson/document.h"
#include "../../include/terrain/MapParameters.hpp"

MapParameters::MapParameters(const std::string& filename)
{
    /*
     * Creating a rapidJSon document so as to parse the JSon configuration
     * file.
     */
    rapidjson::Document document; 
    std::ifstream file(filename);
    std::string fileContent;

    /*
     * Resizing the "fileContent" buffer to the size of the content.
     */
    file.seekg(0, std::ios::end);
    fileContent.reserve(file.tellg());
    file.seekg(0, std::ios::beg);

    /*
     * Copying the content of the file into the "fileContent" buffer.
     */
    fileContent.assign(
        std::istreambuf_iterator<char>(file),
        std::istreambuf_iterator<char>()
    );

    /*
     * Parsing the JSon file, and assigning the parsed value to the
     * stored attributes.
     */
    document.Parse(fileContent.c_str());

    /*
     * Biome "defines".
     */
    m_heightMinSea = document["Biome"]["heightMinSea"].GetFloat();
    m_heightMaxSea = document["Biome"]["heightMaxSea"].GetFloat();
    m_heightMinLake = document["Biome"]["heightMinLake"].GetFloat();
    m_heightMaxLake = document["Biome"]["heightMaxLake"].GetFloat();
    m_heightMinInnerBeach = document["Biome"]["heightMinInnerBeach"].GetFloat();
    m_heightMaxInnerBeach = document["Biome"]["heightMaxInnerBeach"].GetFloat();
    m_heightMinOutterBeach = document["Biome"]["heightMinOutterBeach"].GetFloat();
    m_heightMaxOutterBeach = document["Biome"]["heightMaxOutterBeach"].GetFloat();
    m_heightMinPlains = document["Biome"]["heightMinPlains"].GetFloat();
    m_heightMaxPlains = document["Biome"]["heightMaxPlains"].GetFloat();
    m_heightMinMountain = document["Biome"]["heightMinMountain"].GetFloat();
    m_heightMaxMountain = document["Biome"]["heightMaxMountain"].GetFloat();
    m_heightMinPeak = document["Biome"]["heightMinPeak"].GetFloat();
    m_heightMaxPeak = document["Biome"]["heightMaxPeak"].GetFloat();
    m_scaleLimitInfluence = document["Biome"]["scaleLimitInfluence"].GetFloat();
    m_biomeDepthMin = document["Biome"]["biomeDepthMin"].GetInt();
    m_biomeDepthMax = document["Biome"]["biomeDepthMax"].GetInt();

    /*
     * Biome Repartition "defines".
     */
     m_landBlendingCoefficient = document["BiomeRepartition"]["landBlendingCoefficient"].GetFloat();
     m_lakeGeometricPicking = document["BiomeRepartition"]["lakeGeometricPicking"].GetFloat();
     m_lakeProbTransform = document["BiomeRepartition"]["lakeProbTransform"].GetFloat();
     m_lakePositiveInfluence = document["BiomeRepartition"]["lakePositiveInfluence"].GetFloat();
     m_mountainGeometricPicking = document["BiomeRepartition"]["mountainGeometricPicking"].GetFloat();
     m_mountainProbTransform = document["BiomeRepartition"]["mountainProbTransform"].GetFloat();
     m_mountainMaxTry = document["BiomeRepartition"]["mountainMaxTry"].GetInt();
}

/*
 * Biome "getters".
 */
float MapParameters::getHeightMinSea()
{
    return m_heightMinSea;
}

float MapParameters::getHeightMaxSea()
{
    return m_heightMaxSea;
}

float MapParameters::getHeightMinLake()
{
    return m_heightMinLake;
}

float MapParameters::getHeightMaxLake()
{
    return m_heightMaxLake;
}


float MapParameters::getHeightMinInnerBeach()
{
    return m_heightMinInnerBeach;
}

float MapParameters::getHeightMaxInnerBeach()
{
    return m_heightMaxInnerBeach;
}

float MapParameters::getHeightMinOutterBeach()
{
    return m_heightMinOutterBeach;
}

float MapParameters::getHeightMaxOutterBeach()
{
    return m_heightMaxOutterBeach;
}

float MapParameters::getHeightMinPlains()
{
    return m_heightMinPlains;
}

float MapParameters::getHeightMaxPlains()
{
    return m_heightMaxPlains;
}

float MapParameters::getHeightMinMountain()
{
    return m_heightMinMountain;
}

float MapParameters::getHeightMaxMountain()
{
    return m_heightMaxMountain;
}

float MapParameters::getHeightMinPeak()
{
    return m_heightMinPeak;
}

float MapParameters::getHeightMaxPeak()
{
    return m_heightMaxPeak;
}

float MapParameters::getScaleLimitInfluence()
{
    return m_scaleLimitInfluence;
}

int MapParameters::getBiomeDepthMin()
{
    return m_biomeDepthMin;
}

int MapParameters::getBiomeDepthMax()
{
    return m_biomeDepthMax;
}

/*
 * BiomeRepartition "getters".
 */
float MapParameters::getLandBlendingCoefficient()
{
    return m_landBlendingCoefficient;
}

float MapParameters::getLakeGeometricPicking()
{
    return m_lakeGeometricPicking;
}

float MapParameters::getLakeProbTransform()
{
    return m_lakeProbTransform;
}

float MapParameters::getLakePositiveInfluence()
{
    return m_lakePositiveInfluence;
}

float MapParameters::getMountainGeometricPicking()
{
    return m_mountainGeometricPicking;
}

float MapParameters::getMountainProbTransform()
{
    return m_mountainProbTransform;
}

int MapParameters::getMountainMaxTry()
{
    return m_mountainMaxTry;
}
