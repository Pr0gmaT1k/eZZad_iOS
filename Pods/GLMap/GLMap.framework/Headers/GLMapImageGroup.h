//
//  GLMapImageGroup.h
//  GLMap
//
//  Created by Evgen Bodunov on 3/16/14.
//  Copyright (c) 2014 Evgen Bodunov. All rights reserved.
//

#import <Foundation/Foundation.h>

/// `GLMapImageGroupImageInfo` is a structure that should be returned by `GLMapImageGroupFillBlock` for every image in group.
typedef struct GLMapImageGroupImageInfo {
    /// image identifier, returned by `[GLMapImageGroup setImages:completion:]`
    int imageID;
    /// position of the image
    GLMapPoint pos;
}
/// :nodoc:
GLMapImageGroupImageInfo;

/**
 `GLMapImageGroupFillBlock` called for each object with `index` as input param. Block should create `GLMapImageGroupImageInfo` and fill `imageID` and `pos` fields, to set imageID and position for object at index `index`
 */
typedef GLMapImageGroupImageInfo (^GLMapImageGroupFillBlock)(size_t index);

/**
 `GLMapImageGroupIsUpdatingBlock` called when group updating starts or ends
 */
typedef void (^GLMapImageGroupIsUpdatingBlock)(BOOL isUpdating);

/**
 `GLMapImageGroup` is a bridge class, to work with GLMap internal representation of image group.
 
 Image groups used to display small set of images for the large number of locations. E.g. 1000 locations on map, but only with 10 different images.
 
 @warning When image group is displayed, don't edit it while it updates contents. Check status from `GLMapImageGroupIsUpdatingBlock`
 @see `[GLMapImageGroup setIsUpdatingBlock:]`
 */
@interface GLMapImageGroup : NSObject

#pragma mark - Properties

/**
 A boolean variable that indicates whether this image is displayed or not.
 */
@property (assign) bool hidden;

#pragma mark - Methods

/**
 Sets array of images to the image group

 When images passed to `GLMapImageGroup`, they are loaded into GPU and unique object id's from GPU is returned.
 
 @param images Array of `UIImage` objects
 @param completion A block called when image array is added into object.
 
 @return Array of NSNumber objects with imageID's
 */
-(NSArray<NSNumber *> *_Nonnull) setImages:(NSArray<UIImage *>* _Nonnull)images completion:(dispatch_block_t _Nullable)completion;

/**
 Sets offset for any of images in image group
 
 @param offset An offset
 @param imageID Image ID
 
 @warning This method should be called inside or after completion block of `[GLMapImageGroup setImages:completion:]`
 */
-(void) setImageOffset:(CGPoint)offset forImageWithID:(int) imageID;

/**
 Noties image group about changes
 
 Image group will call fillBlock, to get updated positions for all objects in group.
 */
-(void) setNeedsUpdate;

/**
 Sets number of objects displayed using image group. Object fill block will be called for every object.
 
 @param count count of objects
 */
-(void) setObjectCount:(size_t)count;

/**
 Sets a block called to determine images and locations of different objects on map.
 
 @param fillBlock A block called for each object with `index` as input param. Block should modify `imageID` and `pos`, to set imageID and position for object at index `index`
 
 @warning `fillBlock` is called from background thread. Add multithread syncronisation if needed.
 */
-(void) setObjectFillBlock:(GLMapImageGroupFillBlock _Nonnull)fillBlock;

/**
 Sets a block that called when group updating starts or ends.
 
 @param isUpdatingBlock block that notifies about image group update state
 */
-(void) setIsUpdatingBlock:(GLMapImageGroupIsUpdatingBlock _Nonnull)isUpdatingBlock;

@end
