#!/bin/sh
bindir=$(pwd)
cd /home/willy/Documents/Github/WW1AirPlane-OpenGL/src/
export 

if test "x$1" = "x--debugger"; then
	shift
	if test "xYES" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		/usr/bin/gdb -batch -command=$bindir/gdbscript --return-child-result /home/willy/Documents/Github/WW1AirPlane-OpenGL/src/main-glfw 
	else
		"/home/willy/Documents/Github/WW1AirPlane-OpenGL/src/main-glfw"  
	fi
else
	"/home/willy/Documents/Github/WW1AirPlane-OpenGL/src/main-glfw"  
fi
