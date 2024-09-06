/*
 *  Copyright (C) 2010-2024 Chaoji Li
 *
 *  DOSPAD is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */


#import "Common.h"
#import "FileSystemObject.h"
#import "HoldIndicator.h"
#import "SDL_uikitopenglview.h"
#import "KeyboardView.h"
#import "GamePadView.h"
#import "PianoKeyboard.h"
#import "DOSPadEmulator.h"
#import "KeyboardSpy.h"
#import "DPSettings.h"

typedef enum {
    InputSource_PCKeyboard = 0,
    InputSource_MouseButtons,
    InputSource_NumPad,
    InputSource_GamePad,
    InputSource_Joystick,
    InputSource_PianoKeyboard,
    InputSource_TotalCount
} InputSourceType;

typedef enum {
	DriveMount_Default,
	DriveMount_Folder,
	DriveMount_Packages,
	DriveMount_DiskImage,
	DriveMount_CDImage
} DriveMountType;

@interface DOSPadBaseViewController : UIViewController
<
	SDL_uikitopenglview_delegate,
	MouseHoldDelegate,
	KeyDelegate,
	UIAlertViewDelegate,
	DOSPadEmulatorDelegate,
	UIDocumentPickerDelegate
>
{
    SDL_uikitopenglview *screenView;
    HoldIndicator *holdIndicator;
    
    GamePadView *gamepad;
    GamePadView *joystick;
    KeyboardView *kbd;
    KeyboardView *numpad;
    UIButton *btnMouseLeft;
    UIButton *btnMouseRight;
    PianoKeyboard *piano;
}

@property (nonatomic, strong) SDL_uikitopenglview *screenView;
@property (nonatomic, strong) KeyboardSpy *kbdspy;

+ (DOSPadBaseViewController*)dospadController;

- (void)onMouseLeftDown;
- (void)onMouseLeftUp;
- (void)onMouseRightDown;
- (void)onMouseRightUp;
- (void)sendCommandToDOS:(NSString*)cmd;
- (void)showOption:(id)sender;
- (NSString*)currentCycles;
- (int)currentFrameskip;
- (BOOL)isPortrait;
- (BOOL)isLandscape;

- (bool)isInputSourceEnabled:(InputSourceType)type;
- (BOOL)isInputSourceActive:(InputSourceType)type;
- (void)addInputSource:(InputSourceType)type;
- (void)addInputSourceExclusively:(InputSourceType)type;
- (void)removeInputSource:(InputSourceType)type;
- (void)removeAllInputSources;
- (void)createPCKeyboard;
- (void)createNumpad;
- (void)createGamepad;
- (void)createJoystick;
- (void)createMouseButtons;
- (void)createPianoKeyboard;
- (void)fillScreen:(CGRect)availRect;
- (CGRect)putScreen:(CGRect)availRect scaleMode:(DPScreenScaleMode)scaleMode;

-(void)updateFrameskip:(NSNumber*)skip;
-(void)updateCpuCycles:(NSString*)title;
- (void)updateScreen;
-(void) openMfiMapper:(id)sender;
-(void)openDriveMountPicker:(DriveMountType)mountType;

@end
