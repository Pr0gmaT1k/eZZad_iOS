//
//  GLMapView.h
//  GLMapView
//
//  Copyright (c) 2014 Evgen Bodunov. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKit.h>

#import "GLMapViewTypes.h"
#import "GLMapMarkerLayer.h"

@class GLMapImage;
@class GLMapImageGroup;
@class GLMapVectorObject;
@class GLMapVectorStyle;
@class GLMapVectorCascadeStyle;
@class GLMapRasterTileSource;
@class GLMapMarkerStyleCollection;
@class GLMapTrack;
@class GLMapTrackData;
@class GLSearchCategories;
@class GLMapLocaleSettings;
@class GLMapVectorObjectDrawOptions;

/// :nodoc:
extern NSString * _Nonnull GLMapViewErrorDomain;

NS_ASSUME_NONNULL_BEGIN

/// `GLMapTapGestureBlock` called, when user tapped or long tapped on map. Add custom tap handling logic inside this block.
typedef void (^GLMapTapGestureBlock)(CGPoint pt);

/// `GLMapBBoxChangedBlock` called every time, when map is moved or zoom is changed.
typedef void (^GLMapBBoxChangedBlock)(GLMapBBox bbox);

/// `GLMapAnimationBlock` called every frame wile `YES` returned. If `NO` returned - animation block will be removed
typedef BOOL (^GLMapAnimationBlock)(double dt);

/// `GLMapVisibleTilesChangedBlock` called when set of visible tiles changed
typedef void (^GLMapVisibleTilesChangedBlock)(NSSet *visibleTiles);

/// `GLMapTileErrorBlock` called when there is no data for tile, or map can't download tile. It allows to use custom 'no data' tiles.
typedef UIImage *_Nullable (^GLMapTileErrorBlock)(GLMapTilePos pos, NSError *error);

/// `GLMapCaptureFrameBlock` is called when frame is captured.
typedef void (^GLMapCaptureFrameBlock)(UIImage *_Nullable);

/// `GLMapScaleRulerTextFormatterBlock` is used to change scale ruler format or localize unit name.
typedef NSString *_Nullable(^GLMapScaleRulerTextFormatterBlock)(int value, GLUnits units);

/// `GLMapResourceBlock` is used to load resources from custom place.
typedef GLMapResource (^GLMapResourceBlock)(NSString *_Nonnull name);

/**
 `GLMapView` is a custom `UIView` that renders and presents vector map.
 */
@interface GLMapView : UIView<CLLocationManagerDelegate>

/**
 Captures frame from `GLMapView` to `UIImage`
 
 @return Current state of the `GLMapView`
 */
-(nullable UIImage *) captureFrame;

/**
 Captures frame from `GLMapView` to `UIImage` when all load operations will finish.
 
 @param block Block callback is called when screenshot is ready.
 
 @see `-captureFrame`
 @see `offscreen`
 */
-(void) captureFrameWhenFinish:(GLMapCaptureFrameBlock) block;

/**
 Allows to render offscreen frames
 
 By default offscreen = `NO`. And GLMapView stop render if there is no superview. But in case you need to capture frames from standalone GLMapView, you need to set offscreen = YES;
 */
@property BOOL offscreen;

/**
 Rendering frame interval. By default frameInterval is 2 (30 fps)
 */
@property NSInteger frameInterval;

/**
 State of tile in center of screen
 
 @see `centerTileStateChangedBlock`
 */
@property (readonly) GLMapTileState centerTileState;

#pragma mark - User Interface

/// Gestures handled by `GLMapView`
typedef NS_OPTIONS(NSUInteger, GLMapViewGestures)
{
    /// Gesture recognition disabled
    GLMapViewGesture_None     = 0,
    /// Pan gesture
    GLMapViewGesture_Pan      = 1,
    /// Zoom gesture
    GLMapViewGesture_Zoom     = 1 << 1,
    /// Rotate gesture
    GLMapViewGesture_Rotate   = 1 << 2,
    /// Zoom in gesture
    GLMapViewGesture_ZoomIn   = 1 << 3,
    /// Zoom out gesture
    GLMapViewGesture_ZoomOut  = 1 << 4,
    /// Tap gesture
    GLMapViewGesture_Tap      = 1 << 5,
    /// Long press gesture
    GLMapViewGesture_LongPress= 1 << 6,
    /// Recognise all gestures
    GLMapViewGesture_All =
        GLMapViewGesture_Pan|
        GLMapViewGesture_Zoom|
        GLMapViewGesture_Rotate|
        GLMapViewGesture_ZoomIn|
        GLMapViewGesture_ZoomOut|
        GLMapViewGesture_Tap|
        GLMapViewGesture_LongPress
};

