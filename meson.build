project('blast-attack', 'c')

cc = meson.get_compiler('c')

srcs = [ 'src/main.c'
       , 'src/controller.c'
       , 'src/player.c'
       , 'src/screen.c'
       ]

m_dep    = cc.find_library('m', required: false)
sdl2_dep = dependency('sdl2') 

deps = [ sdl2_dep , m_dep ]

executable('blast-attack',
           sources: srcs,
           dependencies: deps)

test_incdir = include_directories('src')
munit_dep = dependency('munit', fallback: ['munit', 'munit_dep'])

controller_test = executable('controller-test', 
                    'src/controller.c',
                    'test/controller-test.c',
                    include_directories: test_incdir,
                    dependencies: [sdl2_dep, munit_dep])

test('controller test', controller_test)
