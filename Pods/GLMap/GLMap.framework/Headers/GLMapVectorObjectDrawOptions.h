//
//  GLMapVectorObjectDrawOptions.h
//  GLMap
//
//  Created by Arkadiy Tolkun on 8/10/16.
//  Copyright © 2016 Evgen Bodunov. All rights reserved.
//

#import <Foundation/Foundation.h>

/// `GLMapVectorObjectDrawOptions` used to detect matched icon name and text of an object on map
@interface GLMapVectorObjectDrawOptions : NSObject

/// Text displayed for vector object on map
@property (strong) NSString *text;

/// Icon used by vector object on map
@property (strong) NSString *iconName;

@end
