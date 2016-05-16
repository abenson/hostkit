# Architecture

## Run Modes

The main module of the application will handle arguments parsing and calling the modules that pertain to the flags. To add a new module to be called, it's entry point should be added to the list to be called under which section it should be called under. The goal of this is compile time modularity.

There will be three standard modes to run the tool. Basic, Standard, and Full. Each will increase in detail, respectively.

## Basic

Basic will do a function test and identify the machine.

## Standard

Standard will pull limited information about the machine. It will include the same information included in Basic, as well.

## Full

Full will include Basic, Standard, but collect the rest of the available information from the host. This will run all of the modules available, with some caveats.

## Details

Each module can be asked to provide additional details about what it is collecting that otherwise would be left unreported. This may be flags set for a file, for example.

# Adding New Modules

There are 6 lists modules can be added to:

- basic
- basic_only
- standard
- standard_only
- full
- full_only

To add a new module to each mode list, simply add its entry point to the list before the last line (the last line will always be NULL).  Example:

    /* Standard Module List */
    struct module standard[] = {
        network_info,
        my_module,
        NULL};


## Exclusivity

Some modules may behave differently depending on whether they are being run in a basic, standard, or full scan.

With the exception of the *_only* lists, each mode will include the modules listed in the lesser modes. For example, the **basic** run mode will run all of the modules listed in *basic* and *basic_only*. **standard** will run all of the modules listed in *basic*, *standard*, and *standard_only*. As expected, **full** will run all of the modules in *basic*, *standard*, *full*, and *full_only*.

This is necessary for some modules that will behave differently depending on run mode. An example, file information may include system and home directories when run in standard mode, but in full mode would include all folders. To avoid duplicating the system and home directories when run in full mode, the file information module would have two entry points, *file_info* and *file_info_full*.  Example.


    /* Standard *Only* Module List */
    struct module standard_only[] = {
        file_info,
        my_standard_module,
        NULL};

    /* Full *Only* Module List */
    struct module full_only[] = {
        file_info_full,
        my_full_module,
        NULL};

# Fin

