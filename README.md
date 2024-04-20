# Backlog
Yet another #TODO app. Yeah yeah, I know, there are toooo many todo apps out
there. Even I got a few: [jTodo](https://github.com/AravindVasudev/jTodo),
[link-share](https://github.com/AravindVasudev/link-share), etc. I'm just
bored and trying to get a hang of C++, that's it. This code is not intended for
human consumption.

## Build

The project uses [buck2](https://buck2.build/docs/getting_started/#installing-buck2) as its build system. Why you ask? Because why not?

```sh
$ buck2 build //...
```

## Run

```sh
$ buck2 run //:backlog
```