//
// LGVkontakte.m
// LGSharing
//
// SPDX-License-Identifier: MIT
// Copyright (c) 2015 Grigorii Lutkov <grigorii@lutkov.dev>
//

#import "LGSharingVkontakte.h"

@interface LGSharingVkontakte () <VKSdkDelegate>

/** Your vk app id */
@property (strong, nonatomic) NSString *appId;
@property (strong, nonatomic) NSString *text;
@property (strong, nonatomic) NSURL    *link;
@property (assign, nonatomic) BOOL     needsPost;

@end

@implementation LGSharingVkontakte

+ (instancetype)sharedManagerWithAppId:(NSString *)appId navigationController:(UINavigationController *)navigationController
{
    static dispatch_once_t once;
    static id sharedManager = nil;

    dispatch_once(&once, ^
                  {
                      sharedManager = [super new];

                      [(LGSharingVkontakte *)sharedManager setAppId:appId];
                      [(LGSharingVkontakte *)sharedManager setNavigationController:navigationController];

                      [(LGSharingVkontakte *)sharedManager initialize];
                  });

    return sharedManager;
}

- (void)initialize
{
    [VKSdk initializeWithDelegate:self andAppId:_appId];
}

#pragma mark - VKSdk Delagate

- (void)vkSdkShouldPresentViewController:(UIViewController *)controller
{
    [_navigationController presentViewController:controller animated:YES completion:nil];
}

- (void)vkSdkNeedCaptchaEnter:(VKError *)captchaError
{
    VKCaptchaViewController *viewController = [VKCaptchaViewController captchaControllerWithError:captchaError];
    [viewController presentIn:_navigationController];
}

- (BOOL)vkSdkIsBasicAuthorization
{
    return YES;
}

- (void)vkSdkUserDeniedAccess:(VKError *)authorizationError
{
    //
}

- (void)vkSdkReceivedNewToken:(VKAccessToken *)newToken
{
    //
}

- (void)vkSdkTokenHasExpired:(VKAccessToken *)expiredToken
{
    //
}

#pragma mark -

- (void)postWithText:(NSString *)text
                link:(NSURL *)link
            animated:(BOOL)animated
presentCompletionHandler:(void(^)())presentCompletionHandler
   completionHandler:(void(^)(VKShareDialogControllerResult result))completionHandler
dismissCompletionHandler:(void(^)())dismissCompletionHandler
{
    VKShareDialogController *shareDialog = [VKShareDialogController new];
    shareDialog.requestedScope = @[VK_PER_OFFLINE, VK_PER_WALL, VK_PER_PHOTOS];
    shareDialog.text = text;
    shareDialog.shareLink = [[VKShareLink alloc] initWithTitle:text link:link];

    __weak typeof(self) wself = self;

    [shareDialog setCompletionHandler:^(VKShareDialogControllerResult result)
     {
         if (wself)
         {
             __strong typeof(wself) self = wself;

             if (completionHandler) completionHandler(result);

             [self.navigationController dismissViewControllerAnimated:animated completion:dismissCompletionHandler];
         }
     }];

    [_navigationController presentViewController:shareDialog animated:animated completion:presentCompletionHandler];
}

#pragma mark -

+ (void)applicationOpenURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication
{
    [VKSdk processOpenURL:url fromApplication:sourceApplication];
}

@end
