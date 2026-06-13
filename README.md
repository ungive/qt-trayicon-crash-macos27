# QSystemTrayIcon crash on macOS 27

Bug report: https://qt-project.atlassian.net/browse/QTBUG-147449

## Summary

Qt programs that have a tray icon (`QSystemTrayIcon`) seem to immediately crash when that tray icon is clicked. This affects Qt programs running on the latest macOS 27 beta.

## Known affected projects

- https://github.com/ungive/discord-music-presence/issues/833

## Tested Qt versions

- 6.6.3
- 6.9.3
- 6.10.3
- 6.11.1
- 6.12.0

## Reproduction steps

1. Debug the test program (or just run it) on the latest macOS 27 beta
2. Observe that the application creates a tray icon in the menu bar
3. Click the tray icon, you may have to open and close the tray menu a few times
4. Observe the error

## System information

```
% system_profiler SPSoftwareDataType
System Version: macOS 27.0 (26A5353q)
Kernel Version: Darwin 27.0.0
```

## Build instructions

1. Install a C++ compiler (commonly Clang via Xcode)
2. Install CMake: `brew install cmake`
3. Adjust the Qt path in `CMakeLists.txt` to a valid Qt installation (Qt installation instructions below)
4. Run the following commands:
```
mkdir build
cd build
cmake ..
cmake --build .
```

Now execute the app and follow the reproduction steps above:

```
./QtTrayTest
```

### Installing Qt with aqtinstall

This uses https://pypi.org/project/aqtinstall.

```
mkdir -p ~/aqtinstall
cd ~/aqtinstall
python3 -m venv venv
. venv/bin/activate
pip3 install aqtinstall
aqt install-qt -O ~/Qt mac desktop 6.12.0 clang_64
```

## Application output

