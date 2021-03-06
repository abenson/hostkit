                      _  _  ___  ___ _____ _  _____ _____ 
                     | || |/ _ \/ __|_   _| |/ /_ _|_   _|
                     | -- | (_) \__ \ | | | ' | | |  | |  
                     |_||_|\___/|___/ |_| |_|\_\___| |_|  
                                                          

# Introduction

HostKit (temporary name) is a small toolkit to help pull certain information
from a host.

# Targeted Platforms

HostKit is designed to run on Windows Vista/2008 targets and later. Future 
versions may also have limited support for XP/2003.

# Desired Information

## System  

- Hostname
- Domain/Workgroup
- OS Version/Service Pack

## File Listings

- Name/Path
- Size
- MAC Times
- Owner

## Network

- Interface Name
- IPs
- Status

# Building

You will need the `x86-64-w64-mingw32` and/or `i686-w64-mingw32` cross-compilers.

To build from source,

	$ make

To build 32-bit, specify WIN32=yes on the make command line.

	$ make WIN32=yes

By default the makefile targets 64-bit.
