# Output

## Overview

Currently planned output formats are JSON, YAML, and XML, with the default being JSON. From within the application, this should all be abstracted by the logging system. The output format is specified when the results file is initially created. The output will have a very rigid structure, both due to limitations with the library (a full spec will not be implemented) but more importantly to limit complexity of output files, making them easier to parse.

## File Structure

The resulting file structure will be rigid and simple. The overall structure, regardless of format, will be as such:

    Section1:
        Item1:
            Key, Value
            ...
        Item2:
            Key, Value
            ...
        ...
    Section2:
        ...

Each module will have its own section. Each module should have only one section.

## API

User exposed API provides the ability to create a results file with a certain format, create and close a section, create and close a new item, and add key/value pairs to the item.

The file and format should be handled by the host application, with only the section, item, and kv calls handled by the module.

A module would generate output like that shown above with calls similar to the follow.

    /* Assuming this in the host app */
    log_t *loghdnl;
    loghndl = open_log(filename, format);

    ...

    /* This is in the module code .... */

    open_section(loghndl, "Section1");

    open_item(loghndl);
    add_value(loghndl, "Key", "Value");
    close_item(loghdnl);

    open_item(loghndl);
    add_value(loghndl, "Key", "Value");
    close_item(loghndl);

    close_section(loghndl);

    open_section(loghndl, "Section2");
    /* and so on */

This would generate appropriate output for the specified format.

## Output Formats

Currently, only JSON, YAML, and XML are planned to be implemented. Each output module needs to implement the following functions:

- begin: Any pre-output actions, such as a file header, also gives an opportunity to allocate and initialize the moduleData structure.
- end: Any post-output actions, like begin. Also deallocate the structures from begin.
- open_section: Begin a section.
- close_section: End a section.
- open_item: Begin an item within the section.
- close_item: Close an item within the section.
- add_value: Add a key/value pair to an item.


Prepend the name of the format to these to avoid symbol conflicts.

A module's identifier and methods are registered in the modules structure. For example, if a module "foo" is implemented, it would be registered in the structure as follows. The last line will always be NULL.

    #include "modules/foo.h"
    struct module modules[] = {
        {"foo", foo_begin, foo_end, foo_open_section, foo_close_section, foo_open_item, foo_close_item, foo_add_value},
        ...
        {NULL, NULL, NULL, NULL, NULL, NULL}
    };

