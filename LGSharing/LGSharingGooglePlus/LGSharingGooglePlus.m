//
// LGSharingGooglePlus.m
// LGSharing
//
// SPDX-License-Identifier: MIT
// Copyright (c) 2015 Grigorii Lutkov <grigorii@lutkov.dev>
//

#import "LGSharingGooglePlus.h"
#import "GooglePlus.h"
#import "GTLPlusConstants.h"

@interface LGSharingGooglePlus () <GPPSignInDelegate, GPPShareDelegate>

/** Your app client id */
@property (strong, nonatomic) NSString *clientId;
/** app deep link id */
@property (strong, nonatomic) NSString *deepLinkId;

@property (strong, nonatomic) GPPSignIn *signIn;
@property (strong, nonatomic) GPPShare  *share;
@property (strong, nonatomic) NSString  *text;
@property (strong, nonatomic) NSURL     *link;
@property (assign, nonatomic) BOOL      needsPost;

@property (strong, nonatomic) void (^completionHandler)();

@end

@implementation LGSharingGooglePlus

+ (instancetype)sharedManagerWithClientId:(NSString *)clientId deepLinkId:(NSString *)deepLinkId
{
    static dispatch_once_t once;
    static id sharedManager;

    dispatch_once(&once, ^(void)
                  {
                      sharedManager = [super new];

                      [(LGSharingGooglePlus *)sharedManager setClientId:clientId];
                      [(LGSharingGooglePlus *)sharedManager setDeepLinkId:deepLinkId];

                      [(LGSharingGooglePlus *)sharedManager initialize];
                  });

    return sharedManager;
}

- (void)initialize
{
    _signIn = [GPPSignIn sharedInstance];
    _signIn.delegate = self;
    _signIn.clientID = _clientId;
    _signIn.scopes = @[kGTLAuthScopePlusLogin]; // определяется в файле GTLPlusConstants.h

    _share = [GPPShare sharedInstance];
    _share.delegate = self;
}

#pragma mark -

- (BOOL)isAuthorized
{
    return (_signIn.authentication == nil ? NO : YES);
}

- (void)authorize
{
    if (![_signIn trySilentAuthentication]) [_signIn authenticate];
}

- (void)postWithText:(NSString *)text
                link:(NSURL *)link
   completionHandler:(void(^)(NSError *error))completionHandler
{
    _text = text;
    _link = link;
    _completionHandler = completionHandler;

    if ([self isAuthorized])
    {
        id<GPPShareBuilder> shareBuilder = [_share nativeShareDialog];

        // Подставляются заголовок, описание, эскиз и ссылка,
        // связанные с передаваемым URL.
        [shareBuilder setURLToShare:link];
        [shareBuilder setPrefillText:text];

        // This line passes the deepLinkID to our application
        // if somebody opens the link on a supported mobile device
        if (_deepLinkId.length)
            [shareBuilder setContentDeepLinkID:_deepLinkId];

        // Вручную подставим заголовок, описание и эскиз
        // для передаваемого контента.
        // [shareBuilder setTitle:title
        //           description:text
        //          thumbnailURL:link];

        [shareBuilder open];
    }
    else
    {
        _needsPost = YES;

        [self authorize];
    }
}

- (void)signOut
{
    [_signIn signOut];
}

- (void)disconnect
{
    [_signIn disconnect];
}

#pragma mark - GPPSignInDelegate

- (void)finishedWithAuth:(GTMOAuth2Authentication *)auth error:(NSError *)error
{
    if (error)
    {
        NSLog(@"LGSharingGooglePlus: Received error %@ and auth object %@", error, auth);

        if (_completionHandler) _completionHandler(error);
    }
    else if (_text)
        [self postWithText:_text link:_link completionHandler:_completionHandler];
}

- (void)didDisconnectWithError:(NSError *)error
{
    if (error)
        NSLog(@"LGSharingGooglePlus: Received disconnect error %@", error);
    else
    {
        // Пользователь вышел и отключился.
        // Удалим данные пользователя если нужно
    }
}

#pragma mark - GPPShareDelegate

- (void)finishedSharing:(BOOL)shared
{
    if (_completionHandler) _completionHandler(nil);
}

- (void)finishedSharingWithError:(NSError *)error
{
    if (_completionHandler) _completionHandler(error);
}

#pragma mark -

+ (void)applicationOpenURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation
{
    [GPPURLHandler handleURL:url sourceApplication:sourceApplication annotation:annotation];
}

@end