/**
 Sets mask that defines enabled gestures.
 
 Use `tapGestureBlock` and `longPressGestureBlock` to add your tap and long press handlers.
 */
@property (nonatomic, assign) GLMapViewGestures gestureMask;

/// `tapGestureBlock` called for each tap gesture recognized.
@property (copy) GLMapTapGestureBlock _Nullable tapGestureBlock;

/// `longPressGestureBlock` called for each long press gesture recognized.
@property (copy) GLMapTapGestureBlock _Nullable longPressGestureBlock;

/// `bboxChangedBlock` called when map is moved or zoomed.
@property (copy) GLMapBBoxChangedBlock _Nullable bboxChangedBlock;

/// `mapDidMoveBlock` called when animation or deceleration ends.
@property (copy) GLMapBBoxChangedBlock _Nullable mapDidMoveBlock;

/// `visibleTilesChangedBlock` called when set of visible tiles is changed.
@property (copy) GLMapVisibleTilesChangedBlock _Nullable visibleTilesChangedBlock;

/**
 `tileErrorBlock` called when empty tile without data becomes visible.
 
 This method is used to show custom data inside empty tiles.
 */
@property (copy) GLMapTileErrorBlock _Nullable tileErrorBlock;

/// `centerTileStateChangedBlock` called when centerTileState is changed
@property (copy) dispatch_block_t centerTileStateChangedBlock;

/// Bounding box of the map
@property (readonly) GLMapBBox bbox;

/**
 Sets position of map attribution.
 
 @param position Position to set.
 */
-(void) setAttributionPosition:(GLMapPlacement)position;

/**
 Sets text at the bottom of ruler.
 
 It's used to display map center coordinates or any other useful information
 */
-(void) setScaleRulerBottomText:(NSString *_Nullable)text;

/**
 Sets style of the scale ruler.
 
     //Sets scale ruler position to the bottom center part of screen. And width to half of screen width
     [_mapView setScaleRulerUnits:[AppSettings settings].units placement:GLMapPlacement_BottomLeft paddings:CGPointMake(5, 5) maxWidth:300];
 
 @param unitSystem Unit system used by scale ruler
 @param placement placement of text
 @param paddings paddings of scale ruler
 @param maxWidth maxWidth of scale hit in points
 */
-(void) setScaleRulerUnits:(GLUnitSystem)unitSystem placement:(GLMapPlacement)placement paddings:(CGPoint)paddings maxWidth:(float)maxWidth;

/**
 Sets block that called when ruler value is updated. Block allows to translate units and use custom digit format inside ruler.
 
 @param block New text formatter block
 */
-(void) setScaleRulerTextFormatterBlock:(GLMapScaleRulerTextFormatterBlock)block;

#pragma mark - User Location
/**
 In order to show user location using GLMapView you should create your own CLLocationManager and set GLMapView as CLLocationManager's delegate. Or you could forward `-locationManager:didUpdateLocations:` calls from your location manager delegate to the GLMapView.
 */

/// Last location received by `GLMapView`
@property (readonly) CLLocation *_Nullable lastLocation;

/// Defines if user location is displayed or not. If `YES`, user location is displayed.
@property (assign, nonatomic) BOOL showUserLocation;

/**
 Sets alternative user location images.
 
 @param locationImage new user location image. If `nil`, old image is left unchanged.
 @param movementImage new user movement image. If `nil`, old image is left unchanged.
 */
- (void)setUserLocationImage:(UIImage *_Nullable)locationImage movementImage:(UIImage *_Nullable)movementImage;

#pragma mark - Style

/**
 Loads map style.
 
 By default GLMapView tries to load `[[NSBundle mainBundle] pathForResource:@"DefaultStyle" ofType:@"bundle"];`
 
 @param styleBundle Bundle object with Style.mapcss and images
 @return Returns `YES` if style is loaded without errors
 */
-(BOOL) loadStyleFromBundle:(NSBundle *)styleBundle;

/**
 Allows to modify way framework loads map resources. 
 
 Usually it looks into map style bundle contents, but for some cases it's useful to have all resoureces merged together into one file or even generated programmatically
 
 @param resourceBlock Block that returns style data
 @return YES if style is loaded without errors
 */
-(BOOL) loadStyleWithBlock:(GLMapResourceBlock)resourceBlock;

