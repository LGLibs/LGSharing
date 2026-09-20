//
// LGSharingGooglePlus.h
// LGSharing
//
// SPDX-License-Identifier: MIT
// Copyright (c) 2015 Grigorii Lutkov <grigorii@lutkov.dev>
//

#import <Foundation/Foundation.h>

@interface LGSharingGooglePlus : NSObject

+ (instancetype)sharedManagerWithClientId:(NSString *)clientId deepLinkId:(NSString *)deepLinkId;

/** Do not forget about weak referens to self for completionHandler block */
- (void)postWithText:(NSString *)text
                link:(NSURL *)link
   completionHandler:(void(^)(NSError *error))completionHandler;

+ (void)applicationOpenURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation;

#pragma mark -

/** Unavailable, use +sharedManagerWithClientId... instead */
+ (instancetype)alloc __attribute__((unavailable("use +sharedManagerWithClientId... instead")));
/** Unavailable, use +sharedManagerWithClientId... instead */
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable("use +sharedManagerWithClientId... instead")));
/** Unavailable, use +sharedManagerWithClientId... instead */
- (instancetype)init __attribute__((unavailable("use +sharedManagerWithClientId... instead")));
/** Unavailable, use +sharedManagerWithClientId... instead */
+ (instancetype)new __attribute__((unavailable("use +sharedManagerWithClientId... instead")));
/** Unavailable, use +sharedManagerWithClientId... instead */
- (id)copy __attribute__((unavailable("use +sharedManagerWithClientId... instead")));

@end
