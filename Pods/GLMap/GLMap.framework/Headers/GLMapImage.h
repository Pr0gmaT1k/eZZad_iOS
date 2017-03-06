//
//  GLMapImage.h
//  GLMap
//
//  Created by Evgen Bodunov on 3/16/14.
//  Copyright (c) 2014 Evgen Bodunov. All rights reserved.
//

#import <Foundation/Foundation.h>

@class GLMapVectorStyle;

/**
 `GLMapImage` is a bridge class, to work with GLMap internal representation of image on map. Typically is used for single image object. Check `GLMapImageGroup` for big groups of images. Or `GLMapMarkerLayer` to display map markers with clustering.
 
 @see `[GLMapView displayImage:]`
 @see `GLMapMarkerLayer`
 @see `GLMapImageGroup`
 */
@interface GLMapImage : NSObject

#pragma mark - Properties

/**
 When set to `YES` image rotates with map. Default value is 'NO'
 */
@property (assign) BOOL rotatesWithMap;
/**
 A Boolean value that determines whether the image is hidden. Default value is 'NO'
 */
@property (assign) BOOL hidden;
/**
 A position that sets image position in map internal coordinates
 */
@property (assign) GLMapPoint position;
/**
 Image offset from `position` point.
 
 When offset is (0,0), bottom left corner of image is displayed at `position`
 */
@property (assign) CGPoint offset;
/**
 A float variable that defines image angle
 */
@property (assign) float angle;
/**
 A size of image in pixels
 */
@property (readonly) CGSize size;

#pragma mark - Methods

/**
 Sets image to be displayed using `GLMapImage`
 
 @param image New image to display on map
 @param completion A block called when image is replaced.
 */
-(void) setImage:(UIImage *)image completion:(dispatch_block_t)completion;

/**
 Sets text associated with the image
 
 @param text New text
 @param style A style object used for text
 @param completion A block called when text is replaced.
 
 @see `GLMapVectorStyle`
 */
-(void) setText:(NSString *)text withStyle:(GLMapVectorStyle *)style completion:(dispatch_block_t)completion;

@end
