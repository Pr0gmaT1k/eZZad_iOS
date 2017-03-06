//
//  GLSearchCategory.h
//  GLMap
//
//  Created by Arkadiy Tolkun on 12/7/16.
//  Copyright © 2016 Evgen Bodunov. All rights reserved.
//

#import <Foundation/Foundation.h>

@class GLMapLocaleSettings;
/**
 `GLSearchCategory` class holds infromation that can be displayed to user.
 */
@interface GLSearchCategory : NSObject

/**
 Returns name of the category according language priority settings. It checks for aviability of translated name from first language in priority list to the last one until first translated name is found.
 
 @param settings language order settings
 
 @return localised name of the category.
 */
- (NSString *_Nullable) localizedName:(GLMapLocaleSettings *_Nonnull)settings;

/**
 Returns name of the category according language priority settings. It checks for aviability of translated name from first language in priority list to the last one until first translated name is found. If category was found by search request matched part of text will be highlighted by given color.
 
 @param localeSettings language order settings
 @param color default color of text
 @param highlightColor colof of highlighted text
 
 @return localised name of the category.
 */
- (NSMutableAttributedString *_Nullable) attributedNameWithColor:(UIColor *_Nonnull)color andHighlightColor:(UIColor *_Nonnull)highlightColor localeSettings:(GLMapLocaleSettings *_Nonnull)localeSettings;

/**
 Icon name of the category.
 */
@property (readonly) NSString *_Nonnull iconName;

/**
 Child categories of the category.
 */
@property (readonly) NSArray<GLSearchCategory *> *_Nonnull childs;

@end
