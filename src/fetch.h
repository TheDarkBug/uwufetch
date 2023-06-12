/*
 *  UwUfetch is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef _FETCH_H_
#define _FETCH_H_
#include <stdbool.h>

#ifndef LIBFETCH_INTERNAL
	#ifdef __APPLE__
		#include <TargetConditionals.h> // for checking iOS
	#endif
	#include <dirent.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <unistd.h>
	#if defined(__APPLE__) || defined(__BSD__)
		#include <sys/sysctl.h>
		#if defined(__OPENBSD__)
			#include <sys/time.h>
		#else
			#include <time.h>
		#endif // defined(__OPENBSD__)
	#else		 // defined(__APPLE__) || defined(__BSD__)
		#ifdef __BSD__
		#else // defined(__BSD__) || defined(_WIN32)
			#ifndef _WIN32
				#ifndef __OPENBSD__
					#include <sys/sysinfo.h>
				#else	 // __OPENBSD__
				#endif // __OPENBSD__
			#else		 // _WIN32
				#include <sysinfoapi.h>
			#endif // _WIN32
		#endif	 // defined(__BSD__) || defined(_WIN32)
	#endif		 // defined(__APPLE__) || defined(__BSD__)
	#ifndef _WIN32
		#include <sys/ioctl.h>
		#include <sys/utsname.h>
		#include <pthread.h> // linux only right now
	#else									 // _WIN32
		#include <windows.h>
	#endif // _WIN32
#endif

// info that will be printed with the logo
struct info {
	char user[128],	 // username
			host[256],	 // hostname (computer name)
			shell[64],	 // shell name
			model[256],	 // model name
			kernel[256], // kernel name (linux 5.x-whatever)
			os_name[64], // os name (arch linux, windows, mac os)
			cpu_model[256], gpu_model[256][256],
			pkgman_name[64], // package managers string
			image_name[128];
	int target_width, // for the truncate_str function
			screen_width, screen_height, ram_total, ram_used,
			pkgs; // full package count
	long uptime;

#ifndef _WIN32
	struct utsname sys_var;
#endif // _WIN32
#ifndef __APPLE__
	#ifdef __linux__
	struct sysinfo sys;
	#else // __linux__
		#ifdef _WIN32
	struct _SYSTEM_INFO sys;
		#endif // _WIN32
	#endif	 // __linux__
#endif		 // __APPLE__
#ifndef _WIN32
	struct winsize win;
#else	 // _WIN32
	int ws_col, ws_rows;
#endif // _WIN32
};

// Args struct for get_something thread oriented functions
struct thread_varg {
	char* buffer;
	struct info* user_info;
	FILE* cpuinfo;
	bool thread_flags[8];
};

#ifdef __DEBUG__
void set_libfetch_log_level(int level);
	#define SET_LIBFETCH_LOG_LEVEL(level) set_libfetch_log_level(level)
#else
	#define SET_LIBFETCH_LOG_LEVEL(level)
#endif

// Retrieves system information
struct info* get_all();

#endif // _FETCH_H_
