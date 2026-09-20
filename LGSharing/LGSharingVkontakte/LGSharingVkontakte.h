//
// LGSharingVkontakte.h
// LGSharing
//
// SPDX-License-Identifier: MIT
// Copyright (c) 2015 Grigorii Lutkov <grigorii@lutkov.dev>
//

#import <Foundation/Foundation.h>
#import "VKSdk.h"

@interface LGSharingVkontakte : NSObject

@property (assign, nonatomic) UINavigationController *navigationController;

+ (instancetype)sharedManagerWithAppId:(NSString *)appId navigationController:(UINavigationController *)navigationController;

- (void)postWithText:(NSString *)text
                link:(NSURL *)link
            animated:(BOOL)animated
presentCompletionHandler:(void(^)())presentCompletionHandler
   completionHandler:(void(^)(VKShareDialogControllerResult result))completionHandler
dismissCompletionHandler:(void(^)())dismissCompletionHandler;

+ (void)applicationOpenURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication;

#pragma mark -

/** Unavailable, use +sharedManagerWithAppId... instead */
+ (instancetype)alloc __attribute__((unavailable("use +sharedManagerWithAppId... instead")));
/** Unavailable, use +sharedManagerWithAppId... instead */
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable("use +sharedManagerWithAppId... instead")));
/** Unavailable, use +sharedManagerWithAppId... instead */
- (instancetype)init __attribute__((unavailable("use +sharedManagerWithAppId... instead")));
/** Unavailable, use +sharedManagerWithAppId... instead */
+ (instancetype)new __attribute__((unavailable("use +sharedManagerWithAppId... instead")));
/** Unavailable, use +sharedManagerWithAppId... instead */
- (id)copy __attribute__((unavailable("use +sharedManagerWithAppId... instead")));

@end
