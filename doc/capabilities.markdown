# Capabilities

This will describe each module and their function.

## Basic

- System
	- Hostname, implemented
	- Domain, implemented
	- OS, implemented
	- Version, implemented
	- Machine Type, implemented
	- Processor Type, implemented
	- Count of Processors, implemented
	- Memory, implemented
	- Detect VM
- Drives
	- Physical Device, implemented
	- Assigned Drive Letter, implemented
	- Filesystem, implemented
	- Volume serial, implemented
	- Model
	- Serial

## Standard

- Filesystem (%PATH%)
	- Name
	- Folder
	- Size
	- SHA-256
	- Owner
	- Verbose: ACLs¹
- Services
	- Name
	- Display Name
	- Description
	- Status
	- Type
	- StartType
- Processes
	- PID
	- Name
	- Path
	- Owner
	- Loaded Modules¹
- Network Info
	- Gateways¹
	- Routes¹
	- DNS Servers¹
- Network Devices
	- Name
	- HW Address
	- IPs¹
	- Subnet Mask
- DNS Cache
	- Name
	- Type
- Autoruns
	- Location
	- Name
	- Value
- USBs
	- Serial
	- Vendor
	- Date

## Full

- Filesystem (everything)


# Notes

¹ ~~This may (read: will) require an implementation change to add subitems.~~ Implementation now supports multiple levels of subitems.
