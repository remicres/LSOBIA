#ifndef otbObiaSpatialTools_h
#define otbObiaSpatialTools_h
#include <cstdint>
#include <cmath>
#include <array>
#include <algorithm>
#include <limits>
#include <unordered_set>

#include "otbObiaConstExpr.h"
#include "itkImageRegion.h"

namespace otb
{

namespace obia
{

/*
*    Processing Tile
*
*    
**/
struct ProcessingTile
{
    // Coordinates of the tile in the tiling referential
    uint32_t m_Tx;
    uint32_t m_Ty;

    // Frame of the tile with a potential margin
    itk::ImageRegion<2> m_Frame;

    // Values of the margins in each direction
    std::array<long int, 4> m_MarginValues;
};

/** Create an enum class for the directions to be more readable */
enum Direction{
    TOP = 0,
    RIGHT,
    BOTTOM,
    LEFT
};



/** class SpatialTools
 * \brief class gathering a set of methods
 *        of spatial computations.
 */
 class SpatialTools
 {
 public:

     /** Compute the neighbors at top, right, bottom and left */
     static std::array<int64_t, 4> FourConnectivity(const uint64_t vecCoords,
                          const uint32_t imgWidth, 
                          const uint32_t imgHeight);

     /** 
         In addition to the four previous neighbors, it computes at top right, bottom right,
         bottom left and top left.
      */
     static std::array<int64_t, 8> EightConnectivity(const uint64_t vecCoords,
                           const uint32_t imgWidth, 
                           const uint32_t imgHeight);

     /** Union of the bounding boxes bboxIn and bboxOut, the result is bboxIn */
     static void MergeBoundingBox(std::array<uint32_t,4>& bboxIn, 
                const std::array<uint32_t, 4>& bboxOut);

     /** Returns the union of bounding boxe bboxIn with bboxOut */
     static std::array<uint32_t, 4> GetMergedBoundingBox(const std::array<uint32_t,4>& bboxIn,
                               const std::array<uint32_t, 4>& bboxOut);


  /**
      TransformPixelCoordsFromTileRefToImgRef

      This method transforms the pixel coordinates from the tile referential
      to the image referential.

      @param pixCoords: pixel coordinates in the tile referential
      @param tile: data structure representing a tile in the image.
      @param imageWidth: size of the image in the new referential

      @return: the new pixel coordinates in the image referential.
    */
    static
    CoordValueType
    TransformPixelCoordsFromTileRefToImgRef(const CoordValueType pixCoords,
                                            const ProcessingTile& tile,
                                            const uint32_t imageWidth);

    /**
      TransformBBoxCoordsFromTileRefToImgRef

      This method transforms the pixel coordinates from the tile referential
      to the image referential.

      @param bbox: bbox in the tile referential
      @param tile: data structure representing a tile in the image.

      @return: the new bbox in the image referential.
    */
    static
    std::array<uint32_t, 4>
    TransformBBoxCoordsFromTileRefToImgRef(const std::array<uint32_t, 4>& bbox,
                                           const ProcessingTile& tile);

    /**
      IsBboxInsideBoundaries

      This method returns true if the bbox is within the rectangle delimited
      by the boundaries.

      @param bbox: bbox in the tile referential
      @param lowerCol: Left side of the rectangle
      @param lowerRow: top side of the rectangle
      @param upperCol: right side of the rectangle
      @param upperRow: bottom side of the rectangle

      @return: a boolean indicating if the bbox is within the rectangle.
    */
    static
    bool
    IsBboxInsideBoundaries(const std::array<uint32_t, 4>& bbox,
                           const uint32_t lowerCol,
                           const uint32_t lowerRow,
                           const uint32_t upperCol,
                           const uint32_t upperRow);

    /**
      IsBboxStrictlyInsideBoundaries

      This method returns true if the bbox is strictly within the rectangle delimited
      by the boundaries.

      @param bbox: bbox in the tile referential
      @param lowerCol: Left side of the rectangle
      @param lowerRow: top side of the rectangle
      @param upperCol: right side of the rectangle
      @param upperRow: bottom side of the rectangle

      @return: a boolean indicating if the bbox is strictly within the rectangle.
    */
    static
    bool
    IsBboxStrictlyInsideBoundaries(const std::array<uint32_t, 4>& bbox,
                                     const uint32_t lowerCol,
                                     const uint32_t lowerRow,
                                     const uint32_t upperCol,
                                     const uint32_t upperRow);

    /**
      IsBboxOutsideBoundaries

      This method returns true if the bbox is outside of the rectangle delimited
      by the boundaries.

      @param bbox: bbox in the tile referential
      @param lowerCol: Left side of the rectangle
      @param lowerRow: top side of the rectangle
      @param upperCol: right side of the rectangle
      @param upperRow: bottom side of the rectangle

      @return: a boolean indicating if the bbox is outside the rectangle.
    */
    static
    bool
    IsBboxOutsideBoundaries(const std::array<uint32_t, 4>& bbox,
                            const uint32_t lowerCol,
                            const uint32_t lowerRow,
                            const uint32_t upperCol,
                            const uint32_t upperRow);

    static
    bool
    IsPixelAtTileBorder(const CoordValueType pixCoords,
                        const uint32_t tx,
                        const uint32_t ty,
                        const uint32_t lowerCol,
                        const uint32_t lowerRow,
                        const uint32_t upperCol,
                        const uint32_t upperRow,
                        const uint32_t nbTilesX,
                        const uint32_t nbTilesY,
                        const uint32_t imageWidth);

    static
    bool
    IsPixelAtBoundaries(const CoordValueType pixCoords,
                        std::unordered_set<uint32_t>& rowBounds,
                        std::unordered_set<uint32_t>& colBounds,
                        const uint32_t inputLSImageWidth);

     /** Compare safely two float numbers...*/
     static bool AreFloatNumbersApproximatelyEqual(const float a, const float b);
};

} // end of namespace obia

} // end of namespace otb

#endif
