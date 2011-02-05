target  = 'mpool'
sources = [Glob('*.c')]
env = Environment(CPPFLAGS=['-Wall', '-g', '-O2', '-std=c99', '-fPIC'])
test = env.SharedLibrary(target, sources)
