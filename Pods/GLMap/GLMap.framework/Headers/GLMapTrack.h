//
//  GLMapTrack.h
//  GLMap
//
//  Created by Arkadiy Tolkun on 1/28/16.
//  Copyright © 2016 Evgen Bodunov. All rights reserved.
//

#import <Foundation/Foundation.h>

@class GLMapTrackData;

/**
 `GLMapTrack` is container class for track objects. Main difference from line - is data generalization function used for tracks to remove data points redundant for current zoom level.
 */
@interface GLMapTrack : NSObject

/**
 Sets track width
 
 @param width New track width in points
 */
-(void) setWidth:(CGFloat)width;

/**
 Sets track data
 
 @param data New track data
 */
-(void) setTrackData:(GLMapTrackData *_Nullable)data;

/**
 @return track draw order set during initialization
 */
-(uint32_t) drawOrder;

/**
 Finds nearest point of track, to given point. It's used, for example, to find nearest point of track to user tap.
 
 @param nearestPoint Parameter used to store return variable
 @param point Point on map
 @param distance Max distance from track allowed
 
 @return YES if point found, otherwise NO.
 */
-(BOOL) findNearestPoint:(GLMapPoint *_Nonnull)nearestPoint toPoint:(GLMapPoint)point maxDistance:(CGFloat)distance;

@end
