//
//  GLMapVectorCascadeStyle.h
//  GLMap
//
//  Created by Evgen Bodunov on 1/10/17.
//  Copyright © 2017 Evgen Bodunov. All rights reserved.
//

#import <Foundation/Foundation.h>

@class GLMapView;

/** `GLMapVectorCascadeStyle` is used to define appearance of `GLMapVectorObject`. One style could be used with many `GLMapVectorObjects`.
 
 Style used to render map stored inside DefaultStyle.bundle/Style.mapcss. Detailed MapCSS specification is located at: http://www.mapcss.org
 
 MapCSS examples:
 
 Any point with tag natural=peak, should be displayed on zoom level 11+ with trangle icon tinted with brown color.
 ```
 node|z11-[natural=peak] {
	icon-image:"triangle.svgpb";
	icon-tint:brown;
 }
 ```
 Any point with tag natural=peak, should display it's localized name on zoom level 13+.
 ```
 node|z13-[natural=peak] {
 text: eval( locTag('name') );
	text-color:brown;
	font-size:12;
 }
 ```
*/

@interface GLMapVectorCascadeStyle : NSObject

NS_ASSUME_NONNULL_BEGIN

/**
 Creates cascade style object.
 
 `GLMapVectorCascadeStyle *style = [GLMapVectorCascadeStyle createStyle(@"area{fill-color:#10106050;}"];`
 
 @param style NSString with style rules in MapCSS format
 
 @return New `GLMapVectorCascadeStyle` object
 */
+(nullable instancetype) createStyle:(NSString *_Nonnull)style;

/**
 Creates cascade style object.
 
 @param style NSString with style rules in MapCSS format
 @param error Error is filled if object cannot be created
 
 @return New `GLMapVectorCascadeStyle` object
 */
+(nullable instancetype) createStyle:(NSString *_Nonnull)style error:(NSError **)error;

NS_ASSUME_NONNULL_END

@end