/**
 Sets scale of font loaded frrom styleBundle. By default fontScale is 1.0
 */
-(void) setFontScale:(float) fontScale;

/**
 Custom raster tile sources. By default mapView have no raster layers.
 
 @param sources Array of raster map sources
 */
-(void) setRasterSources:(NSArray<GLMapRasterTileSource *> *_Nullable)sources;

/**
  @return Raster tile sources array
 */
-(NSArray<GLMapRasterTileSource *> *_Nullable) rasterSources;

/**
 Returns set of names of map options defined in map style.
 
 For example in selector
 
     node|z17-[_optOn=Bar][amenity=bar],
 
 part `[_optOn=Bar]` requires option `Bar` enabled. By default all options is enabled. But you can manage enabled options via `setEnabledStyleOptions:`
 @see `setEnabledStyleOptions:`
 */
- (NSSet<NSString *> *_Nullable) getStyleOptions;

/**
 Sets list of enabled style options
 
 @param opts Set of enabled options
 */
- (void) setEnabledStyleOptions:(NSSet<NSString *> *)opts;

/**
 Forces reloading of all tiles
 */
-(void) reloadTiles;

/**
 Removes all tiles. Useful to reduce memory usage in background mode
 */
-(void) removeAllTiles;

/**
 Adds new animation block that is called each frame unitl `NO` is returned.
 
 @param animationBlock Animation block that should be started.
 */
-(void) startAnimationBlock:(GLMapAnimationBlock)animationBlock;

#pragma mark - Configuring the Map Position

/**
 Origin point of the map coordinate system (X, Y). 
 
 Changing the values in this property between 0 and 1 in relative coordinates describes the point of GLMapView which is considered as a center point for `mapCenter` and `setMapCenter:animated:`.
 
 @see `mapCenter`, `setMapCenter:`
 */
@property (assign) CGPoint mapOrigin;

/**
 Coordinates of the origin point of the map.
 
 @see `mapOrigin`
 */
-(GLMapPoint) mapCenter;

/**
 Moves the map view to the given point.
 
 @param center New map center position.
 */
-(void) setMapCenter:(GLMapPoint)center;

/**
 Moves the map view to the given point and zoom.
 
 @param center New map center position.
 @param zoom New map zoom.
 */
-(void) setMapCenter:(GLMapPoint)center zoom:(double)zoom;

/**
 Moves the map view to the given point using transition.
 
 @param center New map center position.
 @param transition Transition used during map center change.
 */
-(void) setMapCenter:(GLMapPoint)center transition:(GLMapTransitionFunction)transition;

/**
 Moves the map view to the given point and zoom using transition.
 
 @param center New map center position.
 @param zoom New map zoom.
 @param transition Transition used during map center change.
 */
-(void) setMapCenter:(GLMapPoint)center zoom:(double)zoom transition:(GLMapTransitionFunction)transition;

/**
 Moves to new center with animation optimized for long distances.
 
 @param geoPoint Target location.
 */
-(void) flyTo:(GLMapGeoPoint)geoPoint;

/**
 Moves to new center and zoom with animation optimized for long distances.
 
 @param geoPoint Target location.
 @param zoomLevel New map zoom level.
 */
-(void) flyTo:(GLMapGeoPoint)geoPoint zoomLevel:(CGFloat)zoomLevel;
/**
 Moves to new center and zoom with animation optimized for long distances.
 
 @param geoPoint Target location.
 @param zoomLevel New map zoom level.
 @param velocity Velocity of the movement. Units is screen width per second.
 */
-(void) flyTo:(GLMapGeoPoint)geoPoint zoomLevel:(CGFloat)zoomLevel velocity:(CGFloat)velocity;

/**
 Moves to new center and zoom with animation optimized for long distances.
 
 @param geoPoint Target location.
 @param zoomLevel New map zoom level.
 @param duration Desired duration of the movement.
 */
-(void) flyTo:(GLMapGeoPoint)geoPoint zoomLevel:(CGFloat)zoomLevel duration:(CGFloat)duration;


/// @return Returns `YES` if fly animation is in progress.
-(BOOL) flyToInProgress;

/**
 Moves map to new location.
 
 If flyTo animation is active and moveTo is called, it updates target point inside active animation.
 
 @param geoPoint New location.
 */
-(void) moveTo:(GLMapGeoPoint)geoPoint;

/**
 Moves map to new location and zoom level.
 
 If flyTo animation is active and moveTo is called, it updates target point inside active animation.
 
 @param geoPoint New location.
 @param zoomLevel New zoom level.
 */
