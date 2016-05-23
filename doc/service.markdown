# Service Mode

In addition to the standardalone run modes, two service modes are available. In this mode, the application will install itself as a service, run as though it were in standalone mode, and then clean itself up. This will be most useful when a method to run as system is not available, such as  being able to `psexec -s`. There will also be a persistent service mode, in which case it will install as a service, and will allow interaction via a named pipe or callback server.

## Service Mode 1 (/runAsService)

The /runAsService flag tells the tool to install itself as a service, execute according the rest of the flags, then clean up.

## Service Mode 2 (/persistAsService)

When run with the /persistAsService option, the tool will install as a service and behave as though the /persist option had been specified. See doc/persist.txt for more details on this mode.

