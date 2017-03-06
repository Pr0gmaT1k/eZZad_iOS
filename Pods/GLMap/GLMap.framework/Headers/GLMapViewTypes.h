//
//  GLMapViewTypes.h
//  GLMap
//
//  Created by Arkadiy Tolkun on 1/15/16.
//  Copyright © 2016 Evgen Bodunov. All rights reserved.
//

#ifndef GLMapViewSDK_GLMapViewTypes_h
#define GLMapViewSDK_GLMapViewTypes_h

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

    /// Placement of the object on map view. It's used for scale ruler and attribution placement
    typedef enum GLMapPlacement
    {
        /// Top left corner
        GLMapPlacement_TopLeft,
        /// Top center of the screen
        GLMapPlacement_TopCenter,
        /// Top right corner
        GLMapPlacement_TopRight,
        
        /// Bottom left corner
        GLMapPlacement_BottomLeft,
        /// Bottom center of the screen
        GLMapPlacement_BottomCenter,
        /// Bottom rigth corner
        GLMapPlacement_BottomRight,
        
        /// Object should be hidden
        GLMapPlacement_Hidden
    }
    /// :nodoc:
    GLMapPlacement;
    
    /// Errors retured by download tasks
    typedef enum GLMapError
    {
        /// No error
        GLMapError_Success = 0x0000,
        /// Error information is not set
        GLMapError_Empty,
        /// Map download task is cancelled
        GLMapError_Cancelled,
        /// Error occured during tile parsing
        GLMapError_InvalidTileData,
        /// Unused
        GLMapError_InvalidObjectID,
        /// Map list cannot be parsed
        GLMapError_InvalidMapListData,
        /// Can't allocate new objects
        GLMapError_NoMemory,
        
        /// Failed to open output file
        GLMapError_FailedToOpenOutputFile,
        /// Error during writing data into file
        GLMapError_FailedToWrite,
        
        /// Used internally. Check for `[NSError domain]`, if it's equal to `HTTP`, `[NSError code]` is HTTP error code.
        GLMapError_HTTP = 0x1000,
        /// Used internally. Check for `[NSError domain]`, if it's equal to `CURL`, `[NSError code]` is CURL error code. https://curl.haxx.se/libcurl/c/libcurl-errors.html
        GLMapError_CURL = 0x2000,
        /// Used internally. Check for `[NSError domain]`, if it's equal to `XZ`, `[NSError code]` is XZ archiver error code.
        GLMapError_XZ = 0x4000,
        /// Unused
        GLMapError_ExpireWarning = 0x8000,
        /// :nodoc:
    }
    /// :nodoc:
    GLMapError;
    
    /// Checks if it's error or success code
    static inline bool GLMapIsSuccess(GLMapError v) {
        return v == GLMapError_Success;
    }
    
    /// Supported unit systems
    typedef enum GLUnitSystem
    {
        /// International System of Units (SI)
        GLUnitSystem_International,
        /// Imperial units
        GLUnitSystem_Imperial,
        /// Nautical units
        GLUnitSystem_Nautical
    }
    /// :nodoc:
    GLUnitSystem;
    
    /// Supported units
    typedef enum GLUnits
    {
        /// Kilometers
        GLUnits_Kilometers,
        /// Meters
        GLUnits_Meters,
        /// Miles
        GLUnits_Miles,
        /// Foots
        GLUnits_Foots,
        /// Nautical miles
        GLUnits_NauticalMiles
    }
    /// :nodoc:
    GLUnits;
    
    /// Resource information filled by `GLMapResourceBlock`
    typedef struct GLMapResource {
        /// Object data
        void *data;
        /// Object data size
        uint32_t dataSize;
        /// Image scale if it's image
        float imageScale;
    }
    /// :nodoc:
    GLMapResource;
    
    /// @return Returns empty resource data.
    static inline GLMapResource GLMapResourceEmpty() {
#ifdef __cplusplus
        GLMapResource resource = {nullptr, 0, 0.f};
#else
        GLMapResource resource = {NULL, 0, 0.f};
#endif
        return resource;
    }
    
    /// Map tile state
    typedef enum GLMapTileState : unsigned char
    {
        /// Tile without data
        GLMapTileState_NoData,
        /// Tile data is being loaded
        GLMapTileState_Updating,
        /// Tile already has data
        GLMapTileState_HasData,
    }
    /// :nodoc:
    GLMapTileState;
    
    /// Transition functions available
    typedef enum GLMapTransitionFunction
    {
        /// Instant set value. No animation.
        GLMapTransitionInstant = 0,
        /// Linear animation.
        GLMapTransitionLinear,
        /// Ease-in animation.
        GLMapTransitionEaseIn,
        /// Ease-out animation.
        GLMapTransitionEaseOut,
        /// Ease-in-out animation.
        GLMapTransitionEaseInOut,
    }
    /// :nodoc:
    GLMapTransitionFunction;
    
    /// Merkator tile coordinates
    typedef struct GLMapTilePos {
        /// X coordinate
        int x;
        /// Y coordinate
        int y;
        /// Z coordinate
        int z;
    }
    /// :nodoc:
    GLMapTilePos;

    /**
     Creates `GLMapTilePos`
     
     @param x X coordinate
     @param y Y coordinate
     @param z Z coordinate
     @return New tile position
     */
    static inline GLMapTilePos GLMapTilePosMake(int x, int y, int z) {
        GLMapTilePos pos;
        pos.x = x;
        pos.y = y;
        pos.z = z;
        return pos;
    }
    
    /// Geo point with latitude and longitude
    typedef struct GLMapGeoPoint
    {
        /// Latitude
        double lat;
        /// Longitude
        double lon;
    }
    /// :nodoc:
    GLMapGeoPoint;
    
    /**
     Creates new `GLMapGeoPoint`.
     
     @param lat Latitude
     @param lon Longitude
     @return New geo point
     */
    static inline GLMapGeoPoint GLMapGeoPointMake(double lat, double lon) {
        GLMapGeoPoint pt;
        pt.lat = lat;
        pt.lon = lon;
        return pt;
    }
    
    /// `GLMapPoint` always uses internal map coordinates. From 0 to `GLMapPointMax` for X and Y axis. Origin is at the top left corner.
    typedef struct GLMapPoint
    {
        /// X coordinate
        double x;
        /// Y coordinate
        double y;
    }
    /// :nodoc:
    GLMapPoint;
    
    /// Maximum `GLMapPoint` value. World size in map coordinates is from 0 to `GLMapPointMax`.
    extern const int GLMapPointMax;
    
    /** 
     Creates new `GLMapPoint`
    
     @param x X coordinate
     @param y Y coordinate
     @return New map point
     */
    static inline GLMapPoint GLMapPointMake(double x, double y) {
        return (GLMapPoint){x,y};
    }
    
    /**
     Checks equality of two map points
     
     @param a First map point
     @param b Second map point
     @return `true` if map points is equal
     */
    static inline bool GLMapPointEqual(GLMapPoint a, GLMapPoint b) {
        return a.x == b.x && a.y == b.y;
    }
    
    
    /// `GLMapColor` is color type based on `uint32_t`
    typedef uint32_t GLMapColor;
    
    /**
     Creates new color from int chanel values 0 - 255
     
     @param r Red channel value
     @param g Green channel value
     @param b Blue channel value
     @param a Alpha channel value
     
     @return Returns new color object
     */
    static inline GLMapColor GLMapColorMake(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        return (a << 24) | (b << 16) | (g << 8) | r;
    }
    
    /**
     Creates new color from float chanel values 0.0 - 1.0
     
     @param r Red channel value
     @param g Green channel value
     @param b Blue channel value
     @param a Alpha channel value
     
     @return Returns new color object
     */
    static inline GLMapColor GLMapColorMakeF(float r, float g, float b, float a) {
        return ((uint8_t)(a * 255) << 24) | ((uint8_t)(b * 255) << 16) | ((uint8_t)(g * 255) << 8) | (uint8_t)(r * 255);
    }
    