-(void) moveTo:(GLMapGeoPoint)geoPoint zoomLevel:(CGFloat)zoomLevel;

/**
 Moves map to the new location using transition.

 If flyTo animation is active and moveTo is called, it updates target point inside active animation.
 
 @param geoPoint New location.
 @param transition Transition used during map center change.
 */
-(void) moveTo:(GLMapGeoPoint)geoPoint transition:(GLMapTransitionFunction)transition;

/**
 Moves map to the new location and zoom using transition.
 
 If flyTo animation is active and moveTo is called, it updates target point inside active animation.
 
 @param geoPoint New location.
 @param zoomLevel New zoom level.
 @param transition Transition used during map center change.
 */
-(void) moveTo:(GLMapGeoPoint)geoPoint zoomLevel:(CGFloat)zoomLevel transition:(GLMapTransitionFunction)transition;

/**
 Changes zoom level for a given number of levels.
 
 @param diff Difference between current and new zoom level.
 @param center Map center used during animation
 */
-(void) changeZoomLevel:(int)diff center:(GLMapPoint)center;

/**
 Defines the scrolling speed at the end of map scrolling movement.
 
 @param velocity Initial velocity of deceleration
 */
-(void) startDecelerate:(GLMapPoint) velocity;

/**
 Calculates map zoom to fit bbox in view with given size.
 
 @warning If bbox size is 0, returns +inf.
 */
-(double) mapZoomForBBox:(GLMapBBox)bbox viewSize:(CGSize)size;

/**
 Defines the current zoom of the map view.
 
 @return Current zoom of the map.
 
 @see `-setMapZoom:`
 */
-(double) mapZoom;

/// Maximum possible value of `mapZoom`. Map won't zoom closer.
@property (assign) double maxZoom;

/**
 Sets the new zoom for the map view.
 
 @param mapZoom New map zoom
 
 @see `mapZoom`
 */
-(void) setMapZoom:(double)mapZoom;

/**
 Sets the new zoom for the map view using center point.
 
 @param mapZoom New map zoom
 @param center Center point for zooming transition
 
 @see `mapZoom`
 */
-(void) setMapZoom:(double)mapZoom center:(GLMapPoint)center;

/**
 Sets the new zoom for the map view with transition.
 
 @param mapZoom New map zoom
 @param transition Transition used during map zoom change.
 
 @see `mapZoom`
 */
-(void) setMapZoom:(double)mapZoom transition:(GLMapTransitionFunction)transition;

/**
 Sets the new zoom for the map view with transition.
 
 @param mapZoom New map zoom
 @param center Center point for zooming transition
 @param transition Transition used during map zoom change.
 
 @see `mapZoom`
 */
-(void) setMapZoom:(double)mapZoom center:(GLMapPoint)center transition:(GLMapTransitionFunction)transition;

/**
 Returns the map rotation angle.
 
 @return Angle in degrees from 0° to 360°
 
 @see `-setMapAngle:`
 */
-(double) mapAngle;

/**
 Rotates map with angle.
 
 @param angle Angle in degrees from 0° to 360°
 
 @see `mapAngle`
 */
-(void) setMapAngle:(double)angle;
/**
 Rotates map with angle.
 
 @param angle Angle in degrees from 0° to 360°
 @param center Rotation center
 
 @see `mapAngle`
 */
-(void) setMapAngle:(double)angle center:(GLMapPoint)center;
/**
 Rotates map with angle.
 
 @param angle Angle in degrees from 0° to 360°
 @param transition Transition used during map rotate
 
 @see `mapAngle`
 */
-(void) setMapAngle:(double)angle transition:(GLMapTransitionFunction)transition;

/**
 Rotates map with angle.
 
 @param angle Angle in degrees from 0° to 360°
 @param center Rotation center
 @param transition Transition used during map rotate
 
 @see `mapAngle`
 */
-(void) setMapAngle:(double)angle center:(GLMapPoint)center transition:(GLMapTransitionFunction)transition;

#pragma mark - Converting map coordinates

/**
 Converts a point on the screen to an internal map coordinate.
 
 @param displayPoint The point you want to convert.
 @return The internal map coordinate of the specified point.
 */
-(GLMapPoint) makeMapPointFromDisplayPoint:(CGPoint)displayPoint;

/**
 Converts a distance between two points on the screen to an internal map coordinate at current map zoom.
 
 @param displayDelta The delta you want to convert.
 @return The delta in internal map coordinates.
 */
