//
//  GLSearchOffline.h
//  GLMap
//
//  Created by Arkadi Tolkun on 9/7/15.
//  Copyright (c) 2015 Evgen Bodunov. All rights reserved.
//

#ifndef GLMap_GLSearchOffline_h
#define GLMap_GLSearchOffline_h

@class GLSearchCategory;
@class GLSearchCategories;
@class GLMapLocaleSettings;
@class GLMapVectorObject;

/**
 `GLMapSearchCompletionBlock` called when search task is finished. If results is nil - task is cancelled.
 
 @warning If custom results is also added, results will contain `GLMapVectorObject`s and objects of user type.
 */
typedef void(^GLMapSearchCompletionBlock)(NSArray<GLMapVectorObject *> * _Nonnull results);

/**
 `GLMapSearchInfoBlock` called to fetch information that used to sort custom search results.
 */
typedef void(^GLMapSearchInfoBlock)(id _Nonnull result, GLMapPoint * _Nonnull location, GLSearchCategory * _Nullable * _Nonnull category);

/**
 `GLSearchOffline` class contains a set of parameters that defines search in offline maps
 */
@interface GLSearchOffline : NSObject
{
}

/**
 Adds name filter (name of object contains word)
 
 @param word Word query
 */
-(void) addNameFilter:(NSString *_Nonnull)word;

/**
 Adds name filter (name of object contains ANY of word in array). If any word is found in name - we'll use this result.
 
 @param words Array of words
 */
-(void) addNamesFilter:(NSArray<NSString *> *_Nonnull)words;

/**
 Adds set of tile hashes to use for search (child tiles will be skipped)
 
 @param tiles Set of tile hashes
 */
-(void) setTiles:(NSSet<NSNumber *> *_Nonnull)tiles;

/**
 Sets categories that used to sort results by importance. Some categories contain score bonus. It's used to put most important results first in list.
 
 @param categories Categories container
 */
-(void) setCategories:(GLSearchCategories *_Nonnull) categories;

/**
 Sets locale settings that used to sort results by importance. Results in user language displayed on top.
 
 @param localeSettings Language priority settings.
 */
-(void) setLocaleSetgings:(GLMapLocaleSettings *_Nonnull) localeSettings;

/**
 Adds category filter. Only results with given category will be displayed.
 
 @param category Category object
 */
-(void) addCategoryFilter:(GLSearchCategory *_Nonnull)category;

/**
 Adds custom filter by tag (value of tag is ecxactly matches to given value)
 
 @param tag Tag
 @param value Value
 */
-(void) addTagFilter:(NSString * _Nonnull)tag value:(NSString * _Nonnull)value;

/**
 Adds custom filter by tag (value of tag ecactly matches to one of given values)
 
 @param tag Tag. e.g. "amenity"
 @param values Array of values. e.g. ["bar", "pub"]
 */
-(void) addTagFilter:(NSString * _Nonnull)tag values:(NSArray<NSString *> * _Nonnull)values;

/**
 Sets maximum number of results to fetch from map
 
 @param limit Results limit
 */
-(void) setLimit:(uint32_t) limit;

/**
 Sets bounding box where search will be performed
 
 @param bbox Search bounding box.
 */
-(void) setBBox:(GLMapBBox)bbox;

/**
 Sets center of search. Distance from this center will define importance of object. Usually center is user location or center of the screen.
 
 @param center Center point.
 */
-(void) setCenter:(GLMapPoint)center;

/**
 Adds custom search results. Information returned by `infoBlock` will be used to sort this results.
 
 @param results Array of user objects.
 @param infoBlock Block called for each custom result to fill category and location.
 */
-(void) addResults:(NSArray<id> * _Nonnull)results infoBlock:(GLMapSearchInfoBlock _Nonnull)infoBlock;

/**
 Starts search. 
 
 @param completionBlock Block will be called when search is finished.
 */
-(void) startWithCompletionBlock:(GLMapSearchCompletionBlock _Nonnull)completionBlock;

/**
 Cancels search operation.
 */
-(void) cancel;

@end

#endif
