flags = [
        '-Wall',
        #        '-Wextra',
        '-Werror',
        '-DUSE_CLANG_COMPLETER',
        '-std=c++11',
        '-x', 'c++',
        '-I../lib',
    ]

def FlagsForFile(fname):
    return {
            'flags' : flags,
            'do_cache' : True
        }