-(GLMapPoint) makeMapPointFromDisplayDelta:(CGPoint)displayDelta;

/**
 Converts a distance between two points on the screen to an internal map coordinate.
 
 @param displayDelta The delta you want to convert.
 @param mapZoom Zoom of map
 @return The delta in internal map coordinates.
 */
-(GLMapPoint) makeMapPointFromDisplayDelta:(CGPoint)displayDelta andMapZoom:(double)mapZoom;

/**
 Converts a geo point to the point on the screen.
 
 @param geoPoint The geo point you want to convert.
 @return Coresponding point on the screen.
 */
-(CGPoint) makeDisplayPointFromGeoPoint:(GLMapGeoPoint)geoPoint;

/**
 Converts a point on the screen to the geo point.
 
 @param displayPoint Point on screen you want to convert.
 @return Coresponding geo point.
 */
-(GLMapGeoPoint) makeGeoPointFromDisplayPoint:(CGPoint)displayPoint;

/**
 Converts an internal map coordinate to the point on the screen.
 
 @param mapPoint The map point you want to convert.
 @return Coresponding point on the screen.
 */
-(CGPoint) makeDisplayPointFromMapPoint:(GLMapPoint)mapPoint;

/**
 Converts geo coordinates to the internal point.
 
 @param geoPoint Geo point you want to convert.
 @return Corresponding point in map coordinates.
 */
+(GLMapPoint) makeMapPointFromGeoPoint:(GLMapGeoPoint)geoPoint;

/**
 Converts an internal point to geo coordinates.
 
 @param mapPoint Point in map coordinates.
 @return Corresponding point in geo coordinates.
 */
+(GLMapGeoPoint) makeGeoPointFromMapPoint:(GLMapPoint)mapPoint;

/**
 Converts distance in meters to pixels on the screen
 
 @param meters Distance in meters
 @return Distance in pixels
 */
-(double) makePixelsFromMeters:(double)meters;

/**
 Converts distance in pixels on the screen to meters
 
 @param pixels Distance in pixels
 @return Distance in meters
 */
-(double) makeMetersFromPixels:(double)pixels;

/**
 Converts distance in meters to map coordinates
 
 @param meters Distance in meters
 @return Distance in map coordinates
 */
-(double) makeInternalFromMeters:(double)meters;

/**
 Converts distance in map coordinates to meters
 
 @param internal Distance in map coordinates
 @return Distance in meters
 */
-(double) makeMetersFromInternal:(double)internal;

/**
 Converts distance in pixels to map coordinates
 
 @param pixels Distance in pixels
 @return Distance in map coordinates
 */
-(double) makeInternalFromPixels:(double)pixels;

/**
 Converts distance in map coordinates to pixels
 
 @param internal Distance in map coordinates
 @return Distance in pixels
 */
-(double) makePixelsFromInternal:(double)internal;

#pragma mark - Single image

/**
 Adds the `UIImage` to the map view.
 
 @param image The image to display
 @return Object used to refer image inside `GLMapView`.
 @see `-removeImage:`
 */
-(GLMapImage *_Nullable) displayImage:(UIImage *)image;

/**
 Adds the `UIImage` to the map view.
 
 @param image The image to display
 @param drawOrder Object priority among other objects. Object with biggest draw order displayed on top.
 
 @return Object used to refer image inside `GLMapView`.
 @see `-removeImage:`
 */
-(GLMapImage *_Nullable) displayImage:(UIImage *)image drawOrder:(int)drawOrder;

/**
 Adds text to the map view. Could be used to display icon with text.
 
 @param text The text to display
 @param style Style of the text object
 @param drawOrder Object priority among other objects. Object with biggest draw order displayed on top.
 
 @return Object used to refer resource inside `GLMapView`.
 @see `-removeImage:`
 */
-(GLMapImage *_Nullable) displayText:(NSString *)text withStyle:(GLMapVectorStyle *)style drawOrder:(int)drawOrder completion:(dispatch_block_t)completion;

/**
 Removes `GLMapImage` object from the map view.
 
 @param image Image to remove
 @see `-displayImage:`
 */
- (void) removeImage:(GLMapImage *)image;

#pragma mark - Image Group

/**
 Creates a group for storing array of `UIImage`.
 
 @return New image group object.
 @see `-removeImageGroup:`
 */
-(GLMapImageGroup *_Nullable) createImageGroup;

