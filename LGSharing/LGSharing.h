//
// LGSharing.h
// LGSharing
//
// SPDX-License-Identifier: MIT
// Copyright (c) 2015 Grigorii Lutkov <grigorii@lutkov.dev>
//

#import <Foundation/Foundation.h>
#import "LGSharingVkontakte.h"
#import "LGSharingGooglePlus.h"

@import Social;
@import MessageUI;

@class LGSharingObject;

@interface LGSharing : NSObject

typedef enum
{
    LGSharingDestinationAll        = 0,
    LGSharingDestinationVkontakte  = 1 << 0,
    LGSharingDestinationFacebook   = 1 << 1,
    LGSharingDestinationTwitter    = 1 << 2,
    LGSharingDestinationGooglePlus = 1 << 3,
    LGSharingDestinationEmail      = 1 << 4,
    LGSharingDestinationSMS        = 1 << 5
}
LGSharingDestination;

+ (instancetype)sharedManagerWithNavigationController:(UINavigationController *)navigationController
                                              vkAppId:(NSString *)vkAppId
                                   googlePlusClientId:(NSString *)googlePlusClientId
                                 googlePlusDeepLinkId:(NSString *)googlePlusDeepLinkId;

#pragma mark -

/** Do not forget about weak referens to self for presentCompletionHandler, completionHandler and dismissCompletionHandler blocks */
- (void)showActionSheetWithDestinations:(LGSharingDestination)destinations
                              shareText:(NSString *)text
                              shareLink:(NSString *)link
               presentCompletionHandler:(void(^)(LGSharingDestination destination))presentCompletionHandler
                      completionHandler:(void(^)(LGSharingObject *object))completionHandler
               dismissCompletionHandler:(void(^)(LGSharingDestination destination))dismissCompletionHandler;

/** Do not forget about weak referens to self for presentCompletionHandler, completionHandler and dismissCompletionHandler blocks */
- (void)showActionSheetWithDestinations:(LGSharingDestination)destinations
                           setupHandler:(void(^)(LGSharingObject *object))setupHandler
               presentCompletionHandler:(void(^)(LGSharingDestination destination))presentCompletionHandler
                      completionHandler:(void(^)(LGSharingObject *object))completionHandler
               dismissCompletionHandler:(void(^)(LGSharingDestination destination))dismissCompletionHandler;

- (void)setEmailAlertTitle:(NSString *)title message:(NSString *)message;
- (void)setSmsAlertTitle:(NSString *)title message:(NSString *)message;

#pragma mark -

- (void)shareToVkontakteText:(NSString *)text
                        link:(NSString *)link
                    animated:(BOOL)animated
    presentCompletionHandler:(void(^)())presentCompletionHandler
           completionHandler:(void(^)(VKShareDialogControllerResult result))completionHandler
    dismissCompletionHandler:(void(^)())dismissCompletionHandler;

- (void)shareToFacebookText:(NSString *)text
                       link:(NSString *)link
                   animated:(BOOL)animated
   presentCompletionHandler:(void(^)())presentCompletionHandler
          completionHandler:(void(^)(SLComposeViewControllerResult result))completionHandler
   dismissCompletionHandler:(void(^)())dismissCompletionHandler;

- (void)shareToTwitterText:(NSString *)text
                      link:(NSString *)link
                  animated:(BOOL)animated
  presentCompletionHandler:(void(^)())presentCompletionHandler
         completionHandler:(void(^)(SLComposeViewControllerResult result))completionHandler
  dismissCompletionHandler:(void(^)())dismissCompletionHandler;

/** Do not forget about weak referens to self for completionHandler block */
- (void)shareToGooglePlusText:(NSString *)text
                         link:(NSString *)link
            completionHandler:(void(^)(NSError *error))completionHandler;

/** Do not forget about weak referens to self for completionHandler and dismissCompletionHandler blocks */
- (void)shareToEmailText:(NSString *)text
                    link:(NSString *)link
                animated:(BOOL)animated
presentCompletionHandler:(void(^)())presentCompletionHandler
       completionHandler:(void(^)(MFMailComposeResult result, NSError *error))completionHandler
dismissCompletionHandler:(void(^)())dismissCompletionHandler;

/** Do not forget about weak referens to self for completionHandler and dismissCompletionHandler blocks */
- (void)shareToSmsText:(NSString *)text
                  link:(NSString *)link
              animated:(BOOL)animated
presentCompletionHandler:(void(^)())presentCompletionHandler
     completionHandler:(void(^)(MessageComposeResult result))completionHandler
dismissCompletionHandler:(void(^)())dismissCompletionHandler;

#pragma mark -

+ (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation;

#pragma mark -

/** Unavailable, use +sharedManagerWithNavigationController instead */
+ (instancetype)alloc __attribute__((unavailable("use +sharedManagerWithNavigationController... instead")));
/** Unavailable, use +sharedManagerWithNavigationController... instead */
+ (instancetype)allocWithZone:(struct _NSZone *)zone __attribute__((unavailable("use +sharedManagerWithNavigationController... instead")));
/** Unavailable, use +sharedManagerWithNavigationController... instead */
+ (instancetype)new __attribute__((unavailable("use +sharedManagerWithNavigationController... instead")));
/** Unavailable, use +sharedManagerWithNavigationController... instead */
- (instancetype)init __attribute__((unavailable("use +sharedManagerWithNavigationController... instead")));
/** Unavailable, use +sharedManagerWithNavigationController... instead */
- (id)copy __attribute__((unavailable("use +sharedManagerWithNavigationController... instead")));

@end

#pragma mark -

@interface LGSharingObject : NSObject

@property (assign, nonatomic) LGSharingDestination destination;
@property (strong, nonatomic) NSString *buttonTitle;
@property (strong, nonatomic) NSString *text;
@property (strong, nonatomic) NSString *link;

@end
