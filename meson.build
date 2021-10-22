project('HostKit', 'c', version: '0.0.1')

winmod = import('windows')

src = [
    'src/writer/writers.c',
    'src/writer/writer_json.c',
    'src/writer/writer.c',
    'src/writer/writer_xml.c',
    'src/modules/modules.c',
    'src/modules/basic/host.c',
    'src/modules/basic/drives.c',
    'src/arguments.c',
    'src/util.c',
    'src/service.c',
    'src/persist.c',
    'src/main.c',
    winmod.compile_resources('src/hostkit.rc')
]

exe = executable('HostKit',
    src,
    link_args: 
        ['-static', 
         '-mconsole',
         '-lnetapi32']
)
