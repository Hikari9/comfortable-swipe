#ifndef __comfortable_swipe_defines__
#define __comfortable_swipe_defines__
/** All global #define statements go here */
/*
Comfortable Swipe
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
/**
 * COMFORTABLE_SWIPE_CONFIG
 *
 * This definition points to the location of the configuration file.
 * A warning will be issued to the compiler if you do not define this at compile
 * time.
 */
#ifndef COMFORTABLE_SWIPE_CONFIG
#pragma message "Please define COMFORTABLE_SWIPE_CONFIG during compilation!"
// just point to config from source directory
#define COMFORTABLE_SWIPE_CONFIG "/dev/null"
#endif /* COMFORTABLE_SWIPE_CONFIG */
/**
 * COMFORTABLE_SWIPE_AUTOSTART
 *
 * This definition points to the location of the autostart (.desktop) file.
 * A warning will be issued to the compiler if you do not define this at compile
 * time.
 */
#ifndef COMFORTABLE_SWIPE_AUTOSTART
#pragma message "Please define COMFORTABLE_SWIPE_AUTOSTART during compilation!"
// just point to autostart from source directory
#define COMFORTABLE_SWIPE_AUTOSTART "/dev/null"
#endif /* COMFORTABLE_SWIPE_AUTOSTART */
/**
 * COMFORTABLE_SWIPE_VERSION
 *
 * This is an optional definition for the version string of comfortable-swipe.
 */
#ifndef COMFORTABLE_SWIPE_VERSION
#pragma message "Please define COMFORTABLE_SWIPE_VERSION during compilation!"
#define COMFORTABLE_SWIPE_VERSION "v(UNKNOWN)"
#endif /* COMFORTABLE_SWIPE_VERSION */

#endif /* __comfortable_swipe_defines__ */
