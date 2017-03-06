//
//  GLMapVectorObject.h
//  GLMap
//
//  Created by Arkadi Tolkun on 3/21/14.
//  Copyright (c) 2014 Evgen Bodunov. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "GLMapViewTypes.h"

@class GLMapVectorStyle;
@class GLSearchCategory;
@class GLSearchCategories;
@class GLMapLocaleSettings;

/// Type of data inside of the `GLMapVectorObject`
typedef NS_ENUM(NSInteger, GLMapVectorObjectType) {
    /// No geometry loaded yet
    GLMapVectorObjectType_Unknown,
    /// Point object
    GLMapVectorObjectType_Point,
    /// Line object
    GLMapVectorObjectType_Line,
    /// Polygon object
    GLMapVectorObjectType_Polygon
};

/**
 `GLMapVectorObject` is a bridge class, to work with GLMap internal representation of vector object.
 */
@interface GLMapVectorObject : NSObject

#pragma mark - Properties

/**
 Point that belongs to vector object.
 */
@property (readonly) GLMapPoint point;

/**
 Data previously loaded by <code>-[GLMapVectorObject loadMultiLine:]</code> or <pre>-[GLMapVectorObject loadGeoMultiLine:]</pre>.
 */
@property (readonly) NSArray<NSData *> *_Nullable multilineData;

/**
 Bounding box of an object
 */
@property (readonly) GLMapBBox bbox;

/**
 Contains kind of geometry loaded to object. GLMapVectorObjectType_Unknown means that no geomety is loaded.
 */
@property(readonly) GLMapVectorObjectType type;

#pragma mark - Static Methods

/**
 Creates array of vector object from GeoJSON data
 
 @param geoJSONData Data with GeoJSON inside
 
 @return Array of new vector objects
 */
+(NSArray<GLMapVectorObject *> * _Nullable) createVectorObjectsFromGeoJSONData:(NSData * _Nonnull)geoJSONData;

/**
 Creates array of vector object from GeoJSON string
 
 @param geoJSON String with GeoJSON inside
 
 @return Array of new vector objects
 */
+(NSArray<GLMapVectorObject *> * _Nullable) createVectorObjectsFromGeoJSON:(NSString * _Nonnull)geoJSON;

/**
 Creates array of vector object from GeoJSON file
 
 @param filePath Path to GeoJSON file
 
 @return Array of new vector objects
 */
+(NSArray<GLMapVectorObject *> * _Nullable) createVectorObjectsFromFile:(NSString * _Nonnull)filePath;

#pragma mark - Methods

/**
 Sets geometry data for point object.
 
 @param point Point on the map.
 */
-(void) loadPoint:(GLMapPoint)point;

/**
 Loads geometry data into vector object.
 
 Example of creation of multiLineData with one line:

 NSMutableArray *multilineData = [[NSMutableArray alloc] init];
 
 int pointCount = 5;
 NSMutableData *data = [NSMutableData dataWithLength:sizeof(GLMapGeoPoint)*pointCount];
 GLMapGeoPoint *pts= (GLMapGeoPoint *)data.mutableBytes;
 
 pts[0] = GLMapGeoPointMake(53.8869, 27.7151); // Minsk
 pts[1] = GLMapGeoPointMake(50.4339, 30.5186); // Kiev
 pts[2] = GLMapGeoPointMake(52.2251, 21.0103); // Warsaw
 pts[3] = GLMapGeoPointMake(52.5037, 13.4102); // Berlin
 pts[4] = GLMapGeoPointMake(48.8505, 2.3343);  // Paris
 [multilineData addObject:data];
 
 @param multiLineData `NSArray` of the `NSData` objects. Each NSData contains array of `GLMapPoint` objects.
 */
-(void) loadMultiLine:(NSArray<NSData *> *_Nonnull)multiLineData NS_SWIFT_UNAVAILABLE("Please use addLine: or addGeoLine:");

/**
 Loads geometry data into vector object.
 
 @param multiLineData `NSArray` of the `NSData` objects. Each NSData contains array of `GLMapGeoPoint` objects.
 */
-(void) loadGeoMultiLine:(NSArray<NSData *> *_Nonnull)multiLineData NS_SWIFT_UNAVAILABLE("Please use addLine: or addGeoLine:");

/**
 Adds line
 
 @param lineArray Array of `GLMapPoint` objects
 @param pointCount Number of points inside the `lineArray`
 */
-(void) addLine:(const GLMapPoint *_Nonnull)lineArray pointCount:(NSInteger)pointCount NS_REFINED_FOR_SWIFT;

/**
 Adds geo line
 
 @param geoLineArray Array of `GLMapGeoPoint` objects
 @param pointCount Number of points inside the `lineArray`
 */
-(void) addGeoLine:(const GLMapGeoPoint *_Nonnull)geoLineArray pointCount:(NSInteger)pointCount NS_REFINED_FOR_SWIFT;

/**
 Sets geometry data for vector object.
 
 Creation of polygonData will looks like this:
 
 <pre>
 NSMutableArray *outerRings = [[NSMutableArray alloc] init];
 NSMutableArray *innerRings = [[NSMutableArray alloc] init];
 
 GLMapPoint *pts= (GLMapPoint *)malloc(sizeof(GLMapPoint)*pointCount);
 <fill pts with data>
 [outerRings addObject:[NSData dataWithBytesNoCopy:pts length:sizeof(GLMapPoint)*pointCount]];
 
 pts= (GLMapPoint *)malloc(sizeof(GLMapPoint)*pointCount);
 <fill pts with data>
 [innerRings addObject:[NSData dataWithBytesNoCopy:pts length:sizeof(GLMapPoint)*pointCount]];
 polygonData = @[outerRings, innerRings];
 </pre>
 
 @param polygonData `NSArray` with 2 objects. First one contains outer rings of polygons. Second contains inner rings. Format of rings is same as for multiline.
 
 @see `[GLMapVectorObject addPolygonOuterRing:pointCount:]`
 @see `[GLMapVectorObject addPolygonInnerRing:pointCount:]`
 */
