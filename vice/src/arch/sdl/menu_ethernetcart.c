/*
 * menu_ethernetcart.c - Ethernet Cart menu for SDL UI.
 *
 * Written by
 *  Hannu Nuotio <hannu.nuotio@tut.fi>
 *  Marco van den Heuvel <blackystardust68@yahoo.com>
 *
 * This file is part of VICE, the Versatile Commodore Emulator.
 * See README for copyright notice.
 *
 *  This program is free software; you can redistribute it and/or modify
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
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 *  02111-1307  USA.
 *
 */

#include "vice.h"

#ifdef HAVE_PCAP

#include <stdio.h>

#include "types.h"

#include "lib.h"
#include "menu_common.h"
#include "menu_ethernetcart.h"
#include "rawnet.h"
#include "resources.h"
#include "uimenu.h"

/* Common menus */

UI_MENU_DEFINE_TOGGLE(ETHERNETCART_ACTIVE)
UI_MENU_DEFINE_RADIO(ETHERNETCARTMode)
UI_MENU_DEFINE_RADIO(ETHERNETCARTBase)

static const ui_menu_entry_t ethernetcart_mode_menu[] = {
    { "RR-Net compatible",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTMode_callback,
      (ui_callback_data_t)1 },
    { "TFE compatible",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTMode_callback,
      (ui_callback_data_t)0 },
    SDL_MENU_LIST_END
};

static const ui_menu_entry_t ethernetcart_base64_menu[] = {
    { "$DE00",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0xde00 },
    { "$DE10",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0xde10 },
    { "$DE20",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0xde20 },
    { "$DE30",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0xde30 },
    { "$DE40",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0xde40 },
    { "$DE50",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0xde50 },
    { "$DE60",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0xde60 },
    { "$DE70",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0xde70 },
    { "$DE80",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0xde80 },
    { "$DE90",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0xde90 },
    { "$DEA0",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0xdea0 },
    { "$DEB0",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0xdeb0 },
    { "$DEC0",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0xdec0 },
    { "$DED0",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0xded0 },
    { "$DEE0",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0xdee0 },
    { "$DEF0",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0xdef0 },
    { "$DF00",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0xdf00 },
    { "$DF10",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0xdf10 },
    { "$DF20",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0xdf20 },
    { "$DF30",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0xdf30 },
    { "$DF40",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0xdf40 },
    { "$DF50",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0xdf50 },
    { "$DF60",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0xdf60 },
    { "$DF70",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0xdf70 },
    { "$DF80",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0xdf80 },
    { "$DF90",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0xdf90 },
    { "$DFA0",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0xdfa0 },
    { "$DFB0",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0xdfb0 },
    { "$DFC0",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0xdfc0 },
    { "$DFD0",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0xdfd0 },
    { "$DFE0",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0xdfe0 },
    { "$DFF0",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0xdff0 },
    SDL_MENU_LIST_END
};

static const ui_menu_entry_t ethernetcart_base20_menu[] = {
    { "$9800",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0x9800 },
    { "$9810",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0x9810 },
    { "$9820",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0x9820 },
    { "$9830",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0x9830 },
    { "$9840",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0x9840 },
    { "$9850",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0x9850 },
    { "$9860",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0x9860 },
    { "$9870",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0x9870 },
    { "$9880",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0x9880 },
    { "$9890",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0x9890 },
    { "$98A0",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0x98a0 },
    { "$98B0",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0x98b0 },
    { "$98C0",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0x98c0 },
    { "$98D0",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0x98d0 },
    { "$98E0",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0x98e0 },
    { "$98F0",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0x98f0 },
    { "$9C00",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0x9c00 },
    { "$9C10",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0x9c10 },
    { "$9C20",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0x9c20 },
    { "$9C30",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0x9c30 },
    { "$9C40",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0x9c40 },
    { "$9C50",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0x9c50 },
    { "$9C60",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0x9c60 },
    { "$9C70",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0x9c70 },
    { "$9C80",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0x9c80 },
    { "$9C90",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0x9c90 },
    { "$9CA0",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0x9ca0 },
    { "$9CB0",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0x9cb0 },
    { "$9CC0",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0x9cc0 },
    { "$9CD0",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0x9cd0 },
    { "$9CE0",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0x9ce0 },
    { "$9CF0",
      MENU_ENTRY_RESOURCE_RADIO,
      radio_ETHERNETCARTBase_callback,
      (ui_callback_data_t)0x9cf0 },
    SDL_MENU_LIST_END
};

const ui_menu_entry_t ethernetcart_menu[] = {
    { "Ethernet Cart emulation",
      MENU_ENTRY_RESOURCE_TOGGLE,
      toggle_ETHERNETCART_ACTIVE_callback,
      NULL },
    { "Ethernet Cart mode",
      MENU_ENTRY_SUBMENU,
      submenu_radio_callback,
      (ui_callback_data_t)ethernetcart_mode_menu },
    { "Ethernet Cart base address",
      MENU_ENTRY_SUBMENU,
      submenu_radio_callback,
      (ui_callback_data_t)ethernetcart_base64_menu },
    SDL_MENU_LIST_END
};

const ui_menu_entry_t ethernetcart20_menu[] = {
    { "Ethernet Cart emulation",
      MENU_ENTRY_RESOURCE_TOGGLE,
      toggle_ETHERNETCART_ACTIVE_callback,
      NULL },
    { "Ethernet Cart mode",
      MENU_ENTRY_SUBMENU,
      submenu_radio_callback,
      (ui_callback_data_t)ethernetcart_mode_menu },
    { "Ethernet Cart base address",
      MENU_ENTRY_SUBMENU,
      submenu_radio_callback,
      (ui_callback_data_t)ethernetcart_base20_menu },
    SDL_MENU_LIST_END
};

#endif /* HAVE_PCAP */