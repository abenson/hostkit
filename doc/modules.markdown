# Modules

## Writing Modules

Each module should perform one collection task. Unrelated collection tasks, such as file system enumeration and network device enumeration, should never be included in the same module.

Modules are not typically named, but are referred to by the entry point they provide.

Modules shall be self-contained, with one source file per module.

## Entry Points

While each module must have one entry point, multiple entry points can be defined for a module. This is especially useful for modules that have specific functionality for a given run mode. Entry points have the following form:

    int entry_point_name(BOOL verbose)
    {
        [...]

        if(error) {
            return error_code;
        } else {
            return 0;
        }
    }

Return code should be 0 if no error occurred. Currently defined error codes are as follows:

- *ERR_NONE*: No error occurred, equivalent to 0.
- *ERR_SYSFAIL*: An error occurred in the system, indicating an issue with the machine or an issue with the implementation of the module.
- *ERR_MODFAIL*: An error occurred inside the module.
- *ERR_NOTFOUND*: Something was not found, and the module could not successfully complete.
- *ERR_LOGFAIL*: Some error occurred in the logging system.
- *ERR_GENFAIL*: Some other error that does not fit well into the previous categories occurred.
- *ERR_NOTIMPL*: This function is not implemented yet.

## Supporting Functions

Supporting functions should be declared static. They should not be accessible outside of the module source file.

## Output