/**
 Creates a group for storing array of `UIImage`.
 
 @param drawOrder Object priority among other objects. Object with biggest draw order displayed on top.
 @return The image group object.
 @see `-removeImageGroup:`
 */
-(GLMapImageGroup *_Nullable) createImageGroupWithDrawOrder:(int)drawOrder;

/**
 Removes a group of images from map.
 
 @param imageGroup Image group to be removed
 @see `-createImageGroup`
 */
-(void) removeImageGroup:(GLMapImageGroup *)imageGroup;

#pragma mark - Styles

/**
 Adds style for map.
 
 @param style Style to be added
 */
-(void) addStyle:(GLMapVectorCascadeStyle *)style;

/**
 Removes style from map.
 
 @param style Style to be removed
 */
-(void) removeStyle:(GLMapVectorCascadeStyle *)style;

#pragma mark - Vector Objects

/**
 Returns object near some point on map
 
 @param point Point on map
 @param maxDistance Distance in points
 @param categories Possible categories
 @return Vector object on map
 */
-(GLMapVectorObject *_Nullable) mapObjectNearPoint:(GLMapPoint)point maxDistance:(double)maxDistance categories:(GLSearchCategories *)categories;

/**
 Computes draw options from vector object. Sometimes we can't detect object category and object name or icon name could be used as object description.
 
 @param object Object on map
 @return Detected image name and object name
 */
-(GLMapVectorObjectDrawOptions *_Nullable) drawOptionsForVectorObject:(GLMapVectorObject *)object;

/** 
 Adds vector object on map.

 @param object Vector object to add.
 @param style Style used for that vector object.
 @param onReadyToDraw Block called when object is added on map.
 */
-(void) addVectorObject:(GLMapVectorObject *)object withStyle:(GLMapVectorCascadeStyle *_Nullable)style onReadyToDraw:(dispatch_block_t _Nullable)onReadyToDraw;

/**
 Adds vector objects on map.
 
 @param objects Vector objects array to add.
 @param style Style used for that vector object.
 */
-(void) addVectorObjects:(NSArray<GLMapVectorObject *> *)objects withStyle:(GLMapVectorCascadeStyle *_Nullable)style;

/**
 Removes vector object from map.
 
 @param object Object to be removed.
 */
-(void) removeVectorObject:(GLMapVectorObject *)object;

/**
 Removes vector objects from map.
 
 @param objects Objects to be removed.
 */
-(void) removeVectorObjects:(NSArray<GLMapVectorObject *> *)objects;

/**
 Creates layer with provided array of markers and display it on map with provided style set.
 
 @return Layer that can be used to remove markers or replaced with other
 */
-(GLMapMarkerLayer *) displayMarkers:(NSArray<id> *)markers withStyles:(GLMapMarkerStyleCollection *)styles;

/**
 Adds the `GLMapMarkerLayer` to the map view.
 
 @param layer Layer to display
 */
-(void) displayMarkerLayer:(GLMapMarkerLayer *)layer completion:(dispatch_block_t _Nullable)completion;

/**
 Removes previsously added `GLMapMarkerLayer` from the map view.
 
 @param layer Layer to be removed.
 */
-(void) removeMarkerLayer:(GLMapMarkerLayer *)layer;

/**
 Displays track data on map view.
 
 @param trackData Points of track.
 @return New track object.
 */
-(GLMapTrack *) displayTrackData:(GLMapTrackData *)trackData;

/**
 Displays track data on the map view.
 
 @param trackData Points of track.
 @param drawOrder Object priority among other objects. Object with biggest draw order displayed on top.

 @return New track object
 */
-(GLMapTrack *_Nullable) displayTrackData:(GLMapTrackData *)trackData drawOrder:(int)drawOrder;

/**
 Removes track from the map view.
 
 @param track The track to be removed
 */
-(void) removeTrack:(GLMapTrack *)track;

/**
 Removes all previsously added tracks from the map view.
 */
-(void) removeAllTracks;

/**
 Map locale settings
 
 Set of supported locales is returned by `[GLMapLocaleSettings supportedLocales]`
 
 E.g. to set map languages priority to English, Deutsch, native
 
     [_mapView setLocaleSettings:[[GLMapLocaleSettings alloc] initWithLocalesOrder:@[@"en", @"de", @"native"]]];
     // Then reload tiles to apply new locale settings
     [_mapView reloadTiles];
 
 Default value is supported languages from `[NSLocale preferredLanguages]`
 */
@property (strong) GLMapLocaleSettings *localeSettings;

@end

NS_ASSUME_NONNULL_END
