Blast Attack
============

## Download

```shell
$ git clone --recursive git@git.sr.ht:~johnnyrichard/blast-attack
```

## Dependencies

- meson
- ninja
- SDL2

## Run

```shell
$ meson setup builddir
$ meson compile -C builddir # or ninja -C builddir
$ ./builddir/blast-attack
```

## Tests

```shell
$ meson test -C builddir -v
```