```
2026-06-13 02:39:16.835840+0200 QtTrayTest[28780:163278] [general] *** Assertion failure in -[NSEvent clickCount], NSEvent.m:2597
2026-06-13 02:40:51.560873+0200 QtTrayTest[28780:163278] *** Terminating app due to uncaught exception 'NSInternalInconsistencyException', reason: 'Invalid message sent to event "NSEvent: type=KitDefined loc=(0,0) time=6016.0 flags=0 win=0x0 winNum=7 ctxt=0x0 subtype=255 data1=0 data2=0"'
*** First throw call stack:
(
        0   CoreFoundation                      0x000000018792ee60 __exceptionPreprocess + 176
        1   libobjc.A.dylib                     0x00000001873907fc objc_exception_throw + 88
        2   Foundation                          0x00000001890cbf7c -[NSCalendarDate initWithCoder:] + 0
        3   AppKit                              0x000000018bf0c9b8 -[NSEvent clickCount] + 152
        4   libqcocoa.dylib                     0x0000000101c7f40c qt_plugin_instance + 188632
        5   CoreFoundation                      0x00000001878b38ec __CFNOTIFICATIONCENTER_IS_CALLING_OUT_TO_AN_OBSERVER__ + 148
        6   CoreFoundation                      0x0000000187942708 ___CFXRegistrationPost_block_invoke + 92
        7   CoreFoundation                      0x000000018794264c _CFXRegistrationPost + 440
        8  
*** Terminating app due to uncaught exception 'NSInternalInconsistencyException', reason: 'Invalid message sent to event "NSEvent: type=KitDefined loc=(0,0) time=6016.0 flags=0 win=0x0 winNum=7 ctxt=0x0 subtype=255 data1=0 data2=0"'
*** First throw call stack:
(
        0   CoreFoundation                      0x000000018792ee60 __exceptionPreprocess + 176
        1   libobjc.A.dylib                     0x00000001873907fc objc_exception_throw + 88
        2   Foundation                          0x00000001890cbf7c -[NSCalendarDate initWithCoder:] + 0
        3   AppKit                              0x000000018bf0c9b8 -[NSEvent clickCount] + 152
        4   libqcocoa.dylib                     0x0000000101c7f40c qt_plugin_instance + 188632
        5   CoreFoundation                      0x00000001878b38ec __CFNOTIFICATIONCENTER_IS_CALLING_OUT_TO_AN_OBSERVER__ + 148
        6   CoreFoundation                      0x0000000187942708 ___CFXRegistrationPost_block_invoke + 92
        7   CoreFoundation                      0x000000018794264c _CFXRegistrationPost + 440
        8   CoreFoundation                      0x00000001878804a4 _CFXNotificationPost + 696
        9   Foundation                          0x0000000188fc6750 -[NSNotificationCenter postNotificationName:object:userInfo:] + 88
        10  AppKit                              0x000000018c3134e4 -[NSMenuTrackingSession sendBeginTrackingNotifications] + 188
        11  AppKit                              0x000000018c31abc4 -[NSMenuTrackingSession beginTrackingSession:] + 644
        12  AppKit                              0x000000018c2c9804 +[NSContextMenuImpl presentPopup:fromView:withContext:animated:async:completionBlock:] + 432
        13  AppKit                              0x000000018c51a800 _NSPopUpMenu + 1772
        14  AppKit                              0x000000018c51a03c -[NSCocoaMenuImpl popUpMenu:atLocation:width:view:selectedItemIndexProvider:font:positioningRect:flags:options:] + 432
        15  AppKit                              0x000000018c519e64 -[NSCocoaMenuImpl popUpMenu:atLocation:width:forView:withSelectedItem:withFont:withFlags:withOptions:] + 96
        16  AppKit                              0x000000018c4db9f4 +[NSStatusBarButtonCell popUpStatusBarMenu:ofItem:ofBar:inRect:ofView:withEvent:] + 500
        17  AppKit                              0x000000018c4e3cb4 -[NSStatusItem popUpStatusItemMenu:] + 108
        18  AppKit                              0x000000018c4e4138 -[NSStatusItem _beginExpandedInterfaceSession:] + 252
        19  AppKit                              0x000000018c39fd18 -[NSSceneStatusItem _beginExpandedInterfaceSession:] + 192
        20  AppKit                              0x000000018c39e9dc __33-[NSSceneStatusItem _setupScene:]_block_invoke.25 + 292
        21  AppKit                              0x000000018ce7332c block_destroy_helper + 22440
        22  AppKit                              0x000000018ce734a8 block_destroy_helper + 22820
        23  FrontBoardServices                  0x00000001a461bc40 -[FBSSceneObserver scene:handlePrivateActions:] + 80
        24  FrontBoardServices                  0x00000001a45df850 -[FBSScene updater:didReceiveActions:forExtension:] + 740
        25  FrontBoardServices                  0x00000001a4607d10 __71-[FBSWorkspaceScenesClient sceneID:sendActions:toExtension:completion:]_block_invoke + 204
        26  FrontBoardServices                  0x00000001a45c2bc4 -[FBSWorkspace _calloutQueue_executeCalloutFromSource:withBlock:] + 180
        27  libdispatch.dylib                   0x00000001876585bc _dispatch_client_callout + 16
        28  libdispatch.dylib                   0x0000000187643700 _dispatch_block_invoke_direct + 284
        29  BoardServices                       0x00000001a46a99d4 __BSSERVICEMAINRUNLOOPQUEUE_IS_CALLING_OUT_TO_A_BLOCK__ + 48
        30  BoardServices                       0x00000001a46a87f4 BSServiceMainRunLoopSourceHandler + 232
        31  CoreFoundation                      0x00000001878bf0c0 __CFRUNLOOP_IS_CALLING_OUT_TO_A_SOURCE0_PERFORM_FUNCTION__ + 28
        32  CoreFoundation                      0x00000001878bf054 __CFRunLoopDoSource0 + 172
        33  CoreFoundation                      0x00000001878bedc0 __CFRunLoopDoSources0 + 232
        34  CoreFoundation                      0x00000001878bd9c0 __CFRunLoopRun + 836
        35  CoreFoundation                      0x0000000187996ba4 _CFRunLoopRunSpecificWithOptions + 532
        36  HIToolbox                           0x0000000194ba35a4 RunCurrentEventLoopInMode + 320
        37  HIToolbox                           0x0000000194ba692c ReceiveNextEventCommon + 488
        38  HIToolbox                           0x0000000194d28f8c _BlockUntilNextEventMatchingListInMode + 48
        39  AppKit                              0x000000018c0b7924 _DPSBlockUntilNextEventMatchingListInMode + 292
        40  AppKit                              0x000000018bd738fc _DPSNextEvent + 580
        41  AppKit                              0x000000018c4ed17c -[NSApplication(NSEventRouting) _nextEventMatchingEventMask:untilDate:inMode:dequeue:] + 780
        42  AppKit                              0x000000018c4ecc9c -[NSApplication(NSEventRouting) nextEventMatchingMask:untilDate:inMode:dequeue:] + 244
        43  AppKit                              0x000000018bd66a4c -[NSApplication run] + 396
        44  libqcocoa.dylib                     0x0000000101c5f198 qt_plugin_instance + 56932
        45  QtCore                              0x00000001020a5270 _ZN10QEventLoop4execE6QFlagsINS_17ProcessEventsFlagEE + 576
        46  QtCore                              0x000000010209b7cc _ZN16QCoreApplication4execEv + 228
        47  QtTrayTest                          0x00000001000039c8 main + 72
        48  dyld                                0x000000018742c914 start + 6700
)
2026-06-13 02:40:51.561702+0200 QtTrayTest[28780:163278] [General] An uncaught exception was raised
2026-06-13 02:40:51.561762+0200 QtTrayTest[28780:163278] [General] Invalid message sent to event "NSEvent: type=KitDefined loc=(0,0) time=6016.0 flags=0 win=0x0 winNum=7 ctxt=0x0 subtype=255 data1=0 data2=0"
2026-06-13 02:40:51.561974+0200 QtTrayTest[28780:163278] [General] (
        0   CoreFoundation                      0x000000018792ee60 __exceptionPreprocess + 176
        1   libobjc.A.dylib                     0x00000001873907fc objc_exception_throw + 88
        2   Foundation                          0x00000001890cbf7c -[NSCalendarDate initWithCoder:] + 0
        3   AppKit                              0x000000018bf0c9b8 -[NSEvent clickCount] + 152
        4   libqcocoa.dylib                     0x0000000101c7f40c qt_plugin_instance + 188632
        5   CoreFoundation                      0x00000001878b38ec __CFNOTIFICATIONCENTER_IS_CALLING_OUT_TO_AN_OBSERVER__ + 148
        6   CoreFoundation                      0x0000000187942708 ___CFXRegistrationPost_block_invoke + 92
        7   CoreFoundation                      0x000000018794264c _CFXRegistrationPost + 440
        8   CoreFoundation                      0x00000001878804a4 _CFXNotificationPost + 696
        9   Foundation                          0x0000000188fc6750 -[NSNotificationCenter postNotificationName:object:userInfo:] + 88
        10  AppKit                              0x000000018c3134e4 -[NSMenuTrackingSession sendBeginTrackingNotifications] + 188
        11  AppKit                              0x000000018c31abc4 -[NSMenuTrackingSession beginTrackingSession:] + 644
        12  AppKit                              0x000000018c2c9804 +[NSContextMenuImpl presentPopup:fromView:withContext:animated:async:completionBlock:] + 432
        13  AppKit                              0x000000018c51a800 _NSPopUpMenu + 1772
        14  AppKit                              0x000000018c51a03c -[NSCocoaMenuImpl popUpMenu:atLocation:width:view:selectedItemIndexProvider:font:positioningRect:flags:options:] + 432
        15  AppKit                              0x000000018c519e64 -[NSCocoaMenuImpl popUpMenu:atLocation:width:forView:withSelectedItem:withFont:withFlags:withOptions:] + 96
        16  AppKit                              0x000000018c4db9f4 +[NSStatusBarButtonCell popUpStatusBarMenu:ofItem:ofBar:inRect:ofView:withEvent:] + 500
        17  AppKit                              0x000000018c4e3cb4 -[NSStatusItem popUpStatusItemMenu:] + 108
        18  AppKit                              0x000000018c4e4138 -[NSStatusItem _beginExpandedInterfaceSession:] + 252
        19  AppKit                              0x000000018c39fd18 -[NSSceneStatusItem _beginExpandedInterfaceSession:] + 192
        20  AppKit                              0x000000018c39e9dc __33-[NSSceneStatusItem _setupScene:]_block_invoke.25 + 292
        21  AppKit                              0x000000018ce7332c block_destroy_helper + 22440
        22  AppKit                              0x000000018ce734a8 block_destroy_helper + 22820
        23  FrontBoardServices                  0x00000001a461bc40 -[FBSSceneObserver scene:handlePrivateActions:] + 80
        24  FrontBoardServices                  0x00000001a45df850 -[FBSScene updater:didReceiveActions:forExtension:] + 740
        25  FrontBoardServices                  0x00000001a4607d10 __71-[FBSWorkspaceScenesClient sceneID:sendActions:toExtension:completion:]_block_invoke + 204
        26  FrontBoardServices                  0x00000001a45c2bc4 -[FBSWorkspace _calloutQueue_executeCalloutFromSource:withBlock:] + 180
        27  libdispatch.dylib                   0x00000001876585bc _dispatch_client_callout + 16
        28  libdispatch.dylib                   0x0000000187643700 _dispatch_block_invoke_direct + 284
        29  BoardServices                       0x00000001a46a99d4 __BSSERVICEMAINRUNLOOPQUEUE_IS_CALLING_OUT_TO_A_BLOCK__ + 48
        30  BoardServices                       0x00000001a46a87f4 BSServiceMainRunLoopSourceHandler + 232
        31  CoreFoundation                      0x00000001878bf0c0 __CFRUNLOOP_IS_CALLING_OUT_TO_A_SOURCE0_PERFORM_FUNCTION__ + 28
        32  CoreFoundation                      0x00000001878bf054 __CFRunLoopDoSource0 + 172
        33  CoreFoundation                      0x00000001878bedc0 __CFRunLoopDoSources0 + 232
        34  CoreFoundation                      0x00000001878bd9c0 __CFRunLoopRun + 836
        35  CoreFoundation                      0x0000000187996ba4 _CFRunLoopRunSpecificWithOptions + 532
        36  HIToolbox                           0x0000000194ba35a4 RunCurrentEventLoopInMode + 320
        37  HIToolbox                           0x0000000194ba692c ReceiveNextEventCommon + 488
        38  HIToolbox                           0x0000000194d28f8c _BlockUntilNextEventMatchingListInMode + 48
        39  AppKit                              0x000000018c0b7924 _DPSBlockUntilNextEventMatchingListInMode + 292
        40  AppKit                              0x000000018bd738fc _DPSNextEvent + 580
        41  AppKit                              0x000000018c4ed17c -[NSApplication(NSEventRouting) _nextEventMatchingEventMask:untilDate:inMode:dequeue:] + 780
        42  AppKit                              0x000000018c4ecc9c -[NSApplication(NSEventRouting) nextEventMatchingMask:untilDate:inMode:dequeue:] + 244
        43  AppKit                              0x000000018bd66a4c -[NSApplication run] + 396
        44  libqcocoa.dylib                     0x0000000101c5f198 qt_plugin_instance + 56932
        45  QtCore                              0x00000001020a5270 _ZN10QEventLoop4execE6QFlagsINS_17ProcessEventsFlagEE + 576
        46  QtCore                              0x000000010209b7cc _ZN16QCoreApplication4execEv + 228
        47  QtTrayTest                          0x00000001000039c8 main + 72
        48  dyld                                0x000000018742c914 start + 6700
)
2026-06-13 02:40:51.569969+0200 QtTrayTest[28780:163278] [HIExceptions] FAULT: NSInternalInconsistencyException: Invalid message sent to event "NSEvent: type=KitDefined loc=(0,0) time=6016.0 flags=0 win=0x0 winNum=7 ctxt=0x0 subtype=255 data1=0 data2=0"; {
    NSAssertFile = "NSEvent.m";
    NSAssertLine = 2597;
}
libc++abi: terminating due to uncaught exception of type NSException
```