#ifdef __OBJC__
    /// :nodoc:
    @class UIColor;
    
    /**
     Creates `UIColor` object from our `GLMapColor`
     
     @param color Initial color
     @return New `UIColor` object
     */
    UIColor *UIColorFromGLMapColor(GLMapColor color);
#endif    
    
    /// Point of track with color
    typedef struct GLTrackPoint {
        /**
         Point of track in framework coordinates
         */
        GLMapPoint pt;
        /**
         Color of point. Specific color could be set for each point.
         */
        GLMapColor color;
    }
    /// :nodoc:
    GLTrackPoint;
    
    /// Bounding box
    typedef struct GLMapBBox
    {
        /// Bounding box origin. Point with minimal coordinates.
        GLMapPoint origin;
        /// Size of the bounding box.
        GLMapPoint size;
    }
    /// :nodoc:
    GLMapBBox;

    /**
     @return Returns empty bounding box
     */
    static inline GLMapBBox GLMapBBoxEmpty() {
        GLMapBBox bbox;
        bbox.origin = GLMapPointMake(0, 0);
        bbox.size = GLMapPointMake(-1, -1);
        return bbox;
    }

    /**
     Adds point into existing bounding box.
     
     @param bbox Bounding box
     @param point Point to add into bounding box
     */
    static inline void GLMapBBoxAddPoint(GLMapBBox *bbox, GLMapPoint point) {
        if (!bbox)
            return;
        
        if (bbox->size.x < 0 && bbox->size.y < 0) {
            bbox->size = GLMapPointMake(0,0);
            bbox->origin = point;
        } else {
            if (point.x < bbox->origin.x) {
                bbox->size.x += bbox->origin.x - point.x;
                bbox->origin.x = point.x;
            }
            if (point.x > bbox->origin.x + bbox->size.x) {
                bbox->size.x = point.x - bbox->origin.x;
            }
            
            if (point.y < bbox->origin.y) {
                bbox->size.y += bbox->origin.y - point.y;
                bbox->origin.y = point.y;
            }
            if (point.y > bbox->origin.y + bbox->size.y) {
                bbox->size.y = point.y - bbox->origin.y;
            }
        }
    }
    
    /**
     Creates new bounding box
     
     @param origin Origin point
     @param width Width
     @param height Height
     @return New bounding box
     */
    static inline GLMapBBox GLMapBBoxMake(GLMapPoint origin, double width, double height) {
        GLMapBBox bbox;
        bbox.origin = origin;
        bbox.size = GLMapPointMake(width, height);
        return bbox;
    }
    
    /**
     Checks equality of two bounding boxes
     
     @param a First bounding box
     @param b Second bounding box
     @return `true` if bounding boxes is equal
     */
    static inline bool GLMapBBoxEqual(GLMapBBox a, GLMapBBox b) {
        return GLMapPointEqual(a.origin, b.origin) &&  GLMapPointEqual(a.size, b.size);
    }
    
    /**
     Creates map point from geo coordinates
     
     @param lat Latitude
     @param lon Longitude
     @return New map point
     */
    GLMapPoint GLMapPointMakeFromGeoCoordinates(double lat, double lon);
    
    /**
     Creates geo point from map coordinates
     
     @param point Map point
     @return New geo point
     */
    GLMapGeoPoint GLMapGeoPointFromMapPoint(GLMapPoint point);
    
    /**
     Calculates distance between two points on map
     
     @param a First point on map
     @param b Second point on map
     @return Distance in meters
     */
    double GLMapMetersBetweenPoints(GLMapPoint a, GLMapPoint b);
    
    /// Allows application to change verbosity of GLMap logs
    extern char GLMapLogMask;
    
    // loglevel
#define VERBOSE_FLAG	1 << 0
#define ERROR_FLAG      1 << 1
#define FATAL_FLAG		1 << 2
#define OPENGL_FLAG     1 << 3
    
    /// :nodoc:
    void SendLogMessage(const char *, ...);
    
#ifdef __cplusplus
}
#endif

#endif
