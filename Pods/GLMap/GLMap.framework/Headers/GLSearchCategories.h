//
//  GLSearchCategories.h
//  GLMap
//
//  Created by Arkadiy Tolkun on 3/10/16.
//  Copyright © 2016 Evgen Bodunov. All rights reserved.
//

#import <Foundation/Foundation.h>

@class GLMapLocaleSettings;
@class GLSearchCategory;

/**
 `GLSearchCategories` class holds a set of `GLSearchCategory` that will be used to sort search results by priority.
 */
@interface GLSearchCategories : NSObject

/**
 Loads categories from given file;
 */
-(nullable instancetype) initWithPath:(NSString * _Nonnull)path;

/**
 @return Returns top categories
 */
-(NSArray<GLSearchCategory *> * _Nonnull) topCategories;

/**
 Returns categories that starts with given words
 
 @param words Words array
 @param localeSettings Language priority settings
 @return Matched array of categories
 */
-(NSArray<GLSearchCategory *> * _Nonnull) categoriesStartedWith:(NSArray<NSString *> * _Nonnull)words localeSettings:(GLMapLocaleSettings * _Nonnull)localeSettings;

/**
 @return Returns category with given name.
 */
-(GLSearchCategory * _Nullable) findByName:(NSString * _Nonnull)name;

/**
 @return Returns category with given iconName.
 */
-(GLSearchCategory * _Nullable) findByIconName:(NSString * _Nonnull)iconName;

@end

