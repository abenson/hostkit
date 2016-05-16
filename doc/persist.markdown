# Persistence

If the /persist command line flags are provided, the application will remain resident and only perform actions when instructed to do so over either via 1) reach back server 2) named pipe.

If /persist is specified along with /service, the application will be installed a service, ensuring it will persist across reboots.

## Reach back Server

The application can be configured to connect to a server to receive commands from.

## Named Pipes

The application will be default create a named pipe when running in persist mode.


