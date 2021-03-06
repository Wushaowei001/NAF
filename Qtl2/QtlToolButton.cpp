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

#include <QToolButton>
#include <QAction>
#include <QMenu>
#include "QtlToolButton.h"
#include <Script2/QtObject.h>
#include <Script2/QtValue.h>
#include <Script/Util.h>
using namespace Qtl;
using namespace Lua;
int ToolButton::defaultAction(lua_State * L) // const : QAction *
{
    QToolButton* obj = QtObject<QToolButton>::check( L, 1);
    QtObject<QAction>::create( L, obj->defaultAction() );
	return 1;
}
int ToolButton::menu(lua_State * L) // const : QMenu *
{
    QToolButton* obj = QtObject<QToolButton>::check( L, 1);
    QtObject<QMenu>::create( L, obj->menu() );
	return 1;
}
int ToolButton::setMenu(lua_State * L) // ( QMenu * menu )
{
    QToolButton* obj = QtObject<QToolButton>::check( L, 1);
    QMenu* menu = QtObject<QMenu>::check( L, 2);
	obj->setMenu( menu );
	return 0;
}
static const luaL_reg _ToolButton[] = 
{
	{ "defaultAction", ToolButton::defaultAction },
	{ "menu", ToolButton::menu },
	{ "setMenu", ToolButton::setMenu },
	{ 0, 0 }
};
void ToolButton::install(lua_State * L){
    QtObject<QToolButton,QAbstractButton>::install( L, "QToolButton", _ToolButton );
}
