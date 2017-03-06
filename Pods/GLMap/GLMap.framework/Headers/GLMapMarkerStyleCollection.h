//
//  GLMapMarkerStyleCollection.h
//  GLMap
//
//  Created by Arkadiy Tolkun on 1/19/16.
//  Copyright © 2016 Evgen Bodunov. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GLMapVectorStyle.h"

/// `GLMapMarkerData` is type used to reference an internal object.
typedef void* GLMapMarkerData;

#ifdef __cplusplus
extern "C" {
#endif
/**
 Changes map marker location
 
 @param data Marker object to be changed
 @param point New marker location
 */
void GLMapMarkerSetLocation(GLMapMarkerData _Nonnull data, GLMapPoint point);

/**
 Changes map marker style
 
 @param data Marker object to be changed
 @param style Style identifier
 */
void GLMapMarkerSetStyle(GLMapMarkerData _Nonnull data, unsigned int style);

/**
 Sets text for map marker.
 
 @param data Marker object to be changed
 @param text Text for marker object
 @param offset offset on screen in points
 @param style Text style
 */
void GLMapMarkerSetText(GLMapMarkerData _Nonnull data, NSString *_Nonnull text, CGPoint offset, GLMapVectorStyle * _Nonnull style);

#ifdef __cplusplus
}
#endif
    
/**
 `GLMapMarkerDataFillBlock` is called for each marker to fill needed data
 
 @see `GLMapMarkerSetLocation`
 @see `GLMapMarkerSetStyle`
 @see `GLMapMarkerSetText`
 */
typedef void (^GLMapMarkerDataFillBlock)(NSObject * _Nonnull marker, GLMapMarkerData _Nonnull data);

/**
 `GLMapMarkerUnionBlock` called when marker layer needs style for union of `count` markers
 */
typedef void (^GLMapMarkerUnionFillBlock)(uint32_t count, GLMapMarkerData _Nonnull data);

/**
 `GLMapMarkerStyleCollection` class holds collection of styles, used to draw marker layer.
 */
@interface GLMapMarkerStyleCollection : NSObject

/// @return Returns new instance of `GLMapMarkerStyleCollection`
-(instancetype _Nonnull) init;

/**
 Adds block used to fill data for markers. `GLMapMarkerDataFillBlock` is called for each marker, is should set marker information into `GLMapMarkerData` variable using `GLMapMarkerSetLocation`, `GLMapMarkerSetStyle`, `GLMapMarkerSetText` functions.
 
 @param block A marker data fill block
 */
-(void) setMarkerDataFillBlock:(GLMapMarkerDataFillBlock _Nullable)block;

/**
 `GLMapMarkerUnionBlock` called when marker layer needs style for union of `count` markers. It should return number
 
 @param block A cluster data fill block
 */
-(void) setMarkerUnionFillBlock:(GLMapMarkerUnionFillBlock _Nullable)block;

/**
 Adds new marker image to collection
 
 @param image Image that will have default offset (center of image)
 @retun index in collection for this style
 */
-(uint32_t) addMarkerImage:(UIImage *_Nonnull)image;

/**
 Adds new marker images to collection
 
 @param images array of images that will have default offset (center of image)
 @retun index in collection for this style
 */
-(uint32_t) addMarkerImages:(NSArray<UIImage *> *_Nonnull)images;

/**
 Adds new marker images with offsets to collection
 
 @param images array of images
 @param offsets offsets of images
 @retun index in collection for this style
 */
-(uint32_t) addMarkerImages:(NSArray<UIImage *> *_Nonnull)images offsets:(NSArray<NSValue *> *_Nullable)offsets;

@end
