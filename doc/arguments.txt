                   _   ___  ___ _   _ __  __ ___ _  _ _____ ___ 
                  /_\ | _ \/ __| | | |  \/  | __| \| |_   _/ __|
                 / _ \|   / (_ | |_| | |\/| | _|| .` | | | \__ \
                /_/ \_\_|_\\___|\___/|_|  |_|___|_|\_| |_| |___/
                                                                
# Arguments

A complete list of arguments and their behaviors follow.

# Run Modes

These options specify what run mode the application will run in. These are better described in in arch.txt.

- **/basic** Basic mode, only collects some basic system information.
- **/standard** Standard mode. Will basically enumerate processes, services, files in %SYSTEMHOME% and Documents and Settings. Default mode if none are specified.
- **/full** Will enumerate all files, modules loaded by processes, etc. 

# Output Options

These specify the format and where the results are logged to. 

- **/filename** *<filename>* Default is hostname.
- **/writer** *<writername>* Currently implemented options are JSON and XML. Specify list to see a list of available options. Default is JSON.

# Service

- **/service** Run as a service. Will install itself as a service, execute, and then clean up.

# Persistence

- **/persist** Don't immediately execute, but wait for instructions via named pipe or server. 
- **/server** *<server>* Call back to a server for instructions. Will not open the named pipe unless instructed.
- **/pipe** *<pipe>* Create a named pipe for control. Default pipe is *hkadmin*.

Only valid options with /persist are /server, /pipe and /service. /pipe and /server can only be used in combination with /persist. 