-(void) loadPolygon:(NSArray<NSArray<NSData*> *> *_Nonnull)polygonData NS_SWIFT_UNAVAILABLE("Please use addPolygonOuterRing: or addPolygonInnerRing:");

/**
 Sets geometry data for vector object.
 
 @param polygonData `NSArray` with 2 objects. First one contains outer rings of polygons. Second contains inner rings. Format of rings is same as for geo multiline.
 
 @see `[GLMapVectorObject addGeoPolygonOuterRing:pointCount:]`
 @see `[GLMapVectorObject addGeoPolygonInnerRing:pointCount:]`
 */
-(void) loadGeoPolygon:(NSArray<NSArray<NSData*> *> *_Nonnull)polygonData NS_SWIFT_UNAVAILABLE("Please use addPolygonOuterRing: or addPolygonInnerRing:");

/**
 Adds one outer ring from `GLMapPoint` array
 
 @param outerRing Array of `GLMapPoint` objects
 @param pointCount Number of points inside the `lineArray`
 */
-(void) addPolygonOuterRing:(const GLMapPoint *_Nonnull)outerRing pointCount:(NSInteger)pointCount NS_REFINED_FOR_SWIFT;

/**
 Adds one inner ring from `GLMapPoint` array
 
 @param innerRing Array of `GLMapPoint` objects
 @param pointCount Number of points inside the `lineArray`
 */
-(void) addPolygonInnerRing:(const GLMapPoint *_Nonnull)innerRing pointCount:(NSInteger)pointCount NS_REFINED_FOR_SWIFT;

/**
 Adds one outer ring from `GLMapGeoPoint` array
 
 @param outerRing Array of `GLMapPoint` objects
 @param pointCount Number of points inside the `lineArray`
 */
-(void) addGeoPolygonOuterRing:(const GLMapGeoPoint *_Nonnull)outerRing pointCount:(NSInteger)pointCount NS_REFINED_FOR_SWIFT;

/**
 Adds one inner ring from `GLMapGeoPoint` array
 
 @param innerRing Array of `GLMapGeoPoint` objects
 @param pointCount Number of points inside the `lineArray`
 */
-(void) addGeoPolygonInnerRing:(const GLMapGeoPoint *_Nonnull)innerRing pointCount:(NSInteger)pointCount NS_REFINED_FOR_SWIFT;

/**
 Adds big circle line from `start` to `end`. Useful to display plane routes. Should be used only on empty `GLMapVectorObject`
 
 @param start Start point
 @param end End point
 @param quality Maximum distance from point to line, used for simplification in Douglas Peucker algorithm. Units is map internal coordinates.
 */
-(void) setGeoLineStart:(GLMapPoint)start end:(GLMapPoint)end quality:(double)quality;

/**
 Sets properties of object. This can be used by mapcss to apply different styles.
 
 In MapCSS style if you have for example rule `area|z9-[key=value]{ .. style params .. }`, "[key=value]" part means, that it will be applied only to objects, which have key equal to value. And this function allows you to set key and value. Other option is to pass keys and values is set them as properties of Features in GeoJSON.
 
 @param value Value to be set, or nil to remove value
 @param key Key to be set
 */
-(void) setValue:(NSString *_Nullable)value forKey:(NSString *_Nonnull)key;

/**
 Returns value of object style
 
 @param key Key string
 @return Value that set by `[GLMapVectorObject setValue:forKey:]` or loaded from geojson
 */
-(NSString *_Nullable) valueForKey:(NSString *_Nonnull)key;

/**
 Used for objects returned by offline search. When part of an object name is matched during search, this functions returns `NSAttributedString` with higlighted parts.
 
 @param color Text color
 @param highlightColor Highlighted text color
 @param localeSettings Locale settings used to find first matched name
 
 @return Name with highlighted parts
 */
-(NSAttributedString *_Nullable) attributedNameWithColor:(UIColor *_Nonnull)color andHighlightColor:(UIColor *_Nonnull)highlightColor localeSettings:(GLMapLocaleSettings *_Nonnull)localeSettings;

/**
 Returns name of search result.
 
 @param localeSettings Locale settings used to find first matched name
 
 @return Object name
 */
-(NSString *_Nullable) nameWithLocaleSettings:(GLMapLocaleSettings *_Nonnull)localeSettings;

/**
 Detects category of the object.
 
 @param categories All possible categories
 
 @return matched category object
 */
-(GLSearchCategory *_Nullable) searchCategory:(GLSearchCategories *_Nonnull)categories;

/**
 Call this method before adding vector object on map to use custom offset and scale for object.
 
 @see `[GLMapVectorObject setOffset:andScale:]`
 */
-(void) useTransform;

/**
 Sets offset and scale for vector object.
 
 @param offset offset to set
 @param scale scale to set
 */
-(void) setOffset:(GLMapPoint)offset andScale:(CGFloat)scale;

/**
 Finds nearest point of object to given point
 */
-(BOOL) findNearestPoint:(GLMapPoint *_Nonnull)nearestPoint toPoint:(GLMapPoint)point maxDistance:(CGFloat)distance;

@end