## Stack trace

C++ stack trace (VSCodium debug window):

```
__cxa_throw (@__cxa_throw:3)
objc_exception_throw (@objc_exception_throw:115)
-[NSAssertionHandler handleFailureInMethod:object:file:lineNumber:description:] (@-[NSCalendarDate initWithCoder:]:3)
-[NSEvent clickCount] (@-[NSEvent clickCount]:41)
___lldb_unnamed_symbol_373e0 (@___lldb_unnamed_symbol_373e0:14)
__CFNOTIFICATIONCENTER_IS_CALLING_OUT_TO_AN_OBSERVER__ (@__CFNOTIFICATIONCENTER_IS_CALLING_OUT_TO_AN_OBSERVER__:40)
___CFXRegistrationPost_block_invoke (@___CFXRegistrationPost_block_invoke:26)
_CFXRegistrationPost (@_CFXRegistrationPost:113)
_CFXNotificationPost (@_CFXNotificationPost:177)
-[NSNotificationCenter postNotificationName:object:userInfo:] (@-[NSNotificationCenter postNotificationName:object:userInfo:]:25)
-[NSMenuTrackingSession sendBeginTrackingNotifications] (@-[NSMenuTrackingSession sendBeginTrackingNotifications]:50)
-[NSMenuTrackingSession beginTrackingSession:] (@-[NSMenuTrackingSession beginTrackingSession:]:164)
+[NSContextMenuImpl presentPopup:fromView:withContext:animated:async:completionBlock:] (@+[NSContextMenuImpl presentPopup:fromView:withContext:animated:async:completionBlock:]:111)
_NSPopUpMenu (@_NSPopUpMenu:446)
-[NSCocoaMenuImpl popUpMenu:atLocation:width:view:selectedItemIndexProvider:font:positioningRect:flags:options:] (@-[NSCocoaMenuImpl popUpMenu:atLocation:width:view:selectedItemIndexProvider:font:positioningRect:flags:options:]:111)
-[NSCocoaMenuImpl popUpMenu:atLocation:width:forView:withSelectedItem:withFont:withFlags:withOptions:] (@-[NSCocoaMenuImpl popUpMenu:atLocation:width:forView:withSelectedItem:withFont:withFlags:withOptions:]:27)
+[NSStatusBarButtonCell popUpStatusBarMenu:ofItem:ofBar:inRect:ofView:withEvent:] (@+[NSStatusBarButtonCell popUpStatusBarMenu:ofItem:ofBar:inRect:ofView:withEvent:]:128)
-[NSStatusItem popUpStatusItemMenu:] (@-[NSStatusItem popUpStatusItemMenu:]:30)
-[NSStatusItem _beginExpandedInterfaceSession:] (@-[NSStatusItem _beginExpandedInterfaceSession:]:66)
-[NSSceneStatusItem _beginExpandedInterfaceSession:] (@-[NSSceneStatusItem _beginExpandedInterfaceSession:]:51)
__33-[NSSceneStatusItem _setupScene:]_block_invoke.25 (@__33-[NSSceneStatusItem _setupScene:]_block_invoke.25:76)
___lldb_unnamed_symbol_185efed9c (@___lldb_unnamed_symbol_185efed9c:359)
___lldb_unnamed_symbol_185eff440 (@___lldb_unnamed_symbol_185eff440:29)
-[FBSSceneObserver scene:handlePrivateActions:] (@-[FBSSceneObserver scene:handlePrivateActions:]:23)
-[FBSScene updater:didReceiveActions:forExtension:] (@-[FBSScene updater:didReceiveActions:forExtension:]:188)
__71-[FBSWorkspaceScenesClient sceneID:sendActions:toExtension:completion:]_block_invoke (@__71-[FBSWorkspaceScenesClient sceneID:sendActions:toExtension:completion:]_block_invoke:54)
-[FBSWorkspace _calloutQueue_executeCalloutFromSource:withBlock:] (@-[FBSWorkspace _calloutQueue_executeCalloutFromSource:withBlock:]:48)
_dispatch_client_callout (@_dispatch_client_callout:7)
_dispatch_block_invoke_direct (@_dispatch_block_invoke_direct:74)
__BSSERVICEMAINRUNLOOPQUEUE_IS_CALLING_OUT_TO_A_BLOCK__ (@__BSSERVICEMAINRUNLOOPQUEUE_IS_CALLING_OUT_TO_A_BLOCK__:15)
BSServiceMainRunLoopSourceHandler (@BSServiceMainRunLoopSourceHandler:61)
__CFRUNLOOP_IS_CALLING_OUT_TO_A_SOURCE0_PERFORM_FUNCTION__ (@__CFRUNLOOP_IS_CALLING_OUT_TO_A_SOURCE0_PERFORM_FUNCTION__:10)
__CFRunLoopDoSource0 (@__CFRunLoopDoSource0:46)
__CFRunLoopDoSources0 (@__CFRunLoopDoSources0:61)
__CFRunLoopRun (@__CFRunLoopRun:212)
_CFRunLoopRunSpecificWithOptions (@_CFRunLoopRunSpecificWithOptions:136)
RunCurrentEventLoopInMode (@RunCurrentEventLoopInMode:83)
ReceiveNextEventCommon (@ReceiveNextEventCommon:125)
_BlockUntilNextEventMatchingListInMode (@_BlockUntilNextEventMatchingListInMode:15)
_DPSBlockUntilNextEventMatchingListInMode (@_DPSBlockUntilNextEventMatchingListInMode:76)
_DPSNextEvent (@_DPSNextEvent:148)
-[NSApplication(NSEventRouting) _nextEventMatchingEventMask:untilDate:inMode:dequeue:] (@-[NSApplication(NSEventRouting) _nextEventMatchingEventMask:untilDate:inMode:dequeue:]:198)
-[NSApplication(NSEventRouting) nextEventMatchingMask:untilDate:inMode:dequeue:] (@-[NSApplication(NSEventRouting) nextEventMatchingMask:untilDate:inMode:dequeue:]:64)
-[NSApplication run] (@-[NSApplication run]:102)
___lldb_unnamed_symbol_16900 (@___lldb_unnamed_symbol_16900:553)
QEventLoop::exec(QFlags<QEventLoop::ProcessEventsFlag>) (@QEventLoop::exec(QFlags<QEventLoop::ProcessEventsFlag>):147)
QCoreApplication::exec() (@QCoreApplication::exec():60)
main (/Users/me/git/qt-trayicon-crash-macos27/main.cpp:48)
start (@start:1678)
```
