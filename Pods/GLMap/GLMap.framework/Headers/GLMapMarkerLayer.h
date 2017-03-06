//
//  GLMapMarkerLayer.h
//  GLMap
//
//  Created by Arkadiy Tolkun on 1/15/16.
//  Copyright © 2016 Evgen Bodunov. All rights reserved.
//

#import <Foundation/Foundation.h>

@class GLMapView;
@class GLMapMarkerStyleCollection;

/**
 `GLMapMarkerLayer` displays big number of markers with given style. It supports marker clustering.
 */
@interface GLMapMarkerLayer : NSObject

NS_ASSUME_NONNULL_BEGIN

/**
 Initializes `GLMapMarkerLayer` with given markers and `style`
 
 @param markers Array of marker objects. Usually you set objects with data, that you need to display on map.
 @param styles A style collection object used to display markers.
 
 @return A new marker layer
 */
-(instancetype) initWithMarkers:(NSArray<id> *)markers andStyles:(GLMapMarkerStyleCollection *)styles;

/**
 Adds or removes markers on layer
 
 @param markersToAdd markers that should be added
 @param markersToRemove markers that should be removed (compared by pointer)
 @param markersToReload markers that should be reloaded
 @param animated if `YES` modification will be animated
 @param completion block that will be called when modification is finished
 */
-(void) add:(NSArray<id> *_Nullable)markersToAdd remove:(NSArray<id> *_Nullable)markersToRemove reload:(NSArray<id> *_Nullable)markersToReload animated:(BOOL)animated completion:(dispatch_block_t _Nullable)completion;

/**
 Changes style of marker layer
 
 @param style New style
 @param completion block that will be called when modification is finished
 */
-(void) changeStyle:(GLMapMarkerStyleCollection *)style completion:(dispatch_block_t _Nullable)completion;

/**
 Searchs nearest object or cluster of objects at given mapView
 
 @param mapView map view where layer is displayed
 @param point point where object(s) will be searched
 @param distanceInPoints maximum hit distance in points
 
 @return An array of objects that meets search criteria
 */
-(NSArray<id> * _Nullable) objectsAtMapView:(GLMapView *)mapView nearPoint:(GLMapPoint)point distance:(double)distanceInPoints;

/**
 If it's equal to `NO` marker clustering will be disabled. By default is `YES`
 */
@property (assign) BOOL clusteringEnabled;

/**
 Marker layer draw order could be changed by editing this variable. Object with smaller draw order displayed earlier. Draw order applied when object is added on the `GLMapView`. DrawOrder variable is also avaialble for `GLMapImage`, `GLMapImageGroup`, `GLMapTrack`.
 */
@property (assign) int drawOrder;

/**
 Animation duraration
 */
@property (assign) double animationDuration;

NS_ASSUME_NONNULL_END

@end
