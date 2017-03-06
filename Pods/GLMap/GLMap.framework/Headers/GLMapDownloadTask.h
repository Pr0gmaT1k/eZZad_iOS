//
//  GLMapDownloadTask.h
//  GLMap
//
//  Copyright (c) 2014 Evgen Bodunov. All rights reserved.
//

@class GLMapInfo;

/**
 `GLMapDownloadTask` is a class that downloads offline maps. It allows to cancel map download and check download error. 
 
 @see `[GLMapManager downloadMap:withCompletionBlock:]`
 */
@interface GLMapDownloadTask : NSObject

#pragma mark - Properties

/**
 `error` is nil if no error happens. Otherwise error contains information from component that failed. Error domain could be 'CURL', 'HTTP', 'XZ' or 'GLMap'. For more information check `GLMapError`
 
 @see `GLMapError`
 */
@property (readonly) NSError *_Nullable error;

/**
 `isCancelled` set to `YES` when task was cancelled.
 */
@property (readonly) BOOL isCancelled;

/**
 `GLMapInfo` for map being downloaded.
 */
@property (readonly) GLMapInfo *_Nonnull map;

#pragma mark - Methods

/**
 Cancels downloading task at any time
 */
-(void) cancel;

@end
