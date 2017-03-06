//
//  GLMapLocaleSettings.h
//  GLMap
//
//  Created by Arkadiy Tolkun on 6/3/16.
//  Copyright © 2016 Evgen Bodunov. All rights reserved.
//

#include <Foundation/Foundation.h>

/**
 `GLMapLocaleSettings` is used to set language order to all `GLMapView` objects.
 
 For each label on map framework checks translated names in order set by `-initWithLocalesOrder:`, if no translated label is available - native name is used.
 
 Following map languages is included in vector map data
 
 * native - native language in for country or region
 * en - English
 * de - German
 * es - Spanish
 * fr - French
 * it - Italian
 * ja - Japanese
 * nl - Dutch
 * ru - Russan
 * zh - Chinese
 * uk - Urkrainian
 * be - Belarusian
 
 Check [Multilingual names in OpenStreetMap](http://wiki.openstreetmap.org/wiki/Multilingual_names) for more information.
 
 */
@interface GLMapLocaleSettings : NSObject

#pragma mark - Static Methods

/**
 @return Settings object gets values from `+[NSLocale preferredLanguages]` to set order of locales
 */
+(GLMapLocaleSettings *_Nonnull) systemSettings;

/**
 Set of supported map languages
 
 @return Returns language codes supported by framework
 */
+(NSSet<NSString *> *_Nonnull) supportedLocales;

/**
 @return Returns `YES` if `mapLanguage` is among supported languages
 */
+(BOOL) isLocaleSupported:(NSString *_Nonnull)locale;

#pragma mark - Methods

/**
 Create instance of GLMapLocaleSettings with given order of locales
 
 @param localesOrder Ordered array of language codes
 @return New locale settings object
 */
-(instancetype _Nonnull) initWithLocalesOrder:(NSArray<NSString *> *_Nullable) localesOrder;

@end
