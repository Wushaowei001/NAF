/*
 * Copyright 2000-2015 Rochus Keller <mailto:rkeller@nmr.ch>
 *
 * This file is part of the CARA (Computer Aided Resonance Assignment,
 * see <http://cara.nmr.ch/>) NMR Application Framework (NAF) library.
 *
 * The following is the license that applies to this copy of the
 * library. For a license to use the library under conditions
 * other than those described here, please email to rkeller@nmr.ch.
 *
 * GNU General Public License Usage
 * This file may be used under the terms of the GNU General Public
 * License (GPL) versions 2.0 or 3.0 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in
 * the packaging of this file. Please review the following information
 * to ensure GNU General Public Licensing requirements will be met:
 * http://www.fsf.org/licensing/licenses/info/GPLv2.html and
 * http://www.gnu.org/copyleft/gpl.html.
 */

#if !defined(AFX_EVENT_H__3BCB87E2_D391_11D4_B823_00D00918E99C__INCLUDED_)
#define AFX_EVENT_H__3BCB87E2_D391_11D4_B823_00D00918E99C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Root/Message.h>
#include <Root/Resource.h>
#include <Root/Sequence.h>
#include <Lexi2/LxGlyph.h>
#include <string>

namespace Lexi2
{
	class Glyph;

	class FocusEvent : public Root::InputEvent
	{
	public:
		FocusEvent( bool in ):d_focusIn( in ),d_target( 0 ) {}
		~FocusEvent() {}
		bool focusIn() const { return d_focusIn; }
		void reset( bool in );
		Glyph* accepted() const { return d_target; }
		//* Mit den folgenden Methoden legt der Controller fest, wer effektiv den Fokus erh�lt.
		//.	GlyphWidget verwendet den accepted und nicht den send-to Target.
		void accept( Glyph* g ) { d_target = g; }
		//. Wird vom Handler aufgerufen, wenn dieser bereit ist, den Fokus abzugeben oder anzunehmen.
		void reject() { d_target = 0; }
		//. Analog zu accept, jedoch wenn der Handler den Fokus nicht annehmen oder abgeben will.
	private:
		bool d_focusIn;
		Root::ExRef<Glyph> d_target;
	};

	class MouseEvent : public Root::InputEvent
	{
	public:
		enum Button { Left, Mid, Right, Shift, Ctrl, Alt };
		typedef std::bitset<8> ButtonSet;

		enum Action { Press, Release, DblClick, Move };
		MouseEvent( Coord x, Coord y, const ButtonSet& b, Action = Press );
		~MouseEvent() {}

		Coord getX() const { return d_point[ DimX ]; }
		Coord getY() const { return d_point[ DimY ]; }
		bool isPressed(Button b) const { return d_buttons.test( b ); }
		bool isLeft() const { return isPressed( Left ); }
		bool isRight() const { return isPressed( Right ); }
		bool isMid() const { return isPressed( Mid ); }
		bool isShift() const { return isPressed( Shift ); }
		bool isCtrl() const { return isPressed( Ctrl ); }
		bool isAlt() const { return isPressed( Alt ); }
		bool isNoKey() const { return !isShift() && !isAlt() && !isCtrl(); }
		Coord getPos( Dimension d ) const { return d_point[ d ]; }
		bool mousePress() const { return d_action == Press; }
		bool mouseRelease() const { return d_action == Release; }
		bool mouseMove() const { return d_action == Move; }
		bool doubleClick() const { return d_action == DblClick; }
	private:
		Coord d_point[ MaxDim ];
		ButtonSet d_buttons;
		Action d_action;
	};

	class DragEvent : public MouseEvent
	{
	public:
		DragEvent( Coord x, Coord y, const ButtonSet& b, Coord sx, Coord sy,
			 Coord lx, Coord ly );
		~DragEvent() {}
		Coord getStartX() const {  return d_start[ DimX ]; }
		Coord getStartY() const {  return d_start[ DimY ]; }
		Coord getLastX() const {  return d_last[ DimX ]; }
		Coord getLastY() const {  return d_last[ DimY ]; }
		Coord getDeltaX() const { return getX() - d_last[ DimX ]; }
		Coord getDeltaY() const { return getY() - d_last[ DimY ]; }
		Coord getRelativeX() const { return getX() - d_start[ DimX ]; }
		Coord getRelativeY() const { return getY() - d_start[ DimY ]; }
	private:
		Coord d_start[ MaxDim ];
		Coord d_last[ MaxDim ];
	};

	class KeyEvent : public Root::InputEvent
	{
	public:
		bool isHelp() const;
		bool isMenu() const;
		bool isChar() const;
		bool isPageUp() const;
		bool isPageDown() const;
		bool isDown() const;
		bool isRight() const;
		bool isUp() const;
		bool isLeft() const;
		bool isEnd() const;
		bool isHome() const;
		bool isDelete() const;
		bool isEscape() const;
		bool isTab() const;
		bool isSpace() const;
		bool isReturn() const;
		bool isBackspace() const;

		enum Button { Shift, Ctrl, Alt };
		typedef std::bitset<8> ButtonSet;

		enum Action { Press, Release };
		KeyEvent( int key, const char* ascii, const ButtonSet& b, Action = Press );
		~KeyEvent() {}

		int getKey() const { return d_key; }
		const char* getChar() const { return d_ascii.c_str(); }
		bool isPressed(Button b) const { return d_buttons.test( b ); }
		bool isPlainKey() const { return d_buttons.none(); }
		bool isShift() const { return isPressed( Shift ); }
		bool isCtrl() const { return isPressed( Ctrl ); }
		bool isAlt() const { return isPressed( Alt ); }
		bool keyPress() const { return d_action == Press; }
		bool keyRelease() const { return d_action == Release; }
	private:
		ButtonSet d_buttons;
		int d_key;
		std::string d_ascii;
		Action d_action;
	};
}
#endif // !defined(AFX_EVENT_H__3BCB87E2_D391_11D4_B823_00D00918E99C__INCLUDED_)
