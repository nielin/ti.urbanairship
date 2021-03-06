/*
 Copyright 2009-2015 Urban Airship Inc. All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.

 2. Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE URBAN AIRSHIP INC ``AS IS'' AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 EVENT SHALL URBAN AIRSHIP INC OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#import <Foundation/Foundation.h>
#import "UAHTTPRequest.h"

/**
 * A wrapper for NSURLConnection implementing the NSURLConnectionDelegate protocol.
 */
@interface UAHTTPConnection : NSObject <NSURLConnectionDelegate> {

}

/**
 * The connection sending the message.
 */
@property (nonatomic, strong, readonly) NSURLConnection *urlConnection;

/**
 * The connection request as a UAHTTPRequest.
 */
@property (nonatomic, strong, readonly) UAHTTPRequest *request;

/**
 * The connection delegate.
 */
@property (nonatomic, weak) id delegate;

/**
 * The connection success selector.
 */
@property (nonatomic, assign) SEL successSelector;

/**
 * The connection failure selector.
 */
@property (nonatomic, assign) SEL failureSelector;

/**
 * The connection success block.
 */
@property (nonatomic, copy) UAHTTPConnectionSuccessBlock successBlock;

/**
 * The connection failure block.
 */
@property (nonatomic, copy) UAHTTPConnectionFailureBlock failureBlock;

/**
 * The queue on which to dispatch block and delegate callbacks.
 *
 * If unset, callbacks will occur on the thread from which the connection was started.
 * Note: you cannot reschedule the delegate queue once a connection is in flight.
 */
@property (nonatomic, strong) NSOperationQueue *delegateQueue;

/**
 * Class factory method for creating a UAHTTPConnection.
 * @param httpRequest An instance of UAHTTPRequest.
 * @return A UAHTTPConnection with the specified httpRequest.
 */
+ (instancetype)connectionWithRequest:(UAHTTPRequest *)httpRequest;

/**
 * Class factory method for creating a UAHTTPConnection.
 * @param httpRequest An instance of UAHTTPRequest.
 * @param delegate The delegate
 * @param successSelector The selector to be called if the connection was successful.
 * @param failureSelector The selector to be called if the connection was unsuccessful.
 * @return A UAHTTPConnection with the specified httpRequest.
 */
+ (instancetype)connectionWithRequest:(UAHTTPRequest *)httpRequest
                             delegate:(id)delegate
                              success:(SEL)successSelector
                              failure:(SEL)failureSelector;

/**
 * Class factory method for creating a UAHTTPConnection.
 * @param httpRequest An instance of UAHTTPRequest.
 * @param successBlock A UAHTTPConnectionSuccessBlock that will be called if the connection was successful.
 * @param failureBlock A UAHTTPConnectionFailureBlock that will be called if the connection was unsuccessful.
 * @return A UAHTTPConnection with the specified httpRequest.
 */
+ (instancetype)connectionWithRequest:(UAHTTPRequest *)httpRequest
                         successBlock:(UAHTTPConnectionSuccessBlock)successBlock
                         failureBlock:(UAHTTPConnectionFailureBlock)failureBlock;

/**
 * Initializer with the HTTP request.
 * @param httpRequest An instance of UAHTTPRequest.
 */
- (instancetype)initWithRequest:(UAHTTPRequest *)httpRequest;

/**
 * Start the connection asynchronously.
 * @return `YES` if the connection was started, otherwise `NO`.
 */
- (BOOL)start;

/**
 * Start the connection synchronously.
 * @return `YES` if the connection was started, otherwise `NO`.
 */
- (BOOL)startSynchronous;

/**
 * Cancel the connection
 */
- (void)cancel;

#pragma mark -
#pragma mark NSURLConnectionDelegate

- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSHTTPURLResponse *)response;
- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data;
- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error;
- (void)connectionDidFinishLoading:(NSURLConnection *)connection;

@end
