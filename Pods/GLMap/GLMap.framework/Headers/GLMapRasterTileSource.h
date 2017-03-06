//
//  GLRasterTileSource.h
//  GLMap
//
//  Created by Arkadiy Tolkun on 11/10/15.
//  Copyright © 2015 Evgen Bodunov. All rights reserved.
//

#import "GLMapViewTypes.h"

/**
 @abstract GLMapRasterTileSource is used to setup custom raster tile source.
 */
@interface GLMapRasterTileSource : NSObject

/**
 @abstract Initialize tile source. If cachePath==nil no caching will happens.
 */
-(instancetype _Nullable) initWithCachePath:(NSString *_Nullable) cachePath;

/**
 @abstract This method is used to get url of tile. Default implementation reuturns nil.
 */
-(NSURL *_Nullable) urlForTilePos:(GLMapTilePos)pos;

/**
 @abstract This method is used to get image of tile. Default implementation reuturns nil.
 */
-(UIImage *_Nullable) imageForTilePos:(GLMapTilePos)pos expired:(BOOL *_Nonnull)expired;

/**
 @abstract This method is used to get image of tile. Default implementation reuturns nil.
 */
-(void) saveTileData:(NSData * _Nonnull)data forTilePos:(GLMapTilePos)pos;

/**
 @abstract Cached tile will be refreshed if it will stay in cache more than given time.
 @discussion By default tileRefreshTimeInterval = -1. If tileRefreshTimeInterval < 0  no tile refreshing will be triggered.
 */
@property (assign) int64_t tileRefreshTimeInterval;

/**
 @abstract Defines valid zooms for tile source. Default is 0xFFFFFFFF.
 */
@property (assign) uint32_t validZoomMask;

/**
 @abstract Size of tile in points. Could be used to magnify raster tiles. Default is 256.
 */
@property (assign) uint32_t tileSize;

/**
 @abstract This property is used to set attribution text for map source. Default is @"© OpenStreetMap"
 */
@property (strong) NSString *_Nullable attributionText;

/**
 @abstract This property is used to get size of cache file
 */
@property (readonly) uint64_t cacheSize;

/**
 @abastact Remove all cached data
 */
-(void) dropCache;

@end
