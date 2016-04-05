/**
 * Ti.Urbanairship Module
 * Copyright (c) 2010-2013 by Appcelerator, Inc. All Rights Reserved.
 * Please see the LICENSE included with this distribution for details.
 */

#import "TiModule.h"

#import "UAirship.h"
#import "UAConfig.h"
#import "UAPush.h"
#import "UAPushNotificationHandler.h"

@interface TiUrbanairshipModule : TiModule <UAPushNotificationDelegate, UARegistrationDelegate>

@property(readonly,nonatomic) BOOL notificationsEnabled;
@property(readwrite,nonatomic) BOOL autoResetBadge;
@property(nonatomic,readwrite,getter=isInitialized) BOOL initialized;

@property(nonatomic,readonly) NSString *EVENT_URBAN_AIRSHIP_CALLBACK;
@property(nonatomic,readonly) NSString *EVENT_URBAN_AIRSHIP_SUCCESS;
@property(nonatomic,readonly) NSString *EVENT_URBAN_AIRSHIP_ERROR;

@end
