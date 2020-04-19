#ifndef __comfortable_swipe_defines__
#define __comfortable_swipe_defines__
// Place #define statements here

/*
Comfortable Swipe (as of v1.2.0)
by Rico Tiongson

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef COMFORTABLE_SWIPE_CONFIG
#warning Please define COMFORTABLE_SWIPE_CONFIG during compilation!\
    (g++ -DCOMFORTABLE_SWIPE_CONFIG="\"/home/$USER/.config/comfortable-swipe.conf\"")
#endif /* COMFORTABLE_SWIPE_CONFIG */

#ifndef COMFORTABLE_SWIPE_AUTOSTART
#warning Please define COMFORTABLE_SWIPE_AUTOSTART during compilation!\
    (g++ -DCOMFORTABLE_SWIPE_AUTOSTART="\"/home/$USER/.config/autostart/comfortable-swipe.desktop\"")
#endif /* COMFORTABLE_SWIPE_AUTOSTART */

#ifndef COMFORTABLE_SWIPE_VERSION
#warning COMFORTABLE_SWIPE_VERSION is not defined
#define COMFORTABLE_SWIPE_VERSION "v(UNKNOWN)"
#endif /* COMFORTABLE_SWIPE_VERSION */

#endif /* __comfortable_swipe_defines__ */
