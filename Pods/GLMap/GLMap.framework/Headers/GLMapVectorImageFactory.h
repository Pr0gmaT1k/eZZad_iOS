//
//  GLMapVectorImage.h
//  GLMap
//
//  Created by Evgen Bodunov on 12/16/16.
//  Copyright © 2016 Evgen Bodunov. All rights reserved.
//

#import <Foundation/Foundation.h>
/**
 `GLMapVectorImageFactory` used to render images from svgpb files. Image factory caches rendered images for future use. 
 
 SVGPB - is preprocessed small and fast SVG files. SVG tags saved into protocol buffer files to maximize parsing speed. Resulting files 5 times smaller and 10x times faster to parse.
 
 To create svgpb files from your svg images please use open source util from https://github.com/molind/svgpb
 */
@interface GLMapVectorImageFactory : NSObject

NS_ASSUME_NONNULL_BEGIN

/// Disables disk caching if set to `YES`. Default value is `NO`
@property (assign) BOOL disableCaching;

/// @return Returns singleton factory object
+(GLMapVectorImageFactory *) sharedFactory;

/// Removes all cached images from disk
-(void) clearCaches;

/**
 Renders `UIImage` from svgpb file.
 
 @param imagePath Path to the svgpb file
 
 @return Returns rendered image
 */
-(nullable UIImage *) imageFromSvgpb:(NSString *)imagePath;
/**
 Renders `UIImage` from svgpb file.
 
 @param imagePath Path to the svgpb file
 @param scale Scale applied during render. 1.0 - original image size.
 
 @return Returns rendered image
 */
-(nullable UIImage *) imageFromSvgpb:(NSString *)imagePath withScale:(double)scale;
/**
 Renders `UIImage` from svgpb file.
 
 @param imagePath Path to the svgpb file
 @param scale Scale applied during render. 1.0 - original image size.
 @param tintColor Tint color applied to the image. Use `0`, when no tint required.
 
 @return Returns rendered image
 */
-(nullable UIImage *) imageFromSvgpb:(NSString *)imagePath withScale:(double)scale andTintColor:(uint32_t)tintColor;
/**
 Renders `UIImage` from svgpb file.
 
 @param imagePath Path to the svgpb file
 @param size Target image size
 @param tintColor Tint color applied to the image. Use `0`, when no tint required.
 
 @return Returns rendered image
 */
-(nullable UIImage *) imageFromSvgpb:(NSString *)imagePath withSize:(CGSize)size andTintColor:(uint32_t)tintColor;
/**
 Renders `UIImage` from svgpb file.
 
 @param imagePath Path to the svgpb file
 @param size Target image size
 @param contentMode Image placement inside the canvas
 @param tintColor Tint color applied to the image. Use `0`, when no tint required.
 
 @return Returns rendered image
 */
-(nullable UIImage *) imageFromSvgpb:(NSString *)imagePath withSize:(CGSize)size contentMode:(UIViewContentMode)contentMode andTintColor:(uint32_t)tintColor;

NS_ASSUME_NONNULL_END

@end
