//
// Copyright 2020 Electronic Arts Inc.
//
// TiberianDawn.DLL and RedAlert.dll and corresponding source code is free 
// software: you can redistribute it and/or modify it under the terms of 
// the GNU General Public License as published by the Free Software Foundation, 
// either version 3 of the License, or (at your option) any later version.

// TiberianDawn.DLL and RedAlert.dll and corresponding source code is distributed 
// in the hope that it will be useful, but with permitted additional restrictions 
// under Section 7 of the GPL. See the GNU General Public License in LICENSE.TXT 
// distributed with this program. You should have received a copy of the 
// GNU General Public License along with permitted additional restrictions 
// with this program. If not, see https://github.com/electronicarts/CnC_Remastered_Collection

/***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Westwood 32 Bit Library                                      *
 *                                                                                             *
 *                    File Name : MOUSE.H                                                      *
 *                                                                                             *
 *                   Programmer : Philip W. Gorrow                                             *
 *                                                                                             *
 *                   Start Date : 12/12/95                                                     *
 *                                                                                             *
 *                  Last Update : December 12, 1995 [PWG]                                      *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#ifndef WW_MOUSE_H
#define WW_MOUSE_H

#include <gbuffer.h>

#define MAX_CURSOR_FRAMES			221

class WWMouseClass {
	public:
		WWMouseClass(GraphicViewPortClass *scr, int mouse_max_width, int mouse_max_height);
		~WWMouseClass();
		void *Set_Cursor(int xhotspot, int yhotspot, int cursor);
		void Process_Mouse(void);
		void Hide_Mouse(void);
		void Show_Mouse(void);
		void Conditional_Hide_Mouse(int x1, int y1, int x2, int y2);
		void Conditional_Show_Mouse(void);
		int Get_Mouse_State(void);
		int Get_Mouse_X(void);
		int Get_Mouse_Y(void);
		void Get_Mouse_XY(int &x, int &y);
		//
		// The following two routines can be used to render the mouse onto a graphicbuffer
		// other than the hidpage.
		//
		void Draw_Mouse(GraphicViewPortClass *scr);
		void Erase_Mouse(GraphicViewPortClass *scr, int forced = FALSE);

		void Block_Mouse(GraphicBufferClass *buffer);
		void Unblock_Mouse(GraphicBufferClass *buffer);
		void Set_Cursor_Clip(void);
		void Clear_Cursor_Clip(void);

// jmarshall - accessor functions to hook up mouse code from chronoshift.
		int Get_Hotspot_X(void) { return MouseXHot; }
		int Get_Hotspot_Y(void) { return MouseYHot; }
		int Get_Cursor_Width(void) { return CursorWidth; }
		int Get_Cursor_Height(void) { return CursorHeight; }
		int Get_Max_Width(void) { return MaxWidth; }
		int Get_Max_Height(void) { return MaxHeight; }
		void Set_Hotspot_X(int hotspotX) { MouseXHot = hotspotX; }
		void Set_Hotspot_Y(int hotspotY) { MouseYHot = hotspotY; }
		void Set_Cursor_Width(int width) { CursorWidth = width; }
		void Set_Cursor_Height(int height) { CursorHeight = height; }
		void Set_Max_Width(int width) { MaxWidth = width; }
		void Set_Max_Height(int height) { MaxHeight = height; }

		char* Get_Image_Buff(void) { return MouseCursor; }
		void* Get_Frame_Pointer() { return PrevCursor; }
		void Set_Frame_Pointer(void* frame) { PrevCursor = (char *)frame; }

		void RenderMouse(void);
// jmarshall end
	private:
		enum 	{
			CONDHIDE		= 1,
			CONDHIDDEN 	= 2,
		};
		void Low_Hide_Mouse(void);
		void Low_Show_Mouse(int x, int y);

		char						*MouseCursor;	// pointer to the mouse cursor in memory
		int						MouseXHot;		// X hot spot of the current mouse cursor
		int						MouseYHot;		// Y hot spot of the current mouse cursor
		int						CursorWidth;	// width of the mouse cursor in pixels
		int						CursorHeight;	// height of the mouse cursor in pixels

		char						*MouseBuffer;	// pointer to background buffer in memory
		int						MouseBuffX;		// pixel x mouse buffer was preserved at
		int						MouseBuffY;		// pixel y mouse buffer was preserved at
		int						MaxWidth;		// maximum width of mouse background buffer
		int						MaxHeight;		// maximum height of mouse background buffer

		int						MouseCXLeft;	// left x pos if conditional hide mouse in effect
		int						MouseCYUpper;	// upper y pos if conditional hide mouse in effect
		int						MouseCXRight;	// right x pos if conditional hide mouse in effect
		int						MouseCYLower;	// lower y pos if conditional hide mouse in effect
		char						MCFlags;			// conditional hide mouse flags
		char						MCCount;			// nesting count for conditional hide mouse

		GraphicViewPortClass	*Screen;			// pointer to the surface mouse was init'd with
		char *					PrevCursor;		// pointer to previous cursor shape
		int						MouseUpdate;
		int						State;

		char						*EraseBuffer;	// Buffer which holds background to restore to hidden page
		int						EraseBuffX;		// X position of the hidden page background
		int						EraseBuffY;		// Y position of the hidden page background
		int						EraseBuffHotX;	// X position of the hidden page background
		int						EraseBuffHotY;	// Y position of the hidden page background

		int						EraseFlags;		// Records whether mutex has been released

		CRITICAL_SECTION		MouseCriticalSection;  // Control for mouse re-enterancy
		unsigned					TimerHandle;
// jmarshall
private:
	struct	Image_t*			cursor_frames[MAX_CURSOR_FRAMES];
	struct  Image_t*			current_cursor;
	bool	isMouseVisible;
// jmarshall end
};

void __cdecl Mouse_Shadow_Buffer(WWMouseClass& mouse, GraphicViewPortClass& viewport, void* buffer, int x_pos, int y_pos, int hspot_x, int hspot_y, BOOL save);
void __cdecl Mouse_Draw(WWMouseClass& mouse, GraphicViewPortClass& viewport, int x_pos, int y_pos);
void* __cdecl Mouse_Set_Cursor(WWMouseClass& mouse, int hspot_x, int hspot_y, void* frame);

void Hide_Mouse(void);
// jmarshall
void Show_Mouse(bool clearPrevious = true);
// jmarshall end
void Conditional_Hide_Mouse(int x1, int y1, int x2, int y2);
void Conditional_Show_Mouse(void);
int Get_Mouse_State(void);
void *Set_Mouse_Cursor(int hotx, int hoty, int cursor);
int Get_Mouse_X(void);
int Get_Mouse_Y(void);

#endif
